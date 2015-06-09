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

package rina.src.DIF.RA;

simple RA
{
    parameters:
        @display("i=block/segm");
        
        @signal[RA-CreateFlowPositive](type=Flow?);
        @signal[RA-CreateFlowNegative](type=Flow?);
        @signal[RA-ExecuteSlowdown](type=CongestionDescriptor?);
        @signal[RA-InvokeSlowdown](type=cPacket?);
        @signal[RA-MgmtFlowAllocated](type=Flow?);
        @signal[RA-MgmtFlowDeallocated](type=Flow?);

        xml qoscubesData = default(xml("<QoSCube/>"));
        xml qosReqData = default(xml("<QoSReq/>"));
        xml preallocation = default(xml("<root/>"));
}
