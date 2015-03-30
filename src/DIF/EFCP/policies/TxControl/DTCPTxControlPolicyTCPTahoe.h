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
/**
 * @file DTCPTxControlPolicyTCPTahoe.h
 * @author
 * @date Jan 9, 2015
 * @brief
 * @detail
 */
#ifndef DTCPTXCONTROLPOLICYTCPTAHOE_H_
#define DTCPTXCONTROLPOLICYTCPTAHOE_H_

#include <omnetpp.h>

#include "DTCPTxControlPolicyBase.h"
#include "DTPState.h"
#include "DTCPState.h"

#define MAX_SSTHRESH    1000000000      ///< slow start threshold
#define RST_WND         1               ///< restart window
#define INL_WND         3               ///< restart window         - 10 for Google's suggestion!
#define SMSS            1500            ///< sender maximum segment size

//state
#define STATE_STARTING_SLOW_START       0           ///< starting slow start
#define STATE_SLOW_START                1           ///< slow start
#define STATE_CNG_AVOID                 2           ///< congestion avoidance

class DTCPTxControlPolicyTCPTahoe : public DTCPTxControlPolicyBase {
public:
    float snd_cwnd;            ///< congestion window
    float ssthresh;            ///< slow start threshold

    uint32 state;
    uint32 rxSent;
    uint32 ackRcvd;

    DTCPTxControlPolicyTCPTahoe();
    virtual ~DTCPTxControlPolicyTCPTahoe();

    virtual bool run(DTPState* dtpState, DTCPState* dtcpState);
protected:
    //Statistic signals
    simsignal_t sigStatTCPTahoeCWND;
    virtual void initialize(int step);
};

#endif /* DTCPTXCONTROLPOLICYTCPTAHOE_H_ */
