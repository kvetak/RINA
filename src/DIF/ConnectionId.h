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
/*
 *
 */
class ConnectionId: public cObject {

private:
    int qoSId;
    int destCEPId;
    int srcCEPId;

public:
    ConnectionId();
    virtual ~ConnectionId();
    int getDestCepId() const;
    void setDestCepId(int destCepId);
    int getQoSId() const;
    void setQoSId(int qoSId);
    int getSrcCepId() const;
    void setSrcCepId(int srcCepId);

    virtual ConnectionId *dup() const;

};

#endif /* CONNECTIONID_H_ */
