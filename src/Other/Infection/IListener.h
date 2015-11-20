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

#ifndef __RINA_IListener_H_
#define __RINA_IListener_H_

//Standard libraries
#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include "AEConstantMsgs.h"

#include <set>
#include <map>


using namespace std;

class IListenerModule : public cListener {
  public:
    set<string> QoS;
    map<string, double> QoSDelay, QoSJitter;


    IListenerModule();
    void print();
    void print(ofstream &out);

    void initialize();
    virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);

  private:
    void record_send(string qos);
    void record_loss(string qos);
    map<string, long> sent, lost;

    void record_hop_delay(string qos, simtime_t t);
    map<string, long> hop_delay_count;
    map<string, simtime_t> sum_hop_delay, max_hop_delay;

    void record_delay(string qos, simtime_t t);
    map<string, long> delay_count;
    map<string, simtime_t> sum_delay, max_delay;
    map<string, int > delay_degraded;
    map<string, map<int, int> > delay_degradation;

    bool record_unnorder(string qos, int cepID, unsigned int seqN);
    map<int, unsigned int> lastRcv;
    map<string, int> unorderedRCV;


    void record_jitter(string qos, int cepID, simtime_t delay);
    map<string, long> jitter_count;
    map<string, simtime_t> sum_jitter, max_jitter;
    map<int, simtime_t> last_time;
    map<string, map<int, int> > jitter_degradation;


};

class IListener : public cSimpleModule {
  protected:
    virtual void initialize();
    virtual void finish();
  private:
    IListenerModule module;
};


double Idround(double a, int ndigits);

#endif
