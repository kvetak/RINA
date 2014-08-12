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

FABase* DA::resolveApnToDifFa(const APN& apn) {
    Enter_Method("resolveApnToDifFa()");
    DirectoryEntry* dre = Dir->findEntryByApn(apn);
    return dre ? dre->getFlowAlloc() : NULL;
}

FABase* DA::resolveApniToDifFa(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDifFa()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToDifFa(apni.getApn());
}

cModule* DA::resolveApnToDif(const APN& apn) {
    Enter_Method("resolveApnToDif()");
    FABase* fab = resolveApnToDifFa(apn);
    return  fab ? fab->getParentModule()->getParentModule() : NULL;
}

cModule* DA::resolveApniToDif(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDif()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToDif(apni.getApn());
}

std::string DA::resolveApnToDifName(const APN& apn) {
    Enter_Method("resolveApnToDifName()");
    cModule* dif = resolveApnToDif(apn);
    return  dif ? dif->getFullPath() : NULL;
}

std::string DA::resolveApniToDifName(const APNamingInfo& apni) {
    Enter_Method("resolveApniToDifName()");
    //TODO: Vesely - Complete APNI search
    return resolveApnToDifName(apni.getApn());
}


void DA::handleMessage(cMessage *msg)
{

}
