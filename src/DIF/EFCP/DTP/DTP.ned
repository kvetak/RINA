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

package rina.DIF.EFCP.DTP;

//
// TODO auto-generated type
//
simple DTP
{
    
    parameters:
        @display("i=block/layer");
        string rcvrInactivityPolicy = default("");
        string senderInactivityPolicy = default("");
        string initialSeqNumPolicy = default("");
        string rttEstimatorPolicy = default("");
        
        @signal[DTP_RTT](type=double);
        @statistic[dtp-rtt](title="Estimated RTT"; source=DTP_RTT; record=vector, mean);
        
        @signal[DTP_CLOSED_WIN_Q](type=int);
        @statistic[dtp-close-win-q](title="Closed-window Queue length"; source=DTP_CLOSED_WIN_Q; record=vector, mean);
        

    gates:
        inout northIo; //towards Delimiting
        inout southIo; //towards RMT
        

}
