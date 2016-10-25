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

moduleinterface IAE
{
    parameters:
        @display("i=block/socket");        
        @class(AE);
        string aeName;
        string aeInstance;
        string dstApName;
        string dstApInstance;
        string dstAeName;
        string dstAeInstance;
        
        bool initiator;
        
        //QoS -> Default DoNotCare value -1
        int averageBandwidth @unit(bps); //bits/s
        int averageSDUBandwidth; //SDU/s
        int peakBandwidthDuration @unit(bps); //Peak bandwidth-duration (measured in bits/sec);
        int peakSDUBandwidthDuration; //Peak SDU bandwidth-duration (measured in SDUs/sec);
        int burstPeriod	@unit(us); //Burst period measured in useconds
        int burstDuration @unit(us); //Burst duration, measured in useconds fraction of Burst Period
        double undetectedBitErr; //Undetected bit error rate measured as a probability
        double pduDroppingProbability; //PDU dropping probability
        int maxSDUsize @unit(B); //MaxSDUSize measured in bytes
        bool partialDelivery; //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
        bool incompleteDelivery; //Incomplete Delivery – Can SDUs with missing pieces be delivered?
        bool forceOrder; //Must SDUs be delivered in-order bits
        int maxAllowGap; //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
        int delay @unit(us); //Delay in usecs
        int jitter @unit(us); //Jitter in usecs
        int costTime; //measured in $/ms
        int costBits; //measured in $/Mb        
        
        //Authentication
        int authType;
        string authName;
        string authPassword;
        string authOther; //Other type of authentication different from name & password 
}
