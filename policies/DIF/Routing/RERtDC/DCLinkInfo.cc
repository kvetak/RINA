#include "DCLinkInfo.h"

namespace RERtDC {

    linkId::linkId():
            src(DCAddr()), dst(DCAddr()){}

    linkId::linkId(const DCAddr &_src, const DCAddr &_dst) {
        if(_src.type < _dst.type) {
            src =_src;
            dst =_dst;
        } else {
            src =_dst;
            dst =_src;
        }
    }

    bool linkId::operator<(const linkId & o) const {
        if(src < o.src) { return true; }
        if(o.src < src) { return false; }
        if(dst < o.dst) { return true; }

        return false;
    }

    bool linkId::operator==(const linkId & o) const {
        return src==o.src && dst==o.dst;
    }

    bool linkId::operator!=(const linkId & o) const {
        return src!=o.src || dst!=o.dst;
    }


    linkInfo::linkInfo():
        link(), status(true), timestamp(-1){}

    linkInfo::linkInfo(const linkId &_link, const bool &_status, const long &_timestamp):
        link(_link), status(_status), timestamp(_timestamp){}

}
