#include "GDC_FWD_iface.h"

namespace GDC {
    using namespace std;

    iface_FWD::iface_FWD() : myports(nullptr), myportsSyze(0) {}

    iface_FWD::~iface_FWD() {
        if(myports != nullptr) { delete[] myports; }
        exceptionsT.clear();
    }

    void iface_FWD::onPolicyInit() {
        string myAddr = getModuleByPath("^.^")->par("ipcAddress").stringValue();
        Im = Addr(myAddr);

        nSpines = par("nSpines").longValue();
        nPod = par("nPod").longValue();
        nEdgeP = par("nEdgeP").longValue();
        nFab = par("nFab").longValue();
        nTor = par("nTor").longValue();
        nEdge = par("nEdge").longValue();

        initializeSubPolicy();
        for(unsigned char i = 0; i< myportsSyze; i++) {  myports[i] = nullptr; }
        cacheLivespan = par("cacheLivespan").doubleValue();
        scheduleAt(simTime()+cacheLivespan, new cMessage("Clean cache"));
    }

    void iface_FWD::handleMessage(cMessage * msg) {
        cache.clean(simTime());
        scheduleAt(simTime()+cacheLivespan/3, msg);
    }

    vecPort iface_FWD::lookup(const PDU * pdu) {
        string raw_dst = pdu->getDstAddr().getIpcAddress().getName();
        Addr dst = Addr(raw_dst);

        //Malformed address or empty
        if(dst.a == 0 && dst.b == 0) {  return vecPort(); }

        //TTL > 15
        PDU * p = const_cast<PDU*>(pdu);
        p->setHopCount(p->getHopCount()+1);
        if(p->getHopCount()> 15) {
            cerr << "MaxHops?" << endl;
            return vector<Port>();
        }

        //Check on cache
        FlowId fId(pdu);
        auto & cEntry = cache.getDst(fId);
        //If cache returns null, search next hop
        if(cEntry == nullptr) {
            vecushort possible = search(dst);
            if(possible.size() > 0) {
                cEntry = myports[possible[intuniform(0, possible.size()-1)]];
            }
        }

        vecPort ret;
        if(cEntry != nullptr) {
            ret.push_back(cEntry);
            cache.resetTimer(fId, simTime()+cacheLivespan);
        }

        return ret;
    }

    vecPort iface_FWD::lookup(const Address & Adst, const string & qos) {
        string raw_dst = Adst.getIpcAddress().getName();
        Addr dst = Addr(raw_dst);

        //Malformed address or empty
        if(dst.a == 0 && dst.b == 0) {  return vecPort(); }

        vecushort possible = search(dst);

        vecPort ret;
        if(possible.size() > 0) {
            int k = intuniform(0, possible.size()-1);
            ret.push_back(myports[possible[k]]);
        }

        return ret;
    }

    vecushort iface_FWD::search(const Addr & dst) {
        Exception e = nullptr;
        if(dst.a != 0) {
            e = exceptionsT.getNodeException(dst);
            if(e != nullptr) { e = exceptionsT.getGroupException(dst.a); }
            if(e != nullptr && useDefault(dst)) { e = exceptionsT.getDefaultException(); }
        }
        if(e != nullptr) { return readException(e); }
        else { return executeRule(dst); }
    }

    string iface_FWD::toString() { return "iface_FWD : " + Im.toString(); };

    void iface_FWD::setExceptions(const vecRawException & exceptions) {
        for(const RawException & raw : exceptions) {
            Exception current_e = nullptr;
            const Addr & dst = raw.addr;
            uchar etype;
            if(dst.a == 0 && dst.b == 0) { //Case Default exception
                current_e = exceptionsT.getDefaultException();
                etype = 0;
            } else if(dst.b == 0) { //Case Group exception
                current_e = exceptionsT.getGroupException(dst.a);
                etype = 1;
            } else if(dst.b){ // Case Node exception
                current_e = exceptionsT.getNodeException(dst);
                etype = 2;
            }

            vecushort rawL = readRawException(raw);
            vecushort ruleL = executeRule(dst);

            if(rawL == ruleL) {
                if(current_e != nullptr) {
                    vecushort oldL = readException(current_e);
                    refreshCache(dst, oldL, rawL);
                    switch(etype) {
                        case 0 : exceptionsT.removeDefaultException(); break;
                        case 1 : exceptionsT.removeGroupException(dst.a); break;
                        case 2 : exceptionsT.removeNodeException(dst); break;
                    }
                }
            } else {
                Exception new_e = computeException(raw);
                if(current_e == nullptr) {
                    refreshCache(dst, ruleL, rawL);
                } else {
                    vecushort oldL = readException(current_e);
                    refreshCache(dst, oldL, rawL);
                }
                switch(etype) {
                    case 0 : exceptionsT.addDefaultException(new_e); break;
                    case 1 : exceptionsT.addGroupException(dst.a, new_e); break;
                    case 2 : exceptionsT.addNodeException(dst, new_e); break;
                }
            }
        }
    }

    void iface_FWD::refreshCache(const Addr & addr, vecushort oldPorts, vecushort newPorts) {
        vecushort removed;
        if(newPorts.empty()) { removed = oldPorts; }
        else {
            ushort j = 0;
            ushort current = newPorts[j];
            for(const ushort & i : oldPorts) {
                while( i > current) {
                    j++;
                    if(j > newPorts.size()) { current = myportsSyze; }
                    else { current = newPorts[j]; }
                }
                if(i < current) { removed.push_back(i); }
            }
        }
        for(const ushort & pId : removed) {
            cache.removeDstPort(addr, myports[pId]);
        }
    }

    vecushort iface_FWD::directList(const ushort &  p) {
        vecushort ret;
        ret.push_back(p);
        return ret;
    }

    vecushort iface_FWD::inverseList(vecushort list, ushort a, ushort b) {
        vecushort ret;
        ushort j = 0;
        ushort current = b;
        if(list.size()>j) { current = list[j]; }
        for(ushort i = a; i < b; i++) {
            if(myports[i] == nullptr) { continue; }
            while( i > current) {
                j++;
                if(j >= list.size()) { current = b; }
                else { current = list[j]; }
            }
            if(i < current) { ret.push_back(i); }
        }
        return ret;
    }

    void iface_FWD::finish() {

        if(!par("printAtEnd").boolValue()) { return; }

        cout << "Forwarding at "<< Im << endl;
        cout << "\tMy ports status:" <<endl;
        for(ushort i = 0; i < myportsSyze; i++) {
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
