#include "DIF/RMT/Monitor/ModularMonitor/SM_Burst/SM_Burst.h"

namespace ModularMonitor {

SM_Burst::SM_Burst() {
    duration = 0.0;
    size = 1500;
    currentSize = 0;
}

SM_Burst::SM_Burst(simtime_t t, unsigned int s) {
    duration = t;
    size = s;
    currentSize = 0;
}

void SM_Burst::set(simtime_t t, unsigned int s) {
    duration = t;
    size = s;
}

void SM_Burst::in(unsigned int s) {
    pTimes.push_back(simTime()+duration);
    pSizes.push_back(s);
    currentSize += s;
}

void SM_Burst::out() {
    simtime_t c = simTime();

    while(!pTimes.empty() && c >= pTimes.front()){
        currentSize -= pSizes.front();
        pTimes.pop_front();
        pSizes.pop_front();
    }

}

double SM_Burst::tic() {
    out();
    return (double)currentSize/(double)size;
}

double SM_Burst::tic(unsigned int s) {
    out();
    return (double)(currentSize+s)/(double)size;
}

simtime_t SM_Burst::getTime(unsigned int s) {
    unsigned int freeSize = size - currentSize;

    auto tIt = pTimes.begin();
    auto sIt = pSizes.begin();

    while(tIt != pTimes.end() && sIt != pSizes.end()) {
        freeSize += *sIt;

        if(freeSize >= s) { return *tIt; }

        tIt++;
        sIt++;
    }

    return 0;
}

}
