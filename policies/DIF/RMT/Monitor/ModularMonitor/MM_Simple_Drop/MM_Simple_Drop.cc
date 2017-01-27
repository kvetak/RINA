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

#include "DIF/RMT/Monitor/ModularMonitor/MM_Simple_Drop/MM_Simple_Drop.h"

namespace MM_Simple_Drop {

Define_Module(MM_Simple_Drop);

MM_Simple_Drop::~MM_Simple_Drop(){
    queueCount.clear();
}

void MM_Simple_Drop::pduInsertered(RMTQueue * q, RMTPort * p) {
    queueCount[q]++;
}

void MM_Simple_Drop::pduDropped(RMTQueue * q, const cPacket * s, RMTPort * p) {
    queueCount[q]--;
}

void MM_Simple_Drop::pduReleased(RMTQueue * q, RMTPort * p) {
    queueCount[q]--;
}

void MM_Simple_Drop::queueCreated(RMTQueue * q, RMTPort * p) {
    queueCount[q] = 0;
}

double MM_Simple_Drop::getDropProbability(RMTQueue * q, RMTPort * p) {
    return (q->getMaxLength() < queueCount[q])? 1.0 : 0.0;
}

}
