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

#pragma once

//Standard libraries
#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include "AEConstantMsgs.h"

#include <set>
#include <map>

namespace IListener {

    using namespace std;

    struct modQoSInfo {
        int maxDel;
        map<int, int> distDel;
        int countDel;
        int sumDel;

        int rcv, drop;

        modQoSInfo();
        void RcvMsg();
        void DropMsg();
        void ServeMsg(int t);
    };

    struct flowId {
        string src, dst;
        int srcCepId;
        string qos;

        flowId(string _src, string _dst, int _srcCepId, string _qos);
        bool operator<( const flowId & o ) const ;
    };

    struct flowInfo {
        simtime_t minDel, maxDel;
        map<simtime_t, int> distDel;
        int countDel;
        simtime_t sumDel;


        int minPST, maxPST;
        map<int, int> distPST;
        int countPST;
        long sumPST;

        simtime_t lastDelay;
        simtime_t minJitter, maxJitter;
        map<simtime_t, int> distJit;
        int countJit;
        simtime_t sumJit;


        int snd, rcv;
        map<int, int> countConsDrop;
        int lastSec, consDrop;

        flowInfo();

        void SendMsg();
        void RcvMsg(int nSec, simtime_t h_delay, simtime_t p_delay, int pst_delay);
    };


    class IListenerModule : public cListener {
          public:
                set<string> QoS;
                map<string, double> QoSDelay, QoSJitter;

                void initialize();
                virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj);
                void print(ofstream &out);
                void printHopInfo(ofstream &out);
                void printGHopInfo(ofstream &out);
                void printFlowInfo(ofstream &out);
                void printJFlowInfo(ofstream &out, ofstream &outb);

                void printPSTFlowInfo(ofstream &out);
                void printPSTJFlowInfo(ofstream &out);

                void printQoSInfo(ofstream &out, ofstream &outb);
                double h_delayV;

          protected:
                map<string, map<cModule *, modQoSInfo> > modulesQoSInfo;
                map<string, modQoSInfo> hopQoSInfo;
                map<string, int> QoSsend;

                map<cModule *, modQoSInfo> modulesInfo;

                map<string, map<flowId, flowInfo> > QoSFlowInfo;

    };

    class IListener : public cSimpleModule {
      protected:
        virtual void initialize();
        virtual void finish();
      private:
        IListenerModule module;
        double h_delayV;
    };

    double Idround(double a, int ndigits);
    simtime_t toDistIndex(simtime_t t);

}
