#include "GDC_defines.h"
#include "Utils.h"

namespace GDC {
    using namespace std;
    Addr::Addr(const uchar & _a, const uchar &  _b):a(_a), b(_b){};

    Addr::Addr(const string & raw) {
        vector<string> s_vec = split(raw, '.');
        if(s_vec.size() != 2) { a = 0; b =0;
        } else {
            a = (uchar)atoi(s_vec[0].c_str());
            b = (uchar)atoi(s_vec[1].c_str());
        }
    }

    bool Addr::operator >(const Addr & o) const {
        if(a > o.a) { return true; }
        if(a < o.a) { return false; }
        return b > o.b;
    }

    bool Addr::operator <(const Addr & o) const {
        if(a < o.a) { return true; }
        if(a > o.a) { return false; }
        return b < o.b;
    }

    bool Addr::operator ==(const Addr & o) const {
        return a == o.a && b == o.b;
    }

    bool Addr::operator !=(const Addr & o) const {
        return a != o.a && b != o.b;
    }


    string Addr::toString() {
        return to_string ((int)a)  + "." +to_string ((int)b);
    }

    std::ostream& operator << (std::ostream &o, const Addr &a) {
      o << to_string ((int)a.a)  + "." +to_string ((int)a.b);
      return o;
    }
};
