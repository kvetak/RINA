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
#include "DataTransferPDU.h"

class SendInfMsg  : public cObject {
public:

    std::string qos;

    SendInfMsg(std::string _qos) : qos(_qos) {}
    ~SendInfMsg(){}
};

class RecvInfMsg  : public cObject {
public:

    std::string qos;
    simtime_t delay;
    int cepID;
    unsigned int seqN;

    RecvInfMsg(std::string _qos, simtime_t _delay, int _cepID, unsigned int _seqN) :
        qos(_qos), delay(_delay), cepID(_cepID), seqN(_seqN){}
    ~RecvInfMsg(){}
};


class InfectedDataTransferPDU : public DataTransferPDU {
public:
    simtime_t sendT;
    bool signaled;
    int fcepID;

    InfectedDataTransferPDU(bool _signaled, int _fcepID, const char *name=NULL):
            DataTransferPDU(name, 0),
            signaled(_signaled),
            fcepID(_fcepID)
            {sendT = simTime();}
    InfectedDataTransferPDU(const InfectedDataTransferPDU& other) :
            DataTransferPDU(other),
            signaled(other.signaled),
            fcepID(other.fcepID)
            {sendT = other.sendT;}
    InfectedDataTransferPDU(const DataTransferPDU& other) :
            DataTransferPDU(other)
            {sendT = simTime(); fcepID = 0; signaled = false;}

    virtual InfectedDataTransferPDU *dup() const {return new InfectedDataTransferPDU(*this);}
    ~InfectedDataTransferPDU(){};
};
