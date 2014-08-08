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

void DA::initialize()
{
    //Retrieve pointers to submodules
    Dir         = ModuleAccess<Directory>("directory").get();
    NamInfo     = ModuleAccess<NamingInformation>("namingInformation").get();
    NeighborTab = ModuleAccess<NeighborTable>("neighborTable").get();
    SearchTab   = ModuleAccess<SearchTable>("searchTable").get();
}

FABase* DA::resolveApnToDif(const APN& apn) {
    return Dir->findEntryByApn(apn)->getFlowAlloc();
}

FABase* DA::resolveApniToDif(const APNamingInfo& apni) {
    return Dir->findEntryByApni(apni)->getFlowAlloc();
}

void DA::handleMessage(cMessage *msg)
{

}
