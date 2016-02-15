#include "RuleExceptionsFWD.h"

namespace REFwdDC {

using namespace std;
using namespace NSPSimpleDC;

//RuleExceptionsFWD common functions
    RuleExceptionsFWD::RuleExceptionsFWD() {
        myports = nullptr;
    }

    RuleExceptionsFWD::~RuleExceptionsFWD() {
        if(myports != nullptr) {
            delete[] myports;
        }
        exceptionsT.clear();
    }

    void RuleExceptionsFWD::onPolicyInit() {
        initializeSubPolicy();
        for(unsigned char i = 0; i< myportsSyze; i++) {  myports[i] = nullptr; }
        cacheLivespan = par("cacheLivespan").doubleValue();
        scheduleAt(simTime()+cacheLivespan, new cMessage("Clean cache"));
    }

    void RuleExceptionsFWD::handleMessage(cMessage * msg) {
        cache.clean(simTime());
        scheduleAt(simTime()+cacheLivespan/3, msg);
    }

    void RuleExceptionsFWD::setNodeInfo(const DCAddr & n_addr) {
        Im = n_addr;
    }

    vector<Port> RuleExceptionsFWD::lookup(const PDU * pdu) {
        string s_addr = pdu->getDstAddr().getIpcAddress().getName();
        DCAddr n_addr = DCAddr(s_addr);
        //Malformed address or empty
        if(n_addr.type < 0) {  return vector<Port>(); }

        //TTL > 15
        PDU * p = const_cast<PDU*>(pdu);
        p->setHopCount(p->getHopCount()+1);
        if(p->getHopCount()> 15) {
            cerr << "MaxHops? " << p->getHopCount() << endl;
            return vector<Port>();
        }

        //Check on cache
        FlowIdentifier fId(pdu);
        auto & cEntry = cache.getDst(fId);
        //If cache returns null, search next hop
        if(cEntry == nullptr) {
            portList possible = search(n_addr);
            if(possible.size() > 0) {
                cEntry = myports[possible[intuniform(0, possible.size()-1)]];
            }
        }

        vector<Port> ret;
        if(cEntry != nullptr) {
            ret.push_back(cEntry);
            cache.resetTimer(fId, simTime()+cacheLivespan);
        }

        return ret;
    }

    vector<Port> RuleExceptionsFWD::lookup(const Address & dst, const std::string & qos) {
        string s_addr = dst.getIpcAddress().getName();
        DCAddr n_addr = DCAddr(s_addr);
        //Malformed address or empty
        if(n_addr.type < 0) {  return vector<Port>(); }

        portList possible = search(n_addr);
        vector<Port> ret;
        if(possible.size() > 0) {
            int k = intuniform(0, possible.size()-1);
            ret.push_back(myports[possible[k]]);
        }
        return ret;
    }

    string RuleExceptionsFWD::toString() {
        return "RuleExceptionsFWD";
    }

    portList RuleExceptionsFWD::search(const DCAddr & n_addr) {
        Exception e = nullptr;
        switch(n_addr.type) {
            case TYPEID_ToR:
                e = exceptionsT.findToRException(n_addr);
                break;
            case TYPEID_Edge:
                e = exceptionsT.findEdgeException(n_addr);
                break;
        }
        if(e != nullptr) { return readException(e); }
        else { return executeRule(n_addr); }
    }

    portList RuleExceptionsFWD::directList(const portId & p) {
        portList ret;
        ret.push_back(p);
        return ret;
    }

    void RuleExceptionsFWD::setExceptions(const RawExceptionsList & exceptions) {
        for(const RawException & raw : exceptions) {
            Exception current_e = nullptr;
            switch (raw.addr.type) {
                case TYPEID_ToR:
                    current_e = exceptionsT.findToRException(raw.addr); break;
                case AGID_Pod:
                    current_e = exceptionsT.findPodOnlyException(raw.addr); break;
                case TYPEID_Edge:
                    current_e = exceptionsT.findEdgeException(raw.addr); break;
                case AGID_Spine:
                    current_e = exceptionsT.findPodOnlyException(raw.addr); break;
                default:
                    cerr << "At "<<Im << " - Received Exception for invalid addr/set "<< raw.addr <<endl;
                    continue;
            }
            portList rawList = readRawException(raw);
            portList ruleList = executeRule(raw.addr);

            //cout << Im << " - Received Raw Exception to " << raw.addr <<endl;
            if(rawList == ruleList) {
                if(current_e != nullptr) {
                    portList oldList = readException(current_e);
                    refreshCache(raw.addr, oldList, ruleList);
                    switch (raw.addr.type) {
                        case TYPEID_ToR:
                            exceptionsT.removeTorException(raw.addr.a, raw.addr.b);
                        case AGID_Pod:
                            exceptionsT.removePodException(raw.addr.a);
                        case TYPEID_Edge:
                            exceptionsT.removeEdgeException(raw.addr.a, raw.addr.b);
                        case AGID_Spine:
                            exceptionsT.removeSpinesException(raw.addr.a);
                    }
                }
            } else {
                Exception new_e = computeException(raw);
                if(current_e == nullptr) {
                    refreshCache(raw.addr, ruleList, rawList);
                    switch (raw.addr.type) {
                        case TYPEID_ToR:
                            exceptionsT.addTorException(raw.addr.a, raw.addr.b, new_e); break;
                        case AGID_Pod:
                            exceptionsT.addPodException(raw.addr.a, new_e); break;
                        case TYPEID_Edge:
                            exceptionsT.addEdgeException(raw.addr.a, raw.addr.b, new_e); break;
                        case AGID_Spine:
                            exceptionsT.addSpinesException(raw.addr.a, new_e); break;
                    }
                } else {
                    portList oldList = readException(current_e);
                    refreshCache(raw.addr, oldList, rawList);
                    switch (raw.addr.type) {
                        case TYPEID_ToR:
                            exceptionsT.removeTorException(raw.addr.a, raw.addr.b);
                            exceptionsT.addTorException(raw.addr.a, raw.addr.b, new_e); break;
                        case AGID_Pod:
                            exceptionsT.removePodException(raw.addr.a);
                            exceptionsT.addPodException(raw.addr.a, new_e); break;
                        case TYPEID_Edge:
                            exceptionsT.removeEdgeException(raw.addr.a, raw.addr.b);
                            exceptionsT.addEdgeException(raw.addr.a, raw.addr.b, new_e); break;
                        case AGID_Spine:
                            exceptionsT.removeSpinesException(raw.addr.a);
                            exceptionsT.addSpinesException(raw.addr.a, new_e); break;
                    }
                }
            }
        }
    }

    void RuleExceptionsFWD::refreshCache(const DCAddr & addr, portList oldPorts, portList newPorts) {
        portList removed;
        if(newPorts.size() == 0) { removed = oldPorts; }
        else {
            unsigned char j = 0;
            portId current = newPorts[j];
            for(portId i : oldPorts) {
                while( i > current) {
                    j++;
                    if(j > newPorts.size()) { current = myportsSyze; }
                    else { current = newPorts[j]; }
                }
                if(i < current) { removed.push_back(i); }
            }
        }
        for(const portId & pId : removed) {
            cache.removeDstPort(addr, myports[pId]);
        }
    }


    portList RuleExceptionsFWD::inverseList(portList list, portId a, portId b) {
        portList ret;
        unsigned char j = 0;
        portId current = b;
        if(list.size()>j) { current = list[j]; }
        for(portId i = a; i < b; i++) {
            if(myports[i] == nullptr) { continue; }
            while( i > current) {
                j++;
                if(j > list.size()) { current = b; }
                else { current = list[j]; }
            }
            if(i < current) { ret.push_back(i); }
        }
        return ret;
    }


    void RuleExceptionsFWD::finish() {
        if(!par("printAtEnd").boolValue()) { return; }

        cout << "Forwarding at "<< Im << endl;
        cout << "\tMy ports status:" <<endl;
        for(portId i = 0; i < myportsSyze; i++) {
            auto n = myports[i];
            cout << "\t\t" << "Port : " << (int)i;
            if(n == nullptr) {
                cout << " | off-line";
            } else {
                cout << " | on-line";
            }
            cout <<endl;
        }
        cout << "\tStored exceptions:" <<endl;
        exceptionsT.print();

        cout << "\tCache entries:" <<endl;
        cache.print();


        cout << endl;
    }

}
