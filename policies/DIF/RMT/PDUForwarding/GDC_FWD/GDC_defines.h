#pragma once

#include <omnetpp.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "RMTPort.h"

#define  GDC_EXCEPTION_FLAG_NONE 0
#define  GDC_EXCEPTION_FLAG_UP 1
#define  GDC_EXCEPTION_FLAG_DOWN 2
#define  GDC_EXCEPTION_FLAG_UPDOWN 3
#define  GDC_EXCEPTION_FLAG_INVERSE 4

namespace GDC {
    using namespace std;

    typedef vector<bool> vbool;

    typedef unsigned char uchar;
    typedef unsigned short ushort;

    typedef vector<uchar> vecuchar;
    typedef set<uchar> setuchar;

    typedef vector<ushort> vecushort;
    typedef set<ushort> setushort;

    typedef vecuchar::iterator vecucharIt;
    typedef setuchar::iterator setucharIt;

    struct Addr {
        uchar a, b;

        Addr(const uchar &  _a= 0, const uchar &  _b = 0);
        Addr(const string & raw);

        bool operator >(const Addr & o) const;
        bool operator <(const Addr & o) const;
        bool operator ==(const Addr & o) const;
        bool operator !=(const Addr & o) const;

        string toString();
    };
    std::ostream& operator << (std::ostream &o, const Addr &a);

    typedef vector<Addr> vecAddr;
    typedef set<Addr> setAddr;

    typedef vecAddr::iterator vecDCAddrIt;
    typedef setAddr::iterator setDCAddrIt;


    typedef map<Addr, setAddr> Addr2setAddr;
    typedef map<uchar, setuchar> uchar2setuchar;

    typedef Addr2setAddr::iterator Addr2setAddrIt;
    typedef uchar2setuchar::iterator uchar2setucharIt;

    typedef RMTPort * Port;
    typedef vector<Port> vecPort;
    typedef set<Port> setPort;
};
