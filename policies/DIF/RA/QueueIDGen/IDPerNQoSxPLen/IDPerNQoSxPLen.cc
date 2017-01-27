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

#include "DIF/RA/QueueIDGen/IDPerNQoSxPLen/IDPerNQoSxPLen.h"
#include "DIF/RA/PDUFG/IPLSPDUFG/IPLSPDUFG.h"

using namespace std;

Define_Module(IDPerNQoSxPLen);

string IDPerNQoSxPLen::generateOutputQueueID(PDU* pdu)
{
    if(pdu->getConnId().getQoSId() == VAL_MGMTQOSID){
        return "M";
    }

    string qos = pdu->getConnId().getQoSId();

    int h = hCount[qos][pdu->getDstAddr().getIpcAddress().getName()] + pdu->getHopCount();
    if(h >= maxHCount) { h = maxHCount; }
    if(h <= 0) { h = 1; }

    return qos + "_" + to_string(h);
}

string IDPerNQoSxPLen::generateInputQueueID(PDU* pdu)
{
    if(pdu->getConnId().getQoSId() != VAL_MGMTQOSID){ return "M"; }
    return "Q";
}


void IDPerNQoSxPLen::initialize() {
    maxHCount = par("maxHCount").longValue();
    if(maxHCount <= 0) { maxHCount = 1; }

    cXMLElement* Xml = NULL;
    if (par("data").xmlValue() != NULL && par("data").xmlValue()->hasChildren()) {
        Xml = par("data").xmlValue();

        cXMLElementList nodeList = Xml->getChildrenByTagName("node");
        for(auto & node : nodeList) {
            if(!node->getAttribute("addr")) { error("node/addr parameter not initialized!"); }
            if(!node->getAttribute("qos")) { error("node/qos parameter not initialized!"); }
            if(!node->getAttribute("d")) { error("node/d parameter not initialized!"); }

            string addr = node->getAttribute("addr");
            string qos = node->getAttribute("qos");
            int d = atoi(node->getAttribute("d"));
            if(d <= 0) { d = 1; }

            hCount[qos][addr] = d;
        }
    }

    IPLSPDUFG * genMod = check_and_cast<IPLSPDUFG *>
        (getModuleByPath(par("genModPath").stdstringValue().c_str()));
    genMod->registerQidsGen(this);

}

void IDPerNQoSxPLen::finalize() {
    IPLSPDUFG * genMod = check_and_cast<IPLSPDUFG *>
        (getModuleByPath(par("genModPath").stdstringValue().c_str()));
    genMod->unregisterQidsGen(this);
}

void IDPerNQoSxPLen::setDistance(string addr, string qos, int d) {
    hCount[qos][addr] = d;
}
