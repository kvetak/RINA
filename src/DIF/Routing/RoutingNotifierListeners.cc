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

#include "DIF/Routing/RoutingNotifierListeners.h"

RoutingNotifierListeners::RoutingNotifierListeners(RoutingNotifierBase* rnb) :
        rnb(rnb)
{
}

RoutingNotifierListeners::~RoutingNotifierListeners()
{
    rnb = NULL;
}

void LisRIBDRoutingUpdate::receiveSignal(cComponent* src, simsignal_t id,
        cObject* obj, cObject *detail)
{
    EV << "LisRIBDRoutingUpdate initiated by " << src->getFullPath()
            << " and processed by " << rnb->getFullPath() << endl;

    IntRoutingUpdate * info = dynamic_cast<IntRoutingUpdate *>(obj);

    if (info)
    {
        rnb->receiveRoutingUpdateFromRouting(info);
    }
    else
    {
        EV << "ForwardingInfoUpdate listener received unknown object!" << endl;
    }
}
