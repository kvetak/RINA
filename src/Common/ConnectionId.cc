// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Common/ConnectionId.h"

//Consts
const int VAL_UNDEF_CEPID = -1;
const int VAL_MGMT_CEPID = 0;

ConnectionId::ConnectionId() :
    qosId(VAL_UNDEF_QOSID), srcCEPId(VAL_UNDEF_CEPID), dstCEPId(VAL_UNDEF_CEPID)
{
}

int ConnectionId::getDstCepId() const
{
    return dstCEPId;
}

void ConnectionId::setDstCepId(int destCepId)
{
    dstCEPId = destCepId;
}

std::string ConnectionId::getQoSId() const
{
    return qosId;
}

void ConnectionId::setQoSId(std::string qoSId)
{
    this->qosId = qoSId;
}

int ConnectionId::getSrcCepId() const
{
    return srcCEPId;
}

void ConnectionId::setSrcCepId(int srcCepId)
{
    srcCEPId = srcCepId;
}

ConnectionId::~ConnectionId()
{
    qosId = VAL_UNDEF_QOSID;
    srcCEPId = 0;
    dstCEPId = 0;
}

ConnectionId *ConnectionId::dup() const
{
  ConnectionId* connId = new ConnectionId();
  connId->setDstCepId(this->dstCEPId);
  connId->setSrcCepId(this->srcCEPId);
  connId->setQoSId(this->qosId);
  return connId;
}

bool ConnectionId::operator<(const ConnectionId other) const
{
    if (qosId < other.qosId)  return true;
    if (qosId > other.qosId)  return false;

    if (dstCEPId < other.dstCEPId)  return true;
    if (dstCEPId > other.dstCEPId)  return false;

    if (srcCEPId < other.srcCEPId)  return true;
    if (srcCEPId > other.srcCEPId)  return false;

    return false;
}

bool ConnectionId::operator==(const ConnectionId other) const
{
    return qosId == other.qosId
           && dstCEPId == other.dstCEPId
           && srcCEPId == other.srcCEPId;
}

ConnectionId& ConnectionId::swapCepIds()
{
    int tmp = srcCEPId;
    srcCEPId = dstCEPId;
    dstCEPId = tmp;
    return *this;
}

std::string ConnectionId::info() const
{
  std::ostringstream os;

  os << srcCEPId << ":" << dstCEPId << ":"  << qosId;
  return os.str();
}

std::ostream& operator <<(std::ostream& os, const ConnectionId& connId)
{
    return os << connId.info();
}

