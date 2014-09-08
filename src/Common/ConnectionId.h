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

#ifndef CONNECTIONID_H_
#define CONNECTIONID_H_

#include <cobject.h>
#include <string>
#include "QosCube.h"

/*
 *
 */
class ConnectionId: public cObject {

private:
    unsigned int qoSId;
    unsigned int destCEPId;
    unsigned int srcCEPId;


public:
    ConnectionId();
    virtual ~ConnectionId();
    unsigned int getDestCepId() const;
    void setDestCepId(unsigned int destCepId);
    unsigned int getQoSId() const;
    void setQoSId(unsigned int qoSId);
    unsigned int getSrcCepId() const;
    void setSrcCepId(unsigned int srcCepId);


    bool operator<(const ConnectionId other) const;
    bool operator==(const ConnectionId other) const;

    virtual ConnectionId *dup() const;
//    QosCube* getQosCube();
//    void setQosCube(QosCube* qosCube);
};

#endif /* CONNECTIONID_H_ */
