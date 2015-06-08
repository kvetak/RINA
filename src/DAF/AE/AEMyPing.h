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

#ifndef __RINA_AEMYPING_H_
#define __RINA_AEMYPING_H_

//Standard library
#include <omnetpp.h>
//RINASim library
#include "AEPing.h"

struct timestamps_t {
    simtime_t t1;
    simtime_t t2;
    simtime_t t3;
};

class AEMyPing : public AEPing
{


  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    virtual void onStart();
    virtual void onPing();
    virtual void onStop();

    virtual void processMRead(CDAPMessage* msg);
    virtual void processMReadR(CDAPMessage* msg);
};

#endif
