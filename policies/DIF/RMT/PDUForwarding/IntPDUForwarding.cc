#include "IntPDUForwarding.h"

IntPDUForwarding::IntPDUForwarding(){}

IntPDUForwarding::~ IntPDUForwarding(){}

void IntPDUForwarding::initialize(){
    // Display active policy name.
    cDisplayString& disp = getDisplayString();
    disp.setTagArg("t", 1, "t");
    disp.setTagArg("t", 0, getClassName());

    onPolicyInit();
}
