#include <QoSTable/QoSTable.h>


Register_Class(QoSTable::QoSTable);

namespace QoSTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > QoSTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > QoSTable::lookup(const Address &dst, const unsigned short &qos){
    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();

    ret = lookupInt(dstAddr, qos);

    if(ret.empty() && qos == 0) {
        for(QoSFWDTableIt qIt = table.begin(); qIt != table.end(); qIt++){
            ret = lookupInt(dstAddr, qIt->first);
            if(!ret.empty()) { return ret; }
        }
    }

    return ret;
}

vector<RMTPort * > QoSTable::lookupInt(const string &dst, const unsigned short &qos){
    vector<RMTPort* > ret;
    FWDTableIt it = table[qos].find(dst);
    if(it != table[qos].end()){
        ret.push_back(it->second);
    }
    return ret;
}

// Returns a representation of the Forwarding Knowledge
string QoSTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;

    for(QoSFWDTableIt qIt = table.begin(); qIt != table.end(); qIt++){
        os << "\tQoS : " <<qIt->first << endl;
        for(FWDTableIt tIt = qIt->second.begin(); tIt != qIt->second.end(); tIt++){
            os << "\t\t" <<tIt->first << "  ->  " <<tIt->second->getFullPath() << endl;
        }
    }


    return os.str();
}

//Insert/Remove an entry
void QoSTable::insert(const Address &addr, const unsigned short &qos, RMTPort * port){
    insert(addr.getIpcAddress().getName(), qos, port);
}
void QoSTable::remove(const Address &addr, const unsigned short &qos){
    remove(addr.getIpcAddress().getName(), qos);
}
void QoSTable::insert(const string &addr, const unsigned short &qos, RMTPort * port){
    table[qos][addr] = port;
}
void QoSTable::remove(const string &addr, const unsigned short &qos){
    table[qos].erase(addr);
    if(table[qos].empty()){
        table.erase(qos);
    }
}
void QoSTable::clean(){
    table.clear();
}


// Called after initialize
void QoSTable::onPolicyInit(){}

void QoSTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << toString() <<endl;
    }
}

}
