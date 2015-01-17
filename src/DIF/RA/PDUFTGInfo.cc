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

#include "PDUFTGInfo.h"

PDUFTGInfo::PDUFTGInfo()
{

}

PDUFTGInfo::PDUFTGInfo(Address src, Address dst, unsigned short QoSID, unsigned int metric)
{
    setDestination(dst);
    setMetric(metric);
    setQoSID(QoSID);
    setSource(src);
}

PDUFTGInfo::~PDUFTGInfo()
{

}

// Getters.

Address PDUFTGInfo::getDestination()
{
    return dstAddr;
}

unsigned int PDUFTGInfo::getMetric()
{
    return metricWeight;
}

short unsigned int PDUFTGInfo::getQoSID()
{
    return QoSID;
}

Address PDUFTGInfo::getSource()
{
    return srcAddr;
}

// Setters.

void PDUFTGInfo::setDestination(Address dest)
{
    dstAddr = dest;
}

void PDUFTGInfo::setMetric(unsigned int weight)
{
    metricWeight = weight;
}

void PDUFTGInfo::setQoSID(unsigned short id)
{
    QoSID = id;
}

void PDUFTGInfo::setSource(Address src)
{
    srcAddr = src;
}

bool PDUFTGInfo::operator == (const PDUFTGInfo& info) const
{
    return srcAddr == info.srcAddr &&
        dstAddr == info.dstAddr &&
        QoSID == info.QoSID;
}
