#include "ConnectivityTest.h"

#include "ConnectivityTestComparator.h"
#include "ConnectivityTestListener.h"
#include "Utils.h"
#include <algorithm>


Define_Module(ConnectivityTest);

CT_PDU * ConnectivityTest::genPDU(const string & dst, const string & _QoS, const int & stage, const int & srcCep) {
    CT_PDU * pdu = new CT_PDU();
    connID.setQoSId(_QoS);
    connID.setSrcCepId(srcCep);
    pdu->setConnId(connID);
    pdu->setSrcAddr(srcAddr);
    pdu->setSrcApn(srcAddr.getApn());
    dstAddr = Address(dst.c_str(), dif.c_str());
    pdu->setDstAddr(dstAddr);
    pdu->setDstApn(dstAddr.getApn());
    pdu->xdata = shared_ptr < CT_data > (new CT_data(header, stage));
    pdu->setByteLength(header);
    return pdu;
}

void ConnectivityTest::initialize() {
    //Init ini/fin times
    double iniT = par("ini").doubleValue();
    if (iniT < 0 || par("infectedIPC").stdstringValue() == "") { return; }
    interval = par("interval").doubleValue();

    //Get IPCP
    cModule * ipc = this->getParentModule()->getSubmodule(par("infectedIPC").stringValue());
    if (ipc == nullptr) { return; }

    //Connect to RMT
    cModule * rmt = ipc->getSubmodule("relayAndMux")->getSubmodule("rmt");
    rmt->addGate("infGate", cGate::INOUT, false);
    cGate * modIn = rmt->gateHalf("infGate", cGate::INPUT);
    cGate * modOut = rmt->gateHalf("infGate", cGate::OUTPUT);
    cGate * In = gateHalf("g", cGate::INPUT);
    cGate * Out = gateHalf("g", cGate::OUTPUT);
    modOut->connectTo(In);
    Out->connectTo(modIn);

    //Conect comparator
    cModule *ac = ipc->getSubmodule("resourceAllocator")->getSubmodule( "addressComparator");
    if (ConnectivityTestComparator * oac = dynamic_cast<ConnectivityTestComparator*>(ac)) { oac->p = this; }

    //Init node info
    dif = ipc->par("difName").stdstringValue();
    src = ipc->par("ipcAddress").stdstringValue();
    srcAddr = Address(src.c_str(), dif.c_str());
    dstAddr = Address("", dif.c_str());
    connID.setDstCepId(-1);
    QoS = par("QoS").stdstringValue();
    header = par("header_size").longValue();

    string nodes_raw = par("nodes").stdstringValue();
    split(nodes_raw, ' ', remaining);
    random_shuffle ( remaining.begin(), remaining.end() );

    scheduleAt(iniT+uniform(0.0, interval), &nextSend);
}

void ConnectivityTest::handleMessage(cMessage *msg) {
    Enter_Method_Silent();

    if(msg == &nextSend) {
        string next = remaining.back();
        remaining.pop_back();
        send(genPDU(next, QoS, 0, intuniform(0,500)), "g$o");
        if(ConnectivityTestListener::instance) {
            ConnectivityTestListener::instance->sent(src, next, QoS, 0);
        }

        if(!remaining.empty()) { scheduleAt(simTime()+interval, msg); }
    } else {
        cout << "Unknown message received"<< endl;
    }
}
void ConnectivityTest::finish() {
    if(nextSend.isScheduled()) { drop(&nextSend); }
}

void ConnectivityTest::receiveData(const string & _src, const string & _qos, const int & srcCep, shared_ptr<CT_data> data) {
    Enter_Method_Silent();

    if(ConnectivityTestListener::instance) {
        ConnectivityTestListener::instance->received(_src, src, _qos, data->stage, data->t0);
    }

    if(data->stage == 0) {
        send(genPDU(_src, _qos, 1, srcCep), "g$o");
        if(ConnectivityTestListener::instance) {
            ConnectivityTestListener::instance->sent(src, _src, _qos, 1);
        }
    }
}


