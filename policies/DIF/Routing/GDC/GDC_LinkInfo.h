#pragma once

#include "GDC_defines.h"

namespace GDC {
    using namespace std;

    struct linkId {
        Addr src, dst;

        linkId();
        linkId(const Addr &_src, const Addr &_dst);

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
