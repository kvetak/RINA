/*
 * ECNMarker.h
 *
 *  Created on: 15. 11. 2014
 *      Author: cloq
 */

#ifndef ECNMARKER_H_
#define ECNMARKER_H_

#include "RMTQMonitorBase.h"

class ECNMarker : public RMTMaxQBase
{
  public:
    virtual void run(RMTQueue* queue);
};

#endif /* ECNMARKER_H_ */
