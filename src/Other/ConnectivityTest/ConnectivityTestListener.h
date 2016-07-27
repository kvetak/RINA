#pragma once

#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include <set>
#include <map>

using namespace std;


struct info_t {
    int sent, received;
    vector<simtime_t> times;
    info_t() : sent(0), received(0) {};
};

class ConnectivityTestListener : public cSimpleModule {
public:
    void initialize();
    virtual void finish();

    static ConnectivityTestListener * instance;

    void sent(const string & src, const string & dst, const string & qos, const int & stage);
    void received(const string & src, const string & dst, const string & qos, const int & stage, const simtime_t & sentAt);

protected:
    map<string, info_t > dataInfo;
};

