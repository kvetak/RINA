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

//Constants
const char* MOD_DIRECTORY       = "directory";
const char* MOD_NAMINFO         = "namingInformation";
const char* MOD_NEIGHBORTAB     = "neighborTable";
const char* MOD_SEARCHTAB       = "searchTable";

Define_Module(DA);

const APNList* DA::findApnNeigbors(const APN& apn) {
    return NeighborTab->findNeighborsByApn(apn);
}

const Address* DA::resolveApnToBestAddress(const APN& apn) {
    Enter_Method("resolveApnToBestAddress()");

    DirectoryEntry* de = resolveApn(apn);
    if (de == NULL) {
        EV << "DA does not know target application" << endl;
        return NULL;
    }

    //Return first local DIF address
    for (AddrCItem it = de->getSupportedDifs().begin(); it != de->getSupportedDifs().end(); ++it) {
        if (isDifLocal(it->getDifName()))
            return &(*it);
    }

    EV << "None of found DIFs is local!" << endl;
    return NULL;
}

void DA::initPointers() {
    //Retrieve pointers to submodules
    Dir = ModuleAccess<Directory>(MOD_DIRECTORY).get();
    NamInfo = ModuleAccess<NamingInformation>(MOD_NAMINFO).get();
    NeighborTab = ModuleAccess<NeighborTable>(MOD_NEIGHBORTAB).get();
    SearchTab = ModuleAccess<SearchTable>(MOD_SEARCHTAB).get();
}

void DA::initialize()
{
    //Retrieve pointers to submodules
    initPointers();
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

bool DA::isAppLocal(const APN& apn) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if ( (submodp->hasPar(PAR_APNAME)
                && !opp_strcmp(submodp->par(PAR_APNAME), apn.getName().c_str() ) )
             ||
             (submodp->hasPar(PAR_IPCADDR)
                && !opp_strcmp(submodp->par(PAR_IPCADDR), apn.getName().c_str() ) )
           )
            return true;
    }
    return false;
}

bool DA::isDifLocal(const DAP& difName) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if (submodp->hasPar(PAR_DIFNAME)
            && !opp_strcmp(submodp->par(PAR_DIFNAME), difName.getName().c_str())
           )
            return true;
    }
    return false;
}

bool DA::isIpcLocal(cModule* ipc) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if (submodp == ipc)
            return true;
    }
    return false;
}

cModule* DA::getDifMember(const DAP& difName) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if (submodp->hasPar(PAR_DIFNAME)
            && !opp_strcmp(submodp->par(PAR_DIFNAME), difName.getName().c_str())
           )
            return submodp;
    }
    return NULL;
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

DirectoryEntry* DA::resolveApn(const APN& apn) {
    Enter_Method("resolveApn()");
    APNList apns = NamInfo->findAllApnNames(apn);
    //Return first Directory mapping from APN and all its synonyms
    for (ApnCItem it = apns.begin(); it != apns.end(); ++it) {
        DirectoryEntry* dre = Dir->findDirEntryByApn(*it);
        if (dre)
            return dre;
    }
    return NULL;
}

void DA::handleMessage(cMessage *msg)
{

}

cModule* DA::findApp(const APN& apn) {
    cModule* top = this->getParentModule()->getParentModule();
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (submodp->hasPar(PAR_APNAME) && !strcmp(submodp->par(PAR_APNAME), apn.getName().c_str()) ) {
            return submodp;
        }
    }
    return NULL;
}
/*
cModule* DA::resolveApnToIpc(const APN& apn) {
    Enter_Method("resolveApnToDif()");
    DirectoryEntry* dre = Dir->findDirEntryByApn(apn);
    return  dre ? dre->getIpc() : NULL;
}

FABase* DA::resolveApnToFa(const APN& apn) {
    Enter_Method("resolveApnToDifFa()");
    DirectoryEntry* dre = Dir->findDirEntryByApn(apn);
    return dre ? dre->getFlowAlloc() : NULL;
}

std::string DA::resolveApnToIpcPath(const APN& apn) {
    Enter_Method("resolveApnToDifName()");
    DirectoryEntry* dre = Dir->findDirEntryByApn(apn);
    return  dre ? dre->getIpcPath() : NULL;
}

std::string DA::resolveApniToIpcPath(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDifName()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToIpcPath(apni.getApn());
}

cModule* DA::resolveApniToIpc(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDif()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToIpc(apni.getApn());
}

FABase* DA::resolveApniToFa(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDifFa()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToFa(apni.getApn());
}

DirectoryEntry* DA::resolveApni(const APNamingInfo& apni) {
    return Dir->findEntryByApni(apni);
}
*/
