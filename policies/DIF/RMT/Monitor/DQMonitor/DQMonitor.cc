//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include <DQMonitor.h>

namespace DQMonitor {

Define_Module(DQMonitor);

void DQMonitor::onPolicyInit() {

    //Parsing L data
    if (par("lData").xmlValue() != NULL
            && par("lData").xmlValue()->hasChildren()) {
        parseL(par("lsData").xmlValue());
    } else {
        error("lData parameter not initialized!");
    }


    //Parsing C data
    if (par("cData").xmlValue() != NULL
            && par("cData").xmlValue()->hasChildren()) {
        parseC(par("cData").xmlValue());
    } else {
        error("cData parameter not initialized!");
    }


    //Parsing U data
    if (par("uData").xmlValue() != NULL
            && par("uData").xmlValue()->hasChildren()) {
        parseU(par("uData").xmlValue());
    } else {
        error("uData parameter not initialized!");
    }


    //Parsing cuData
    cXMLElement* xml = NULL;
    if (par("cuData").xmlValue() != NULL
            && par("cuData").xmlValue()->hasChildren()) {
        xml = par("cuData").xmlValue();
    } else {
        error("cuData parameter not initialized!");
    }
    cXMLElementList cus = xml->getChildrenByTagName("CUItem");
    for(cXMLElement * m : cus){
        if (!m->getAttribute("id")) {
            error("Error parsing CU. Its ID is missing!");
        }

        std::string id = m->getAttribute("id");
        if (id == "") {
            error("Error parsing CU. Its ID is missing!");
        }

        string qn = "";
        L * l;
        U * u;
        C * c;

        cXMLElementList attrs = m->getChildren();
        for(cXMLElement * n : attrs ){
            string val = n->getNodeValue();
            if (!strcmp(n->getTagName(), "limit")) {
                if (Ls.find(val) != Ls.end()) {
                    l = &Ls[val];
                }
            } else if (!strcmp(n->getTagName(), "cherish")) {
                if (Cs.find(val) != Cs.end()) {
                    c = &Cs[val];
                }
            } else if (!strcmp(n->getTagName(), "urgency")) {
                if (Us.find(val) != Us.end()) {
                    u = &Us[val];
                }
            } else if (!strcmp(n->getTagName(), "queue")) {
                qn = val;
            }
        }
        CUs[id] = dlCUInfo(qn, l, c, u);
    }

}
void DQMonitor::parseL(cXMLElement* xml) {
    cXMLElementList ls = xml->getChildrenByTagName("L");
    for(cXMLElement* m  : ls){
        if (!m->getAttribute("id")) {
            error("Error parsing L. Its ID is missing!");
        }

        std::string id = m->getAttribute("id");
        if (id == "") {
            error("Error parsing L. Its ID is missing!");
        }

        bool limit = (m->getChildrenByTagName("limit").size() > 0);
        bool space = (m->getChildrenByTagName("limit").size() > 0);

        ILimValsList v;
        IDropProbList p;

        if (limit || space) {
            cXMLElementList limVals = m->getChildrenByTagName("limVals");
            for(cXMLElement* n : limVals) {
                double index;
                long long rate; // bps
                long long spaceRate; //bps
                double spaceVar; //[0..1]
                double dropProb = 0; //[0..1]

                if (!n->getAttribute("wt")) {
                    error("Error parsing limVals. Its wt is missing!");
                }
                index = atof(n->getAttribute("wt"));
                if (index < 0.0 ) {
                    error("Error parsing limVals. rate cannot be negative");
                }

                //Rate
                if (n->getChildrenByTagName("rate").size() != 1) {
                    error(  "Error parsing limVals. There must be one an only one rate per limVals");
                }
                rate = atoll((*n->getChildrenByTagName("rate").begin())->getNodeValue());
                if (rate <= 0) {
                    error( "Error parsing limVals. rate cannot be 0 or negative");
                }

                //Space Rate
                if (n->getChildrenByTagName("spaceRate").size() != 1) {
                    error("Error parsing limVals. There must be one an only one spaceRate per limVals");
                }
                spaceRate = atoll((*n->getChildrenByTagName("spaceRate").begin())->getNodeValue());
                if (spaceRate <= 0) {
                    error(
                            "Error parsing limVals. spaceRate cannot be 0 or negative");
                }

                //Space Rate Variation
                if (n->getChildrenByTagName("spaceVar").size() != 1) {
                        error(
                                "Error parsing limVals. There must be one an only one spaceVar per limVals");
                    }
                spaceVar = atof((*n->getChildrenByTagName("spaceVar").begin())->getNodeValue());
                if (spaceRate < 0 || spaceRate > 1) {
                    error(
                            "Error parsing limVals. spaceVar must be between 0 and 1");
                }

                if (limit) {
                    //Drop Probability
                    if (n->getChildrenByTagName("dropProb").size() != 1) {
                            error(
                                    "Error parsing limVals. There must be one an only one dropProb per limVals");
                        }
                    dropProb = atof((*n->getChildrenByTagName("dropProb").begin())->getNodeValue());
                    if (dropProb < 0 || spaceRate > 1) {
                        error(
                                "Error parsing limVals. dropProb must be between 0 and 1");
                    }
                }
                v.push_back(ILimVals(index, rate, spaceRate, spaceVar, dropProb));
            }
        }

        if (limit) {
            cXMLElementList dropVals = m->getChildrenByTagName("dropProb");
            for(cXMLElement* n : dropVals) {
                double index;
                double dropProb; //[0..1]

                if (!n->getAttribute("wt")) {
                    error("Error parsing dropProb. Its wt is missing!");
                }
                index = atof(n->getAttribute("wt"));
                if (index < 0 ) {
                    error("Error parsing dropProb. rate cannot be negative");
                }


                //Drop Probability
                if (!n->getAttribute("prob")) {
                    error("Error parsing dropProb. Its prob is missing!");
                }
                dropProb = atof(n->getAttribute("prob"));
                if (dropProb < 0 || dropProb > 1 ) {
                    error("Error parsing dropProb. prob must be between 0 and 1");
                }

                p.push_back(IDropProb(index, dropProb));
            }
        }
        Ls[id] = L(limit, space, v, p);
    }

}
void DQMonitor::parseC(cXMLElement* xml){
    cXMLElementList ls = xml->getChildrenByTagName("C");
    for(cXMLElement* m : ls) {
        if (!m->getAttribute("id")) {
            error("Error parsing C. Its ID is missing!");
        }

        std::string id = m->getAttribute("id");
        if (id == "") {
            error("Error parsing C. Its ID is missing!");
        }

        double def = 0.0; //[0..1]
        IDropProbList p;

        if (m->getAttribute("defaultDropProb")) {
            def = atof(m->getAttribute("defaultDropProb"));
            if(def < 0 || def > 1) {
                error("Error parsing C. defaultDropProb must be between 0 and 1");
            }
        }

        cXMLElementList dropPVals = m->getChildrenByTagName("dropProb");
        for (cXMLElement* n : dropPVals) {
                double index;
                double dropProb; //[0..1]

                if (!n->getAttribute("wt")) {
                    error("Error parsing dropProb. Its wt is missing!");
                }
                index = atof(n->getAttribute("wt"));
                if (index < 0 ) {
                    error("Error parsing dropProb. wt cannot be negative");
                }

                //Drop Probability
                if (!n->getAttribute("prob")) {
                    error("Error parsing dropProb. Its prob is missing!");
                }
                dropProb = atof(n->getAttribute("prob"));
                if (dropProb < 0 || dropProb > 1 ) {
                    error("Error parsing dropProb. prob must be between 0 and 1");
                }

                p.push_back(IDropProb(index, dropProb));
            }
        Cs[id] = C(def, p);
    }
}
void DQMonitor::parseU(cXMLElement* xml) {

    cXMLElementList ls = xml->getChildrenByTagName("U");
    for(cXMLElement* m  : ls){
        if (!m->getAttribute("id")) {
            error("Error parsing U. Its ID is missing!");
        }

        std::string id = m->getAttribute("id");
        if (id == "") {
            error("Error parsing U. Its ID is missing!");
        }

        int defPrio = 0;
        if (m->getAttribute("defaultPriority")) {
            defPrio = atoi(m->getAttribute("defaultPriority"));
        }

        bool degraded = (m->getChildrenByTagName("degraded").size() > 0);

        long long rate = 0;
        IDegradList dl;

        if (degraded) {
            //Rate
            if (m->getChildrenByTagName("rate").size() != 1) {
                error(  "Error parsing U. There must be one an only one rate per limVals");
            }
            rate = atoll((*m->getChildrenByTagName("rate").begin())->getNodeValue());
            if (rate <= 0) {
                error( "Error parsing U. rate cannot be 0 or negative");
            }

            cXMLElementList degVals = m->getChildrenByTagName("degradList");
            for(cXMLElement* n : degVals) {
                double index;
                if (!n->getAttribute("wt")) {
                    error("Error parsing degradList. Its wt is missing!");
                }
                index = atof(n->getAttribute("wt"));
                if (index < 0.0 ) {
                    error("Error parsing degradList. rate wt be negative");
                }

                IDegrad dd(index);

                cXMLElementList ppl = n->getChildrenByTagName("PP");
                for(cXMLElement* w : ppl) {
                    int prior;
                    double prob;

                    //Priority
                    if (w->getChildrenByTagName("priority").size() != 1) {
                        error(  "Error parsing PP. There must be one an only one priority per PP");
                    }
                    prior = atoi((*w->getChildrenByTagName("rate").begin())->getNodeValue());

                    //Probability
                    if (w->getChildrenByTagName("probability").size() != 1) {
                        error(  "Error parsing PP. There must be one an only one probability per PP");
                    }
                    prob = atof((*w->getChildrenByTagName("rate").begin())->getNodeValue());
                    if (prob <= 0) {
                        error( "Error parsing PP. probability  must be between 0 and 1");
                    }

                    dd.PPs.push_back(PP(prior, prob));
                }
                dl.push_back(dd);
            }
        }

        Us[id] = U(defPrio, degraded, rate, dl);
    }
}

void DQMonitor::postPDUInsertion(RMTQueue* queue) {
    //Get port and dlCUInfo for the queue
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    dlCUInfo * cu = Q2CU[queue];

    if (port != NULL && cu != NULL ) {
        switch(queue->getType()){

            //At input::
            case RMTQueue::INPUT : {

                //Get queue times list
                list<simtime_t> * times = &LTimes[port][cu->limit];

                //Clear serving times of past times
                for(list<simtime_t>::iterator it = times->begin(); it != times->end();){
                    list<simtime_t>::iterator tmpIt = it++;
                    if(*tmpIt <= simTime()) { times->erase(tmpIt); }
                }

                // Get serve and space times
                Times t;
                if(times->empty()){
                    t = Times( cu->limit->getTimes(0.0, queue->getLastPDU()->getBitLength()) );
                } else {
                    t = Times( cu->limit->getTimes( (times->back() - simTime()).dbl(), queue->getLastPDU()->getBitLength()) );
                }

                //Insert new serve and space times
                LTimes[port][cu->limit].push_back( t.serveT+simTime() );
                SpaceTimes[port][cu->limit].push_back( t.spaceT+simTime() );

                //Push "queue serve" into waiting queue
                LQueues[port][cu->limit].push_back(queue);

            } break;

            //At output::
            case RMTQueue::OUTPUT : {

                //Count number of PDUs waiting on port
                outC[port]++;

                //Get queue times list
                list<simtime_t> * times = &UTimes[queue];

                //Clear serving times of past times
                for(list<simtime_t>::iterator it = times->begin(); it != times->end();){
                    list<simtime_t>::iterator tmpIt = it++;
                    if(*tmpIt <= simTime()) { times->erase(tmpIt); }
                }

                //Get last serving time, if none, current
                simtime_t lt = simTime();
                if(!times->empty()) { lt = times->back();}

                //Get next urgency given last serving time
                /** Save it as negative to get inverse order in map list **/
                int u = -cu->urgency->getPriority( (lt-simTime()).dbl() );
                lastUrgency[queue] = u;

                //Compute next servint time and add to the queue times list
                lt += cu->urgency->getTime(queue->getLastPDU()->getBitLength());
                times->push_back(lt);

                //Push "queue serve" into waiting queue for given priority
                UQueues[port][u].push_back(queue);

            } break;
        }
    } else {
        error ("Unkown queue");
    }
}

void DQMonitor::onMessageDrop(RMTQueue* queue, const cPacket* pdu) {
    //Get port and dlCUInfo for the queue
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    dlCUInfo * cu = Q2CU[queue];

    if (port != NULL && cu != NULL ) {
        switch(queue->getType()){

            //At input::
            case RMTQueue::INPUT : {

                //Remove last serve and space times
                LTimes[port][cu->limit].pop_back();
                SpaceTimes[port][cu->limit].pop_back();

                //Remove last "queue serve"
                LQueues[port][cu->limit].pop_back();

            } break;

            //At output::
            case RMTQueue::OUTPUT : {
                //Decrement number of PDUs waiting on port
                outC[port]--;

                //Check for weird errors
                if(lastUrgency.find(queue) == lastUrgency.end()) { error("PDUs removed without going through monitor?"); }

                //Get and clear lastUrgency
                int lastU = lastUrgency[queue];
                lastUrgency.erase(queue);

                //Pop last "queue serve" from waiting queue for given priority.
                //Erase urgency queue if empty
                UQueues[port][lastU].pop_back();
                if(UQueues[port][lastU].empty()){ UQueues[port].erase(lastU); }


                //Get queue times list and try to remove last insertion
                list<simtime_t> * times = &UTimes[queue];
                if(!times->empty()) {
                    times->pop_back();
                } else {
                    error("PDUs removed without going through monitor?");
                }
            } break;
        }
    }
}

void DQMonitor::postQueueCreation(RMTQueue* queue) {
    std::string cu = "BE";

    for(auto cl : CUs){
        if(cl.second.queueName == queue->getName()){
            cu = cl.first;
        }
    }

    Q2CU[queue] = &CUs[cu];
}

double DQMonitor::getInDropProb(RMTQueue * queue) {
    //Get port and dlCUInfo for the queue
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    dlCUInfo * cu = Q2CU[queue];

    if (port != NULL && cu != NULL ) {
        //Return state : drop with prob X, given by last serving time + waiting pdus
        list<simtime_t> * times = &LTimes[port][cu->limit];
        cu->limit->getDropProb((times->back()-simTime()).dbl(), times->size());
    }

    return 1;
}

RMTQueue* DQMonitor::getNextInput(RMTPort* port) {
    //Initialice vars
    RMTQueue* q = NULL;
    L * minL = NULL;
    simtime_t minT = DBL_MAX;

    //Iterate through all L and get that with lower space time
    for(auto l : SpaceTimes[port]) {
        if(l.second.empty()){
            simtime_t tmp = l.second.front();
            if(tmp < minT) {
                minT = tmp;
                minL = l.first;
            }
        }
    }

    if(minL != NULL) {
        //save nextServe time for the port
        nextServe[port] = minT;

        //If next serve is not in the future, get the next queue and pop extra data
        if(minT <= simTime()) {
            q = LQueues [port][minL].front();
            LQueues [port][minL].pop_front();
            LTimes [port][minL].pop_front();
            SpaceTimes [port][minL].pop_front();
        }
    }
    return q;
}

simtime_t DQMonitor::getNextInputTime(RMTPort* port) {
    //return last computed nextServe time for that port
    return nextServe[port];
}



double DQMonitor::getOutDropProb(RMTQueue * queue) {
    //Get port and dlCUInfo for the queue
    RMTPort* port = rmtAllocator->getQueueToPortMapping(queue);
    dlCUInfo * cu = Q2CU[queue];

    if (port == NULL || cu == NULL) { error ("Unkown queue"); }

    //Compute the drop probability
    return cu->cherish->getDropProb(outC[port]);
}

RMTQueue* DQMonitor::getNextOutput(RMTPort* port) {

    //Iterate through all priorities and return the first queue found
    /** priorities are stored with negative values in order to make the map order correct **/
    for(auto uQ : UQueues[port]){
        if(!uQ.second.empty()) {
            RMTQueue* q = uQ.second.front();
            uQ.second.pop_front();
            outC[port]--;
            return q;
        }
    }

    return NULL;
}

}
