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

package rina.src.EthShimDIF.RINArp;

simple RINArp {
    parameters:
        double retryTimeout @unit("s") = default(1s);
        int retryCount = default(3);
        double cacheTimeout @unit("s") = default(120s);
        @display("i=block/layer");
        @signal[sentRINArpReq](type=long);
        @signal[sentRINArpReply](type=long);
        @signal[initiatedRINArpResolution](type=RINArp::ArpNotification);
        @signal[completedRINArpResolution](type=RINArp::ArpNotification);
        @signal[failedRINArpResolution](type=RINArp::ArpNotification);
        @statistic[sentRINArpReq](title="ARP requests sent"; record=count,vector);
        @statistic[sentRINArpReply](title="ARP replies sent"; record=count,vector);
        @statistic[initiatedRINArpResolution](title="ARP resolutions initiated"; record=count);
        @statistic[completedRINArpResolution](title="ARP resolutions completed"; record=count);
        @statistic[failedRINArpResolution](title="ARP resolutions failed"; record=count);
    gates:
        input ifIn @labels(RINArpPacket+Ieee802Ctrl);
        output ifOut @labels(RINArpPacket+Ieee802Ctrl);
}
