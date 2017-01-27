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

#include "DIF/RMT/PDUForwarding/GREFWD/GRE_Helpers.h"


string getRawAddr_t(const addr_t & dst_addr) {
    stringstream sstream;
    sstream << hex << dst_addr;
    string dst_raw = sstream.str();
    while(dst_raw.size()<4) { dst_raw = "0"+dst_raw; }
    return dst_raw;
}

bool subAddrSet(const set<addr_t> & search, const set<addr_t> & in) {
    auto ita = search.begin();
    auto itb = in.end();

    while(ita != search.end() && itb != in.end()) {
        if(*ita == *itb) { ita++; itb++; }
        else if(*ita > *itb) { itb++; }
        else { return false; }
    }
    return ita == search.end();
}
