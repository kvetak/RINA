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

package rina.src.DIF.RIB;

simple RIBd
{
    parameters:
    	@display("i=block/control");
    	
    	@signal[RIBd-DataSend](type=CDAPMessage?);
    	@signal[RIBd-CreateFlow](type=Flow?);    	
    	@signal[RIBd-CreateRequestFlow](type=Flow?);
    	@signal[RIBd-CreateFlowResponsePositive](type=Flow?);
    	@signal[RIBd-CreateFlowResponseNegative](type=Flow?);
    	@signal[RIBd-DeleteRequestFlow](type=Flow?);
    	@signal[RIBd-DeleteResponseFlow](type=Flow?);
    	@signal[AEorRIBd-AllocateResponsePositive](type=Flow?);
    	@signal[RIBd-CongestionNotification](type=CongestionDescriptor?);
    	
        @signal[RIBd-StartEnrollmentRequest](type=CDAPMessage?);
        @signal[RIBd-StartEnrollmentResponse](type=CDAPMessage?);
        @signal[RIBd-StopEnrollmentRequest](type=CDAPMessage?);
        @signal[RIBd-StopEnrollmentResponse](type=CDAPMessage?);
        @signal[RIBd-StartOperationRequest](type=CDAPMessage?);
        @signal[RIBd-StartOperationResponse](type=CDAPMessage?);
        
        @signal[RIBd-ConnectionResponsePositive](type=CDAPMessage?);
        @signal[RIBd-ConnectionResponseNegative](type=CDAPMessage?);
        @signal[RIBd-ConnectionRequest](type=CDAPMessage?);
        @signal[RIBd-CACEDataSend](type=CDAPMessage?);
}
