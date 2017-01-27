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

#include "DIF/RMT/Monitor/ModularMonitor/MM_SPort_Drop/MM_SPort_Drop.h"

namespace MM_SPort_Drop {

Define_Module(MM_SPort_Drop);

MM_SPort_Drop::~MM_SPort_Drop(){
    portCount.clear();
}

void MM_SPort_Drop::pduInsertered(RMTQueue * q, RMTPort * p) {
    portCount[p]++;
}

void MM_SPort_Drop::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    portCount[p]--;
}

void MM_SPort_Drop::pduReleased(RMTQueue * q, RMTPort * p) {
    portCount[p]--;
}

void MM_SPort_Drop::queueCreated(RMTQueue * q, RMTPort * p) {
    portCount[p] = 0;
}

double MM_SPort_Drop::getDropProbability(RMTQueue * q, RMTPort * p) {
    return (q->getMaxLength() < portCount[p])? 1.0 : 0.0;
}

}
