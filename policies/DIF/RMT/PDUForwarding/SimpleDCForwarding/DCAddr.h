#pragma once

namespace NSPSimpleDC {

using namespace std;

    struct DCAddr {
        int type, a, b;

        DCAddr();
        DCAddr(const int & _type, const int & _a, const int & _b);
        DCAddr(const string & s_addr);

        bool operator<( const DCAddr & n ) const;
        bool operator==( const DCAddr & n ) const;
    };
}
