// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include "sRA.h"

Define_Module(sRA);



void sRA::initialize(int stage)
{
    if (stage == 1)
    {
        //rmt->enableRelay();

        // preallocate flows
        initFlowAlloc();
        return;
    }

    EV << "Register signal agentRequest at :"<< this->getParentModule()->getParentModule()->getFullPath()<<endl;

    signalToAgent = this->getParentModule()->getParentModule()->registerSignal("agentRequest");

    // retrieve pointers to other modules
    thisIPC = this->getModuleByPath("^.^");
    rmtModule = (getRINAModule<cModule*>(this, 2, {MOD_RELAYANDMUX}));

    // Get access to the forwarding and routing functionalities...
    fwdtg = getRINAModule<IntPDUFG *>(this, 1, {MOD_PDUFWDGEN});
    difAllocator = getRINAModule<DA*>(this, 3, {MOD_DIFALLOC, MOD_DA});;
    flowTable = getRINAModule<NM1FlowTable*>(this, 1, {MOD_RANM1FLOWTABLE});
    rmt = getRINAModule<RMT*>(this, 2, {MOD_RELAYANDMUX, MOD_RMT});
    rmtAllocator = getRINAModule<RMTModuleAllocator*>(this, 2, {MOD_RELAYANDMUX, MOD_RMTALLOC});
    fa = getRINAModule<FABase*>(this, 2, {MOD_FLOWALLOC, MOD_FA});

    // retrieve pointers to policies
    qAllocPolicy = getRINAModule<QueueAllocBase*>(this, 1, {MOD_POL_QUEUEALLOC});

    // initialize attributes
    std::ostringstream os;
    os << thisIPC->par(PAR_IPCADDR).stringValue() << "_"
       << thisIPC->par(PAR_DIFNAME).stringValue();
    processName  = os.str();

    initSignalsAndListeners();
    initQoSCubes();

    WATCH_LIST(this->QoSCubes);
}


/**
 * Assigns a suitable (N-1)-flow to the (N)-flow (and creates one if there isn't any)
 *
 * @param flow specified flow object
 * @return true if an interface or an (N-1)-flow is ready to serve, false otherwise
 */
bool sRA::bindNFlowToNM1Flow(Flow* flow)
{
    Enter_Method("bindNFlowToNM1Flow()");
    EV << "---------------------------------------------------------bindNFlowToNM1Flow" << endl << endl;


    EV << "Received a request to bind an (N)-flow (dst "
       << flow->getDstApni().getApn().getName() << ", QoS-id "
       << flow->getConId().getQoSId() << ") to an (N-1)-flow." << endl;

    if(Flow2Index.find(flow) == Flow2Index.end()) { return false; }

    return true;
}


void sRA::AddNM1Flow(Flow * f, int index) {
    Flow2Index[f] = index;

    // retrieve the south gate
    cGate* thisIPCIn = thisIPC->gateHalf("southIo$i", cGate::INPUT, index);
    cGate* thisIPCOut = thisIPC->gateHalf("southIo$o", cGate::OUTPUT, index);

    //// connect bottom of this IPC to rmtModule
    // create an INOUT gate on the bottom of rmtModule
    std::ostringstream rmtGate;
    rmtGate << GATE_SOUTHIO_ << "PHY"<<index;
    rmtModule->addGate(rmtGate.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(rmtGate.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(rmtGate.str().c_str(), cGate::OUTPUT);

    rmtModuleOut->connectTo(thisIPCOut);
    thisIPCIn->connectTo(rmtModuleIn);

    // create a mock "(N-1)-port" for interface
    RMTPort* port = rmtAllocator->addPort(nullptr);
    // connect the port to the bottom
    interconnectModules(rmtModule, port->getParentModule(), rmtGate.str(), std::string(GATE_SOUTHIO));
    // finalize initial port parameters
    port->postInitialize();
    port->setOutputReady();
    port->setInputReady();

    // apply queue allocation policy handler
    qAllocPolicy->onNM1PortInit(port);

    fa->invokeNewFlowRequestPolicy(f);

    if(f->getSrcAddr().getIpcAddress().getName() == thisIPC->par("ipcAddress").stdstringValue()) {
        fwdtg->insertFlowInfo(f->getDstAddr(), f->getQosCube(), port);
    } else {
        fwdtg->insertFlowInfo(f->getSrcAddr(), f->getQosCube(), port);
    }
}





















