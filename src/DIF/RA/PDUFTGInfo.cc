#include "PDUFTGInfo.h"


PDUFTGInfo::PDUFTGInfo(){}
PDUFTGInfo::PDUFTGInfo(Address src, Address dst, unsigned short QoSID, unsigned int metric)
{
    setDestination(dst);
    setMetric(metric);
    setQoSID(QoSID);
    setSource(src);
}

PDUFTGInfo::~PDUFTGInfo(){}

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
