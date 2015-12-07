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

#ifndef AUTHLISTENERS_H_
#define AUTHLISTENERS_H_

#include <omnetpp.h>
#include "Auth.h"

class Auth;
class AuthListeners : public cListener {
public:
    AuthListeners(Auth* nauth);
    virtual ~AuthListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj) {
                   EV << "Signal to CACE initiated by " << src->getFullPath() << endl;
            }
protected:
    Auth* auth;
};

class LisAuthValidate: public AuthListeners {
public:
    LisAuthValidate(Auth* nauth): AuthListeners(nauth){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);

};

#endif /* AUTHLISTENERS_H_ */
