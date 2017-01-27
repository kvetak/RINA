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

#ifndef DAFRIBDLISTENERS_H_
#define DAFRIBDLISTENERS_H_

//Standard libraries
#include <omnetpp.h>
//RINASim libraries
#include "DAF/RIB/DAFRIBdBase.h"

class DAFRIBdListeners : public cListener {
public:
    DAFRIBdListeners(DAFRIBdBase* nribd);
    virtual ~DAFRIBdListeners();
    virtual void receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail) {
        EV << "Signal to DAFRIBd initiated by " << src->getFullPath() << endl;
    }
  protected:
    DAFRIBdBase* ribd;
};

class LisDAFRIBDRcvData : public DAFRIBdListeners {
  public:
    LisDAFRIBDRcvData(DAFRIBdBase* nribd) : DAFRIBdListeners(nribd) {};
    void virtual receiveSignal(cComponent *src, simsignal_t id, cObject *obj, cObject *detail);
};

#endif /* DAFRIBDLISTENERS_H_ */
