//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rina.DIF.EFCP.DTCP;

//
// TODO auto-generated type
//
simple DTCPState
{
    @display("i=block/subqueue");
    
    int initialSenderCredit = default(3);
    int rcvCredit = default(3);
    double aTime @unit(ms)= default(0ms);
    int nextSenderControlSeqNum = default(1);
    int dataReXmitMax = default(3);
    
    int maxClosedWinQueLen = default(4);
    
    int timeUnit @unit(ms) = default(1000ms); 
    int sendingTimeUnit @unit(ms) = default(1000ms);
    int rcvBufferPercentThreshold  = default(75); 
    
    int initialSendingRate  = default(1); // measured in PDU/timeUnit
    int configRcvrRate = default(1); // measured in PDU/timeUnit
}
