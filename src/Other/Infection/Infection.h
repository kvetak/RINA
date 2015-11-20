#pragma once

#include <omnetpp.h>

#include <string.h>

#include "DataTransferPDU.h"

using namespace std;

namespace Infection {

    class Infection;

    class FlowInstance {
        public:
          static unsigned int cepID;

          unsigned int fcepID, secNum;
          FlowInstance();
    };

    class Flows {
        public:
            int lim;
            ConnectionId connID;
            Address srcAddr, dstAddr;

            int minPDU, maxPDU;

            vector<FlowInstance> flows;
            vector<FlowInstance>::iterator current;

            Flows(int _lim, int avgPDU, int varPDU, string DIF, string SRC, string DST, string QoS);
            Flows(int _lim, ConnectionId _connID, Address _srcAddr, Address _dstAddr, int _minPDU, int _maxPDU);

            void addFlow();
            Flows dup();
    };

    class PortFlows {
        public:
            double avgBitWt;
            int lim;
            vector<Flows> flows;

            PortFlows(double _avgBitWt);

            Flows * addFlows(int _lim, int avgPDU, int varPDU, string DIF, string SRC, string DST, string QoS);
            Flows * addFlows(Flows fls);

            PortFlows dup();
    };

    class commMsg : public cMessage {
    public:
        PortFlows * pf;

        commMsg(PortFlows * _pf);
    };

    class Infection : public cSimpleModule
    {
      public:
      //  void finish();

      protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

        vector<PortFlows> flows;

        double finTime;

        int partitions;

        bool emitSignals;
        simsignal_t signal;

        double markIniT, markFinT;
    };
}
    /*


    class InfectionFlows {
        double bitWTime;
        int minPDU, maxPDU;
        Address srcAddr, dstAddr;
        string QoS;
        ConnectionId connID;

        long count;

    };

    class InfectionFlow {
      public:
        static int cepID;

        int fcepID;

        long count;
        unsigned int secNum;
    };

    class InfectionFlow
    {
      public:
        static int cepID;

        int fcepID;

        long count;
        unsigned int secNum;

        InfectionFlow();

        DataTransferPDU* getPDU(Infection * parent, bool signaled);
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

        double finTime;

        int partitions;

        bool emitSignals;
        simsignal_t signal;

        double markIniT, markFinT;
    };
*/
