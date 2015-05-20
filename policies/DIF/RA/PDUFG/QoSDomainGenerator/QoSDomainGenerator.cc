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

#include <QoSDomainGenerator/QoSDomainGenerator.h>
#include "APN.h"

#include <stdio.h>
#include <stdlib.h>


namespace QoSDomainGenerator {

Register_Class(QoSDomainGenerator);

using namespace std;

void QoSDomainGenerator::removedFlow(const Address &addr, const std::string &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[qos][dst].erase(port);

    if(neighbours[qos][dst].size() <= 0){
        //char intStr[10];
        //sprintf(intStr, "%d", qos);
        //string str = string(intStr);
        rt->removeFlow(addr,qos, dst);
        neighbours[qos].erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void QoSDomainGenerator::routingUpdated(){
    DMRnms::dmUpdateM changes = rt->getChanges();
    for(DMRnms::dmUpdateMIt it = changes.begin(); it!= changes.end(); it++){
        std::string QoS;
        int value = atoi(it->domain.c_str());
        if(value > 0 && value <= nDom) { QoS = it->domain; }
        else { continue; }

        for(DMRnms::s2AIt eIt = it->entries.begin(); eIt != it->entries.end(); eIt++){
            std::string dst = eIt->first;
            std::string nextHop = eIt->second.getIpcAddress().getName();

            EV << "Entry ::: "<< dst << " -> " << nextHop << " ("<< eIt->second<<")" <<endl;
            RMTPort * p = NULL;

            NTableIt n = neighbours[QoS].find(nextHop);
            if(n != neighbours[QoS].end()){
                p = *(n->second.begin());
            }

            if(p == NULL) {
                fwd->remove(dst, QoS);
            } else {
                fwd->insert(dst, QoS, p);
            }
        }
    }
}

// Called after initialize
void QoSDomainGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<QoSTable::QoSTable *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));

    rt = check_and_cast<DMRnms::Routing *>
        (getModuleByPath("^.^.routingPolicy"));

    std::string alg = par("alg").stdstringValue();

    nDom = par("nDomains").longValue();

    if(alg == "LS"){
        char intStr[10];
        string str;
        for(int i = 1; i<= nDom; i++){
            sprintf(intStr, "%d", i);
            str = string(intStr);
            rt->addDomain(str, getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
        }
    } else {
        char intStr[10];
        string str;
        for(int i = 1; i<= nDom; i++){
            sprintf(intStr, "%d", i);
            str = string(intStr);
            rt->addDomain(str, getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
        }
    }

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
