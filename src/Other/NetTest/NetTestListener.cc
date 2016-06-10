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

#include "NetTestListener.h"
#include "NetTest/SigMessages.h"

Define_Module(NetTestListener);

void NetTestListener::initialize() {
    this->getParentModule()->subscribe("InjSignal", this);

    msgRcv = 0;
    msgSent = 0;
}

void NetTestListener::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    if(SigSend *inf = dynamic_cast<SigSend * >(obj)){
        string src = inf->src;
        string dst = inf->dst;
        pairs[src][dst] = INT32_MAX;
        msgSent++;
        return;
    }
    if(SigReceived *inf = dynamic_cast<SigReceived * >(obj)){
        string src = inf->src;
        string dst = inf->dst;
        int hops = inf->hops;
        pairs[src][dst] = hops;
        msgRcv++;
        return;
    }
}

void NetTestListener::finish(){
    cout << "Messages sent : " << msgSent <<endl;
    cout << "Messages received : " << msgRcv <<endl;
    if(msgSent > msgRcv) {
        int fails = 0;
    cout << "Failures : " << endl;
        for(const auto & A : pairs) {
            for(const auto & B : A.second) {
                if(B.second == INT32_MAX) {
                    cout << A.first << " > " << B.first << endl;
                    fails++;
                }
            }
        }
        cout << "Total : "<<fails<<endl;
    }
}
