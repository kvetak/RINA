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
 * @file EFCPListeners.h
 * @author Marcel Marek
 * @date Feb 12, 2015
 * @brief
 * @detail

 */

#ifndef EFCPLISTENERS_H_
#define EFCPLISTENERS_H_


#include <omnetpp.h>

//#include "Common/CongestionDescriptor.h"
#include "DIF/EFCP/EFCPTable/EFCPTable.h"

class EFCPListeners : public cListener
{
  public:
    EFCPListeners(EFCPTable* efcpTable);
    virtual ~EFCPListeners();

  protected:
    EFCPTable* efcpTable;
};


class LisEFCPCongestFromRA : public EFCPListeners {
  public:
    LisEFCPCongestFromRA(EFCPTable* efcpTable): EFCPListeners(efcpTable){};
    void virtual receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail);
};

class LisEFCPQueueInfoFromRMT : public EFCPListeners {
  public:
    LisEFCPQueueInfoFromRMT(EFCPTable* efcpTable): EFCPListeners(efcpTable){};
    void virtual receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail);
};

class LisEFCPQueueInfoFromAE : public EFCPListeners {
  public:
    LisEFCPQueueInfoFromAE(EFCPTable* efcpTable): EFCPListeners(efcpTable){};
    void virtual receiveSignal(cComponent* src, simsignal_t id, cObject* obj, cObject *detail);
};

#endif /* EFCPLISTENERS_H_ */
