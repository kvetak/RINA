#pragma once

#include <string>

namespace NSPSimpleDC {

using namespace std;

    struct DCAddr {
        int type, a, b;

        DCAddr();
        DCAddr(const int &_type, const int &_a, const int &_b);
        DCAddr(const string &saddr);

        bool operator<( const DCAddr &n ) const;
        bool operator==( const DCAddr &n ) const;
        bool operator!=( const DCAddr &n ) const;

        string toString();
    };

    std::ostream& operator << (std::ostream &o, const DCAddr &a);
}
