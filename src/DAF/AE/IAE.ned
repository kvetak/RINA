//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rina.DAF.AE;

moduleinterface IAE
{
    parameters:
        @display("i=block/socket");
        @class(AE);
        string aeName;
        string aeInstance;
        
        //QoS -> Default DoNotCare value -1
        int averageBandwidth @unit(bps); //bits/s
        int averageSDUBandwidth; //SDU/s
        int peakBandwidthDuration @unit(bps); //Peak bandwidth-duration (measured in bits/sec);
        int peakSDUBandwidthDuration; //Peak SDU bandwidth-duration (measured in SDUs/sec);
        int burstPeriod	@unit(us); //Burst period measured in useconds
        int burstDuration @unit(us); //Burst duration, measured in useconds fraction of Burst Period
        double undetectedBitErr; //Undetected bit error rate measured as a probability
        int maxSDUsize @unit(B); //MaxSDUSize measured in bytes
        bool partialDelivery; //Partial Delivery - Can SDUs be delivered in pieces rather than all at once?
        bool incompleteDelivery; //Incomplete Delivery – Can SDUs with missing pieces be delivered?
        bool forceOrder; //Must SDUs be delivered in-order bits
        int maxAllowGap; //Max allowable gap in SDUs, (a gap of N SDUs is considered the same as all SDUs delivered, i.e. a gap of N is a "don't care.")
        int delay @unit(us); //Delay in usecs
        int jitter @unit(us); //Jitter in usecs
        int costTime; //measured in $/ms
        int costBits; //measured in $/Mb
}
