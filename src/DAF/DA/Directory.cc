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
const char*   PAR_DIRDATA         = "directoryData";
const char*   ATTR_DIRMAPPING     = "APNtoDIF";
const char*   ATTR_IPCADDR        = "ipcAddress";
const char*   ATTR_APN            = "apn";
const char*   ATTR_DIFNAME        = "difName";

Define_Module(Directory);

void Directory::initialize()
{
    cXMLElement* dirXml = par(PAR_DIRDATA).xmlValue();
    cXMLElementList map = dirXml->getChildrenByTagName(ATTR_DIRMAPPING);


    cModule* top = this->getParentModule()->getParentModule()->getParentModule();

    for (cXMLElementList::iterator i = map.begin(); i != map.end(); ++i) {
        cXMLElement* m = *i;

        if (! (m->getAttribute(ATTR_APN) && m->getAttribute(ATTR_DIFNAME) && m->getAttribute(ATTR_IPCADDR)) ) {
            EV << "\nError when parsing DA-Directory record" << endl
               << m->getAttribute(ATTR_APN)
               << "\t" << m->getAttribute(ATTR_IPCADDR)
               << "\t" << m->getAttribute(ATTR_DIFNAME) << endl;
            continue;
        }

        for (cModule::SubmoduleIterator k(top); !k.end(); k++) {
            //EV << k()->getFullPath() << endl;

            cModule* submodp = NULL;
            for (cModule::SubmoduleIterator j(k()); !j.end(); j++) {
                //EV << j()->getFullPath() << endl;

                submodp = j();

                if (submodp->hasPar(ATTR_IPCADDR) && submodp->hasPar(ATTR_DIFNAME)
                        && !opp_strcmp(submodp->par(ATTR_IPCADDR).stringValue(), m->getAttribute(ATTR_IPCADDR))
                        && !opp_strcmp(submodp->par(ATTR_DIFNAME).stringValue(), m->getAttribute(ATTR_DIFNAME))
                   )
                     break;
                else
                    submodp = NULL;
            }

            //Appropriate IPCProcess found in simulation topology
            if (submodp) {
                //EV << "!!!!!OK" << endl;
                this->insert(DirectoryEntry(APNamingInfo(APN(m->getAttribute(ATTR_APN))),
                                            Address(m->getAttribute(ATTR_IPCADDR), m->getAttribute(ATTR_DIFNAME)),
                                            submodp->getFullPath(),
                                            dynamic_cast<FABase*>(submodp->getSubmodule(MOD_FLOWALLOC)->getSubmodule(MOD_FA))
                             ));
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
