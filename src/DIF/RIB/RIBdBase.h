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

#ifndef RIBDBASE_H_
#define RIBDBASE_H_

//Standard libraries
#include <omnetpp.h>

class RIBdBase : public cSimpleModule {
  public:
    RIBdBase();
    virtual ~RIBdBase();

    virtual void sendCreateRequestFlow(cObject* obj) = 0;
    virtual void receiveData(cObject* obj) = 0;

  protected:
    //SimpleModule overloads
    virtual void initialize() = 0;
    virtual void handleMessage(cMessage *msg) = 0;
};

#endif /* RIBDBASE_H_ */
