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

#ifndef __RINA_DA_H_
#define __RINA_DA_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "Directory.h"
#include "NamingInformation.h"
#include "NeighborTable.h"
#include "SearchTable.h"
#include "ModuleAccess.h"
#include "FABase.h"
#include "ExternConsts.h"

class DA : public cSimpleModule
{
  public:

    DirectoryEntry* resolveApn(const APN& apn);
    FABase* resolveApnToFa(const APN& apn);
    std::string resolveApnToIpcPath(const APN& apn);
    cModule* resolveApnToIpc(const APN& apn);


    //Methods checking local-ness relevant to DA
    bool isAppLocal(const APN apn);
    bool isDifLocal(const std::string difName);
    bool isIpcLocal(cModule* ipc);

    //DIFAllocator magical oraculum methods

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

    DirectoryEntry* resolveApni(const APNamingInfo& apni);
    FABase* resolveApniToFa(const APNamingInfo& apni);
    cModule* resolveApniToIpc(const APNamingInfo& apni);
    std::string resolveApniToIpcPath(const APNamingInfo& apni);

};

#endif
