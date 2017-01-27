// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/RA/QueueIDGen/IDPerNCU/IDPerNCU.h"

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
