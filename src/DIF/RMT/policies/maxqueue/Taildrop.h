/*
 * SimpleMonitor.h
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#ifndef TAILDROP_H_
#define TAILDROP_H_

#include "RMTQMonitorBase.h"

class Taildrop : public RMTMaxQBase
{
  public:
    virtual void run(RMTQueue* queue);
};

#endif /* TAILDROP_H_ */
