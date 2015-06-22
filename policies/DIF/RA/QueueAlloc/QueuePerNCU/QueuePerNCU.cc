//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "QueuePerNCU.h"

Define_Module(QueuePerNCU);


void QueuePerNCU::onPolicyInit()
{
    cXMLElement* cuXml = NULL;
    if (par("cuData").xmlValue() != NULL && par("cuData").xmlValue()->hasChildren())
        cuXml = par("cuData").xmlValue();
    else
        error("cuData parameter not initialized!");

    cXMLElementList cus = cuXml->getChildrenByTagName("CUItem");
    for (cXMLElementList::iterator it = cus.begin(); it != cus.end(); ++it) {
        cXMLElement* m = *it;
        if (!m->getAttribute("id")) {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }
        std::string cu = m->getAttribute("id");
        if (cu == "") {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }

        CUs.insert(cu);
    }
}

void QueuePerNCU::onNM1PortInit(RMTPort* port)
{
    rmtAllocator->addQueue(RMTQueue::OUTPUT, port, "BE");
    rmtAllocator->addQueue(RMTQueue::INPUT, port, "BE");

    for(std::set<std::string>::iterator it = CUs.begin(); it!= CUs.end(); it++){
        rmtAllocator->addQueue(RMTQueue::OUTPUT, port, it->c_str());
        rmtAllocator->addQueue(RMTQueue::INPUT, port, it->c_str());
    }
}
