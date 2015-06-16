#pragma once

#include <string>
#include <vector>
#include "CDAP.h"

using namespace std;

class HelloMsg : public CDAP_M_Read {
public:
    string src;
    string dif;
    HelloMsg(string _src, string _dif) : src(_src), dif(_dif) {}
};


class reqFlowMsg : public CDAP_M_Read {
public:
    string src;
    string dif;
    vector<string> flowsDstAppName;

    reqFlowMsg(string _src, string _dif) : src(_src), dif(_dif) {}
};
