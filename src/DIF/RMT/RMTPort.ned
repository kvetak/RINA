//
// Copyright © 2014 PRISTINE Consortium (http://ict-pristine.eu)
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

package rina.DIF.RMT;

simple RMTPort
{
    parameters:
    	@display("i=block/square;is=s");
    	@signal[RMTPort_PassUp](type=bool);
        @signal[RMTPort_PassDown](type=bool);
        @statistic[rmtport-up](title="msg passed up"; source=count(RMTPort_PassUp); record=last;);
        @statistic[rmtport-down](title="msg passed down"; source=count(RMTPort_PassDown); record=last);
        
        double postServeDelay @unit(ms) = default(0.0ms);
        
	gates:
    	inout southIo;
}
