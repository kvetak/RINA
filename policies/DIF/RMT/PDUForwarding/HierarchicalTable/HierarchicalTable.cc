#include <HierarchicalTable/HierarchicalTable.h>


Register_Class(HierarchicalTable::HierarchicalTable);

#include "Utils.h"
#include <sstream>

namespace HierarchicalTable {

using namespace std;


HierarchicalTable::HierarchicalTable() : anyQoS ("*"){}

void HierarchicalTable::addDomain(const string & domId, const string & qos, const string & prefix) {
    table[domId];
    vector<string> parsed = split(prefix, '.');
    domains[prefix][qos] = domData(domId, parsed.size());
}

void HierarchicalTable::addDomain(const string & domId, const string & prefix) {
    addDomain(domId, anyQoS, prefix);
}

void HierarchicalTable::removeDomain(string domId) {
    string prefix, qos;
    for(const auto & addrP : domains) {
        for(const auto & qosP : addrP.second) {
            if(qosP.second.domId == domId) {
                prefix = addrP.first;
                qos = qosP.first;
            }
        }
    }
    domains[prefix].erase(qos);
    table.erase(domId);
}


// Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
vector<RMTPort * > HierarchicalTable::lookup(const PDU * pdu){
    return lookup(pdu->getDstAddr(), pdu->getConnId().getQoSId());
}
vector<RMTPort * > HierarchicalTable::lookup(const Address &dst, const std::string& qos){
    string domId;
    string dstAddr = dst.getIpcAddress().getName();
    vector<RMTPort* >* found = NULL;
    vector<string> parsed = split(dstAddr, '.');

    for(auto & addrP : domains) {
        if(!isPrefix(addrP.first, dstAddr)){ continue; }
        bool foundAtQoS = false;
        bool foundAtAddr = false;
        if(addrP.second.find(qos) != addrP.second.end()) {
            domData dd = addrP.second[qos];
            if(dd.prefLen < parsed.size() && table[dd.domId].find(parsed[dd.prefLen]) != table[dd.domId].end()) {
                found = &table[dd.domId][parsed[dd.prefLen]];
                foundAtQoS = true;
                foundAtAddr = true;
            }
            if(!foundAtAddr && table[dd.domId].find("") != table[dd.domId].end()) {
                found = &table[dd.domId][""];
                foundAtQoS = true;
            }
        }
        if(!foundAtQoS && addrP.second.find(anyQoS) != addrP.second.end()) {
            domData dd = addrP.second[anyQoS];
            if(!foundAtAddr && dd.prefLen < parsed.size() && table[dd.domId].find(parsed[dd.prefLen]) != table[dd.domId].end()) {
                found = &table[dd.domId][parsed[dd.prefLen]];
                foundAtAddr = true;
            }
            if(!foundAtQoS && !foundAtAddr && table[dd.domId].find("") != table[dd.domId].end()) {
                found = &table[dd.domId][""];
            }
        }
    }

    vector<RMTPort* > ret;
    if(found != NULL && !found->empty()) {
        ret.push_back((*found)[intuniform(0, found->size()-1)]);
    }
    return ret;
}

// Returns a representation of the Forwarding Knowledge
string HierarchicalTable::toString(){
    std::ostringstream os;

    os << this->getName()<<endl;
    for(const auto & addrP : domains) {
        for(const auto & qosP : addrP.second) {
            os << " Domain " << qosP.second.domId << " (\""<<addrP.first<<"\" , QoS "<< qosP.first<<")" << endl;
            for(const auto &entry : table[qosP.second.domId]) {
                os << "\t" <<entry.first << "  ->  ";
                   for(RMTPort * p : entry.second){
                       os << p->getFullPath() << "   ";
                   }
                os << endl;
            }
        }
    }

    return os.str();
}

//Insert/Remove an entry
void HierarchicalTable::addReplace(const string &domId, const string &addr, vector<RMTPort *> ports){
    if(ports.empty()){
        table[domId].erase(addr);
    } else {
        table[domId][addr] = ports;
    }
}

// Called after initialize
void HierarchicalTable::onPolicyInit(){}

void HierarchicalTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
    }
}

}
