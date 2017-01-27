#pragma once

#include "DIF/Routing/TSimpleRouting/TSimpleDV/TSimpleDV.h"

class int_TSimpleDV : public TSimpleDV::TSimpleDV<int> { public : int_TSimpleDV(); };
class uint_TSimpleDV : public TSimpleDV::TSimpleDV<unsigned int> { public : uint_TSimpleDV(); };
class short_TSimpleDV : public TSimpleDV::TSimpleDV<short> { public : short_TSimpleDV(); };
class ushort_TSimpleDV : public TSimpleDV::TSimpleDV<unsigned short> { public : ushort_TSimpleDV(); };
class double_TSimpleDV : public TSimpleDV::TSimpleDV<double> { public : double_TSimpleDV(); };
