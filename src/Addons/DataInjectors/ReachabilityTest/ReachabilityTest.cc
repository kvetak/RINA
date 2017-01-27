#include "Addons/DataInjectors/ReachabilityTest/ReachabilityTest.h"

#include "Addons/DataInjectors/ReachabilityTest/ReachabilityTest_Comparator.h"
#include "Addons/DataInjectors/ReachabilityTest/ReachabilityTest_Listener.h"
#include "Common/Utils.h"
#include <algorithm>


Define_Module(ReachabilityTest);

CT_PDU * ReachabilityTest::genPDU(const string & dst, const string & _QoS, const int & stage, const int & srcCep) {
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

void ReachabilityTest::initialize() {
    //Init ini/fin times

    if (par("infectedIPC").stdstringValue() == "") { return; }
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
    if (ReachabilityTest_Comparator * oac = dynamic_cast<ReachabilityTest_Comparator*>(ac)) { oac->p = this; }


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

    double iniT = par("ini").doubleValue();
    if (iniT < 0) { return; }
    interval = par("interval").doubleValue();
    scheduleAt(iniT+omnetpp::uniform(omnetpp::getEnvir()->getRNG(0), 0.0, interval), &nextSend);
}

void ReachabilityTest::handleMessage(cMessage *msg) {
    Enter_Method_Silent();

    if(msg == &nextSend) {
        string next = remaining.back();
        remaining.pop_back();
        send(genPDU(next, QoS, 0, omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0,500)), "g$o");
        if(ReachabilityTest_Listener::instance) {
            ReachabilityTest_Listener::instance->sent(src, next, QoS, 0);
        }

        if(!remaining.empty()) { scheduleAt(simTime()+interval, msg); }
    } else {
        cout << "Unknown message received"<< endl;
    }
}
void ReachabilityTest::finish() {
    if(nextSend.isScheduled()) { drop(&nextSend); }
}

void ReachabilityTest::receiveData(const string & _src, const string & _qos, const int & srcCep, shared_ptr<CT_data> data) {
    Enter_Method_Silent();

    if(ReachabilityTest_Listener::instance) {
        ReachabilityTest_Listener::instance->received(_src, src, _qos, data->stage, data->t0);
    }

    if(data->stage == 0) {
        send(genPDU(_src, _qos, 1, srcCep), "g$o");
        if(ReachabilityTest_Listener::instance) {
            ReachabilityTest_Listener::instance->sent(src, _src, _qos, 1);
        }
    }
}


