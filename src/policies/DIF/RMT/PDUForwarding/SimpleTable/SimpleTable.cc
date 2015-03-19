#include <SimpleTable/SimpleTable.h>


Register_Class(SimpleTable::SimpleTable);

namespace SimpleTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > SimpleTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > SimpleTable::lookup(const Address &dst, const unsigned short &qos){
    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();
    qos2Port * t = &table[dstAddr];
    if(t->find(qos) != t->end()){
        ret.push_back((*t)[qos]);
    } else if (qos == 0 && t->size() > 0){
        ret.push_back(t->begin()->second);
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
void SimpleTable::insert(const Address &addr, const unsigned short &qos, RMTPort * port){
    EV << "Insert "<<addr << " , " << qos << " -> " << port->getFullPath()<<endl;
    string dstAddr = addr.getIpcAddress().getName();
    table[dstAddr][qos] = port;
}
void SimpleTable::remove(const Address &addr, const unsigned short &qos){
    EV << "Remove "<<addr << " , " << qos <<endl;
    string dstAddr = addr.getIpcAddress().getName();
    table[dstAddr].erase(qos);
    if(table[dstAddr].empty()){
        table.erase(dstAddr);
    }
}


// Called after initialize
void SimpleTable::onIni(){}

void SimpleTable::finish(){
    EV << toString() <<endl;
}

}
