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

#include "DIF/RA/PDUFG/BiDomainGenerator/BiDomainGenerator.h"
#include "Common/APN.h"
#include "Common/Utils.h"



namespace BiDomainGenerator {

Register_Class(BiDomainGenerator);

using namespace std;

// A new flow has been inserted/or removed
void BiDomainGenerator::insertedFlow(const Address &addr, const QoSCube &qos, RMTPort * port){

    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].insert(port);
    if(neighbours[dst].size() == 1){
        pAddr parsedA = parseAddr(dst);
        if(parsedA.domain != ""){
            rt->addFlow(addr, "", parsedA.domain, 1);
            rt->addFlow(addr, parsedA.domain, parsedA.addr,1);
        } else {
            rt->addFlow(addr, parsedA.domain, parsedA.addr,1);
        }

        routingUpdated();
    }
}
void BiDomainGenerator::removedFlow(const Address &addr, const QoSCube& qos, RMTPort * port){
    std::string dst = addr.getIpcAddress().getName();
    neighbours[dst].erase(port);
    if(neighbours[dst].size() <= 0){
        pAddr parsedA = parseAddr(dst);

        if(parsedA.domain != ""){
            rt->removeFlow(addr, "", parsedA.domain);
            rt->removeFlow(addr, parsedA.domain, parsedA.addr);
        } else {
            rt->removeFlow(addr, parsedA.domain, parsedA.addr);
        }

        neighbours.erase(dst);

        routingUpdated();
    }
}

//Routing has processes a routing update
void BiDomainGenerator::routingUpdated(){
    DMRnms::dmUpdateM changes = rt->getChanges();
    for(DMRnms::dmUpdateMIt it = changes.begin(); it!= changes.end(); it++){
        for(DMRnms::s2AIt eIt = it->entries.begin(); eIt != it->entries.end(); eIt++){

            std::string dst = eIt->first;
            std::string nextHop = eIt->second.getIpcAddress().getName();

            EV << "Entry ::: \""<< it->domain << "\"/\""<< dst << "\" -> " << nextHop << " ("<< eIt->second<<")" <<endl;
            RMTPort * p = NULL;

            NTableIt n = neighbours.find(nextHop);
            if(nextHop != "" && n != neighbours.end()){
                p = *(n->second.begin());
            }

            if(p == NULL) {
                fwd->remove(it->domain, dst);
            } else {
                fwd->insert(it->domain, dst, p);
            }

        }
    }
}

// Called after initialize
void BiDomainGenerator::onPolicyInit(){
    //Set Forwarding policy
    fwd = getRINAModule<DomainTable::DomainTable *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_PDUFWD});

    rt = getRINAModule<DMRnms::Routing *>(this, 2, {MOD_POL_ROUTING});

    string myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();

    vector<string> parsStr = split(myAddr, '.');
    if(parsStr.size() != 2) {
        error("BiDomainGenerator own address must be on the form A.B");
    }
    myPrefix = parsStr[0];
    mySufix = parsStr[1];

    string alg0 = par("alg0").stdstringValue();
    string alg1 = par("alg1").stdstringValue();

    fwd->addDomain(myPrefix);
    fwd->addDomain("");

    if(alg0 == "LS"){
        rt->addDomain("", myPrefix, DMRnms::LS);
    } else {
        rt->addDomain("", myPrefix, DMRnms::DV);
    }

    if(alg1 == "LS"){
        rt->addDomain(myPrefix, mySufix, DMRnms::LS);
    } else {
        rt->addDomain(myPrefix, mySufix, DMRnms::DV);
    }


    difA = getRINAModule<DA *>(this, 3, {MOD_DIFALLOC, MOD_DA});
}

pAddr BiDomainGenerator::parseAddr(const string &addr){
    vector<string> sep = split(addr, '.');
    if(isPrefix(myPrefix, addr)){
        if(sep.size()>=2) {
            return pAddr(myPrefix, sep[1]);
        } else {
            return pAddr(myPrefix, "");
        }
    } else {
        return pAddr("", sep[0]);
    }
}

}
