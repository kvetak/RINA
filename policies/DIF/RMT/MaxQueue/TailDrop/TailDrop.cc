//
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

#include "DIF/RMT/MaxQueue/TailDrop/TailDrop.h"

#include <iostream>

Define_Module(TailDrop);

bool TailDrop::run(RMTQueue* queue)
{
    count[queue]++;
    if (queue->getLength() >= queue->getMaxLength()) {
        drop[queue]++;
        EV << "TailDrop: dropping message for queue " << queue->getName() << "!" << endl;
        return true;
    }  else {
        accepted[queue]++;
        return false;
    }
}

void TailDrop::finish() {
    if(par("printAtEnd").boolValue()) {
        std::cout << "TailDrop::finish" << endl;
        std::cout << this->getFullPath() << endl;
        for(auto & ql : count) {
            RMTQueue * q = ql.first;
            std::cout << "\tQueue : "<< q->getFullPath()<<endl;
            std::cout << "\t\tReceived : "<< count[q]<<endl;
            std::cout << "\t\tAccepted : "<< accepted[q]<<endl;
            std::cout << "\t\tRefused : "<< drop[q]<<endl;

        }
    }
}

