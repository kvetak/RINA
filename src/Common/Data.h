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
 * @file Data.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Sep 18, 2014
 * @brief
 * @detail
 */

#ifndef DATA_H_
#define DATA_H_

#include <omnetpp.h>
#include "Data_m.h"

class Data : public Data_Base
  {
    private:
      void copy(const Data& other) {};
    public:
     Data(const char *name=NULL, int kind=0) : Data_Base(name,kind) {}
     Data(const Data& other) : Data_Base(other) {copy(other);}
     Data& operator=(const Data& other) {if (this==&other) return *this; Data_Base::operator=(other); copy(other); return *this;}
     virtual Data *dup() const {return new Data(*this);}
      // ADD CODE HERE to redefine and implement pure virtual functions from Data_Base
  };
//class Data
//{
//    public:
//        Data();
//        virtual ~Data();
//};

#endif /* DATA_H_ */
