#pragma once
#include <omnetpp.h>
#include <iostream>
#include <fstream>

#include "MultipathStructs.h"

namespace FullPathMonitor {

    using namespace std;
    using namespace MultipathStructs;

    class FullPathMonitor  : public cSimpleModule {

    public:

        void initialize();
        void finish();

    private:
        struct PathInfo{
            vector< pair<pair<double,double>,pair<string, RMTPort *>>> steps;
            //list< pair<pair<TotalWeight,QoSWeight>,pair<nodeID, Port>>> steps;
            bool ok;
            string qos;
            PathInfo(){
                ok = false;
                qos="";
            }
        };
        double QoSFactor;
        double TotalFactor;
        void registerNode(RegisterInfo info);
        void handleMessage(cMessage * msg);
        void lookPath(string nodeIdOrg, string nodeIdDst, string qos, int flowId, cModule * requestModule);
        void recursivePathFinder(string nodeIdOrg, string nodeIdDst, string qos, int flowId);
        void deletePath(string nodeIdOrg, string nodeIdDst, int flowId);
        unsigned int WeightedRandom(vector<double> &weight);
        unsigned numberOfAppearances (vector<RMTPort *> Vector, RMTPort * Port);

        map<string, int> QoS_BWreq;
        BWcontrol BWControl;
        map<string, RegisterInfo> nodeDataBase;
        vector<PathInfo> posiblePaths;
        map<tuple<string, string, int>, PathInfo> cache; //map<tuple<org,dst,flowid>, pathInfo>
        map<int, simtime_t> dropedFlows; //map<flowId, time>

    };
}
