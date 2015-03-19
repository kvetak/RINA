#include <dummyRouting/dummyRouting.h>

Register_Class(dummyRouting);

bool dummyRouting::processUpdate(const IntRoutingUpdate * update) {
    return false;
}
void dummyRouting::onIni(){}
