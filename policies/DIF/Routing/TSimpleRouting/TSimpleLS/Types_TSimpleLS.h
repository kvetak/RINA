#pragma once

#include "DIF/Routing/TSimpleRouting/TSimpleLS/TSimpleLS.h"

class int_TSimpleLS : public TSimpleLS::TSimpleLS<int> { public : int_TSimpleLS(); };
class uint_TSimpleLS : public TSimpleLS::TSimpleLS<unsigned int> { public : uint_TSimpleLS(); };
class short_TSimpleLS : public TSimpleLS::TSimpleLS<short> { public : short_TSimpleLS(); };
class ushort_TSimpleLS : public TSimpleLS::TSimpleLS<unsigned short> { public : ushort_TSimpleLS(); };
class double_TSimpleLS : public TSimpleLS::TSimpleLS<double> { public : double_TSimpleLS(); };
