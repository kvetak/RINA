#include "FullPathMonitor.h"
#include <iostream>
#include <fstream>
#include <cmath>

Define_Module(FullPathMonitor::FullPathMonitor);

namespace FullPathMonitor {

    void FullPathMonitor::initialize(){

        QoSFactor = par("QoSFactor").doubleValue();
        TotalFactor = par("TotalFactor").doubleValue();

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
            bool foundedPath = false;
            recursivePathFinder(nodeIdOrg, nodeIdDst, qos, flowId);
            vector<double> auxweightQoS;
            vector<double> auxweightTotal;
            for(auto it : posiblePaths){
                auxweightTotal.push_back(1);
                auxweightQoS.push_back(1);
                if (it.ok==true){
                    foundedPath=true;
                }
            }
            if (foundedPath==true){
                for(unsigned i=0; i < posiblePaths.begin()->steps.size(); i++){
                    vector<RMTPort *> steps;
                    for(auto it : posiblePaths){
                        steps.push_back(it.steps[i].second.second);
                    }
                    for(unsigned j=0; j < posiblePaths.size(); j++){
                        if(numberOfAppearances(steps,posiblePaths[j].steps[i].second.second)==1){
                            if(auxweightTotal[j]>posiblePaths[j].steps[i].first.first){
                                auxweightTotal[j]=posiblePaths[j].steps[i].first.first;
                            }
                            if(auxweightQoS[j]>posiblePaths[j].steps[i].first.second){
                                auxweightQoS[j]=posiblePaths[j].steps[i].first.second;
                            }
                        }
                    }
                }

                vector<double> finalweight;
                double sum =0;
                for(unsigned i=0; i < posiblePaths.size(); i++){
                    finalweight.push_back(auxweightQoS[i]*QoSFactor + auxweightTotal[i]*TotalFactor);
                    sum = sum + (auxweightQoS[i]*QoSFactor + auxweightTotal[i]*TotalFactor);
                }
                for (auto it : finalweight){
                    it=it/sum;
                }
                auto auxPath = posiblePaths[WeightedRandom(finalweight)];
                path->ok=auxPath.ok;
                path->steps=auxPath.steps;
                path->qos=qos;
            }

            MonitorMsg * ackMsg = new MonitorMsg();
            ackMsg->setName("MonitorMsg");
            ackMsg->type="ACK";
            ackMsg->ackInfo.flowID=flowId;
            take(ackMsg);
            sendDirect(ackMsg, requestModule, "radioIn");

            for(auto it : path->steps){
                BWControl.addBW(it.second.second, qos, QoS_BWreq[qos]);
                MonitorMsg * monMsg = new MonitorMsg();
                cEntry entry;
                entry.QoS=qos;
                entry.SrcCepId=flowId;
                entry.dst=nodeIdDst;
                entry.p=it.second.second;
                entry.reqBW=QoS_BWreq[qos];
                entry.t=simTime();
                monMsg->setName("MonitorMsg");
                monMsg->type="RSV";
                monMsg->rsvInfo.entry=entry;
                take(monMsg);
                cModule *targetModule = getModuleByPath(nodeDataBase[it.second.first].nodePath.c_str());
                sendDirect(monMsg, targetModule, "radioIn");
            }
        }
        else{
            MonitorMsg * nackMsg = new MonitorMsg();
            nackMsg->setName("MonitorMsg");
            nackMsg->type="NACK";
            nackMsg->nackInfo.flowID=flowId;
            take(nackMsg);
            sendDirect(nackMsg, requestModule, "radioIn");
            dropedFlows[flowId]=simTime();
        }
        posiblePaths.clear();

    }

    unsigned FullPathMonitor::numberOfAppearances (vector<RMTPort *> Vector, RMTPort * Port){

        unsigned count = 0;
        for (auto it : Vector){
            if (it == Port){
                count ++;
            }
        }
        return count;
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
                        double QoSocupation = (double)(it.BW-(nodeDataBase[nodeIdOrg].schedulerInfo[it.p].qosUsage[qos])) /(double)it.BW;
                        double Totalocupation = (double)(it.BW-(nodeDataBase[nodeIdOrg].schedulerInfo[it.p].totalUsage)) /(double)it.BW;
                        posiblePaths.back().steps.push_back(make_pair(make_pair(Totalocupation,QoSocupation),make_pair(nodeIdOrg, it.p)));
                        //posiblePaths.back().weight = posiblePaths.back().weight + ((double)(it.BW-(nodeDataBase[nodeIdOrg].schedulerInfo.at(qos)[it.p]))/(double)it.BW);



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
            BWControl.removeBW(it.second.second, path->qos, QoS_BWreq[path->qos]);
            MonitorMsg * monMsg = new MonitorMsg();
            cEntry entry;
            entry.QoS=path->qos;
            entry.SrcCepId=flowId;
            entry.dst=nodeIdDst;
            entry.p=it.second.second;
            entry.reqBW=QoS_BWreq[path->qos];
            entry.t=simTime();
            monMsg->setName("MonitorMsg");
            monMsg->type="FREE";
            monMsg->rsvInfo.entry=entry;
            take(monMsg);
            cModule *targetModule = getModuleByPath(nodeDataBase[it.second.first].nodePath.c_str());
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
                                      if(it2.second.second==it.first){
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
        else if(monMsg->type.compare("Free")==0){
            deletePath(monMsg->freeInfo.nodeIdOrg, monMsg->freeInfo.nodeIdDst, monMsg->freeInfo.flowId);
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

        map<RMTPort *, long> portUsage;
        for(auto it : cache){
            for(auto it2 : it.second.steps){
                if(portUsage.count(it2.second.second)>0){
                    portUsage[it2.second.second] = portUsage[it2.second.second] + QoS_BWreq[it.second.qos];
                }
                else{
                    portUsage[it2.second.second] = QoS_BWreq[it.second.qos];
                }
            }
        }
        EV << "-----------------" << endl;
        EV << "Cache table::" << endl;
        for(auto it : portUsage){
            EV << it.first->getFullPath()<<" : "<<it.second<<" bps"<<endl;
        }
        EV << "Rejected Flows::" << endl;
        for(auto it : dropedFlows){
            EV << "Flow : " << it.first <<"\tTime: "<< it.second.str()<<endl;
        }


    }
}
