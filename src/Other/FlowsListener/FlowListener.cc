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

#include "FlowListener.h"

Define_Module(FlowListener);


FlowContainer::FlowContainer(Flow * _f, RA * _ra):f(_f), ra(_ra){}

void FlowListener::initialize() {
    getParentModule()->subscribe(SIG_RA_CreateFlowPositive, this);
}

void FlowListener::handleMessage(cMessage *msg) {
    Enter_Method_Silent();
    if(FlowContainer * fc = dynamic_cast<FlowContainer*> (msg) ) {
        std::cout << "At "<< simTime()
                <<" sleep flow " << fc->f->getSrcAddr() << " -> "
                << fc->f->getDstAddr() << " / "
                << fc->f-> getConId().getQoSId() << endl;

        fc->ra->sleepFlow(fc->f, simTime() + 5.2);
    }
    delete msg;
}

void FlowListener::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    Enter_Method_Silent();
    Flow * f = dynamic_cast<Flow*>(obj);
    std::cout << "At "<< simTime()
            <<" new flow " << f->getSrcAddr()
            << " -> " << f->getDstAddr() << " / "
            << f-> getConId().getQoSId() << endl;

    RA * ra = dynamic_cast<RA*>(source);

    if(uniform(0,10) <= 1) {
        scheduleAt(simTime()+15.2, new FlowContainer(f,  ra));
    }
}
