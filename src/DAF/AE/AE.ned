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

package rina.src.DAF.AE;

simple AE like IAE
{        
    parameters:
        @display("i=block/socket");        
        @class(AE);
        string dstApName = default("AppErr");
        string dstApInstance = default("0");
        string dstAeName = default("AeErr");
        string dstAeInstance = default("0");
        bool initiator = default(true);
        
        @signal[AEorRIBd-AllocateResponsePositive];
        @signal[AEorRIBd-AllocateResponseNegative];
        @signal[AE-DataSend];
        @signal[AE-Enrolled];
        @signal[AE-AP-API];
        @signal[AP-AE-API];
        
        string aeName = default("AeErr");
        string aeInstance = default("0");
        
        //QoS -> Default DoNotCare value -1
        int averageBandwidth @unit(bps) 		= default(-1bps); //bits/s
        int averageSDUBandwidth 				= default(-1); //SDU/s
        int peakBandwidthDuration @unit(bps)	= default(-1bps); //Peak bandwidth-duration (measured in bits/sec);
        int peakSDUBandwidthDuration			= default(-1); //Peak SDU bandwidth-duration (measured in SDUs/sec);
        int burstPeriod	@unit(us)				= default(-1us); //Burst period measured in useconds
        int burstDuration @unit(us)				= default(-1us); //Burst duration, measured in useconds fraction of Burst Period
        double undetectedBitErr					= default(-1); //Undetected bit error rate measured as a probability
        double pduDroppingProbability			= default(-1); //PDU dropping probability
        int maxSDUsize @unit(B)					= default(-1B); //MaxSDUSize measured in bytes
        bool partialDelivery					= default(false); //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
        bool incompleteDelivery					= default(false); //Incomplete Delivery – Can SDUs with missing pieces be delivered?
        bool forceOrder							= default(false); //Must SDUs be delivered in-order bits
        int maxAllowGap							= default(-1); //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
        int delay @unit(us)						= default(-1us); //Delay in usecs
        int jitter @unit(us)					= default(-1us); //Jitter in usecs
        int costTime							= default(-1); //measured in $/ms
        int costBits							= default(-1); //measured in $/Mb
        int resiliencyFactor					= default(-1);        
        
        //Authentication
        int authType							= default(0);
        string authName							= default("0");
        string authPassword						= default("0");
        string authOther						= default("0");

//        int averageBandwidth @unit(bps) 		= default(maxSDUsize*8*averageSDUBandwidth); //bits/s
//        int averageSDUBandwidth 				= default(1000); //SDU/s
//        int peakBandwidthDuration @unit(bps)	= default(2*averageBandwidth); //Peak bandwidth-duration (measured in bits/sec);
//        int peakSDUBandwidthDuration			= default(2*averageSDUBandwidth); //Peak SDU bandwidth-duration (measured in SDUs/sec);
//        int burstPeriod	@unit(us)			= default(10000000us); //Burst period measured in useconds
//        int burstDuration @unit(us)			= default(burstPeriod/10); //Burst duration, measured in useconds fraction of Burst Period
//        double undetectedBitErr				= default(0.0); //Undetected bit error rate measured as a probability
//        int maxSDUsize @unit(B)				= default(1500B); //MaxSDUSize measured in bytes
//        bool partDeliv						= default(false); //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
//        bool incompleteDeliv					= default(false); //Incomplete Delivery – Can SDUs with missing pieces be delivered?
//        bool forceOrder						= default(false); //Must SDUs be delivered in-order bits
//        int maxAllowGap						= default(10); //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
//        int delay @unit(us)					= default(1000000us); //Delay in usecs
//        int jitter @unit(us)					= default(delay/2); //Jitter in usecs
//        int costTime							= default(0); //measured in $/ms
//        int costBits							= default(0); //measured in $/Mb
//        bool dtcpOn							= default(false); //DTCPOn flag			                  
}
