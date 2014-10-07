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
const unsigned short VAL_RESERVEDQOSID = 0;
const int VAL_UNDEF_CEPID = -1;

ConnectionId::ConnectionId() :
    qosId(VAL_RESERVEDQOSID), srcCEPId(VAL_UNDEF_CEPID), dstCEPId(VAL_UNDEF_CEPID)
{
}

unsigned int ConnectionId::getDstCepId() const {
    return dstCEPId;
}

void ConnectionId::setDstCepId(unsigned int destCepId) {
    dstCEPId = destCepId;
}

unsigned short ConnectionId::getQoSId() const {
    return qosId;
}

void ConnectionId::setQoSId(unsigned short qoSId) {
    this->qosId = qoSId;
}

unsigned int ConnectionId::getSrcCepId() const {
    return srcCEPId;
}

void ConnectionId::setSrcCepId(unsigned int srcCepId) {
    srcCEPId = srcCepId;
}

ConnectionId::~ConnectionId() {
    // TODO Auto-generated destructor stub
}

//QosCube* ConnectionId::getQosCube()
//{
//  return qosCube;
//}
//
//void ConnectionId::setQosCube(QosCube* qosCube)
//{
//  this->qosCube = qosCube;
//}

ConnectionId *ConnectionId::dup() const{

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
    return ((qosId == other.qosId) && (dstCEPId == other.dstCEPId)
            && (srcCEPId < other.srcCEPId));
}

