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
/**
 * @file EFCPTable.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#include "DIF/EFCP/EFCPTable/EFCPTable.h"

Define_Module(EFCPTable);

EFCPTable::EFCPTable()
{

//  efcpTable.clear();


}

EFCPTable::~EFCPTable()
{

}

void EFCPTable::handleMessage(cMessage* msg){

}

void EFCPTable::initialize(){

  WATCH_VECTOR(efcpTable);
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
EFCPTableEntry* EFCPTable::getEntryByFlow(const Flow* flow){

  for(TEFCPTable::iterator it = this->efcpTable.begin(); it != efcpTable.end(); ++it){


    if((*it)->getFlow()->getConId() == flow->getConId()){
      return (*it);
    }
  }

  return nullptr;

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

DTP* EFCPTable::getDTPBySrcCEP(int srcCEP)
{

  for(TEFCPTable::iterator it = this->efcpTable.begin(); it!= efcpTable.end(); ++it){

    if((*it)->getFlow()->getConId().getSrcCepId() == srcCEP){
      //TODO B1 What to return in case of multiple EFCPi per Flow?
      return (*it)->getEfcpiTab()->front()->getDtp();
    }
  }
  return NULL;
}
