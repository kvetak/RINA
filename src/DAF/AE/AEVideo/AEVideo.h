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

#ifndef __RINA_AEVideo_H_
#define __RINA_AEVideo_H_

#include "AESInt.h"
#include <vector>

namespace AEVideo {

using namespace std;

typedef double (*RNG_function)(double, double, int rng);

class Stream {
public:
    Stream();

    void setFps(double);
    void setBrt(double);
    void setVarFrameS(double);
    void setRNG(RNG_function);

    int getid();
    double getWt();
    int getNextFrame();

    void compute();


private:
    static int nextId;
    int id;

    double wt, brt;

    double varFrameS;
    double minFrameS, maxFrameS;

    RNG_function rng;
};

typedef vector<Stream> sVec;
typedef sVec::iterator sVecIt;

class Stream_Timer : public _AESInt_self {
public:
    int streamId;
    Stream_Timer(int);
};

class AEVideo : public AESInt {
protected :
    sVec streams;
    simtime_t startVar;

    int k;

    void doIni();
    void doFin();
    void iniCom();

    void processMsg(_AESInt_self *);
};

}
#endif
