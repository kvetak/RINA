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

Define_Module(IListener::IListener);

namespace IListener {

    modQoSInfo::modQoSInfo() :
            maxDel(0.0),
            countDel(0),
            sumDel(0),
            rcv(0),
            drop(0) {}

    void modQoSInfo::RcvMsg() {
        rcv++;
    }

    void modQoSInfo::DropMsg() {
        drop++;
    }

    void modQoSInfo::ServeMsg(int t) {
        countDel++;
        if(maxDel < t) { maxDel = t; }
        sumDel += t;
        distDel[t]++;
    }

    flowId::flowId(string _src, string _dst, int _srcCepId, string _qos) :
            src(_src),
            dst(_dst),
            srcCepId(_srcCepId),
            qos(_qos) {}

    bool flowId::operator<( const flowId & o ) const {
        if(src != o.src) { return src < o.src; }
        if(dst != o.dst) { return dst < o.dst; }
        if(qos != o.qos) { return qos < o.qos; }
        return srcCepId < o.srcCepId;
    }

    flowInfo::flowInfo() :
            minDel(SIMTIME_MAX),
            maxDel(0.0),
            countDel(0),
            sumDel(0.0),
            minPST(9999),
            maxPST(0),
            countPST(0),
            sumPST(0),
            minJitter(SIMTIME_MAX),
            maxJitter(0.0),
            countJit(0),
            sumJit(0.0),
            snd(0),
            rcv(0),
            lastSec(0),
            consDrop(0) {}

    void flowInfo::SendMsg() {
        snd++;
    }

    void flowInfo::RcvMsg(int nSec, simtime_t h_delay, simtime_t p_delay, int pst_delay) {
        if(lastSec > nSec) {
            cerr << "Messages should not arrive unordered";

            exit(0);
        }
        rcv++;

        simtime_t delay = h_delay + p_delay;

        if(minDel > delay) { minDel = delay; }
        if(maxDel < delay) { maxDel = delay; }
        sumDel += delay;
        distDel[toDistIndex(delay)]++;
        countDel++;



        if(minPST > pst_delay) { minPST = pst_delay; }
        if(maxPST < pst_delay) { maxPST = pst_delay; }
        sumPST += pst_delay;
        distPST[pst_delay]++;
        countPST++;

        // Case All OK
        if(lastSec+1 == nSec) {
            if(lastSec > 0) {
                consDrop = 0;

                simtime_t jitter = lastDelay - delay;
                if(jitter < 0) { jitter = -jitter; }

                if(minJitter > jitter) { minJitter = jitter; }
                if(maxJitter < jitter) { maxJitter = jitter; }
                sumJit += jitter;
                countJit++;
                distJit[toDistIndex(jitter)]++;
            }
        } else {
            consDrop++;
            countConsDrop[consDrop]++;
        }



        lastSec = nSec;
        lastDelay = delay;
    }

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


            h_delayV = par("mtu").longValue()/1500.0;
            module.h_delayV = h_delayV;
        }

    }

    void IListenerModule::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
        if(HopDelayMsg * m = dynamic_cast<HopDelayMsg*>(obj)) {
            modulesQoSInfo[m->qos][m->module].ServeMsg(m->t);
            hopQoSInfo[m->qos].ServeMsg(m->t);
            modulesInfo[m->module].ServeMsg(m->t);
        } else if(HopRcvMsg * m = dynamic_cast<HopRcvMsg*>(obj) ) {
            modulesQoSInfo[m->qos][m->module].RcvMsg();
            hopQoSInfo[m->qos].RcvMsg();
            modulesInfo[m->module].RcvMsg();
        } else if(HopLossMsg * m = dynamic_cast<HopLossMsg*>(obj) ) {
            modulesQoSInfo[m->qos][m->module].DropMsg();
            hopQoSInfo[m->qos].DropMsg();
            modulesInfo[m->module].DropMsg();
        } else if(SendInfMsg * m = dynamic_cast<SendInfMsg*>(obj) ) {
            QoSsend[m->qos]++;
            flowId fId(m->src, m->dst, m->srcCepId, m->qos);
            QoSFlowInfo[m->qos][fId].SendMsg();
        } else if(RecvInfMsg * m = dynamic_cast<RecvInfMsg*>(obj)) {
            flowId fId(m->src, m->dst, m->src_cepID, m->qos);
            QoSFlowInfo[m->qos][fId].RcvMsg(m->seqN, m->h_delay*h_delayV, m->p_delay, m->pst_delay);
        }
    }

    void IListenerModule::print(ofstream &out) {
        out << "Processed per hop :: " << endl;
        for(string qos : QoS) {
            out << "\tQoS :: " << qos << endl;
            modQoSInfo & mI = hopQoSInfo[qos];
            out << "\t\tProcessed/Dropped : "
                    << mI.rcv <<"/"<<  mI.drop
                    << "  -  ("<< Idround(100.0*mI.drop/(double)mI.rcv, 4)<<"%)"
                    << endl;

            out << "\t\tHop Delay : "
                    << Idround(mI.sumDel/(double)mI.countDel, 4) << "pk AVG  /  "
                    << mI.maxDel << "pk MAX"
                    << endl;
        }
    }

    void IListenerModule::printHopInfo(ofstream &out) {
        for(string qos : QoS) {
            out << "QoS," << qos << endl;
            out << "RCV, DROP, DROP %,,AVG PK W, MAX PK W,,DIST PK WT:";
            for(int i = 0; i<4000;) {
                out << "," << i;
                if(i < 10) { i += 1; }
                else if(i < 100) { i += 10; }
                else { i += 100; }
            }
            out << endl;
            for(auto & mI : modulesQoSInfo[qos]) {
                out << mI.second.rcv <<
                        "," << mI.second.drop <<
                        "," << Idround(100.0*mI.second.drop/(double)mI.second.rcv, 4) <<
                        ",," << Idround(mI.second.sumDel/(double)mI.second.countDel, 4) <<
                        "," << mI.second.maxDel << ",,";

                int cWT = 0;
                int cC = 0;
                for(auto wt : mI.second.distDel) {
                    while(wt.first > cWT) {
                        out << "," << cC;
                        if(cWT < 10) { cWT += 1; }
                        else if(cWT < 100) { cWT += 10; }
                        else { cWT += 100; }
                        cC = 0;
                    }

                    if(wt.first < cWT) {
                        cC += wt.second;
                    } else if(wt.first == cWT) {
                        cC += wt.second;
                        out << "," << cC;
                        if(cWT < 10) { cWT += 1; }
                        else if(cWT < 100) { cWT += 10; }
                        else { cWT += 100; }
                        cC = 0;
                    }
                }
                out << endl;
            }
            out << "QoS," << qos << endl << endl;

        }
        out << endl;
        out << "QoS,*" << endl;
        out << "RCV, DROP, DROP %,,AVG PK W, MAX PK W,,DIST PK WT:";
        for(int i = 0; i<4000;) {
            out << "," << i;
            if(i < 10) { i += 1; }
            else if(i < 100) { i += 10; }
            else { i += 100; }
        }
        out << endl;
        for(auto & mI : modulesInfo) {
            out << mI.second.rcv <<
                    "," << mI.second.drop <<
                    "," << Idround(100.0*mI.second.drop/(double)mI.second.rcv, 4) <<
                    ",," << Idround(mI.second.sumDel/(double)mI.second.countDel, 4) <<
                    "," << mI.second.maxDel << ",,";

            int cWT = 0;
            int cC = 0;
            for(auto wt : mI.second.distDel) {
                while(wt.first > cWT) {
                    out << "," << cC;
                    if(cWT < 10) { cWT += 1; }
                    else if(cWT < 100) { cWT += 10; }
                    else { cWT += 100; }
                    cC = 0;
                }

                if(wt.first < cWT) {
                    cC += wt.second;
                } else if(wt.first == cWT) {
                    cC += wt.second;
                    out << "," << cC;
                    if(cWT < 10) { cWT += 1; }
                    else if(cWT < 100) { cWT += 10; }
                    else { cWT += 100; }
                    cC = 0;
                }
            }
            out << endl;
        }
        out << "QoS,*" << endl << endl;

    }

    void IListenerModule::printGHopInfo(ofstream &out) {
        out << "QoS,,RCV, DROP, DROP %,,AVG PK W, MAX PK W,,DIST PK WT:";
        for(int i = 0; i<=5000;) {
            out << "," << i;
            if(i < 10) { i += 1; }
            else if(i < 100) { i += 10; }
            else { i += 100; }
        }
        out << endl;
        for(string qos : QoS) {


            out << qos <<",,";

            auto & mI = hopQoSInfo[qos];
            int rcv = QoSsend[qos];

            out << rcv <<
                        "," << mI.drop <<
                        "," << Idround(100.0*mI.drop/(double)rcv, 4) <<
                        ",," << Idround(mI.sumDel/(double)mI.countDel, 4) <<
                        "," << mI.maxDel <<
                        ",," << qos;

                int cWT = 0;
                int cC = 0;
                for(auto wt : mI.distDel) {
                    while(wt.first > cWT) {
                        out << "," << cC;
                        if(cWT < 10) { cWT += 1; }
                        else if(cWT < 100) { cWT += 10; }
                        else { cWT += 100; }
                        cC = 0;
                    }

                    if(wt.first < cWT) {
                        cC += wt.second;
                    } else if(wt.first == cWT) {
                        cC += wt.second;
                        out << "," << cC;
                        if(cWT < 10) { cWT += 1; }
                        else if(cWT < 100) { cWT += 10; }
                        else { cWT += 100; }
                        cC = 0;
                    }
                }
                out << "," << cC;
                out << endl;

        }

        out << endl;
        out << endl;

        out << "QoS,,RCV, DROP, DROP %,,AVG PK W, MAX PK W,,DIST PK WT:";
        for(int i = 0; i<=5000;) {
            out << "," << i;
            if(i == 0) { i = 10; }
            else if(i == 10) { i = 50; }
            else if(i == 50) { i = 100; }
            else if(i == 100) { i = 500; }
            else if(i == 500) { i = 1000; }
            else { i += 1000; }
        }
        out << endl;
        for(string qos : QoS) {


            out << qos <<",,";

            auto & mI = hopQoSInfo[qos];
            int rcv = QoSsend[qos];

            out << rcv <<
                        "," << mI.drop <<
                        "," << Idround(100.0*mI.drop/(double)rcv, 4) <<
                        ",," << Idround(mI.sumDel/(double)mI.countDel, 4) <<
                        "," << mI.maxDel <<
                        ",," << qos;

                int cWT = 0;
                int cC = 0;
                for(auto wt : mI.distDel) {
                    while(wt.first > cWT) {
                        out << "," << cC;
                        if(cWT == 0) { cWT = 10; }
                        else if(cWT == 10) { cWT = 50; }
                        else if(cWT == 50) { cWT = 100; }
                        else if(cWT == 100) { cWT = 500; }
                        else if(cWT == 500) { cWT = 1000; }
                        else { cWT += 1000; }
                        cC = 0;
                    }

                    if(wt.first < cWT) {
                        cC += wt.second;
                    } else if(wt.first == cWT) {
                        cC += wt.second;
                        out << "," << cC;
                        if(cWT == 0) { cWT = 10; }
                        else if(cWT == 10) { cWT = 50; }
                        else if(cWT == 50) { cWT = 100; }
                        else if(cWT == 100) { cWT = 500; }
                        else if(cWT == 500) { cWT = 1000; }
                        else { cWT += 1000; }
                        cC = 0;
                    }
                }
                out << "," << cC;
                out << endl;

        }
    }

    void IListenerModule::printFlowInfo(ofstream &out) {
        for(string qos : QoS) {
            out << "QoS," << qos << endl;
            out << "SRC, DST, CEPID,,SEND, DROP, DROP %,,MIN DELAY,AVG DELAY,MAX DELAY,,MIN JITTER,AVG JITTER,MAX JITTER";
            out << endl;
            for(auto & mI : QoSFlowInfo[qos]) {
                out << mI.first.src <<
                        ","<< mI.first.dst <<
                        ","<< mI.first.srcCepId <<
                        ",," << mI.second.snd <<
                        "," << (mI.second.snd - mI.second.rcv) <<
                        "," << 100.0*(mI.second.snd - mI.second.rcv)/(double)mI.second.snd <<
                        ",," << 1000*mI.second.minDel.dbl() <<
                        "," << 1000*mI.second.sumDel.dbl()/(double)mI.second.countDel <<
                        "," << 1000*mI.second.maxDel.dbl() <<
                        ",," << 1000*mI.second.minJitter.dbl() <<
                        "," << 1000*mI.second.sumJit.dbl()/(double)mI.second.countJit <<
                        "," << 1000*mI.second.maxJitter.dbl() <<
                        endl;
            }
            out << "QoS," << qos << endl << endl;
        }
    }

    void IListenerModule::printJFlowInfo(ofstream &out, ofstream &outb) {
        map<string, map<string, map<string, flowInfo> > > qos_src_dst_fInfo;
        set<simtime_t> delays, jitters;
        set<int> consDrops;

        for(string qos : QoS) {
            for(auto & mI : QoSFlowInfo[qos]) {
                flowInfo &cI = mI.second;
                flowInfo & fI = qos_src_dst_fInfo[qos][mI.first.src][mI.first.dst];

                if(cI.minDel < fI.minDel) { fI.minDel = cI.minDel; }
                if(cI.maxDel > fI.maxDel) { fI.maxDel = cI.maxDel; }
                fI.sumDel += cI.sumDel;
                fI.countDel += cI.countDel;
                for(auto & d:cI.distDel) {
                    fI.distDel[d.first] += d.second;
                    delays.insert(d.first);
                }

                if(cI.minJitter < fI.minJitter) { fI.minJitter = cI.minJitter; }
                if(cI.maxJitter > fI.maxJitter) { fI.maxJitter = cI.maxJitter; }
                fI.sumJit += cI.sumJit;
                fI.countJit += cI.countJit;
                for(auto & d:cI.distJit) {
                    fI.distJit[d.first] += d.second;
                    delays.insert(d.first);
                }

                fI.snd += cI.snd;
                fI.rcv += cI.rcv;
                for(auto & d:cI.countConsDrop) {
                    fI.countConsDrop[d.first] += d.second;
                    consDrops.insert(d.first);
                }
            }
        }

        for(string qos : QoS) {
            out << "QoS," << qos << endl;
            out << "SRC, DST,,SEND, DROP, DROP %,,MIN DELAY,AVG DELAY,MAX DELAY,,MIN JITTER,AVG JITTER,MAX JITTER";
            out << endl;
            for(auto & src_ : qos_src_dst_fInfo[qos]) {
                string src = src_.first;
                for(auto & dst_ : src_.second) {
                    string dst = dst_.first;
                    flowInfo &mI = dst_.second;


                    out << src <<
                            ","<< dst <<
                            ",," << mI.snd <<
                            "," << (mI.snd - mI.rcv) <<
                            "," << 100.0*(mI.snd - mI.rcv)/(double)mI.snd <<
                            ",," << 1000*mI.minDel.dbl() <<
                            "," << 1000*mI.sumDel.dbl()/(double)mI.countDel <<
                            "," << 1000*mI.maxDel.dbl() <<
                            ",," << 1000*mI.minJitter.dbl() <<
                            "," << 1000*mI.sumJit.dbl()/(double)mI.countJit <<
                            "," << 1000*mI.maxJitter.dbl() <<
                            endl;
                }
            }
        }


        for(string qos : QoS) {
            outb << "QoS," << qos << endl;
            outb << "SRC, DST,,SEND, DROP, DROP %,, DROPs";
            for(auto & d : consDrops) { outb << "," <<d; }
            outb << endl;
            for(auto & src_ : qos_src_dst_fInfo[qos]) {
                string src = src_.first;
                for(auto & dst_ : src_.second) {
                    string dst = dst_.first;
                    flowInfo &mI = dst_.second;

                    outb << src <<
                            ","<< dst <<
                            ",," << mI.snd <<
                            "," << (mI.snd - mI.rcv) <<
                            "," << 100.0*(mI.snd - mI.rcv)/(double)mI.snd <<
                            ",,";
                            for(auto & d : consDrops) {
                                outb << "," << mI.countConsDrop[d];
                            }
                    outb << endl;
                }
            }
        }
    }

    void IListenerModule::printPSTFlowInfo(ofstream &out) {
        for(string qos : QoS) {
            out << "QoS," << qos << endl;
            out << "SRC, DST, CEPID,,SEND, DROP, DROP %,,MIN DELAY,AVG DELAY,MAX DELAY,,MIN JITTER,AVG JITTER,MAX JITTER";
            out << endl;
            for(auto & mI : QoSFlowInfo[qos]) {
                out << mI.first.src <<
                        ","<< mI.first.dst <<
                        ","<< mI.first.srcCepId <<
                        ",," << mI.second.snd <<
                        "," << (mI.second.snd - mI.second.rcv) <<
                        "," << 100.0*(mI.second.snd - mI.second.rcv)/(double)mI.second.snd <<
                        ",," << mI.second.minPST <<
                        "," << mI.second.sumPST/(double)mI.second.countPST <<
                        "," << mI.second.maxPST <<
                        endl;
            }
            out << "QoS," << qos << endl << endl;
        }
    }

    void IListenerModule::printPSTJFlowInfo(ofstream &out) {
        map<string, map<string, map<string, flowInfo> > > qos_src_dst_fInfo;
        set<int> delays;
        set<int> consDrops;

        for(string qos : QoS) {
            for(auto & mI : QoSFlowInfo[qos]) {
                flowInfo &cI = mI.second;
                flowInfo & fI = qos_src_dst_fInfo[qos][mI.first.src][mI.first.dst];

                if(cI.minPST < fI.minPST) { fI.minPST = cI.minPST; }
                if(cI.maxPST > fI.maxPST) { fI.maxPST = cI.maxPST; }
                fI.sumPST += cI.sumPST;
                fI.countPST += cI.countPST;
                for(auto & d:cI.distPST) {
                    fI.distPST[d.first] += d.second;
                    delays.insert(d.first);
                }

                fI.snd += cI.snd;
                fI.rcv += cI.rcv;
                for(auto & d:cI.countConsDrop) {
                    fI.countConsDrop[d.first] += d.second;
                    consDrops.insert(d.first);
                }
            }
        }

        for(string qos : QoS) {
            out << "QoS," << qos << endl;
            out << "SRC, DST,,SEND, DROP, DROP %,,MIN DELAY,AVG DELAY,MAX DELAY,,MIN JITTER,AVG JITTER,MAX JITTER";
            out << endl;
            for(auto & src_ : qos_src_dst_fInfo[qos]) {
                string src = src_.first;
                for(auto & dst_ : src_.second) {
                    string dst = dst_.first;
                    flowInfo &mI = dst_.second;


                    out << src <<
                            ","<< dst <<
                            ",," << mI.snd <<
                            "," << (mI.snd - mI.rcv) <<
                            "," << 100.0*(mI.snd - mI.rcv)/(double)mI.snd <<
                            ",," << mI.minPST <<
                            "," << mI.sumPST/(double)mI.countPST <<
                            "," << mI.maxPST <<
                            endl;
                }
            }
        }
    }



    void IListenerModule::printQoSInfo(ofstream &out, ofstream &outb) {
        map<string, flowInfo> qos_fInfo;
        set<simtime_t> delays, jitters;
        set<int> consDrops;

        for(string qos : QoS) {
            for(auto & mI : QoSFlowInfo[qos]) {
                flowInfo &cI = mI.second;
                flowInfo & fI = qos_fInfo[qos];

                if(cI.minDel < fI.minDel) { fI.minDel = cI.minDel; }
                if(cI.maxDel > fI.maxDel) { fI.maxDel = cI.maxDel; }
                fI.sumDel += cI.sumDel;
                fI.countDel += cI.countDel;
                for(auto & d:cI.distDel) {
                    fI.distDel[d.first] += d.second;
                    delays.insert(d.first);
                }

                if(cI.minJitter < fI.minJitter) { fI.minJitter = cI.minJitter; }
                if(cI.maxJitter > fI.maxJitter) { fI.maxJitter = cI.maxJitter; }
                fI.sumJit += cI.sumJit;
                fI.countJit += cI.countJit;
                for(auto & d:cI.distJit) {
                    fI.distJit[d.first] += d.second;
                    delays.insert(d.first);
                }

                fI.snd += cI.snd;
                fI.rcv += cI.rcv;
                for(auto & d:cI.countConsDrop) {
                    fI.countConsDrop[d.first] += d.second;
                    consDrops.insert(d.first);
                }
            }
        }

        out << "QoS,,SEND, DROP, DROP %,,MIN DELAY,AVG DELAY,MAX DELAY,,MIN JITTER,AVG JITTER,MAX JITTER";
        out << endl;
        for(string qos : QoS) {
            flowInfo &mI = qos_fInfo[qos];
            out << qos <<
                   ",," << mI.snd <<
                   "," << (mI.snd - mI.rcv) <<
                   "," << 100.0*(mI.snd - mI.rcv)/(double)mI.snd <<
                   ",," << 1000*mI.minDel.dbl() <<
                   "," << 1000*mI.sumDel.dbl()/(double)mI.countDel <<
                   "," << 1000*mI.maxDel.dbl() <<
                   ",," << 1000*mI.minJitter.dbl() <<
                   "," << 1000*mI.sumJit.dbl()/(double)mI.countJit <<
                   "," << 1000*mI.maxJitter.dbl() <<
                   endl;
        }


        outb << "QoS,,SEND, DROP, DROP %,, DROPs";
        for(auto & d : consDrops) { outb << "," <<d; }
        outb << endl;
        for(string qos : QoS) {
            flowInfo &mI = qos_fInfo[qos];
            outb << qos <<
                    ",," <<mI.snd <<
                            "," << (mI.snd - mI.rcv) <<
                            "," << 100.0*(mI.snd - mI.rcv)/(double)mI.snd <<
                            ",,";
                            for(auto & d : consDrops) {
                                outb << "," << mI.countConsDrop[d];
                            }
                    outb << endl;
        }
    }


    void IListener::finish() {
        string config = par("configname").stdstringValue();
        string run = par("runname").stdstringValue();

        string filename = "logs/" + config + "." + run;
        EV << "outfile "<< filename << endl;

        ofstream out, outb;

        out.open (filename +".out");
        out << "Config : "<< config << endl;
        out << "Rate : "<< run << endl;
        module.print(out);
        out.close();


        out.open (filename +".hopInfo.csv");
        out << config << endl;
        out << run << endl;
        module.printHopInfo(out);
        out.close();

        out.open (filename +".gHopInfo.csv");
        out << config << endl;
        out << run << endl;
        module.printGHopInfo(out);
        out.close();


        out.open (filename +".FlowInfo.csv");
        out << config << endl;
        out << run << endl;
        module.printFlowInfo(out);
        out.close();

        out.open (filename +".jFlowInfo.csv");
        outb.open (filename +".jFlowDrops.csv");
        out << config << endl;
        out << run << endl;
        outb << config << endl;
        outb << run << endl;
        module.printJFlowInfo(out, outb);
        out.close();
        outb.close();


        out.open (filename +".PSTFlowInfo.csv");
        out << config << endl;
        out << run << endl;
        module.printPSTFlowInfo(out);
        out.close();

        out.open (filename +".jPSTFlowInfo.csv");
        out << config << endl;
        out << run << endl;
        outb << config << endl;
        outb << run << endl;
        module.printPSTJFlowInfo(out);
        out.close();
        outb.close();


        out.open (filename +".QoSInfo.csv");
        outb.open (filename +".QoSDrops.csv");
        out << config << endl;
        out << run << endl;
        outb << config << endl;
        outb << run << endl;
        module.printQoSInfo(out, outb);
        out.close();
        outb.close();

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

    simtime_t toDistIndex(simtime_t t) {
        return Idround(t.dbl(), 2);
    }
}
