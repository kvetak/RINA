#include <algorithm>
#include "NetTestInj.h"
#include "Inj_PDU.h"
#include "NetTest/SigMessages.h"

Define_Module(NetTestInj);

void NetTestInj::initialize() {
    double ini = par("ini").doubleValue();
    wait = par("wait").doubleValue();
    string infectedIPC = par("infectedIPC").stdstringValue();
    if(ini < 0 || wait <= 0 || infectedIPC == "") { return; }

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
    string qos = par("qos").stdstringValue();
    connID.setDstCepId(-1);
    connID.setQoSId(qos);
    connID.setSrcCepId(-1);

    dif = mod->par("difName").stdstringValue();
    src = mod->par("ipcAddress").stdstringValue();
    srcAddr = Address(src.c_str(), dif.c_str());

    //Read flows config
    cXMLElementList flowsXML = Xml->getChildrenByTagName("NodeAddr");
    for(cXMLElement * n : flowsXML) {
        string xNode = n->getAttribute("id");

        if(xNode == src) { continue; }
        destinations.push_back(xNode);
    }

    random_shuffle ( destinations.begin(), destinations.end() );
    scheduleAt(ini, new cMessage("SendNext"));
}

void NetTestInj::handleMessage(cMessage *msg) {
    if(destinations.empty()) {
        destinations = tDest;
        tDest.clear();
        random_shuffle ( destinations.begin(), destinations.end() );
      //  delete msg; return;
    }

    string dst = destinations.back();
    destinations.pop_back();
    tDest.push_back(dst);

    //Create new PDU
    Inj_PDU * pdu = new Inj_PDU();
    pdu->setConnId(connID);
    pdu->setSrcAddr(srcAddr);
    pdu->setSrcApn(srcAddr.getApn());
    dstAddr = Address(dst.c_str(), dif.c_str());
    pdu->setDstAddr(dstAddr);
    pdu->setDstApn(dstAddr.getApn());
    pdu->first = true;
    pdu->setSeqNum(0);
    UserDataField * ud = new UserDataField();
    ud->setCompleteSDU(true);
    ud->setNoLength(false);
    ud->setSduSeqNumPresent(true);
    ud->setSduSeqNum(0);
    pdu->encapsulate(ud);
    pdu->setHopCount(0);
    pdu->setByteLength(1480);
    send(pdu, "g$o");

    emit(signal, new SigSend(src, dst) );

    scheduleAt(simTime() + wait, msg);
}
