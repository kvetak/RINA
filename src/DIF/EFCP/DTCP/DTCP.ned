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

package rina.src.DIF.EFCP.DTCP;

//
// TODO auto-generated type
//
simple DTCP
{
    parameters:
        @display("i=block/subqueue");
        
        string ecnPolicy = default("");
        string rcvrFCPolicy = default("");
        string rcvrAckPolicy = default("");
        string receivingFCPolicy = default("");
        string sendingAckPolicy = default("");
        string lostControlPDUPolicy = default("");
        string rcvrControlAckPolicy = default("");
        string senderAckPolicy = default("");
        string fcOverrunPolicy = default("");
        string noOverridePeakPolicy = default("");
        string txControlPolicy = default("");
        string noRateSlowDownPolicy = default("");
        string reconcileFCPolicy = default("");
        string rateReductionPolicy = default("");
        string ecnSlowDownPolicy = default("");
        
//        @signal[DTCP_CLOSED_WIN_Q](type=double);
//        @statistic[dtcp-rtt](title="Closed-window Queue length"; source=DTCP_CLOSED_WIN_Q; record=vector, mean);
        @signal[DTCP_RX_SENT](type=unsigned long);
        @statistic[dtcp-rx-sent](title="Sum of all retransmissions"; source=DTCP_RX_SENT; record=last);
}
