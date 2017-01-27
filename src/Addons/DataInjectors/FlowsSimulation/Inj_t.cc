#include "Addons/DataInjectors/FlowsSimulation/Inj_t.h"
#include "Addons/DataInjectors/FlowsSimulation/Comparator_FWDG/Inj_Comparator.h"
#include "Addons/DataInjectors/FlowsSimulation/Comparator_FWDG/Inj_FWDG.h"
#include "./Flows/Flow_t.h"

Flow_PDU * Inj_t::genPDU(const PDU_Req & req) {
    dstAddr = Address(req.f->dstAddr.c_str(), dif.c_str());

    Flow_PDU * pdu = new Flow_PDU(srcAddr.getIpcAddress().getName() +" > "+dstAddr.getIpcAddress().getName());
    connID.setQoSId(req.f->QoS);
    connID.setSrcCepId(req.f->flowId);
    pdu->setConnId(connID);
    pdu->setSrcAddr(srcAddr);
    pdu->setSrcApn(srcAddr.getApn());
    pdu->setDstAddr(dstAddr);
    pdu->setDstApn(dstAddr.getApn());
    req.data->pduId = pduId++;
    pdu->xdata = shared_ptr < Flow_Data > (req.data);
    pdu->setByteLength(pdu->xdata->len);
    return pdu;
}

void Inj_t::initialize() {
    //Init ini/fin times
    iniT = par("ini").doubleValue();
    finT = par("fin").doubleValue();
    if(iniT < 0.0) { iniT = 0.0; }
    if (finT < iniT || par("infectedIPC").stdstringValue() == "") { return; }

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
    if (Inj_Comparator * oac = dynamic_cast<Inj_Comparator*>(ac)) { oac->p = this; }

    //Conect pdufwgen
    cModule *fwdg = ipc->getSubmodule("resourceAllocator")->getSubmodule( "pduFwdGenerator");
    if (Inj_FWDG * ofwdg = dynamic_cast<Inj_FWDG*>(fwdg)) { ofwdg->inj = this; }

    //Init node info
    dif = ipc->par("difName").stdstringValue();
    src = ipc->par("ipcAddress").stdstringValue();
    srcAddr = Address(src.c_str(), dif.c_str());
    dstAddr = Address("", dif.c_str());
    connID.setDstCepId(-1);

    headers = par("headers_size").longValue();

    pduId = 0;

    postInitialize();
}

