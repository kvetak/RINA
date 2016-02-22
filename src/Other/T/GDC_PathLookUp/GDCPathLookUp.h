#pragma once
#include "PathLookupPolicy.h"

using namespace std;

class GDC_Server_PathLookUp : public PathLookupPolicy{
public:
    void initialize();
    virtual vector<PathLookupEntry> lookUp(Flow * f);
protected:
    string DCName;
    string MyPrefix;
    Address ToRAddress;

    QoSReq computeReq(Flow * f);
};

class GDC_ToR_PathLookUp : public PathLookupPolicy{
public:
    void initialize();
    virtual vector<PathLookupEntry> lookUp(Flow * f);

protected:
    string DCName;
    string MyPrefix;

    QoSReq computeReq(Flow * f);
};
