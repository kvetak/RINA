#include "InjListener.h"

InjListener * InjListener::instance = nullptr;

Define_Module(InjListener);


voiceFlowStat::voiceFlowStat():
    min_lat(500000.0), max_lat(0.0), sum_lat(0.0), count(0){}

void voiceFlowStat::add(simtime_t lat) {
    double l = lat.dbl();
    if(min_lat > l) { min_lat = l; }
    if(max_lat < l) { max_lat = l; }
    sum_lat += l;
    count++;
}


void InjListener::initialize() {
    InjListener::instance = this;
}


void InjListener::finish(){
    cout << "Listener finish"<<endl;
    cout << "VOICE"<<endl;
    for(auto src_ : voiceStats) {
        for(auto dst_ : src_.second) {
            for(auto flow_ : dst_.second) {
                cout << "Flow "
                        << src_.first << " -> " << dst_.first
                        << " ["<< flow_.first<< "]"
                        << endl;
                cout << "  Min/Max : "<< flow_.second.min_lat*1000.0 << "ms/"<<flow_.second.max_lat*1000.0 << "ms"<< endl;
                cout << "  Avg - count : "<< (flow_.second.sum_lat/flow_.second.count)*1000.0 << "ms - "<<flow_.second.count<< endl;
            }
        }
    }
    cout << "DATA"<<endl;
    for(auto src_ : dataStart) {
        for(auto dst_ : src_.second) {
            for(auto flow_ : dst_.second) {
                cout << "Flow "
                        << src_.first << " -> " << dst_.first
                        << " ["<< flow_.first<< "]"
                        << endl;
                cout << "  request : "<< flow_.second
                        << " / received "<< dataEnd[src_.first][dst_.first][flow_.first]<< endl;
            }
        }
    }
    cout <<endl;
}

void InjListener::voiceReceived(string src, string dst, int flow, simtime_t lat) {
    //voiceStats[src][dst][flow].add(lat);
    voiceStats[src][dst][-1].add(lat);
}
void InjListener::dataRequestStarted(string src, string dst, int flow){
    dataStart[src][dst][flow]++;
   // cout <<simTime()<< " - Data req start "<< src << " -> "<< dst << " + "<< flow<<endl;
}
void InjListener::dataRequestEnded(string src, string dst, int flow){
    dataEnd[src][dst][flow]++;
   // cout <<simTime()<< " - Data req end "<< src << " -> "<< dst << " + "<< flow<<endl;
}
