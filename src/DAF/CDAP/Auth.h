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

#ifndef __RINA_AUTH_H_
#define __RINA_AUTH_H_

#include <omnetpp.h>
#include "CDAPMessage_m.h"
#include "AuthListeners.h"
#include "ExternConsts.h"
#include "RINASignals.h"
#include "AE.h"


/**
 * TODO - Generated class
 */
class LisAuthValidate;
class Auth : public cSimpleModule
{
public:
    void validate(CDAPMessage *cmsg);
  protected:
    int authType;
    std::string authName;
    std::string authPassword;
    std::string authOther;

    simsignal_t sigAuthRes;

    LisAuthValidate* lisAuthValidate;
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void initSignalsAndListeners();
    void initParameters();
    void signalizeAuthResult(CDAPMessage *cmsg);
};

#endif
