//
// Copyright � 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file RIBd.cc
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief Kind of a Notification Board for DIF
 * @detail
 */

#include "RIBd.h"

Define_Module(RIBd);

void RIBd::initialize() {
    //Init CDAP gates and connections
    initCdapBindings();
}

void RIBd::handleMessage(cMessage *msg) {

}

void RIBd::initCdapBindings() {

    //Get RIBDaemon gates
    cModule* RibD = this->getParentModule();
    cGate* gRibdIn = RibD->gateHalf(GATE_RMTIO, cGate::INPUT);
    cGate* gRibdOut = RibD->gateHalf(GATE_RMTIO, cGate::OUTPUT);

    //CDAPParent Module gates
    cModule* Cdap = RibD->getSubmodule(MOD_CDAP);
    cGate* gCdapParentIn;
    cGate* gCdapParentOut;
    Cdap->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gCdapParentIn, *&gCdapParentOut);

    //CDAPSplitter gates
    cModule* CdapSplit = Cdap->getSubmodule(MOD_CDAPSPLIT);
    cGate* gSplitIn;
    cGate* gSplitOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_SOUTHIO, false, true, *&gSplitIn, *&gSplitOut);
    cGate* gSplitCaceIn;
    cGate* gSplitCaceOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_CACEIO, false, true, *&gSplitCaceIn, *&gSplitCaceOut);
    cGate* gSplitAuthIn;
    cGate* gSplitAuthOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_AUTHIO, false, true, *&gSplitAuthIn, *&gSplitAuthOut);
    cGate* gSplitCdapIn;
    cGate* gSplitCdapOut;
    CdapSplit->getOrCreateFirstUnconnectedGatePair(GATE_CDAPIO, false, true, *&gSplitCdapIn, *&gSplitCdapOut);

    //CACE Module gates
    cModule* CdapCace = Cdap->getSubmodule(MOD_CDAPCACE);
    cGate* gCaceIn;
    cGate* gCaceOut;
    CdapCace->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gCaceIn, *&gCaceOut);

    //AUTH Module gates
    cModule* CdapAuth = Cdap->getSubmodule(MOD_CDAPAUTH);
    cGate* gAuthIn;
    cGate* gAuthOut;
    CdapAuth->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gAuthIn, *&gAuthOut);

    //CDAP Module gates
    cModule* CdapCdap = Cdap->getSubmodule(MOD_CDAPCDAP);
    cGate* gCdapIn;
    cGate* gCdapOut;
    CdapCdap->getOrCreateFirstUnconnectedGatePair(GATE_SPLITIO, false, true, *&gCdapIn, *&gCdapOut);

    //Connect gates together
    gRibdIn->connectTo(gCdapParentIn);
    gCdapParentIn->connectTo(gSplitIn);

    gSplitOut->connectTo(gCdapParentOut);
    gCdapParentOut->connectTo(gRibdOut);

    gSplitCaceOut->connectTo(gCaceIn);
    gCaceOut->connectTo(gSplitCaceIn);

    gSplitAuthOut->connectTo(gAuthIn);
    gAuthOut->connectTo(gSplitAuthIn);

    gSplitCdapOut->connectTo(gCdapIn);
    gCdapOut->connectTo(gSplitCdapIn);

}
