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

void RA::initialize(int stage)
{
    if (stage == 1)
    {
        // determine and set RMT mode of operation
        setRmtMode();
        initFlowAlloc();
        return;
    }

    // retrieve pointers to other modules
    thisIpc = this->getParentModule()->getParentModule();
    rmtModule = thisIpc->getSubmodule("rmt");

    /* Get access to the forwarding and routing functionalities... */
    fwdtg = ModuleAccess<PDUFwdTabGenerator>("pduFwdTabGenerator").get();

    difAllocator = check_and_cast<DA*>
        (getModuleByPath("^.^.^.difAllocator.da"));
    fwTable = check_and_cast<PDUForwardingTable*>
        (getModuleByPath("^.pduForwardingTable"));
    flTable = check_and_cast<NM1FlowTable*>
        (getModuleByPath("^.nm1FlowTable"));
    rmt = check_and_cast<RMT*>
        (getModuleByPath("^.^.rmt.rmt"));
    rmtQM = check_and_cast<RMTQueueManager*>
        (getModuleByPath("^.^.rmt.rmtQueueManager"));

    // retrieve pointers to policies
    qAllocPolicy = check_and_cast<QueueAllocBase*>
        (getModuleByPath("^.queueAllocPolicy"));

    // initialize attributes
    std::ostringstream os;
    os << thisIpc->par(PAR_IPCADDR).stringValue() << "_"
       << thisIpc->par(PAR_DIFNAME).stringValue();
    processName  = os.str();

    initSignalsAndListeners();
    initQoSCubes();

    WATCH_LIST(this->QosCubes);
}

void RA::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (!opp_strcmp(msg->getName(), "RA-CreateFlow"))
        {
            createNM1Flow(preparedFlows.front());
            preparedFlows.pop_front();
            delete msg;
        }
    }
}

void RA::initSignalsAndListeners()
{
    sigRACreFloPosi = registerSignal(SIG_RA_CreateFlowPositive);
    sigRACreFloNega = registerSignal(SIG_RA_CreateFlowNegative);

    lisRAAllocResPos = new LisRAAllocResPos(this);
    thisIpc->subscribe(SIG_FAI_AllocateResponsePositive, lisRAAllocResPos);

    lisRACreAllocResPos = new LisRACreAllocResPos(this);
    thisIpc->subscribe(SIG_FAI_CreateFlowResponsePositive, lisRACreAllocResPos);

    lisRACreFlow = new LisRACreFlow(this);
    thisIpc->subscribe(SIG_RIBD_CreateFlow, lisRACreFlow);

    lisRACreResPosi = new LisRACreResPosi(this);
    thisIpc->getParentModule()->
            subscribe(SIG_RIBD_CreateFlowResponsePositive, this->lisRACreResPosi);
}

void RA::initFlowAlloc()
{
    cXMLElement* dirXml = par("flows").xmlValue();
    cXMLElementList map = dirXml->getChildrenByTagName("Flow");

    for (cXMLElementList::const_iterator it = map.begin(); it != map.end(); ++it)
    {
        cXMLElement* m = *it;

        const char* apn = m->getAttribute("apn");
        unsigned short qosId = (unsigned short)atoi(m->getAttribute("qosCube"));

        APNamingInfo src = APNamingInfo(APN(processName));
        APNamingInfo dst = APNamingInfo(APN(apn));

        const QoSCube* qosCube = getQosCubeById(qosId);
        if (qosCube == NULL)
        {
            EV << "!!! Invalid QoS-id provided for flow with dst " << apn
               << "! Allocation won't be initiated." << endl;
            return;
        }

        Flow *fl = new Flow(src, dst);
        fl->setQosParameters(*qosCube);

        preparedFlows.push_back(fl);
        cMessage* msg = new cMessage("RA-CreateFlow");
        scheduleAt(simTime(), msg);
    }
}

/**
 * Sets up RMT's mode of operation by "layer" of this IPC process
 *
 * @param m1 first module
 * @param m2 second module
 * @param n1 first module gate name
 * @param n2 second module gate name
 */
void RA::setRmtMode()
{
    // identify the role of this IPC process in processing system
    std::string bottomGate = thisIpc->gate("southIo$o", 0)->getNextGate()->getName();

    if (bottomGate == "medium$o")
    {
        // we're on wire! this is the bottommost "interface" DIF
        rmt->setOnWire(true);
        // connect RMT to the medium
        bindMediumToRMT();
    }
    else if (bottomGate == "northIo$i")
    { // other IPC processes are below us
        rmt->setOnWire(false);
    }

    if (thisIpc->par("relay").boolValue() == true)
    { // this is an IPC process that uses PDU forwarding
        rmt->enableRelay();
    }
}

/**
 * Initializes QoS cubes from given XML configuration directive.
 *
 */
void RA::initQoSCubes()
{
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

        QoSCube cube;
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


/**
 * Convenience function for interconnecting two modules.
 * TODO: convert this into a global utility method so others can use it
 *
 * @param m1 first module
 * @param m2 second module
 * @param n1 first module gate name
 * @param n2 second module gate name
 */
void RA::interconnectModules(cModule* m1, cModule* m2, std::string n1, std::string n2)
{
    if (!m1->hasGate(n1.c_str()))
    {
        m1->addGate(n1.c_str(), cGate::INOUT, false);
    }
    cGate* m1In = m1->gateHalf(n1.c_str(), cGate::INPUT);
    cGate* m1Out = m1->gateHalf(n1.c_str(), cGate::OUTPUT);

    if (!m2->hasGate(n2.c_str()))
    {
        m2->addGate(n2.c_str(), cGate::INOUT, false);
    }
    cGate* m2In = m2->gateHalf(n2.c_str(), cGate::INPUT);
    cGate* m2Out = m2->gateHalf(n2.c_str(), cGate::OUTPUT);

    if (m2->getParentModule() == m1)
    {
        m1In->connectTo(m2In);
        m2Out->connectTo(m1Out);
    }
    else
    {
        m1Out->connectTo(m2In);
        m2Out->connectTo(m1In);
    }
}


/**
 * Connects the medium defined in NED to the RMT module.
 * Used only for bottom IPC processes in a computing systems.
 *
 * @return mock (N-1)-port for the interface
 */
void RA::bindMediumToRMT()
{
    // retrieve the south gate
    cGate* thisIpcIn = thisIpc->gateHalf("southIo$i", cGate::INPUT, 0);
    cGate* thisIpcOut = thisIpc->gateHalf("southIo$o", cGate::OUTPUT, 0);

    //// connect bottom of this IPC to rmtModule
    // create an INOUT gate on the bottom of rmtModule
    std::ostringstream rmtGate;
    rmtGate << GATE_SOUTHIO_ << "PHY";
    rmtModule->addGate(rmtGate.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(rmtGate.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(rmtGate.str().c_str(), cGate::OUTPUT);

    rmtModuleOut->connectTo(thisIpcOut);
    thisIpcIn->connectTo(rmtModuleIn);

    // create a mock "(N-1)-port" for interface
    RMTPort* port = rmtQM->addPort(NULL);
    // connect the port to the bottom
    interconnectModules(rmtModule, port, rmtGate.str(), std::string(GATE_SOUTHIO));

    // create extra queues for management purposes
    rmtQM->addMgmtQueues(port);
    // apply queue allocation policy handler
    qAllocPolicy->onNM1PortInit(port);
}

/**
 * Connects the specified (N-1)-flow to the RMT.
 *
 * @param bottomIpc IPC process containing the (N-1)-flow
 * @param fab the (N-1)-FA
 * @param flow the (N-1)-flow
 * @return RMT port (handle) for the (N-1)-flow
 */
RMTPort* RA::bindNM1FlowToRMT(cModule* bottomIpc, FABase* fab, Flow* flow)
{
    // get (N-1)-port-id and expand it so it's unambiguous within this IPC
    int portId = flow->getSrcPortId();
    std::string combinedPortId = normalizePortId(bottomIpc->getFullName(), portId);

    // binding begins at the bottom and progresses upwards:
    // 1) interconnect bottom IPC <-> this IPC <-> compound RMT module
    std::ostringstream bottomIpcGate, thisIpcGate;
    bottomIpcGate << GATE_NORTHIO_ << portId;
    thisIpcGate << GATE_SOUTHIO_ << combinedPortId;
    interconnectModules(bottomIpc, thisIpc, bottomIpcGate.str(), thisIpcGate.str());
    interconnectModules(thisIpc, rmtModule, thisIpcGate.str(), thisIpcGate.str());

    // 2) attach a RMTPort instance (pretty much a representation of an (N-1)-port)
    RMTPort* port = rmtQM->addPort(flow);
    interconnectModules(rmtModule, port, thisIpcGate.str(), std::string(GATE_SOUTHIO));

    // 3) allocate queues
    // create extra queues for management purposes (this will likely go away later)
    rmtQM->addMgmtQueues(port);
    // apply queue allocation policy handler
    qAllocPolicy->onNM1PortInit(port);    

    // 4) update the flow table
    flTable->insert(flow, fab, port, thisIpcGate.str().c_str());

    return port;
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
 * Invokes allocation of an (N-1)-flow (this is the mechanism behind Allocate() call).
 *
 * @param flow specified flow object
 */
void RA::createNM1Flow(Flow *flow)
{
    Enter_Method("createNM1Flow()");

    const APN& dstApn = flow->getDstApni().getApn();

    //Ask DA which IPC to use to reach dst App
    const Address* ad = difAllocator->resolveApnToBestAddress(dstApn);
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << dstApn << endl;
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
        RMTPort* port = bindNM1FlowToRMT(targetIpc, fab, flow);
        // update the PDU forwarding table

        //fwTable->insert(Address(flow->getDstApni().getApn().getName()),
        //                flow->getConId().getQoSId(), port);

        fwdtg->insertFlowInfo(
            Address(flow->getDstApni().getApn().getName()),
            flow->getConId().getQoSId(),
            port);
    }
    else
    {
        EV << "Flow not allocated!" << endl;
    }
}

/**
 * Handles receiver-side allocation of an (N-1)-flow requested by other IPC.
 * (this is the mechanism behind M_CREATE_R).
 *
 * @param flow specified flow object
 */
void RA::createNM1FlowWithoutAllocate(Flow* flow)
{
    Enter_Method("createNM1FlowWoAlloc()");

    const APN& dstApn = flow->getDstApni().getApn();
    unsigned short qosId = flow->getConId().getQoSId();

    //Ask DA which IPC to use to reach dst App
    const Address* ad = difAllocator->resolveApnToBestAddress(dstApn);
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << dstApn << endl;
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

    // attach the new flow to RMT
    RMTPort* port = bindNM1FlowToRMT(targetIpc, fab, flow);
    // update the PDU forwarding table

    //fwTable->insert(Address(flow->getDstApni().getApn().getName()),
    //                        flow->getConId().getQoSId(), port);

    fwdtg->insertFlowInfo(
        Address(flow->getDstApni().getApn().getName()),
        flow->getConId().getQoSId(),
        port);

    // add other accessible applications into forwarding table
    const APNList* remoteApps = difAllocator->findNeigborApns(dstApn);
    if (remoteApps)
    {
        for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it)
        {
            Address addr = Address(it->getName());

            //fwTable->insert(addr, flow->getConId().getQoSId(), port);

            fwdtg->insertFlowInfo(addr, flow->getConId().getQoSId(), port);
        }
    }

    signalizeCreateFlowPositiveToRibd(flow);

    // mark this flow as connected
    flTable->findFlowByDstApni(dstApn.getName(), qosId)->
            setConnectionStatus(NM1FlowTableItem::CON_ESTABLISHED);
}

/**
 * Event hook handler invoked after an (N)-flow is successfully established
 *
 * @param flow established (N)-flow
 */
void RA::postNFlowAllocation(Flow* flow)
{
    Enter_Method("postNFlowAllocation()");

    // invoke QueueAlloc policy on relevant (N-1)-ports
    if (rmt->isOnWire())
    {
        qAllocPolicy->onNFlowAlloc(rmtQM->getInterfacePort(), flow);
    }
    else
    {
        const std::string& neighApn = flow->getDstNeighbor().getApname().getName();
        unsigned short qosId = flow->getConId().getQoSId();

        NM1FlowTableItem* item = flTable->findFlowByDstApni(neighApn, qosId);
        if (item != NULL)
        {
            qAllocPolicy->onNFlowAlloc(item->getRmtPort(), flow);
        }
    }
}

/**
 * Event hook handler invoked after an (N-1)-flow is successfully established
 *
 * @param flow established (N-1)-flow
 */
void RA::postNM1FlowAllocation(Flow* flow)
{
    Enter_Method("postNM1FlowAllocation()");

    const APN& dstApn = flow->getDstApni().getApn();
    unsigned short qosId = flow->getConId().getQoSId();

    // TODO: move this to receiveSignal()
    NM1FlowTableItem* item = flTable->findFlowByDstApni(dstApn.getName(), qosId);
    if (item == NULL) return;

    // add other accessible applications into the forwarding table
    const APNList* remoteApps = difAllocator->findNeigborApns(dstApn);
    if (remoteApps)
    {
        for (ApnCItem it = remoteApps->begin(); it != remoteApps->end(); ++it)
        {
            Address addr = Address(it->getName());
            fwTable->insert(addr, qosId, item->getRmtPort());
        }
    }

    // mark this flow as connected
    item->setConnectionStatus(NM1FlowTableItem::CON_ESTABLISHED);
}

/**
 * Removes specified (N-1)-flow and bindings (this is the mechanism behind Deallocate() call).
 *
 * @param flow specified flow object
 */
void RA::removeNM1Flow(Flow *flow)
{ // TODO: part of this should be split into something like postNM1FlowDeallocation

    NM1FlowTableItem* flowItem = flTable->lookup(flow);
    flowItem->setConnectionStatus(NM1FlowTableItem::CON_RELEASING);

    RMTPort* port = flowItem->getRmtPort();
    const char* gateName = flowItem->getGateName().c_str();
    cGate* thisIpcIn = thisIpc->gateHalf(gateName, cGate::INPUT);
    cGate* thisIpcOut = thisIpc->gateHalf(gateName, cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName, cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(gateName, cGate::OUTPUT);
    cGate* portOut = port->getSouthOutputGate();

    portOut->disconnect();
    thisIpcIn->disconnect();
    thisIpcOut->disconnect();
    rmtModuleIn->disconnect();
    rmtModuleOut->disconnect();

    fwdtg->removeFlowInfo(flowItem->getRmtPort());
    //fwTable->remove(flowItem->getFlow());
    rmtQM->removePort(flowItem->getRmtPort());
    rmtModule->deleteGate(gateName);
    flowItem->getFaBase()->receiveDeallocateRequest(flow);

    thisIpc->deleteGate(gateName);
    flTable->remove(flow);
}

/**
 * Assigns a suitable (N-1)-flow to the (N)-flow (and creates one if there isn't any)
 *
 * @param flow specified flow object
 * @return true if an interface or an (N-1)-flow is ready to serve, false otherwise
 */
bool RA::bindNFlowToNM1Flow(Flow* flow)
{
    Enter_Method("bindNFlowToNM1Flow()");

    if (rmt->isOnWire())
    { // nothing to be done
        return true;
    }

    std::string dstAddr = flow->getDstAddr().getApname().getName();
    // immediate neighbor (e.g. an interior router)
    std::string neighAddr = flow->getDstNeighbor().getApname().getName();
    unsigned short qosId = flow->getConId().getQoSId();

    // see if any appropriate (N-1)-flow already exists
    NM1FlowTableItem* nm1FlowItem = flTable->findFlowByDstApni(neighAddr, qosId);

    if (nm1FlowItem == NULL)
    { // we need to allocate a new (N-1)-flow to suit our needs
        EV << getFullName()
           << " allocating an (N-1)-flow (dstApp " << neighAddr << ")" << endl;

        APNamingInfo src = APNamingInfo(APN(processName));
        APNamingInfo dst = APNamingInfo(APN(neighAddr));

        Flow *nm1Flow = new Flow(src, dst);
        // FIXME: useless, appropriate QoS class has to be chosen by some algorithm
        nm1Flow->setQosParameters(flow->getQosParameters());
        // initiate flow creation
        createNM1Flow(nm1Flow);
        // repeat the lookup
        nm1FlowItem = flTable->findFlowByDstApni(neighAddr, qosId);

        if (nm1FlowItem == NULL)
        {
            EV << "!!! not able to allocate (N-1)-flow for " << neighAddr << endl;
            return false;
        }
    }

    // add another fwtable entry for direct srcApp->dstApp messages (if needed)
    // TODO: there must be a better place to put this
    if (neighAddr != dstAddr)
    {
        fwTable->insert(Address(dstAddr), qosId, nm1FlowItem->getRmtPort());
    }

    if (nm1FlowItem->getConnectionStatus() == NM1FlowTableItem::CON_ESTABLISHED)
    {
        return true;
    }
    else
    {
        //rmt->addEfcpiToQueueMapping(flow->getConnectionId().getSrcCepId(),
        //                            targetFlow->getRmtOutputQueues().front());
        // add another fwtable entry for direct srcApp->dstApp messages (if needed)
        //if (neighAddr != dstAddr)
        //{
        //    fwdtg->insertFlowInfo(Address(dstAddr), qosId, targetFlow->getRmtPort());
            //fwTable->insert(Address(dstAddr), qosId, targetFlow->getRmtPort());
        //}

        return false;
    }
}


void RA::signalizeCreateFlowPositiveToRibd(Flow* flow)
{
    emit(sigRACreFloPosi, flow);
}

void RA::signalizeCreateFlowNegativeToRibd(Flow* flow)
{
    emit(sigRACreFloNega, flow);
}
