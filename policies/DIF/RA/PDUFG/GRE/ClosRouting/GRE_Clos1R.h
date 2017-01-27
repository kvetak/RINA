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

#pragma once

#include "DIF/RA/PDUFG/GRE/ClosRouting/GRE_ClosR.h"

namespace GRE_Clos {

using namespace GRE;
using namespace std;

class GRE_ClosR1: public GRE_ClosR {
protected:
    virtual void postPolicyInit();
    virtual void resetNeiGroups();
    virtual index_t getNeiId(const addr_t & d);

    virtual void routingUpdated();

    Clos1 * fwd_;
};

}
