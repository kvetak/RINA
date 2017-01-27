#include "Addons/DataInjectors/ReachabilityTest/ReachabilityTest_Listener.h"

ReachabilityTest_Listener * ReachabilityTest_Listener::instance = nullptr;

Define_Module(ReachabilityTest_Listener);


void ReachabilityTest_Listener::initialize() {
    ReachabilityTest_Listener::instance = this;
}

void ReachabilityTest_Listener::finish(){
    cout << "Listener finish"<<endl;

    long long sent = 0;
    long long received = 0;
    long long lost = 0;
    for(auto a : dataInfo) {
        info_t & i = a.second;
        sent += i.sent;
        received += i.received;
        lost += i.sent-i.received;
        if(!i.times.empty()) {
        cout << a.first << " || "<< i.sent<<"/"<<i.received <<endl;
            for(auto t : i.times) {
                cout << "  Lost sent at "<< t<<endl;
            }
        }
    }
    cout << "Sent/Received "<< sent<<"/"<<received << " | Lost "<<lost<<endl;
    cout <<endl;
}

void ReachabilityTest_Listener::sent(const string & src, const string & dst, const string & qos, const int & stage) {
//    cout << "Sent "<< src << " -> " << dst << "("<<qos<<"), stage " << stage << ", sent at " << simTime()<<endl;

    info_t & i = dataInfo[src+"_"+dst+"_"+qos+"_"+to_string(stage)];
    i.sent++;
    i.times.push_back(simTime());
}

void ReachabilityTest_Listener::received(const string & src, const string & dst, const string & qos, const int & stage, const simtime_t & sentAt) {
//    cout << "Received "<< src << " -> " << dst << "("<<qos<<"), stage " << stage << ", sent at " <<sentAt << " - received at "<< simTime()<<endl;

    info_t & i = dataInfo[src+"_"+dst+"_"+qos+"_"+to_string(stage)];
    i.received++;
    i.times.pop_back();
}
