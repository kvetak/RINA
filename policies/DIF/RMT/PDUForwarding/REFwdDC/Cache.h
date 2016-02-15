#pragma once

#include "DC_Defines.h"
#include "DCAddr.h"
#include "PDU.h"
#include <map>
#include <omnetpp.h>


namespace REFwdDC {
using namespace std;
using namespace NSPSimpleDC;

    struct FlowIdentifier {
        DCAddr src, dst;
        int srcCep, dstCep;

        FlowIdentifier(const PDU * pdu);
        bool match(const DCAddr & n) const;

        bool operator<( const FlowIdentifier & n ) const;
        bool operator==( const FlowIdentifier & n ) const;
        bool operator!=( const FlowIdentifier & n ) const;
    };

    struct Cache {
        map<FlowIdentifier, Port> table;
        map<FlowIdentifier, simtime_t> clearAt;

        Port & getDst(const FlowIdentifier & FlowIdentifier);
        void replacePort(Port old, Port current);
        void removePort(Port old);
        void removeDst(const DCAddr & dst);
        void removeDstPort(const DCAddr & dst, Port old);


        void resetTimer(const FlowIdentifier & FlowIdentifier, const simtime_t & t);
        void clean(const simtime_t & t);

        void print();
    };

}
