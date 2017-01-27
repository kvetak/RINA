//
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

#include "DIF/RMT/Monitor/QTAMux/Mux5/Mux5.h"
#include "DIF/RMT/Monitor/QTAMux/QTAMonitor.h"

namespace QTAMux {
using namespace std;


void M5Qinfo::removeTk(int s) {
    tk -= s * sTkBit;
    if(tk < 0) { tk = 0; }
}

void M5Qinfo::addTk(int s) {
    tk += s*rTkBit;
    if(tk > maxTk) { tk = maxTk; }
}

M5QinfoStat M5Qinfo::getInfo(const int & s) {
    return M5QinfoStat(tk >= s * sTkBit, priority);
}


bool M5QinfoStat::compare(const M5QinfoStat & o) const {
    if(enoughTk) {
        if(o.enoughTk) {
            return priority > o.priority;
        } else {
            return false;
        }
    } else {
        if(o.enoughTk) {
            return true;
        } else {
            return priority > o.priority;
        }
    }
}

Mux5::Mux5 (QTAMonitor * _parent, cXMLElement* config) :
        Mux(_parent) {
    defaultTh = 100;
    maxE = 10;

    if(config != nullptr) {
        defaultTh = atoi(config->getAttribute("defaultTh"));
        maxE = atoi(config->getAttribute("MaxE"));

        if(defaultTh < 1) { defaultTh = 1; }
        if(maxE < 0) { maxE = 0; }

        //Initialize queue ECN Th
        cXMLElementList queueConfig = config->getChildrenByTagName("queue");
        for (cXMLElement * qConfig : queueConfig) {
            string name = qConfig->getAttribute("id");
            if (name == "" || name == "default") {
                name = "default";
            }

            int th = atoi(qConfig->getAttribute("th"));
            if(th<=0) { th = 1; }

            int rTkBit = atoi(qConfig->getAttribute("rTkBit"));
            if(rTkBit<=0) { rTkBit = 1; }

            int sTkBit = atoi(qConfig->getAttribute("sTkBit"));
            if(sTkBit<=0) { sTkBit = 1; }

            int maxTk = atoi(qConfig->getAttribute("maxTk"));
            if(maxTk<=0) { maxTk = 1; }

            int priority = atoi(qConfig->getAttribute("priority"));
            if(priority<=0 || priority > 999) { priority = 999; }

            M5Qinfo & info = baseQInfo[name];
            info.th = th;
            info.rTkBit = rTkBit;
            info.sTkBit = sTkBit;
            info.maxTk = maxTk;
            info.maxTk = maxTk;
            info.priority = priority;
        }

        M5Qinfo & info = baseQInfo["default"];
        if(info.th == 0) {
            info.th = defaultTh;
        }
    }
}

Mux5::Mux5 (QTAMonitor * _parent, int _defaultTh, int _maxE, map<string, M5Qinfo> _baseQInfo) :
    Mux(_parent), defaultTh(_defaultTh), maxE(_maxE), baseQInfo(_baseQInfo){}

Mux * Mux5::clone(RMTPort * _port) {
    Mux5 * c = new Mux5(parent, defaultTh, maxE, baseQInfo);
    c->set(_port);
    return c;
}

void Mux5::addedQueue(RMTQueue * q) {
    QInfo[q] = baseQInfo[q->getName()];

}

void Mux5::add(RMTQueue * q, char urgency, char cherish) {
    const cPacket *p = q->getLastPDU();
    const PDU * pdu = dynamic_cast<const PDU*>(p);
    if(pdu == nullptr) {
        cerr << "Non-PDU received"<< endl;
        return;
    }


    int & ecnM = FlowECN[pdu->getConnId()];
    M5Qinfo & qi = QInfo[q];

    if(qi.th > qi.w) {
        //Insert
        qi.w++;

        if(ecnM > 0) {
            q->markCongestionOnLast();
            ecnM--;
        }
    } else {
        // Drop
        parent->recDelete(q->dropLast());
        if(ecnM > maxE) { ecnM++; }
    }
}

RMTQueue * Mux5::getNext() {
    RMTQueue * ret = nullptr;
    M5QinfoStat best;

    for(auto & data : QInfo) {
        if(data.second.w > 0) {
            int nextL = data.first->getFirstPDU()->getByteLength();
            M5QinfoStat t = data.second.getInfo(nextL);

            if(best.compare(t)) {
                ret = data.first;
                best = t;
            }
        }
    }
    if(ret != nullptr) {
        int nextL = ret->getFirstPDU()->getByteLength();
        M5Qinfo & tInfo = QInfo[ret];
        tInfo.w--;
        tInfo.removeTk(nextL);

        for(auto & data : QInfo) {
            data.second.addTk(nextL);
        }
    }

    return ret;
}

}
