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

package rina.src.DIF.RA;

simple RA
{
    parameters:
        @display("i=block/segm");
        
        @signal[RA-CreateFlowPositive](type=Flow?);
        @signal[RA-CreateFlowNegative](type=Flow?);
        @signal[RA-ExecuteSlowdown](type=CongestionDescriptor?);
        @signal[RA-InvokeSlowdown](type=cPacket?);
        @signal[RA-MgmtFlowAllocated](type=APNIPair?);
        @signal[RA-MgmtFlowDeallocated](type=Flow?);
        @signal[Routing-Update](type=cPacket?);
       

        xml qoscubesData = default(xml("<QoSCube/>"));
        xml qosReqData = default(xml("<QoSReq/>"));
        xml preallocation = default(xml("<root/>"));
        
        bool onWire = default(false);
}
