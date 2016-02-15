#include "GDC_Cache.h"


namespace GDC {
    using namespace std;


    //FlowId for cache
    FlowId::FlowId(const PDU * pdu) {
        dst = Addr(pdu->getDstAddr().getIpcAddress().getName());
        src = Addr(pdu->getSrcAddr().getIpcAddress().getName());
        srcCep = pdu->getConnId().getSrcCepId();
        dstCep = pdu->getConnId().getDstCepId();
    }

    bool FlowId::match(const Addr & n) const { return dst == n; }

    bool FlowId::operator<( const FlowId & n ) const {
        if(src < n.src) { return true; }
        if(n.src < src) { return false; }
        if(dst < n.dst) { return true; }
        if(n.dst < dst) { return false; }
        if(srcCep < n.srcCep) { return true; }
        if(n.srcCep < srcCep) { return false; }
        return dstCep < n.dstCep;
    }

    bool FlowId::operator==( const FlowId & n ) const {
        return dst == n.dst && src == n.src &&  srcCep == n.srcCep && dstCep == n.dstCep;
    }

    bool FlowId::operator!=( const FlowId & n ) const {
        return dst != n.dst || src != n.src || srcCep != n.srcCep || dstCep != n.dstCep;
    }

    //Cache
    Port & Cache::getDst(const FlowId & fid) { return table[fid]; }

    void Cache::replacePort(Port old, Port current) {
        for(auto & e : table) {
            if(e.second == old) { e.second = current; }
        }
    }

    void Cache::removePort(Port old) {
        auto it = table.begin();
        while(it != table.end()) {
            if(it->second == old) { it = table.erase(it); }
            else { it++; }
        }
    }

    void Cache::removeDst(const Addr & dst) {
        auto it = table.begin();
        while(it != table.end()) {
            if(it->first.match(dst)) { it = table.erase(it); }
            else { it++; }
        }
    }

    void Cache::removeDstPort(const Addr & dst, Port old) {
        auto it = table.begin();
        while(it != table.end()) {
            if(it->second == old && it->first.match(dst)) { it = table.erase(it); }
            else { it++; }
        }
    }


    void Cache::resetTimer(const FlowId & fid, const simtime_t & t) { clearAt[fid] = t; }

    void Cache::clean(const simtime_t & t) {
        auto itt = clearAt.begin();
        while(itt != clearAt.end()) {
            if(itt->second <= t) {
                table[itt->first] = nullptr;
                clearAt.erase(itt++);
            } else { itt++; }
        }
        auto it = table.begin();
        while(it != table.end()) {
            if(it->second == nullptr) { table.erase(it++); }
            else { it++; }
        }
    }

    void Cache::print() {
        for(auto & ce : table) {
            auto & fid = ce.first;
            simtime_t t = clearAt[fid];
            cout << "\t\t" << fid.src <<" -> " << fid.dst
                    << " ["<<fid.srcCep<<","<<fid.dstCep <<"]"
                    << " - Stored until "<< t
                    << endl;
        }
    }
}
