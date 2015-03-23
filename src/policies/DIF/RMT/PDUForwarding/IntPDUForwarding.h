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

#ifndef INTPDUFORWARDING_H_
#define INTPDUFORWARDING_H_

#include <omnetpp.h>

#include <vector>

#include "PDU.h"
#include "RMTPort.h"

class IntPDUForwarding  : public cSimpleModule {
public:

    // Constructor/Destructor
    IntPDUForwarding();
    ~IntPDUForwarding();

    // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
    virtual std::vector<RMTPort * > lookup(const PDU * pdu) = 0;
    virtual std::vector<RMTPort * > lookup(const Address &dst, const unsigned short &qos) = 0;
    // Returns a representation of the Forwarding Knowledge
    virtual std::string toString() = 0;

protected:
    // Initialize.
    void initialize();

    // Called after initialize
    virtual void onPolicyInit() = 0;
};

#endif /* INTPDUFORWARDING_H_ */
