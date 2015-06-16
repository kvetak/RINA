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

#ifndef __RINA_AEData_H_
#define __RINA_AEData_H_

#include "AESInt.h"
#include <vector>

namespace AEData {

using namespace std;

typedef double (*RNG_function)(double, double, int rng);

class Stream {
public:
    Stream();

    void setWaiting();
    void setSending();

    void setBrt(double);

    void setDataS(int);
    void setVarDataS(double);
    void setRNG(RNG_function);

    void setWaitT(double);
    void setVarWaitT(double);
    void setWTRNG(RNG_function);

    int getid();
    bool getState();

    int getRemaining();
    int getNextPDU(int);
    double getWt(int);
    double getWait();

    void compute();


private:
    static int nextId;
    int id;

    bool state;

    double wt, brt;

    int wData;

    int dataS;
    double varDataS;
    int minDataS, maxDataS;

    double waitT;
    double varWaitT;
    int minWaitT, maxWaitT;

    RNG_function rng, rngwt;
};

typedef vector<Stream> sVec;
typedef sVec::iterator sVecIt;

class State_Change : public _AESInt_self {
public:
    int streamId;
    bool newState;
    State_Change(int, bool);
};

class Stream_Timer : public _AESInt_self {
public:
    int streamId;
    Stream_Timer(int);
};

class AEData : public AESInt {
protected :
    sVec streams;
    simtime_t startVar;

    void doIni();
    void doFin();
    void iniCom();

    void processMsg(_AESInt_self *);
};

}
#endif
