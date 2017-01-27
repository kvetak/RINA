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

#include "DAF/DA/DA.h"

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

const Address* DA::resolveApnToBestAddress(const APN& apn, const DAP& difName) {
    Enter_Method("resolveApnToBestAddress()");

    DirectoryEntry* de = resolveApn(apn);
    if (de == NULL) {
        EV << "DA does not know target application" << endl;
        return NULL;
    }

    //Return address from a given DIF
    for (AddrCItem it = de->getSupportedDifs().begin(); it != de->getSupportedDifs().end(); ++it) {
        if (it->getDifName() == difName && isDifLocal(it->getDifName()))
            return &(*it);
    }

    EV << "None of found DIFs is local!" << endl;
    return NULL;
}

const APNList* DA::findNeigborApns(const APN& neighbor) {
    return NeighborTab->findApnsByNeighbor(neighbor);
}

void DA::initPointers() {
    //Retrieve pointers to submodules
    Dir = getRINAModule<Directory*>(this, 1, {MOD_DIRECTORY});
    NamInfo = getRINAModule<NamingInformation*>(this, 1, {MOD_NAMINFO});
    NeighborTab = getRINAModule<NeighborTable*>(this, 1, {MOD_NEIGHBORTABLE});
    SearchTab = getRINAModule<SearchTable*>(this, 1, {MOD_SEARCHTAB});
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
    cModule* top = this->getModuleByPath("^.^");
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if ( (submodp->hasPar(PAR_APNAME)
                && !opp_strcmp(submodp->par(PAR_APNAME), apn.getName().c_str() ) )
//             ||
//             (submodp->hasPar(PAR_IPCADDR)
//                && !opp_strcmp(submodp->par(PAR_IPCADDR), apn.getName().c_str() ) )
           )
            return true;
    }
    return false;
}

bool DA::isDifLocal(const DAP& difName) {
    cModule* top = this->getModuleByPath("^.^");
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if (submodp->hasPar(PAR_DIFNAME)
            && !opp_strcmp(submodp->par(PAR_DIFNAME), difName.getName().c_str())
           ) {
            //EV << "!!!!!" << difName << "!!!!!" << submodp->getFullPath() << endl;
            return true;
        }
    }
    return false;
}

bool DA::isIpcLocal(cModule* ipc) {
    cModule* top = this->getModuleByPath("^.^");
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule* submodp = j();
        if (submodp == ipc)
            return true;
    }
    return false;
}

cModule* DA::getDifMember(const DAP& difName) {
    cModule* top = this->getModuleByPath("^.^");
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
    cModule* top = this->getModuleByPath("^.^");
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
    cModule* top = this->getModuleByPath("^.^");
    for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
        cModule *submodp = j();
        if (submodp->hasPar(PAR_APNAME) && !strcmp(submodp->par(PAR_APNAME), apn.getName().c_str()) ) {
            return submodp;
        }
    }
    return NULL;
}


const Addresses* DA::resolveApnToAddressList(const APN& apn, const DAP& difName) {
    Enter_Method("resolveApnToAddressList()");

    DirectoryEntry* de = resolveApn(apn);
    if (de == NULL) {
        EV << "DA does not know target application" << endl;
        return NULL;
    }

    Addresses* addrs = new Addresses();
    //Return address from a given DIF
    for (AddrCItem it = de->getSupportedDifs().begin(); it != de->getSupportedDifs().end(); ++it) {
        if (it->getDifName() == difName && isDifLocal(it->getDifName()))
            addrs->push_back(*it);
    }

    if (addrs->empty()) {
        EV << "None of found DIFs is local!" << endl;
    }

    return addrs;
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
