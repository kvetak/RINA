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

// Author: Kewin Rausch (kewin.rausch@create-net.org)

#include "FSInfo.h"

FSInfo::FSInfo()
{

}

FSInfo::FSInfo(Address src, Address dst, unsigned short QoSID, unsigned int metric)
{
    setDestination(dst);
    setMetric(metric);
    setQoSID(QoSID);
    setSource(src);
}

FSInfo::~FSInfo()
{

}

// Getters.

Address FSInfo::getDestination()
{
    return dstAddr;
}

unsigned int FSInfo::getMetric()
{
    return metricWeight;
}

short unsigned int FSInfo::getQoSID()
{
    return QoSID;
}

Address FSInfo::getSource()
{
    return srcAddr;
}

// Setters.

void FSInfo::setDestination(Address dest)
{
    dstAddr = dest;
}

void FSInfo::setMetric(unsigned int weight)
{
    metricWeight = weight;
}

void FSInfo::setQoSID(unsigned short id)
{
    QoSID = id;
}

void FSInfo::setSource(Address src)
{
    srcAddr = src;
}
