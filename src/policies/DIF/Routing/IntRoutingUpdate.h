/*
 * IntRoutingUpdate.h
 *
 *  Created on: Mar 18, 2015
 *      Author: gaixas1
 */

#ifndef INTROUTINGUPDATE_H_
#define INTROUTINGUPDATE_H_

#include "Address.h"

class IntRoutingUpdate : public cObject {
protected:
    Address dstAddr;
    Address srcAddr;

public:
    IntRoutingUpdate();
    IntRoutingUpdate(Address addr);
    ~IntRoutingUpdate();

    // Getters.
    Address getDestination();
    Address getSource();

    // Setters.
    void setDestination(Address addr);
    void setSource(Address src);
};

#endif /* INTROUTINGUPDATE_H_ */
