#include "DCInfection.h"

using namespace std;


namespace Infection {

    Define_Module(DCInfection);


    void DCInfection::initialize() {
        double iniT = par("iniTime").doubleValue();
        loopRem = par("loop").longValue();

        if(loopRem <= 0 || iniT<0 || par("infectedIPC").stdstringValue() == "") { return; }

        toTors = par("toTors");
        toFabric = par("toFabric");
        toSpines = par("toSpines");
        toEdges = par("toEdges");

        if(toTors || toFabric || toSpines) {
                scheduleAt(iniT, new cMessage());
        } else { return; }

        interTime = par("interTime").doubleValue();

        mod = this->getParentModule()->getSubmodule(par("infectedIPC").stringValue());
        if(mod==NULL) { return; }

        rmt = mod->getSubmodule("relayAndMux")->getSubmodule("rmt");

        rmt->addGate("infGate", cGate::INOUT, false);
        cGate * modIn = rmt->gateHalf("infGate", cGate::INPUT);
        cGate * modOut = rmt->gateHalf("infGate", cGate::OUTPUT);

        cGate * In = gateHalf("g", cGate::INPUT);
        cGate * Out = gateHalf("g", cGate::OUTPUT);

        modOut->connectTo(In);
        Out->connectTo(modIn);


        string DIF = mod->par("difName");
        string SRC = mod->par("ipcAddress");
        Im = DCAddr(SRC);
        current = Im;

        string qosId = par("qosId");


        srcAddr = Address(SRC.c_str(), DIF.c_str());
        dstAddr = srcAddr;
        connID.setSrcCepId(-1);
        connID.setDstCepId(-1);
        connID.setQoSId(qosId);

        pods = par("pods").longValue();
        torXpod = par("torXpod").longValue();
        fabricXpod = par("fabricXpod").longValue();
        spineXfabric = par("spineXfabric").longValue();
        edgeSets =  par("edgeSets").longValue();

        if(pods < 1) { pods = 1; }
        if(torXpod < 1) { torXpod = 1; }
        if(fabricXpod < 1) { fabricXpod = 1; }
        if(spineXfabric < 1) { spineXfabric = 1; }
        if(edgeSets < 0) { edgeSets = 0; }
    }


    void DCInfection::handleMessage(cMessage *msg) {
        simtime_t now = simTime();
        if(loopRem <= 0) { delete msg; return; }

        PDU * pdu = getPDU();
        if(pdu != nullptr) {
            scheduleAt(now + interTime, msg);
            send(pdu, "g$o");
        } else { delete msg; }
    }


    void DCInfection::setNext() {
        DCAddr tCurr = current;
        switch(current.type) {
            case 0:
                if(!toTors) {
                    current.type = 1;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                current.b++;
                if(current.b == torXpod) {
                    current.b = 0;
                    current.a++;
                }
                if(current.a == pods) {
                    current.type = 1;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                break;
            case 1:
                if(!toFabric) {
                    current.type = 2;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                current.b += 1;
                if(current.b == fabricXpod) {
                    current.b = 0;
                    current.a++;
                }
                if(current.a == pods) {
                    current.type = 2;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                break;
            case 2:
                if(!toSpines) {
                    current.type = 3;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                current.b += 1;
                if(current.b == spineXfabric) {
                    current.b = 0;
                    current.a++;
                }
                if(current.a == fabricXpod) {
                    current.type = 3;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                break;
            case 3:
                if(!toEdges) {
                    current.type = 0;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                current.b += 1;
                if(current.b == fabricXpod) {
                    current.b = 0;
                    current.a++;
                }
                if(current.a == edgeSets) {
                    current.type = 0;
                    current.a = 0;
                    current.b = -1;
                    setNext();
                    return;
                }
                break;
        }

        if(current == Im && tCurr != Im) { loopRem--; setNext(); }
        else {
            dstAddr = Address(current.toString().c_str(), dstAddr.getDifName().getName().c_str());
       //     cout << Im << " -> " << current << endl;
        }
    }

    PDU * DCInfection::getPDU() {
        setNext();

        DataTransferPDU * pdu = new DataTransferPDU( "DCInfectedPDU");

        pdu->setConnId(connID);
        pdu->setSrcAddr(srcAddr);
        pdu->setDstAddr(dstAddr);
        pdu->setSrcApn(srcAddr.getApn());
        pdu->setDstApn(dstAddr.getApn());
        pdu->setSeqNum(0);

        UserDataField * ud = new UserDataField();

        ud->setCompleteSDU(true);
        ud->setNoLength(false);
        ud->setSduSeqNumPresent(true);
        ud->setSduSeqNum(0);
        pdu->encapsulate(ud);

        pdu->setByteLength(0);
        pdu->setHopCount(0);

        return pdu;

    }
}
