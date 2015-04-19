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

#ifndef INTBbPDUFTG_H_
#define INTBBPDUFTG_H_

#include <omnetpp.h>

#include "IntPDUFG.h"
#include "IntBbPDUForwarding.h"
#include "IntBbRouting.h"

class IntBbPDUFG  : public IntPDUFG {
public:

protected:
    IntBbPDUForwarding * fwd;
    IntBbRouting * routing;
    void onPolicyInit();
    virtual void onBIni() = 0;
};

#endif /* INTBbPDUFTG_H_ */
