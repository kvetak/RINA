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

simple AEStream extends AE like IAE
{ 
    parameters:
        @class(AEStream);
        string dstApName = default("AppErr");
        string dstApInstance = default("0");
        string dstAeName = default("AeErr");
        string dstAeInstance = default("0");
                       
        int 	startAt 		@unit(s) = default(0s);
        int 	stopAt  		@unit(s) = default(0s);
        int 	beginStreamAt  	@unit(s) = default(0s);
        int 	endStreamAt  	@unit(s) = default(0s);
        
        int 	size    		@unit(B) = default(1024B);        
        double 	interval  		@unit(s) = default(100ms);        
    
		@signal[AE_PING_BYTES_RCVD](type=int);
        @statistic[AE-PING-BYTES-RCVD](title="Bytes received"; source=AE_PING_BYTES_RCVD; record=vector, last);
        
}
