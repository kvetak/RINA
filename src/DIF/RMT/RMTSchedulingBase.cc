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

#include <RMTSchedulingBase.h>

Define_Module(RMTSchedulingBase);

void RMTSchedulingBase::initialize()
{
    rmtAllocator = check_and_cast<RMTModuleAllocator*>
        (getModuleByPath("^.allocator"));

    // display active policy name
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    onPolicyInit();
}

void RMTSchedulingBase::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() && !opp_strcmp(msg->getFullName(), "processPort"))
    { // TODO: this is lousy, think of something better
        RMTQueueType direction = (RMTQueueType)msg->par("direction").longValue();
        const char* portName = msg->par("portName").stringValue();
        RMTPort* port = rmtAllocator->getPort(portName);
        if (port != NULL)
        {
            processQueues(port, direction);
        }
        else
        {
            EV << "RMT Scheduler reinvocation: Port " << portName
               << " ceased to exist!" << endl;
        }
    }

    delete msg;
}

void RMTSchedulingBase::onPolicyInit()
{
}

void RMTSchedulingBase::scheduleReinvocation(simtime_t time, RMTPort* port, RMTQueueType direction)
{
    // TODO: this is lousy, think of something better
    cMessage* msg = new cMessage("processPort");
    msg->addPar("portName");
    msg->par("portName").setStringValue(port->getParentModule()->getFullName());

    msg->addPar("direction");
    msg->par("direction").setLongValue(direction);

    scheduleAt(time, msg);
}

void RMTSchedulingBase::processQueues(RMTPort* port, RMTQueueType direction)
{
}
