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
 * @file SDUFrag.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Sep 18, 2014
 * @brief
 * @detail
 */

#ifndef SDUFRAG_H_
#define SDUFRAG_H_

#include <omnetpp.h>
#include "SDUFrag_m.h"

class SDUFrag: public SDUFrag_Base
{
    private:
      void copy(const SDUFrag& other) { };
    public:
          SDUFrag(const char *name=NULL, int kind=0) : SDUFrag_Base(name,kind) {}
          SDUFrag(const SDUFrag& other) : SDUFrag_Base(other) {copy(other);}
          SDUFrag& operator=(const SDUFrag& other) {if (this==&other) return *this; SDUFrag_Base::operator=(other); copy(other); return *this;}
          virtual SDUFrag *dup() const {return new SDUFrag(*this);}
          // ADD CODE HERE to redefine and implement pure virtual functions from SDUFrag_Base
    SDUFrag();
    virtual ~SDUFrag();
};

#endif /* SDUFRAG_H_ */
