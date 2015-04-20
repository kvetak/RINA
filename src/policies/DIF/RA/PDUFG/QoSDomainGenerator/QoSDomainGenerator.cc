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



namespace QoSDomainGenerator {

Register_Class(QoSDomainGenerator);

using namespace std;

// A new flow has been inserted/or removed
void QoSDomainGenerator::insertedFlow(const Address &addr, const unsigned short &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[qos][dst].insert(port);
    if(neighbours[qos][dst].size() == 1){
        switch(qos) {
            case 1 :rt->addFlow(addr,"1", dst,1); break;
            case 2 :rt->addFlow(addr,"2", dst,1); break;
            case 3 :rt->addFlow(addr,"3", dst,1); break;
            case 4 :rt->addFlow(addr,"4", dst,1); break;
        }
        routingUpdated();
    }
}
void QoSDomainGenerator::removedFlow(const Address &addr, const unsigned short &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[qos][dst].erase(port);
    if(neighbours[qos][dst].size() <= 0){
        switch(qos) {
            case 1 :rt->removeFlow(addr,"1", dst); break;
            case 2 :rt->removeFlow(addr,"2", dst); break;
            case 3 :rt->removeFlow(addr,"3", dst); break;
            case 4 :rt->removeFlow(addr,"4", dst); break;
        }
        neighbours[qos].erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void QoSDomainGenerator::routingUpdated(){
    DMRnms::dmUpdateM changes = rt->getChanges();
    for(DMRnms::dmUpdateMIt it = changes.begin(); it!= changes.end(); it++){
        unsigned short QoS;
        if(it->domain == "1") { QoS = 1; }
        else if(it->domain == "2") { QoS = 2; }
        else if(it->domain == "3") { QoS = 3; }
        else if(it->domain == "4") { QoS = 4; }
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

    if(alg == "LS"){
        rt->addDomain("1", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
        rt->addDomain("2", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
        rt->addDomain("3", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
        rt->addDomain("4", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::LS);
    } else {
        rt->addDomain("1", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
        rt->addDomain("2", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
        rt->addDomain("3", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
        rt->addDomain("4", getParentModule()->getParentModule()->par("ipcAddress").stringValue(), DMRnms::DV);
    }

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));
}

}
