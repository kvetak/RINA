// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "DIF/Routing/SimpleRouting/SimpleLS/SimpleLS.h"

namespace SimpleLS {

Register_Class(SimpleLS);

using namespace std;


RoutingUpdate::RoutingUpdate(const Address &_addr, const std::string &_qos):IntRoutingUpdate(_addr){
    qos = _qos;
}

std::string RoutingUpdate::getQoS(){
    return qos;
}

void RoutingUpdate::addEntry(const std::string & id, linksU links){
    entries.insert(linksStEntry(id, links));
}

void RoutingUpdate::setEntries(linksSt _entries){
    RoutingUpdate::entries = _entries;
}

linksStIt RoutingUpdate::entriesBegin(){
    return entries.begin();
}
linksStIt RoutingUpdate::entriesEnd(){
    return entries.end();
}


//Flow inserted/removed
void SimpleLS::insertFlow(const Address &addr, const std::string &dst, const std::string& qos, const unsigned short &metric){
    neig[qos][addr] = metric;
    lastChanges[qos].insert(myAddr);
    secId++;
    linksU * myEntry = &(netState[qos][myAddr]);
    myEntry->sId = secId;
    myEntry->links[dst] = metric;
    scheduleUpdate();
}
void SimpleLS::removeFlow(const Address &addr, const std::string &dst, const std::string& qos){
    neig[qos].erase(addr);
    if(neig[qos].size() <= 0){
        neig.erase(qos);
    }
    lastChanges[qos].insert(myAddr);
    secId++;
    linksU * myEntry = &(netState[qos][myAddr]);
    myEntry->sId = secId;
    myEntry->links.erase(dst);
    scheduleUpdate();
}


void SimpleLS::scheduleUpdate(){
    Enter_Method_Silent();
    if(!scheduledUpdate){
        scheduledUpdate = true;
        scheduleAt(simTime()+1, new cMessage("Time2Update"));
    }
}


//Get Changes
entries2Next SimpleLS::getChanges(){
    entries2Next ret;
    for(linksStColIt qosIt = netState.begin(); qosIt != netState.end(); qosIt++){
        std::string qos = qosIt->first;
        TreeNode t = constructTree(qosIt->second);
        for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++){
            entType * et = &ret[qosPaddr(qos, (*it)->addr)];
            et->metric = (*it)->metric;
            et->nh.insert((*it)->addr);
            addRecursive(ret, qos, (*it)->addr, *it);
        }
    }

    entries2Next t = ret;

    for(entries2NextIt tIt = table.begin(); tIt != table.end(); tIt++){
        if (ret[tIt->first].metric == tIt->second.metric && ret[tIt->first].nh == tIt->second.nh){
            ret.erase(tIt->first);
        }
    }
    table = t;

    return ret;
}

entries2Next SimpleLS::getAll(){
    entries2Next ret;

    for(linksStColIt qosIt = netState.begin(); qosIt != netState.end(); qosIt++){
        std::string qos = qosIt->first;
        TreeNode t = constructTree(qosIt->second);
        for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++){
            entType * et = &ret[qosPaddr(qos, (*it)->addr)];
            et->metric = (*it)->metric;
            et->nh.insert((*it)->addr);
            addRecursive(ret, qos, (*it)->addr, *it);
        }
    }

    table = ret;
    return table;
}

TreeNode SimpleLS::constructTree(linksSt &ls){
    TreeNode t(myAddr, 0);
    aMap added;
    added[myAddr] = 0;

    wMap waiting;
    aMap * links = &(ls[myAddr].links);
    for(linksIt it = links->begin(); it !=links->end(); it++){
        waiting[it->first] = psT(&t, it->second);
    }

    while(!waiting.empty()){
        unsigned short min = UINT16_MAX;
        addrList mins;

        for (wMapIt it = waiting.begin(); it != waiting.end(); it++){
            if(it->second.metric < min){
                min = it->second.metric;
                mins.clear();
            }
            if(it->second.metric == min){
                mins.push_back(it->first);
            }
        }

        while(!mins.empty()){
            string addr = mins.back();
            mins.pop_back();

            psT ps = waiting[addr];
            waiting.erase(addr);

            TreeNode * nt = new TreeNode(addr, ps.metric);
            bool fPar = true;
            for(TreeNode * par : ps.p){
                if(fPar) {
                    par->chldel.insert(nt);
                    fPar = false;
                }
                par->chl.insert(nt);
            }


            added[addr] = ps.metric;

            links = &(ls[addr].links);

            for(linksIt it = links->begin(); it !=links->end(); it++){
                string daddr = it->first;
                if(added.find(daddr) == added.end()){
                    wMapIt eI = waiting.find(daddr);
                    if(eI == waiting.end()){
                        waiting[daddr] = psT(nt, ps.metric + it->second);
                    } else if(eI->second.metric >= ps.metric + it->second){
                        eI->second.addParent(nt, ps.metric + it->second);
                    }
                }
            }
        }
    }

    return t;
}
void SimpleLS::addRecursive(entries2Next &ret, const std::string& qos, const std::string &next, TreeNode * t){
    for(TreeNodeIt it = t->chl.begin(); it != t->chl.end(); it++){
        entType * et = &ret[qosPaddr(qos, (*it)->addr)];
        et->metric = (*it)->metric;
        et->nh.insert(next);
        addRecursive(ret, qos, next, *it);
    }
}

//Process a Routing Update, return true => inform FWDG of the update
bool SimpleLS::processUpdate(IntRoutingUpdate * update){
    RoutingUpdate * up = check_and_cast<RoutingUpdate*>(update);

    std::string qos = up->getQoS();
    linksSt * st = &(netState[qos]);

    for(linksStIt it = up->entriesBegin(); it != up->entriesEnd(); it++){
        string node = it->first;
        if((*st)[node].sId < it->second.sId){
            (*st)[node] = it->second;
            lastChanges[qos].insert(node);
        }
    }
    if(!lastChanges.empty()){
        scheduleUpdate();
        return true;
    }
    return false;
}

// Called after initialize
void SimpleLS::onPolicyInit(){
    myAddr = par("myAddr").stdstringValue();
    if(myAddr == "") {
        myAddr = myAddress.getIpcAddress().getName();
    }

    infMetric = par("infMetric").longValue();
    secId = 1;
}


void SimpleLS::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        //Iterate all Qos
        for(qosNeighMetricIt it = neig.begin(); it!= neig.end(); it++){
            //get Changes per QoS;
            linksSt _entries = getChangedEntries (it->first);

            //iterate all Qos->Neighbour
            for(neighMetricIt it2 = it->second.begin(); it2 != it->second.end(); it2++){
                //New Update to QoS + Neighbour
                RoutingUpdate * update = new RoutingUpdate(it2->first, it->first);

                //Add entries
                update->setEntries(_entries);

                //And send
                sendUpdate(update);
            }
        }

        lastChanges.clear();
        scheduledUpdate = false;
    }
    delete msg;
}

linksSt SimpleLS::getChangedEntries (const std::string& qos){
    linksSt ret;
    addrSet * set = &lastChanges[qos];
    for(addrSetIt it = set->begin(); it != set->end(); it++){
        ret.insert(linksStEntry(*it, netState[qos][*it]));
    }
    return ret;
}


void SimpleLS::finish(){
    IntRouting::finish();

    if(par("printAtEnd").boolValue() ){
        EV << "I'm "<< myAddr<<endl;

        for(linksStColIt qosIt = netState.begin(); qosIt != netState.end(); qosIt++){
            EV << "  QoS " << qosIt->first<<endl;
            TreeNode t = constructTree(qosIt->second);

            for(TreeNodeIt it = t.chl.begin(); it != t.chl.end(); it++){
                printTreeNode(*it, (*it)->addr);
            }

        }
    }
}

void SimpleLS::printTreeNode(TreeNode *t, const std::string &next){
    for(int i = 0; i < t->metric; i++) { EV <<" ";}
    EV<<"    " << t->addr << " -> "<<next << " ("<<t->metric<<") " << " childs: "<< t->chl.size() << endl;
    for(TreeNodeIt it = t->chl.begin(); it != t->chl.end(); it++){
        printTreeNode(*it, next);
    }
}

}
