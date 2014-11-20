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
 * @file EFCPTable.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#include "EFCPTable.h"

Define_Module(EFCPTable);

EFCPTable::EFCPTable()
{

//  efcpTable.clear();
  // TODO Auto-generated constructor stub

  if(this->isModule()){
    int a = 5;
  }

}

EFCPTable::~EFCPTable()
{
  // TODO Auto-generated destructor stub
}

void EFCPTable::handleMessage(cMessage* msg){

}

void EFCPTable::initialize(){

//  WATCH_LIST(efcpTable);
}

std::string EFCPTable::info() const {
    std::ostringstream os;
    os << "id=" << endl;// this->getId() << endl;
    /*
    for(TFTConstIter it = FaiTable.begin(); it != FaiTable.end(); ++it )
    {
        FAITableEntry tft = *it;
        os << tft << endl;
    }
    */
    return os.str();
}

/**
 *
 * @param flow
 * @return
 */
EFCPTableEntry* EFCPTable::getEntryByFlow(Flow* flow){
  //TODO A! remove
//  return NULL;
  for(TEFCPTable::iterator it = this->efcpTable.begin(); it != efcpTable.end(); ++it){


    if((*it)->getFlow() == flow){
      return (*it);
    }
  }

  return NULL;

}

/**
 *
 * @param efcpi
 * @return
 */
EFCPTableEntry* EFCPTable::getEntryByEFCPI(EFCPInstance* efcpi){

  for(TEFCPTable::iterator it = this->efcpTable.begin(); it!= efcpTable.end(); ++it){

    for(TEFCPITab::const_iterator efcpiIt = (*it)->getEfcpiTab()->begin(); efcpiIt != (*it)->getEfcpiTab()->end(); ++efcpiIt){
      if((*efcpiIt) == efcpi){
        return (*it);
      }
    }
  }

  return NULL;

}

/**
 *
 * @param delimit
 * @return
 */
EFCPTableEntry* EFCPTable::getEntryByDelimit(Delimiting* delimit){


  for(TEFCPTable::iterator it = this->efcpTable.begin(); it!= efcpTable.end(); ++it){

    if((*it)->getDelimit() == delimit){
      return (*it);
    }
  }

  return NULL;

}



void EFCPTable::insertEntry(EFCPTableEntry* entry){
//  Enter_Method("insertEntry(EFCPTableEntry* entry)");

//  this->efcpTable.empty();
  this->efcpTable.push_back(entry);


}
