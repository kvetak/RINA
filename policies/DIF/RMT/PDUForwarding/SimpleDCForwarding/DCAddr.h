#pragma once

#include <string>
#include <vector>
#include <set>
#include <map>

namespace NSPSimpleDC {

using namespace std;

    typedef unsigned char uchar;
    typedef vector<uchar> vecuchar;
    typedef set<uchar> setuchar;

    typedef vecuchar::iterator vecucharIt;
    typedef setuchar::iterator setucharIt;

    struct DCAddr {
        char type;
        uchar a, b;

        DCAddr();
        DCAddr(const  char & _type, const uchar & _a, const uchar & _b);
        DCAddr(const string & s_addr);

        bool operator<( const DCAddr & n ) const;
        bool operator==( const DCAddr & n ) const;
        bool operator!=( const DCAddr & n ) const;

        string toString();
    };

    typedef vector<DCAddr> vecDCAddr;
    typedef set<DCAddr> setDCAddr;

    typedef vecDCAddr::iterator vecDCAddrIt;
    typedef setDCAddr::iterator setDCAddrIt;

    std::ostream& operator << (std::ostream &o, const DCAddr &a);

    typedef map<DCAddr, setDCAddr> Addr2setDCAddr;
    typedef map<uchar, setuchar> uchar2setuchar;

    typedef Addr2setDCAddr::iterator Addr2setDCAddrIt;
    typedef uchar2setuchar::iterator uchar2setucharIt;

    typedef vector<bool> vbool;
}
