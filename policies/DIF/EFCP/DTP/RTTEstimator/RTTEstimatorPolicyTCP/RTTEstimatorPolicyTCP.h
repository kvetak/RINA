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

#ifndef RTTESTIMATORPOLICYTCP_H_
#define RTTESTIMATORPOLICYTCP_H_

#include "DIF/EFCP/DTP/RTTEstimator/RTTEstimatorPolicyBase.h"

#include "DIF/EFCP/DTP/DTPState.h"
#include "DIF/EFCP/DTCP/DTCPState.h"
#include "DIF/EFCP/DTCP/ControlPDU_m.h"
#include "math.h"

#define STATE_FIRST     1
#define STATE_NEXT      2

class RTTEstimatorPolicyTCP : public RTTEstimatorPolicyBase {
public:
    double RTO;

    simsignal_t sigStatTCPRTO;


    RTTEstimatorPolicyTCP();
    virtual ~RTTEstimatorPolicyTCP();

    virtual bool run(DTPState* dtpState, DTCPState* dtcpState);
private:
    int state;
    double SRTT;
    double RTTVar;
    double k;
    double G;

};

#endif /* RTTESTIMATORPOLICYTCP_H_ */
