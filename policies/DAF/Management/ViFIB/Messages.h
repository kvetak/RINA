#pragma once

#include <string>
#include "CDAPMessage_m.h"

namespace ViFIB{

using namespace std;

struct miniInfo {
    string vifibId;
    string location;
    string cAddr;
    string bAddr;
};

struct vifibInfo {
    string location;

    int cloud_addr;
    string cloud_id;

    bool isBorder;
    int border_addr;
    string border_id;

    vifibInfo()
        : location(""), cloud_id(""), isBorder(false), border_id(""){}
    vifibInfo(const string & loc, const string & c_id)
        : location(loc), cloud_id(c_id), isBorder(false), border_id(""){}
    vifibInfo(const string & loc, const string & c_id, const string & b_id)
        : location(loc), cloud_id(c_id), isBorder(true), border_id(b_id){}
};


// VIFIB <-> Master Messages

class _vifibMessage : public  CDAPMessage {
public:
    string VifibId;
    _vifibMessage(const string & _dstVifibId) : VifibId(_dstVifibId) {}
};


class vifibConnect : public _vifibMessage {
public:
    vector<vifibInfo> dsts;

    vifibConnect(const string & _dstVifibId)
        : _vifibMessage(_dstVifibId){}
};

class vifibDisconnect : public _vifibMessage {
public:
    vector<string> dsts;

    vifibDisconnect(const string & _dstVifibId)
        : _vifibMessage(_dstVifibId) {}
};

class vifibHello : public _vifibMessage  {
public:
    string location;

    vifibHello(const string & _id, const string & _location)
        : _vifibMessage(_id), location(_location) {}
};

class vifibBye : public _vifibMessage  {
public:
    vifibBye(const string & _id)
        : _vifibMessage(_id) {}
};

class vifibIniValues : public _vifibMessage {
public:
    string cloudAddr, cloudDIF;
    string backboneAddr, backboneDIF;
    bool isBorder;

    vifibIniValues(const string & _dstVifibId, const string & _cloudAddr, const string & _cloudDIF)
        : _vifibMessage(_dstVifibId), cloudAddr(_cloudAddr), cloudDIF(_cloudDIF), backboneAddr(""), backboneDIF(""), isBorder(false) {}

    vifibIniValues(const string & _dstVifibId, const string & _cloudAddr, const string & _cloudDIF,const string & _backboneAddr, const string & _backboneDIF)
        : _vifibMessage(_dstVifibId), cloudAddr(_cloudAddr), cloudDIF(_cloudDIF), backboneAddr(_backboneAddr), backboneDIF(_backboneDIF), isBorder(true) {}
};


// Master <-> Core Messages

class _masterMessage : public  CDAPMessage {
public:
    string zoneId;
    _masterMessage(const string & _zoneId) : zoneId(_zoneId) {}
};

class masterHello : public _masterMessage  {
public:
    masterHello(const string & _id)
        : _masterMessage(_id) {}
};

class masterNewBorder : public _masterMessage  {
public:
    string vifib;
    string bAddr;

    masterNewBorder(const string & _id, const string & _vifib, const string & _bAddr)
        : _masterMessage(_id), vifib(_vifib), bAddr(_bAddr) {}
};

class masteRemovedBorder : public _masterMessage  {
public:
    string vifib;
    string bAddr;

    masteRemovedBorder(const string & _id, const string & _vifib, const string & _bAddr)
        : _masterMessage(_id), vifib(_vifib), bAddr(_bAddr) {}
};

class masteBordersList : public _masterMessage  {
public:
    map<string, vector<miniInfo> > borders;

    masteBordersList(const string & _id)
        : _masterMessage(_id) {}
};

class masterConenctTo : public _masterMessage  {
public:
    string dstZone;

    masterConenctTo(const string & _id, const string & _dst)
        : _masterMessage(_id), dstZone(_dst) {}
};

}
