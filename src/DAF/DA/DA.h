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

#ifndef __RINA_DA_H_
#define __RINA_DA_H_

//Standard libraries
#include <omnetpp.h>
#include "Common/Utils.h"
//RINASim libraries
#include "DAF/DA/Directory.h"
#include "DAF/DA/NamingInformation.h"
#include "DAF/DA/NeighborTable.h"
#include "DAF/DA/SearchTable.h"
#include "DIF/FA/FABase.h"
#include "Common/ExternConsts.h"

//Constants
extern const char* MOD_DIRECTORY;
extern const char* MOD_NAMINFO;
extern const char* MOD_SEARCHTAB;
extern const char* MOD_NEIGHBORTAB;

class DA : public cSimpleModule
{
  public:

    DirectoryEntry* resolveApn(const APN& apn);



    const Address* resolveApnToBestAddress(const APN& apn);
    const Address* resolveApnToBestAddress(const APN& apn, const DAP& difName);
    const Addresses* resolveApnToAddressList(const APN& apn, const DAP& difName);

    const APNList* findApnNeigbors(const APN& apn);
    const APNList* findNeigborApns(const APN& neighbor);

    //Methods checking local-ness relevant to this DA
    bool isAppLocal(const APN& apn);
    bool isDifLocal(const DAP& difName);
    bool isIpcLocal(cModule* ipc);

    //Gets local IPC that is member of a given DIF
    cModule* getDifMember(const DAP& difName);

    //------------------ DIFAllocator magical oraculum methods ------------------

    cModule* findIpc(const Address& addr);
    FABase* findFaInsideIpc(cModule* ipc);
    cModule* findApp(const APN& apn);

    /** Check whether any IPC within given DIF name is available on computation system with source IPC
     *
     * @param difName Given DIF name
     * @param ipc Source IPC Process
     * @return True if yes, otherwise false
     */
    bool isDifLocalToIpc(const std::string difName, cModule* ipc);

    /**
     * Check whether given IPC X is on the same computation system as IPC Y
     * @param ipcX target
     * @param ipcY source
     * @return True if yes, otherwise false.
     */
    bool isIpcXLocalToIpcY(cModule* ipcX, cModule* ipcY);


  protected:
    Directory*          Dir;
    NamingInformation*  NamInfo;
    NeighborTable*      NeighborTab;
    SearchTable*        SearchTab;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void initPointers();

/*
    DirectoryEntry* resolveApni(const APNamingInfo& apni);
    FABase* resolveApniToFa(const APNamingInfo& apni);
    cModule* resolveApniToIpc(const APNamingInfo& apni);
    std::string resolveApniToIpcPath(const APNamingInfo& apni);
*/
};

#endif
