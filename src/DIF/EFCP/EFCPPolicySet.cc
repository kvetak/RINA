//
// Copyright © 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

/*
 * @file EFCPPolicySet.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date April 3, 2015
 * @brief Holds names of EFCP policies to be used in specific QoSCube.
 * @detail
 */

#include <EFCPPolicySet.h>

const char* ELEM_FCOVERRUN             = "FCOverrun";
const char* DEFAULT_FCOVERRUN          = "DTCPFCOverrunPolicyDefault";

EFCPPolicySet::EFCPPolicySet()
{
  // TODO Auto-generated constructor stub

}

const char* EFCPPolicySet::getFcOverrun() const
{
  return fcOverrun;
}

void EFCPPolicySet::setFcOverrun(const char* fcOverrun)
{
  this->fcOverrun = fcOverrun;
}

EFCPPolicySet::~EFCPPolicySet()
{
  // TODO Auto-generated destructor stub
}

bool EFCPPolicySet::init(cXMLElement* parent)
{


    cXMLElementList attrs = parent->getChildren();
  for (cXMLElementList::iterator jt = attrs.begin(); jt != attrs.end(); ++jt)
  {
    cXMLElement* policyTag = *jt;
    if (!strcmp(policyTag->getTagName(), ELEM_FCOVERRUN ))
    {
      fcOverrun = policyTag->getNodeValue() ? policyTag->getNodeValue() : DEFAULT_FCOVERRUN;
    }
  }
}
