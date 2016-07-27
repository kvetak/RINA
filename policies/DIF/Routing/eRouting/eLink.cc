
#include "eLink.h"

elink_t getELink(const eaddr_t & a, const eaddr_t & b) {
    return (a<=b)?
            ((a << 16) & 0xFFFF0000) | (b & 0x0000FFFF)
                :
            ((b << 16) & 0xFFFF0000) | (a & 0x0000FFFF);
}
