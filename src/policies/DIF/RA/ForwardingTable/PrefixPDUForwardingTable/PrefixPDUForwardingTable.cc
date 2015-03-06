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
 * @file PrefixPDUForwardingTable.cc
 * @author Tomas Hykel (xhykel01@stud.fit.vutbr.cz)
 * @brief PDU forwarding (routing) table used by RMT relay.
 * @detail
 */

#include "PrefixPDUForwardingTable.h"
#include "Utils.h"

Define_Module(PrefixPDUForwardingTable);


PrefixPDUForwardingTable::PrefixPDUForwardingTable()
{
    delimiter = '.';
}


void PrefixPDUForwardingTable::initialize(){}
void PrefixPDUForwardingTable::handleMessage(cMessage *msg){}



/**
* Adds an entry to the forwarding table.
*
*/
void PrefixPDUForwardingTable::addEntry(std::string dstAddr, unsigned short QoSid, RMTPort* p){
    table[addrQoS(dstAddr, QoSid)] = p;
    qosCol.insert(QoSid);
}
void PrefixPDUForwardingTable::addEntryIfNot(std::string dstAddr, unsigned short QoSid, RMTPort* p){
    if(table[addrQoS(dstAddr, QoSid)] == NULL){
        table[addrQoS(dstAddr, QoSid)] = p;
        qosCol.insert(QoSid);
    }
}

/**
* Removes an entry of the forwarding table.
*
*/
void PrefixPDUForwardingTable::remove(std::string dstAddr, unsigned short QoSid){
    table.erase(addrQoS(dstAddr, QoSid));
}


/**
* Removes an entry of the forwarding table, by address only.
*
*/
void PrefixPDUForwardingTable::remove(std::string dstAddr){
    for(QoSColIterator it = qosCol.begin(); it != qosCol.end(); it++){
        table.erase(addrQoS(dstAddr, *it));
    }
}


/**
* Set the prefix delimiter to use
*
*/
void PrefixPDUForwardingTable::setDelimiter(char _delimiter){
    delimiter = _delimiter;
}

/**
* Dumps the contents of the forwarding table to OMNeT++ output console.
*
*/
void PrefixPDUForwardingTable::printAll()
{
    EV << "Printing the whole forwarding table: " << endl;
    for(PFwTabIterator it = table.begin(); it!= table.end(); ++it)
    {
        addrQoS a = it->first;
        EV << this->getFullPath()
           << " dstAddr: " << a.first
           << "; QoS ID: " << a.second
           << "; port-id: " << it->second->getFullName() << endl;
    }
}

/**
* Looks up a port-id to be used for given address and Qos-id.
*
* @param destAddr destination IPC process address
* @param QoSid QoS-id
* @return port-id
*/
RMTPort* PrefixPDUForwardingTable::lookup(Address& destAddr, unsigned short QoSid)
{
    std::string s = destAddr.getIpcAddress().getName();
    addrQoS aq = addrQoS(s, QoSid);
    PFwTabIterator query = table.find(aq);
    if(query != table.end()){
        return query->second;
    }

    std::vector<std::string> addrParsed = split(s, delimiter);

    for(int i = addrParsed.size()-1; i>=0; i++){
        aq.first = join(addrParsed, i, delimiter);
        query = table.find(aq);
        if(query != table.end()){
            return query->second;
        }
    }

    return NULL;
}

RMTPort* PrefixPDUForwardingTable::lookup(Address& destAddr)
{
    std::string s = destAddr.getIpcAddress().getName();
    addrQoS aq = addrQoS(s, 0);
    PFwTabIterator query;
    for(QoSColIterator it = qosCol.begin(); it != qosCol.end(); it++){
        aq.second = *it;
        query = table.find(aq);
        if(query != table.end()){
            return query->second;
        }
    }

    std::vector<std::string> addrParsed = split(s, delimiter);

    for(int i = addrParsed.size()-1; i>=0; i++){
        aq.first = join(addrParsed, i, delimiter);

        for(QoSColIterator it = qosCol.begin(); it != qosCol.end(); it++){
            aq.second = *it;
            query = table.find(aq);
            if(query != table.end()){
                return query->second;
            }
        }
    }

    return NULL;
}


void PrefixPDUForwardingTable::clean()
{
    table.clear();
    qosCol.clear();
}
