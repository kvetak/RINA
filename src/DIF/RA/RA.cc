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
    DifAllocator = ModuleAccess<DA>(MOD_DA).get();
    cModule* hostModule = getParentModule()->getParentModule();
    rmt = (RMT*) this->getParentModule()->getParentModule()->getModuleByPath(".rmt.rmt");

    processName = hostModule->par(PAR_IPCADDR).stdstringValue();
    std::string bottomGate = hostModule->gate("southIo$o", 0)->getNextGate()->getName();

    // identify the role of IPC process in processing system
    if (bottomGate == "medium$o")
    {
        // we're on wire! this is the bottommost "interface" DIF
        // let's connect RMT to the medium
        bindMediumToRMT();
    }
    else if (bottomGate == "northIo$o")
    { // other IPC processes are below us
        if (hostModule->gateSize("northIo") > 1)
        {
            // multiple (N-1)-DIFs are present, RMT shall be relaying
            rmt->enableRelay();
        }
        else
        {
            // we're on top of a single IPC process, RMT will only multiplex
        }
    }

    initQoSCubes();
    initSignalsAndListeners();

    WATCH_LIST(this->QosCubes);
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
        int avgBand                 = VAL_QOSPARAMDONOTCARE;    //Average bandwidth (measured at the application in bits/sec)
        int avgSDUBand              = VAL_QOSPARAMDONOTCARE;    //Average SDU bandwidth (measured in SDUs/sec)
        int peakBandDuration        = VAL_QOSPARAMDONOTCARE;    //Peak bandwidth-duration (measured in bits/sec);
        int peakSDUBandDuration     = VAL_QOSPARAMDONOTCARE;    //Peak SDU bandwidth-duration (measured in SDUs/sec);
        int burstPeriod             = VAL_QOSPARAMDONOTCARE;    //Burst period measured in useconds
        int burstDuration           = VAL_QOSPARAMDONOTCARE;    //Burst duration, measured in usecs fraction of Burst Period
        int undetectedBitErr        = VAL_QOSPARAMDONOTCARE;    //Undetected bit error rate measured as a probability
        int maxSDUsize              = VAL_QOSPARAMDONOTCARE;    //MaxSDUSize measured in bytes
        bool partDeliv              = VAL_QOSPARAMDEFBOOL;      //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
        bool incompleteDeliv        = VAL_QOSPARAMDEFBOOL;      //Incomplete Delivery - Can SDUs with missing pieces be delivered?
        bool forceOrder             = VAL_QOSPARAMDEFBOOL;      //Must SDUs be delivered in order?
        unsigned int maxAllowGap    = VAL_QOSPARAMDONOTCARE;    //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
        int delay                   = VAL_QOSPARAMDONOTCARE;    //Delay in usecs
        int jitter                  = VAL_QOSPARAMDONOTCARE;    //Jitter in usecs2
        int costtime                = VAL_QOSPARAMDONOTCARE;    //measured in $/ms
        int costbits                = VAL_QOSPARAMDONOTCARE;    //measured in $/Mb

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), ELEM_AVGBW) ) {
                avgBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (avgBand < 0)
                    avgBand = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_AVGSDUBW)) {
                avgSDUBand = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (avgSDUBand < 0)
                    avgSDUBand = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_PEAKBWDUR)) {
                peakBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (peakBandDuration < 0)
                    peakBandDuration = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_PEAKSDUBWDUR)) {
                peakSDUBandDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (peakSDUBandDuration < 0)
                    peakSDUBandDuration = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_BURSTPERIOD)) {
                burstPeriod = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (burstPeriod < 0)
                    burstPeriod = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_BURSTDURATION)) {
                burstDuration = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (burstDuration < 0)
                    burstDuration = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_UNDETECTBITERR)) {
                undetectedBitErr = n->getNodeValue() ? atof(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (undetectedBitErr < 0 || undetectedBitErr > 1 )
                    undetectedBitErr = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_MAXSDUSIZE)) {
                maxSDUsize = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (maxSDUsize < 0)
                    maxSDUsize = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_PARTIALDELIVER)) {
                partDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDEFBOOL;
            }
            else if (!strcmp(n->getTagName(), ELEM_INCOMPLETEDELIVER)) {
                incompleteDeliv = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDEFBOOL;
            }
            else if (!strcmp(n->getTagName(), ELEM_FORCEORDER)) {
                forceOrder = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDEFBOOL;
            }
            else if (!strcmp(n->getTagName(), ELEM_MAXALLOWGAP)) {
                maxAllowGap = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (maxAllowGap < 0)
                    maxAllowGap = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_DELAY)) {
                delay = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (delay < 0)
                    delay = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_JITTER)) {
                jitter = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDONOTCARE;
                if (jitter < 0)
                    jitter = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_COSTTIME)) {
                costtime = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDEFBOOL;
                if (costtime < 0)
                    costtime = VAL_QOSPARAMDONOTCARE;
            }
            else if (!strcmp(n->getTagName(), ELEM_COSTBITS)) {
                costbits = n->getNodeValue() ? atoi(n->getNodeValue()) : VAL_QOSPARAMDEFBOOL;
                if (costbits < 0)
                    costbits = VAL_QOSPARAMDONOTCARE;
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
        std::stringstream os;
        os << this->getFullPath() << " does not have any QoSCube in its set. It cannot work without at least one valid QoS cube!" << endl;
        error(os.str().c_str());
    }
}

void RA::initSignalsAndListeners() {
/*
    FABase* fa = ModuleAccess<FABase>(MOD_FA).get();
    //Register signals
    sigFACreReq = registerSignal("CreateRequestFlow");
    sigFACreRes = registerSignal("CreateResponseFlow");
    sigDelReq = registerSignal("DeleteRequestFlow");
    sigDelRes = registerSignal("DeleteResponseFlow");
    //Subscribe FA signals
    //this->getParentModule()->getParentModule()->subscribe("CreateRequest",  lCreReq);
    fa->lisCreReq = new LisFACreReq(fa);
    this->subscribe(sigFACreReq,  fa->lisCreReq);
    fa->lisCreRes = new LisFACreRes(fa);
    this->subscribe(sigFACreRes, fa->lisCreRes);
    fa->lisDelReq = new LisFADelReq(fa);
    this->subscribe(sigDelReq,  fa->lisDelReq);
    fa->lisDelRes = new LisFADelRes(fa);
    this->subscribe(sigDelRes, fa->lisDelRes);
*/
}

void RA::handleMessage(cMessage *msg)
{

}

/**
 * Connects the RMT module to the medium defined in NED.
 * Used only for the bottom IPC process in a processing system.
 */
void RA::bindMediumToRMT()
{
    rmt->createSouthGate("rmtIo_PHY");
    cGate* rmtIn = rmt->getParentModule()->gateHalf("rmtIo_PHY", cGate::INPUT);
    cGate* rmtOut = rmt->getParentModule()->gateHalf("rmtIo_PHY", cGate::OUTPUT);

    cModule* thisIpc = this->getParentModule()->getParentModule();
    cGate* thisIpcIn = thisIpc->gateHalf("southIo$i", cGate::INPUT, 0);
    cGate* thisIpcOut = thisIpc->gateHalf("southIo$o", cGate::OUTPUT, 0);

    rmtOut->connectTo(thisIpcOut);
    thisIpcIn->connectTo(rmtIn);
}

/**
 * Connects the RMT module to the specified (N-1)-flow.
 *
 * @param ipc IPC process containing the (N-1)-flow
 * @param flow the (N-1)-flow
 */
void RA::bindFlowToRMT(cModule* ipc, Flow* flow)
{
    std::ostringstream rmtPortId;
    rmtPortId << "rmtIo_"
              << ipc->getFullName()
              << '_' << flow->getSrcPortId() << endl;

    rmt->createSouthGate(rmtPortId.str());

    // get (N-1)-IPC gates
    std::ostringstream bottomIpcGate;
    bottomIpcGate << "northIo_" << flow->getSrcPortId();
    cGate* bottomIpcIn = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::INPUT);
    cGate* bottomIpcOut = ipc->gateHalf(bottomIpcGate.str().c_str(), cGate::OUTPUT);

    // get RMT gates
    cGate* rmtIn = rmt->getParentModule()->gateHalf(rmtPortId.str().c_str(), cGate::INPUT);
    cGate* rmtOut = rmt->getParentModule()->gateHalf(rmtPortId.str().c_str(), cGate::OUTPUT);

    // create an intermediate border gate
    cModule* thisIpc = this->getParentModule()->getParentModule();
    std::ostringstream thisIpcGate;
    thisIpcGate << "southIo_"
                << ipc->getFullName()
                << '_' << flow->getSrcPortId() << endl;

    thisIpc->addGate(thisIpcGate.str().c_str(), cGate::INOUT, false);
    cGate* thisIpcIn = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::INPUT);
    cGate* thisIpcOut = thisIpc->gateHalf(thisIpcGate.str().c_str(), cGate::OUTPUT);


    bottomIpcOut->connectTo(thisIpcIn);
    thisIpcIn->connectTo(rmtIn);

    rmtOut->connectTo(thisIpcOut);
    thisIpcOut->connectTo(bottomIpcIn);

}

/**
 * Creates an (N-1)-flow.
 *
 * @param dstIpc address of the destination IPC process
 */
void RA::createFlow(std::string dstIpc)
{
    EV << "allocating an (N-1)-flow for IPC " << processName << endl;

    /*XXX: Vesely @Hykel ->
     *     Vytvaret Flow, ve kterem je SrcAPNI klasicke aplikacni jmeno
     *     a DstAPNI adresa IPC, je nepochybne spatne. Flow object jako takovy
     *     uz existuje a ty si v nem MAXIMALNE prepises nejake hodnoty.
     *     Chapu, ze zbytek metody je Ctrl+C+V nad obdobnou metodou v IRM,
     *     ale svou cinnosti je to rozhodne spatny koncept 8-X Prepracovat, predelat!
     */
    APNamingInfo src = APNamingInfo(APN(processName));
    APNamingInfo dst = APNamingInfo(APN(dstIpc));
    Flow *fl = new Flow(src, dst);

    //Ask DA which IPC to use to reach dst App
    cModule* ipc = DifAllocator->resolveApnToIpc(fl->getDstApni().getApn());
    FABase* fa = DifAllocator->resolveApnToFa(fl->getDstApni().getApn());


    bool status = false;
    if (fa)
        //signalizeAllocateRequest(flow);
        status = fa->receiveAllocateRequest(fl);
    else
        EV << "DA does not know target application" << endl;

    if (status)
        // connect the new flow to the RMT
        bindFlowToRMT(ipc, fl);
    else
        EV << "Flow not allocated!" << endl;
}

/*
void RA::signalizeFADeleteResponseFlow() {
    emit(sigDelRes, true);
}

void RA::signalizeFACreateResponseFlow() {
    emit(sigFACreRes, true);
}

void RA::signalizeFADeleteRequestFlow() {
    emit(sigDelReq, true);
}

void RA::signalizeFACreateRequestFlow() {
    //EV << "Sending... " << getSignalName(sigFACreReq) << endl;
    emit(sigFACreReq, true);
}
*/
