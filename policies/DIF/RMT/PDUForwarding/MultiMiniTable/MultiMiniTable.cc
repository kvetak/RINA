#include <MultiMiniTable/MultiMiniTable.h>


Register_Class(MultiMiniTable::MultiMiniTable);

namespace MultiMiniTable {

using namespace std;

#include <sstream>

// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > MultiMiniTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > MultiMiniTable::lookup(const Address &dst, const std::string& qos){

    vector<RMTPort* > ret;
    string dstAddr = dst.getIpcAddress().getName();
    FWDTableIt it = table.find(dstAddr);

    if(it != table.end()){
        int i = intuniform(0, it->second.size()-1);
        ret.push_back(it->second.at(i));
    }

    return ret;
}

// Returns a representation of the Forwarding Knowledge
string MultiMiniTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(FWDTableIt tIt = table.begin(); tIt != table.end(); tIt++){
        os << "\t" <<tIt->first << "  ->  ";
        for(RMTPort * p : tIt->second){
            os << p->getFullPath() << "   ";
        }
        os << endl;
    }

    return os.str();
}

//Insert/Remove an entry
void MultiMiniTable::addReplace(const std::string &addr, vector<RMTPort *> ports){
    if(ports.empty()){
        table.erase(addr);
    } else {
        table[addr] = ports;
    }
}

// Called after initialize
void MultiMiniTable::onPolicyInit(){}

void MultiMiniTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
