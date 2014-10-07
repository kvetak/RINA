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

#include "DA.h"

Define_Module(DA);

void DA::initPointers() {
    //Retrieve pointers to submodules
    Dir = ModuleAccess<Directory>("directory").get();
    NamInfo = ModuleAccess<NamingInformation>("namingInformation").get();
    NeighborTab = ModuleAccess<NeighborTable>("neighborTable").get();
    SearchTab = ModuleAccess<SearchTable>("searchTable").get();
}

void DA::initialize()
{
    //Retrieve pointers to submodules
    initPointers();
}

FABase* DA::resolveApnToFa(const APN& apn) {
    Enter_Method("resolveApnToDifFa()");
    DirectoryEntry* dre = Dir->findEntryByApn(apn);
    return dre ? dre->getFlowAlloc() : NULL;
}

FABase* DA::resolveApniToFa(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDifFa()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToFa(apni.getApn());
}

/** Check whether any IPC within given DIF name is available on computation system with source IPC
  *
  * @param difName Given DIF name
  * @param ipc Source IPC Process
  * @return True if yes, otherwise false
  */
bool DA::isDifLocalToIpc(const std::string difName, cModule* ipc) {
    cModule* top = ipc->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (isIpcXLocalToIpcY(submodp, ipc)
                && !opp_strcmp(submodp->par(PAR_DIFNAME), difName.c_str())                    //...has a given DIF name
           )
            return true;
    }
    return false;
}

/**
 * Check whether given IPC X is on the same computation system as IPC Y
 * @param ipcX target
 * @param ipcY source
 * @return True if yes, otherwise false.
 */
bool DA::isIpcXLocalToIpcY(cModule* ipcX, cModule* ipcY) {
    //Both of them have same parent module
    //...AND both of them are IPC (has IPCAddress parameter)
    return ipcX->getParentModule() == ipcY->getParentModule()
            && ipcX->hasPar(PAR_IPCADDR) && ipcX->hasPar(PAR_DIFNAME)
            && ipcY->hasPar(PAR_IPCADDR) && ipcY->hasPar(PAR_DIFNAME);
}

cModule* DA::resolveApnToIpc(const APN& apn) {
    Enter_Method("resolveApnToDif()");
    DirectoryEntry* dre = Dir->findEntryByApn(apn);
    return  dre ? dre->getIpc() : NULL;
}

cModule* DA::resolveApniToIpc(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDif()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToIpc(apni.getApn());
}

std::string DA::resolveApnToIpcPath(const APN& apn) {
    Enter_Method("resolveApnToDifName()");
    DirectoryEntry* dre = Dir->findEntryByApn(apn);
    return  dre ? dre->getIpcPath() : NULL;
}

bool DA::isAppLocal(const APN apn) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (submodp->hasPar(PAR_APNAME)
            && !opp_strcmp(submodp->par(PAR_APNAME), apn.getName().c_str())
           )
            return true;
    }
    return false;
}

bool DA::isDifLocal(const std::string difName) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (submodp->hasPar(PAR_DIFNAME)
            && !opp_strcmp(submodp->par(PAR_DIFNAME), difName.c_str())
           )
            return true;
    }
    return false;
}

bool DA::isIpcLocal(cModule* ipc) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (submodp == ipc)
            return true;
    }
    return false;
}

cModule* DA::findIpc(const Address& addr) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (submodp->hasPar(PAR_IPCADDR) && submodp->hasPar(PAR_DIFNAME)) {
            Address adr = Address(submodp->par(PAR_IPCADDR), submodp->par(PAR_DIFNAME));
            if (adr == addr)
                return submodp;
        }
    }
    return NULL;
}

FABase* DA::findFaInsideIpc(cModule* ipc) {
    return dynamic_cast<FABase*>(ipc->getSubmodule(MOD_FLOWALLOC)->getSubmodule(MOD_FA));
}

std::string DA::resolveApniToIpcPath(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDifName()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToIpcPath(apni.getApn());
}

void DA::handleMessage(cMessage *msg)
{

}

DirectoryEntry* DA::resolveApni(const APNamingInfo& apni) {
    return Dir->findEntryByApni(apni);
}

DirectoryEntry* DA::resolveApn(const APN& apn) {
    return Dir->findEntryByApn(apn);
}

