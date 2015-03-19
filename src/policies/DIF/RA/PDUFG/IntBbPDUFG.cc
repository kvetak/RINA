#include "IntBbPDUFG.h"

void IntBbPDUFG::onIni(){

    //Set Forwarding policy
    fwd = check_and_cast<IntBbPDUForwarding *>(getModuleByPath("^.pduForwardingPolicy"));
    //Set Routing policy
    routing = check_and_cast<IntBbRouting *>(getModuleByPath("^.routingPolicy"));

    onBIni();
}
