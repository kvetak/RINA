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


package rina.src.DIF.EFCP;

import rina.src.DIF.EFCP.EFCPTable.EFCPTable;

module EFCPModule
{
    @display("i=block/layer;bgb=405,261");
    gates:
        //        inout faIo[];
        //        inout rmtIo[];
        inout ribd;
        inout mockToRMT;

    submodules:
        efcpTable: EFCPTable {
            @display("p=151,44");
        }
        efcp: EFCP {
            @display("p=52,44;i=block/circle");
        }


        mockEFCPI: MockEFCPI {
            @display("p=261,44");
        }
    connections allowunconnected:
        //        efcp.rmtIo <--> rmtIo++;
        mockEFCPI.northIo <--> ribd;
        mockEFCPI.southIo <--> mockToRMT;

}
