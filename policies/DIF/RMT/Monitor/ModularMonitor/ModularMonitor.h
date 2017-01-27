//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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
#pragma once

#include "DIF/RMT/Monitor/SmartMonitor/SmartMonitor.h"
#include "DIF/RMT/Monitor/ModularMonitor/Int_MM_Out_Module.h"
#include "DIF/RMT/Monitor/ModularMonitor/Int_MM_Drop_Module.h"

namespace ModularMonitor {

using namespace std;

class ModularMonitor : public SmartMonitor
{
public:
    void onPolicyInit();
    void postPDUInsertion(RMTQueue* queue);
    void onMessageDrop(RMTQueue* queue, const cPacket* pdu);
    void prePDURelease(RMTQueue* queue);
    void postQueueCreation(RMTQueue* queue);

    double getInDropProb(RMTQueue * queue);
    double getOutDropProb(RMTQueue * queue);

    RMTQueue* getNextInput(RMTPort* port);
    RMTQueue* getNextOutput(RMTPort* port);

    simtime_t getInNextTime(RMTPort * port);
    simtime_t getOutNextTime(RMTPort * port);

protected:
    Int_MM_Out_Module  * inOutModule;
    Int_MM_Drop_Module * inDropModule;
    Int_MM_Out_Module  * outOutModule;
    Int_MM_Drop_Module * outDropModule;

    bool emitSignals;
    simsignal_t signal;
    map<const cPacket *, simtime_t> inTime;
    map<const cPacket *, int> inPos;
    map<RMTPort *, int> portServed;
};

}
