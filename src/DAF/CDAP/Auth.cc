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

#include "Auth.h"

Define_Module(Auth);

void Auth::initialize()
{
    initSignalsAndListeners();
}

void Auth::initSignalsAndListeners() {
    cModule* catcher = this->getParentModule()->getSubmodule(MOD_CDAPCACE);

    //Signals emitted by this module
    sigAuthRes = registerSignal(SIG_Auth_AuthenticationResponse);

    //Signals that this module is processing
    //authentication request from CACE module
    lisAuthValidate = new LisAuthValidate(this);
    catcher->subscribe(SIG_CACE_AuthenticationRequest, lisAuthValidate);
}

void Auth::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void Auth::validate(CDAPMessage *cmsg) {
    Enter_Method("validate()");
    CDAP_M_Connect* cmsgC = check_and_cast<CDAP_M_Connect*>(cmsg);

    CDAP_M_Connect_R* cmsgCR = new CDAP_M_Connect_R();
    result_t result;

    if (cmsgC->getAuth().authType == 0) {
        result.resultReason = "success";
        result.resultValue = 0;

    }
    else if (cmsgC->getAuth().authType == 1) {

    }

    cmsgCR->setResult(result);
    cmsgCR->setAuth(cmsgC->getAuth());
    cmsgCR->setHandle(cmsgC->getHandle());

    signalizeAuthResult(cmsgCR);
}

void Auth::signalizeAuthResult(CDAPMessage *cmsg) {
    emit(sigAuthRes, cmsg);
}
