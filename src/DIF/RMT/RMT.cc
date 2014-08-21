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

void RMT::fromDTPToRMT(APNamingInfo* destAddr, unsigned int qosId, PDU *pdu)
{
    // to be purged
}

void RMT::initialize() {

    // TODO: interface-to-portID mapping

    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    flows = ModuleAccess<RMTFlowManager>("rmtFlowManager").get();
}

// a primitive implementation of queue processing (for now)
// just iterate through queues and empty all of them in current simTime
void RMT::runRelay()
{
    //EV << this->getFullPath() << " emptying input queues." << endl;
    for(RMTFlowManager::iterator it = flows->begin(); it != flows->end(); ++it)
    {
        int gate = it->second->getEfcpiGateId();

        while (it->second->getIncomingLength())
        {
            DataTransferPDU* pdu = it->second->popIncomingPDU();

            if (pdu->getDestAddr().getName() !=
                    this->getParentModule()->getParentModule()->par("ipcAddress").stdstringValue())
            { // this PDU isn't for us, let's relay it elsewhere
                this->enqueueMuxPDU(pdu);
                EV << this->getFullPath() << " relaying a PDU elsewhere (gate " << gate << ")" << endl;
                continue;
            }
            // TODO: any additional inbound processing

            EV << this->getFullPath() << " delivering a PDU to EFCPI (gate " << gate << ")" << endl;
            //send(pdu, gate);

            delete pdu;
        }
    }
}

// a primitive implementation of queue processing (for now)
// just iterate through queues and empty all of them in current simTime
void RMT::runMux()
{
    //EV << this->getFullPath() << " emptying output queues." << endl;
    for(RMTFlowManager::iterator it = flows->begin(); it != flows->end(); ++it)
    {
        int gate = it->second->getSouthGateId();

        while (it->second->getOutgoingLength())
        {
            DataTransferPDU* pdu = it->second->popOutgoingPDU();

            // TODO: any additional outbound processing

            EV << this->getFullPath() << " sending a PDU out of gate " << gate << endl;
            send(pdu, "southIo$o", 0);

            //delete pdu;
        }
    }
}

// processing of messages arriving from (N-1) ports
void RMT::enqueueRelayPDU(DataTransferPDU* pdu)
{
    // TODO: identify CDAP packets and put them in a separate queue

    flows->getFlow(1)->addIncomingPDU(pdu);

    cMessage *selfmsg = new cMessage("processIn");
    scheduleAt(simTime() + PROCESSING_DELAY, selfmsg);
}


// processing of messages arriving from EFCP instances
void RMT::enqueueMuxPDU(DataTransferPDU* pdu)
{
    std::string pduDestAddr = pdu->getDestAddr().getName();
    int pduQosId = pdu->getConnId().getQoSId();

    // forwarding table lookup
    int outPortId = fwTable->lookup(pduDestAddr, pduQosId);

    // TODO: ditch the -1 and make it throw an exception instead
    if (outPortId == -1)
    {
        EV << this->getFullPath() << " couldn't find any match in FWTable." << endl;
        delete pdu;
    }
    else
    {
        RMTFlow* qOut = flows->getFlow(outPortId);

        if (qOut != NULL)
        {
            qOut->addOutgoingPDU(pdu);

            cMessage *selfmsg = new cMessage("processOut");
            scheduleAt(simTime() + PROCESSING_DELAY, selfmsg);
        }
        else
        {
            // this shouldn't happen (RA's fault)
        }
    }
}


void RMT::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    { // scheduled PDU processing
        std::string msgtype = msg->getName();

        if (msgtype == "processOut")
        {
            this->runMux();
        }
        else if (msgtype == "processIn")
        {
            this->runRelay();
        }
        delete msg;
    }
    else if (dynamic_cast<DataTransferPDU*>(msg) != NULL)
    { // PDU arrival
        DataTransferPDU* pdu = (DataTransferPDU*) msg;
        std::string gate = msg->getArrivalGate()->getName();

        if (gate == "southIo$i")
        {
            this->enqueueRelayPDU(pdu);
        }
        else if ((gate == "efcpIo$i") || (gate == "ribdIo$i"))
        {
            this->enqueueMuxPDU(pdu);
        }
    }
    else
    {
        EV << this->getFullPath() << " message type not supported" << endl;
        delete msg;
    }
}
