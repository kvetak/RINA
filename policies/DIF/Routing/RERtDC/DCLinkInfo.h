#pragma once


#include "DCAddr.h"
#include <omnetpp.h>

namespace RERtDC {

using namespace std;
using namespace NSPSimpleDC;

    struct linkId {
        DCAddr src, dst;

        linkId();
        linkId(const DCAddr &_src, const DCAddr &_dst);

        bool operator<(const linkId &o) const;
        bool operator==(const linkId & o) const;
        bool operator!=(const linkId & o) const;
    };

    struct linkInfo {
        linkId link;
        bool status;
        long timestamp;

        linkInfo();
        linkInfo(const linkId &_link, const bool &_status, const long &_timestamp);
    };

}
