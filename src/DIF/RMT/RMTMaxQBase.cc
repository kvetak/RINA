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

#include <RMTMaxQBase.h>

Define_Module(RMTMaxQBase);


void RMTMaxQBase::initialize()
{
    qMonPolicy = check_and_cast<RMTQMonitorBase*>
        (getModuleByPath("^.queueMonitorPolicy"));

    addrComparator = check_and_cast<AddressComparatorBase*>
            (getModuleByPath("^.^.resourceAllocator.addressComparator"));

    rmtAllocator = check_and_cast<RMTModuleAllocator*>
        (getModuleByPath("^.rmtModuleAllocator"));

    // register slowdown signal for RA
    sigRMTSDReq = registerSignal(SIG_RMT_SlowdownRequest);

    // display active policy name
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    onPolicyInit();
}

void RMTMaxQBase::onPolicyInit()
{
}

void RMTMaxQBase::handleMessage(cMessage *msg)
{

}

bool RMTMaxQBase::run(RMTQueue* queue)
{
    return false;
}

void RMTMaxQBase::notifySenderOfCongestion(const cPacket* pdu)
{
    emit(sigRMTSDReq, pdu);
}
