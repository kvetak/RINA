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

#include "DIF/RA/PDUFG/SimpleLatOrHopMEntries/SimpleLatOrHopMEntries.h"
#include "Common/APN.h"



namespace NSPSimpleLatOrHopMEntries {

Register_Class(SimpleLatOrHopMEntries);

using namespace std;
using namespace common_GraphCL;

// A new flow has been inserted/or removed
void SimpleLatOrHopMEntries::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){

    string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);
    int lat = dstLat[dst];
    fwd->setPortDelay(port, dstDLat[dst]);

    if(lat <= 0) {
        lat = maxLat;
        dstLat[dst] = maxLat;
    }

    if(neighbours[dst].size() == 1){
        rt->insertFlow(addr, dst, "lat", lat);
        rt->insertFlow(addr, dst, "hops", 1);
        routingUpdated();
    }
}
void SimpleLatOrHopMEntries::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();

    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        rt->removeFlow(addr, dst, "lat");
        rt->removeFlow(addr, dst, "hops");
        neighbours.erase(dst);
        routingUpdated();
    }
}

//Routing has processes a routing update
void SimpleLatOrHopMEntries::routingUpdated(){
    map<string, map<string, nhLMetric<mType>  > > changes = rt->getChanges();

    for(const auto & qosEntries : changes){
        bool lat = qosEntries.first == "lat";
        for(const auto & entry : qosEntries.second){
            std::vector< RMTPort * > ps;
            for(string nextHop : entry.second.nh){
                if(nextHop != "") {
                    if(!neighbours[nextHop].empty()) {
                        ps.push_back(*neighbours[nextHop].begin());
                    }
                }
            }

            if(lat) {
                for(auto & qos : latQoS) {
                    fwd->addReplace(entry.first, qos, ps);
                }
            } else {
                for(auto & qos : hopQoS) {
                    fwd->addReplace(entry.first, qos, ps);
                }
            }
        }
    }
}

// Called after initialize
void SimpleLatOrHopMEntries::onPolicyInit(){
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

        if (!qos->getAttribute("urgent")) {
            hopQoS.insert(id);
        } else {
            latQoS.insert(id);
        }
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
