/*
 * FlowParams.cc
 *
 *  Created on: Apr 15, 2015
 *      Author: gaixas1
 */

#include <WeightedFairQMonitor/FlowParams.h>

namespace FWQ {

FlowParams::FlowParams() {
    minRate = 0;
    lastFinTime = 0;
    prevLastFinTime = 0;
}

FlowParams::FlowParams(const double &rate) {
    minRate = rate;
    lastFinTime = 0;
    prevLastFinTime = 0;
}

FlowParams::~FlowParams() {}

void FlowParams::setMinRate(const double &rate){
    minRate = rate;
}

void FlowParams::insert(const int &size){
    simtime_t vStartTime = simTime();
    if(!vFinTimes.empty() && vStartTime<lastFinTime){
        vStartTime = lastFinTime;
    }
    prevLastFinTime = lastFinTime;
    lastFinTime = vStartTime + minRate*size;
    vFinTimes.push_back(lastFinTime);
}

void FlowParams::removeLast(){
    lastFinTime = prevLastFinTime;
    vFinTimes.pop_back();
}
void FlowParams::removeFirst(){
    vFinTimes.pop_front();
}

simtime_t FlowParams::getFirstFinTime() {
    if(vFinTimes.empty()){
        return DBL_MAX;
    } else {
        return vFinTimes.front();
    }
}
simtime_t FlowParams::getLastFinTime() {
    if(vFinTimes.empty()){
        return DBL_MAX;
    } else {
        return vFinTimes.back();
    }
}
} /* namespace FWQ */
