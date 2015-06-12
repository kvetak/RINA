#include <MiniTable/MiniTable.h>


Register_Class(MiniTable::MiniTable);

namespace MiniTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > MiniTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > MiniTable::lookup(const Address &dst, const std::string& qos){

    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();
    FWDTableIt it = table.find(dstAddr);

    if(it != table.end()){
        ret.push_back(it->second);
        EV << "MT Found => "<<dst<<endl;
    } else {
        EV << "MT NOT Found => "<<dst<<endl;
        EV << toString() << endl;
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string MiniTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(FWDTableIt tIt = table.begin(); tIt != table.end(); tIt++){
        os << "\t" <<tIt->first << "  ->  " <<tIt->second->getFullPath() << endl;
    }

    return os.str();
}

//Insert/Remove an entry
void MiniTable::insert(const Address &addr, RMTPort * port){
    insert(addr.getIpcAddress().getName(), port);
}
void MiniTable::remove(const Address &addr){
    remove(addr.getIpcAddress().getName());
}
void MiniTable::insert(const string &addr, RMTPort * port){
    table[addr] = port;
}
void MiniTable::remove(const string &addr){
    table.erase(addr);
}
void MiniTable::clean(){
    table.clear();
}


// Called after initialize
void MiniTable::onPolicyInit(){}

void MiniTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << toString() <<endl;
    }
}

}
