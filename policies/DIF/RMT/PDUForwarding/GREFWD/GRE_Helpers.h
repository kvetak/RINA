// The MIT License (MIT)
//
// Copyright (c) 2014-2016 Brno University of Technology, PRISTINE project
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "DIF/RMT/RMTPort.h"

using namespace std;

typedef uint16_t addr_t;
typedef uint8_t index_t;
typedef uint8_t maskl_t;
typedef uint16_t rand_t;
typedef RMTPort * port_t;
typedef vector<port_t> vPorts;
typedef vector<index_t> vPortsIndex;
typedef vPortsIndex vGroups;
typedef map<addr_t, index_t> addrIndex;


enum exception_m { UNREACHABLE = 1, COMMON = 2, ANY = 3, GROUPA = 4, INVERSE = 5, INVERSEGROUP = 6};

struct mask_t {
    addr_t v;
    unsigned char l;
    mask_t(const addr_t & _v, const unsigned char &_l) : v(_v), l(_l) {}

    bool operator<(const mask_t & o) const {
        if(l > o.l) { return true; }
        if(l < o.l) { return false; }
        if(v < o.v) { return true; }
        return false;
    }

    bool operator==(const mask_t & o) const {
        return l == o.l && v == o.v;
    }
};

struct exception_t {
    exception_m mode;
    index_t group;
    vPortsIndex list;
    exception_t():
        mode(UNREACHABLE), group(0) {};
    exception_t(const exception_m & _mode, const index_t & _group):
        mode(_mode), group(_group) {};
    exception_t(const exception_m & _mode, const index_t & _group, const vPortsIndex & _list):
        mode(_mode), group(_group), list(_list){};
};

typedef exception_t* exception_p;

struct grouprange_t {
    index_t group, first, total;
    grouprange_t(const index_t & _group, const index_t & _first, const index_t & _total) :
        group(_group), first(_first), total(_total) {};
};

inline addr_t parseRawAddr(const string & raw) { return std::stoul (raw, nullptr, 16);}


inline addr_t getZone(const addr_t & a) { return a >> 8; }
inline addr_t getIdentifier(const addr_t & a){ return a & 0x00FF; }
inline addr_t getAddr(const addr_t & zone, const addr_t & id) { return id | (zone<<8); }


inline rand_t hashFlow(addr_t src, addr_t dst, addr_t src_cepid, addr_t dst_cepid) { return src ^ dst ^ src_cepid ^ dst_cepid; }


struct addr_s {
    addr_t addr;
    addr_t Z;
    addr_t Id;

    addr_s(const addr_t & raw) :
        addr(raw), Z(getZone(raw)), Id(getIdentifier(raw)) {}
};

string getRawAddr_t(const addr_t & dst_addr);

bool subAddrSet(const set<addr_t> & search, const set<addr_t> & in);
