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

package rina.src.DIF.RMT;

simple RMTQueue
{
    parameters:
        @display("i=block/queue;is=vs");        
        
        @signal[RMT-QueuePDUPreRcvd](type=RMTQueue?);
        @signal[RMT-QueuePDUPostRcvd](type=RMTQueue?);
        @signal[RMT-QueuePDUPreSend](type=RMTQueue?);
        @signal[RMT-QueuePDUSent](type=RMTQueue?);
        
        @signal[RMTQueue_Length](type="long");
        @signal[RMTQueue_Drop](type=bool);
        
        @statistic[rmtqueue-size](title="RMTQueue Size"; source=RMTQueue_Length; record=vector);
        @statistic[rmtqueue-drop](title="dropped PDUs"; source=count(RMTQueue_Drop); record=last);
    gates:
        input inputGate;
        output outputGate;        
}
