#include <dummyRouting/dummyRouting.h>

Register_Class(dummyRouting);

bool dummyRouting::processUpdate(IntRoutingUpdate * update) {
    return false;
}
void dummyRouting::onPolicyInit(){}
