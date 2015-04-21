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

#include <QoSCubeComparerMin.h>

Define_Module(QoSCubeComparerMin);

bool QoSCubeComparerMin::run(Flow& flow) {
    Enter_Method("invokeNewFlowRequestPolicy()");
    //Is flow policy acceptable
    std::string apname = flow.getSrcApni().getApn().getName();

    //FIXME: Vesely - Simulate error and DTCP flag better
    if ( apname.find("Err") != std::string::npos) {
        return false;
    }

    //TODO: Compare QoS Parameters with available QoS cubes
    QoSCubeSet cubes = ResourceAllocator->getQoSCubes();
    //EV << ResourceAllocator->getQoSCubes();

    unsigned short qosid = 0;
    double cost = DBL_MAX;

    for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
        if(flow.getQosParameters().isFeasibility(*it)){
            if (cost > it->getCostBits()) {
                cost = it->getCostBits();
                qosid = it->getQosId();
            }
        }
    }
    if(!qosid) {
        short score = -99;

        for (QCubeCItem it = cubes.begin(); it != cubes.end(); ++it) {
            short tmpscore = flow.getQosParameters().countFeasibilityScore(*it);
            if (score < tmpscore || (score == tmpscore && cost > it->getCostBits() ) ) {
                score = tmpscore;
                qosid = it->getQosId();
                cost = it->getCostBits();
            }
        }
    }
    flow.getConnectionId().setQoSId(qosid);

    return qosid ? true : false;

}

