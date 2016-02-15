// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <IntPDUForwarding.h>

#include <map>
#include <string>
#include <vector>
#include <map>

#include "DCAddr.h"
#include "DC_Defines.h"
#include "Exceptions.h"
#include "RawExceptions.h"
#include "Cache.h"

namespace REFwdDC {

using namespace std;
using namespace NSPSimpleDC;

    class RuleExceptionsFWD: public IntPDUForwarding {

    public:
        RuleExceptionsFWD();
        virtual ~RuleExceptionsFWD();

        void setNodeInfo(const DCAddr & n_addr);

        // Lookup function, return a list of RMTPorts to forward a PDU/Address+qos.
        vector<Port> lookup(const PDU * pdu);
        vector<Port> lookup(const Address & dst, const std::string & qos);

        // Returns a representation of the Forwarding Knowledge
        virtual string toString();

        virtual bool setNeigh(const DCAddr & n_addr, Port port) = 0;
        void setExceptions(const RawExceptionsList & exceptions);

    protected:
        DCAddr Im;

        ExceptionTable exceptionsT;

        Port * myports;
        unsigned char myportsSyze;

        Cache cache;
        simtime_t cacheLivespan;

        void onPolicyInit();
        virtual void initializeSubPolicy() = 0;

        virtual void handleMessage(cMessage * msg);

        virtual portList search(const DCAddr & n_addr);

        virtual portList readException(const Exception & e) = 0;
        virtual portList readRawException(const RawException & raw) = 0;
        virtual portList executeRule(const DCAddr & n_addr) = 0;

        virtual Exception computeException(const RawException & raw) = 0;

        portList directList(const portId &  p);


        void refreshCache(const DCAddr & addr, portList oldPorts, portList newPorts);


        portList inverseList(portList list, portId a, portId b);

        void finish();
    };

}
