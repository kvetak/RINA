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
bool FlowContainer::operator<(const FlowContainer &o) const {
    if(f < o.f) { return true; }
    if(f > o.f) { return false; }
    if(ra < o.ra) { return true; }
    return false;
}

bool FlowContainer::operator==(const FlowContainer & o) const {
    return (f == o.f && ra == o.ra);
}

void FlowListener::initialize() {
    getParentModule()->subscribe(SIG_RA_CreateFlowPositive, this);
    killTime = par("killTime").doubleValue();
    killTimeVar = par("killTimeVar").doubleValue();
    killCount = par("killCount");

    if(killCount > 0 && killTime > simTime().dbl()) {
        kM = new cMessage("Kill");
        scheduleAt(killTime, kM);
    } else {  kM = nullptr; }


    if (par("killList").xmlValue() == NULL || !par("killList").xmlValue()->hasChildren()){
        return;
    }

    cXMLElement* Xml = par("killList").xmlValue();
    cXMLElementList kFl = Xml->getChildrenByTagName("Flow");
    for(auto kf : kFl){
        string src = kf->getAttribute("src");
        string dst = kf->getAttribute("dst");
        cout << "request to kill "<< src <<" -> "<< dst <<endl;

        killReq[src].insert(dst);
    }
}

void FlowListener::handleMessage(cMessage *msg) {
    Enter_Method_Silent();

    if(!kflows.empty()){
        auto f = kflows.back();
        kflows.pop_back();
        std::cout << "!!!---Remove flow "<<
                f.f->getSrcAddr() << " -> " << f.f->getDstAddr() << endl<< endl;
        f.ra->sleepFlow(f.f, -1);
    } else if(killCount > 0) {
        if(flows.empty()) {
            cerr << "All flows removed, requested to remove "<<killCount << " more flows" << endl;
            killCount = 0;
        } else {
            int r = intuniform(0, flows.size()-1);
            auto f = flows[r];
            if(r == (int)flows.size()-1) {
                flows[r] = flows.back();
                flows.pop_back();
            }
            std::cout << "!!!---Remove flow "<<
                    f.f->getSrcAddr() << " -> " << f.f->getDstAddr() << endl<< endl;
            f.ra->sleepFlow(f.f, -1);
            killCount--;
        }
    }

    if(!kflows.empty() || killCount > 0) {
        scheduleAt(killTimeVar+simTime(), msg);
    } else {
        delete kM;
        kM = nullptr;
    }
}

void FlowListener::receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) {
    Enter_Method_Silent();

    Flow * f = dynamic_cast<Flow*>(obj);
    RA * ra = dynamic_cast<RA*>(source);

    bool added = false;

    string src = f->getSrcAddr().getIpcAddress().getName();
    string dst = f->getSrcAddr().getIpcAddress().getName();
    if(killReq.find(src) != killReq.end()){
        auto & ks = killReq[src];
        if(ks.find("*") != ks.end() || ks.find(dst) != ks.end()) {
            kflows.push_back(FlowContainer(f,  ra));
            added = true;
        }
    }
    if(!added && killReq.find(dst) != killReq.end()){
        auto & ks = killReq[dst];
        if(ks.find("*") != ks.end() || ks.find(src) != ks.end()) {
            kflows.push_back(FlowContainer(f,  ra));
            added = true;
        }
    }

    if(!added && killCount > 0 && killTime > simTime().dbl()) {
        flows.push_back(FlowContainer(f,  ra));
        added = true;
    }

    if(added && kM == nullptr) {
        simtime_t now = simTime();
        kM = new cMessage("Kill");
        if(killTime > now.dbl()) {
            scheduleAt(killTime, kM);
        } else {
            scheduleAt(now, kM);
        }
    }

}
