#include <SimpleDV/SimpleDV.h>

namespace SimpleDV {

Register_Class(SimpleDV);

using namespace std;


RoutingUpdate::RoutingUpdate(const Address &_addr, const std::string &_src, const unsigned short &_qos):IntRoutingUpdate(_addr){
    src = _src;
    qos = _qos;
}

std::string RoutingUpdate::getSrc(){
    return src;
}
unsigned short RoutingUpdate::getQoS(){
    return qos;
}

void RoutingUpdate::addEntry(rtEntry entry){
    entries.push_back(entry);
}

entriesIt RoutingUpdate::entriesBegin(){
    return entries.begin();
}
entriesIt RoutingUpdate::entriesEnd(){
    return entries.end();
}


//Flow inserted/removed
void SimpleDV::insertFlow(const Address &addr, const std::string &dst, const unsigned short &qos, const unsigned short &metric){

    neig[qos][addr] = metric;

    rtEntry * oldEntry = &table[qos][dst];

    bool entryChangedDst = false;

    if(oldEntry->addr == dst){
        if(oldEntry->metric != metric){
            oldEntry->metric = metric;
        }
    } else if(oldEntry->metric >= metric){
        oldEntry->addr = dst;
        oldEntry->metric = metric;
        entryChangedDst = true;
    }

    if(oldEntry->metric >= infMetric){
        changes.insert(entries2NextItem(qosPaddr(qos, dst),""));
        table[qos].erase(dst);
    } else if(entryChangedDst){
        changes.insert(entries2NextItem(qosPaddr(qos, dst),dst));
    }
}
void SimpleDV::removeFlow(const Address &addr, const std::string &dst, const unsigned short &qos){
    neig[qos].erase(addr);
    if(neig[qos].size() <= 0){
        neig.erase(qos);
    }

    tTable * qosTable = &table[qos];

    for(tTableIt it = qosTable->begin(); it != qosTable->end();){
        rtEntry * oldEntry = &it->second;
        tTableIt actIt = it;
        it++;

        if(oldEntry->addr == dst){
            changes.insert(entries2NextItem(qosPaddr(qos, oldEntry->addr),""));
            qosTable->erase(actIt);
        }
    }
}

//Get Changes
entries2Next SimpleDV::getChanges(){
    entries2Next ret = changes;
    changes.clear();
    return ret;
}

entries2Next SimpleDV::getAll(){
    entries2Next ret;

    for(rtTableIt it = table.begin(); it != table.end(); it++){
        for(tTableIt it2 = it->second.begin(); it2 != it->second.end(); it2++){
            if(it2->second.metric < infMetric) {
                ret[qosPaddr(it->first, it2->first)] = it2->second.addr;
            } else {
                ret[qosPaddr(it->first, it2->first)] = "";
            }
        }
    }
    map<unsigned short, map<string, rtEntry> > table;

    return ret;
}

//Process a Routing Update, return true => inform FWDG of the update
bool SimpleDV::processUpdate(IntRoutingUpdate * update){
    RoutingUpdate * up = check_and_cast<RoutingUpdate*>(update);

    std::string src = up->getSrc();
    if(src == myAddr){
        return false;
    }

    unsigned short qos = up->getQoS();

    for(entriesIt it = up->entriesBegin(); it!= up->entriesEnd(); it++){
        if(it->addr == myAddr) {
            continue;
        }

        rtEntry * newEntry = &(*it);
        rtEntry * oldEntry = &table[qos][newEntry->addr];

        bool entryChangedDst = false;

        if(oldEntry->addr == newEntry->addr){
            if(oldEntry->metric == newEntry->metric){
                oldEntry->metric = newEntry->metric;
            }
        } else if(oldEntry->metric >= newEntry->metric){
            oldEntry->addr = src;
            oldEntry->metric = newEntry->metric;
            entryChangedDst = true;
        }

        if(oldEntry->metric >= infMetric){
            changes.insert(entries2NextItem(qosPaddr(qos, newEntry->addr),""));
            table[qos].erase(newEntry->addr);
        } else if(entryChangedDst){
            changes.insert(entries2NextItem(qosPaddr(qos, newEntry->addr),src));
        }
    }
    return ! changes.empty();
}

// Called after initialize
void SimpleDV::onIni(){
    myAddr = par("myAddr").stdstringValue();
    if(myAddr == "") {
        myAddr = myAddress.getIpcAddress().getName();
    }

    infMetric = 32;

    scheduleAt(simTime()+30, new cMessage("Time2Update"));
}


void SimpleDV::handleMessage(cMessage *msg){
    if(msg->isSelfMessage()){
        //Iterate all Qos
        for(qosNeighMetricIt it = neig.begin(); it!= neig.end(); it++){
            //getTable per QoS
            tTable * qosTable = &table[it->first];

            //iterate all Qos->Neighbour
            for(neighMetricIt it2 = it->second.begin(); it2 != it->second.end(); it2++){
                //New Update to QoS + Neighbour
                RoutingUpdate * update = new RoutingUpdate(it2->first, myAddr, it->first);

                //Populate the update
                for(tTableIt it3 = qosTable->begin(); it3 != qosTable->end();it3++){
                    update->addEntry(rtEntry(it3->first, it3->second.metric+ it2->second));
                }

                //Add our entry
                update->addEntry(rtEntry(myAddr, it2->second));

                //And send
                sendUpdate(update);
            }
        }

        scheduleAt(simTime()+30, msg);
    }
}


void SimpleDV::finish(){
    IntRouting::finish();

    EV << "I'm "<< myAddr<<endl;

    for(rtTableIt it = table.begin(); it != table.end(); it++){
        EV << "  QoS " << it->first<<endl;
        for(tTableIt it2 = it->second.begin(); it2 != it->second.end(); it2++){
            EV<<"    " << it2->first << " -> "<<it2->second.addr << " ("<<it2->second.metric<<")" << endl;
        }
    }

}

}
