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

#include "DIF/RMT/Monitor/ModularMonitor/MM_Simple_Out/MM_Simple_Out.h"

namespace MM_Simple_Out {

Define_Module(MM_Simple_Out);

MM_Simple_Out::~MM_Simple_Out() {
    for(auto & pQ : portQueues) {
        pQ.second.clear();
    }
    portQueues.clear();
}

void MM_Simple_Out::pduInsertered(RMTQueue * q, RMTPort * p) {
    portQueues[p].push_back(q);
}

void MM_Simple_Out::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    portQueues[p].pop_back();
}

void MM_Simple_Out::pduReleased(RMTQueue * q, RMTPort * p) {}

void MM_Simple_Out::queueCreated(RMTQueue * q, RMTPort * p) {
    portQueues[p];
}

RMTQueue * MM_Simple_Out::getnextQueue(RMTPort * p) {
    auto pQ = &portQueues[p];
    while(!pQ->empty()) {
        RMTQueue * q = pQ->front();
        pQ->pop_front();
        if(q->getLength() > 0) return q;
    }
    return NULL;
}

simtime_t  MM_Simple_Out::getnextTime(RMTPort * p) {
    return simTime();
}

}
