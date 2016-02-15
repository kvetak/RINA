#include "Cache.h"

namespace REFwdDC {

using namespace std;
using namespace NSPSimpleDC;

//FlowIdentifier for cache

    FlowIdentifier::FlowIdentifier(const PDU * pdu) {
        dst = DCAddr(pdu->getDstAddr().getIpcAddress().getName());
        src = DCAddr(pdu->getSrcAddr().getIpcAddress().getName());
        srcCep = 0;
        dstCep = 0;
        srcCep = pdu->getConnId().getSrcCepId();
        dstCep = pdu->getConnId().getDstCepId();
    }

    bool FlowIdentifier::match(const DCAddr & n) const {
        return dst == n;
    }

    bool FlowIdentifier::operator<( const FlowIdentifier & n ) const {
        if(src < n.src) { return true; }
        if(n.src < src) { return false; }
        if(dst < n.dst) { return true; }
        if(n.dst < dst) { return false; }
        if(srcCep < n.srcCep) { return true; }
        if(n.srcCep < srcCep) { return false; }
        return dstCep < n.dstCep;
    }

    bool FlowIdentifier::operator==( const FlowIdentifier & n ) const {
        return dst == n.dst && src == n.src &&  srcCep == n.srcCep && dstCep == n.dstCep;
    }

    bool FlowIdentifier::operator!=( const FlowIdentifier & n ) const {
        return dst != n.dst || src != n.src || srcCep != n.srcCep || dstCep != n.dstCep;
    }

//Cache
    Port & Cache::getDst(const FlowIdentifier & fId) {
        return table[fId];
    }

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

    void Cache::removeDst(const DCAddr & dst) {
        auto it = table.begin();
        while(it != table.end()) {
            if(it->first.match(dst)) { it = table.erase(it); }
            else { it++; }
        }
    }


    void Cache::removeDstPort(const DCAddr & dst, Port old) {
        auto it = table.begin();
        while(it != table.end()) {
            if(it->second == old && it->first.match(dst)) { it = table.erase(it); }
            else { it++; }
        }
    }


    void Cache::resetTimer(const FlowIdentifier & fId, const simtime_t & t) {
        clearAt[fId] = t;
    }

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
            auto & fId = ce.first;
            simtime_t t = clearAt[fId];
            cout << "\t\t" << fId.src <<" -> " << fId.dst
                    << " ["<<fId.srcCep<<","<<fId.dstCep <<"]"
                    << " - Stored until "<< t
                    << endl;
        }
    }
}
