#pragma once

#include <omnetpp.h>
#include "DIF/RMT/RMTQueue.h"
#include "DIF/RMT/RMTPort.h"

class Int_MM_Out_Module : public cSimpleModule
{
    public:
        virtual ~Int_MM_Out_Module() {}

        virtual void pduInsertered(RMTQueue *, RMTPort *)         = 0;
        virtual void pduDropped(RMTQueue *, const cPacket *, RMTPort *) = 0;
        virtual void pduReleased(RMTQueue *, RMTPort *)           = 0;
        virtual void queueCreated(RMTQueue *, RMTPort *)          = 0;

        virtual RMTQueue * getnextQueue(RMTPort *)                = 0;
        virtual simtime_t  getnextTime(RMTPort *)                 = 0;
};
