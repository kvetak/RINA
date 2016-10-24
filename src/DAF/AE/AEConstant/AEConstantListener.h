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

#ifndef __RINA_AEConstantListener_H_
#define __RINA_AEConstantListener_H_

//Standard libraries
#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include "AEConstantMsgs.h"

#include <set>
#include <map>


using namespace std;

class AEConstantListenerModule : public cListener {
  public:
    AEConstantListenerModule();
    void print();
    void print(ofstream &out);
    using cListener::receiveSignal;
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);

  private:
    void record_send(string qos);
    void record_prcv(string qos);
    void record_rcv(string qos);

    void record_hop_delay(string qos, simtime_t t);
    void record_hop_loss(string qos);

    void record_delay(string qos, simtime_t t);
    void record_rtt(string qos, simtime_t t);

    set<string> QoS;
    map<string, long> count_send, count_prcv, count_rcv, hop_loss;
    map<string, simtime_t> sum_delay, sum_rtt, max_delay, max_rtt, max_hop;


};

class AEConstantListener : public cSimpleModule {
  protected:
    virtual void initialize();
    virtual void finish();
  private:
    AEConstantListenerModule module;
};


double dround(double a, int ndigits);

#endif
