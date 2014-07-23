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

#include "Flow.h"

Register_Class(Flow);


Flow::Flow() :
        srcPortId(UNDEFINED_PORTADDR), dstPortId(UNDEFINED_PORTADDR),
        srcAddr(UNDEFINED_PORTADDR), dstAddr(UNDEFINED_PORTADDR),
        createFlowRetries(0), maxCreateFlowRetries(MAX_CREATERETRIES), hopCount(MAX_HOPCOUNT) {
}

Flow::Flow(APNamingInfo src, APNamingInfo dst) :
        srcPortId(UNDEFINED_PORTADDR), dstPortId(UNDEFINED_PORTADDR),
        srcAddr(UNDEFINED_PORTADDR), dstAddr(UNDEFINED_PORTADDR),
        createFlowRetries(0), maxCreateFlowRetries(MAX_CREATERETRIES), hopCount(MAX_HOPCOUNT) {
    this->srcApni = src;
    this->dstApni = dst;
}

Flow::~Flow() {
    this->srcPortId = UNDEFINED_PORTADDR;
    this->dstPortId = UNDEFINED_PORTADDR;
    this->srcAddr = UNDEFINED_PORTADDR;
    this->dstAddr = UNDEFINED_PORTADDR;
    this->createFlowRetries = 0;
    this->maxCreateFlowRetries = 0;
    this->hopCount = 0;
}

std::string Flow::info() const {
    std::stringstream os;
    os << "SRC>\t" << srcApni <<  "\tport: " << srcPortId << "\taddr: " << srcAddr << "\n" <<
          "DST>\t" << dstApni <<  "\tport: " << dstPortId << "\taddr: " << dstAddr << "\n" <<
          "Hop Count: " << hopCount << "\n" <<
          "Retries: " << createFlowRetries << "/" << maxCreateFlowRetries << endl;
    return os.str();
}

//Free function
std::ostream& operator<< (std::ostream& os, const Flow& fl) {
    return os << fl.info();
}
