#include "IntBbPDUFG.h"

void IntBbPDUFG::onPolicyInit(){

    //Set Forwarding policy
    fwd = check_and_cast<IntBbPDUForwarding *>(getModuleByPath("^.pduForwardingPolicy"));
    //Set Routing policy
    routing = check_and_cast<IntBbRouting *>(getModuleByPath("^.routingPolicy"));

    onBIni();
}
