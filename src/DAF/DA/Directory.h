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

#ifndef __RINA_DIRECTORY_H_
#define __RINA_DIRECTORY_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DirectoryEntry.h"
#include "ExternConsts.h"

typedef std::list<DirectoryEntry> TDirectory;
typedef TDirectory::iterator TDirIter;

//Constants
extern const char*      ELEM_DIRDATA;
extern const char*      ELEM_DIF;
extern const char*      ATTR_IPCADDR;
extern const char*      ATTR_DIFNAME;

class Directory : public cSimpleModule
{
  public:
    std::string info() const;

    void addDirEntry(const APN& apn);
    DirectoryEntry* findDirEntryByApn(const APN& apn);
    void addNewDif(const APN& apn, const Address& member);
    void removeDirEntry(const APN& apn);

  protected:
    TDirectory Director;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

    void parseConfig(cXMLElement* config);

  private:

};

#endif
