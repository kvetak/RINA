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

#include "InjListener.h"
#include "./SigMessages.h"

Define_Module(InjListener);

void InjListener::initialize() {
    this->getParentModule()->subscribe("InjSignal", this);
}

void InjListener::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    if(SigFlow * s = dynamic_cast<SigFlow*>(obj) ) {
        long & flows = SDQ_Flows[s->src][s->dst][s->qos];
        double & rate = SDQ_Rate[s->src][s->dst][s->qos];
        long & Gflows = SDQ_Flows[s->src][s->dst][""];
        double & Grate = SDQ_Rate[s->src][s->dst][""];

        if(s->on) {
            flows++;
            rate += s->rate;
            //cout << simTime() << " | Added flow "<< s->src << "->"<<s->dst << " ["<< s->flowID <<  "] ("<<s->qos<<")" << " | #Flows "<< flows << " / Rate " << rate << endl;
            Gflows++;
            Grate += s->rate;
            //cout << " + "<< s->src << "->"<<s->dst << " | #Flows "<< Gflows << " / Rate " << Grate << endl;
        } else  {
            flows--;
            rate -= s->rate;
            //cout << simTime() << " | Removed flow "<< s->src << "->"<<s->dst << " ["<< s->flowID <<  "] ("<<s->qos<<")" << " | #Flows "<< flows << " / Rate " << rate << endl;
            Gflows--;
            Grate -= s->rate;
            //cout << " - "<< s->src << "->"<<s->dst << " | #Flows "<< Gflows << " / Rate " << Grate << endl;
        }
        return;
    }
    if(SigPDU * s = dynamic_cast<SigPDU*>(obj) ) {
        if(s->status == 0) {
            SDQ_PDUSsend[s->src][s->dst][s->qos]++;
            SDQ_PDUSsend[s->src][s->dst][""]++;
            SDQ_DATAsend[s->src][s->dst][s->qos] += s->data;
            SDQ_DATAsend[s->src][s->dst][""] += s->data;
        } else if(s->status == 1) {
            SDQ_PDUSreceived[s->src][s->dst][s->qos]++;
            SDQ_PDUSreceived[s->src][s->dst][""]++;
            SDQ_Delay[s->src][s->dst][s->qos] += s->delay;
            SDQ_Delay[s->src][s->dst][""] += s->delay;
            SDQ_DATAreceived[s->src][s->dst][s->qos] += s->data;
            SDQ_DATAreceived[s->src][s->dst][""] += s->data;

            if(s->delay > SDQ_MAXDelay[s->src][s->dst][s->qos]) {
                SDQ_MAXDelay[s->src][s->dst][s->qos] = s->delay;
            }
            if(s->delay > SDQ_MAXDelay[s->src][s->dst][""]) {
                SDQ_MAXDelay[s->src][s->dst][""] = s->delay;
            }
        }
        return;
    }
}

void InjListener::finish(){
    for(auto S_DQ : SDQ_PDUSsend) {
        const string & src = S_DQ.first;
        for(auto D_Q : S_DQ.second) {
            const string & dst = D_Q.first;

            cout << src <<"->"<< dst <<endl;
            cout <<" PDUs :: Send " << SDQ_PDUSsend[src][dst][""]
                 << " Received "<< SDQ_PDUSreceived[src][dst][""]
                 << " Dropped "<< (SDQ_PDUSsend[src][dst][""] - SDQ_PDUSreceived[src][dst][""]) << endl;
            cout <<" DATA :: Send " << SDQ_DATAsend[src][dst][""]
                 << " Received "<< SDQ_DATAreceived[src][dst][""]
                 << " Dropped "<< (SDQ_DATAsend[src][dst][""] - SDQ_DATAreceived[src][dst][""]) << endl;
            cout << "\tAVG Delay "<< (SDQ_Delay[src][dst][""]/SDQ_PDUSreceived[src][dst][""]) <<endl;
            cout << "\tMAX Delay "<< SDQ_MAXDelay[src][dst][""] <<endl;
            for(auto Q : D_Q.second) {
                const string & qos = Q.first;
                if(qos == "") { continue; }

                cout << src <<"->"<< dst << " [" << qos<< "]" <<endl;
                cout <<" PDUs :: Send " << SDQ_PDUSsend[src][dst][qos]
                     << " Received "<< SDQ_PDUSreceived[src][dst][qos]
                     << " Dropped "<< (SDQ_PDUSsend[src][dst][qos] - SDQ_PDUSreceived[src][dst][qos]) << endl;
                cout <<" DATA :: Send " << SDQ_DATAsend[src][dst][qos]
                     << " Received "<< SDQ_DATAreceived[src][dst][qos]
                     << " Dropped "<< (SDQ_DATAsend[src][dst][qos] - SDQ_DATAreceived[src][dst][qos]) << endl;
                cout << "\tAVG Delay "<< (SDQ_Delay[src][dst][qos]/SDQ_PDUSreceived[src][dst][qos]) <<endl;
                cout << "\tMAX Delay "<< SDQ_MAXDelay[src][dst][qos] <<endl;

            }
        }
    }
}
