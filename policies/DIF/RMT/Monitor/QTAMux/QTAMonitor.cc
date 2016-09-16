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

PSSched::PSSched(PS * _ps) :
        ps(_ps) {
}

void QTAMonitor::onPolicyInit() {
    scheduler = getRINAModule<QTASch*>(this, 1, { MOD_POL_RMT_SCHEDULER });
    if (scheduler == NULL) {
        error("!!! QASch has to be used in conjecture with QTAMonitor!");
    }

    cXMLElement* Xml = nullptr;

    //Initialize base P/S
    Xml = par("shapersData").xmlValue();
    if (Xml != nullptr) {
        cXMLElementList shapersConfig = Xml->getChildrenByTagName("shaper");
        for (cXMLElement * shConfig : shapersConfig) {
            string name = shConfig->getAttribute("id");
            if (name == "" || name == "default") {
                name = "default";
            }
            if (baseShapers.find(name) != baseShapers.end()) {
                cout << "P/S >> " << name << endl;
                error("!!! QTAMonitor, named P/S already configured!!");
            }

            int type = atoi(shConfig->getAttribute("type"));
            PS * shaper = nullptr;
            switch (type) {
            case 1:
                shaper = new PS1(name, this, shConfig);
                break;
            case 2:
                shaper = new PS2(name, this, shConfig);
                break;
            case 3:
                shaper = new PS3(name, this, shConfig);
                break;
            default:
                shaper = new PS0(name, this, shConfig);
            }
            baseShapers[name] = shaper;
        }
    }
    if (baseShapers["default"] == nullptr) {
        baseShapers["default"] = new PS0("default", this, nullptr);
    }

    //Initialize Mux
    Xml = par("muxData").xmlValue();
    if (Xml != nullptr && Xml->hasAttributes()) {
        int type = atoi(Xml->getAttribute("type"));
        switch (type) {
        case 1:
            baseMux = new Mux1(this, Xml);
            break;
        default:
            baseMux = new Mux0(this, Xml);
        }
    } else {
        baseMux = new Mux0(this, nullptr);
    }

    recordStats = par("recordStats").boolValue();
    intervalM = nullptr;
    if (recordStats) {
        nodeName = par("nodeName").stdstringValue();
        if (nodeName == "") {
            nodeName = getFullPath();
        }

        pdu_IO = par("pdu_IO").boolValue();
        data_IO = par("data_IO").boolValue();
        saveStats = par("saveStats").boolValue();
        if (saveStats) {
            record_interval = par("record_interval").doubleValue();
            double first_interval = par("first_interval").doubleValue();
            last_interval = par("last_interval").doubleValue();

            if (record_interval > 0.0) {
                pdu_IOi = par("pdu_IOi").boolValue();
                data_IOi = par("data_IOi").boolValue();
                string temp = "IntervalM" + nodeName;
                intervalM = new cMessage(temp.c_str());
                scheduleAt(first_interval, intervalM);
            }
        }

    }

}

void QTAMonitor::postQueueCreation(RMTQueue* queue) {
    if (queue->getType() == RMTQueue::OUTPUT) {
        //First Queue of port? -> Initialize Mux
        RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);

        Mux * mux = muxs[port];
        if (mux == nullptr) {
            mux = baseMux->clone(port);
            muxs[port] = mux;

            if (recordStats && saveStats) {
                string name = port->getName();
                if (port->getFlow()) {
                    name = port->getFlow()->getDstAddr().getIpcAddress().getName();
                }
                PortName[port] = name;
                auto & out = PortStream[port];

                out.open("stats/" + nodeName + "."+name+".stats", fstream::out);
                if (!out.is_open()) {
                    string eMessage = "Error Creating stats file \"stats/"
                            + nodeName + "."+name+".stats\"";
                    error(eMessage.c_str());
                }

                out << "Node\t" << nodeName << endl;
                out << "Port\t" << name << endl << endl;
                out << "QoS";
                if (pdu_IO) {
                    out << "\tpdu_in";
                    out << "\tpdu_out";
                    out << "\tpdu_drop";
                }
                if (data_IO) {
                    out << "\tdata_in";
                    out << "\tdata_out";
                    out << "\tdata_drop";
                }
                out << endl;

            }
        }

        //Initialize shaper for queue
        if (shapers.find(queue) != shapers.end()) {
            error("!!! QTAMonitor, queue P/S already configured!");
        }
        string name = queue->getName();
        if (baseShapers.find(name) == baseShapers.end()) {
            name = "default";
        }
        shapers[queue] = baseShapers[name]->clone(port, queue, mux);
    }
}

void QTAMonitor::finish() {
    for (auto pMux : muxs) {
        Mux * mux = pMux.second;
        if (mux != nullptr) {
            mux->finish();
            delete mux;
        }
    }
    muxs.clear();

    for (auto qPS : shapers) {
        PS * shaper = qPS.second;
        if (shaper != nullptr) {
            shaper->finish();
            delete shaper;
        }
    }
    shapers.clear();

    for (auto qPS : baseShapers) {
        PS * shaper = qPS.second;
        if (shaper != nullptr) {
            shaper->finish();
            delete shaper;
        }
    }
    baseShapers.clear();

    if (intervalM != nullptr) {
        cancelAndDelete(intervalM);
    }

    if (recordStats) {

        if (saveStats) {
            printInterval();
            if (pdu_IO || data_IO) {
                printSummary();
            }
            for(auto it = PortStream.begin(); it != PortStream.end(); it++) {
                it->second.close();
            }
        }

        if (par("printAtEnd").boolValue()) {
            if (pdu_IO || data_IO) {
                coutSummary();
            }
        }
    }
}

void QTAMonitor::preQueueRemoval(RMTQueue* queue) {
    PS * shaper = shapers[queue];
    if (shaper != nullptr) {
        shaper->finish();
        delete shaper;
    }
    shapers.erase(queue);
}

cMessage * QTAMonitor::schedulePS(PS * ps, simtime_t t) {
    Enter_Method_Silent
    ();
    cMessage * m = new PSSched(ps);
    scheduleAt(simTime() + t, m);
    return m;
}

void QTAMonitor::callMux(RMTPort * port) {
    Enter_Method_Silent
    ();
    scheduler->scheduleNow(port);
}

void QTAMonitor::handleMessage(cMessage * msg) {
    if (msg == intervalM) {
        printInterval();
        if (simTime() < last_interval) {
            scheduleAt(simTime() + record_interval, intervalM);
        } else {
            delete intervalM;
            intervalM = nullptr;
        }
        return;
    }
    if (PSSched * m = dynamic_cast<PSSched *>(msg)) {
        m->ps->run();
    }
    delete msg;
}

void QTAMonitor::postPDUInsertion(RMTQueue* queue) {
    if (queue->getType() == RMTQueue::INPUT) {
        return;
    }

    PS * shaper = shapers[queue];
    if (shaper == nullptr) {
        error("!!! QTAMonitor, queue P/S not configured!");
    }

    if (recordStats) {
        if (const PDU * c = dynamic_cast<const PDU*>(queue->getLastPDU())) {
            int len = c->getByteLength();
            string qos = c->getConnId().getQoSId();
            recordedQoS.insert(qos);
            RMTPort * port = shaper->port;
            PDU2Port[c] = port;
            PDU2Arrival[c] = simTime();

            if (pdu_IO) {
                qos_pdu_IO_in[port][qos]++;
            }
            if (pdu_IOi) {
                qos_pdu_IOi_in[port][qos]++;
            }
            if (data_IO) {
                qos_data_IO_in[port][qos] += len;
            }
            if (data_IOi) {
                qos_data_IOi_in[port][qos] += len;
            }
        }
    }

    shaper->inserted();
}

RMTQueue * QTAMonitor::getNext(RMTPort * port) {
    Mux * mux = muxs[port];
    if (mux == nullptr) {
        error("!!! QTAMonitor, mux not started!");
    }
    RMTQueue * q = mux->getNext();

    if (q != nullptr && recordStats) {
        if (const PDU * c = dynamic_cast<const PDU*>(q->getFirstPDU())) {
            int len = c->getByteLength();
            string qos = c->getConnId().getQoSId();
            recordedQoS.insert(qos);
            PDU2Port.erase(c);
/*
            if(nodeName == "A") {
                cout << "\t"<< (simTime() - PDU2Arrival[c])<<endl;
            }
*/
            PDU2Arrival.erase(c);

            if (pdu_IO) {
                qos_pdu_IO_out[port][qos]++;
            }
            if (pdu_IOi) {
                qos_pdu_IOi_out[port][qos]++;
            }
            if (data_IO) {
                qos_data_IO_out[port][qos] += len;
            }
            if (data_IOi) {
                qos_data_IOi_out[port][qos] += len;
            }
        }
    }
    return q;
}

void QTAMonitor::recDelete(cPacket * p) {
    if (recordStats && p != nullptr) {
        if (const PDU * c = dynamic_cast<const PDU*>(p)) {
            int len = c->getByteLength();
            string qos = c->getConnId().getQoSId();
            RMTPort * port = PDU2Port[c];
            PDU2Port.erase(c);

            if (pdu_IO) {
                qos_pdu_IO_drop[port][qos]++;
            }
            if (pdu_IOi) {
                qos_pdu_IOi_drop[port][qos]++;
            }
            if (data_IO) {
                qos_data_IO_drop[port][qos] += len;
            }
            if (data_IOi) {
                qos_data_IOi_drop[port][qos] += len;
            }
        }
    }
    recIDelete(p);
}
void QTAMonitor::recIDelete(cPacket * p) {
    cPacket * enc = p->decapsulate();
    if (enc != nullptr) {
        recIDelete(enc);
    }
    delete p;
}

void QTAMonitor::printInterval() {
    for(auto it = PortStream.begin(); it != PortStream.end(); it++) {
        auto & out = it->second;
        auto port = it->first;
        out << "Interval\t" << currentInterval << endl;
        for (const string & qos : recordedQoS) {
            out << qos;
            if (pdu_IOi) {
                out << "\t" << qos_pdu_IOi_in[port][qos];
                out << "\t" << qos_pdu_IOi_out[port][qos];
                out << "\t" << qos_pdu_IOi_drop[port][qos];
            }
            if (data_IOi) {
                out << "\t" << qos_data_IOi_in[port][qos];
                out << "\t" << qos_data_IOi_out[port][qos];
                out << "\t" << qos_data_IOi_drop[port][qos];
            }
            out << endl;
        }
    }
    if (pdu_IOi) {
        qos_pdu_IOi_in.clear();
        qos_pdu_IOi_out.clear();
        qos_pdu_IOi_drop.clear();
    }
    if (data_IOi) {
        qos_data_IOi_in.clear();
        qos_data_IOi_out.clear();
        qos_data_IOi_drop.clear();
    }

    currentInterval++;
}

void QTAMonitor::printSummary() {
    for(auto it = PortStream.begin(); it != PortStream.end(); it++) {
        auto & out = it->second;
        auto port = it->first;
        out << endl << "Summary" << endl;
        long long count_in = 0;
        long long count_out = 0;
        long long count_drop = 0;
        long long data_in = 0;
        long long data_out = 0;
        long long data_drop = 0;

        out << "QoS";
        if (pdu_IO) {
            out << "\tpdu_in";
            out << "\tpdu_out";
            out << "\tpdu_drop";
        }
        if (data_IO) {
            out << "\tdata_in";
            out << "\tdata_out";
            out << "\tdata_drop";
        }
        out << endl;

        for (const string & qos : recordedQoS) {
            out << qos;
            if (pdu_IO) {
                out << "\t" << qos_pdu_IO_in[port][qos];
                out << "\t" << qos_pdu_IO_out[port][qos];
                out << "\t" << qos_pdu_IO_drop[port][qos];

                count_in += qos_pdu_IO_in[port][qos];
                count_out += qos_pdu_IO_out[port][qos];
                count_drop += qos_pdu_IO_drop[port][qos];
            }
            if (data_IO) {
                out << "\t" << qos_data_IO_in[port][qos];
                out << "\t" << qos_data_IO_out[port][qos];
                out << "\t" << qos_data_IO_drop[port][qos];

                data_in += qos_pdu_IOi_in[port][qos];
                data_out += qos_pdu_IOi_out[port][qos];
                data_drop += qos_pdu_IOi_drop[port][qos];
            }
            out << endl;
        }
        out << "Total";
        if (pdu_IO) {
            out << "\t" << count_in;
            out << "\t" << count_out;
            out << "\t" << count_drop;
        }
        if (data_IO) {
            out << "\t" << data_in;
            out << "\t" << data_out;
            out << "\t" << data_drop;
        }
    }
}

void QTAMonitor::coutSummary() {
    cout << "--Node " << nodeName << endl;

    for (auto ps : PortName) {
        auto name = ps.second;
        auto port = ps.first;
        cout << "Summary port :: " << name << endl;

        long long count_in = 0;
        long long count_out = 0;
        long long count_drop = 0;
        long long data_in = 0;
        long long data_out = 0;
        long long data_drop = 0;

        cout << "QoS";
        if (pdu_IO) {
            cout << "\tpdu_in";
            cout << "\tpdu_out";
            cout << "\tpdu_drop";
        }
        if (data_IO) {
            cout << "\tdata_in";
            cout << "\tdata_out";
            cout << "\tdata_drop";
        }
        cout << endl;

        for (const string & qos : recordedQoS) {
            cout << qos;
            if (pdu_IO) {
                cout << "\t" << qos_pdu_IO_in[port][qos];
                cout << "\t" << qos_pdu_IO_out[port][qos];
                cout << "\t" << qos_pdu_IO_drop[port][qos];

                count_in += qos_pdu_IO_in[port][qos];
                count_out += qos_pdu_IO_out[port][qos];
                count_drop += qos_pdu_IO_drop[port][qos];
            }
            if (data_IO) {
                cout << "\t" << qos_data_IO_in[port][qos];
                cout << "\t" << qos_data_IO_out[port][qos];
                cout << "\t" << qos_data_IO_drop[port][qos];

                data_in += qos_pdu_IOi_in[port][qos];
                data_out += qos_pdu_IOi_out[port][qos];
                data_drop += qos_pdu_IOi_drop[port][qos];
            }
            cout << endl;
        }
        cout << "Total";
        if (pdu_IO) {
            cout << "\t" << count_in;
            cout << "\t" << count_out;
            cout << "\t" << count_drop;
        }
        if (data_IO) {
            cout << "\t" << data_in;
            cout << "\t" << data_out;
            cout << "\t" << data_drop;
        }
        cout << endl;
    }
    cout << endl;
}

}
