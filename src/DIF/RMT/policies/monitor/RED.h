/*
 * RED.h
 *
 *  Created on: 17. 11. 2014
 *      Author: cloq
 */

#ifndef RED_H_
#define RED_H_

#include "RMTQMonitorBase.h"

class RED : public RMTQMonitorBase
{
  public:
    virtual void run(RMTQueue* queue);
};

#endif /* RED_H_ */
