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

package rina.src.DIF.EFCP;

simple EFCP
{
    parameters:
        @display("i=block/fork");
        bool pduDroppingEnabled = default(false);
        bool rendezvousEnabled = default(false);
        
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
        
        string rcvrInactivityPolicy = default("");
  		string senderInactivityPolicy = default("");
  		string initialSeqNumPolicy = default("");
  		string rttEstimatorPolicy = default("");
  		
  		double rtt @unit(s) = default(2s);
  		double mpl @unit(s) = default(50s);
        
  		int rcvCredit = default(10);
  		int initialSenderCredit = default(10);
  		int maxClosedWinQueLen = default(4);

        
}
