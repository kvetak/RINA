#include "MA.h"

Define_Module(MA);

MA::MA() {}

void MA::initialize() {
    EV << "Holas"<<endl;
}



void MA::handleMessage(cMessage *m) {
    EV << "Received Message"<<endl;

    if(helloMsg * msg = dynamic_cast<helloMsg*>(m)) {
           EV << "New Agent "<< msg->id <<" registered"<<endl;
           agents[msg->id] = msg->mod;
           agentGates[msg->id] = gateHalf("maIo", cGate::OUTPUT, msg->getArrivalGate()->getIndex());

    } else if(requestMsg * msg = dynamic_cast<requestMsg*>(m)) {
           string src = msg->f->getSrcAddr().getIpcAddress().getName();
           string dst = msg->f->getDstAddr().getIpcAddress().getName();

           EV << "New Flow request from "<< src <<"  to " << dst <<endl;

           cModule * srcM = agents[src]->getParentModule();
           srcM->setGateSize("southIo", srcM->gateSize("southIo")+1);
           cGate * srcGateIn = srcM->gateHalf("southIo", cGate::INPUT, srcM->gateSize("southIo")-1);
           cGate * srcGateOut = srcM->gateHalf("southIo", cGate::OUTPUT, srcM->gateSize("southIo")-1);

           cModule * dstM = agents[dst]->getParentModule();
           dstM->setGateSize("southIo", dstM->gateSize("southIo")+1);
           cGate * dstGateIn = dstM->gateHalf("southIo", cGate::INPUT, dstM->gateSize("southIo")-1);
           cGate * dstGateOut = dstM->gateHalf("southIo", cGate::OUTPUT, dstM->gateSize("southIo")-1);

           srcGateOut->connectTo(dstGateIn);
           dstGateOut->connectTo(srcGateIn);

           responseMsg *toSrc = new responseMsg(agents[src], agents[dst],msg->f, srcGateIn->getIndex());
           send(toSrc, agentGates[src]);

           responseMsg *toDst = new responseMsg(agents[src], agents[dst],msg->f, dstGateIn->getIndex());
           send(toDst, agentGates[dst]);
    }

    delete m;
}
