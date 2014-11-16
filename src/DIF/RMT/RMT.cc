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
{
    relayOn = false;
    onWire = false;
    waitingMsgs = 0;
}

RMT::~RMT() {}


void RMT::initialize()
{
    WATCH_PTRMAP(efcpiToQueue);

    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    queues = ModuleAccess<RMTQueueManager>("rmtQueueManager").get();

    cModule* ipcModule = getParentModule()->getParentModule();
    thisIpcAddr = Address(ipcModule->par("ipcAddress").stringValue(),
                          ipcModule->par("difName").stringValue());

    // register signal for notifying others about a missing local EFCP instance
    sigRMTNoConnID = registerSignal(SIG_RMT_NoConnId);

    // listen for a signal indicating that a new message has arrived into a queue
    lisRMTMsgRcvd = new LisRMTPDURcvd(this);
    getParentModule()->subscribe(SIG_RMT_MessageReceived, lisRMTMsgRcvd);

    schedPolicy = ModuleAccess<RMTSchedulingBase>("schedulingPolicy").get();
    qMonPolicy = ModuleAccess<RMTQMonitorBase>("queueMonitorPolicy").get();
}

/**
 * Schedules an end-of-queue-service event.
 *
 */
void RMT::scheduleServiceEnd()
{
    scheduleAt(simTime() + par("queueServiceTime"), new cMessage("queueServiceDone"));
}

/**
 * Tries to begin service of a message that has newly arrived into a queue.
 * If servicing takes place right now, the wait counter is increased instead.
 *
 */
void RMT::invokeSchedulingPolicy(cObject* obj)
{
    Enter_Method("invokeSchedulingPolicy()");

    qMonPolicy->run(dynamic_cast<RMTQueue*>(obj));

    if (!waitingMsgs)
    {
        scheduleServiceEnd();
    }
    else
    {
        waitingMsgs++;
    }
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

    deleteEfcpiToQueueMapping(efcpiId);
    efcpiOut.erase(efcpiId);
    efcpiIn.erase(efcpiId);
}

/**
 * Creates a direct mapping from an EFCPI input gate to a RMT queue.
 *
 * @param cepId EFCP ID
 * @param outQueue output RMT queue
 */
void RMT::addEfcpiToQueueMapping(unsigned cepId, RMTQueue* outQueue)
{
    efcpiToQueue[efcpiIn[cepId]] = outQueue;
}

/**
 * Deletes a direct EFCPI->queue mapping.
 *
 * @param cepId EFCP ID
 */
void RMT::deleteEfcpiToQueueMapping(unsigned cepId)
{
    efcpiToQueue.erase(efcpiIn[cepId]);
}

/**
 * Wrapper around forwarding table lookup returning the target output gate itself.
 *
 * @param destAddr destination address
 * @param qosId qos-id
 * @return RMT gate leading to an output RMT queue
 */
cGate* RMT::fwTableLookup(Address& destAddr, short qosId)
{
    cGate* outGate = NULL;
    RMTQueue* outQueue = fwTable->lookup(destAddr, qosId);

    if (outQueue != NULL)
    {
        outGate = outQueue->getRmtAccessGate();
    }

    return outGate;
}

/**
 * Passes a PDU from an EFCP instance to an appropriate output queue.
 *
 * @param pdu PDU to be passed
 */
void RMT::efcpiToPort(PDU_Base* pdu)
{
    cGate* outGate = NULL;

    outGate = efcpiToQueue[pdu->getArrivalGate()]->getRmtAccessGate();
    if (outGate != NULL)
    {
        EV << this->getFullPath() << " passing a PDU to an output queue" << endl;
        send(pdu, outGate);
    }
    else
    {
        EV << this->getFullPath() << "efcpi->port-id mapping not present!" << endl;
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

    if (!onWire)
    {
        outGate = fwTableLookup(cdap->getDstAddr(), -1);
    }
    else
    {
        outGate = queues->getFirst(RMTQueue::OUTPUT)->getRmtAccessGate();
    }

    if (outGate != NULL)
    {
        EV << this->getFullPath() << " passing a CDAP message to an output queue" << endl;
        send(cdap, outGate);
    }
    else
    {
        EV << "there isn't any suitable output queue available!" << endl;
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
    short qosId;

    if (dynamic_cast<PDU_Base*>(msg) != NULL)
    {
        destAddr = ((PDU_Base*)msg)->getDstAddr();
        qosId = ((PDU_Base*)msg)->getConnId().getQoSId();
    }
    else if (dynamic_cast<CDAPMessage*>(msg) != NULL)
    {
        destAddr = ((CDAPMessage*)msg)->getDstAddr();
        qosId = -1;
    }

    cGate* outGate = NULL;

    if (onWire)
    {
        outGate = queues->getFirst(RMTQueue::OUTPUT)->getRmtAccessGate();
    }
    else
    {
        outGate = fwTableLookup(destAddr, qosId);
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

        if (gate.substr(0, 2) == "in")
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

        if (gate.substr(0, 2) == "in")
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
        if (!opp_strcmp(msg->getFullName(), "queueServiceDone"))
        {
            schedPolicy->run(queues);
            if (waitingMsgs)
            {
                scheduleServiceEnd();
                waitingMsgs--;
            }
        }
        delete msg;
    }
    else
    {
        processMessage(msg);
    }
}

