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

    void FullPathMonitor::lookPath(string nodeIdOrg, string nodeIdDst, string qos, int flowId, cModule * requestModule){

        PathInfo* path = &cache[make_tuple(nodeIdOrg, nodeIdDst, flowId)];

        if(path->steps.size()==0){
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
            auto auxPath = posiblePaths[WeightedRandom(auxweight)];
            path->ok=auxPath.ok;
            path->steps=auxPath.steps;
            path->weight=auxPath.weight;
            path->qos=qos;
        }

        MonitorMsg * ackMsg = new MonitorMsg();
        ackMsg->setName("MonitorMsg");
        ackMsg->type="ACK";
        ackMsg->ackInfo.flowID=flowId;
        take(ackMsg);
        sendDirect(ackMsg, requestModule, "radioIn");

        for(auto it : path->steps){
            BWControl.addBW(it.second, qos, QoS_BWreq[qos]);
            MonitorMsg * monMsg = new MonitorMsg();
            cEntry entry;
            entry.QoS=qos;
            entry.SrcCepId=flowId;
            entry.dst=nodeIdDst;
            entry.p=it.second;
            entry.reqBW=QoS_BWreq[qos];
            entry.t=simTime();
            monMsg->setName("MonitorMsg");
            monMsg->type="RSV";
            monMsg->rsvInfo.entry=entry;
            take(monMsg);
            cModule *targetModule = getModuleByPath(nodeDataBase[it.first].nodePath.c_str());
            sendDirect(monMsg, targetModule, "radioIn");
        }
        posiblePaths.clear();

    }

    void FullPathMonitor::recursivePathFinder(string nodeIdOrg, string nodeIdDst, string qos, int flowId){
        if(nodeIdOrg.compare(nodeIdDst)==0){
            posiblePaths.back().ok=true;
        }
        else{
            if(nodeDataBase[nodeIdOrg].routingInfo.find(nodeIdDst)!=nodeDataBase[nodeIdOrg].routingInfo.end()){
                vector<entryT> * entries =  &(nodeDataBase[nodeIdOrg].routingInfo.at(nodeIdDst));
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
                        posiblePaths.back().weight = posiblePaths.back().weight + nodeDataBase[nodeIdOrg].schedulerInfo.at(qos)[it.p];
                        recursivePathFinder(nodeDataBase[nodeIdOrg].neighboursInfo.at(it.p), nodeIdDst, qos, flowId);
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
        MonitorMsg * monMsg = new MonitorMsg();
        monMsg->setName("MonitorMsg");
        monMsg->type="MONITORING_CONFIG";
        monMsg->monConfigInfo.ForwardingMonFrec=par("ForwardingMonFrec").doubleValue();
        monMsg->monConfigInfo.LinksMonFrec=par("ForwardingMonFrec").doubleValue();
        monMsg->monConfigInfo.SchedulerMonFrec=par("ForwardingMonFrec").doubleValue();
        monMsg->monConfigInfo.SchedulerMonThres=par("ForwardingMonFrec").doubleValue();
        take(monMsg);
        cModule *targetModule = getModuleByPath(info.nodePath.c_str());
        sendDirect(monMsg, targetModule, "radioIn");

    }

    void FullPathMonitor::deletePath(string nodeIdOrg, string nodeIdDst, int flowId){


        PathInfo * path = &cache[make_tuple(nodeIdOrg, nodeIdDst, flowId)];
        for(auto it : path->steps){
            BWControl.removeBW(it.second, path->qos, QoS_BWreq[path->qos]);
            MonitorMsg * monMsg = new MonitorMsg();
            cEntry entry;
            entry.QoS=path->qos;
            entry.SrcCepId=flowId;
            entry.dst=nodeIdDst;
            entry.p=it.second;
            entry.reqBW=QoS_BWreq[path->qos];
            entry.t=simTime();
            monMsg->setName("MonitorMsg");
            monMsg->type="FREE";
            monMsg->rsvInfo.entry=entry;
            take(monMsg);
            cModule *targetModule = getModuleByPath(nodeDataBase[it.first].nodePath.c_str());
            sendDirect(monMsg, targetModule, "radioIn");
        }
        cache.erase(make_tuple(nodeIdOrg, nodeIdDst, flowId));

    }

    void FullPathMonitor::handleMessage(cMessage * msg){

        MultipathStructs::MonitorMsg * monMsg = dynamic_cast<MultipathStructs::MonitorMsg *>(msg);
        if(monMsg->type.compare("Register_Node")==0){
            registerNode(monMsg->regInfo);
        }
        else if(monMsg->type.compare("Monitor_Param")==0){
            if(nodeDataBase.count(monMsg->monitorParamInfo.nodeId)>0){
                if(monMsg->monitorParamInfo.neighboursInfo!=nullptr){
                   //nodeDataBase[monMsg->monitorParamInfo.nodeId].neighboursInfo=monMsg->monitorParamInfo.neighboursInfo;
                   auto nodeInfo = nodeDataBase[monMsg->monitorParamInfo.nodeId].neighboursInfo;
                   for (auto it : *(monMsg->monitorParamInfo.neighboursInfo)){
                       if(nodeInfo.count(it.first)==0){
                           nodeInfo.insert(it);
                       }
                   }
                   if (nodeInfo.size()>monMsg->monitorParamInfo.neighboursInfo->size()){//eliminated liks

                       for(auto it : nodeInfo){
                           if(monMsg->monitorParamInfo.neighboursInfo->count(it.first)==0){
                               for(auto it1 : cache){
                                  for(auto it2 : it1.second.steps){
                                      if(it2.second==it.first){
                                          deletePath(get<0>(it1.first), get<1>(it1.first), get<2>(it1.first));
                                      }
                                  }
                              }
                           }
                       }
                   }

                }
                if(monMsg->monitorParamInfo.routingInfo!=nullptr){
                    nodeDataBase[monMsg->monitorParamInfo.nodeId].routingInfo=*(monMsg->monitorParamInfo.routingInfo);
                }
                if(monMsg->monitorParamInfo.schedulerInfo!=nullptr){
                    nodeDataBase[monMsg->monitorParamInfo.nodeId].schedulerInfo=*(monMsg->monitorParamInfo.schedulerInfo);
                }
            }
        }
        else if(monMsg->type.compare("Rsv_Req")==0){
            cModule * requestModule = monMsg->getSenderModule();
            lookPath(monMsg->rsv_ReqInfo.nodeIdOrg, monMsg->rsv_ReqInfo.nodeIdDst, monMsg->rsv_ReqInfo.qos, monMsg->rsv_ReqInfo.flowId, requestModule);
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
        delete msg;

    }
    void FullPathMonitor::finish(){

    }
}
