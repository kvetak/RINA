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

#include <RMT.h>

Define_Module(RMT);

const int PROCESSING_DELAY = 0.0;

RMT::RMT()
{

}

RMT::~RMT()
{
}



void RMT::initialize() {

    processName = this->getParentModule()->getParentModule()->par("ipcAddress").stdstringValue();
    cModule* hostModule = getParentModule()->getParentModule();

    // determine whether we're on wire or on top of another DIF
    std::string bottomModule = hostModule->gate("southIo$o", 0)->getNextGate()->getName();

    if (bottomModule == "medium$o")
    { // we're on wire! no need to relay anything
        relayOn = false;
    }
    else if (bottomModule == "northIo$o")
    { // there are some other IPC processes below
        if (hostModule->gateSize("northIo") > 1)
        {
            fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
            relayOn = true;
        }
        else
        {
            relayOn = false;
        }
    }

    // store the available output gates
    for (int i = 0; i < this->gateSize("southIo"); i++)
    {
        intGates[i] = this->gateHalf("southIo", cGate::OUTPUT, i);
    }

//    ports = ModuleAccess<RMTPortManager>("rmtPortManager").get();
}

bool RMT::relayStatus()
{
    return relayOn;
}

void RMT::createEfcpiGate(unsigned int efcpiId)
{
    if (efcpiGates.count(efcpiId))
    {
        return;
    }

    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << "efcpIo_" << efcpiId;

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

void RMT::deleteEfcpiGate(int efcpiId)
{
    if (!efcpiGates.count(efcpiId))
    {
        return;
    }

    cModule* rmtModule = getParentModule();

    std::ostringstream gateName_str;
    gateName_str << "efcpIo_" << efcpiId;

    cGate* rmtOut = this->gateHalf(gateName_str.str().c_str(), cGate::OUTPUT);
    cGate* rmtModuleIn = rmtModule->gateHalf(gateName_str.str().c_str(), cGate::INPUT);

    rmtOut->disconnect();
    rmtModuleIn->disconnect();

    this->deleteGate(gateName_str.str().c_str());
    rmtModule->deleteGate(gateName_str.str().c_str());

    efcpiGates.erase(efcpiId);
}

void RMT::sendDown(PDU_Base* pdu)
{
    std::string pduDestAddr = pdu->getDestAddr().getName();
    int pduQosId = pdu->getConnId().getQoSId();
    cGate* outPort;

    if (relayOn)
    {
        try
        { // forwarding table lookup
            int outPortId = fwTable->lookup(pduDestAddr, pduQosId);
            outPort = intGates[outPortId];
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
        outPort = intGates[0];
    }

    send(pdu, outPort);
}

void RMT::sendUp(PDU_Base* pdu)
{
    if (pdu->getDestAddr().getName() != processName)
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
        createEfcpiGate(pdu->getConnId().getSrcCepId());
        cGate* efcpiGate = efcpiGates[pdu->getConnId().getSrcCepId()];

        EV << this->getFullPath() << " delivering a PDU to EFCPI " << efcpiGate->getName() << endl;
        //send(pdu, efcpiGate);
        delete pdu;
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
        if ((gate == "southIo$i") || (gate == "ribdIo$i"))
        {
            sendUp(pdu);
        }
        else if (gate.substr(0, 6) == "efcpIo")
        {
          //TODO change it back to Tomas's version
            //sendDown(pdu);
          send(msg, efcpiGates[pdu->getConnId().getSrcCepId()]);
        }
    }
    // TODO: ew, replace this with a shared base class when it's available
    else if (dynamic_cast<CDAP_M_Create*>(msg) || dynamic_cast<CDAP_M_Create_R*>(msg) ||
             dynamic_cast<CDAP_M_Delete*>(msg) || dynamic_cast<CDAP_M_Delete_R*>(msg) ||
             dynamic_cast<CDAP_M_Start*>(msg) || dynamic_cast<CDAP_M_Start_R*>(msg)   ||
             dynamic_cast<CDAP_M_Stop*>(msg) || dynamic_cast<CDAP_M_Stop_R*>(msg)     ||
             dynamic_cast<CDAP_M_Write*>(msg) || dynamic_cast<CDAP_M_Write_R*>(msg)   ||
             dynamic_cast<CDAP_M_Read*>(msg) || dynamic_cast<CDAP_M_Read_R*>(msg)     ||
             dynamic_cast<CDAP_M_CancelRead*>(msg) || dynamic_cast<CDAP_M_CancelRead_R*>(msg))
    {
        if (gate == "southIo$i")
        { // temporary queue bypass
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

