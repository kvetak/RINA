/*
 * IntRoutingUpdate.cc
 *
 *  Created on: Mar 18, 2015
 *      Author: gaixas1
 */

#include <IntRoutingUpdate.h>

IntRoutingUpdate::IntRoutingUpdate(){}
IntRoutingUpdate::IntRoutingUpdate(const Address &addr){
    dstAddr = addr;
}

IntRoutingUpdate::~IntRoutingUpdate(){}

// Getters.
Address IntRoutingUpdate::getDestination(){
    return dstAddr;
}
Address IntRoutingUpdate::getSource(){
    return srcAddr;
}

// Setters.
void IntRoutingUpdate::setDestination(Address addr){
    dstAddr = addr;
}
void IntRoutingUpdate::setSource(Address addr){
    srcAddr = addr;
}
