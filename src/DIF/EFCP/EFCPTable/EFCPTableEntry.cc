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
 * @file EFCPTableEntry.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Jul 31, 2014
 * @brief
 * @detail
 */

#include <EFCPTable/EFCPTableEntry.h>

EFCPTableEntry::EFCPTableEntry()
{
  // TODO Auto-generated constructor stub

}

EFCPTableEntry::~EFCPTableEntry()
{
  // TODO Auto-generated destructor stub
}


std::string EFCPTableEntry::info() const {
    std::ostringstream os;
    os << "TODO";
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

const TEFCPITab* EFCPTableEntry::getEfcpiTab()
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

void EFCPTableEntry::setFlow(Flow* flow)
{
  this->flow = flow;
}
