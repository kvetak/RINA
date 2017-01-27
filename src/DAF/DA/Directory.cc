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

#include "DAF/DA/Directory.h"

//Constants
const char*   ELEM_DIRDATA        = "Directory";
const char*   ELEM_DIF            = "DIF";
const char*   ATTR_IPCADDR        = "ipcAddress";
const char*   ATTR_DIFNAME        = "difName";

Define_Module(Directory);

void Directory::updateDisplayString() {
    std::ostringstream description;
    description << Director.size() << " entries";
    this->getDisplayString().setTagArg("t", 0, description.str().c_str());
    this->getDisplayString().setTagArg("t", 1, "t");
}

void Directory::initialize()
{
    //Parse XML config
    parseConfig(par(PAR_CONFIGDATA).xmlValue());

    updateDisplayString();
    //Init watchers
    WATCH_LIST(Director);
}

DirectoryEntry* Directory::findDirEntryByApn(const APN& apn) {
    for(TDirIter it = Director.begin(); it != Director.end(); ++it) {
        DirectoryEntry entry = *it;
        if (entry.getApn() == apn)
            return &(*it);
    }
    return NULL;
}

void Directory::addDirEntry(const APN& apn) {
    Director.push_back(DirectoryEntry(apn));
}

std::string Directory::info() const {
    std::ostringstream os;
    os << "id=" << this->getId() << endl;
    return os.str();
}

void Directory::handleMessage(cMessage *msg)
{

}

void Directory::addNewDif(const APN& apn, const Address& member) {
    findDirEntryByApn(apn)->addDif(member);
}

void Directory::removeDirEntry(const APN& apn) {
    Director.remove(*(findDirEntryByApn(apn)));
}

void Directory::parseConfig(cXMLElement* config) {
    cXMLElement* mainTag = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(ELEM_DIRDATA))
        mainTag = config->getFirstChildWithTag(ELEM_DIRDATA);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }

    cXMLElementList apnlist = mainTag->getChildrenByTagName(ELEM_APN);
    for (cXMLElementList::const_iterator it = apnlist.begin(); it != apnlist.end(); ++it) {
        cXMLElement* m = *it;

        if (!(m->getAttribute(ATTR_APN) && m->getFirstChildWithTag(ELEM_DIF))) {
            EV << "\nError when parsing Directory record" << endl;
            continue;
        }

        APN newapn = APN(m->getAttribute(ATTR_APN));

        addDirEntry(newapn);

        cXMLElementList diflist = m->getChildrenByTagName(ELEM_DIF);
        for (cXMLElementList::const_iterator jt = diflist.begin(); jt != diflist.end(); ++jt) {
            cXMLElement* n = *jt;

            if (!(n->getAttribute(ATTR_IPCADDR) && n->getAttribute(ATTR_DIFNAME))) {
                EV << "\nError when parsing DIF record" << endl;
                continue;
            }

            addNewDif(newapn, Address(n->getAttribute(ATTR_IPCADDR), n->getAttribute(ATTR_DIFNAME)));
        }
    }

}

/*
void Directory::parseConfig(cXMLElement* config) {
    cXMLElement* dirXml = NULL;
    if (config != NULL && config->hasChildren() && config->getFirstChildWithTag(ELEM_DIRDATA))
        dirXml = config->getFirstChildWithTag(ELEM_DIRDATA);
    else {
        EV << "configData parameter not initialized!" << endl;
        return;
    }

    cXMLElementList map = dirXml->getChildrenByTagName(ELEM_DIRMAPPING);
    cModule* top =
            this->getModuleByPath("^.^.^");
    for (cXMLElementList::iterator i = map.begin(); i != map.end(); ++i) {
        cXMLElement* m = *i;

        if (!(m->getAttribute(ATTR_APN) && m->getAttribute(ATTR_DIFNAME)
                && m->getAttribute(ATTR_IPCADDR))) {
            EV << "\nError when parsing DA-Directory record" << endl
                      << m->getAttribute(ATTR_APN) << "\t"
                      << m->getAttribute(ATTR_IPCADDR) << "\t"
                      << m->getAttribute(ATTR_DIFNAME) << endl;
            continue;
        }

        for (cModule::SubmoduleIterator k(top); !k.end(); k++) {
            //EV << k()->getFullPath() << endl;

            cModule* submodp = NULL;
            for (cModule::SubmoduleIterator j(k()); !j.end(); j++) {
                //EV << j()->getFullPath() << endl;

                submodp = j();

                if (submodp->hasPar(ATTR_IPCADDR)
                        && submodp->hasPar(ATTR_DIFNAME)
                        && !opp_strcmp(submodp->par(ATTR_IPCADDR).stringValue(),
                                m->getAttribute(ATTR_IPCADDR))
                        && !opp_strcmp(submodp->par(ATTR_DIFNAME).stringValue(),
                                m->getAttribute(ATTR_DIFNAME)))
                    break;
                else
                    submodp = NULL;
            }

            //Appropriate IPCProcess found in simulation topology
            if (submodp) {
                //EV << "!!!!!OK" << endl;
                this->addDirEntry(
                        DirectoryEntry(
                                APNamingInfo(APN(m->getAttribute(ATTR_APN))),
                                Address(m->getAttribute(ATTR_IPCADDR),
                                        m->getAttribute(ATTR_DIFNAME)),
                                submodp->getFullPath(),
                                dynamic_cast<FABase*>(submodp->getSubmodule(
                                        MOD_FLOWALLOC)->getSubmodule(MOD_FA))));
            }
        }

    }
}

*/
