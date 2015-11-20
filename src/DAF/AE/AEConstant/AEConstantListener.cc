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

#include "AEConstantListener.h"
#include "AEConstantMsgs.h"
#include "ModularMonitorSignals.h"

#include <iostream>
#include <fstream>

Define_Module(AEConstantListener);


void AEConstantListener::initialize() {

    this->getParentModule()->subscribe("AEConstantPing-SND", &module);
    this->getParentModule()->subscribe("AEConstantPing-RCV", &module);
    this->getParentModule()->subscribe("AEConstantPong-RCV", &module);
    this->getParentModule()->subscribe("ModularSignal", &module);
}

AEConstantListenerModule::AEConstantListenerModule() {}

void AEConstantListenerModule::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    if(SignalMsg * m = dynamic_cast<SignalMsg*>(obj)) {
           switch (m->type) {
               case 0: record_send(m->qos); break;
               case 1: record_delay(m->qos, m->delay); record_prcv(m->qos); break;
               case 2: record_delay(m->qos, m->delay);record_rtt(m->qos, m->rtt); record_rcv(m->qos); break;
           //    case 3: record_hop_delay(m->qos, m->delay); break;
           }
    } else  if(HopDelayMsg * m = dynamic_cast<HopDelayMsg*>(obj)) {
        record_hop_delay(m->qos, m->t);
    } else  if(HopLossMsg * m = dynamic_cast<HopLossMsg*>(obj)) {
        //cout << "OK" << m->qos << endl;
        record_hop_loss(m->qos);
        //exit(1);
    }
}

void AEConstantListenerModule::record_send(string qos) {
    QoS.insert(qos);
    count_send[qos]++;
}

void AEConstantListenerModule::record_prcv(string qos){
    QoS.insert(qos);
    count_prcv[qos]++;
}

void AEConstantListenerModule::record_rcv(string qos){
    QoS.insert(qos);
    count_rcv[qos]++;
}

void AEConstantListenerModule::record_hop_delay(string qos, simtime_t t) {
    QoS.insert(qos);
    if(max_hop.find(qos) == max_hop.end()) {
        max_hop[qos] = t;
    } else  if(max_hop[qos] < t) {
        max_hop[qos] = t;
    }
}

void AEConstantListenerModule::record_hop_loss(string qos) {
    QoS.insert(qos);
    hop_loss[qos]++;
}


void AEConstantListenerModule::record_delay(string qos, simtime_t t) {
    QoS.insert(qos);
    if(sum_delay.find(qos) == sum_delay.end()) {
        sum_delay[qos] = t;
        max_delay[qos] = t;
    } else {
        sum_delay[qos] += t;
        if(max_delay[qos] < t) {
            max_delay[qos] = t;
        }
    }
}

void AEConstantListenerModule::record_rtt(string qos, simtime_t t){
    QoS.insert(qos);
    if(sum_rtt.find(qos) == sum_rtt.end()) {
        sum_rtt[qos] = t;
        max_rtt[qos] = t;
    } else {
        sum_rtt[qos] += t;
        if(max_rtt[qos] < t) {
            max_rtt[qos] = t;
        }
    }
}


void AEConstantListenerModule::print() {
    for(string qos : QoS) {
        EV << "QoS :: " << qos << endl;
        EV << "\tSend : " << count_send[qos] << endl;
        EV << "\tPartial Received : " << count_prcv[qos] << endl;
        EV << "\tReceived : " << count_rcv[qos] << endl;
        EV << endl;
        simtime_t tt = 1000*sum_delay[qos] / (count_prcv[qos] + count_rcv[qos]);
        EV << "\tAVG Delay : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        tt = 1000 * sum_rtt[qos] / count_rcv[qos];
        EV << "\tAVG RTT : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        tt = 1000*max_delay[qos];
        EV << "\tMAX Delay : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        tt = 1000 * max_rtt[qos];
        EV << "\tMAX RTT : " << dround(tt.dbl(), 3) << " ms" <<  endl;

        if(max_hop.find(qos) != max_hop.end()) {
            tt = 1000*max_hop[qos];
            EV << "\tMAX Hop Delay : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        }
        if(hop_loss.find(qos) != hop_loss.end()) {
            int losst = hop_loss[qos];
            EV << "\tHop Lost : " << losst << " pdus" <<  endl;
        }
        EV << " --------- " <<endl << endl;
    }
}

void AEConstantListenerModule::print(ofstream &out) {
    for(string qos : QoS) {
        out << "QoS :: " << qos << endl;
        out << "\tSend : " << count_send[qos] << endl;
        out << "\tPartial Received : " << count_prcv[qos] << endl;
        out << "\tReceived : " << count_rcv[qos] << endl;
        out << endl;
        simtime_t tt = 1000*sum_delay[qos] / (count_prcv[qos] + count_rcv[qos]);
        out << "\tAVG Delay : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        tt = 1000 * sum_rtt[qos] / count_rcv[qos];
        out << "\tAVG RTT : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        tt = 1000*max_delay[qos];
        out << "\tMAX Delay : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        tt = 1000 * max_rtt[qos];
        out << "\tMAX RTT : " << dround(tt.dbl(), 3) << " ms" <<  endl;

        if(max_hop.find(qos) != max_hop.end()) {
            tt = 1000*max_hop[qos];
            out << "\tMAX Hop Delay : " << dround(tt.dbl(), 3) << " ms" <<  endl;
        }
        if(hop_loss.find(qos) != hop_loss.end()) {
            int losst = hop_loss[qos];
            out << "\tHop Lost : " << losst << " pdus" <<  endl;
        }
        out << " --------- " <<endl << endl;
    }
}

void AEConstantListener::finish() {
    module.print();

    string config = par("configname").stdstringValue();
    string run = par("runname").stdstringValue();

    string filename = "logs/" + config + "." + run +".out";
EV << "outfile "<< filename << endl;

    ofstream out;
    out.open (filename);
    out << "Config : "<< config << endl;
    out << "Rate : "<< run << endl;
    module.print(out);
    out.close();
}


double dround(double a, int ndigits) {

  int    exp_base10 = round(log10(a));
  double man_base10 = a*pow(10.0,-exp_base10);
  double factor     = pow(10.0,-ndigits+1);
  double truncated_man_base10 = man_base10 - fmod(man_base10,factor);
  double rounded_remainder    = fmod(man_base10,factor)/factor;

  rounded_remainder = rounded_remainder > 0.5 ? 1.0*factor : 0.0;

  return (truncated_man_base10 + rounded_remainder)*pow(10.0,exp_base10) ;
}

