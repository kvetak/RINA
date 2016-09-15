#include "VDT_Listener.h"

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
}


void VDT_Listener::finish(){
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

void VDT_Listener::voiceSent(string src, string dst, string qos, int flow) {
    voice[src][dst][qos][flow].add();
}
void VDT_Listener::voiceRecv(string src, string dst, string qos, int flow, simtime_t lat) {
    voice[src][dst][qos][flow].add(lat);
}

void VDT_Listener::requestEnd(string src, string dst, string qos, int flow, simtime_t duration) {
    fullRequest[src][dst][qos][flow].add();
    fullRequest[src][dst][qos][flow].add(duration);
}


void VDT_Listener::requestSent(string src, string dst, string qos, int flow) {
    request[src][dst][qos][flow].add();
}
void VDT_Listener::requestRecv(string src, string dst, string qos, int flow, simtime_t lat) {
    request[src][dst][qos][flow].add(lat);
}

void VDT_Listener::dataSent(string src, string dst, string qos, int flow) {
    data[src][dst][qos][flow].add();
}
void VDT_Listener::dataRecv(string src, string dst, string qos, int flow, simtime_t lat) {
    data[src][dst][qos][flow].add(lat);
}



