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

#ifndef ROUTINGNOTIFIERLISTENERES_H_
#define ROUTINGNOTIFIERLISTENERES_H_

#include <omnetpp.h>
#include "DIF/Routing/IntRoutingUpdate.h"
#include "DIF/Routing/RoutingNotifierBase.h"

class RoutingNotifierListeners : public cListener
{
    public:
        RoutingNotifierListeners(RoutingNotifierBase* rnb);
        virtual ~RoutingNotifierListeners();
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail)
        {
            EV << "Signal to RoutingNotifierBase initiated by " << src->getFullPath() << endl;
        }
    protected:
        RoutingNotifierBase* rnb;
};

class LisRIBDRoutingUpdate : public RoutingNotifierListeners
{
    public:
        LisRIBDRoutingUpdate(RoutingNotifierBase* nribd) : RoutingNotifierListeners(nribd) {};
        virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

#endif /* ROUTINGNOTIFIERLISTENERES_H_ */
