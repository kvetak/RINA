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

package rina.src.DAF.AEManagement;

import rina.src.DAF.Enrollment.DAFEnrollmentModule;

module AEManagement
{
    parameters:
        @display("bgb=203,253;i=block/cogwheel,#888A85,50");
    gates:
        inout southIo[];
    submodules:
        //aemanagement: AEmanagementModule {
        //    parameters:
        //        @display("p=100,150");
        //}
        //enrollment: DAFEnrollmentModule {
        //    parameters:
        //        @display("p=100,50");
        //}
    connections allowunconnected:
}
