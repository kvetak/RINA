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

}

void RMT::fromDTPToRMT(APNamingInfo* destAddr, unsigned int qosId, PDU *pdu){

}

void RMT::initialize() {

    FwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();
}


void RMT::handleMessage(cMessage *msg) {

    EV << this->getFullPath() << " Received a message." << endl;

    if (msg->isSelfMessage())
    {
        //
    }
    else if (dynamic_cast<DataTransferPDU*>(msg) != NULL)
    { // should we identify the sender module as well?
        DataTransferPDU* pdu = (DataTransferPDU*) msg;

        std::string name = pdu->getDestAddr().getName();
        int qosid = pdu->getConnId().getQoSId();

        EV << this->getFullPath() << " dest address: " << name << "; QoS-id: " << qosid << endl;


        if (name == this->getParentModule()->par("ipcAddress").stdstringValue())
        {
            // EV << this->getFullPath() << " this goes to my IPC!" << endl;
            // pass to an EFCP instance
        }
        else
        {
            //EV << this->getFullPath() << " initating table lookup..." << endl;

            if (FwTable->lookup(pdu->getDestAddr(), qosid) == -1)
            {
                EV << this->getFullPath() << " Couldn't find the item in FWTable." << endl;
                // drop the PDU?
            }
            else
            {
                // TODO: SDU protection call?

                //send(pdu, "southIo$o[]");
            }
        }
    }
    else
    {
        EV << this->getFullPath() << " unsupported" << endl;
    }

    delete msg;
}
