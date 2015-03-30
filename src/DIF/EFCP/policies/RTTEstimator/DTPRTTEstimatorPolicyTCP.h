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

#ifndef DTPRTTESTIMATORPOLICYTCP_H_
#define DTPRTTESTIMATORPOLICYTCP_H_

#include <DTPRTTEstimatorPolicyBase.h>

#include "DTPState.h"
#include "DTCPState.h"
#include "ControlPDU_m.h"
#include "math.h"

#define STATE_FIRST     1
#define STATE_NEXT      2

class DTPRTTEstimatorPolicyTCP : public DTPRTTEstimatorPolicyBase {
public:
    int state;
    double SRTT;
    double RTTVar;
    double RTO;
    double k;
    double G;

    DTPRTTEstimatorPolicyTCP();
    virtual ~DTPRTTEstimatorPolicyTCP();

    virtual bool run(DTPState* dtpState, DTCPState* dtcpState);
};

#endif /* DTPRTTESTIMATORPOLICYTCP_H_ */
