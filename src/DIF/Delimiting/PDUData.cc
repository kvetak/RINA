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
 * @file PDUData.cc
 * @author Marcel Marek (imarek@fit.vutbr.cz)
 * @date Oct 30, 2015
 * @brief
 * @detail
 */

#include "DIF/Delimiting/PDUData.h"
Register_Class(PDUData);
PDUData::PDUData(const char* name, int kind): PDUData_Base(name, kind)
{

}

PDUData::~PDUData()
{

}

PDUData::PDUData(const PDUData& other): ::PDUData_Base(other)
{
  copy(other);
}

void PDUData::copy(const PDUData& other)
{
  for(auto it = other.encapData.begin(); it != other.encapData.end(); ++it)
  {
    Data* tmpData = (*it)->dup();
    take(tmpData);
    encapData.push_back(tmpData);
  }

}

void PDUData::encapsulate(Data* data)
{

  take(data);
  encapData.push_back(data);
  addByteLength(data->getByteLength());
  switch(data->getDataType()){
    case DATA_SDU_COMPLETE:
    {
      completeSDU = true;
      break;
    }
    case DATA_FIRST_FRAG:
    {
      firstFragment = true;
      break;
    }
    case DATA_MIDDLE_FRAG:
    {
      midFragment = true;
      break;
    }
    case DATA_LAST_FRAG:
    {
      lastFragment = true;
      break;
    }
  }

}

Data* PDUData::decapsulate(void)
{

  if(encapData.size() > 0){
    Data* data = encapData.front();
    encapData.erase(encapData.begin());
    addByteLength(0 - data->getByteLength());

    drop(data);

    return data;
  }else{
    return nullptr;
  }


}

void PDUData::forEachChild(cVisitor *v)
{
  for (auto it = encapData.begin(); it != encapData.end(); ++it)
  {
    v->visit(*it);
  }


}
