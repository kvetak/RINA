//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

RMT::RMT()
: relayOn(false), onWire(false)
{
}

RMT::~RMT()
{
}


void RMT::initialize()
{
    // get pointers to other components
    fwTable = check_and_cast<PDUForwardingTable*>
        (getModuleByPath("^.^.resourceAllocator.pduForwardingTable"));
    rmtQM = check_and_cast<RMTQueueManager*>
        (getModuleByPath("^.rmtQueueManager"));

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

    // set up some parameters
    cModule* ipcModule = getParentModule()->getParentModule();
    thisIpcAddr = Address(ipcModule->par(PAR_IPCADDR).stringValue(),
                          ipcModule->par(PAR_DIFNAME).stringValue());

    // register a signal for notifying others about a missing local EFCP instance
    sigRMTNoConnID = registerSignal(SIG_RMT_NoConnId);

    // listen for a signal indicating that a new message has arrived into a queue
    lisRMTMsgRcvd = new LisRMTPDURcvd(this);
    getParentModule()->subscribe(SIG_RMT_MessageReceived, lisRMTMsgRcvd);

    // listen for a signal indicating that a new message has left a port
    lisRMTMsgSent = new LisRMTPDUSent(this);
    getParentModule()->subscribe(SIG_RMT_MessageSent, lisRMTMsgSent);
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

    // invoke monitor policy
    qMonPolicy->onMessageArrival(queue);

    // invoke maxQueue policy if applicable
    if (queue->getLength() >= queue->getThreshLength())
    {
        // if the PDU has to be dropped, finish it here
        if (maxQPolicy->run(queue))
        {
            const cMessage* dropped = queue->dropLast();
            qMonPolicy->onMessageDrop(queue, dropped);
            delete dropped;
            return;
        }
    }

    // finally, invoke the scheduling policy
    schedPolicy->processQueues(rmtQM->getQueueToPortMapping(queue), queue->getType());
}

/**
 * Takes care of re-invocation of scheduling policy after a queue is popped.
 *
 * @param obj RMT queue object
 */
void RMT::invokeQueueDeparturePolicies(cObject* obj)
{
    Enter_Method("invokeQueueDeparturePolicies()");
    RMTQueue* queue = check_and_cast<RMTQueue*>(obj);
    qMonPolicy->onMessageDeparture(queue);
    schedPolicy->finalizeService(rmtQM->getQueueToPortMapping(queue), queue->getType());
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
RMTPort* RMT::fwTableLookup(Address& destAddr, short qosId, bool useQoS)
{
    RMTPort* outPort = NULL;

    if (onWire)
    { // get the interface port
        outPort = rmtQM->getInterfacePort();
    }
    else
    { // get a suitable port from PDUFT
        if (useQoS)
        {
            outPort = fwTable->lookup(destAddr, qosId);
        }
        else
        {
            outPort = fwTable->lookup(destAddr);
        }
    }

    return outPort;
}

/**
 * Passes a PDU from an EFCP instance to an appropriate output queue.
 *
 * @param pdu PDU to be passed
 */
void RMT::efcpiToPort(PDU_Base* pdu)
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
        outGate = outQueue->getRmtAccessGate();
    }

    if (outGate != NULL)
    {
        EV << this->getFullPath() << " passing a PDU to an output queue" << endl;
        send(pdu, outGate);
    }
    else
    {
        EV << this->getFullPath() << " I can't reach any suitable (N-1)-flow!" << endl;
        EV << "PDU dstAddr = " << pdu->getDstAddr().getApname().getName()
           << ", qosId = " << pdu->getConnId().getQoSId() << endl;
        fwTable->printAll();
    }
}

/**
 * Passes a PDU from an (N-1)-port to an EFCP instance.
 *
 * @param pdu PDU to be passed
 */
void RMT::portToEfcpi(PDU_Base* pdu)
{
    unsigned cepId = pdu->getConnId().getDstCepId();
    cGate* efcpiGate = efcpiOut[cepId];

    if (efcpiGate != NULL)
    {
        EV << this->getFullPath() << " passing a PDU upwards to EFCPI " << cepId << endl;
        send(pdu, efcpiGate);
    }
    else
    {
        EV << this->getFullPath() << " EFCPI " << cepId << " isn't present on this system! Notifying other modules." << endl;
        emit(sigRMTNoConnID, pdu);
        //delete pdu;
    }

}

/**
 * Passes a PDU from an EFCP instance to another local EFCP instance.
 *
 * @param pdu PDU to be passed
 */
void RMT::efcpiToEfcpi(PDU_Base* pdu)
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
void RMT::RIBToPort(CDAPMessage* cdap)
{
    cGate* outGate = NULL;
    RMTQueue* outQueue = NULL;
    RMTPort* outPort = fwTableLookup(cdap->getDstAddr(), 0, false);
    if (outPort != NULL)
    {
        outQueue = outPort->getManagementQueue(RMTQueue::OUTPUT);
    }

    if (outQueue != NULL)
    {
        outGate = outQueue->getRmtAccessGate();
    }

    if (outGate != NULL)
    {
        EV << this->getFullPath() << " passing a CDAP message to an output queue" << endl;
        send(cdap, outGate);
    }
    else
    {
        EV << "there isn't any suitable output queue available!" << endl;
        EV << "PDU dstAddr = " << cdap->getDstAddr().getApname().getName()
                   << ", qosId = 0";
                fwTable->printAll();
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


    if (dynamic_cast<PDU_Base*>(msg) != NULL)
    {
        destAddr = ((PDU_Base*)msg)->getDstAddr();
        short qosId = ((PDU_Base*)msg)->getConnId().getQoSId();

        outPort = fwTableLookup(destAddr, qosId);
        if (outPort == NULL)
        {
            EV << "PORT NOT FOUND" << endl;
            return;
        }
        outQueue = outPort->getQueueById(RMTQueue::OUTPUT,
                queueIdGenerator->generateID((PDU_Base*)msg).c_str());
    }
    else if (dynamic_cast<CDAPMessage*>(msg) != NULL)
    {
        destAddr = ((CDAPMessage*)msg)->getDstAddr();

        outPort = fwTableLookup(destAddr, 0, false);
        if (outPort == NULL)
        {
            EV << "PORT NOT FOUND" << endl;
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
        outGate = outQueue->getRmtAccessGate();
    }

    if (outGate != NULL)
    {
        EV << this->getFullPath() << " relaying a message" << endl;
        send(msg, outGate);
    }
    else
    {
        EV << this->getFullPath() << " I can't reach any suitable (N-1)-flow! Seems like none is allocated." << endl;
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

    if (dynamic_cast<PDU_Base*>(msg) != NULL)
    { // PDU arrival
        PDU_Base* pdu = (PDU_Base*) msg;

        if (gate.substr(0, 1) == "p")
        {
            if (pdu->getDstAddr() == thisIpcAddr)
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
        {
            if (pdu->getDstAddr() == thisIpcAddr)
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
        {
            if (cdap->getDstAddr() == thisIpcAddr)
            {
                portToRIB(cdap);
            }
            else
            {
                portToPort(msg);
            }
        }
        else
        {
            RIBToPort(cdap);
        }
    }
    else
    {
        EV << this->getFullPath() << " message type not supported" << endl;
        delete msg;
    }
}

void RMT::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        // ?
        delete msg;
    }
    else
    {
        processMessage(msg);
    }
}

