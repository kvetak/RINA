#pragma once
#include <omnetpp.h>
#include <iostream>
#include <fstream>
#include <math.h>

#include "MultipathStructs.h"

namespace FullPathMonitor {

    using namespace std;
    using namespace MultipathStructs;

    class FullPathMonitor  : public cSimpleModule {

    public:

        void initialize();
        void finish();

    private:


        struct stepInfo{
            double TotalWeight;
            double QoSWeight;
            string nodeID;
            RMTPort * port;
            int freeBW;
            stepInfo(){
                TotalWeight=0.0;
                QoSWeight=0.0;
                nodeID="";
                port=nullptr;
                freeBW=INFINITY;
            }
        };
        struct PathInfo{
            vector<stepInfo> steps;
            //list< pair<pair<TotalWeight,QoSWeight>,pair<nodeID, Port>>> steps;
            bool ok;
            string qos;
            int BW;
            string src;
            string dst;
            int flowID;
            PathInfo(){
                ok = false;
                qos="";
                BW=0;
            }
        };

        struct RerouteInfo{
            vector<stepInfo> pathOrg;
            vector<stepInfo> pathDst;
            //list< pair<pair<TotalWeight,QoSWeight>,pair<nodeID, Port>>> steps;
            int flowID;
            string qos;
            string src;
            string dst;
            RerouteInfo(){
                flowID = 0;
                qos="";
                src="";
                dst="";
            }
        };


        struct orderedList{
            list<PathInfo*> List;

            void addElement (PathInfo* entry){
                if (List.empty()){
                    List.push_front(entry);
                }
                else{
                    for(list<PathInfo*>::iterator it=List.begin(); it!=List.end(); it++){
                        if(entry->BW >= (*it)->BW){
                            List.insert(it, entry);
                            break;
                        }
                    }
                    List.push_back(entry);
                }
            }
            void erraseElement (PathInfo* entry){
                for(list<PathInfo*>::iterator it=List.begin(); it!=List.end(); it++){
                    if(entry == (*it)){
                        List.erase(it);
                    }
                }
            }
        };


        double QoSFactor;
        double TotalFactor;
        orderedList orderedCache;
        void registerNode(RegisterInfo info);
        void handleMessage(cMessage * msg);
        void lookPath(string nodeIdOrg, string nodeIdDst, string qos, int flowId, cModule * requestModule);
        void recursivePathFinder(string nodeIdOrg, string nodeIdDst, string qos, int flowId, vector<PathInfo> &posiblePaths, BWcontrol BWdata);
        bool reroute(vector<PathInfo> reroutePaths, string nodeIdOrg, string nodeIdDst, string qos, int flowId);
        void deletePath(string nodeIdOrg, string nodeIdDst, int flowId);
        unsigned int WeightedRandom(vector<double> &weight);
        unsigned numberOfAppearances (vector<RMTPort *> Vector, RMTPort * Port);
        PathInfo selectBetterReroute (PathInfo orgPath, vector<PathInfo> posiblePaths);
        void UpdateBW(vector<stepInfo> orgPath, vector<stepInfo> dstPath, BWcontrol& BWdata, string qos);

        map<string, int> QoS_BWreq;
        BWcontrol BWControl;
        map<string, RegisterInfo> nodeDataBase;
        //vector<PathInfo> posiblePaths;
        map<tuple<string, string, int>, PathInfo> cache; //map<tuple<org,dst,flowid>, pathInfo>
        map<int, simtime_t> dropedFlows; //map<flowId, time>

    };
}
