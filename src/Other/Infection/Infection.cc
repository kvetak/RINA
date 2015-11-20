#include "Infection.h"

#include "DataTransferPDU.h"
#include "InfectionSignals.h"

using namespace std;

namespace Infection {

    Define_Module(Infection);

    unsigned int FlowInstance::cepID = 1;

    FlowInstance::FlowInstance() :
        fcepID(cepID++), secNum(0) {}


    Flows::Flows(int _lim, int avgPDU, int varPDU, string DIF, string SRC, string DST, string QoS) :
        lim(_lim),
        srcAddr(Address(SRC.c_str(), DIF.c_str())),
        dstAddr(Address(DST.c_str(), DIF.c_str())),
        minPDU(avgPDU - varPDU),
        maxPDU(avgPDU + varPDU) {
            connID.setSrcCepId(0);
            connID.setDstCepId(0);
            connID.setQoSId(QoS);
            if(minPDU <= 0) { minPDU = 1; }
    }

    Flows::Flows(int _lim, ConnectionId _connID, Address _srcAddr, Address _dstAddr, int _minPDU, int _maxPDU) :
        lim(_lim),
        connID(_connID),
        srcAddr(_srcAddr),
        dstAddr(_dstAddr),
        minPDU(_minPDU),
        maxPDU(_maxPDU) {}

    void Flows::addFlow() {
        flows.push_back(FlowInstance());
        current = flows.begin();
    }

    Flows Flows::dup() {
        Flows ret(lim, connID, srcAddr, dstAddr, minPDU, maxPDU);
        for(unsigned int i = 0; i<flows.size(); i++) { ret.addFlow(); }
        return ret;
    }


    PortFlows::PortFlows(double _avgBitWt) :
        avgBitWt(_avgBitWt), lim(0) {}

    Flows * PortFlows::addFlows(int _lim, int avgPDU, int varPDU, string DIF, string SRC, string DST, string QoS) {
        lim += _lim;
        flows.push_back(Flows(lim, avgPDU, varPDU, DIF, SRC, DST, QoS));
        return &flows.back();
    }

    Flows * PortFlows::addFlows(Flows fls) {
        flows.push_back(fls);
        return &flows.back();
    }

    PortFlows PortFlows::dup() {
        PortFlows ret(avgBitWt);
        for(auto & fls : flows) { ret.addFlows(fls.dup()); }
        ret.lim = lim;
        return ret;
    }

    commMsg::commMsg(PortFlows * _pf) :
            pf(_pf) {}

    void Infection::initialize() {
        double iniT= par("iniTime").doubleValue();

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
        double inPorts = par("inPorts").doubleValue();

        PortFlows pf(1/linkRate * usage / inPorts);

        cXMLElementList flowsXML = Xml->getChildrenByTagName("flow");
        for(cXMLElement * n : flowsXML) {
            string DST = "";
            string QoS = VAL_MGMTQOSID;


            DST = n->getAttribute("dstAddr");
            if (DST == "") {
                error("Error parsing Infected flow. Its dstAddr is missing!"); }
            if(DST == SRC) { continue; }

            if (n->getAttribute("qos")) { QoS = n->getAttribute("qos"); }

            int N = 1, pduS = 1024, pduSv = 0, parts = 1;

            if (n->getAttribute("N") && atoi(n->getAttribute("N")) > 0) {
                N = atoi(n->getAttribute("N")); }

            if (n->getAttribute("pduSizeVar") && atoi(n->getAttribute("pduSizeVar")) > 0) {
                pduSv = atoi(n->getAttribute("pduSizeVar")); }

            if (n->getAttribute("partitions") && atoi(n->getAttribute("partitions")) > 0) {
                parts = atoi(n->getAttribute("partitions")); }

            Flows * fls = pf.addFlows(N, pduS, pduSv, DIF, SRC, DST, QoS);
            for(int i = 0; i < parts; i++) {
                fls->addFlow();
            }
        }

        flows.push_back(pf);
        scheduleAt(iniT + uniform(0, 1500*pf.avgBitWt), new commMsg(&flows.back()));
        for(int i = 1; i < inPorts; i++) {
            flows.push_back(pf.dup());
            scheduleAt(iniT + uniform(0, 1500*pf.avgBitWt), new commMsg(&flows.back()));
        }


    }

    void Infection::handleMessage(cMessage *msg) {
        if(commMsg * m = dynamic_cast<commMsg *>(msg)) {
            int r = uniform(0, m->pf->lim);
            Flows * rf = NULL;
            for(Flows & fl : m->pf->flows) {
                rf = &fl;
                if(fl.lim >= r) { break; }
            }
            if(rf == NULL) {  error("Something wrong!"); }

            int pduSize = intuniform(rf->minPDU, rf->maxPDU);

            simtime_t now = simTime();

            DataTransferPDU * pdu = new InfectedDataTransferPDU( now >= markIniT && now < markFinT, rf->current->fcepID, "InfectedPDU");

            rf->current->secNum++;

            pdu->setConnId(rf->connID);
            pdu->setSrcAddr(rf->srcAddr);
            pdu->setDstAddr(rf->dstAddr);
            pdu->setSrcApn(rf->srcAddr.getApn());
            pdu->setDstApn(rf->dstAddr.getApn());
            pdu->setSeqNum(rf->current->secNum);

            UserDataField * ud = new UserDataField();
            ud->setSduSeqNum(rf->current->secNum);

            SDU * sdu = new SDU();
            sdu->addUserData(new cPacket());
            ud->addData(sdu);
            pdu->setUserDataField(ud);

            pdu->setBitLength(pduSize);

            scheduleAt(now + exponential(pduSize*m->pf->avgBitWt), m);
            send(pdu, "g$o");
        }
    }
}

/*




    int InfectionFlow::cepID = 1;

    InfectionFlow::InfectionFlow() :
        fcepID(cepID++), count(0), secNum(0) {}

    InfectionFlows::InfectionFlows(int linkRate, double ratePercentage, int partitions, int varPDU, string DIF, string SRC, string DST, string _QoS) {

    }

    InfectionFlow::InfectionFlow(int bitRate, int avgPDU, int varPDU, string DIF, string SRC, string DST, string _QoS) {
        minPDU = avgPDU - varPDU;
        maxPDU = avgPDU + varPDU;
        QoS = _QoS;

        fcepID = cepID++;

        connID.setSrcCepId(0);
        connID.setDstCepId(0);
        connID.setQoSId(QoS);

        srcAddr = Address(SRC.c_str(), DIF.c_str());
        dstAddr = Address(DST.c_str(), DIF.c_str());

        bitWTime = 1.0/(1024*bitRate);

        count = 0;
        secNum = 1;
        currentPartition = 0;
    }

    InfectionFlow::InfectionFlow(int _minPDU, int _maxPDU, string _QoS, ConnectionId _connID, Address _srcAddr, Address _dstAddr, double _bitWTime) {
        minPDU = _minPDU;
        maxPDU = _maxPDU;
        QoS = _QoS;

        fcepID = cepID++;

        connID = _connID;
        connID.setSrcCepId(0);
        connID.setDstCepId(0);

        srcAddr = _srcAddr;
        dstAddr = _dstAddr;

        bitWTime = _bitWTime;

        count = 0;
        secNum = 1;
        currentPartition=0;
    }

    InfectionFlow * InfectionFlow::dup() {
        return new InfectionFlow(minPDU, maxPDU, QoS, connID, srcAddr, dstAddr, bitWTime);
    }


    DataTransferPDU* InfectionFlow::getPDU(Infection * parent, bool signaled) {
        int pduSize = intuniform(minPDU, maxPDU);


        DataTransferPDU* pdu = new InfectedDataTransferPDU( signaled, fcepID, "InfectedPDU");


        pdu->setConnId(connID);
        pdu->setSrcAddr(srcAddr);
        pdu->setDstAddr(dstAddr);
        pdu->setSrcApn(srcAddr.getApn());
        pdu->setDstApn(dstAddr.getApn());
        pdu->setSeqNum(secNum);

        UserDataField * ud = new UserDataField();
        ud->setSduSeqNum(secNum++);

        SDU * sdu = new SDU();
        sdu->addUserData(new cPacket());
        ud->addData(sdu);
        pdu->setUserDataField(ud);

        pdu->setBitLength(pduSize);

        double wTime = pduSize*bitWTime;
        parent->recall(this, wTime);

        count++;
        return pdu;
    }

    void Infection::initialize() {
        double iniT= par("iniTime").doubleValue();

        if(iniT<0) { return; }
        if(par("infectedIPC").stdstringValue() == "") { return; }

        emitSignals = par("signal").boolValue();
        if(emitSignals) {
            signal = registerSignal("InfectionSignal");
        }

        markIniT = par("markIniT").doubleValue();
        markFinT = par("markFinT").doubleValue();


        finTime = par("finTime").doubleValue();

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

        double multiplier= par("multiplier").doubleValue();
        int numFlows = par("numFlows").longValue();

        cXMLElementList flows = Xml->getChildrenByTagName("flow");
        for(cXMLElement * n : flows) {
            int bitRate = 1;
            int avgPDU = 1024;
            int varPDU = 0;
            string DST = "";
            string QoS = VAL_MGMTQOSID;

            if (!n->getAttribute("dstAddr")) {
                EV << "Error parsing Infected flow. Its dstAddr is missing!" << endl;
                continue;
            }

            DST = n->getAttribute("dstAddr");
            if (DST == "") {
                EV << "Error parsing Infected flow. Its dstAddr is missing!" << endl;
                continue;
            }

            if(DST == SRC) { continue; }

            if (n->getAttribute("qos")) { QoS = n->getAttribute("qos"); }
            if (n->getAttribute("pduSize") && atoi(n->getAttribute("pduSize")) > 0) {
                avgPDU = atoi(n->getAttribute("pduSize")); }
            if (n->getAttribute("pduSize") && atoi(n->getAttribute("pduSize")) > 0) {
                avgPDU = atoi(n->getAttribute("pduSize")); }
            if (n->getAttribute("bitRate") && atoi(n->getAttribute("bitRate")) > 0) {
                bitRate = atoi(n->getAttribute("bitRate")); }

            InfectionFlow * inf = new InfectionFlow(bitRate*multiplier, avgPDU, varPDU, DIF, SRC, DST, QoS);

            infs.push_back(inf);
            recall(inf, iniT+uniform(0, inf->bitWTime*inf->maxPDU));
            for(int i = 0; i< numFlows-1; i++) {
                inf = inf->dup();
                infs.push_back(inf);
                recall(inf, iniT+uniform(0, inf->bitWTime*inf->maxPDU));
            }
        }

    }

    void Infection::recall(InfectionFlow * inf, double dt) {
        scheduleAt(dt+simTime(), new TimerMessage(inf));
    }

    TimerMessage::TimerMessage(InfectionFlow * _inf) {
        inf = _inf;
    }

    void Infection::handleMessage(cMessage *msg) {
        if(simTime() > finTime) { delete msg; return; }

        if(TimerMessage * tM = dynamic_cast<TimerMessage*>(msg)) {
            if(emitSignals) {
                emit(signal, new SendInfMsg(tM->inf->QoS));}
            simtime_t now = simTime();
            send(tM->inf->getPDU(this, now >= markIniT && now < markFinT), "g$o");
        }
        delete msg;
    }

    void Infection::finish() {
        for(InfectionFlow * inf : infs) {
            delete inf;
        }
    }
*/
