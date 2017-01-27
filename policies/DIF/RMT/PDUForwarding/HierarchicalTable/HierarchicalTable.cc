#include "DIF/RMT/PDUForwarding/HierarchicalTable/HierarchicalTable.h"


Register_Class(HierarchicalTable::HierarchicalTable);

#include "Common/Utils.h"
#include <sstream>

namespace HierarchicalTable {

using namespace std;


HierarchicalTable::HierarchicalTable() : anyQoS ("*"){}

void HierarchicalTable::addDomain(const string & domId, const string & qos, const string & prefix) {
    table[domId];
    if(prefix == "") {
        domains[prefix][qos] = domData(domId, 0);
    } else {
        vector<string> parsed = split(prefix, '.');
        domains[prefix][qos] = domData(domId, parsed.size());
    }
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

    vector<RMTPort* > ret;
    string domId;
    string dstAddr = dst.getIpcAddress().getName();
    if(dstAddr == "") { return ret; };
    vector<RMTPort* >* found = NULL;
    vector<string> parsed = split(dstAddr, '.');

    for(auto & addrP : domains) {
        if(!isPrefix(addrP.first, dstAddr)){ continue; }
        found = NULL;
        bool foundAtQoS = false;
        bool foundAtAddr = false;

        if(addrP.second.find(qos) != addrP.second.end()) {
            domData dd = addrP.second[qos];
            string val = parsed[dd.prefLen];
            if(table[dd.domId].find(val) != table[dd.domId].end()){
                found = &table[dd.domId][val];
                foundAtQoS = true;
                foundAtAddr = true;
            } else if(table[dd.domId].find("*") != table[dd.domId].end()) {
                found = &table[dd.domId]["*"];
                foundAtQoS = true;
            }
        }
        if(!foundAtAddr && addrP.second.find(anyQoS) != addrP.second.end()) {
            domData dd = addrP.second[anyQoS];

            string val = parsed[dd.prefLen];
            if(table[dd.domId].find(val) != table[dd.domId].end()){
                found = &table[dd.domId][val];
            } else if(!foundAtQoS && table[dd.domId].find("*") != table[dd.domId].end()) {
                found = &table[dd.domId]["*"];
            }
        }
    }

    if(found != NULL && !found->empty()) {
        ret.push_back((*found)[omnetpp::intuniform(omnetpp::getEnvir()->getRNG(0), 0, found->size()-1)]);
    } else if(direct.find(dst) != direct.end()) {
        ret.push_back(direct[dst]);
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
void HierarchicalTable::onPolicyInit(){
    // IPCProcess module.
    cModule * ipcModule = getModuleByPath("^.^");

    myAddr   = Address(
        ipcModule->par("ipcAddress").stringValue(),
        ipcModule->par("difName").stringValue());
}

void HierarchicalTable::setAddr(const Address & addr) {
    myAddr = addr;
}

void HierarchicalTable::setTmp(const Address & dst, RMTPort *p) {
    direct[dst] = p;
}

void HierarchicalTable::removeTmp(const Address & dst, RMTPort *p) {
    if(direct[dst]== NULL || direct[dst]==p) {
        direct.erase(dst);
    }
}

void HierarchicalTable::finish(){
    if(par("printAtEnd").boolValue()){
        EV << "-----------------" << endl;
        EV << "Forwarding table::" << endl;
        EV << toString() <<endl;
        EV << "-----------------" << endl;
        for(auto tmp : direct){
            EV << "\t" << tmp.first << " -> " << tmp.second->getFullPath() << endl;
        }
    }
}

}
