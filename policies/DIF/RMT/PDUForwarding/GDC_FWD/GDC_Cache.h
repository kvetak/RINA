#pragma once

#include "GDC_defines.h"


namespace GDC {
    using namespace std;

    struct FlowId {
        Addr src, dst;
        int srcCep, dstCep;

        FlowId(const PDU * pdu);
        bool match(const Addr & n) const;

        bool operator<( const FlowId & n ) const;
        bool operator==( const FlowId & n ) const;
        bool operator!=( const FlowId & n ) const;
    };

    struct Cache {
        map<FlowId, Port> table;
        map<FlowId, simtime_t> clearAt;

        Port & getDst(const FlowId & fid);
        void replacePort(Port old, Port current);
        void removePort(Port old);
        void removeDst(const Addr & dst);
        void removeDstPort(const Addr & dst, Port old);


        void resetTimer(const FlowId & fid, const simtime_t & t);
        void clean(const simtime_t & t);

        void print();
    };

}
