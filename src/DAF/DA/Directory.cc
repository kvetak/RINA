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

#include "Directory.h"

//Constants
const char* DIRECTORY_MAPPING = "APNtoDIF";

Define_Module(Directory);

void Directory::initialize()
{
    cXMLElement* dirXml = par("directoryData").xmlValue();
    cXMLElementList map = dirXml->getChildrenByTagName(DIRECTORY_MAPPING);
    for (cXMLElementList::iterator i = map.begin(); i != map.end(); ++i) {
        cXMLElement* m = *i;
        //EV << m->getAttribute("apn") << "\t" << m->getAttribute("ipcAddress") << endl;
        cModule* top = this->getParentModule()->getParentModule();
        for (cModule::SubmoduleIterator j(top); !j.end(); j++) {
            cModule *submodp = j();
            if (submodp->hasPar("ipcAddress")
                    && !opp_strcmp(submodp->par("ipcAddress").stringValue(), m->getAttribute("ipcAddress"))
               ) {
                //EV << submodp->getSubmodule("flowAllocator")->getSubmodule("fa") << endl;
                this->insert(DirectoryEntry(APNamingInfo(APN(m->getAttribute("apn"))),
                                            submodp->getFullPath(),
                                            dynamic_cast<FABase*>(submodp->getSubmodule("flowAllocator")->getSubmodule("fa"))
                                           )
                            );
            }
        }
    }

    WATCH_LIST(Director);
}

DirectoryEntry* Directory::findEntryByApn(const APN& apn) {
    for(TDirIter it = Director.begin(); it != Director.end(); ++it) {
        DirectoryEntry entry = *it;
        if (entry.getApni().getApn() == apn)
            return &(*it);
    }
    return NULL;
}

DirectoryEntry* Directory::findEntryByApni(const APNamingInfo& apni) {
    for(TDirIter it = Director.begin(); it != Director.end(); ++it) {
        DirectoryEntry entry = *it;
        if (entry.getApni() == apni)
            return &(*it);
    }
    return NULL;
}

void Directory::insert(const DirectoryEntry& entry) {
    Director.push_back(entry);
}

std::string Directory::info() const {
    std::stringstream os;
    os << "id=" << this->getId() << endl;
    return os.str();
}

void Directory::handleMessage(cMessage *msg)
{

}
