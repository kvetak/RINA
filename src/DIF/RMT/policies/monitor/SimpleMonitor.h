/*
 * SimpleMonitor.h
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#ifndef SIMPLEMONITOR_H_
#define SIMPLEMONITOR_H_

#include "RMTQMonitorBase.h"

class SimpleMonitor : public RMTQMonitorBase
{
  public:
    virtual void run(RMTQueue* queue);
};

#endif /* SIMPLEMONITOR_H_ */
