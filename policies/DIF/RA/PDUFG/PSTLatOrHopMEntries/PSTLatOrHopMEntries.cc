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

#include "DIF/RA/PDUFG/PSTLatOrHopMEntries/PSTLatOrHopMEntries.h"
#include "Common/APN.h"
#include "DIF/RA/QueueIDGen/IDPerNQoSxPLen/IDPerNQoSxPLen.h"



namespace NSPPSTLatOrHopMEntries {

Register_Class(PSTLatOrHopMEntries);

using namespace std;
using namespace common_GraphCL;

//Routing has processes a routing update
void PSTLatOrHopMEntries::routingUpdated(){
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
                    if(ps.empty()) {
                        for(auto qId : qIds) {
                            qId->setDistance(entry.first, qos, INT_MAX);
                        }
                    } else {
                        for(auto qId : qIds) {
                            qId->setDistance(entry.first, qos, entry.second.metric);
                        }
                    }
                }
            } else {
                for(auto & qos : hopQoS) {
                    fwd->addReplace(entry.first, qos, ps);
                    if(ps.empty()) {
                        for(auto qId : qIds) {
                            qId->setDistance(entry.first, qos, INT_MAX);
                        }
                    } else {
                        for(auto qId : qIds) {
                            qId->setDistance(entry.first, qos, entry.second.metric);
                        }
                    }
                }
            }
        }
    }
}

}
