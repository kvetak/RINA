#pragma once

#include <omnetpp.h>

#include <list>

namespace ModularMonitor {

using namespace std;

class SM_Burst {
public :
    SM_Burst();
    SM_Burst(simtime_t, unsigned int);
    void set(simtime_t, unsigned int);

    void in(unsigned int);

    double tic();
    double tic(unsigned int);

    simtime_t getTime(unsigned int);

protected :
    simtime_t duration;
    unsigned int size;

    unsigned int currentSize;
    list<unsigned int> pSizes;
    list<simtime_t> pTimes;

    void out();
};

}
