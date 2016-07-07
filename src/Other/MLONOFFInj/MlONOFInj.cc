#include "MlONOFInj.h"
#include "MlInj_PDU.h"
#include "./SigMessages.h"

Define_Module(MlONOFInj);

void MlONOFInj::initialize() {
    double ini = par("ini").doubleValue();
    fin = par("fin").doubleValue();
    string infectedIPC = par("infectedIPC").stdstringValue();
    if(ini < 0 || fin <= ini || infectedIPC == "") { return; }

    wPerBit = 1/par("infRate").doubleValue();
    maxSimult = par("maxSimult").longValue();
    curSimult = 0;

    double rateMult = par("rateMult").doubleValue();

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else { return; }

    //Connect to infected ipcp
    cModule * mod = this->getParentModule()->getSubmodule(infectedIPC.c_str());
    if(mod == nullptr) { return; }
    cModule * rmt = mod->getSubmodule("relayAndMux")->getSubmodule("rmt");
    rmt->addGate("infGate", cGate::INOUT, false);
    cGate * modIn = rmt->gateHalf("infGate", cGate::INPUT);
    cGate * modOut = rmt->gateHalf("infGate", cGate::OUTPUT);
    cGate * In = gateHalf("g", cGate::INPUT);
    cGate * Out = gateHalf("g", cGate::OUTPUT);
    modOut->connectTo(In);
    Out->connectTo(modIn);

    //Register Signal
    signal = registerSignal("InjSignal");

    //Initialize parameters
    connID.setDstCepId(-1);

    dif = mod->par("difName").stdstringValue();
    src = mod->par("ipcAddress").stdstringValue();
    srcAddr = Address(src.c_str(), dif.c_str());


    int flowId = 0;
    int set = 0;

    //Read flows config
    cXMLElementList flowsXML = Xml->getChildrenByTagName("flowSet");
    for(cXMLElement * n : flowsXML) {
        string xSrc = n->getAttribute("src");
        string xDst = n->getAttribute("dst");
        string xQoS = n->getAttribute("QoS");
        string xN = n->getAttribute("N");
        string xR = n->getAttribute("R");
        string xD = n->getAttribute("D");
        string xK = n->getAttribute("K");
        string xPduMin = n->getAttribute("pduMin");
        string xPDUMax = n->getAttribute("pduMax");

        string xRand = n->getAttribute("rand");

        if(xSrc != src) { continue; }
        if(xDst == src || xDst == "") { continue; }
        if(xQoS == "") { continue; }

        if(xN == "" ) { continue; }
        int N = atoi(xN.c_str());
        if( N < 1) { continue; }

        if(xR == "" ) { continue; }
        double R = atof(xR.c_str());
        if( R <= 0) { continue; }

        if(xD == "" ) { continue; }
        double D = atof(xD.c_str());
        if( D <= 0) { continue; }

        if(xK == "" ) { continue; }
        double K = atof(xK.c_str());
        if( K <= 0) { continue; }

        if(xPduMin == "" ) { continue; }
        int pduMin = atoi(xPduMin.c_str());
        if( pduMin < 50) { continue; }

        if(xPDUMax == "" ) { continue; }
        int pduMax = atoi(xPDUMax.c_str());
        if( pduMax < pduMin) { continue; }

        int method = 0;
        if(xRand == "uniform") { method = 0; }

        flowSets.push_back(OF_FlowSet(flowId, method, xDst, xQoS, N, R*rateMult, D, K, pduMin, pduMax));
        scheduleAt(ini, new OF_FlowNext_Msg(set++));

    }
}

void MlONOFInj::handleMessage(cMessage *msg) {
    if(OF_FlowNext_Msg * m = dynamic_cast<OF_FlowNext_Msg *>(msg)) {
        if(simTime() >= fin) { delete m; return; }

        OF_FlowSet & fset = flowSets[m->fset];
        double W = fset.startNext();
        OF_Flow & f = fset.flows[fset.cN];
        emit(signal, new SigFlow(src, fset.dst, fset.QoS, f.flowId, true, 1.0/f.interPDU));

        scheduleAt(simTime(), new OF_PDUNext_Msg(m->fset, fset.cN));
        scheduleAt(simTime()+W, msg);
        return;
    }

    if(OF_PDUNext_Msg * m = dynamic_cast<OF_PDUNext_Msg *>(msg)) {
        OF_FlowSet & fset = flowSets[m->fset];
        OF_Flow & f = fset.flows[m->findex];


        int size = f.pduSize;
        if(f.remaining < size) { size = f.remaining; }

        //Create new PDU
        MlInj_PDU * pdu = new MlInj_PDU();
        connID.setQoSId(fset.QoS);
        connID.setSrcCepId(f.flowId);
        pdu->setConnId(connID);
        pdu->setSrcAddr(srcAddr);
        pdu->setSrcApn(srcAddr.getApn());
        dstAddr = Address(fset.dst.c_str(), dif.c_str());
        pdu->setDstAddr(dstAddr);
        pdu->setDstApn(dstAddr.getApn());
        if(f.secN <= 0) { pdu->first = true; }
        pdu->setSeqNum(f.secN);
        UserDataField * ud = new UserDataField();
        ud->setCompleteSDU(true);
        ud->setNoLength(false);
        ud->setSduSeqNumPresent(true);
        ud->setSduSeqNum(f.secN);
        pdu->encapsulate(ud);
        int bytesize = ceil(size/8);
        pdu->setByteLength(bytesize);
        pdu->setHopCount(0);
        f.secN++;
        scheduleAt(simTime(), pdu);
        emit(signal, new SigPDU(src, fset.dst, fset.QoS, f.flowId, 0, bytesize, 0.0) );

        f.remaining -= size;
        if(f.remaining > 0) {
            scheduleAt(simTime() + f.interPDU, m);
        } else {
            emit(signal, new SigFlow(src, fset.dst, fset.QoS, f.flowId, false, 1.0/f.interPDU));
            delete m;
        }
        return;
    }

    if(MlInj_PDU * m = dynamic_cast<MlInj_PDU *>(msg)) {
        if(curSimult >= maxSimult) {
            q.push(m);
        } else {
            curSimult++;
            int bLen = m->getBitLength()+88;

            send(msg, "g$o");
            scheduleAt(simTime()+bLen * wPerBit, new OF_IRed());
        }
        return;
    }

    if(dynamic_cast<OF_IRed *>(msg) != nullptr) {
        if(!q.empty()) {
            cPacket * p = q.front();
            q.pop();

            int bLen = p->getBitLength()+88;

            send(p, "g$o");
            scheduleAt(simTime()+bLen * wPerBit, msg);
        } else {
            curSimult--;
            delete msg;
        }
        return;
    }
}
