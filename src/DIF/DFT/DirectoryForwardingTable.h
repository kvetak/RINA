//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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
/**
 * @file DirectoryForwardingTable.h
 * @author Vladimir Vesely (ivesely@fit.vutbr.cz)
 * @date Apr 30, 2014
 * @brief
 * @detail
 */

#ifndef DIRECTORYFORWARDINGTABLE_H_
#define DIRECTORYFORWARDINGTABLE_H_

//Standard libraries
#include <map>
#include <string>
#include <APNamingInfo.h>
#include <omnetpp.h>
//RINASim libraries
//#include <DFFMapping.h>

typedef std::map<APNamingInfo, std::string> DFTMappings;

class DirectoryForwardingTable : public cSimpleModule {
public:
    DirectoryForwardingTable();
    virtual ~DirectoryForwardingTable();

    std::string search(APNamingInfo apni);
    void add(APNamingInfo apni, std::string addr);
    void remove(APNamingInfo apni);
    void update(APNamingInfo apni);

protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);

private:
    DFTMappings dffMap;
};

#endif /* DIRECTORYFORWARDINGTABLE_H_ */
