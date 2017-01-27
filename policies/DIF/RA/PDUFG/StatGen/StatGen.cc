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

#include "DIF/RA/PDUFG/StatGen/StatGen.h"

Register_Class(StatGen);

using namespace std;

// A new flow has been inserted/or removed
void StatGen::insertedFlow(const Address &addr, const QoSCube &qos, port_t port){

    int d = stoi(addr.getIpcAddress().getName());
    neis[d] = port;

    for(const auto & i : cTables) {
        const map<int, int> & T = i.second;
        for(const auto & j : T) {
            if(j.second == d) { fwd->setTentry(i.first, j.first, port); }
        }
    }
}

void StatGen::removedFlow(const Address &addr, const QoSCube& qos, port_t port){
    int d = stoi(addr.getIpcAddress().getName());
    neis.erase(d);

    for(const auto & i : cTables) {
        const map<int, int> & T = i.second;
        for(const auto & j : T) {
            if(j.second == d) { fwd->setTentry(i.first, j.first, nullptr); }
        }
    }
}

//Routing has processes a routing update
void StatGen::routingUpdated(){}

// Called after initialize
void StatGen::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<Q2FwdT *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    int maxTable = -1;
    int maxAddr = -1;

    //Read XML
    //Parsing Tables data
    if (par("TData").xmlValue() == nullptr || !par("TData").xmlValue()->hasChildren()) {
        error("lData parameter not initialized!");
    }
    cXMLElementList Tsets = par("TData").xmlValue()->getChildrenByTagName("Tset");
    for(cXMLElement* Tset : Tsets) {
        int src = -1, dst = -1;
        if (Tset->getAttribute("fail") != nullptr) {
            string f = Tset->getAttribute("fail");
            if(f != "") { sscanf (f.c_str(),"%d|%d",&src,&dst); }
            if(src < 0 || dst < 0) { error("Malformed failure identifier!"); }
        }

        map< int, map<int, int> > & Ts = fTables[src][dst];

        cXMLElementList entries = Tset->getChildrenByTagName("entry");
        for (cXMLElement* entry : entries) {
            int T = -1;
            int dst = -1;
            int next = -1;

            if (entry->getAttribute("T") != nullptr) {
                string v = entry->getAttribute("T");
                T = stoi(v);
            }
            if (entry->getAttribute("dst") != nullptr) {
                string v = entry->getAttribute("dst");
                dst = stoi(v);
            }
            if (entry->getAttribute("next") != nullptr) {
                string v = entry->getAttribute("next");
                next = stoi(v);
            }

            if(T < 0 || dst < 0 || next < 0) { error("Malformed table entry!"); }

            Ts[T][dst] = next;

            if(T > maxTable) { maxTable = T; }
            if(dst > maxAddr) { maxAddr = dst; }
        }
    }

    cTables = fTables[-1][-1];

    //Parsing Q2T data
    if (par("Q2T").xmlValue() == nullptr || !par("Q2T").xmlValue()->hasChildren()) {
        error("Q2T parameter not initialized!");
    }
    map<string, int> Q2T;

    cXMLElementList QoSs = par("Q2T").xmlValue()->getChildrenByTagName("QoS");
    for(cXMLElement* QoS : QoSs) {
        int T = -1;
        string id = "---";

        if (QoS->getAttribute("T") != nullptr) {
            string v = QoS->getAttribute("T");
            T = stoi(v);
        }
        if (QoS->getAttribute("id") != nullptr) {
            id = QoS->getAttribute("id");
        }

        if(id == "---" || T < 0 || T > maxTable) { error("Invalid Q2T entry!"); }

        Q2T[id] = T;
    }


    //Init fwd
    fwd->iniStructs(Q2T, maxTable+1, maxAddr+1);
}
