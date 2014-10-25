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

const int PROCESSING_DELAY = 0.0;

RMT::RMT()
{
    relayOn = false;
    qypos = 120;
    qxpos = 45;
}

RMT::~RMT() {}


void RMT::initialize() {
    WATCH_PTRMAP(efcpiToQueue);

    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    queues = ModuleAccess<RMTQueueManager>("rmtQueueManager").get();

    cModule* ipcModule = getParentModule()->getParentModule();
    thisIpcAddr = Address(ipcModule->par("ipcAddress").stringValue(),
                          ipcModule->par("difName").stringValue());

}

RMTQueue* RMT::addQueue(const char* queueName, RMTQueue::queueType type)
{
    // find factory object
    cModuleType *moduleType = cModuleType::get("rina.DIF.RMT.RMTQueue");

    // instantiate a new object
    cModule *module_f = moduleType->createScheduleInit(queueName, this->getParentModule());
    RMTQueue* module = dynamic_cast<RMTQueue*>(module_f);

    // modify the position a little
    std::ostringstream istr;
    istr << "p=" << qxpos << "," << qypos << ";i=block/queue;is=vs";

    cDisplayString& dispStr = module->getDisplayString();
    dispStr.parse(istr.str().c_str());
    qxpos = qxpos + 45;

    // connect to RMT submodule
    if (type == RMTQueue::OUTPUT)
    {
        cGate* rmtOut = this->addGate(queueName, cGate::OUTPUT, false);
        cGate* queueIn = module->addGate("rmtInput", cGate::INPUT, false);
        rmtOut->connectTo(queueIn);
        module->setRmtAccessGate(rmtOut);
    }
    else if (type == RMTQueue::INPUT)
    {
        cGate* rmtIn = this->addGate(queueName, cGate::INPUT, false);
        module->getOutputGate()->connectTo(rmtIn);
    }

    module->setType(type);
    queues->addQueue(module);
    return module;
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
 * Passes given PDU to an (N-1)-flow using information from the forwarding table.
 *
 * @param pdu PDU to be sent
 */
void RMT::sendDown(PDU_Base* pdu)
{
    Address& pduDestAddr = pdu->getDstAddr();
    //int pduQosId = pdu->getConnId().getQoSId();
    cGate* outGate;

    // local degenerate flow
    if (thisIpcAddr == pduDestAddr)
    {
        sendUp(pdu);
        return;
    }

    if (relayOn)
    {
        outGate = fwTableLookup(pduDestAddr, -1);
    }
    else
    {
        outGate = efcpiToQueue[pdu->getArrivalGate()]->getRmtAccessGate();
    }

    EV << this->getFullPath() << " passing a PDU downwards..." << endl;

    if (outGate != NULL)
    {
        send(pdu, outGate);
    }
    else
    {
        EV << this->getFullPath()
           << " I can't reach any suitable (N-1)-flow! Seems like none is allocated. Dropping."
           << endl;

        delete pdu;
    }
}

/**
 * Passes given PDU to the appropriate EFCP instance using PDU's destination CEP-id.
 *
 * @param pdu PDU to be sent
 */
void RMT::sendUp(PDU_Base* pdu)
{
    Address& pduAddr = pdu->getDstAddr();

    if (thisIpcAddr == pduAddr)
    {
        EV << this->getFullPath() << " passing a PDU upwards to EFCPI " << pdu->getConnId().getDstCepId() << endl;
        cGate* efcpiGate = efcpiOut[pdu->getConnId().getDstCepId()];

        if (efcpiGate != NULL)
        {
            send(pdu, efcpiGate);
        }
        else
        {
            EV << this->getFullPath()
               << " I'm not connected to such EFCPI! Notifying other modules."
               << endl;
            // TODO: emit(cosi)
            delete pdu;
        }
    }
    else
    { // this PDU isn't for us
        if (relayOn)
        { // ...let's relay it somewhere else
            EV << this->getFullPath() << " relaying a PDU elsewhere" << endl;
            sendDown(pdu);
        }
        else
        { //
            EV << this->getFullPath()
               << " this PDU isn't for me, dropping it! (" << thisIpcAddr << " != " << pduAddr << ")"
               << endl;
            delete pdu;
        }
    }
}

void RMT::handleMessage(cMessage *msg)
{
    std::string gate = msg->getArrivalGate()->getName();

    if (msg->isSelfMessage())
    {
        delete msg;
    }
    else if (dynamic_cast<PDU_Base*>(msg) != NULL)
    { // PDU arrival
        PDU_Base* pdu = (PDU_Base*) msg;

        if (gate.substr(0, 2) == "q_")
        {
            sendUp(pdu);
        }
        else if (gate.substr(0, 7) == GATE_EFCPIO_)
        {
            sendDown(pdu);
        }
    }
    else if (dynamic_cast<CDAPMessage*>(msg) != NULL)
    { // management message arrival
        CDAPMessage* cdap = (CDAPMessage*) msg;

        if (gate.substr(0, 2) == "q_")
        {
            send(msg, "ribdIo$o");
        }
        else
        {
            cGate* outGate = NULL;

            if (relayOn)
            {
                outGate = fwTableLookup(cdap->getDstAddr(), -1);
            }
            else
            {
                outGate = queues->getFirst(RMTQueue::OUTPUT)->getRmtAccessGate();
            }

            if (outGate != NULL)
            {
                send(msg, outGate);
            }
            else
            {
                EV << "there isn't any suitable output queue available!" << endl;
            }
        }
    }
    else
    {
        EV << this->getFullPath() << " message type not supported" << endl;
        delete msg;
    }
}

