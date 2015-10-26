#pragma once

#include <omnetpp.h>

#include <string.h>

#include "DataTransferPDU.h"

using namespace std;

namespace Infection {

    class Infection;


    class InfectionFlow
    {
      public:
        double bitWTime;
        int minPDU, maxPDU;

        ConnectionId connID;
        Address srcAddr, dstAddr;

        string QoS;

        long count;

        InfectionFlow(int bitRate, int avgPDU, int varPDU, string DIF, string SRC, string DST, string _QoS);

        DataTransferPDU* getPDU(Infection * parent);
    };

    class TimerMessage : public cMessage {
      public:
        InfectionFlow * inf;
        TimerMessage(InfectionFlow * _inf);
    };

    class Infection : public cSimpleModule
    {
      public:
        void recall(InfectionFlow *, double dt);
        void finish();

      protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

        vector<InfectionFlow * > infs;
    };

}
