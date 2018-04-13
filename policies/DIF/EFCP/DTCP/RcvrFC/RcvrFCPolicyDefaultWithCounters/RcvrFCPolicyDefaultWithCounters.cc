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
 * @file RcvrFCPolicyDefaultWithCounters.cc
 * @author Kleber Leal (kal2@cin.ufpe.br)
 * @date Jun 19, 2017
 * @brief This policy registers the goodput and number os packets received
 * @detail
 */

#include "DIF/EFCP/DTCP/RcvrFC/RcvrFCPolicyDefaultWithCounters/RcvrFCPolicyDefaultWithCounters.h"
Register_Class(RcvrFCPolicyDefaultWithCounters);

RcvrFCPolicyDefaultWithCounters::RcvrFCPolicyDefaultWithCounters() {
    // TODO Auto-generated constructor stub

}

RcvrFCPolicyDefaultWithCounters::~RcvrFCPolicyDefaultWithCounters() {
    // TODO Auto-generated destructor stub
}

void RcvrFCPolicyDefaultWithCounters::initialize() {
    sigStatPktRcvd = registerSignal("packets_received");
    sigStatGoodput = registerSignal("goodput");
    pktRcvd = 0;
    lastPktRcvd = 0;
    m1 = new cMessage("measure");
    scheduleAt(simTime(), m1);
}

bool RcvrFCPolicyDefaultWithCounters::run(DTPState* dtpState,DTCPState* dtcpState) {
    Enter_Method("RcvrFCPolicyDefaultWithCounters");

    pktRcvd++;

    emit(sigStatPktRcvd, pktRcvd);

    return true;
}

void RcvrFCPolicyDefaultWithCounters::handleMessage(cMessage* msg) {
    if(msg->isSelfMessage()){
        if(!strcmp(msg->getName(), "measure")){
            emit(sigStatGoodput, pktRcvd - lastPktRcvd);
            lastPktRcvd = pktRcvd;
            m1 = new cMessage("measure");
            scheduleAt(simTime()+1, m1);
        }
        delete(msg);
    }
}
