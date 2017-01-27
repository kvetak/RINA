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

#include "DIF/RIB/RIBdSplitter.h"

Define_Module(RIBdSplitter);

void RIBdSplitter::initialize()
{
    FaiTable = NULL;
    initPointers();
}

void RIBdSplitter::handleMessage(cMessage *msg)
{
    //Output gate pointer
    cGate* out;

    //From CDAP
    if(strstr(msg->getArrivalGate()->getName(), GATE_CDAPIO) != NULL) {
        /*
         * FIXME: Vesely
         * After huge debate with John, we understand now, that reliability of management
         * traffic is done by N-1 flow. Thus, N-management flow exist WITHOUT dedicated
         * exchange of M_CREATE messages. This implies that all mgmt traffic is sent
         * through MockEFCPI. However, one day there may be use-case when we will do not
         * trust N-1 flow and want to provide additional reliability or encryption. Hence,
         * I am just commenting out the code instead of removing it.
         */

        //CDAPMessage* cdapmsg = check_and_cast<CDAPMessage*>(msg);
        //FAITableEntry* tfe = FaiTable->findMgmtEntryByDstNeighbor(cdapmsg->getDstAddr());
        //if (tfe
        //        && !dynamic_cast<CDAP_M_Create*>(msg)
        //        //&& tfe->getCFlow()->getSrcPortId() != VAL_UNDEF_PORTID
        //        //&& tfe->getCFlow()->getDstPortId() != VAL_UNDEF_PORTID
        //    ) {
        //    std::ostringstream ribdName;
        //    ribdName << GATE_EFCPIO_ << tfe->getCFlow()->getSrcPortId();
        //    out = this->gateHalf(ribdName.str().c_str(), cGate::OUTPUT);
        //}
        //else {
        //    EV << "Message sent out via mock EFCP instance!" << endl;
            out = this->gateHalf(GATE_EFCPIO, cGate::OUTPUT);
        //}
    }
    //From EFCP or RMT
    else {
        out = gateHalf(GATE_CDAPIO, cGate::OUTPUT);
    }

    //Send through appropriate gate
    send(msg, out);
}

void RIBdSplitter::initPointers() {
    FaiTable = getRINAModule<NFlowTable*>(this, 2, {MOD_FLOWALLOC, MOD_NFLOWTABLE});
}
