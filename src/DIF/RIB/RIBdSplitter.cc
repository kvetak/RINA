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

#include "RIBdSplitter.h"

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
    FaiTable = ModuleAccess<FAITable>(MOD_FAITABLE).get();
}
