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
 * @file EFCPTableEntry.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#include "DIF/EFCP/EFCPTable/EFCPTableEntry.h"

EFCPTableEntry::EFCPTableEntry()
{


}

EFCPTableEntry::~EFCPTableEntry()
{

}


std::string EFCPTableEntry::info() const {
    std::ostringstream os;
    os << this->flow->info() << "\n" << "EFCPTanleEntry TODO";
    return os.str();
}

Delimiting* EFCPTableEntry::getDelimit() const
{
  return delimit;
}

void EFCPTableEntry::setDelimit(Delimiting* delimit)
{
  this->delimit = delimit;
}

TEFCPITab* EFCPTableEntry::getEfcpiTab()
{
  return &efcpiTab;
}

void EFCPTableEntry::addEFCPI(EFCPInstance* efcpi){
  efcpiTab.insert(efcpiTab.begin(),efcpi);
}


const Flow* EFCPTableEntry::getFlow() const
{
  return flow;
}

void EFCPTableEntry::setFlow(const Flow* flow)
{
  this->flow = flow;
}

bool EFCPTableEntry::flushDTPs()
{
  std::vector<EFCPInstance*>::iterator it;
  for(it = efcpiTab.begin(); it != efcpiTab.end(); ++it){
    (*it)->getDtp()->flushAllQueuesAndPrepareToDie();
  }
  //TODO B2 return value based EFCPI deallocation status
  return true;
}

std::ostream& operator<< (std::ostream& os, const EFCPTableEntry* entry){
    return os << entry->info();
}
