#include "Infection.h"

#include "DataTransferPDU.h"
#include "InfectionSignals.h"

using namespace std;

namespace Infection {

    Define_Module(Infection);

    unsigned int Flow::cepID = 1;

    Flow::Flow(
            string DIF,
            string SRC,
            string DST,
            string _QoS,
            double rate,
            int avgPDU,
            int varPDU,
            int nParts,
            int nRec) :
        QoS (_QoS),
        srcAddr(Address(SRC.c_str(), DIF.c_str())),
        dstAddr(Address(DST.c_str(), DIF.c_str())),
        avgWT(1.0/rate),
        minS(avgPDU - varPDU),
        maxS(avgPDU + varPDU),
        current(0),
        parts(nParts),
        rec(nRec),
        fcepID(Flow::cepID++),
        secNum(0) {
            connID.setSrcCepId(1);
            connID.setDstCepId(-1);
            connID.setQoSId(_QoS);
          //  cout << minS << " " << maxS << endl;
    }

    pduT Flow::getPDU(bool record) {
        //int size = 1024;
        int size = intuniform(minS, maxS);

        pduT ret;
        ret.wT = 8*(size+11) * avgWT * exponential(1);

        //size = 11;
        //ret.wT = 100;

       // ret.wT = 8*(size+40) * avgWT * (4+ exponential(1))/5.0;
       // ret.wT = 8*(size+22) * avgWT * uniform(0.9,1.15);
        //ret.wT = 8*(size+20) * avgWT;
        //ret.wT = size * avgWT;

        if(current == 0) { secNum++; }
        DataTransferPDU * pdu = new InfectedDataTransferPDU( record && current < rec, fcepID, "InfectedPDU");

        pdu->setConnId(connID);
        pdu->setSrcAddr(srcAddr);
        pdu->setDstAddr(dstAddr);
        pdu->setSrcApn(srcAddr.getApn());
        pdu->setDstApn(dstAddr.getApn());
        pdu->setSeqNum(secNum);

        UserDataField * ud = new UserDataField();

        ud->setCompleteSDU(true);
        ud->setNoLength(false);
        ud->setSduSeqNumPresent(true);
        ud->setSduSeqNum(secNum);
        pdu->encapsulate(ud);

        pdu->setByteLength(size);

       // ret.wT = 5555555;
       // pdu->setByteLength(0);

        ret.pdu = pdu;

        current++;
        if(current >= parts) { current = 0;}
        connID.setSrcCepId(current+1);


        return ret;
    }

    commMsg::commMsg(Flow * _f) : f(_f) {}

    void Infection::initialize() {
        double iniT = par("iniTime").doubleValue();

        if(iniT<0 || par("infectedIPC").stdstringValue() == "") { return; }

        finTime = par("finTime").doubleValue();

        emitSignals = par("signal").boolValue();
        if(emitSignals) { signal = registerSignal("InfectionSignal"); }

        markIniT = par("markIniT").doubleValue();
        markFinT = par("markFinT").doubleValue();

        cModule * mod = this->getParentModule()->getSubmodule(par("infectedIPC").stringValue());
        if(mod==NULL) { return; }

        cModule * rmt = mod->getSubmodule("relayAndMux")->getSubmodule("rmt");

        rmt->addGate("infGate", cGate::INOUT, false);
        cGate * modIn = rmt->gateHalf("infGate", cGate::INPUT);
        cGate * modOut = rmt->gateHalf("infGate", cGate::OUTPUT);

        cGate * In = gateHalf("g", cGate::INPUT);
        cGate * Out = gateHalf("g", cGate::OUTPUT);

        modOut->connectTo(In);
        Out->connectTo(modIn);

        string DIF = mod->par("difName");
        string SRC = mod->par("ipcAddress");

        cXMLElement* Xml = NULL;
        if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
            Xml = par("data").xmlValue();
        } else { error("data parameter not initialized!"); }

        double linkRate = par("linkRate").doubleValue();
        double usage = par("usage").doubleValue();

//        cout << "BaseRate : " << linkRate << " | Usage : "<< usage << endl;
        double unitRate = linkRate * usage;

        cXMLElementList flowsXML = Xml->getChildrenByTagName("flow");
        for(cXMLElement * n : flowsXML) {
            string DST = "";
            string QoS = VAL_MGMTQOSID;

            DST = n->getAttribute("dstAddr");
            if (DST == "") {
                error("Error parsing Infected flow. Its dstAddr is missing!"); }
            if(DST == SRC) { continue; }

            if (n->getAttribute("qos")) { QoS = n->getAttribute("qos"); }

            int N = 1, rec = 1, pduS = 1024, pduSv = 0;
            double rate = 1.0;

            if (n->getAttribute("N") && atoi(n->getAttribute("N")) > 0) {
                N = atoi(n->getAttribute("N")); }
            if (n->getAttribute("rec") && atoi(n->getAttribute("rec")) > 0) {
                rec = atoi(n->getAttribute("rec")); }

            if (n->getAttribute("pduSize") && atoi(n->getAttribute("pduSize")) > 0) {
                pduS = atoi(n->getAttribute("pduSize")); }
            if(pduS < 50) { pduS = 50; }

            if (n->getAttribute("pduSizeVar") && atoi(n->getAttribute("pduSizeVar")) > 0) {
                pduSv = atoi(n->getAttribute("pduSizeVar")); }
            if(pduSv > pduS) { pduSv = pduS - 1; }

            if (n->getAttribute("rate") && atof(n->getAttribute("rate")) > 0) {
                rate = atof(n->getAttribute("rate")); }
            if(rate <= 0) { continue; }

            Flow * f = new Flow(DIF, SRC, DST, QoS, unitRate*rate, pduS, pduSv, N, rec);
            flows.push_back(f);
            scheduleAt(iniT + uniform(0, pduS/unitRate), new commMsg(f));

  //          cout << "LinkRate : " << unitRate << " | FlowRate : "<< (unitRate*rate) << " (" << rate << ")" << endl;
        }

    }

    void Infection::handleMessage(cMessage *msg) {
        if(commMsg * m = dynamic_cast<commMsg *>(msg)) {
            simtime_t now = simTime();
            if(now >= finTime) { delete msg; return; }

            bool record = now >= markIniT && now < markFinT;

            pduT k = m->f->getPDU(record);

            scheduleAt(now + k.wT, msg);
            send(k.pdu, "g$o");
            if(emitSignals) { emit(signal, new SendInfMsg(
                    k.pdu->getSrcAddr().getIpcAddress().getName(),
                    k.pdu->getDstAddr().getIpcAddress().getName(),
                    k.pdu->getConnId().getSrcCepId(),
                    m->f->QoS)
            );}
            return;
        }
        delete msg;
    }

    void Infection::finish() {
        for(Flow * f : flows) { delete f; }
    }
}
