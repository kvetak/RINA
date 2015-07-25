#pragma once

#include <string>
#include <set>

namespace common_GraphCL {

using namespace std;

template <class T>
struct nhLMetric  {
    T metric;
    set<string> nh;
    nhLMetric(){}
    nhLMetric(const T & m, const set<string> & n) : metric(m), nh(n) {}
};

} /* namespace common_GraphCL */
