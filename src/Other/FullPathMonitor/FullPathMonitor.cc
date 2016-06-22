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
            vector<PathInfo> posiblePaths;
            vector<PathInfo> correctPaths;
            posiblePaths.push_back(PathInfo());
            posiblePaths.back().BW=QoS_BWreq[qos];
            posiblePaths.back().src=nodeIdOrg;
            posiblePaths.back().dst=nodeIdDst;
            posiblePaths.back().flowID=flowId;
            bool foundedPath = false;
            recursivePathFinder(nodeIdOrg, nodeIdDst, qos, flowId, posiblePaths, BWControl);
            vector<double> auxweightQoS(posiblePaths.size(),1);
            vector<double> auxweightTotal(posiblePaths.size(),1);
            for(auto it : posiblePaths){
                if (it.ok==true){
                    foundedPath=true;
                    correctPaths.push_back(it);
                }
            }
            if (foundedPath==true){
                for(unsigned i=0; i < correctPaths.begin()->steps.size(); i++){
                    vector<RMTPort *> steps;
                    for(auto it : correctPaths){
                        steps.push_back(it.steps[i].port);
                    }
                    for(unsigned j=0; j < correctPaths.size(); j++){
                        if(numberOfAppearances(steps,correctPaths[j].steps[i].port)){
                            if(auxweightTotal[j]>correctPaths[j].steps[i].TotalWeight){
                                auxweightTotal[j]=correctPaths[j].steps[i].TotalWeight;
                            }
                            if(auxweightQoS[j]>correctPaths[j].steps[i].QoSWeight){
                                auxweightQoS[j]=correctPaths[j].steps[i].QoSWeight;
                            }
                        }
                    }
                }

                vector<double> finalweight;
                double sum =0;
                for(unsigned i=0; i < correctPaths.size(); i++){
                    finalweight.push_back(auxweightQoS[i]*QoSFactor + auxweightTotal[i]*TotalFactor);
                    sum = sum + (auxweightQoS[i]*QoSFactor + auxweightTotal[i]*TotalFactor);
                }
                for (auto it : finalweight){
                    it=it/sum;
                }
                PathInfo auxPath = correctPaths[WeightedRandom(finalweight)];
                path->ok=auxPath.ok;
                path->steps=auxPath.steps;
                path->qos=qos;
                path->BW = QoS_BWreq[qos];
                path->src = nodeIdOrg;
                path->dst = nodeIdDst;
                path->flowID = flowId;
                orderedCache.addElement(*path);


                MonitorMsg * ackMsg = new MonitorMsg();
                ackMsg->setName("MonitorMsg");
                ackMsg->type="ACK";
                ackMsg->ackInfo.flowID=flowId;
                take(ackMsg);
                sendDirect(ackMsg, requestModule, "radioIn");

                for(auto it : path->steps){
                    BWControl.addBW(it.port, qos, QoS_BWreq[qos]);
                    MonitorMsg * monMsg = new MonitorMsg();
                    cEntry entry;
                    entry.QoS=qos;
                    entry.SrcCepId=flowId;
                    entry.dst=nodeIdDst;
                    entry.p=it.port;
                    entry.reqBW=QoS_BWreq[qos];
                    entry.t=simTime();
                    monMsg->setName("MonitorMsg");
                    monMsg->type="RSV";
                    monMsg->rsvInfo.entries.push_back(entry);
                    take(monMsg);
                    cModule *targetModule = getModuleByPath(nodeDataBase[it.nodeID].nodePath.c_str());
                    sendDirect(monMsg, targetModule, "radioIn");
                }
            }
            else{
                //Try to reroute
                vector<PathInfo> reroutePaths;
                reroutePaths.push_back(PathInfo());
                recursivePathFinder(nodeIdOrg, nodeIdDst, "rerouteQoS", flowId, reroutePaths, BWControl);
                PathInfo auxPath = reroute(reroutePaths, nodeIdOrg, nodeIdDst, qos, flowId);
                if(auxPath.ok==true){
                    numberOfReroutes++;
                    path->ok=auxPath.ok;
                    path->steps=auxPath.steps;
                    path->qos=qos;
                    path->BW = QoS_BWreq[qos];
                    path->src = nodeIdOrg;
                    path->dst = nodeIdDst;
                    path->flowID = flowId;
                    orderedCache.addElement(*path);
                    MonitorMsg * ackMsg = new MonitorMsg();
                    ackMsg->setName("MonitorMsg");
                    ackMsg->type="ACK";
                    ackMsg->ackInfo.flowID=flowId;
                    take(ackMsg);
                    sendDirect(ackMsg, requestModule, "radioIn");
                    for(auto it : path->steps){
                        MonitorMsg * monMsg = new MonitorMsg();
                        cEntry entry;
                        entry.QoS=qos;
                        entry.SrcCepId=flowId;
                        entry.dst=nodeIdDst;
                        entry.p=it.port;
                        entry.reqBW=QoS_BWreq[qos];
                        entry.t=simTime();
                        monMsg->setName("MonitorMsg");
                        monMsg->type="RSV";
                        monMsg->rsvInfo.entries.push_back(entry);
                        take(monMsg);
                        cModule *targetModule = getModuleByPath(nodeDataBase[it.nodeID].nodePath.c_str());
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
            }
        }
        else{
            MonitorMsg * nackMsg = new MonitorMsg();
            nackMsg->setName("MonitorMsg");
            nackMsg->type="NACK";
            nackMsg->nackInfo.flowID=flowId;
            take(nackMsg);
            sendDirect(nackMsg, requestModule, "radioIn");
        }
    }

    FullPathMonitor::PathInfo FullPathMonitor::reroute(vector<PathInfo> reroutePaths, string nodeIdOrg, string nodeIdDst, string qos, int flowId){

        BWcontrol BWaux = BWControl;
        map<int,RerouteInfo> changeList; //map<flowid,RerouteInfo>
        vector<pair<int,int>> jams(reroutePaths.size(),make_pair(0, 0));//pair<numberofJams, minBW>
        PathInfo finalPath;
        finalPath.ok=false;

        for(unsigned int i=0; i<reroutePaths.size(); i++){
            for(auto it2 : reroutePaths[i].steps){
                if((nodeDataBase[it2.nodeID].findEntrybyPort(it2.port)->BW-BWaux.getTotalBW(it2.port))<QoS_BWreq[qos]){
                    jams[i].first = jams[i].first + 1;
                    jams[i].second = jams[i].second + it2.freeBW;
                }
            }
        }
        vector<PathInfo> candidatesReroute;
        vector<pair<int,int>> candidatesjams;
        int min = INFINITY;
        for(unsigned int i = 0; i<reroutePaths.size(); i++){
            if(jams[i].first<min){
                candidatesReroute.clear();
                candidatesjams.clear();
                candidatesReroute.push_back(reroutePaths[i]);
                candidatesjams.push_back(jams[i]);
                min=jams[i].first;
            }
            else if(jams[i].first==min){
                candidatesReroute.push_back(reroutePaths[i]);
                candidatesjams.push_back(jams[i]);
            }
        }

        candidatesReroute=orderCandidatebyJam(candidatesjams, candidatesReroute);

        for(unsigned i=0; i < candidatesReroute.size(); i++){
            orderedList listAux = orderedCache;
            BWaux = BWControl;
            finalPath.steps.clear();
            changeList.clear();
            for(unsigned j=0; j < candidatesReroute[i].steps.size(); j++){
                if(candidatesReroute[i].steps[j].freeBW < QoS_BWreq[qos]){//Necessary to reroute
                    for(auto it : listAux.List){
                        if(it.steps[j].port==candidatesReroute[i].steps[j].port){//Try to reroute that flow
                            bool foundedPath = false;
                            vector<PathInfo> posiblePaths;
                            posiblePaths.push_back(PathInfo());
                            RemoveBW(it.steps, BWaux, it.qos);
                            recursivePathFinder(it.src, it.dst, it.qos, it.flowID, posiblePaths, BWaux);
                            for(unsigned int k = 0; k < posiblePaths.size(); k++){
                                if (posiblePaths[k].steps.size()>j)//cambiar i por j
                                {
                                    if(posiblePaths[k].steps[j].port==candidatesReroute[i].steps[j].port)
                                    {
                                        posiblePaths[k].ok=false;
                                    }
                                }
                            }
                            for(auto it2 : posiblePaths){
                                if (it2.ok==true){
                                    foundedPath=true;
                                }
                            }
                            if (foundedPath == true){//posible to reroute
                                RerouteInfo newchange;
                                newchange.pathOrg=it.steps;
                                newchange.pathDst=selectBetterReroute(it, posiblePaths).steps;
                                newchange.dst=it.dst;
                                newchange.flowID=it.flowID;
                                newchange.qos=it.qos;
                                newchange.src=it.src;
                                it.steps=newchange.pathDst;
                                if(changeList.count(newchange.flowID)==0){
                                    changeList[newchange.flowID]=newchange;
                                }
                                else{
                                    changeList[newchange.flowID].pathDst=newchange.pathDst;
                                }
                                AddBW(newchange.pathDst,BWaux,it.qos);
                                if((nodeDataBase[candidatesReroute[i].steps[j].nodeID].findEntrybyPort(candidatesReroute[i].steps[j].port)->BW-
                                        BWaux.getTotalBW(candidatesReroute[i].steps[j].port)) > QoS_BWreq[qos]){
                                    posiblePaths.clear();
                                    break;//enought BW
                                }
                            }
                            else{
                                AddBW(it.steps,BWaux,it.qos);
                            }
                            posiblePaths.clear();
                        }
                    }
                    if((nodeDataBase[candidatesReroute[i].steps[j].nodeID].findEntrybyPort(candidatesReroute[i].steps[j].port)->BW-
                            BWaux.getTotalBW(candidatesReroute[i].steps[j].port)) < QoS_BWreq[qos]){
                        finalPath.steps.clear();
                        break;
                    }
                    else{
                        BWaux.addBW(candidatesReroute[i].steps[j].port, qos, QoS_BWreq[qos]);
                        finalPath.steps.push_back(candidatesReroute[i].steps[j]);
                    }
                }
                else{
                    BWaux.addBW(candidatesReroute[i].steps[j].port, qos, QoS_BWreq[qos]);
                    finalPath.steps.push_back(candidatesReroute[i].steps[j]);
                }
            }
            if (finalPath.steps.size()>0)
            {
                BWControl=BWaux;
                finalPath.ok=true;
                orderedCache=listAux;
                ApplyChanges(changeList);
                return finalPath;
            }

        }
        finalPath.steps.clear();
        finalPath.ok=false;
        return finalPath;
    }

    void FullPathMonitor::ApplyChanges (map<int,RerouteInfo> changeList){
        map<string , list<cEntry>> addedEntries;
        map<string , list<cEntry>> removedEntries;
        for(auto it:changeList){
            cache[make_tuple(it.second.src, it.second.dst, it.second.flowID)].steps=it.second.pathDst;
            for(unsigned i =0; i< it.second.pathOrg.size(); i++)
            {
                if(it.second.pathOrg[i].port != it.second.pathDst[i].port){
                    cEntry entry;
                    entry.QoS=it.second.qos;
                    entry.SrcCepId=it.second.flowID;
                    entry.dst=it.second.dst;
                    entry.p=it.second.pathDst[i].port;
                    entry.reqBW=QoS_BWreq[entry.QoS];
                    entry.t=simTime();
                    addedEntries[it.second.pathDst[i].nodeID].push_back(entry);

                    entry.p=it.second.pathOrg[i].port;
                    removedEntries[it.second.pathOrg[i].nodeID].push_back(entry);

                }
            }
        }
        for(auto it2: removedEntries){
            MonitorMsg * monMsg = new MonitorMsg();
            monMsg->setName("MonitorMsg");
            monMsg->type="FREE";
            monMsg->rsvInfo.entries=it2.second;
            take(monMsg);
            cModule *targetModule = getModuleByPath(nodeDataBase[it2.first].nodePath.c_str());
            sendDirect(monMsg, targetModule, "radioIn");
        }
        for(auto it2: addedEntries){
            MonitorMsg * monMsg = new MonitorMsg();
            monMsg->setName("MonitorMsg");
            monMsg->type="RSV";
            monMsg->rsvInfo.entries=it2.second;
            take(monMsg);
            cModule *targetModule = getModuleByPath(nodeDataBase[it2.first].nodePath.c_str());
            sendDirect(monMsg, targetModule, "radioIn");
        }
    }

    vector<FullPathMonitor::PathInfo> FullPathMonitor::orderCandidatebyJam (vector<pair<int,int>> jams, vector<PathInfo> candidates){

        vector<PathInfo> orderedPaths;
        while(candidates.size()>0){
            int max=0;
            int position=0;
            for (unsigned int i=0; i<candidates.size(); i++){
                if(jams[i].second > max){
                    max=jams[i].second;
                    position=i;
                }
            }
            orderedPaths.push_back(candidates[position]);
            jams.erase(jams.begin()+position);
            candidates.erase(candidates.begin()+position);
        }
        return orderedPaths;
    }

    FullPathMonitor::PathInfo FullPathMonitor::selectBetterReroute (PathInfo orgPath, vector<PathInfo> posiblePaths){

        vector<int> distance (posiblePaths.size(),0);
        for(unsigned int i=0; i<posiblePaths.size(); i++){
            distance[i]=0;
        }
        for(unsigned int i=0; i<posiblePaths.size();i++){
            for(unsigned int j=0; j<posiblePaths[i].steps.size(); j++){
                if(posiblePaths[i].steps[j].port != orgPath.steps[j].port){
                    distance[i] = distance[i] + 1;
                }
            }
        }
        int min = INFINITY;
        vector<PathInfo> selectedPaths;
        for(unsigned int i=0; i<posiblePaths.size(); i++){
            if((distance[i]<min) and (posiblePaths[i].ok==true)){
                selectedPaths.clear();
                selectedPaths.push_back(posiblePaths[i]);
                min=distance[i];
            }
            else if((distance[i]==min) and (posiblePaths[i].ok==true)){
                selectedPaths.push_back(posiblePaths[i]);
            }
        }

        int minimunBW = INFINITY;
        PathInfo betterpath;
        for(unsigned i=0; i < selectedPaths.begin()->steps.size(); i++){
            vector<RMTPort *> steps;
            for(auto it : selectedPaths){
                steps.push_back(it.steps[i].port);
            }
            for(unsigned j=0; j < selectedPaths.size(); j++){
                if(numberOfAppearances(steps,selectedPaths[j].steps[i].port)){
                    if(selectedPaths[j].steps[i].freeBW < minimunBW){
                        minimunBW=selectedPaths[j].steps[i].freeBW;
                        betterpath = selectedPaths[j];
                    }
                }
            }
        }
        return betterpath;
    }

    void FullPathMonitor::UpdateBW(vector<stepInfo> orgPath, vector<stepInfo> dstPath, BWcontrol& BWdata, string qos){

        for(unsigned int i = 0; i<orgPath.size(); i++){
            if(orgPath[i].port!=dstPath[i].port){
                BWdata.addBW(dstPath[i].port, qos, QoS_BWreq[qos]);
                BWdata.removeBW(orgPath[i].port, qos, QoS_BWreq[qos]);
            }
        }

    }

    void FullPathMonitor::AddBW(vector<stepInfo> Path, BWcontrol& BWdata, string qos){
        for(unsigned int i = 0; i<Path.size(); i++){
            BWdata.addBW(Path[i].port, qos, QoS_BWreq[qos]);
        }
    }

    void FullPathMonitor::RemoveBW(vector<stepInfo> Path, BWcontrol& BWdata, string qos){
        for(unsigned int i = 0; i<Path.size(); i++){
            BWdata.removeBW(Path[i].port, qos, QoS_BWreq[qos]);
        }
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

    void FullPathMonitor::recursivePathFinder(string nodeIdOrg, string nodeIdDst, string qos, int flowId, vector<PathInfo>& posiblePaths, BWcontrol BWdata){
        if(nodeIdOrg.compare(nodeIdDst)==0){
            posiblePaths.back().ok=true;
        }
        else{
            if(nodeDataBase[nodeIdOrg].routingInfo.find(nodeIdDst)!=nodeDataBase[nodeIdOrg].routingInfo.end()){
                vector<entryT> * entries =  &(nodeDataBase[nodeIdOrg].routingInfo.at(nodeIdDst));
                vector<entryT> possibles;
                for( entryT & e : *entries) {
                    if ((e.BW - BWdata.getTotalBW(e.p)) >= QoS_BWreq[qos]){
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
                        stepInfo newstep;
                        newstep.QoSWeight=QoSocupation;
                        newstep.TotalWeight=Totalocupation;
                        newstep.nodeID=nodeIdOrg;
                        newstep.port=it.p;
                        newstep.freeBW=it.BW - BWdata.getTotalBW(it.p);
                        posiblePaths.back().steps.push_back(newstep);
                        //posiblePaths.back().steps.push_back(make_pair(make_pair(Totalocupation,QoSocupation),make_pair(nodeIdOrg, it.p)));
                        //posiblePaths.back().weight = posiblePaths.back().weight + ((double)(it.BW-(nodeDataBase[nodeIdOrg].schedulerInfo.at(qos)[it.p]))/(double)it.BW);
                        recursivePathFinder(nodeDataBase[nodeIdOrg].neighboursInfo.at(it.p), nodeIdDst, qos, flowId, posiblePaths, BWdata);
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
            BWControl.removeBW(it.port, path->qos, QoS_BWreq[path->qos]);
            MonitorMsg * monMsg = new MonitorMsg();
            cEntry entry;
            entry.QoS=path->qos;
            entry.SrcCepId=flowId;
            entry.dst=nodeIdDst;
            entry.p=it.port;
            entry.reqBW=QoS_BWreq[path->qos];
            entry.t=simTime();
            monMsg->setName("MonitorMsg");
            monMsg->type="FREE";
            monMsg->rsvInfo.entries.push_back(entry);
            take(monMsg);
            cModule *targetModule = getModuleByPath(nodeDataBase[it.nodeID].nodePath.c_str());
            sendDirect(monMsg, targetModule, "radioIn");
        }
        orderedCache.erraseElement(cache[make_tuple(nodeIdOrg, nodeIdDst, flowId)]);
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
                                      if(it2.port==it.first){
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

        map<RMTPort *, map<string, int>> portUsage;
        for(auto it : orderedCache.List){
            for(auto it2 : it.steps){
                if((portUsage.count(it2.port)>0)and(portUsage[it2.port].count(it.qos)>0)){
                    portUsage[it2.port][it.qos] = portUsage[it2.port][it.qos] + 1;
                }
                else{
                    portUsage[it2.port][it.qos] = 1;
                }
            }
        }
        EV << "-----------------" << endl;
        EV << "Cache table::" << endl;
        for(auto it : portUsage){
            float sum =0.0;
            EV << it.first->getFullPath()<<endl;
            for(auto it2 : it.second){
                EV<<"QoS: " << it2.first <<" "<<it2.second<< " flows" << endl;
                if(it2.first == "1"){
                    sum = sum + (0.4*(float)it2.second);
                }
                else if(it2.first == "2"){
                    sum = sum + (0.1*(float)it2.second);
                }
                else if(it2.first == "3"){
                    sum = sum + (0.01*(float)it2.second);
                }
            }
            EV<<endl;
            EV<< "Total Usage: " << sum << endl;
            EV<<endl;
        }
        EV << "Rejected Flows::" << endl;
        for(auto it : dropedFlows){
            EV << "Flow : " << it.first <<"\tTime: "<< it.second.str()<<endl;
        }
        EV <<endl;
        EV <<"Number of Successful reroutes: "<< numberOfReroutes<<endl;
        EV << "-----------------" << endl;

    }
}
