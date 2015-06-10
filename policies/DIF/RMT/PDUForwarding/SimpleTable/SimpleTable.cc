#include <SimpleTable/SimpleTable.h>


Register_Class(SimpleTable::SimpleTable);

namespace SimpleTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > SimpleTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > SimpleTable::lookup(const Address &dst, const std::string&qos){
    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();
    qos2Port * t = &table[dstAddr];
    if(t->empty()){ return ret; }

    if(t->find(qos) != t->end()){
        ret.push_back((*t)[qos]);
    } else if (!qos.compare(VAL_MGMTQOSID) && t->size() > 0){
        ret.push_back(t->begin()->second);
    }

    if(ret.empty()) {
        if(t->find(ANY_QOS) != t->end()){
            ret.push_back((*t)[ANY_QOS]);
        }
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string SimpleTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(FWDTableIt tIt = table.begin(); tIt != table.end(); tIt++){
        os << "\t" <<tIt->first<<endl;
        for(qos2PortIt qIt = tIt->second.begin(); qIt != tIt->second.end(); qIt++){
            os << "\t\t->(" << qIt->first << " , "<<qIt->second->getFullPath()<<")" <<endl;
        }
    }

    return os.str();
}

//Insert/Remove an entry
void SimpleTable::insert(const Address &addr, const std::string&qos, RMTPort * port){
    insert(addr.getIpcAddress().getName(), qos, port);
}
void SimpleTable::remove(const Address &addr, const std::string&qos){
    remove(addr.getIpcAddress().getName(), qos);
}
void SimpleTable::insert(const string &addr, const std::string&qos, RMTPort * port){
    table[addr][qos] = port;
}
void SimpleTable::remove(const string &addr, const std::string&qos){
    table[addr].erase(qos);
    if(table[addr].empty()){
        table.erase(addr);
    }
}


//Insert/Remove a mini entry
void SimpleTable::insert(const Address &addr, RMTPort * port){
    insert(addr.getIpcAddress().getName(), port);
}
void SimpleTable::remove(const Address &addr){
    remove(addr.getIpcAddress().getName());
}
void SimpleTable::insert(const string &addr, RMTPort * port){
    table[addr][ANY_QOS] = port;
}
void SimpleTable::remove(const string &addr){
    table[addr].erase(ANY_QOS);
    if(table[addr].empty()){
        table.erase(addr);
    }
}


// Called after initialize
void SimpleTable::onPolicyInit(){}

void SimpleTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << toString() <<endl;
    }
}

}
