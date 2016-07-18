#include "Flow_t.h"
#include "OFMessages.h"


pduReq::pduReq () :
    f(nullptr), data(nullptr) {}

pduReq::pduReq (Flow_t * _f, Inj_data * _data ) :
    f(_f), data(_data) {}


pduReq Flow_t::act(ONOFInj * parent, bool fin) { return pduReq(); }
pduReq Flow_t::ret(ONOFInj * parent, bool fin) { return pduReq(); }
pduReq Flow_t::sret(ONOFInj * parent, bool fin) { return pduReq(); }
pduReq Flow_t::ack(ONOFInj * parent, bool fin) { return pduReq(); }
