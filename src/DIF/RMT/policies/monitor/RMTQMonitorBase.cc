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

#include <RMTQMonitorBase.h>

Define_Module(RMTQMonitorBase);

RMTQMonitorBase::RMTQMonitorBase()
{
}

RMTQMonitorBase::~RMTQMonitorBase()
{
}

void RMTQMonitorBase::initialize()
{
    // display active policy name
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    onPolicyInit();
}

void RMTQMonitorBase::handleMessage(cMessage *msg)
{
}

void RMTQMonitorBase::onPolicyInit()
{
}

void RMTQMonitorBase::postQueueCreation(RMTQueue* queue)
{
}

void RMTQMonitorBase::preQueueRemoval(RMTQueue* queue)
{
}

void RMTQMonitorBase::run(RMTQueue* queue)
{
}
