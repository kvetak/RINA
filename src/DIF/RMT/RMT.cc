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

/*
 * @file RMT.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 4, 2014
 * @brief
 * @detail
 */

#include <RMT.h>

Define_Module(RMT);

RMT::RMT()
{

}

RMT::~RMT()
{
//    delete inputQueues;
//    delete outputQueues;
}

void RMT::fromDTPToRMT(APNamingInfo* destAddr, unsigned int qosId, PDU *pdu)
{
    // to be purged
}

void RMT::initialize() {

    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
    inputQueues = new RMTQueueList;
    outputQueues = new RMTQueueList;
}


void RMT::relayPDU(DataTransferPDU* pdu)
{
    //inputQueues->getQueue(portID)->insertPDU(*pdu);;
    // TODO: invoke monitoring & scheduling policy
}

void RMT::multiplexPDU(DataTransferPDU* pdu)
{
    std::string pduDestAddr = pdu->getDestAddr().getName();
    int pduQosId = pdu->getConnId().getQoSId();

    // forwarding table lookup
    // TODO: ditch the -1 and make it throw an exception instead
    int outPortId = fwTable->lookup(pduDestAddr, pduQosId);

    if (outPortId == -1)
    {
        //EV << this->getFullPath() << " no match in FWTable." << endl;
        // drop the PDU?
    }
    else
    {
        // TODO: optional SDU protection call (when?)

        // TODO: ditch the NULL and make it throw an exception instead
        RMTQueue* qOut = outputQueues->getQueue(outPortId);

        if (qOut != NULL)
        {
            qOut->insertPDU(*pdu);
            // TODO: invoke monitoring & scheduling policy
        }
        else
        {
            //EV << " output queue " << outPortId << " not present" << endl;
        }
    }
}


void RMT::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        // RMT management stuff
    }
    else if (dynamic_cast<DataTransferPDU*>(msg) != NULL)
    {
        DataTransferPDU* pdu = (DataTransferPDU*) msg;
        std::string gate = msg->getArrivalGate()->getName();

        if (gate == "southIo$i")
        {
            this->relayPDU(pdu);
        }
        else if (gate == "efcpIo$i")
        {
            this->multiplexPDU(pdu);
        }

    }
    else
    {
        EV << this->getFullPath() << " message type unsupported" << endl;
    }

    delete msg;
}
