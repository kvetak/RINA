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

/**
 * @file RMT.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Relaying and Multiplexing Task
 * @detail
 */

#include "DIF/RMT/RMT.h"

// shared access to trace logger
#ifndef RMT_TRACING
#define RMT_TRACING
std::ofstream rmtTraceFile;
#endif

Define_Module(RMT);

RMT::~RMT()
{
    while (!invalidPDUs.empty())
    {
        delete invalidPDUs.front();
        invalidPDUs.pop_front();
    }
}


void RMT::initialize()
{
    // set up features
    relayOn = false;
    onWire = false;
    tracing = getParentModule()->par("pduTracing").boolValue();
    if (tracing && !rmtTraceFile.is_open())
    {
        std::ostringstream filename;
        filename << "results/" << getEnvir()->getConfigEx()->getActiveConfigName() << "-"
                 << getEnvir()->getConfigEx()->getActiveRunNumber() << ".tr";
        rmtTraceFile.open(filename.str().c_str());

        if (!rmtTraceFile.is_open())
        {
            EV << "Couldn't create a trace file!" << endl;
            tracing = false;
        }
    }

    efcpiIn[0] = gateHalf("ribdIo", cGate::INPUT);
    efcpiOut[0] = gateHalf("ribdIo", cGate::OUTPUT);

    // get pointers to other components
    fwd = getRINAModule<IntPDUForwarding*>(this, 1, {MOD_POL_RMT_PDUFWD});
    rmtAllocator = getRINAModule<RMTModuleAllocator*>(this, 1, {MOD_RMTALLOC});
    schedPolicy = getRINAModule<RMTSchedulingBase*>(this, 1, {MOD_POL_RMT_SCHEDULER});
    maxQPolicy = getRINAModule<RMTMaxQBase*>(this, 1, {MOD_POL_RMT_MAXQ});
    qMonPolicy = getRINAModule<RMTQMonitorBase*>(this, 1, {MOD_POL_RMT_QMONITOR});
    qAllocPolicy = getRINAModule<QueueAllocBase*>(this, 2, {MOD_RESALLOC, MOD_POL_RA_QUEUEALLOC});
    queueIdGenerator = getRINAModule<QueueIDGenBase*>(this, 2, {MOD_RESALLOC, MOD_POL_RA_IDGENERATOR});
    addrComparator = getRINAModule<AddressComparatorBase*>(this, 2, {MOD_RESALLOC, MOD_POL_RA_ADDRCOMPARATOR});

    // register a signal for notifying others about a missing local EFCP instance
    sigRMTNoConnID = registerSignal(SIG_RMT_NoConnId);

    // register a signal for notifying others about a packet bit error
    sigRMTPacketError = registerSignal(SIG_RMT_ErrornousPacket);

    // listen for a signal indicating that a new message is to arrive into a queue
    lisRMTQueuePDUPreRcvd = new LisRMTQueuePDUPreRcvd(this);
    getParentModule()->subscribe(SIG_RMT_QueuePDUPreRcvd, lisRMTQueuePDUPreRcvd);

    // listen for a signal indicating that a new message has arrived into a queue
    lisRMTQueuePDUPostRcvd = new LisRMTQueuePDUPostRcvd(this);
    getParentModule()->subscribe(SIG_RMT_QueuePDUPostRcvd, lisRMTQueuePDUPostRcvd);

    // listen for a signal indicating that a message is leaving a queue
    lisRMTQueuePDUPreSend = new LisRMTQueuePDUPreSend(this);
    getParentModule()->subscribe(SIG_RMT_QueuePDUPreSend, lisRMTQueuePDUPreSend);

    // listen for a signal indicating that a message has left a queue
    lisRMTQueuePDUSent = new LisRMTQueuePDUSent(this);
    getParentModule()->subscribe(SIG_RMT_QueuePDUSent, lisRMTQueuePDUSent);

    // listen for a signal indicating that a port is ready to serve
    lisRMTPortReadyToServe = new LisRMTPortReadyToServe(this);
    getParentModule()->subscribe(SIG_RMT_PortReadyToServe, lisRMTPortReadyToServe);

    // listen for a signal indicating that a port is ready to be read from
    lisRMTPortReadyForRead = new LisRMTPortReadyForRead(this);
    getParentModule()->subscribe(SIG_RMT_PortReadyForRead, lisRMTPortReadyForRead);

    WATCH(relayOn);
    WATCH(onWire);
}

/**
 * Notify the user of PDUs left in this RMT on simulation end.
 */
void RMT::finish()
{
    size_t pduCount = invalidPDUs.size();
    if (pduCount)
    {
        EV << "RMT " << this->getFullPath() << " still contains " << pduCount
           << " unprocessed PDUs!" << endl;

        for (auto const& m : invalidPDUs)
        {
            EV << m->getClassName() << " received at " << m->getArrivalTime()
               << " from " << m->getSenderModule()->getFullPath() << endl;
        }
    }

    if (rmtTraceFile.is_open())
    {
        rmtTraceFile.flush();
        rmtTraceFile.close();
    }
}

/**
 * Append a line into the trace file.
 *
 * @param pkt packet
 * @param eventType event (receive/send/enqueue/dequeue/drop)
 */
void RMT::tracePDUEvent(const cPacket* pkt, TraceEventType eventType)
{
    const PDU* pdu = dynamic_cast<const PDU*>(pkt);
    if (pdu == nullptr)
    {
        return;
    }

    std::ostringstream flowID;
    flowID << pdu->getConnId().getSrcCepId() << pdu->getConnId().getDstCepId()
           << pdu->getConnId().getQoSId();

    std::string flags = std::bitset<8>(pdu->getFlags()).to_string().c_str();

    rmtTraceFile << char(eventType) << " "
            << simTime() << " "
            << getModuleByPath("^.^.^.")->getFullName() << " "
            << getModuleByPath("^.^.")->getFullName() << " "
            << pdu->getClassName() << " "
            << pdu->getBitLength() << " "
            << flags << " "
            << flowID.str().c_str() << " "
            << pdu->getDstAddr().getDifName() << " "
            << pdu->getSrcAddr().getIpcAddress() << " "
            << pdu->getDstAddr().getIpcAddress() << " "
            << pdu->getSeqNum() << " "
            << pdu->getId()
            << endl;
}

/**
 * Procedures executed when before a PDU arrives into a queue.
 *
 * @param obj RMT queue object
 */
void RMT::preQueueArrival(cObject* obj)
{
    Enter_Method("preQueueArrival()");
    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);

    // invoke monitor policy
    qMonPolicy->prePDUInsertion(queue);
}

/**
 * Procedures executed when a PDU arrives into a queue.
 *
 * @param obj RMT queue object
 */
void RMT::recDel(cPacket * p) {
    cPacket * enc = p->decapsulate();
    if(enc != nullptr) { recDel(enc); }
    delete p;
}

void RMT::postQueueArrival(cObject* obj)
{
    Enter_Method("onQueueArrival()");

    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);

    if (tracing)
    {
        if (queue->getType() == RMTQueue::INPUT)
        {
            tracePDUEvent(queue->getLastPDU(), MSG_RECEIVE);
        }
        tracePDUEvent(queue->getLastPDU(), MSG_ENQUEUE);
    }

    // detection of channel-induced bit error
    if (queue->getLastPDU()->hasBitError())
    {
        EV << "PDU arriving on " << port->getParentModule()->getFullName()
           << " contains one or more bit errors! Dropping." << endl;
        if (tracing)
        {
            tracePDUEvent(queue->getLastPDU(), MSG_DROP);
        }
        emit(sigRMTPacketError, obj);
        recDel( queue->dropLast() );
        return;
    }

    // invoke monitor policy
    qMonPolicy->postPDUInsertion(queue);

    // invoke maxQueue policy if applicable
    if (queue->getLength() >= queue->getThreshLength())
    {
        // if the PDU has to be dropped, finish it here
        if (maxQPolicy->run(queue))
        {
            if (tracing)
            {
                tracePDUEvent(queue->getLastPDU(), MSG_DROP);
            }
            const auto dropped = queue->dropLast();
            qMonPolicy->onMessageDrop(queue, dropped);
            recDel( dropped );
            return;
        }
    }

    port->addWaiting(queue->getType());
    schedPolicy->processQueues(port, queue->getType());
}

/**
 * Procedures executed right before a PDU leaves its queue.
 *
 * @param obj RMT queue object
 */
void RMT::preQueueDeparture(cObject* obj)
{
    Enter_Method("preQueueDeparture()");
    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);

    qMonPolicy->prePDURelease(queue);

    if (tracing)
    {
        tracePDUEvent(queue->getFirstPDU(), MSG_DEQUEUE);
        if (queue->getType() == RMTQueue::OUTPUT)
        {
            tracePDUEvent(queue->getFirstPDU(), MSG_SEND);
        }
    }
}

/**
 * Procedures executed after a PDU leaves its queue.
 *
 * @param obj RMT queue object
 */
void RMT::postQueueDeparture(cObject* obj)
{
    Enter_Method("postQueueDeparture()");
    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);
    qMonPolicy->postPDURelease(queue);

    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    port->substractWaiting(queue->getType());

    // notify MaxQ in case the queue length just went back under its threshold
    if (queue->getLength() == (queue->getThreshLength() - 1))
    {
        maxQPolicy->onQueueLengthDrop(queue);
    }

    // if this is an incoming PDU, take care of scheduler reinvocation
    if (queue->getType() == RMTQueue::INPUT)
    {
        port->scheduleNextRead();
    }
    else
    { // if this is an outgoing PDU, set the port as busy
        port->setOutputBusy();
    }
}

/**
 * Invokes the scheduling policy for output queues.
 *
 * @param obj RMT queue object
 */
void RMT::writeToPort(cObject* obj)
{
    Enter_Method_Silent("writeToPort()");
    RMTPort* port = check_and_cast<RMTPort*>(obj);
    schedPolicy->processQueues(port, RMTQueue::OUTPUT);
}

/**
 * Invokes the scheduling policy for input queues.
 *
 * @param obj RMT queue object
 */
void RMT::readFromPort(cObject* obj)
{
    Enter_Method_Silent("readFromPort()");
    RMTPort* port = check_and_cast<RMTPort*>(obj);
    schedPolicy->processQueues(port, RMTQueue::INPUT);
}

/**
 * Creates a gate to be used for connection to an EFCP instance.
 *
 * @param efcpiId CEP-id to be used in the gate's name
 */
void RMT::createEfcpiGate(unsigned int efcpiId)
{
    if (efcpiOut.count(efcpiId))
    {
        return;
    }

    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << GATE_EFCPIO_ << efcpiId;

    this->addGate(gateName_str.str().c_str(), cGate::INOUT, false);
    cGate* rmtIn = this->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
    cGate* rmtOut = this->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

    rmtModule->addGate(gateName_str.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

    rmtModuleIn->connectTo(rmtIn);
    rmtOut->connectTo(rmtModuleOut);

    efcpiOut[efcpiId] = rmtOut;
    efcpiIn[efcpiId] = rmtIn;

    // RMT<->EFCP interconnection shall be done by the FAI
}

/**
 * Removes a gate used for an EFCP instance.
 *
 * @param efcpiId CEP-id of the gate meant for removal
 */
void RMT::deleteEfcpiGate(unsigned int efcpiId)
{
    if (!efcpiOut.count(efcpiId))
    {
        return;
    }

    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << GATE_EFCPIO_ << efcpiId;

    cGate* rmtOut = this->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);

    rmtOut->disconnect();
    rmtModuleIn->disconnect();

    this->deleteGate(gateName_str.str().c_str());
    rmtModule->deleteGate(gateName_str.str().c_str());

    efcpiOut.erase(efcpiId);
    efcpiIn.erase(efcpiId);
}

/**
 * A wrapper for forwarding table lookup.
 *
 * @param pdu PDU to forward
 * @return output ports
 */
std::vector<RMTPort*> RMT::fwTableLookup(const PDU * pdu)
{
    RMTPorts ports;

    if (onWire)
    { // get the interface port
        ports.push_back(rmtAllocator->getInterfacePort());
    }
    else
    { // get output ports from PDUFT
        ports = fwd->lookup(pdu);
    }

    return ports;
}

/**
 * Passes a PDU from an EFCP instance to an appropriate output port.
 *
 * @param pdu PDU to be passed
 */
void RMT::relayPDUToPort(PDU* pdu)
{
    auto outPorts = fwTableLookup(pdu);

    if (outPorts.empty())
    {
        EV << "!!! Empty PDUForwarding policy lookup result!" << endl
           << "At " << getParentModule()->getParentModule()->par("ipcAddress").stdstringValue() << endl
           << "PDU dstAddr = " << pdu->getDstAddr().getApn().getName()
           << ", qosId = " <<  pdu->getConnId().getQoSId() << endl
           << "PDUForwarding contents: " << endl << fwd->toString() << endl;

        if(par("coutLookError").boolValue()) {
        std::cout << "!!! Empty PDUForwarding policy lookup result! " << simTime() << endl
           << "At " << getParentModule()->getParentModule()->par("ipcAddress").stdstringValue() << endl
           << "PDU srcAddr = " << pdu->getSrcAddr().getApn().getName()
           << ", dstAddr = " << pdu->getDstAddr().getApn().getName()
           << ", qosId = " <<  pdu->getConnId().getQoSId() << endl
           << "TTL = " <<  pdu->getHopCount() << endl
           << "PDUForwarding contents: " << endl << fwd->toString() << endl;
        }


        if(par("printAtEnd").boolValue()) {
            invalidPDUs.push_back(pdu);
        } else {
            recDel(pdu);
        }
    }

    PDU* outPDU = nullptr;

    for (auto it = outPorts.begin(); it != outPorts.end(); ++it)
    {
        RMTPort* port = *it;

        if (it != (outPorts.end() - 1))
        { // clone the message if sending via multiple ports
            outPDU = pdu->dup();
        }
        else
        {
            outPDU = pdu;
        }

        const std::string& id = queueIdGenerator->generateOutputQueueID(pdu);
        RMTQueue* outQueue = port->getQueueById(RMTQueue::OUTPUT, id.c_str());

        if (outQueue != nullptr)
        {
            cGate* outGate = outQueue->getRMTAccessGate();
            send(outPDU, outGate);
        }
        else
        {
            EV << "Queue with ID \"" << id << "\" doesn't exist!" << endl;
        }
    }
}

/**
 * Passes a PDU from an (N-1)-port to an EFCP instance.
 *
 * @param pdu PDU to be passed
 */
void RMT::relayPDUToEFCPI(PDU* pdu)
{
    int cepId = pdu->getConnId().getDstCepId();

    if(cepId < 0) { delete pdu; return; }

    cGate* efcpiGate = efcpiOut[cepId];
    if (efcpiGate != nullptr)
    {
        send(pdu, efcpiGate);
    }
    else
    {
        std::cout << "WTF " << cepId << endl;
            EV << this->getFullPath() << ": EFCPI " << cepId
               << " isn't present on this system! Notifying other modules." << endl;
            emit(sigRMTNoConnID, pdu);
            invalidPDUs.push_back(pdu);

    }
}

/**
 * The main finite state machine of Relaying and Multiplexing task.
 * Makes a decision about what to do with incoming message based on arrival gate,
 * message type, message destination address and RMT mode of operation.
 *
 * @param msg either a PDU or a CDAP message
 */
void RMT::processMessage(cMessage* msg)
{
    PDU* pdu = dynamic_cast<PDU*>(msg);

    if (pdu != nullptr)
    { // PDU arrival
        cModule* senderModule = msg->getArrivalGate()->getPathStartGate()->getOwnerModule();

        if (dynamic_cast<RMTQueue*>(senderModule) != nullptr)
        { // message from a port
            if (addrComparator->matchesThisIPC(pdu->getDstAddr(), pdu) )
            {
                relayPDUToEFCPI(pdu);
            }
            else if (relayOn)
            {
                relayPDUToPort(pdu);
            }
            else
            {
                EV << getFullPath() << " This PDU isn't for me! Holding it here." << endl;
            }
        }
        else
        { // message from an EFCPI
            if (addrComparator->matchesThisIPC(pdu->getDstAddr(), pdu) )
            {
                relayPDUToEFCPI(pdu);
            }
            else
            {
                relayPDUToPort(pdu);
            }
        }
    }
    else
    {
        EV << this->getFullPath() << " message type not supported" << endl;
        if(par("deleteIfNotValid").boolValue()) {
            invalidPDUs.push_back(msg);
        }
    }
}

void RMT::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        // ?
        if(par("deleteIfNotValid").boolValue()) {
            invalidPDUs.push_back(msg);
        }
    }
    else
    {
        processMessage(msg);
    }
}

