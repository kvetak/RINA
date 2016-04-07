#pragma once

#include <omnetpp.h>

#include <string.h>

#include "DataTransferPDU.h"

using namespace std;

namespace Infection {

    class Infection;

    struct pduT {
        PDU * pdu;
        double wT;
    };

    class Flow {
        public :

            Flow(double startTime, string DIF, string SRC, string DST, string QoS, double rate, int avgPDU, int varPDU, int nParts, int nRec, int DstCepId);


            pduT getPDU(bool record);
            string QoS;
            double startTime;

        private :
            ConnectionId connID;
            Address srcAddr, dstAddr;
            static unsigned int cepID;

            double avgWT;
            int minS, maxS;
            int current, parts, rec;
            unsigned int fcepID, secNum;

    };

    class commMsg : public cMessage {
        public:
            Flow * f;

            commMsg(Flow * _f);


    };

    class Infection : public cSimpleModule{
          public:
                void finish();

          protected:
                virtual void initialize();
                virtual void handleMessage(cMessage *msg);

                vector<Flow *> flows;
                cModule * mod, * rmt;

                bool emitSignals;
                simsignal_t signal;

                double markIniT, markFinT, finTime;
    };
}
