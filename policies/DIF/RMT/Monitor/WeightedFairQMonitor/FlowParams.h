/*
 * FlowParams.h
 *
 *  Created on: Apr 15, 2015
 *      Author: gaixas1
 */

#ifndef FLOWPARAMS_H_
#define FLOWPARAMS_H_

#include <list>
#include <omnetpp.h>

namespace FWQ {

using namespace std;

class FlowParams {
public:
    FlowParams();
    FlowParams(const double &rate);
    virtual ~FlowParams();

    void setMinRate(const double &rate);
    void insert(const int &size);
    void removeLast();
    void removeFirst();

    simtime_t getFirstFinTime();
    simtime_t getLastFinTime();

protected:
    double minRate;
    simtime_t lastFinTime, prevLastFinTime;
    list< simtime_t > vFinTimes;
};

} /* namespace FWQ */

#endif /* FLOWPARAMS_H_ */
