#pragma once

#include <omnetpp.h>

#include <string.h>
#include <queue>

#include "DataTransferPDU.h"
#include "InfectionSignals.h"

using namespace std;

namespace T2Infection {

    class T2Infection;

    struct pduT { InfectedDataTransferPDU * pdu; double wT; bool sig; };

    class Flow {
        public :
            Flow(string DIF, string SRC, string DST, string QoS);
            void setCepId(int id);
            void iniRate(double _avgWtXbit, double var);
            void iniPduSize(unsigned int min, unsigned int max);
            void markStatus(bool status);
            void listenStatus(bool status);

            pduT getPDU();
            double randomWait();

//        private :
            ConnectionId connID;
            Address srcAddr, dstAddr;

            bool mark, listening;

            double avgWtXbit, minWtXbit, maxWtXbit;
            unsigned int minPdusize, maxPduSize;
            double secNum;
    };

    class commMsg : public cMessage {
        public:
            Flow * f;
            commMsg(Flow * _f);
    };

    class T2Infection : public cSimpleModule{
          public:
                void finish();

          protected:
                virtual void initialize();
                virtual void handleMessage(cMessage *msg);

                vector<Flow> flows;
                cModule * mod, * rmt;

                cMessage * start, * stop;
                cMessage * listen, * finlisten;
                cMessage * timer;

                simsignal_t signal;

                double wtXbit;
                queue<InfectedDataTransferPDU *> q;

                long data;
    };
}
