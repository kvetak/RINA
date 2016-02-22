#include "GDCPathLookUp.h"
#include "Utils.h"


void GDC_Server_PathLookUp::initialize() {
    DCName = par("DCName").stdstringValue();
    MyPrefix = par("MyPrefix").stdstringValue();
    string TorAddr = MyPrefix + ".0";
    ToRAddress = Address(TorAddr.c_str(), DCName.c_str());
}
std::vector<PathLookupEntry> GDC_Server_PathLookUp::lookUp(Flow * f) {
    std::vector<PathLookupEntry> ret;
    ret.push_back(PathLookupEntry(ToRAddress, computeReq(f) ));
    return ret;
}

QoSReq GDC_Server_PathLookUp::computeReq(Flow * f) { return f->getQosReqs(); }


void GDC_ToR_PathLookUp::initialize() {
    DCName = par("DCName").stdstringValue();
    MyPrefix = par("MyPrefix").stdstringValue();
}

std::vector<PathLookupEntry> GDC_ToR_PathLookUp::lookUp(Flow * f) {
    std::vector<PathLookupEntry> ret;
    string dstA = f->getDstAddr().getIpcAddress().getName();
    vector<string> parsed = split(dstA, '.');

    if(parsed[0] == MyPrefix) {
        ret.push_back(PathLookupEntry(f->getDstAddr(), computeReq(f) ));
    } else {
        string neiTor = parsed[0] + ".0";
        Address dstToR(neiTor.c_str(), DCName.c_str());
        ret.push_back(PathLookupEntry(dstToR, computeReq(f) ));
    }

    return ret;
}


QoSReq GDC_ToR_PathLookUp::computeReq(Flow * f) { return f->getQosReqs(); }
