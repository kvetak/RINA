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
}

RMT::~RMT()
{
}


void RMT::initialize() {
    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    //ports = ModuleAccess<RMTPortManager>("rmtPortManager").get();

    processName = getParentModule()->getParentModule()->par("ipcAddress").stdstringValue();
}

/**
 * Creates a gate to be used for connection to an (N-1)-flow.
 *
 * @param gateName name to be given to the newly created gate; it has to be
 *        unambiguous within the scope of this IPC's management of (N-1)-flows
 */
void RMT::createSouthGate(std::string gateName)
{
    cModule* rmtModule = getParentModule();

    this->addGate(gateName.c_str(), cGate::INOUT, false);
    cGate* rmtIn = this->gateHalf(gateName.c_str(), cGate::INPUT);
    cGate* rmtOut = this->gateHalf(gateName.c_str(), cGate::OUTPUT);

    rmtModule->addGate(gateName.c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName.c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(gateName.c_str(), cGate::OUTPUT);

    rmtModuleIn->connectTo(rmtIn);
    rmtOut->connectTo(rmtModuleOut);

    // RMT<->(N-1)-EFCP interconnection shall be done by the RA
}

/**
 * Removes a gate used for a (N-1)-flow.
 *
 * @param gateName name of the gate meant for removal
 */
void RMT::deleteSouthGate(std::string gateName)
{
    cModule* rmtModule = getParentModule();

    cGate* rmtOut = this->gateHalf(gateName.c_str(), cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName.c_str(), cGate::INPUT);

    rmtOut->disconnect();
    rmtModuleIn->disconnect();

    this->deleteGate(gateName.c_str());
    rmtModule->deleteGate(gateName.c_str());

    //ports.erase(gateName);
}

void RMT::addRMTPort(RMTPortId portId, cGate* gate)
{
    ports[portId] = gate;
}

/**
 * Creates a gate to be used for connection to an EFCP instance.
 *
 * @param efcpiId CEP-id to be used in the gate's name
 */
void RMT::createEfcpiGate(unsigned int efcpiId)
{
    if (efcpiGates.count(efcpiId))
    {
        return;
    }

    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << GATE_EFCPIO << efcpiId;

    this->addGate(gateName_str.str().c_str(), cGate::INOUT, false);
    cGate* rmtIn = this->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
    cGate* rmtOut = this->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

    rmtModule->addGate(gateName_str.str().c_str(), cGate::INOUT, false);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);
    cGate* rmtModuleOut = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);

    rmtModuleIn->connectTo(rmtIn);
    rmtOut->connectTo(rmtModuleOut);

    efcpiGates[efcpiId] = rmtOut;

    // RMT<->EFCP interconnection shall be done by the FAI
}

/**
 * Removes a gate used for an EFCP instance.
 *
 * @param efcpiId CEP-id of the gate meant for removal
 */
void RMT::deleteEfcpiGate(unsigned int efcpiId)
{
    if (!efcpiGates.count(efcpiId))
    {
        return;
    }

    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << GATE_EFCPIO << efcpiId;

    cGate* rmtOut = this->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);

    rmtOut->disconnect();
    rmtModuleIn->disconnect();

    this->deleteGate(gateName_str.str().c_str());
    rmtModule->deleteGate(gateName_str.str().c_str());

    efcpiGates.erase(efcpiId);
}

/**
 * Passes given PDU to an (N-1)-flow using information from the forwarding table.
 *
 * @param pdu PDU to be sent
 */
void RMT::sendDown(PDU_Base* pdu)
{
    std::string pduDestAddr = pdu->getDstAddr().getName();
    int pduQosId = pdu->getConnId().getQoSId();
    cGate* outPort;

    if (relayOn)
    {
        try
        { // forwarding table lookup
            RMTPortId outPortId = fwTable->lookup(pduDestAddr, pduQosId);
            outPort = ports[outPortId];
        }
        catch (...)
        {
            EV << this->getFullPath() << " couldn't find any match in FWTable." << endl;
            delete pdu;
            return;
        }
    }
    else
    {
        // decide which (N-1)-flow should get the PDU...
        // we'll just grab the first one for now
        outPort = ports.begin()->second;
    }

    // TODO: OMNeT++ 4.4.1 renders the message transfer as if this was sent to this IPC's EFCP. Is this a bug?
    send(pdu, outPort);
}

/**
 * Passes given PDU to the appropriate EFCP instance using PDU's destination CEP-id.
 *
 * @param pdu PDU to be sent
 */
void RMT::sendUp(PDU_Base* pdu)
{
    if (pdu->getDstAddr().getName() != processName)
    { // this PDU isn't for us
        if (relayOn)
        { // ...let's relay it somewhere else
            EV << this->getFullPath() << " relaying a PDU elsewhere" << endl;
            sendDown(pdu);
        }
        else
        {
            EV << this->getFullPath() << " this PDU isn't for me! dropping." << endl;
            delete pdu;
        }
    }
    else
    {
        cGate* efcpiGate = efcpiGates[pdu->getConnId().getDestCepId()];

        EV << this->getFullPath() << " delivering a PDU to EFCPI " << efcpiGate->getName() << endl;
        send(pdu, efcpiGate);
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
        EV << gate << endl;
        if (gate.substr(0, 8) == GATE_SOUTHIO)
        {
            EV << "sendin' up" << endl;
            sendUp(pdu);
        }
        else if (gate.substr(0, 7) == GATE_EFCPIO)
        {
            EV << "sendin' down" << endl;
            sendDown(pdu);
        }
    }
    else if (dynamic_cast<CDAPMessage*>(msg) != NULL)
    { // management message arrival
        if (gate == "southIo$i")
        {
            send(msg, "ribdIo$o");
        }
        else
        {
            send(msg, "southIo$o", 0);
        }
    }
    else
    {
        EV << this->getFullPath() << " message type not supported" << endl;
        delete msg;
    }
}

