
#include "DIF/RMT/PDUForwarding/SimpleDCForwarding/DCAddr.h"
#include "Common/Utils.h"

namespace NSPSimpleDC {

    using namespace std;

    DCAddr::DCAddr(): type(-1), a(0), b(0){}

    DCAddr::DCAddr(const int &_type, const int &_a, const int &_b):
            type(_type), a(_a), b(_b){}

    DCAddr::DCAddr(const string &saddr) {
        vector<string> s_vec = split(saddr, '.');
        if(s_vec.size() != 3) {
            type = -1;
        } else {
            type = atoi(s_vec[0].c_str());
            a = atoi(s_vec[1].c_str());
            b = atoi(s_vec[2].c_str());
        }
    }

    bool DCAddr::operator<( const DCAddr & o ) const {
        if(type < o.type) { return true; }
        if(type > o.type) { return false;}

        if(a < o.a) { return true; }
        if(a > o.a) { return false;}

        if(b < o.b) { return true; }

        return false;
    }

    bool DCAddr::operator==( const DCAddr & o ) const {
        return (type == o.type && a == o.a && b == o.b);
    }

    bool DCAddr::operator!=( const DCAddr & o ) const {
        return (type != o.type || a != o.a || b != o.b);
    }

    string DCAddr::toString() {
        return to_string (type) + "." +to_string (a)  + "." +to_string (b);
    }

    std::ostream& operator << (std::ostream &o, const DCAddr &a) {
      o << a.type << "." << a.a << "."<<a.b;
      return o;
    }
}
