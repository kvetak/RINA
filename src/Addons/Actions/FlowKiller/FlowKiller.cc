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

#include "Addons/Actions/FlowKiller/FlowKiller.h"

Define_Module(FlowKiller);


FlowContainer::FlowContainer(Flow * _f, RA * _ra):f(_f), ra(_ra){}
bool FlowContainer::operator<(const FlowContainer &o) const {
    if(f < o.f) { return true; }
    if(f > o.f) { return false; }
    if(ra < o.ra) { return true; }
    return false;
}

bool FlowContainer::operator==(const FlowContainer & o) const {
    return (f == o.f && ra == o.ra);
}

void FlowKiller::initialize() {
    getParentModule()->subscribe(SIG_RA_CreateFlowPositive, this);
    killTime = par("killTime").doubleValue();
    killCount = par("killCount");

    if(killCount > 0 && killTime > simTime().dbl()) {
        scheduleAt(killTime, new cMessage("Kill flows"));
    }
}

void FlowKiller::handleMessage(cMessage *msg) {
    Enter_Method_Silent();
    for(int i = 0; i < killCount; i++) {
        if(flows.empty()) {
            cerr << "All flows removed, requested to remove "<<(killCount-i) << " more flows" << endl;
            break;
        }

        int r = omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0, flows.size()-1);
        auto f = flows[r];
        if(r == (int)flows.size()-1) {
            flows[r] = flows.back();
            flows.pop_back();
        }
        f.ra->sleepFlow(f.f, -1);
    }
    delete msg;
}

void FlowKiller::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    Enter_Method_Silent();
    if(killCount > 0 && killTime > simTime().dbl()) {
        Flow * f = dynamic_cast<Flow*>(obj);
        RA * ra = dynamic_cast<RA*>(source);
        flows.push_back(FlowContainer(f,  ra));
    }
}
