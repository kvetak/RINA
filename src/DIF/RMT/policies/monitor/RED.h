/*
 * RED.h
 *
 *  Created on: 17. 11. 2014
 *      Author: cloq
 */

#ifndef RED_H_
#define RED_H_

#include "RMTQMonitorBase.h"

typedef std::map<RMTQueue*, double> REDParamMap;

class RED : public RMTQMonitorBase
{
  public:
    virtual void run(RMTQueue* queue);
    virtual void postQueueCreation(RMTQueue* queue);
    virtual void preQueueRemoval(RMTQueue* queue);

  private:
    REDParamMap qAvgLengths;
    REDParamMap qWeights;
    REDParamMap qProbabilities;
    REDParamMap qCounters;
};

#endif /* RED_H_ */
