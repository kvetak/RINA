//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "PrefixMatch.h"

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

bool PrefixMatch::matchesThisIPC(const Address& addr)
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

std::vector<std::string> &PrefixMatch::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> PrefixMatch::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
