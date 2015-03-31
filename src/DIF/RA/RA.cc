//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
const char* ELEM_QOSCUBE             = "QoSCube";
const char* ATTR_ID                  = "id";
const char* ELEM_AVGBW               = "AverageBandwidth";
const char* ELEM_AVGSDUBW            = "AverageSDUBandwidth";
const char* ELEM_PEAKBWDUR           = "PeakBandwidthDuration";
const char* ELEM_PEAKSDUBWDUR        = "PeakSDUBandwidthDuration";
const char* ELEM_BURSTPERIOD         = "BurstPeriod";
const char* ELEM_BURSTDURATION       = "BurstDuration";
const char* ELEM_UNDETECTBITERR      = "UndetectedBitError";
const char* ELEM_PDUDROPPROBAB       = "PDUDroppingProbability";
const char* ELEM_MAXSDUSIZE          = "MaxSDUSize";
const char* ELEM_PARTIALDELIVER      = "PartialDelivery";
const char* ELEM_INCOMPLETEDELIVER   = "IncompleteDelivery";
const char* ELEM_FORCEORDER          = "ForceOrder";
const char* ELEM_MAXALLOWGAP         = "MaxAllowableGap";
const char* ELEM_DELAY               = "Delay";
const char* ELEM_JITTER              = "Jitter";
const char* ELEM_COSTTIME            = "CostTime";
const char* ELEM_COSTBITS            = "CostBits";
const char* ELEM_ATIME               = "ATime";

void RA::initialize(int stage)
{
    if (stage == 1)
    {
        // determine and set RMT mode of operation
        setRMTMode();
        initFlowAlloc();
        return;
    }

    // retrieve pointers to other modules
    thisIPC = this->getParentModule()->getParentModule();
    rmtModule = thisIPC->getSubmodule("relayAndMux");

    // Get access to the forwarding and routing functionalities...
    fwdtg = check_and_cast<IntPDUFG *>
        (getModuleByPath("^.pduFwdGenerator"));


    difAllocator = check_and_cast<DA*>
        (getModuleByPath("^.^.^.difAllocator.da"));
    flowTable = check_and_cast<NM1FlowTable*>
        (getModuleByPath("^.nm1FlowTable"));
    rmt = check_and_cast<RMT*>
        (getModuleByPath("^.^.relayAndMux.rmt"));
    rmtAllocator = check_and_cast<RMTModuleAllocator*>
        (getModuleByPath("^.^.relayAndMux.allocator"));

    // retrieve pointers to policies
    qAllocPolicy = check_and_cast<QueueAllocBase*>
        (getModuleByPath("^.queueAllocPolicy"));

    // initialize attributes
    std::ostringstream os;
    os << thisIPC->par(PAR_IPCADDR).stringValue() << "_"
       << thisIPC->par(PAR_DIFNAME).stringValue();
    processName  = os.str();

    initSignalsAndListeners();
    initQoSCubes();

    WATCH_LIST(this->QoSCubes);
}

void RA::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        if (!opp_strcmp(msg->getName(), "RA-CreateConnections"))
        {
            std::list<Flow*>* flows = preparedFlows[simTime()];

            while (!flows->empty())
            {
                createNM1Flow(flows->front());
                flows->pop_front();
            }

            delete flows;
            delete msg;
        }
    }
}

void RA::initSignalsAndListeners()
{
    sigRACreFloPosi = registerSignal(SIG_RA_CreateFlowPositive);
    sigRACreFloNega = registerSignal(SIG_RA_CreateFlowNegative);
    sigRASDReqFromRMT = registerSignal(SIG_RA_InvokeSlowdown);
    sigRASDReqFromRIB = registerSignal(SIG_RA_ExecuteSlowdown);

    lisRAAllocResPos = new LisRAAllocResPos(this);
    thisIPC->subscribe(SIG_FAI_AllocateResponsePositive, lisRAAllocResPos);

    lisRACreAllocResPos = new LisRACreAllocResPos(this);
    thisIPC->subscribe(SIG_FAI_CreateFlowResponsePositive, lisRACreAllocResPos);

    lisRACreFlow = new LisRACreFlow(this);
    thisIPC->subscribe(SIG_RIBD_CreateFlow, lisRACreFlow);

    lisRACreResPosi = new LisRACreResPosi(this);
    thisIPC->getParentModule()->
            subscribe(SIG_RIBD_CreateFlowResponsePositive, this->lisRACreResPosi);

    lisEFCPStopSending = new LisEFCPStopSending(this);
    thisIPC->getParentModule()->
            subscribe(SIG_EFCP_StahpSending, this->lisEFCPStopSending);

    lisEFCPStartSending = new LisEFCPStartSending(this);
    thisIPC->getParentModule()->
            subscribe(SIG_EFCP_StartSending, this->lisEFCPStartSending);

    lisRMTSDReq = new LisRMTSlowdownRequest(this);
    thisIPC->subscribe(SIG_RMT_SlowdownRequest, this->lisRMTSDReq);

    lisRIBCongNotif = new LisRIBCongNotif(this);
    thisIPC->subscribe(SIG_RIBD_CongestionNotification, this->lisRIBCongNotif);
}

void RA::initFlowAlloc()
{
    cXMLElement* dirXml = par("preallocation").xmlValue();
    cXMLElementList timeMap = dirXml->getChildrenByTagName("SimTime");

    for (cXMLElementList::const_iterator it = timeMap.begin(); it != timeMap.end(); ++it)
    {
        cXMLElement* m = *it;
        simtime_t time = static_cast<simtime_t>(
                atoi(m->getAttribute("t")));

        cXMLElementList connMap = m->getChildrenByTagName("Connection");
        for (cXMLElementList::const_iterator jt = connMap.begin(); jt != connMap.end(); ++jt)
        {
            cXMLElement* n = *jt;
            const char* src = n->getAttribute("src");
            if (opp_strcmp(src, processName.c_str()))
            {
                continue;
            }

            const char* dst = n->getAttribute("dst");
            unsigned short qosId = static_cast<unsigned short>(
                            atoi(n->getAttribute("qosCube")));

            APNamingInfo srcAPN = APNamingInfo(APN(src));
            APNamingInfo dstAPN = APNamingInfo(APN(dst));
            const QoSCube* qosCube = getQoSCubeById(qosId);
            if (qosCube == NULL)
            {
                EV << "!!! Invalid QoS-id provided for flow with dst " << dst
                   << "! Allocation won't be initiated." << endl;
                return;
            }

            Flow *flow = new Flow(srcAPN, dstAPN);
            flow->setQosParameters(*qosCube);

            if (preparedFlows[time] == NULL)
            {
                preparedFlows[time] = new std::list<Flow*>;
                preparedFlows[time]->push_back(flow);

                cMessage* msg = new cMessage("RA-CreateConnections");
                scheduleAt(simTime() + time, msg);
            }
            else
            {
                preparedFlows[time]->push_back(flow);
            }
        }
    }
}

/**
 * Sets up RMT's mode of operation by "recursion level" of this IPC process
 */
void RA::setRMTMode()
{
    // identify the role of this IPC process in processing system
    std::string bottomGate = thisIPC->gate("southIo$o", 0)->getNextGate()->getName();

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

    if (thisIPC->par("relay").boolValue() == true)
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
        //Following data types should be same as in QoSCubes.h
        int avgBand                 = VAL_QOSPARDONOTCARE;    //Average bandwidth (measured at the application in bits/sec)
        int avgSDUBand              = VAL_QOSPARDONOTCARE;    //Average SDU bandwidth (measured in SDUs/sec)
        int peakBandDuration        = VAL_QOSPARDONOTCARE;    //Peak bandwidth-duration (measured in bits/sec);
        int peakSDUBandDuration     = VAL_QOSPARDONOTCARE;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
        int burstPeriod             = VAL_QOSPARDONOTCARE;    //Burst period measured in useconds
        int burstDuration           = VAL_QOSPARDONOTCARE;    //Burst duration, measured in usecs fraction of Burst Period
        double undetectedBitErr     = VAL_QOSPARDONOTCARE;    //Undetected bit error rate measured as a probability
        double pduDropProbab        = VAL_QOSPARDONOTCARE;
        int maxSDUsize              = VAL_QOSPARDONOTCARE;    //MaxSDUSize measured in bytes
        bool partDeliv              = VAL_QOSPARDEFBOOL;      //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
        bool incompleteDeliv        = VAL_QOSPARDEFBOOL;      //Incomplete Delivery - Can SDUs with missing pieces be delivered?
        bool forceOrder             = VAL_QOSPARDEFBOOL;      //Must SDUs be delivered in order?
        unsigned int maxAllowGap    = VAL_QOSPARDONOTCARE;    //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
        int delay                   = VAL_QOSPARDONOTCARE;    //Delay in usecs
        int jitter                  = VAL_QOSPARDONOTCARE;    //Jitter in usecs2
        int costtime                = VAL_QOSPARDONOTCARE;    //measured in $/ms
        int costbits                = VAL_QOSPARDONOTCARE;    //measured in $/Mb
        double aTime               = VAL_QOSPARDONOTCARE;    //measured in ms

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
            }else if (!strcmp(n->getTagName(), ELEM_ATIME)) {
              aTime = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARDEFBOOL;
              if (aTime < 0)
                  aTime = VAL_QOSPARDONOTCARE;
          }
        }

        cube.setAvgBand(avgBand);
        cube.setAvgSduBand(avgSDUBand);
        cube.setPeakBandDuration(peakBandDuration);
        cube.setPeakSduBandDuration(peakSDUBandDuration);
        cube.setBurstPeriod(burstPeriod);
        cube.setBurstDuration(burstDuration);
        cube.setUndetectedBitErr(undetectedBitErr);
        cube.setPduDropProbability(pduDropProbab);
        cube.setMaxSduSize(maxSDUsize);
        cube.setPartialDelivery(partDeliv);
        cube.setIncompleteDelivery(incompleteDeliv);
        cube.setForceOrder(forceOrder);
        cube.setMaxAllowGap(maxAllowGap);
        cube.setDelay(delay);
        cube.setJitter(jitter);
        cube.setCostBits(costbits);
        cube.setCostTime(costtime);
        cube.setATime(aTime);

        QoSCubes.push_back(cube);
    }
    if (!QoSCubes.size()) {
        std::ostringstream os;
        os << this->getFullPath() << " does not have any QoSCube in its set. It cannot work without at least one valid QoS cube!" << endl;
        error(os.str().c_str());
    }
}


/**
 * A convenience function for interconnecting two modules.
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
 */
void RA::bindMediumToRMT()
{
    // retrieve the south gate
    cGate* thisIPCIn = thisIPC->gateHalf("southIo$i", cGate::INPUT, 0);
    cGate* thisIPCOut = thisIPC->gateHalf("southIo$o", cGate::OUTPUT, 0);

    //// connect bottom of this IPC to rmtModule
    // create an INOUT gate on the bottom of rmtModule
    std::ostringstream rmtGate;
    rmtGate << GATE_SOUTHIO_ << "PHY";
    rmtModule->addGate(rmtGate.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(rmtGate.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(rmtGate.str().c_str(), cGate::OUTPUT);

    rmtModuleOut->connectTo(thisIPCOut);
    thisIPCIn->connectTo(rmtModuleIn);

    // create a mock "(N-1)-port" for interface
    RMTPort* port = rmtAllocator->addPort(NULL);
    // connect the port to the bottom
    interconnectModules(rmtModule, port->getParentModule(), rmtGate.str(), std::string(GATE_SOUTHIO));
    // finalize initial port parameters
    port->postInitialize();
    port->setOutputReady();
    port->setInputReady();

    // create extra queues for management purposes
    rmtAllocator->addMgmtQueues(port);
    // apply queue allocation policy handler
    qAllocPolicy->onNM1PortInit(port);
}

/**
 * Connects the specified (N-1)-flow to the RMT.
 *
 * @param bottomIPC IPC process containing the (N-1)-flow
 * @param fab the (N-1)-FA
 * @param flow the (N-1)-flow
 * @return RMT port (handle) for the (N-1)-flow
 */
RMTPort* RA::bindNM1FlowToRMT(cModule* bottomIPC, FABase* fab, Flow* flow)
{
    // get (N-1)-port-id and expand it so it's unambiguous within this IPC
    int portID = flow->getSrcPortId();
    std::string combinedPortID = normalizePortID(bottomIPC->getFullName(), portID);

    // binding begins at the bottom and progresses upwards:
    // 1) interconnect bottom IPC <-> this IPC <-> compound RMT module
    std::ostringstream bottomIPCGate, thisIPCGate;
    bottomIPCGate << GATE_NORTHIO_ << portID;
    thisIPCGate << GATE_SOUTHIO_ << combinedPortID;
    interconnectModules(bottomIPC, thisIPC, bottomIPCGate.str(), thisIPCGate.str());
    interconnectModules(thisIPC, rmtModule, thisIPCGate.str(), thisIPCGate.str());

    // 2) attach a RMTPort instance (pretty much a representation of an (N-1)-port)
    RMTPort* port = rmtAllocator->addPort(flow);
    interconnectModules(rmtModule, port->getParentModule(), thisIPCGate.str(), std::string(GATE_SOUTHIO));
    // finalize initial port parameters
    port->postInitialize();

    // 3) allocate queues
    // create extra queues for management purposes (this will likely go away later)
    rmtAllocator->addMgmtQueues(port);
    // apply queue allocation policy handler
    qAllocPolicy->onNM1PortInit(port);    

    // 4) update the flow table
    flowTable->insert(flow, fab, port, thisIPCGate.str().c_str());

    return port;
}

/**
 * Prefixes given port-id (originally returned by an FAI) with IPC process's ID
 * to prevent name collisions in current IPC process.
 *
 * @param ipcName module identifier of an underlying IPC process
 * @param flowPortID original portId to be expanded
 * @return normalized port-id
 */
std::string RA::normalizePortID(std::string ipcName, int flowPortID)
{
    std::ostringstream newPortID;
    newPortID << ipcName << '_' << flowPortID;
    return newPortID.str();
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

    //
    // A flow already exists from this ipc to the destination one(passing through a neighbor)?
    //
    PDUFTGNeighbor * e = fwdtg->getNextNeighbor(flow->getDstAddr(), flow->getConId().getQoSId());

    if(e)
    {
        NM1FlowTableItem * fi = flowTable->findFlowByDstAddr(
            e->getDestAddr().getApname().getName(),
            flow->getConId().getQoSId());

        if(fi)
        {
            return;
        }
    }
    //
    // End flow exists check.
    //

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
    cModule* targetIPC = difAllocator->getDifMember(addr.getDifName());
    FABase* fab = difAllocator->findFaInsideIpc(targetIPC);

    //Command target FA to allocate flow
    bool status = fab->receiveAllocateRequest(flow);

    //If AllocationRequest ended by creating connections between this IPC's modules
    if (status)
    {
        // connect the new flow to the RMT
        RMTPort* port = bindNM1FlowToRMT(targetIPC, fab, flow);
        // TODO: remove this when management isn't piggy-backed anymore!
        // (port shouldn't be ready to send out data when the flow isn't yet allocated)
        port->setOutputReady();
        port->setInputReady();

        // invoke fwdTable insertion policy
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

    const APN& dstAPN = flow->getDstApni().getApn();
    unsigned short qosID = flow->getConId().getQoSId();

    //
    // A flow already exists from this ipc to the destination one(passing through a neighbor)?
    //
    PDUFTGNeighbor * e = fwdtg->getNextNeighbor(flow->getDstAddr(), flow->getConId().getQoSId());

    if(e)
    {
        NM1FlowTableItem * fi = flowTable->findFlowByDstAddr(
            e->getDestAddr().getApname().getName(),
            flow->getConId().getQoSId());

        if(fi)
        {
            return;
        }
    }
    //
    // End flow exists check.
    //


    // Ask DA which IPC to use to reach dst App
    const Address* ad = difAllocator->resolveApnToBestAddress(dstAPN);
    if (ad == NULL) {
        EV << "DifAllocator returned NULL for resolving " << dstAPN << endl;
        signalizeCreateFlowNegativeToRIBd(flow);
        return;
    }
    Address addr = *ad;

    //TODO: Vesely - New IPC must be enrolled or DIF created
    if (!difAllocator->isDifLocal(addr.getDifName())) {
        EV << "Local CS does not have any IPC in DIF " << addr.getDifName() << endl;
        signalizeCreateFlowNegativeToRIBd(flow);
        return;
    }

    //Retrieve DIF's local IPC member
    cModule* targetIpc = difAllocator->getDifMember(addr.getDifName());
    FABase* fab = difAllocator->findFaInsideIpc(targetIpc);

    // attach the new flow to RMT
    RMTPort* port = bindNM1FlowToRMT(targetIpc, fab, flow);
    // update the PDU forwarding table
    fwdtg->insertFlowInfo(
        Address(flow->getDstApni().getApn().getName()),
        flow->getConId().getQoSId(),
        port);

    signalizeCreateFlowPositiveToRIBd(flow);

    // mark this flow as connected
    flowTable->findFlowByDstApni(dstAPN.getName(), qosID)->
            setConnectionStatus(NM1FlowTableItem::CON_ESTABLISHED);
    port->setOutputReady();
    port->setInputReady();
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
        qAllocPolicy->onNFlowAlloc(rmtAllocator->getInterfacePort(), flow);
    }
    else
    {
        const std::string& neighApn = flow->getDstNeighbor().getApname().getName();
        unsigned short qosId = flow->getConId().getQoSId();

        NM1FlowTableItem* item = flowTable->findFlowByDstApni(neighApn, qosId);
        if (item != NULL)
        {
            qAllocPolicy->onNFlowAlloc(item->getRMTPort(), flow);
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
    NM1FlowTableItem* item = flowTable->findFlowByDstApni(dstApn.getName(), qosId);
    if (item == NULL) return;
    // mark this flow as connected
    item->setConnectionStatus(NM1FlowTableItem::CON_ESTABLISHED);
    item->getRMTPort()->setOutputReady();
    item->getRMTPort()->setInputReady();
}

/**
 * Removes specified (N-1)-flow and bindings (this is the mechanism behind Deallocate() call).
 *
 * @param flow specified flow object
 */
void RA::removeNM1Flow(Flow *flow)
{ // TODO: part of this should be split into something like postNM1FlowDeallocation

    NM1FlowTableItem* flowItem = flowTable->lookup(flow);
    ASSERT(flowItem != NULL);
    flowItem->setConnectionStatus(NM1FlowTableItem::CON_RELEASING);
    flowItem->getFABase()->receiveDeallocateRequest(flow);

    // disconnect and delete gates
    RMTPort* port = flowItem->getRMTPort();
    const char* gateName = flowItem->getGateName().c_str();
    cGate* thisIpcIn = thisIPC->gateHalf(gateName, cGate::INPUT);
    cGate* thisIpcOut = thisIPC->gateHalf(gateName, cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName, cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(gateName, cGate::OUTPUT);
    cGate* portOut = port->getSouthOutputGate()->getNextGate();

    portOut->disconnect();
    rmtModuleOut->disconnect();
    thisIpcOut->disconnect();
    thisIpcIn->disconnect();
    rmtModuleIn->disconnect();

    rmtModule->deleteGate(gateName);
    thisIPC->deleteGate(gateName);

    // remove table entries
    fwdtg->removeFlowInfo(flowItem->getRMTPort());
    rmtAllocator->removePort(flowItem->getRMTPort());
    flowTable->remove(flow);
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
    unsigned short qosID = flow->getConId().getQoSId();

    //
    // A flow already exists from this ipc to the destination one(passing through a neighbor)?
    //
    PDUFTGNeighbor * te =
        fwdtg->getNextNeighbor(flow->getDstAddr(), flow->getConId().getQoSId());

    if(te)
    {
        neighAddr = te->getDestAddr().getApname().getName();
    }

    // see if any appropriate (N-1)-flow already exists
    NM1FlowTableItem* nm1FlowItem = flowTable->findFlowByDstApni(neighAddr, qosID);

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
        nm1FlowItem = flowTable->findFlowByDstApni(neighAddr, qosID);

        if (nm1FlowItem == NULL)
        {
            EV << "!!! not able to allocate (N-1)-flow for " << neighAddr << endl;
            return false;
        }
    }

    if (nm1FlowItem->getConnectionStatus() == NM1FlowTableItem::CON_ESTABLISHED)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void RA::blockNM1PortOutput(Flow* flow)
{
    Enter_Method("blockNM1PortOutput()");

    NM1FlowTableItem* item = flowTable->lookup(flow);
    if (item == NULL)
    {
//        EV << "!!! given (N-1)-flow isn't registered in the flow table;"
//           << " ignoring pushback request." << endl;
        return;
    }

    item->getRMTPort()->blockOutput();
}

void RA::unblockNM1PortOutput(Flow* flow)
{
    Enter_Method("unblockNM1PortOutput()");

    NM1FlowTableItem* item = flowTable->lookup(flow);
    if (item == NULL)
    {
//        EV << "!!! given (N-1)-flow isn't registered in the flow table;"
//           << " ignoring port unblock request." << endl;
        return;
    }

    item->getRMTPort()->unblockOutput();
}

void RA::signalizeCreateFlowPositiveToRIBd(Flow* flow)
{
    emit(sigRACreFloPosi, flow);
}

void RA::signalizeCreateFlowNegativeToRIBd(Flow* flow)
{
    emit(sigRACreFloNega, flow);
}

void RA::signalizeSlowdownRequestToRIBd(cPacket* pdu)
{
    Enter_Method("signalizeSlowdownRequestToRIBd()");
    emit(sigRASDReqFromRMT, pdu);
}

void RA::signalizeSlowdownRequestToEFCP(cObject* obj)
{
    Enter_Method("signalizeSlowdownRequestToEFCP()");
    // TODO: move this to the listener
    CongestionDescriptor* congInfo = check_and_cast<CongestionDescriptor*>(obj);
    emit(sigRASDReqFromRIB, congInfo);
}
