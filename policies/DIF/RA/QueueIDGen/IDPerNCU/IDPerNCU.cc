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

#include "IDPerNCU.h"

Define_Module(IDPerNCU);

void IDPerNCU::onPolicyInit()
{
    cXMLElement* qos2cuXml = NULL;
    if (par("qos2cuData").xmlValue() != NULL && par("qos2cuData").xmlValue()->hasChildren())
        qos2cuXml = par("qos2cuData").xmlValue();
    else
        error("qos2cuData parameter not initialized!");

    cXMLElementList qos2cu = qos2cuXml->getChildrenByTagName("qos");
    for (cXMLElementList::iterator it = qos2cu.begin(); it != qos2cu.end(); ++it) {
        cXMLElement* m = *it;

        if (!m->getAttribute("id")) {
            EV << "Error parsing qos2cu. Its ID is missing!" << endl;
            continue;
        }
        std::string qosId = m->getAttribute("id");

        if (!m->getAttribute("cu")) {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }
        std::string cu = m->getAttribute("cu");
        if (cu == "") {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }


        qos2CU[qosId] =  cu;
    }
}

std::string IDPerNCU::generateOutputQueueID(PDU* pdu)
{
    std::string qosId = pdu->getConnId().getQoSId();
    if(qos2CU.find(qosId) != qos2CU.end()){
        return qos2CU[qosId];
    } else {
        return "BE";
    }
}

std::string IDPerNCU::generateInputQueueID(PDU* pdu)
{
    return generateOutputQueueID(pdu);
}
