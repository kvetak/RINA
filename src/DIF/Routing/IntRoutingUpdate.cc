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
 * IntRoutingUpdate.cc
 *
 *  Created on: Mar 18, 2015
 *      Author: gaixas1
 */

#include "DIF/Routing/IntRoutingUpdate.h"

Register_Class(IntRoutingUpdate);

IntRoutingUpdate::IntRoutingUpdate(){}
IntRoutingUpdate::IntRoutingUpdate(const Address &addr){
    dstAddr = addr;
}

IntRoutingUpdate::~IntRoutingUpdate(){}

// Getters.
Address IntRoutingUpdate::getDestination(){
    return dstAddr;
}
Address IntRoutingUpdate::getSource(){
    return srcAddr;
}

// Setters.
void IntRoutingUpdate::setDestination(Address addr){
    dstAddr = addr;
}
void IntRoutingUpdate::setSource(Address addr){
    srcAddr = addr;
}
