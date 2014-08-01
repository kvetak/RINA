//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
//  
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//
/*
 * DTCP.h
 *
 *  Created on: Apr 17, 2014
 *      Author: Marcel Marek
 */

#ifndef DTCP_H_
#define DTCP_H_

#include <csimplemodule.h>

#include "FlowControl.h"
#include "RXControl.h"
#include "DTCPState.h"

#include "ControlPDU_m.h"
#include "DTCPTimers_m.h"

class DTCP: public cSimpleModule {
    friend class DTP;
  private:
    DTCPState *dtcpState;
    FlowControl* flowControl;
    RXControl* rxControl;

    /*Timers*/
    WindowTimer* windowTimer;




    void schedule(DTCPTimers *timer);
    void resetWindowTimer();

    void sendAckPDU();

public:


    unsigned int getFlowControlRightWinEdge();
    DTCP();
    virtual ~DTCP();

    void handleWindowTimer(WindowTimer* timer);

protected:
    virtual void handleMessage(cMessage *msg);
};

#endif /* DTCP_H_ */
