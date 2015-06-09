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

#ifndef CACELISTENERS_H_
#define CACELISTENERS_H_

#include <omnetpp.h>

#include "CACE.h"


class CACE;
class CACEListeners : public cListener {
public:
    CACEListeners(CACE* ncace);
    virtual ~CACEListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj) {
               EV << "Signal to CACE initiated by " << src->getFullPath() << endl;
        }
      protected:
        CACE* cace;
};

class LisCACESendData : public CACEListeners {
public:
    LisCACESendData(CACE* ncace): CACEListeners(ncace){};
    virtual void receiveSignal(cComponent *src, simsignal_t id,  cObject *obj);
};

#endif /* CACELISTENERS_H_ */
