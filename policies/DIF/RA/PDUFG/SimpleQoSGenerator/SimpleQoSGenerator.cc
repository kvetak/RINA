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

#include <SimpleQoSGenerator/SimpleQoSGenerator.h>
#include "APN.h"



namespace SimpleQoSGenerator {

Register_Class(SimpleQoSGenerator);

using namespace std;
using namespace QoSMultipathTable;


void SimpleQoSGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    nEntry * e = &neighbours[dst];

    if (port != nullptr)
    {
        int bw = qos.getAvgBand();
        if(e->best.p == nullptr) {
            fwd->setPort(port, bw);
            e->best.BW = bw;
            e->best.p = port;
        } else if(e->best.BW < bw) {
            fwd->replacePort(e->best.p, port, bw);
            e->best.BW = bw;
            e->best.p = port;
        }

        e->entries.push_back(entryT(port, bw));

        if(e->entries.size() == 1){
            rt->insertFlow(addr, dst, "", 1);
            routingUpdated();
        }
    }
}
void SimpleQoSGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    nEntry * e = &neighbours[dst];
    //int aux=e->entries.size();
    //for(auto it = e->entries.begin(); it != e->entries.end();) {
    auto it = e->entries.begin();
    while (it != e->entries.end()){
        if(it->p == port) {
            auto tIt = it;
            //it++;
            e->entries.erase(tIt);
            //aux=e->entries.size();
        } else { it++; }
    }

    if(e->best.p == port) {
        e->best.p = nullptr;
        e->best.BW = 0;
        for(auto et : e->entries) {
            if(e->best.BW <= et.BW) {
                e->best = et;
            }
        }

        if(e->best.p != nullptr) {
            fwd->replacePort(port, e->best.p, e->best.BW);
        } else {
            fwd->setPort(port, 0);
            rt->removeFlow(addr, dst, "");
            routingUpdated();
        }
    }
}

void SimpleQoSGenerator::routingUpdated(){
    auto changes = rt->getChanges();

    for(auto & dst : changes[""]) {
        std::vector< entryT > ps;

        for(auto nx : dst.second.nh) {
            if(nx != "") {
                auto n = neighbours[nx].best;
                if(n.p != nullptr) {
                    ps.push_back(n);
                }
            }
        }
        fwd->addReplace(dst.first, ps);
    }
}

void SimpleQoSGenerator::onPolicyInit(){
    fwd = getRINAModule<iQoSMultipathTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});
    rt = getRINAModule<IntTSimpleRouting<mType> *>(this, 2, {MOD_POL_ROUTING});

    difA = getRINAModule<DA*>(this, 3, {MOD_DIFALLOC, MOD_DA});

    mType infMetric = par("infinite");
    rt->setInfinite(infMetric);
}

}
