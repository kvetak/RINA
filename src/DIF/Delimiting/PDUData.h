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

/*
 * @file PDUData.h
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 30, 2015
 * @brief
 * @detail
 */

#ifndef PDUDATA_H_
#define PDUDATA_H_
#include <omnetpp.h>
#include "DIF/Delimiting/PDUData_m.h"
#include <vector>
#include "DIF/Delimiting/Data.h"

class PDUData : public PDUData_Base
{

  private:
    std::vector<Data*> encapData;

    void copy(const PDUData& other);
  public:
    PDUData(const char *name=nullptr, int kind=0);
    PDUData(const PDUData& other);
    virtual ~PDUData();
    using PDUData_Base::encapsulate;
    virtual void encapsulate(Data* data);
    virtual Data *decapsulate();
    virtual void forEachChild(cVisitor *v);
    virtual PDUData* dup() const{return new PDUData(*this);}

    PDUData& operator=(const PDUData& other) {if (this==&other) return *this; PDUData_Base::operator=(other); copy(other); return *this;}
};

#endif /* PDUDATA_H_ */
