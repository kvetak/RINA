//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef INTROUTING_H_
#define INTROUTING_H_

#include <omnetpp.h>

#include <vector>
#include <string>
#include "IntRoutingUpdate.h"



#include "Address.h"
#include "IntPDUFG.h"

class LisRoutingRecv;

class IntRouting  : public cSimpleModule {
    //Consts
    const char* SIG_RIBD_RoutingUpdate;
    const char* SIG_RIBD_RoutingUpdateReceived;

public:
    //Constructor/Destructor
    IntRouting();
    ~IntRouting();

    void receiveUpdate(const IntRoutingUpdate * update);

    //Process a Routing Update, return true => inform FWDG of the update
    virtual bool processUpdate(const IntRoutingUpdate * update) = 0;


protected:
    Address myAddress;

    // Initialize cons, signals, etc.
    void initialize();
    // Sends a Routing Update
    void sendUpdate(IntRoutingUpdate * update);

    // Called after initialize
    virtual void onIni() = 0;

private:
    LisRoutingRecv * listener;
    simsignal_t sigRoutingUpdate;
    IntPDUFG * fwdg;
};

/* Listener for routing updates.  */
class LisRoutingRecv : public cListener {
public:
    LisRoutingRecv(IntRouting * _module);
    void receiveSignal(cComponent *src, simsignal_t id, cObject *obj);
protected:
    IntRouting * module;
};

#endif /* INTROUTING_H_ */
