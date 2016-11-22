#include "VDT_Listener.h"
#include <math.h>

VDT_Listener * VDT_Listener::instance = nullptr;

Define_Module(VDT_Listener);


stats::stats():
    min_lat(500000.0), max_lat(0.0), sum_lat(0.0), countSent(0), countRecv(0){}

void stats::add() {
    countSent++;
}

void stats::add(simtime_t lat) {
    double l = lat.dbl();
    if(min_lat > l) { min_lat = l; }
    if(max_lat < l) { max_lat = l; }
    sum_lat += l;
    countRecv++;
}


void VDT_Listener::initialize() {
    VDT_Listener::instance = this;
    recordTrace = par("recordTrace").boolValue();
    if(recordTrace){
        tracer.open("stats/"
                + string(omnetpp::getEnvir()->getConfigEx()->getActiveConfigName())+"-"
                + to_string(omnetpp::getEnvir()->getConfigEx()->getActiveRunNumber())
                + ".trace", fstream::out | fstream::binary);
        flowsInfo.open("stats/"
                + string(omnetpp::getEnvir()->getConfigEx()->getActiveConfigName())+"-"
                + to_string(omnetpp::getEnvir()->getConfigEx()->getActiveRunNumber())
                + ".traceinfo", fstream::out);
        nextGlobal = 1;
    }
    recordTimes = par("recordDelay").boolValue();
    interval_digits = par("interval_digits").longValue();
    if(recordTimes) {
        cout << "Record delays with "<< interval_digits << " digits"<<endl;
    } else {
        cout << "Don't record delays" << endl;
    }
}


void VDT_Listener::finish(){
    fstream out;
    out.open("stats/"
            + string(omnetpp::getEnvir()->getConfigEx()->getActiveConfigName())+"-"
            + to_string(omnetpp::getEnvir()->getConfigEx()->getActiveRunNumber())
            + ".results", fstream::out);

    out << "Voice"<<endl;
    outStats(voice, out);
    out << endl;

    out << "Full request"<<endl;
    outStats(fullRequest, out);
    out << endl;

    out << "Requests"<<endl;
    outStats(request, out);
    out << endl;

    out << "Data"<<endl;
    outStats(data, out);
    out << endl;

    out.close();

    if(recordTimes) {
        out.open("stats/"
                + string(omnetpp::getEnvir()->getConfigEx()->getActiveConfigName())+"-"
                + to_string(omnetpp::getEnvir()->getConfigEx()->getActiveRunNumber())
                + ".delay.results", fstream::out);
        outDelays(out);
        out.close();
    }

    if(par("printAtEnd").boolValue()) {
        cout << "Listener finish"<<endl;
        cout << "Voice"<<endl;
        coutStats(voice);
        cout << endl;

        cout << "Full request"<<endl;
        coutStats(fullRequest);
        cout << endl;

        cout << "Requests"<<endl;
        coutStats(request);
        cout << endl;

        cout << "Data"<<endl;
        coutStats(data);
        cout << endl;
    }

    if(recordTrace) {
        trace_t t;
        t.type = 255;
        t.time = simTime().dbl();
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
        tracer.close();
        flowsInfo.close();
    }
}


void VDT_Listener::outStats(const map<string, map<string, map<string, map<int, stats> > > > & st, fstream & out) {

    for(auto src_ : st) {
        for(auto dst_ : src_.second) {
            for(auto qos_ : dst_.second) {
                for(auto flow_ : qos_.second) {
                    const stats & stat = flow_.second;
                    out << ":: "<< src_.first << " -> "<< dst_.first
                            << " \\ "<< qos_.first << " ["<<flow_.first<<"]"<<endl;
                    out << "   min/avg/max | "
                            << stat.min_lat*1000.0 << " / "
                            << (stat.sum_lat/stat.countRecv)*1000.0 << " / "
                            << stat.max_lat*1000.0  << " ms"<< endl;
                    out << "   sent/recv/% | "
                            << stat.countSent << " / "
                            << stat.countRecv << " / "
                            << (100.0*stat.countRecv/stat.countSent) << " %"<< endl;

                }
            }
        }
    }
}

void VDT_Listener::coutStats(const map<string, map<string, map<string, map<int, stats> > > > & st) {

    for(auto src_ : st) {
        for(auto dst_ : src_.second) {
            for(auto qos_ : dst_.second) {
                for(auto flow_ : qos_.second) {
                    const stats & stat = flow_.second;
                    cout << ":: "<< src_.first << " -> "<< dst_.first
                            << " \\ "<< qos_.first << " ["<<flow_.first<<"]"<<endl;
                    cout << "   min/avg/max | "
                            << stat.min_lat*1000.0 << " / "
                            << (stat.sum_lat/stat.countRecv)*1000.0 << " / "
                            << stat.max_lat*1000.0  << " ms"<< endl;
                    cout << "   sent/recv/% | "
                            << stat.countSent << " / "
                            << stat.countRecv << " / "
                            << (100.0*stat.countRecv/stat.countSent) << " %"<< endl;

                }
            }
        }
    }
}

void VDT_Listener::outDelays(fstream & out) {
    for(auto & t : srcDstQoS_delay) {
        long long count = 0;
        long double sum = 0;
        out << "--" << t.first << "--" << endl;
        for(auto & v : t.second) {
            out << v.first*1000 << "\t" << v.second << endl;
            count += v.second;
            sum += v.second * v.first;
        }
        out << "=>" << (sum*1000/count)<< endl << endl;
    }
}

void VDT_Listener::voiceSent(string src, string dst, string qos, int flow, long long id, int len) {
    voice[src][dst][qos][flow].add();
    if(recordTrace) {
        trace_t t;
        t.type = 0;
        t.time = simTime().dbl();
        t.pduId = id;
        t.len = len;
        t.globalFlowId = getGlobal(src, dst, qos, flow);
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
    }
}
void VDT_Listener::voiceRecv(string src, string dst, string qos, int flow, simtime_t lat, long long id, int len) {
    voice[src][dst][qos][flow].add(lat);
    if(recordTrace) {
        trace_t t;
        t.type = 1;
        t.time = simTime().dbl();
        t.pduId = id;
        t.len = len;
        t.globalFlowId = getGlobal(src, dst, qos, flow);
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
    }
    if(recordTimes) {
        string sdq = src+" -> " + dst + " with QoS " + qos;
        double interval = dround(lat.dbl(), interval_digits);
        srcDstQoS_delay[sdq][interval]++;
    }
}

void VDT_Listener::requestEnd(string src, string dst, string qos, int flow, simtime_t duration) {
    fullRequest[src][dst][qos][flow].add();
    fullRequest[src][dst][qos][flow].add(duration);

}


void VDT_Listener::requestSent(string src, string dst, string qos, int flow, long long id, int len) {
    request[src][dst][qos][flow].add();

    if(recordTrace) {
        trace_t t;
        t.type = 0;
        t.time = simTime().dbl();
        t.pduId = id;
        t.len = len;
        t.globalFlowId = getGlobal(src, dst, qos, flow);
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
    }
}
void VDT_Listener::requestRecv(string src, string dst, string qos, int flow, simtime_t lat, long long id, int len) {
    request[src][dst][qos][flow].add(lat);
    if(recordTrace) {
        trace_t t;
        t.type = 1;
        t.time = simTime().dbl();
        t.pduId = id;
        t.len = len;
        t.globalFlowId = getGlobal(src, dst, qos, flow);
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
    }
    if(recordTimes) {
        string sdq = src+" -> " + dst + " with QoS " + qos;
        double interval = dround(lat.dbl(), interval_digits);
        srcDstQoS_delay[sdq][interval]++;
    }
}

void VDT_Listener::dataSent(string src, string dst, string qos, int flow, long long id, int len) {
    data[src][dst][qos][flow].add();

    if(recordTrace) {
        trace_t t;
        t.type = 0;
        t.time = simTime().dbl();
        t.pduId = id;
        t.len = len;
        t.globalFlowId = getGlobal(src, dst, qos, flow);
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
    }
}
void VDT_Listener::dataRecv(string src, string dst, string qos, int flow, simtime_t lat, long long id, int len) {
    data[src][dst][qos][flow].add(lat);
    if(recordTrace) {
        trace_t t;
        t.type = 1;
        t.time = simTime().dbl();
        t.pduId = id;
        t.len = len;
        t.globalFlowId = getGlobal(src, dst, qos, flow);
        tracer.write((char*)&t, sizeof(trace_t));
        tracer.flush();
    }
    if(recordTimes) {
        string sdq = src+" -> " + dst + " with QoS " + qos;
        double interval = dround(lat.dbl(), interval_digits);
        srcDstQoS_delay[sdq][interval]++;
    }
}


long long VDT_Listener::getGlobal(string src, string dst, string qos, int flowId) {
    long long & id = globalFlowIds[src][dst][qos][flowId];
    if (id <= 0) {
        id = nextGlobal++;

        flowsInfo << id << " " << src << " " << dst << " "  << qos << " "  << flowId << endl;
        flowsInfo.flush();
    }
    return id;
}




double VDT_Listener::dround(double a, int ndigits) {

  int    exp_base10 = round(log10(a));
  double man_base10 = a*pow(10.0,-exp_base10);
  double factor     = pow(10.0,-ndigits+1);
  double truncated_man_base10 = man_base10 - fmod(man_base10,factor);
  double rounded_remainder    = fmod(man_base10,factor)/factor;

  rounded_remainder = rounded_remainder > 0.5 ? 1.0*factor : 0.0;

  return (truncated_man_base10 + rounded_remainder)*pow(10.0,exp_base10) ;
}

