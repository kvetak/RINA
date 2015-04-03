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
 * @file RMT.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief Relaying and Multiplexing Task
 * @detail
 */

#include <RMT.h>

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
    relayOn = false;
    onWire = false;
    erroneousCount = 0;

    // get pointers to other components
    fwd = check_and_cast<IntPDUForwarding*>
        (getModuleByPath("^.pduForwardingPolicy"));
    rmtAllocator = check_and_cast<RMTModuleAllocator*>
        (getModuleByPath("^.allocator"));

    schedPolicy = check_and_cast<RMTSchedulingBase*>
        (getModuleByPath("^.schedulingPolicy"));
    maxQPolicy = check_and_cast<RMTMaxQBase*>
        (getModuleByPath("^.maxQueuePolicy"));
    qMonPolicy = check_and_cast<RMTQMonitorBase*>
        (getModuleByPath("^.queueMonitorPolicy"));
    qAllocPolicy = check_and_cast<QueueAllocBase*>
        (getModuleByPath("^.^.resourceAllocator.queueAllocPolicy"));
    queueIdGenerator = check_and_cast<QueueIDGenBase*>
        (getModuleByPath("^.^.resourceAllocator.queueIdGenerator"));
    addrComparator = check_and_cast<AddressComparatorBase*>
        (getModuleByPath("^.^.resourceAllocator.addressComparator"));

    // register a signal for notifying others about a missing local EFCP instance
    sigRMTNoConnID = registerSignal(SIG_RMT_NoConnId);

    // register a signal for notifying others about a packet bit error
    sigRMTPacketError = registerSignal(SIG_RMT_ErrornousPacket);

    // register a signal for counting
    sigRMTPacketErrorCount = registerSignal("RMT-ErroneousPacketCount");

    // listen for a signal indicating that a new message has arrived into a queue
    lisRMTQueuePDURcvd = new LisRMTQueuePDURcvd(this);
    getParentModule()->subscribe(SIG_RMT_QueuePDURcvd, lisRMTQueuePDURcvd);

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
        EV << this->getFullPath()<< endl;
        EV << "This RMT still contains " << pduCount << " unprocessed PDUs!" << endl;

        for (std::deque<cMessage*>::iterator it = invalidPDUs.begin(); it != invalidPDUs.end(); ++it)
        {
            cMessage* m = *it;
            EV << m->getClassName() << " received at " << m->getArrivalTime()
               << " from " << m->getSenderModule()->getFullPath() << endl;
        }
    }
}

/**
 * Invokes RMT policies related to queue processing. To be called when a message
 * arrives into a queue.
 *
 * @param obj RMT queue object
 */
void RMT::invokeQueueArrivalPolicies(cObject* obj)
{
    Enter_Method("invokeQueueArrivalPolicies()");

    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);

    // detection of channel-induced bit error
    if (queue->getLastPDU()->hasBitError())
    {
        queue->dropLast();
        EV << "PDU arriving on " << port->getParentModule()->getFullName()
           << " contains one or more bit errors! Dropping." << endl;
        emit(sigRMTPacketError, obj);

        erroneousCount++;
        emit(sigRMTPacketErrorCount, erroneousCount);

        return;
    }

    // invoke monitor policy
    qMonPolicy->onMessageArrival(queue);

    // invoke maxQueue policy if applicable
    if (queue->getLength() >= queue->getThreshLength())
    {
        // if the PDU has to be dropped, finish it here
        if (maxQPolicy->run(queue))
        {
            const cPacket* dropped = queue->dropLast();
            qMonPolicy->onMessageDrop(queue, dropped);
            delete dropped;
            return;
        }
    }

    port->addWaiting(queue->getType());
    schedPolicy->processQueues(port, queue->getType());
}

/**
 * Executed after a PDU leaves its queue; notifies the monitoring policy and
 * queue's port.
 *
 * @param obj RMT queue object
 */
void RMT::invokeQueueDeparturePolicies(cObject* obj)
{
    Enter_Method("invokeQueueDeparturePolicies()");
    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);
    qMonPolicy->onMessageDeparture(queue);

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
 * @param destAddr destination address
 * @param qosId qos-id
 * @return output port
 */
RMTPort* RMT::fwTableLookup(const Address& destAddr, const unsigned short &qosId)
{
    if (onWire)
    { // get the interface port
        return rmtAllocator->getInterfacePort();
    }
    else
    { // get a suitable ports from PDUF
        std::vector<RMTPort*> ports = fwd->lookup(destAddr, qosId);
        if (ports.size() > 0)
        {
            return ports.front();
        }
        else
        {
            return NULL;
        }
    }
}

/**
 * A wrapper for forwarding table lookup.
 *
 * @param pdu PDU to forward
 * @return output port
 */
RMTPort* RMT::fwTableLookup(const PDU * pdu)
{
    if (onWire)
    { // get the interface port
        return rmtAllocator->getInterfacePort();
    }
    else
    { // get output ports from PDUFT
        std::vector<RMTPort*> ports = fwd->lookup(pdu);
        if(ports.size()>0)
        {
            return ports.front();
        }
        else
        {
            return NULL;
        }
    }
}

/**
 * Passes a PDU from an EFCP instance to an appropriate output queue.
 *
 * @param pdu PDU to be passed
 */
void RMT::efcpiToPort(PDU* pdu)
{
    RMTQueue* outQueue = NULL;

    RMTPort* outPort = fwTableLookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
    if (outPort != NULL)
    {
        const std::string& id = queueIdGenerator->generateID(pdu);
        outQueue = outPort->getQueueById(RMTQueue::OUTPUT, id.c_str());
    }

    cGate* outGate = NULL;
    if (outQueue != NULL)
    {
        outGate = outQueue->getRMTAccessGate();
    }

    if (outGate != NULL)
    {
        send(pdu, outGate);
    }
    else
    {
        EV << getFullPath() << ": could not send out a PDU coming from EFCPI!" << endl;
        EV << "PDU dstAddr = " << pdu->getDstAddr().getApname().getName()
           << ", qosId = " <<  pdu->getConnId().getQoSId() << endl;
    }
}

/**
 * Passes a PDU from an (N-1)-port to an EFCP instance.
 *
 * @param pdu PDU to be passed
 */
void RMT::portToEfcpi(PDU* pdu)
{
    unsigned cepId = pdu->getConnId().getDstCepId();
    cGate* efcpiGate = efcpiOut[cepId];

    if (efcpiGate != NULL)
    {
        send(pdu, efcpiGate);
    }
    else
    {
        EV << this->getFullPath() << ": EFCPI " << cepId
           << " isn't present on this system! Notifying other modules." << endl;
        emit(sigRMTNoConnID, pdu);
        invalidPDUs.push_back(pdu);
    }

}

/**
 * Passes a PDU from an EFCP instance to another local EFCP instance.
 *
 * @param pdu PDU to be passed
 */
void RMT::efcpiToEfcpi(PDU* pdu)
{
    portToEfcpi(pdu);
}

/**
 * Passes a CDAP mesage from an (N-1)-port instance to RIB daemon.
 *
 * @param cdap CDAP message to be passed
 */
void RMT::portToRIB(CDAPMessage* cdap)
{
    send(cdap, "ribdIo$o");
}

/**
 * Passes a CDAP mesage from the RIB daemon to an appropriate output queue.
 *
 * @param cdap CDAP message to be passed
 */
void RMT::ribToPort(CDAPMessage* cdap)
{
    cGate* outGate = NULL;
    RMTQueue* outQueue = NULL;
    RMTPort* outPort = fwTableLookup(cdap->getDstAddr(), 0);
    if (outPort != NULL)
    {
        outQueue = outPort->getManagementQueue(RMTQueue::OUTPUT);
    }

    if (outQueue != NULL)
    {
        outGate = outQueue->getRMTAccessGate();
    }

    if (outGate != NULL)
    {
        send(cdap, outGate);
    }
    else
    {
        EV << getFullPath() << ": could not send out a CDAP message!" << endl;
        EV << "CDAP dstAddr = " << cdap->getDstAddr().getApname().getName()
           << ", qosId = 0" << endl;
    }
}

/**
 * Relays incoming message to an output queue based on data from PDUFwTable.
 *
 * @param msg either a PDU or a CDAP message to be relayed
 */
void RMT::portToPort(cMessage* msg)
{
    Address destAddr;
    RMTPort* outPort = NULL;
    RMTQueue* outQueue = NULL;

    PDU* pdu = dynamic_cast<PDU*>(msg);
    if (pdu != NULL)
    {
        outPort = fwTableLookup(pdu);
        if (outPort == NULL)
        {
            EV << getFullPath()
               << ": no suitable output (N-1)-flow present for relay!" << endl;
            return;
        }
        outQueue = outPort->getQueueById(RMTQueue::OUTPUT,
                queueIdGenerator->generateID((PDU*)msg).c_str());
    }
    else if (dynamic_cast<CDAPMessage*>(msg) != NULL)
    {
        destAddr = ((CDAPMessage*)msg)->getDstAddr();

        outPort = fwTableLookup(destAddr, 0);
        if (outPort == NULL)
        {
            EV << getFullPath()
               << ": no suitable output (N-1)-flow present for relay!" << endl;
            return;
        }
        outQueue = outPort->getManagementQueue(RMTQueue::OUTPUT);
    }
    else
    {
        EV << "This message isn't supported by relaying application! Aborting." << endl;
        return;
    }

    cGate* outGate = NULL;

    if (outQueue != NULL)
    {
        outGate = outQueue->getRMTAccessGate();
    }

    if (outGate != NULL)
    {
        send(msg, outGate);
    }
    else
    {
        EV << getFullPath()
           << ": couldn't retrieve the proper queue for this message!" << endl;
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
    std::string gate = msg->getArrivalGate()->getName();

    if (dynamic_cast<PDU*>(msg) != NULL)
    { // PDU arrival
        PDU* pdu = (PDU*) msg;

        // TODO: replace with something less dumb
        if (gate.substr(0, 1) == "p")
        { // from a port
            if (addrComparator->matchesThisIPC(pdu->getDstAddr()))
            {
                portToEfcpi(pdu);
            }
            else if (relayOn)
            {
                portToPort(msg);
            }
            else
            {
                EV << getFullPath() << " This PDU isn't for me! Holding it here." << endl;
            }
        }
        else if (gate.substr(0, 7) == GATE_EFCPIO_)
        { // from an EFCPI
            if (addrComparator->matchesThisIPC(pdu->getDstAddr()))
            {
                efcpiToEfcpi(pdu);
            }
            else
            {
                efcpiToPort(pdu);
            }
        }
    }
    else if (dynamic_cast<CDAPMessage*>(msg) != NULL)
    { // management message arrival
        CDAPMessage* cdap = (CDAPMessage*) msg;

        if (gate.substr(0, 1) == "p")
        { // from a port
            if (addrComparator->matchesThisIPC(cdap->getDstAddr()))
            {
                portToRIB(cdap);
            }
            else
            {
                portToPort(msg);
            }
        }
        else
        { // from the RIBd
            ribToPort(cdap);
        }
    }
    else
    {
        EV << this->getFullPath() << " message type not supported" << endl;
        invalidPDUs.push_back(msg);
    }
}

void RMT::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        // ?
        invalidPDUs.push_back(msg);
    }
    else
    {
        processMessage(msg);
    }
}

