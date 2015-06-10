//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

#include "ConnectionId.h"

//Consts
const int VAL_UNDEF_CEPID = -1;

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

