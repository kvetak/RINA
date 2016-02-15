#include "RawExceptions.h"

namespace REFwdDC {

    using namespace std;
    using namespace NSPSimpleDC;

    RawException::RawException(DCAddr _addr):
            addr(_addr), OK(true) {}
    RawException::RawException(DCAddr _addr, vector<DCAddr> _validNeis):
            addr(_addr), OK(false), validNeis(_validNeis) {}

}
