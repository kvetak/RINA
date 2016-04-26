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
            list< pair<string, RMTPort *>> steps;
            double weight;
            bool ok;
            PathInfo(){
                weight = 0;
                ok = false;
            }
        };
        void registerNode(RegisterInfo info);
        void handleMessage(cMessage * msg);
        void lookPath(string nodeIdOrg, string nodeIdDst, string qos, int flowId);
        void recursivePathFinder(string nodeIdOrg, string nodeIdDst, string qos, int flowId);
        unsigned int WeightedRandom(vector<double> &weight);

        map<string, int> QoS_BWreq;
        BWcontrol BWControl;
        map<string, RegisterInfo> nodeDataBase;
        vector<PathInfo> posiblePaths;
        map<string, map<int, cEntry>> cache; //map<dst, map<flowidentifier(SrcCepId), entry>>

    };
}
