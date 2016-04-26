#include "FullPathMonitor.h"
#include <iostream>
#include <fstream>


Define_Module(FullPathMonitor::FullPathMonitor);

namespace FullPathMonitor {

    void FullPathMonitor::initialize(){
        cXMLElement* Xml = NULL;
        if (par("QoS_BW").xmlValue() != NULL && par("QoS_BW").xmlValue()->hasChildren()){
           Xml = par("QoS_BW").xmlValue();
        } else { error("QoS BW requirements not configured");}


        cXMLElementList QoSs = Xml->getChildrenByTagName("QoS");
        for(auto qos : QoSs){
           if (!qos->getAttribute("id")) { error("Error parsing QoS BW requirement. Its ID is missing!"); }
           std::string id = qos->getAttribute("id");
           if (id=="") { error("Error parsing QoS BW requirement. Queue ID cannot be empty!"); }

           if (!qos->getAttribute("bw")) { error("Error parsing QoS BW requirement. Its BW is missing!"); }
           int bw = atoi(qos->getAttribute("bw"));
           if (bw < 0) { error("Error parsing QoS BW requirement. Queue BW cannot < 0"); }

           QoS_BWreq[id] = bw;
        }
    }

    void FullPathMonitor::lookPath(string nodeIdOrg, string nodeIdDst, string qos, int flowId){
        RMTPort * next = nullptr;
        cEntry * e = &cache[nodeIdDst][flowId];
        string QoSid;
        next = e->p;
        if(next == nullptr) {
            posiblePaths.push_back(PathInfo());
            recursivePathFinder(nodeIdOrg, nodeIdDst, qos, flowId);
            vector<double> auxweight;
            long double sum = 0;
            for(auto it : posiblePaths) {
                if(it.ok){
                    auxweight.insert(auxweight.end(),it.weight);
                    sum = sum + it.weight;
                }
            }
            for(vector<double>::iterator it2 = auxweight.begin(); it2 != auxweight.end(); it2++){
                *it2 = (*it2)/sum;//Normalization
            }
            PathInfo* finalPath;
            finalPath = &posiblePaths[WeightedRandom(auxweight)];
            for(auto it : finalPath->steps){

            }
        }

    }

    void FullPathMonitor::recursivePathFinder(string nodeIdOrg, string nodeIdDst, string qos, int flowId){
        if(nodeIdOrg.compare(nodeIdDst)==0){
            posiblePaths.back().ok=true;
        }
        else{
            if(nodeDataBase[nodeIdOrg].routingInfo->find(nodeIdDst)!=nodeDataBase[nodeIdOrg].routingInfo->end()){
                vector<entryT> * entries =  &(nodeDataBase[nodeIdOrg].routingInfo->at(nodeIdDst));
                vector<entryT> possibles;
                for( entryT & e : *entries) {
                    if ((e.BW - BWControl.getTotalBW(e.p)) >= QoS_BWreq[qos]){
                        possibles.push_back(e);
                    }
                }
                PathInfo auxpath = posiblePaths.back();
                if (!possibles.empty()){
                    for(auto it : possibles){
                        if (it.p != possibles.begin()->p){
                            posiblePaths.push_back(auxpath);
                        }
                        posiblePaths.back().steps.push_back(make_pair(nodeIdOrg, it.p));
                        posiblePaths.back().weight = posiblePaths.back().weight + nodeDataBase[nodeIdOrg].schedulerInfo->at(qos)[it.p];
                        recursivePathFinder(nodeDataBase[nodeIdOrg].neighboursInfo->at(it.p), nodeIdDst, qos, flowId);
                    }
                }
            }
        }
    }

    unsigned int FullPathMonitor::WeightedRandom(vector<double> &weight){

        double sum = 0;
        std::random_device rd;
        std::mt19937 gen(rd());
        for (unsigned int i=0; i<weight.size(); i++){
                sum = sum + weight[i];
            }
        std::uniform_real_distribution<double> generator(0.0, sum);

        if(sum == 0)
        {
            return 0;
        }
        double rnd = generator(gen);
        for (unsigned int i=0; i<weight.size(); i++){

            if(rnd < weight[i]){
                return i;
            }
            else{
                rnd = rnd - weight[i];
            }
        }
        return 0;//Never should end here
    }

    void FullPathMonitor::registerNode(RegisterInfo info){
        nodeDataBase[info.nodeId]=info;
    }

    void FullPathMonitor::handleMessage(cMessage * msg){

        MultipathStructs::MonitorMsg * monMsg = dynamic_cast<MultipathStructs::MonitorMsg *>(msg);
        if(monMsg->type.compare("Register_Node")==0){
            registerNode(monMsg->regInfo);
        }
        else if(monMsg->type.compare("Monitoring_Param")==0){
            //Codigo
        }
        else if(monMsg->type.compare("Rsv_Req")==0){
            lookPath(monMsg->rsvInfo.nodeIdOrg, monMsg->rsvInfo.nodeIdDst, monMsg->rsvInfo.qos, monMsg->rsvInfo.flowId);
        }
        else if(monMsg->type.compare("Free_Req")==0){
            //Codigo
        }
        else if(monMsg->type.compare("Ack")==0){
            //Codigo
        }
        else{
            EV << "Incorrect Message" << endl;
        }
//        EV << "Mensaje recibido" << endl;
//        cModule *targetModule = getModuleByPath("InfectedMultipathFatTree.AS1.relayIpc.relayAndMux.rmt");
//        MonitorMsg *msg2 = new MonitorMsg("MonitorMsg");
//        msg2->setType("ack");
//        take(msg2);
//        sendDirect(msg2, targetModule, "radioIn");

    }
    void FullPathMonitor::finish(){

    }
}
