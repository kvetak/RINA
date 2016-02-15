#include "GDC_RawExceptions.h"

namespace GDC {
    using namespace std;

    RawException::RawException(Addr _addr):
            addr(_addr), OK(true) {}

    RawException::RawException(Addr _addr, vecAddr _validNeis):
            addr(_addr), OK(false), validNeis(_validNeis) {}
}
