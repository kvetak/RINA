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

#ifndef __RINA_AEBStream_H_
#define __RINA_AEBStream_H_

#include "AESInt.h"
#include <vector>

namespace AEBStream {

using namespace std;

typedef double (*RNG_function)(double, double, int rng);

class Stream {
public:
    Stream();

    void setState(bool);

    void setBrt(double);

    void setPduS(int);
    void setVarPduS(double);
    void setRNG(RNG_function);

    void setBurstS(int);
    void setVarBurstS(double);
    void setBRNG(RNG_function);

    void setBurstProb(double);

    int getid();
    bool getState();
    double getWt(int size);
    int getPDU();
    int getBurst();
    double getBurstProb();

    void compute();


private:
    static int nextId;
    int id;

    bool state;

    double wt, brt;

    int pduS, burstS;
    double varPduS, varBurstS;
    double burstProb;

    int minPduS, maxPduS;
    int minBurstS, maxBurstS;

    RNG_function rng, rngb;
};

typedef vector<Stream> sVec;
typedef sVec::iterator sVecIt;


class Stream_Timer : public _AESInt_self {
public:
    int streamId;
    Stream_Timer(int);
};

class AEBStream : public AESInt {
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
