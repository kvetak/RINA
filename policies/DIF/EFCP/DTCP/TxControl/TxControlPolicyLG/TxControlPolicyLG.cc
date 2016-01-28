// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
/**
 * @file TxControlPolicyLG.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date May 3, 2015
 * @brief This is an example policy class implementing LG Tx Control
 * @detail
 */

#include "TxControlPolicyLG.h"

const char * Tx_LG_RATE = "Tx_LG_RATE";
const char * Tx_FLIGHT_SIZE = "Tx_LG_FLIGHT_SIZE";
const char * USED_LOAD = "USED_LOAD";

Register_Class(TxControlPolicyLG);

TxControlPolicyLG::TxControlPolicyLG()
{
    rate = INITIAL_RATE;
    alpha = ALPHA;
    flightSize = 0;
    lastUpdate = 0;

    totalPackets = 0;
    ecnMarkedPackets = 0;
    usedLoad = 0;
}

TxControlPolicyLG::~TxControlPolicyLG()
{
}

void TxControlPolicyLG::initialize() {
    sigStatRate = registerSignal(Tx_LG_RATE);
    sigStatFlightSize = registerSignal(Tx_FLIGHT_SIZE);
    sigStatUsedLoad = registerSignal(USED_LOAD);

    rttEstimatorPolicyLG = getRINAModule<RTTEstimatorPolicyLG*>(this, 1, {"rttEstimatorPolicy"});
}

void TxControlPolicyLG::updateRate(double load, double acked, double lastECN)
{
    if(load > 0)
        alpha = ALPHA;

    totalPackets++;
    ecnMarkedPackets += lastECN;

    simtime_t now = simTime();
    if(now - lastUpdate >= rttEstimatorPolicyLG->getMinRTT()) {
        if(usedLoad == 0 && load > 0)
            usedLoad = 1;
        else
            usedLoad = (ecnMarkedPackets / totalPackets) * 0.04 + 0.96 * usedLoad;

        load = usedLoad;

        rate = rate * alpha * (1 - rate - load) + rate;
        lastUpdate = now;
        emit(sigStatUsedLoad, load);

        totalPackets = 0;
        ecnMarkedPackets = 0;
    }

    flightSize -= acked;

    emit(sigStatRate, rate);
    emit(sigStatFlightSize, flightSize);
}

double TxControlPolicyLG::getActualRate(DTPState* dtpState)
{
    return flightSize * SEGMENT_SIZE * 8 / rttEstimatorPolicyLG->getMinRTT();//dtpState->getRtt();//0.045; //dtpState->getRtt();   // segment size
}

double TxControlPolicyLG::getRate()
{
    return rate * BANDWIDTH;               // bandwidth
}

bool TxControlPolicyLG::run(DTPState* dtpState, DTCPState* dtcpState)
{
    Enter_Method("TxControlPolicyLG");

    if(getActualRate(dtpState) < getRate()) {
        double addRate = (getRate() - getActualRate(dtpState));
        sendCredit = addRate * rttEstimatorPolicyLG->getMinRTT() / (SEGMENT_SIZE * 8);
        if(sendCredit > 0 && sendCredit < 1 && flightSize == 0)
            sendCredit = 1;

        // -------------  adding packets to send queue
        std::vector<DataTransferPDU*>::iterator it;
        PDUQ_t* pduQ = NULL;
        int sentNo = 1;

        for(int i = 1; i <= 2; i++) {
            if (dtcpState->getClosedWinQueLen() > 0) {
                pduQ = dtcpState->getClosedWindowQ();
            } else
                pduQ = dtpState->getGeneratedPDUQ();

            for (it = pduQ->begin(); it != pduQ->end() && (*it)->getSeqNum() <= dtcpState->getSndRightWinEdge() && sentNo <= sendCredit; sentNo++) {
                dtpState->pushBackToPostablePDUQ((*it));
                flightSize++;
                emit(sigStatFlightSize, flightSize);
                it = pduQ->erase(it);
            }
        }
    }

    dtcpState->setClosedWindow(true);

    return false;
}
