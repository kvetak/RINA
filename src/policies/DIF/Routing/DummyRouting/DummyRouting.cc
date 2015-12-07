#include <DummyRouting/DummyRouting.h>

Register_Class(DummyRouting);

bool DummyRouting::processUpdate(IntRoutingUpdate * update) {
    return false;
}
void DummyRouting::onPolicyInit(){}
