#pragma once

#include "DIF/Routing/TDomainRouting/TDomainRouting.h"

class int_TDomain : public tDomain::TDomainRouting<int> { public : int_TDomain(); };
class uint_TDomain : public tDomain::TDomainRouting<unsigned int> { public : uint_TDomain(); };
class short_TDomain : public tDomain::TDomainRouting<short> { public : short_TDomain(); };
class ushort_TDomain : public tDomain::TDomainRouting<unsigned short> { public : ushort_TDomain(); };
class double_TDomain : public tDomain::TDomainRouting<double> { public : double_TDomain(); };
