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

#ifndef DIRECTORYENTRY_H_
#define DIRECTORYENTRY_H_

//RINASim libraries
//#include "Common/APNamingInfo.h"
//#include "DIF/FA/FABase.h"
#include "Common/Address.h"



class DirectoryEntry {
  public:
/*
    DirectoryEntry();
    DirectoryEntry(APNamingInfo napni, Address naddr, std::string path, FABase* fa);
*/
    DirectoryEntry(const APN& napn);
    virtual ~DirectoryEntry();

    bool operator== (const DirectoryEntry& other) const;

    const APN& getApn() const;
    void setApn(const APN& apn);
    const Addresses& getSupportedDifs() const;
    void setSupportedDifs(const Addresses& supportedDifs);

    std::string info() const;

    void addDif(const Address& member);
    bool hasDif(const Address& member);

/*
    const APNamingInfo& getApni() const;
    FABase* getFlowAlloc() const;
    const std::string& getIpcPath() const;
    const Address& getAddr() const;
    cModule* getIpc();
*/

  private:
    APN Apn;
    Addresses SupportedDifs;

};

//Free function
std::ostream& operator<< (std::ostream& os, const DirectoryEntry& dte);

#endif /* DIRECTORYENTRY_H_ */
