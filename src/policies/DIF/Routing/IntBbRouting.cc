#include "IntBbRouting.h"

void IntBbRouting::insertFlow(const Address &dst){
    insertFlow(dst, 0, 1);
}
void IntBbRouting::insertFlow(const Address &dst, const unsigned short &qos){
    insertFlow(dst, qos, 1);
}

void IntBbRouting::onIni(){
}
