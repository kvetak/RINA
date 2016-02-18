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

#include <QoSMultipathDynamicTable/QoSMultipathDynamicTable.h>
//#include "APN.h"



namespace QoSMultipathDynamicTable {

    using namespace std;

    entryT::entryT(): p(nullptr), BW(0) {}
    entryT::entryT(RMTPort * _p, int _bw): p(_p), BW(_bw) {}

    void iQoSMultipathDynamicTable::onPolicyInit() {

        mon = getRINAModule<ModularMonitor::ModularMonitor *>(this, 2, {MOD_RELAYANDMUX, MOD_POL_RMT_QMONITOR});

        cXMLElement* Xml = NULL;
        if (par("QoS_BW").xmlValue() != NULL && par("QoS_BW").xmlValue()->hasChildren()){
            Xml = par("QoS_BW").xmlValue();
        } else { error("QoS BW requirements not configured");}


        cXMLElementList QoSs = Xml->getChildrenByTagName("QoS");
        for(auto qos : QoSs){
            if (!qos->getAttribute("id")) { error("Error parsing QoS BW requirement. Its ID is missing!"); }
            std::string id = qos->getAttribute("id");
            if (id=="") { error("Error parsing QoS BW requirement. Queue ID cannot be empty!"); }

            if (!qos->getAttribute("bw")) { error("Error parsing QoS BW requirement. Its BW is missing!"); }
            int bw = atoi(qos->getAttribute("bw"));
            if (bw < 0) { error("Error parsing QoS BW requirement. Queue BW cannot < 0"); }

            QoS_BWreq[id] = bw;
        }

        onMainPolicyInit();
    }

    void iQoSMultipathDynamicTable::setPort(RMTPort * p, const int bw) {
        if(bw > 0) {
            Port_avBW[p] = bw;
        }
        else {
            Port_avBW.erase(p);
        }
        onSetPort(p, bw);
    }

    void iQoSMultipathDynamicTable::replacePort(RMTPort * oldP, RMTPort * newP, const int bw) {
        preReplacePort(oldP, newP, bw);
        Port_avBW.erase(oldP);
        if(bw > 0) {
            Port_avBW[newP] = bw;
        }
    }

}
