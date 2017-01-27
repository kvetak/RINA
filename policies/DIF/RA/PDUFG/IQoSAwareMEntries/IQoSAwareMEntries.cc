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

#include "DIF/RA/PDUFG/IQoSAwareMEntries/IQoSAwareMEntries.h"
#include "Common/APN.h"



namespace IQoSAwareMEntries {

Register_Class(IQoSAwareMEntries);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void IQoSAwareMEntries::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){

    string dst = addr.getIpcAddress().getName();
    string qosId = qos.getQosId();
    portQoS[port] = qosId;
    neighbours[qosId][dst].insert(port);
    int lat = dstLat[dst];

    fwd->setPortDelay(port, dstDLat[dst]);

    if(lat <= 0) {
        lat = maxLat;
        dstLat[dst] = maxLat;
    }

    if(neighbours[qosId][dst].size() == 1){
        if(urgentQoS.find(qosId) != urgentQoS.end()) {
            rt->insertFlow(addr, dst, qosId, lat);
        } else {
            rt->insertFlow(addr, dst, qosId, 1);
        }
        routingUpdated();
    }

    qosId = "*";
    neighbours[qosId][dst].insert(port);
    if(neighbours[qosId][dst].size() == 1){
        if(urgentQoS.find(qosId) != urgentQoS.end()) {
            rt->insertFlow(addr, dst, qosId, lat);
        } else {
            rt->insertFlow(addr, dst, qosId, 1);
        }
        routingUpdated();
    }
}
void IQoSAwareMEntries::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    string qosId = portQoS[port];
    neighbours[qosId][dst].erase(port);
    if(neighbours[qosId][dst].size() <= 0){
        rt->removeFlow(addr, dst, qosId);
        neighbours[qosId].erase(dst);
        if(neighbours[qosId].size()<=0) {
            neighbours.erase(qosId);
        }
        routingUpdated();
    }

    qosId = "*";
    neighbours[qosId][dst].erase(port);
    if(neighbours[qosId][dst].size() <= 0){
        rt->removeFlow(addr, dst, qosId);
        neighbours[qosId].erase(dst);
        if(neighbours[qosId].size()<=0) {
            neighbours.erase(qosId);
        }
        routingUpdated();
    }

    portQoS.erase(port);
}

//Routing has processes a routing update
void IQoSAwareMEntries::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & qosEntries : changes){
        string qosId = qosEntries.first;
        for(const auto & entry : qosEntries.second){
            std::vector< RMTPort * > ps;
            for(string nextHop : entry.second.nh){
                RMTPort * p = NULL;
                if(nextHop != "") {
                    auto n = neighbours[qosId].find(nextHop);
                    if(n != neighbours[qosId].end()){
                        if(!n->second.empty()) {
                            p = *(n->second.begin());
                        }
                    }
                }
                if(p != NULL) {
                    ps.push_back(p);
                }
                fwd->addReplace(entry.first, qosId, ps);
            }
        }
    }
}

// Called after initialize
void IQoSAwareMEntries::onPolicyInit(){
    //Set Forwarding policy
    fwd = check_and_cast<IntIQoSMForwarding *>
        (getModuleByPath("^.^.relayAndMux.pduForwardingPolicy"));
    rt = check_and_cast<IntTSimpleRouting<mType> *>
        (getModuleByPath("^.^.routingPolicy"));

    difA = check_and_cast<DA *>(getModuleByPath("^.^.^.difAllocator.da"));

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);

    maxLat = par("maxLat").longValue();

    string myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();


    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else { return; }


    cXMLElementList QoSs = Xml->getChildrenByTagName("Qos");
    for(auto qos : QoSs){
        if (!qos->getAttribute("id")) { error("Error. ID is missing!"); }
        std::string id = qos->getAttribute("id");
        if (id=="") { error("Error. ID cannot be empty!"); }

        if (!qos->getAttribute("urgent")) { continue; }
        urgentQoS.insert(id);
    }

    double latMultip = par("latMultip").doubleValue();

    cXMLElementList Links = Xml->getChildrenByTagName("Link");
    for(auto link : Links){
        if (!link->getAttribute("src")) { error("Error. Addr is missing!"); }
        std::string src = link->getAttribute("src");
        if (src=="") { error("Error. Addr cannot be empty!"); }

        if (!link->getAttribute("dst")) { error("Error. Addr is missing!"); }
        std::string dst = link->getAttribute("dst");
        if (dst=="") { error("Error. Addr cannot be empty!"); }


        if (!link->getAttribute("l")) { error("Error. Latency is missing!"); }
        double l = atof(link->getAttribute("l"));
        if (l < 0.0) { error("Error. Latency cannot be < 0"); }
        int lat = l*latMultip;
        if (lat > maxLat) { lat = maxLat; }

        if(src == myAddr) { dstLat[dst] = lat; dstDLat[dst] = l/1000.0; }
        else if(dst == myAddr) { dstLat[src] = lat; dstDLat[src] = l/1000.0; }
    }
}

}
