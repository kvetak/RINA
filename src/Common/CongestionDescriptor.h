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

#ifndef CONGESTIONDESCRIPTOR_H_
#define CONGESTIONDESCRIPTOR_H_

#include "ConnectionId.h"

class CongestionDescriptor : public cObject {
  public:
    CongestionDescriptor();
    CongestionDescriptor(int srcCepId, int dstCepId, unsigned short qosId);
    virtual ~CongestionDescriptor();

    virtual CongestionDescriptor* dup() const;

    ConnectionId& getConnectionId();
    void setConnectionId(const ConnectionId& conId);

    std::string getCongesDescrName() const;

  protected:
    ConnectionId ConId;
};

#endif /* CONGESTIONDESCRIPTOR_H_ */
