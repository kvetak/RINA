#pragma once

#include <omnetpp.h>

using namespace std;

class SigFlow : public cObject {
public:
    string src, dst, qos;
    int flowID;
    bool on;
    double rate;

    SigFlow(string _src, string _dst, string _qos, int _flowID, bool _on, double _rate ) :
        src(_src), dst(_dst), qos(_qos), flowID(_flowID), on(_on), rate(_rate) {}
};
class SigPDU : public cObject {
public:
    string src, dst, qos;
    int flowID;
    int status;
    long data;
    double delay;

    SigPDU(string _src, string _dst, string _qos, int _flowID, int _status, long _data, double _delay ) :
        src(_src), dst(_dst), qos(_qos), flowID(_flowID), status(_status), data(_data), delay(_delay) {}
};
