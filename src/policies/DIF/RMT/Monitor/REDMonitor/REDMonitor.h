//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef REDMONITOR_H_
#define REDMONITOR_H_

#include "RMTQMonitorBase.h"

typedef std::map<RMTQueue*, double> REDParamMap;

class REDMonitor : public RMTQMonitorBase
{
  friend class REDDropper;

  public:
    virtual void onMessageArrival(RMTQueue* queue);
    virtual void postQueueCreation(RMTQueue* queue);
    virtual void preQueueRemoval(RMTQueue* queue);

  private:
    REDParamMap qAvgLengths;
    REDParamMap qWeights;
    REDParamMap qCounters;
};

#endif /* REDMONITOR_H_ */
