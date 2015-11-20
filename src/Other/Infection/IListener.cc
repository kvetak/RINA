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

#include "IListener.h"
#include "AEConstantMsgs.h"
#include "ModularMonitorSignals.h"
#include "InfectionSignals.h"

#include <iostream>
#include <fstream>

Define_Module(IListener);


void IListener::initialize() {
    this->getParentModule()->subscribe("ModularSignal", &module);
    this->getParentModule()->subscribe("InfectionSignal", &module);

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()){
        Xml = par("data").xmlValue();
    } else { error("data parameter not initialized!"); }


    cXMLElementList QoSs = Xml->getChildrenByTagName("qos");
    for(cXMLElement * n : QoSs) {
        if (!n->getAttribute("name")) {
            EV << "Error parsing Infected QoS. Its name is missing!" << endl;
            continue;
        }
        if (!n->getAttribute("delay")) {
            EV << "Error parsing Infected QoS. Its delay is missing!" << endl;
            continue;
        }
        if (!n->getAttribute("jitter")) {
            EV << "Error parsing Infected QoS. Its jitter is missing!" << endl;
            continue;
        }

        string name = n->getAttribute("name");
        double delay = atof(n->getAttribute("delay"))/1000.0;
        double jitter = atof(n->getAttribute("jitter"))/1000.0;
        if(name == "") {
            EV << "Error parsing Infected QoS. Its name is empty!" << endl;
            continue;
        }
        if(delay <= 0) {
            EV << "Error parsing Infected QoS. Its delay <=0!" << endl;
            continue;
        }
        if(jitter <= 0) {
            EV << "Error parsing Infected QoS. Its jitter <=0!" << endl;
            continue;
        }

        module.QoS.insert(name);
        module.QoSDelay[name] = delay;
        module.QoSJitter[name] = jitter;

    }

}

IListenerModule::IListenerModule() {}

void IListenerModule::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    if(HopDelayMsg * m = dynamic_cast<HopDelayMsg*>(obj)) {
        //Signal <QoS, delay> each HOP
        record_hop_delay(m->qos, m->t);
    } else if(HopLossMsg * m = dynamic_cast<HopLossMsg*>(obj) ) {
        //Signal <QoS> each HOP if drop
        record_loss(m->qos);
    } else if(SendInfMsg * m = dynamic_cast<SendInfMsg*>(obj) ) {
        //Signal <QoS> at Send
        record_send(m->qos);
    } else if(RecvInfMsg * m = dynamic_cast<RecvInfMsg*>(obj)) {
         //Signal <QoS, delay, cepID, seqN> at Rcv
        record_delay(m->qos, m->delay);
        /*
        if(record_unnorder(m->qos, m->cepID, m->seqN)) {
            record_jitter(m->qos, m->cepID, m->delay);
        }
        */
    }
}

void IListenerModule::record_send(string qos) { sent[qos]++; }
void IListenerModule::record_loss(string qos) { lost[qos]++; }

void IListenerModule::record_hop_delay(string qos, simtime_t t) {
    hop_delay_count[qos]++;
    sum_hop_delay[qos] += t;
    if(max_hop_delay[qos] < t) { max_hop_delay[qos] = t; }
}

void IListenerModule::record_delay(string qos, simtime_t t) {
    delay_count[qos]++;
    sum_delay[qos] += t;
    if(max_delay[qos] < t) { max_delay[qos] = t; }

    //Count over X% jitter degradation
    double maxDelay = QoSDelay[qos];
    if(maxDelay > 0) {
        double degradation = t.dbl()/maxDelay;
        int o100deg = (int) ceil(degradation*10);
        if(o100deg > 10) {
            delay_degraded[qos]++;
            delay_degradation[qos][o100deg*10]++;
//            cout << jitter <<  " -> "<< o100deg<< endl;
        }

    }
}


bool IListenerModule::record_unnorder(string qos, int cepID, unsigned int seqN) {
    unsigned int prev = lastRcv[cepID];
    if(prev>seqN) {
        unorderedRCV[qos]++;
        return false;
    }
    lastRcv[cepID] = seqN;
    if(prev > 1) {
        return true;
    } else {
        return false;
    }
}

void IListenerModule::record_jitter(string qos, int cepID, simtime_t delay) {
    jitter_count[qos]++;
    simtime_t jitter = delay-last_time[cepID];
    if(jitter<0){jitter =- jitter; }
    last_time[cepID] = delay;


    sum_jitter[qos] += jitter;
    if(max_jitter[qos] < jitter) { max_jitter[qos] = jitter; }

    //Count over X% jitter degradation
    double maxJitter = QoSJitter[qos];
    if(maxJitter > 0) {
        double degradation = jitter.dbl()/maxJitter;
        int o100deg = (int) ceil(degradation*100);
        if(o100deg > 100) {
            jitter_degradation[qos][o100deg]++;
//            cout << jitter <<  " -> "<< o100deg<< endl;
        }

    }
}


void IListenerModule::print() {
    for(string qos : QoS) {
        EV << "QoS :: " << qos << endl;

        EV << "\tSent/Lost : "
                << sent[qos] <<"/"<<  lost[qos]
                << "  -  ("<< Idround(100.0*(double)lost[qos]/(double)sent[qos], 2)<<"%)"
                << endl;

        EV << "\tHop Delay : "
                << Idround(1000*sum_hop_delay[qos].dbl()/(double)hop_delay_count[qos], 2) << "ms AVG  /  "
                << Idround(1000*max_hop_delay[qos].dbl(), 2) << "ms MAX"
                << endl;



        EV << "\tDelay : "

                << Idround(1000*sum_delay[qos].dbl()/(double)delay_count[qos], 2) << "ms AVG  /  "
                << Idround(1000*max_delay[qos].dbl(), 2) << "ms MAX"
                << endl;
        if(delay_degradation[qos].empty()) {
            EV << "\t\tDegraded : 0%" << endl;
        } else {
            EV << "\t\tDegraded : " << Idround((double)delay_degraded[qos]/(double)delay_count[qos], 3) << "%" << endl;
            for(const auto & deg : delay_degradation[qos]) {
                EV << "\t\t\t "<< deg.first <<"% deg : "
                        << Idround(deg.second/(double)delay_count[qos], 3) << "% msg  "
                        <<endl;
            }
        }

/*
        EV << "\tJitter : "
                << Idround(1000*sum_jitter[qos].dbl()/(double)jitter_count[qos], 2) << "ms AVG  /  "
                << Idround(1000*max_jitter[qos].dbl(), 2) << "ms MAX"
                << endl;
       /*
        if(jitter_degradation[qos].empty()) {
            EV << "\t\tDegraded : 0%" << endl;
        } else {
            EV << "\t\tDegraded : "<< endl;
            for(const auto & deg : jitter_degradation[qos]) {
                EV << "\t\t\t "<< deg.first <<"% deg : "
                        << Idround(deg.second/(double)jitter_count[qos], 3) << "% msg  "
                        <<endl;
            }
        }
        */
        /*
        EV << "\tUnnordered : "
                << Idround(100.0*(double)unorderedRCV[qos]/(double)delay_count[qos], 2)<<"%"
                << endl;
*/
        EV << " --------- " <<endl << endl;
    }
}

void IListenerModule::print(ofstream &out) {
    for(string qos : QoS) {
        out << "QoS :: " << qos << endl;

        out << "\tSent/Lost : "
                << sent[qos] <<"/"<<  lost[qos]
                << "  -  ("<< Idround(100.0*(double)lost[qos]/(double)sent[qos], 2)<<"%)"
                << endl;

        out << "\tHop Delay : "
                << Idround(1000*sum_hop_delay[qos].dbl()/(double)hop_delay_count[qos], 2) << "ms AVG  /  "
                << Idround(1000*max_hop_delay[qos].dbl(), 2) << "ms MAX"
                << endl;

        out << "\tDelay : "
                << Idround(1000*sum_delay[qos].dbl()/(double)delay_count[qos], 2) << "ms AVG  /  "
                << Idround(1000*max_delay[qos].dbl(), 2) << "ms MAX"
                << endl;
        if(delay_degradation[qos].empty()) {
            out << "\t\tDegraded : 0%" << endl;
        } else {
            out << "\t\tDegraded : " << Idround((double)delay_degraded[qos]/(double)delay_count[qos], 3) << "%" << endl;
            for(const auto & deg : delay_degradation[qos]) {
                out << "\t\t\t "<< deg.first <<"% deg : "
                        << Idround(deg.second/(double)delay_count[qos], 3) << "% msg  "
                        <<endl;
            }
        }

/*
        out << "\tJitter : "
                << Idround(1000*sum_jitter[qos].dbl()/(double)jitter_count[qos], 2) << "ms AVG  /  "
                << Idround(1000*max_jitter[qos].dbl(), 2) << "ms MAX"
                << endl;
        if(jitter_degradation[qos].empty()) {
            out << "\t\tDegraded : 0%" << endl;
        } else {
            out << "\t\tDegraded : "<< endl;
            for(const auto & deg : jitter_degradation[qos]) {
                out << "\t\t\t "<< deg.first <<"% deg : "
                        << Idround(deg.second/(double)jitter_count[qos], 3) << "% msg  "
                        <<endl;
            }
        }
        out << "\tUnnordered : "
                << Idround(100.0*(double)unorderedRCV[qos]/(double)delay_count[qos], 2)<<"%"
                << endl;
*/
        out << " --------- " <<endl << endl;
    }
}

void IListener::finish() {
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


double Idround(double a, int ndigits) {

  int    exp_base10 = round(log10(a));
  double man_base10 = a*pow(10.0,-exp_base10);
  double factor     = pow(10.0,-ndigits+1);
  double truncated_man_base10 = man_base10 - fmod(man_base10,factor);
  double rounded_remainder    = fmod(man_base10,factor)/factor;

  rounded_remainder = rounded_remainder > 0.5 ? 1.0*factor : 0.0;

  return (truncated_man_base10 + rounded_remainder)*pow(10.0,exp_base10) ;
}

