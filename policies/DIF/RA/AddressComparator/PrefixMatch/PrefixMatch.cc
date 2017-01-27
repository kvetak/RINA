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

#include "DIF/RA/AddressComparator/PrefixMatch/PrefixMatch.h"
#include "Common/Utils.h"

Define_Module(PrefixMatch);

void PrefixMatch::onPolicyInit()
{
    any = par("any").stdstringValue();
    std::string del = par("delimiter").stdstringValue();
    if(del.length() > 0 && del.at(0)!= ' '){
        delimiter = del.at(0);
    } else {
        delimiter = '.';
    }

    thisIPCAddrParsed = split(thisIPCAddr.getIpcAddress().getName(), delimiter);
}

bool PrefixMatch::matchesThisIPC(const Address& addr, PDU * pdu)
{
    if(addr == thisIPCAddr){
        return true;
    }

    std::vector<std::string> addrParsed  = split(addr.getIpcAddress().getName(), delimiter);

    std::vector<std::string>::iterator itS = addrParsed.begin();
    std::vector<std::string>::iterator itM = thisIPCAddrParsed.begin();

    while(itS != addrParsed.end() && itM != thisIPCAddrParsed.end()){
        if(*itS == any){
            return true;
        } else if(*itS != *itM){
            return false;
        }
        itS++;
        itM++;
    }

    return (itS == addrParsed.end() && itM == thisIPCAddrParsed.end());
}
