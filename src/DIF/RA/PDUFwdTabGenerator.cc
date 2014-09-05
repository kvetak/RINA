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

#include "PDUFwdTabGenerator.h"

Define_Module(PDUFwdTabGenerator);


void PDUFwdTabGenerator::initialize()
{
    fwTable = ModuleAccess<PDUForwardingTable>("pduForwardingTable").get();

    cXMLElement* dirXml = par("PDUFwData").xmlValue();
    cXMLElementList map = dirXml->getChildrenByTagName("FwTableItem");

    for (cXMLElementList::iterator i = map.begin(); i != map.end(); ++i)
    {
        cXMLElement* m = *i;

        int qosid = atoi(m->getAttribute("qosId"));
        int portid = atoi(m->getAttribute("portId"));

        this->insertFwEntry(m->getAttribute("dest"), qosid, portid);
    }
    //fwTable->printAll();
}

void PDUFwdTabGenerator::handleMessage(cMessage *msg)
{

}

void PDUFwdTabGenerator::removeFwEntry(int portId) {
    fwTable->remove(portId);
}

void PDUFwdTabGenerator::insertFwEntry(std::string destAddr, const int qosId, int portId)
{
    PDUTableEntry *ret = new PDUTableEntry(destAddr, qosId, portId);
    fwTable->insert(ret);
}
