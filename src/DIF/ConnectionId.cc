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

ConnectionId::ConnectionId() {
    // TODO Auto-generated constructor stub

}

unsigned int ConnectionId::getDestCepId() const {
    return destCEPId;
}

void ConnectionId::setDestCepId(unsigned int destCepId) {
    destCEPId = destCepId;
}

unsigned int ConnectionId::getQoSId() const {
    return qoSId;
}

void ConnectionId::setQoSId(unsigned int qoSId) {
    this->qoSId = qoSId;
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

QosCube* ConnectionId::getQosCube()
{
  return qosCube;
}

void ConnectionId::setQosCube(QosCube* qosCube)
{
  this->qosCube = qosCube;
}

ConnectionId *ConnectionId::dup() const{

  ConnectionId* connId = new ConnectionId();
  connId->setDestCepId(this->destCEPId);
  connId->setSrcCepId(this->srcCEPId);
  connId->setQoSId(this->qoSId);
  connId->setQosCube(this->qosCube);

  return connId;

}



