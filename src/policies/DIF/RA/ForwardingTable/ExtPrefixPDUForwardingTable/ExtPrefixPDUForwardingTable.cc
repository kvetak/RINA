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

/**
 * @file ExtPrefixPDUForwardingTable.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief PDU forwarding (routing) table used by RMT relay.
 * @detail
 */

#include "ExtPrefixPDUForwardingTable.h"
#include "Utils.h"

Define_Module(ExtPrefixPDUForwardingTable);


ExtPrefixPDUForwardingTable::ExtPrefixPDUForwardingTable(){
    delimiter = '.';
}

void ExtPrefixPDUForwardingTable::finish(){
    printAll();
    for(Type2ListIt it = qos2Valid.begin(); it != qos2Valid.end(); it++){
        EV << "QOS : " << it->first << endl;
        for(typeListIt it2 = it->second.begin(); it2 != it->second.end(); it2++){
            EV << "\tvalid : " << *it2 << endl;
        }
    }
}

void ExtPrefixPDUForwardingTable::initialize(){
    beQoSId = (unsigned short) par("beQoSId").longValue();

    cXMLElement* validXml = NULL;
    if (par("qos2Valid").xmlValue() != NULL && par("qos2Valid").xmlValue()->hasChildren())
        validXml = par("qos2Valid").xmlValue();
    else
        error("qos2Valid parameter not initialized!");

    cXMLElementList qosL = validXml->getChildrenByTagName("QosCube");
    for (cXMLElementList::iterator it = qosL.begin(); it != qosL.end(); ++it) {
        cXMLElement* m = *it;
        if (!m->getAttribute("id")) {
            EV << "Error parsing CU. Its ID is missing!" << endl;
            continue;
        }
        if ((unsigned short)atoi(m->getAttribute("id")) < 0 ) {
            EV << "QosID < 0 cannot be used!" << endl;
            continue;
        }
        unsigned short QoSId = (unsigned short) atoi(m->getAttribute("id"));
        typeList valids;

        cXMLElementList attrs = m->getChildren();
        for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt) {
            cXMLElement* n = *jt;
            if ( !strcmp(n->getTagName(), "accepts") && n->getNodeValue() && atoi(n->getNodeValue())>0) {
                unsigned short valid = (unsigned short) atoi(n->getNodeValue());
                valids.push_back(valid);
            }
        }

        qos2Valid[QoSId] = valids;
    }

}
void ExtPrefixPDUForwardingTable::handleMessage(cMessage *msg){}



/**
* Adds an entry to the forwarding table.
*
*/
void ExtPrefixPDUForwardingTable::addEntry(std::string dstAddr, unsigned short QoSid, RMTPort* p){
    table[dstAddr][QoSid] = p;
}

void ExtPrefixPDUForwardingTable::addEntryIfNot(std::string dstAddr, unsigned short QoSid, RMTPort* p){
    if(table[dstAddr].find(QoSid) == table[dstAddr].end()){
        table[dstAddr][QoSid] = p;
    }
}

/**
* Removes an entry of the forwarding table.
*
*/
void ExtPrefixPDUForwardingTable::remove(std::string dstAddr, unsigned short QoSid){
    table[dstAddr].erase(QoSid);
    if(table[dstAddr].size() <= 0){
        table.erase(dstAddr);
    }
}


/**
* Removes an entry of the forwarding table, by address only.
*
*/
void ExtPrefixPDUForwardingTable::remove(std::string dstAddr){
    table.erase(dstAddr);
}


/**
* Set the prefix delimiter to use
*
*/
void ExtPrefixPDUForwardingTable::setDelimiter(char _delimiter){
    delimiter = _delimiter;
}

/**
* Dumps the contents of the forwarding table to OMNeT++ output console.
*
*/
void ExtPrefixPDUForwardingTable::printAll()
{
    EV << "Printing the whole forwarding table: " << endl;
    for(FWDTableIt it = table.begin(); it!= table.end(); ++it)
    {
        std::string addr = it->first;
        for(type2PortIt it2 = it->second.begin(); it2 != it->second.end(); it2++){
            EV << this->getFullPath()
               << " dstAddr: " << it->first
               << "; QoS ID: " << it2->first
               << "; port-id: " << it2->second->getFullName() << endl;
        }
    }
}

/**
* Looks up a port-id to be used for given address and Qos-id.
*
* @param destAddr destination IPC process address
* @param QoSid QoS-id
* @return port-id
*/
RMTPort* ExtPrefixPDUForwardingTable::lookup(const std::string& destAddr, const unsigned short &QoSid)
{
    typeList * accepted = &qos2Valid[QoSid];
    RMTPort* ret = search(destAddr, QoSid, accepted);
    if(ret != NULL){
        return ret;
    }
    std::vector<std::string> addrParsed = split(destAddr, delimiter);
    for(int i = addrParsed.size()-1; i>=0; i--){
        ret = search(join(addrParsed, i, delimiter), QoSid, accepted);
        if(ret != NULL){
            return ret;
        }
    }
    return NULL;
}

RMTPort* ExtPrefixPDUForwardingTable::lookup(const std::string & destAddr)
{
    return lookup(destAddr, beQoSId);
}

RMTPort* ExtPrefixPDUForwardingTable::lookup(Address& destAddr, unsigned short QoSid)
{
    return lookup(destAddr.getIpcAddress().getName(), QoSid);
}

RMTPort* ExtPrefixPDUForwardingTable::lookup(Address& destAddr)
{
    return lookup(destAddr.getIpcAddress().getName(), beQoSId);
}

RMTPort * ExtPrefixPDUForwardingTable::search(const std::string &pref, const unsigned short &QoSid, const typeList * accepted){
    FWDTableIt query = table.find(pref);
    if(query == table.end()){
        return NULL;
    }

    type2PortIt res = query->second.find(QoSid);
    if(res != query->second.end()){
        return res->second;
    }

    for(typeListCIt it = accepted->begin(); it != accepted->end(); it++){
        res = query->second.find(*it);
        if(res != query->second.end()){
            return res->second;
        }
    }

    return NULL;
}


void ExtPrefixPDUForwardingTable::clean()
{
    table.clear();
}
