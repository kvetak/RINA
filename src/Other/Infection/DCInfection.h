#pragma once

#include "Infection.h"
#include "DCAddr.h"

using namespace std;
using namespace NSPSimpleDC;


namespace Infection {
    class DCInfection;

    class DCInfection : public cSimpleModule {
          public:
          protected:
                virtual void initialize();
                virtual void handleMessage(cMessage *msg);

                virtual void setNext();
                PDU * getPDU();

                cModule * mod, * rmt;

                DCAddr Im, current;
                int pods, torXpod, fabricXpod, spineXfabric, edgeSets;
                bool toTors, toFabric, toSpines, toEdges;

                double interTime;
                int loopRem;

                ConnectionId connID;
                Address srcAddr, dstAddr;
    };
}
