#pragma once

#include <omnetpp.h>

using namespace std;

class SigSend : public cObject {
public:
    string src, dst;

    SigSend(string _src, string _dst) :
        src(_src), dst(_dst) {}
};
class SigReceived : public cObject {
public:
    string src, dst;
    int hops;

    SigReceived(string _src, string _dst, int hops) :
        src(_src), dst(_dst) {}
};
