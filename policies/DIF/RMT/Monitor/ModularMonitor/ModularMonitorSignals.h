//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

#include <omnetpp.h>

class HopDelayMsg  : public cObject {
public:

    std::string qos;
    int t;
    cModule * module;

    HopDelayMsg(std::string _qos, int _t, cModule * _module) : qos(_qos), t(_t), module(_module) {}
    ~HopDelayMsg(){}
};


class HopRcvMsg  : public cObject {
public:

    std::string qos;
    cModule * module;

    HopRcvMsg(std::string _qos, cModule * _module) : qos(_qos), module(_module) {}
    ~HopRcvMsg(){}
};

class HopLossMsg  : public cObject {
public:

    std::string qos;
    cModule * module;

    HopLossMsg(std::string _qos, cModule * _module) : qos(_qos), module(_module) {}
    ~HopLossMsg(){}
};
