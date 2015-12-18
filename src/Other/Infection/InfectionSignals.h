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

using namespace std;

class SendInfMsg  : public cObject {
public:

    string src, dst;
    int srcCepId;
    string qos;

    SendInfMsg(string _src, string _dst, int _srcCepId, string _qos) :
        src(_src), dst(_dst), srcCepId(_srcCepId), qos(_qos) {}
    ~SendInfMsg(){}
};

class RecvInfMsg  : public cObject {
public:

    string src, dst;
    int src_cepID;
    string qos;
    unsigned int seqN;

    simtime_t h_delay, p_delay;
    int pst_delay;

    RecvInfMsg(string _src, string _dst, int _cepID, string _qos,
           unsigned int _seqN,  simtime_t _h_delay, simtime_t _p_delay, int _pst_delay) :
        src(_src), dst(_dst), src_cepID(_cepID), qos(_qos),
        seqN(_seqN),
        h_delay(_h_delay),
        p_delay(_p_delay),
        pst_delay(_pst_delay){}
    ~RecvInfMsg(){}
};


class InfectedDataTransferPDU : public DataTransferPDU {
public:
    simtime_t sendT;
    bool signaled;
    int fcepID;
    double pathDelay;
    int pstDelay;

    InfectedDataTransferPDU(bool _signaled, int _fcepID, const char *name=NULL):
            DataTransferPDU(name, 0),
            signaled(_signaled),
            fcepID(_fcepID),
            pathDelay(0.0),
            pstDelay(0)
            {sendT = simTime();}
    InfectedDataTransferPDU(const InfectedDataTransferPDU& other) :
            DataTransferPDU(other),
            signaled(other.signaled),
            fcepID(other.fcepID),
            pathDelay(other.pathDelay),
            pstDelay(other.pstDelay)
            {sendT = other.sendT;}
    InfectedDataTransferPDU(const DataTransferPDU& other) :
            DataTransferPDU(other),
            pathDelay(0.0),
            pstDelay(0)
            {sendT = simTime(); fcepID = 0; signaled = false;}

    void addPSTdelay(int hd) {
        pstDelay += hd;
    }

    virtual InfectedDataTransferPDU *dup() const {return new InfectedDataTransferPDU(*this);}
};
