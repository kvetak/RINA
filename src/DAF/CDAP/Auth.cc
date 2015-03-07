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

void Auth::initParameters() {
    AE* iae = dynamic_cast<AE*>(this->getParentModule()->getParentModule()->getSubmodule(MOD_IAE));

    //assign authentication parameters from iae
    if (iae) {
        authType = iae->par("authType");
        authName = iae->par("authName").stringValue();
        authPassword = iae->par("authPassword").stringValue();
        authOther = iae->par("authOther").stringValue();
    }
}

void Auth::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}

void Auth::validate(CDAPMessage *cmsg) {
    Enter_Method("validate()");
    CDAP_M_Connect* cmsgC = check_and_cast<CDAP_M_Connect*>(cmsg);

    //create new M_Connect_R for passing parameters to cace
    CDAP_M_Connect_R* cmsgCR = new CDAP_M_Connect_R();
    result_t result;

    //check and validate expected auth type
    if (cmsgC->getAuth().authType == authType) {
        //none auth option
        if (cmsgC->getAuth().authType == AUTH_NONE) {
            result.resultReason = "success";
            result.resultValue = R_SUCCESS;

        }
        //passwd auth option
        else if (cmsgC->getAuth().authType == AUTH_PASSWD) {
            //correct pass
            if (!strcmp(cmsgC->getAuth().authValue.authPassword.c_str(), authPassword.c_str())) {
                result.resultReason = "success";
                result.resultValue = R_SUCCESS;
            }
            else {
                result.resultReason = "fail";
                result.resultValue = R_FAIL;
            }
        }
        //TODO: support for other options
    }
    //unexpected auth
    else {
        result.resultReason = "fail";
        result.resultValue = R_FAIL;
    }

    cmsgCR->setAbsSyntax(GPB);
    cmsgCR->setOpCode(M_CONNECT_R);
    cmsgCR->setResult(result);
    cmsgCR->setAuth(cmsgC->getAuth());
    cmsgCR->setHandle(cmsgC->getHandle());

    signalizeAuthResult(cmsgCR);
}

void Auth::signalizeAuthResult(CDAPMessage *cmsg) {
    emit(sigAuthRes, cmsg);
}
