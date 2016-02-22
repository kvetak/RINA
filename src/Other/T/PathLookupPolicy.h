#pragma once
#include <Flow.h>
#include <vector>

struct PathLookupEntry {
    Address neighbour;
    QoSReq requirements;
    PathLookupEntry (const Address & _neighbour, const QoSReq & _requirements):
        neighbour(_neighbour), requirements(_requirements) {};
};

class PathLookupPolicy :public cModule {
public :
    //Look up for next neighbour and N-1 requirements to reach flow dstAddr
    //Default : Next neighbour = dstAddr, requirements = flow requirements
    virtual std::vector<PathLookupEntry> lookUp(Flow * f) {
        std::vector<PathLookupEntry> ret;
        ret.push_back(PathLookupEntry(f->getDstAddr(), f->getQosReqs()));
        return ret;
    }
};
