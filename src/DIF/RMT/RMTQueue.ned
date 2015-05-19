//
// Copyright © 2014 - 2015 PRISTINE Consortium (http://ict-pristine.eu)
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

package rina.src.DIF.RMT;

simple RMTQueue
{
    parameters:
        @display("i=block/queue;is=vs");        
        
        @signal[RMT-QueuePDUPreRcvd](type=RMTQueue?);
        @signal[RMT-QueuePDUPostRcvd](type=RMTQueue?);
        @signal[RMT-QueuePDUPreSend](type=RMTQueue?);
        @signal[RMT-QueuePDUSent](type=RMTQueue?);
        
        @signal[RMTQueue_Length](type="long");
        @signal[RMTQueue_Drop](type=bool);
        
        @statistic[rmtqueue-size](title="RMTQueue Size"; source=RMTQueue_Length; record=vector);
        @statistic[rmtqueue-drop](title="dropped PDUs"; source=count(RMTQueue_Drop); record=last);
    gates:
        input inputGate;
        output outputGate;        
}
