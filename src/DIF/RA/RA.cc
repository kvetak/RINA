//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

/**
 * @file RA.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Monitoring and adjustment of IPC process operations
 * @detail
 */

#include "RA.h"

Define_Module(RA);

const char* PAR_QOSDATA              = "qoscubesData";
const char* ELEM_QOSCUBE             = "QosCube";
const char* ATTR_ID                  = "id";
const char* ELEM_AVGBW               = "AverageBandwidth";
const char* ELEM_AVGSDUBW            = "AverageSDUBandwidth";
const char* ELEM_PEAKBWDUR           = "PeakBandwidthDuration";
const char* ELEM_PEAKSDUBWDUR        = "PeakSDUBandwidthDuration";
const char* ELEM_BURSTPERIOD         = "BurstPeriod";
const char* ELEM_BURSTDURATION       = "BurstDuration";
const char* ELEM_UNDETECTBITERR      = "UndetectedBitError";
const char* ELEM_MAXSDUSIZE          = "MaxSDUSize";
const char* ELEM_PARTIALDELIVER      = "PartialDelivery";
const char* ELEM_INCOMPLETEDELIVER   = "IncompleteDelivery";
const char* ELEM_FORCEORDER          = "ForceOrder";
const char* ELEM_MAXALLOWGAP         = "MaxAllowableGap";
const char* ELEM_DELAY               = "Delay";
const char* ELEM_JITTER              = "Jitter";
const char* ELEM_COSTTIME            = "CostTime";
const char* ELEM_COSTBITS            = "CostBits";

void RA::initialize()
{
    // connect to other modules
    difAllocator = ModuleAccess<DA>(MOD_DA).get();
    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    flTable = ModuleAccess<FlowTable>("flowTable").get();
    rmt = (RMT*) this->getParentModule()->getParentModule()->getModuleByPath(".rmt.rmt");
    rmtQM = (RMTQueueManager*) this->getParentModule()->getParentModule()->getModuleByPath(".rmt.rmtQueueManager");

    // initialize attributes
    std::ostringstream os;
    os << getParentModule()->getParentModule()->par(PAR_IPCADDR).stdstringValue()
       << "_" << getParentModule()->getParentModule()->par(PAR_DIFNAME).stdstringValue();
    processName  = os.str();

    initSignalsAndListeners();
    initQoSCubes();

    // determine and set RMT mode of operation
    setRmtMode();

    WATCH_LIST(this->QosCubes);

}


void RA::setRmtMode()
{
    // identify the role of this IPC process in processing system
    cModule* hostModule = getParentModule()->getParentModule();
    std::string bottomGate = hostModule->gate("southIo$o", 0)->getNextGate()->getName();

    if (bottomGate == "medium$o")
    {
        // we're on wire! this is the bottommost "interface" DIF
        rmt->setOnWire(true);
        // let's connect RMT to the medium
        bindMediumToRMTQueue();
    }
    else if (bottomGate == "northIo$i")
    { // other IPC processes are below us
        rmt->setOnWire(false);
//        // create a queue for each QoS of each (N-1)-DIF
//        for (int i = 0; i <= hostModule->gateSize("northIo"); i++)
//        {
//            EV << hostModule->gate("southIo$o", i)->getNextGate()->getOwnerModule()->getFullName() << endl;
//            cModule* module = hostModule->gate("southIo$o", i)->getNextGate()->getOwnerModule();
//            cModule* raBottom = module->getModuleByPath(".resourceAllocator.ra");
//            QosCubeSet cubes = dynamic_cast<RABase*>(raBottom)->getQosCubes();
//            for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
//                short qosid = it->getQosId();
//                std::ostringstream ostr;
//                ostr << "q_" << module->par("difName").stringValue() << "_" << qosid;
//
//                rmt->addQueueSet(ostr.str().c_str());
//            }
//        }
    }

    if (hostModule->par("routing").boolValue() == true)
    {
        rmt->enableRelay();
    }

    rmt->setSchedulingPolicy(new LongestQFirst);
    EV << rmt->getSchedulingPolicy()->getName() << endl;
}


void RA::initQoSCubes() {
    cXMLElement* qosXml = NULL;
    if (par(PAR_QOSDATA).xmlValue() != NULL && par(PAR_QOSDATA).xmlValue()->hasChildren())
        qosXml = par(PAR_QOSDATA).xmlValue();
    else
        error("qoscubesData parameter not initialized!");

    cXMLElementList cubes = qosXml->getChildrenByTagName(ELEM_QOSCUBE);
    for (cXMLElementList::iterator it = cubes.begin(); it != cubes.end(); ++it) {
        cXMLElement* m = *it;
        if (!m->getAttribute(ATTR_ID)) {
            EV << "Error parsing QoSCube. Its ID is missing!" << endl;
            continue;
        }
        else if (! (unsigned short)atoi(m->getAttribute(ATTR_ID)) ) {
            EV << "QosID = 0 is reserved and cannot be used!" << endl;
            continue;
        }

        QosCube cube;
        cube.setQosId((unsigned short)atoi(m->getAttribute(ATTR_ID)));
        //Following data types should be same as in QosCubes.h
        int avgBand                 = VAL_QOSPARDONOTCARE;    //Average bandwidth (measured at the application in bits/sec)
        int avgSDUBand              = VAL_QOSPARDONOTCARE;    //Average SDU bandwidth (measured in SDUs/sec)
        int peakBandDuration        = VAL_QOSPARDONOTCARE;    //Peak bandwidth-duration (measured in bits/sec);
        int peakSDUBandDuration     = VAL_QOSPARDONOTCARE;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
        int burstPeriod             = VAL_QOSPARDONOTCARE;    //Burst period measured in useconds
        int burstDuration           = VAL_QOSPARDONOTCARE;    //Burst duration, measured in usecs fraction of Burst Period
        int undetectedBitErr        = VAL_QOSPARDONOTCARE;    //Undetected bit error rate measured as a probability
        int maxSDUsize              = VAL_QOSPARDONOTCARE;    //MaxSDUSize measured in bytes
        bool partDeliv              = VAL_QOSPARDEFBOOL;      //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
        bool incompleteDeliv        = VAL_QOSPARDEFBOOL;      //Incomplete Delivery - Can SDUs with missing pieces be delivered?
        bool forceOrder             = VAL_QOSPARDEFBOOL;      //Must SDUs be delivered in order?
        unsigned int maxAllowGap    = VAL_QOSPARDONOTCARE;    //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
        int delay                   = VAL_QOSPARDONOTCARE;    //Delay in usecs
        int jitter                  = VAL_QOSPARDONOTCARE;    //Jitter in usecs2
        int costtime                = VAL_QOSPARDONOTCARE;    //measured in $/ms
        int costbits                = VAL_QOSPARDONOTCARE;    //measured in $/Mb

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), ELEM_AVGBW) ) {
                avgBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (avgBand < 0)
                    avgBand = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_AVGSDUBW)) {
                avgSDUBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (avgSDUBand < 0)
                    avgSDUBand = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_PEAKBWDUR)) {
                peakBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (peakBandDuration < 0)
                    peakBandDuration = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_PEAKSDUBWDUR)) {
                peakSDUBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (peakSDUBandDuration < 0)
                    peakSDUBandDuration = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_BURSTPERIOD)) {
                burstPeriod = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (burstPeriod < 0)
                    burstPeriod = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_BURSTDURATION)) {
                burstDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (burstDuration < 0)
                    burstDuration = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_UNDETECTBITERR)) {
                undetectedBitErr = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (undetectedBitErr < 0 || undetectedBitErr > 1 )
                    undetectedBitErr = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_MAXSDUSIZE)) {
                maxSDUsize = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (maxSDUsize < 0)
                    maxSDUsize = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_PARTIALDELIVER)) {
                partDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
            }
            else if (!strcmp(n->getTagName(), ELEM_INCOMPLETEDELIVER)) {
                incompleteDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
            }
            else if (!strcmp(n->getTagName(), ELEM_FORCEORDER)) {
                forceOrder = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
            }
            else if (!strcmp(n->getTagName(), ELEM_MAXALLOWGAP)) {
                maxAllowGap = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (maxAllowGap < 0)
                    maxAllowGap = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_DELAY)) {
                delay = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (delay < 0)
                    delay = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_JITTER)) {
                jitter = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDONOTCARE;
                if (jitter < 0)
                    jitter = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_COSTTIME)) {
                costtime = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
                if (costtime < 0)
                    costtime = VAL_QOSPARDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_COSTBITS)) {
                costbits = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
                if (costbits < 0)
                    costbits = VAL_QOSPARDONOTCARE;
            }
        }

        cube.setAvgBand(avgBand);
        cube.setAvgSduBand(avgSDUBand);
        cube.setPeakBandDuration(peakBandDuration);
        cube.setPeakSduBandDuration(peakSDUBandDuration);
        cube.setBurstPeriod(burstPeriod);
        cube.setBurstDuration(burstDuration);
        cube.setUndetectedBitErr(undetectedBitErr);
        cube.setMaxSduSize(maxSDUsize);
        cube.setPartialDelivery(partDeliv);
        cube.setIncompleteDelivery(incompleteDeliv);
        cube.setForceOrder(forceOrder);
        cube.setMaxAllowGap(maxAllowGap);
        cube.setDelay(delay);
        cube.setJitter(jitter);
        cube.setCostBits(costbits);
        cube.setCostTime(costtime);

        QosCubes.push_back(cube);
    }
    if (!QosCubes.size()) {
        std::ostringstream os;
        os << this->getFullPath() << " does not have any QoSCube in its set. It cannot work without at least one valid QoS cube!" << endl;
        error(os.str().c_str());
    }
}

void RA::handleMessage(cMessage *msg)
{
    if (!msg->isSelfMessage())
    {
        delete msg;
        return;
    }
}

/**
 * Connects the medium defined in NED to the RMT module.
 * Used only for the bottom IPC process in a processing system.
 */
void RA::bindMediumToRMTQueue()
{
    // retrieve the south gate
    cModule* thisIpc = this->getParentModule()->getParentModule();
    cGate* thisIpcIn = thisIpc->gateHalf("southIo$i", cGate::INPUT, 0);
    cGate* thisIpcOut = thisIpc->gateHalf("southIo$o", cGate::OUTPUT, 0);

    // now let's connect rmtModule to bottom of IPC
    // create an INOUT on the bottom of rmtModule
    std::ostringstream rmtGate;
    rmtGate << GATE_SOUTHIO_ << "PHY";

    rmt->getParentModule()->addGate(rmtGate.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmt->getParentModule()->gateHalf(rmtGate.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmt->getParentModule()->gateHalf(rmtGate.str().c_str(), cGate::OUTPUT);

    // interconnect rmtModule and bottom of IPC
    rmtModuleOut->connectTo(thisIpcOut);
    thisIpcIn->connectTo(rmtModuleIn);

    RMTQueue* inputQueue = rmtQM->addQueue(RMTQueue::INPUT);
    RMTQueue* outputQueue = rmtQM->addQueue(RMTQueue::OUTPUT);

    outputQueue->getOutputGate()->connectTo(rmtModuleOut);
    rmtModuleIn->connectTo(inputQueue->getInputGate());
}

/**
 * Connects the specified (N-1)-flow to an RMT queue.
 *
 * @param ipc IPC process containing the (N-1)-flow
 * @param flow the (N-1)-flow
 * @return output gate for the (N-1)-flow
 */
RMTQueue* RA::bindLowerFlowToRmtQueue(cModule* ipc, Flow* flow)
{

    int portId = flow->getSrcPortId();
    /*
    if ( difAllocator->isAppLocal(flow->getDstApni().getApn()) )
        portId = flow->getDstPortId();
    else if ( difAllocator->isAppLocal(flow->getSrcApni().getApn()) )
        portId = flow->getSrcPortId();
    else
        throw("Binding to inconsistant PortId occured!");
    */

    // expand the given portId so it's unambiguous within this IPC
    std::string combinedPortId = normalizePortId(ipc->getFullName(), portId);

    //// binding begins at the bottom: first, we need to interconnect both IPCs
    // get (N-1)-IPC north gates
    std::ostringstream bottomIpcGate;
    bottomIpcGate << "northIo_" << portId;
    cGate* bottomIpcIn = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::INPUT);
    cGate* bottomIpcOut = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::OUTPUT);

    // create a border south gate for this IPC
    cModule* thisIpc = this->getParentModule()->getParentModule();
    std::ostringstream thisIpcGate;
    thisIpcGate << "southIo_" << combinedPortId;

    thisIpc->addGate(thisIpcGate.str().c_str(), cGate::INOUT, false);
    cGate* thisIpcIn = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::INPUT);
    cGate* thisIpcOut = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::OUTPUT);

    // interconnect IPCs
    bottomIpcOut->connectTo(thisIpcIn);
    thisIpcOut->connectTo(bottomIpcIn);

    //// now we'll connect bottom of this IPC to rmtModule
    // create an INOUT gate on the bottom of rmtModule
    std::ostringstream rmtGate;
    rmtGate << GATE_SOUTHIO_ << combinedPortId;

    rmt->getParentModule()->addGate(rmtGate.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmt->getParentModule()->gateHalf(rmtGate.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmt->getParentModule()->gateHalf(rmtGate.str().c_str(), cGate::OUTPUT);

    // interconnect rmtModule and bottom of IPC
    rmtModuleOut->connectTo(thisIpcOut);
    thisIpcIn->connectTo(rmtModuleIn);

    // all that's left to do is a binding of rmtModule south gate to a queue...
    // since the specifications are (at this time) a bit unclear about cardinality
    // between queues and (N-1)-flows, we'll simply create a new set of queues
    // for each (N-1)-flow, i.e. 1:1

    RMTQueue* inputQueue = rmtQM->addQueue(RMTQueue::INPUT);
    RMTQueue* outputQueue = rmtQM->addQueue(RMTQueue::OUTPUT);

    rmtModuleIn->connectTo(inputQueue->getInputGate());
    outputQueue->getOutputGate()->connectTo(rmtModuleOut);

    return outputQueue;
}

/**
 * Prefixes given port-id (originally returned by an FAI) with IPC process's ID
 * to prevent name collisions in current IPC process.
 *
 * @param ipcName module identifier of an underlying IPC process
 * @param flowPortId original portId to be expanded
 * @return normalized port-id
 */
std::string RA::normalizePortId(std::string ipcName, int flowPortId)
{
    std::ostringstream newPortId;
    newPortId << ipcName << '_' << flowPortId;
    return newPortId.str();
}

/**
 * Creates an (N-1)-flow (this is the mechanism behind Allocate() call).
 *
 * @param flow specified flow object
 */
void RA::createFlow(Flow *flow)
{
    Enter_Method("createFlow()");

    //Ask DA which IPC to use to reach dst App
    const Address* ad = difAllocator->resolveApnToBestAddress(flow->getDstApni().getApn());
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << flow->getDstApni().getApn() << endl;
        return;
    }
    Address addr = *ad;

    //TODO: Vesely - New IPC must be enrolled or DIF created
    if (!difAllocator->isDifLocal(addr.getDifName())) {
        EV << "Local CS does not have any IPC in DIF " << addr.getDifName() << endl;
        return;
    }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = difAllocator->getDifMember(addr.getDifName());
    FABase* fab = difAllocator->findFaInsideIpc(targetIpc);

    //Command target FA to allocate flow
    bool status = fab->receiveAllocateRequest(flow);

    //FIXME: Vesely - WAIT!

    //If AllocationRequest ended by creating connections
    if (status)
    {
        // connect the new flow to the RMT
        RMTQueue* outQ = bindLowerFlowToRmtQueue(targetIpc, flow);
        // we're ready to go!
        // update the flow table
        flTable->insert(flow, fab, outQ);
        // update the PDU forwarding table
        fwTable->insert(Address(flow->getDstApni().getApn().getName()), flow->getConId().getQoSId(), outQ);
    }
    else
    {
       EV << "Flow not allocated!" << endl;
    }
}

/**
 * Creates an (N-1)-flow (this is the mechanism behind response to an M_CREATE request).
 *
 * @param flow specified flow object
 */
void RA::createFlowWithoutAllocate(Flow* flow) {
    Enter_Method("createFlowWoAlloc()");

    //Ask DA which IPC to use to reach dst App
    const Address* ad = difAllocator->resolveApnToBestAddress(flow->getDstApni().getApn());
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << flow->getDstApni().getApn() << endl;
        signalizeCreateFlowNegativeToRibd(flow);
        return;
    }
    Address addr = *ad;

    //TODO: Vesely - New IPC must be enrolled or DIF created
    if (!difAllocator->isDifLocal(addr.getDifName())) {
        EV << "Local CS does not have any IPC in DIF " << addr.getDifName() << endl;
        signalizeCreateFlowNegativeToRibd(flow);
        return;
    }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = difAllocator->getDifMember(addr.getDifName());
    FABase* fab = difAllocator->findFaInsideIpc(targetIpc);

    // connect the new flow to the RMT
    RMTQueue* outQ = bindLowerFlowToRmtQueue(targetIpc, flow);
    // we're ready to go!
    // update the flow table
    flTable->insert(flow, fab, outQ);
    // update the PDU forwarding table
    fwTable->insert(Address(flow->getDstApni().getApn().getName()), flow->getConId().getQoSId(), outQ);

    signalizeCreateFlowPositiveToRibd(flow);
}

void RA::initSignalsAndListeners() {
    cModule* catcher2 = this->getParentModule()->getParentModule();

    sigRACreFloPosi = registerSignal(SIG_RA_CreateFlowPositive);
    sigRACreFloNega = registerSignal(SIG_RA_CreateFlowNegative);

    lisRACreFlow = new LisRACreFlow(this);
    catcher2->subscribe(SIG_RIBD_CreateFlow, lisRACreFlow);



}

/**
 * Creates a binding between a flow in this IPC and medium defined in NED
 * @param flow specified flow object
 *
 */
void RA::bindFlowToMedium(Flow* flow)
{
    EV << "binding a flow to the medium" << endl;

    RMTQueue* outQueue = rmtQM->getFirst(RMTQueue::OUTPUT);
    rmt->addEfcpiToQueueMapping(flow->getConnectionId().getSrcCepId(), outQueue);
}

/**
 * Creates a binding between a flow in this IPC and a suitable (N-1)-flow
 *
 * @param flow specified flow object
 * @return Returns TRUE if connected onWire else return FALSE
 */
bool RA::bindFlowToLowerFlow(Flow* flow)
{
    //EV << "XXXXXXXXXXXXXX" << flow->info();
    Enter_Method("bindToLowerFlow()");
    if (rmt->isOnWire())
    {
        bindFlowToMedium(flow);
        return true;
    }

    // see if any appropriate (N-1)-flow already exists
    std::string dstAddr = flow->getDstNeighbor().getApname().getName();
    unsigned short qosId = flow->getConId().getQoSId();

    FlowTableItem* curFlow = NULL;
    curFlow = flTable->lookup(dstAddr, qosId);

    if (curFlow == NULL)
    { // we need to create a new (N-1)-flow to suit our needs
        EV << "creating an (N-1)-flow (dst AP " << dstAddr << ")" << endl;

        APNamingInfo src = APNamingInfo(APN(processName));
        APNamingInfo dst = APNamingInfo(APN(dstAddr));

        Flow *lowerFlow = new Flow(src, dst);
        lowerFlow->setQosParameters(flow->getQosParameters());
        createFlow(lowerFlow);
    }

    EV << "binding a flow to an (N-1)-flow" << endl;

    // add efcpi->rmtQueue mapping for direct multiplexing
    FlowTableItem* targetFlow = flTable->lookup(dstAddr, qosId);
    if (targetFlow == NULL)
    {
        EV << "!!! something went wrong! there isn't any suitable (N-1)-flow present for dst "
           << dstAddr << " so it won't be multiplexed further." << endl;
    }
    else
    {
        rmt->addEfcpiToQueueMapping(flow->getConnectionId().getSrcCepId(),
                                    targetFlow->getRmtQueue());
        // add another fwtable entry for direct srcApp->dstApp messages
        fwTable->insert(Address(flow->getDstAddr().getApname().getName()), qosId,
                        targetFlow->getRmtQueue());
    }

    return false;
}

void RA::signalizeCreateFlowPositiveToRibd(Flow* flow) {
    EV << "Emits CreateFlowPositive signal for flow" << endl;
    emit(sigRACreFloPosi, flow);
}

void RA::signalizeCreateFlowNegativeToRibd(Flow* flow) {
    EV << "Emits CreateFlowNegative signal for flow" << endl;
    emit(sigRACreFloNega, flow);
}
