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

#include "QTAMux/QTAMonitor.h"
#include "QTASch/QTASch.h"
#include "QTAMux/PS0/PS0.h"
#include "QTAMux/PS1/PS1.h"
#include "QTAMux/PS2/PS2.h"
#include "QTAMux/PS3/PS3.h"
#include "QTAMux/Mux0/Mux0.h"
#include "QTAMux/Mux1/Mux1.h"

namespace QTAMux {
using namespace std;

Define_Module(QTAMonitor);

PSSched::PSSched(PS * _ps) : ps(_ps){};

void QTAMonitor::onPolicyInit(){
    scheduler= getRINAModule<QTASch*>(this, 1, {MOD_POL_RMT_SCHEDULER});
    if (scheduler == NULL) { error("!!! QASch has to be used in conjecture with QTAMonitor!"); }

    cXMLElement* Xml = nullptr;

    //Initialize base P/S
    Xml = par("shapersData").xmlValue();
    if(Xml != nullptr) {
        cXMLElementList shapersConfig = Xml->getChildrenByTagName("shaper");
        for(cXMLElement * shConfig : shapersConfig) {
            string name = shConfig->getAttribute("id");
            if(name == "" || name == "default") { name = "default"; }
            if(baseShapers.find(name) != baseShapers.end()) {
                cout << "P/S >> " << name << endl;
                error("!!! QTAMonitor, named P/S already configured!!");
            }

            int type = atoi(shConfig->getAttribute("type"));
            PS * shaper = nullptr;
            switch(type) {
                case 1:
                    shaper = new PS1(name, this, shConfig); break;
                case 2:
                    shaper = new PS2(name, this, shConfig); break;
                case 3:
                    shaper = new PS3(name, this, shConfig); break;
                default:
                    shaper = new PS0(name, this, shConfig);
            }
            baseShapers[name] = shaper;
        }
    }
    if(baseShapers["default"] == nullptr ) {
        baseShapers["default"] = new PS0("default", this, nullptr);
    }

    //Initialize Mux
    Xml = par("muxData").xmlValue();
    if(Xml != nullptr && Xml->hasAttributes()) {
        int type = atoi(Xml->getAttribute("type"));
        switch(type) {
            case 1:
                baseMux = new Mux1(this, Xml); break;
            default:
                baseMux = new Mux0(this, Xml);
        }
    } else {
        baseMux = new Mux0(this, nullptr);
    }
}

void QTAMonitor::postQueueCreation(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::OUTPUT) {
        //First Queue of port? -> Initialize Mux
        RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);

        Mux * mux = muxs[port];
        if(mux == nullptr) {
            mux = baseMux->clone(port);
            muxs[port] = mux;
        }

        //Initialize shaper for queue
        if(shapers.find(queue) != shapers.end()) {
            error("!!! QTAMonitor, queue P/S already configured!");
        }
        string name = queue->getName();
        if(baseShapers.find(name) == baseShapers.end()) { name = "default"; }
        shapers[queue] = baseShapers[name]->clone(port, queue, mux);
    }
}

void QTAMonitor::finish() {
    for(auto pMux : muxs) {
        Mux * mux = pMux.second;
        if(mux != nullptr) {
            mux->finish();
            delete mux;
        }
    }
    muxs.clear();

    for(auto qPS : shapers) {
        PS * shaper = qPS.second;
        if(shaper != nullptr) {
            shaper->finish();
            delete shaper;
        }
    }
    shapers.clear();

    for(auto qPS : baseShapers) {
        PS * shaper = qPS.second;
        if(shaper != nullptr) {
            shaper->finish();
            delete shaper;
        }
    }
    baseShapers.clear();

    if(par("printAtEnd").boolValue()) {
        cout << "At " << getFullPath()<<endl;
        for(auto p_ : received) {
            cout << "  Port "<< p_.first->getFullPath()<<endl;
            for(auto q_ : p_.second) {
                cout << "    QoS "<< q_.first << " | "<<q_.second << " / "<< sent[p_.first][q_.first]<<endl;
            }
        }
        cout << "-----------------" <<endl;
    }
}

void QTAMonitor::preQueueRemoval(RMTQueue* queue) {
    PS * shaper = shapers[queue];
    if(shaper != nullptr) {
        shaper->finish();
        delete shaper;
    }
    shapers.erase(queue);
}

cMessage * QTAMonitor::schedulePS(PS * ps, simtime_t t) {
    Enter_Method_Silent();
    cMessage * m = new PSSched(ps);
    scheduleAt(simTime() + t, m);
    return m;
}

void QTAMonitor::callMux(RMTPort * port) {
    Enter_Method_Silent();
    scheduler->scheduleNow(port);
}

void QTAMonitor::handleMessage(cMessage * msg) {
    if(PSSched * m = dynamic_cast<PSSched *>(msg)) {
        m->ps->run();
    }
    delete msg;
}

void QTAMonitor::postPDUInsertion(RMTQueue* queue) {
    if(queue->getType() == RMTQueue::INPUT) { return; }

    cPacket * p = const_cast<cPacket*>(queue->getLastPDU());
    PDUarrival[p] = currentPDU;

    PS * shaper = shapers[queue];
    if(shaper == nullptr) { error("!!! QTAMonitor, queue P/S not configured!"); }
    shaper->inserted();

    received[shaper->port][queue->getName()]++;

}

RMTQueue * QTAMonitor::getNext(RMTPort * port) {
    Mux * mux = muxs[port];
    if(mux == nullptr) { error("!!! QTAMonitor, mux not started!"); }
    RMTQueue * q = mux->getNext();
    if(q!=nullptr) {
        cPacket * p = const_cast<cPacket*>(q->getFirstPDU());
        long arrival = PDUarrival[p];
        PDUarrival.erase(p);
        if(InfectedDataTransferPDU * cPdu = dynamic_cast< InfectedDataTransferPDU*>(p)) {
            cPdu->pstDelay += currentPDU-arrival;
        }
        sent[port][q->getName()]++;
        currentPDU++;
    }
    return q;
}

void QTAMonitor::recDelete(cPacket * p) {
    PDUarrival.erase(p);
    recIDelete(p);
}
void QTAMonitor::recIDelete(cPacket * p) {
    cPacket * enc = p->decapsulate();
    if(enc != nullptr) { recIDelete(enc); }
    delete p;
}

}
