#include "Infection.h"

#include "DataTransferPDU.h"

using namespace std;

namespace Infection {

    Define_Module(Infection);


    InfectionFlow::InfectionFlow(int bitRate, int avgPDU, int varPDU, string DIF, string SRC, string DST, string _QoS) {
        minPDU = avgPDU - varPDU;
        maxPDU = avgPDU + varPDU;
        QoS = _QoS;

        connID.setSrcCepId(0);
        connID.setDstCepId(0);
        connID.setQoSId(QoS);

        srcAddr = Address(SRC.c_str(), DIF.c_str());
        dstAddr = Address(DST.c_str(), DIF.c_str());

        bitWTime = 1.0/(1024*bitRate);

        count = 0;
    }


    DataTransferPDU* InfectionFlow::getPDU(Infection * parent) {
        int pduSize = intuniform(minPDU, maxPDU);

        DataTransferPDU* pdu = new DataTransferPDU("InfectedPDU");
        pdu->setConnId(connID);
        pdu->setSrcAddr(srcAddr);
        pdu->setDstAddr(dstAddr);
        pdu->setSrcApn(srcAddr.getApn());
        pdu->setDstApn(dstAddr.getApn());
        pdu->setSeqNum(0);

        UserDataField * ud = new UserDataField();
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

            InfectionFlow * inf = new InfectionFlow(bitRate, avgPDU, varPDU, DIF, SRC, DST, QoS);

            infs.push_back(inf);
            recall(inf, iniT);
        }

    }

    void Infection::recall(InfectionFlow * inf, double dt) {
        scheduleAt(dt+simTime(), new TimerMessage(inf));
    }

    TimerMessage::TimerMessage(InfectionFlow * _inf) {
        inf = _inf;
    }

    void Infection::handleMessage(cMessage *msg) {
        if(TimerMessage * tM = dynamic_cast<TimerMessage*>(msg)) {
            send(tM->inf->getPDU(this), "g$o");
        }
        delete msg;
    }

    void Infection::finish() {
        for(InfectionFlow * inf : infs) {
            EV << "Flow : " << inf->srcAddr << " -> " << inf->dstAddr << " (" << inf->QoS<< ") : " << inf->count << endl;
            delete inf;
        }
    }

}
