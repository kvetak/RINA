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

package rina.DIF.FA;

simple FAI
{
    parameters:
    	@display("i=block/rxtx");
    	
    	@signal[FAI-AllocateRequest](type=Flow?);
    	@signal[FAI-AllocateResponsePositive](type=Flow?);
    	@signal[FAI-AllocateResponseNegative](type=Flow?);
    	@signal[FAI-CreateFlowRequest](type=Flow?);
    	@signal[FAI-DeleteFlowRequest](type=Flow?);
    	@signal[FAI-CreateFlowResponsePositive](type=Flow?);
    	@signal[FAI-CreateFlowResponseNegative](type=Flow?);
    	@signal[FAI-DeleteFlowResponse](type=Flow?);
    	
    	int localPortId 	= default(-1);
    	int localCEPId 		= default(-1);
    	int remotePortId 	= default(-1);
    	int remoteCEPId 	= default(-1);
    	       	
    	double createRequestTimeout @unit(s) = default(10s);   	  	
}
