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

package rina.DIF.EFCP;
import rina.DIF.EFCP.DTP.DTP;
import rina.DIF.EFCP.DTP.DumbGate;


module EFCPI
{
    @display("i=block/layer;bgb=517,232");
    gates:
        inout northIo; //to FAI
        inout southIo; //to RMT
    submodules:
        dtp: DTP {
            @display("p=41,112");
        }
        northG: DumbGate {
            @display("p=41,29;is=vs");
        }
        southG: DumbGate {
            @display("p=41,201;is=vs");
        }
    connections allowunconnected:
        northG.northIo <--> northIo;
        dtp.northIo <--> northG.southIo;
//        
        dtp.southIo <--> southG.northIo;
        southG.southIo <--> southIo;


}
