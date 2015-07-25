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

#ifndef dlCUInfo_H_
#define dlCUInfo_H_

#include <omnetpp.h>

#include <string>
#include <map>
#include <vector>
#include <list>

namespace DQMonitor {

using namespace std;


struct ILimVals {
    double index;
    long long rate; // bps
    long long spaceRate; //bps
    double spaceVar; //[0..1]
    double dropProb; //[0..1]

    ILimVals(double i, long long r, long long sr, double sv, double p);
};

struct IDropProb {
    int index;
    double prob;

    IDropProb(int i, double p);
};

struct PP {
    int priority;
    double probability;

    PP(int prio, double prob);
};

typedef vector<PP> PPlist;
typedef PPlist::iterator PPlistIt;

struct IDegrad {
    double index;
    PPlist PPs;

    IDegrad(double i);
    int getRandomPriority (int def);
};

template <typename T> bool compareIndex(const T& a, const T& b);


typedef vector<ILimVals> ILimValsList;
typedef vector<IDropProb> IDropProbList;
typedef vector<IDegrad> IDegradList;

typedef ILimValsList::iterator ILimValsIt;
typedef IDropProbList::iterator IDropProbIt;
typedef IDegradList::iterator IDegradIt;

struct Times {
    double serveT;
    double spaceT;

    Times();
    Times(double se, double sp);
};

class L {
private:
    bool limit, space;

    ILimValsList vl;
    IDropProbList dl;

public:
    L();
    L(bool lim, bool spa, ILimValsList v, IDropProbList d);

    bool needRate();
    bool spaces();
    bool limits();
    Times getTimes(double wt, int size);
    double getDropProb(double wt, int ws);
};

class C {
private:
    double defaultDropProb;
    IDropProbList dl;

public:
    C();
    C(double dd, IDropProbList d);

    double getDropProb(int s);
};

class U {
private:
    int defaultPriority;

    bool degrad;

    long long rate;
    IDegradList dl;

public:
    U();
    U(int dp, bool deg, long long r, IDegradList d);

    bool isDegraded();
    double getTime(int size);
    int getPriority(double wt);
};

class dlCUInfo {
public:
    string queueName;
    L * limit;
    C * cherish;
    U * urgency;

    dlCUInfo();
    dlCUInfo(string qn, L * l, C * c, U * u);
};

}
#endif /* SIMPLEMONITOR_H_ */
