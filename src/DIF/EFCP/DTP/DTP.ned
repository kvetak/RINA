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

package rina.src.DIF.EFCP.DTP;

//
// TODO auto-generated type
//
simple DTP
{
    
    parameters:
        @display("i=block/layer");
//        string rcvrInactivityPolicy = default("");
//        string senderInactivityPolicy = default("");
//        string initialSeqNumPolicy = default("");
//        string rttEstimatorPolicy = default("");
        
        @signal[EFCP-StopSending](type=Flow?);
        @signal[EFCP-StartSending](type=Flow?);
        
        @signal[DTP_RTT](type=double);
        @statistic[dtp-rtt](title="Estimated RTT"; source=DTP_RTT; record=vector, mean);
        
        @signal[DTP_CLOSED_WIN_Q](type=unsigned long);
        @statistic[dtp-close-win-q](title="Closed-window Queue length"; source=DTP_CLOSED_WIN_Q; record=vector, mean);
        
        @signal[DTP_SEQ_NUM_SENT](type="unsigned long");
        @statistic[dtp-seq-num-sent](title="Sent seq num"; source="DTP_SEQ_NUM_SENT"; record=vector, last);
        
        @signal[DTP_SEQ_NUM_RCVD](type=unsigned long);
        @statistic[dtp-seq-num-rcvd](title="Received seq num"; source="DTP_SEQ_NUM_RCVD"; record=vector, last);

    gates:
        inout northIo; //towards Delimiting
        inout southIo; //towards RMT
        

}
