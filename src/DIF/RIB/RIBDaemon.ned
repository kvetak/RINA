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

import rina.src.DAF.CDAP.CommonDistributedApplicationProtocol;

module RIBDaemon
{
    parameters:
        @display("i=block/control;bgb=271,295");

    gates:
        inout rmtIo;
        inout efcpIo;

    submodules:
        commonDistributedApplicationProtocol: CommonDistributedApplicationProtocol {
            parameters:
                @display("p=135,148");
            gates:
                southIo;
        }
        ribd: RIBd {
            parameters:
                @display("p=135,52");
        }

        ribdSplitter: RIBdSplitter {
            @display("p=135,241");
        }
    connections allowunconnected:
        commonDistributedApplicationProtocol.southIo <--> ribdSplitter.cdapIo;
        ribdSplitter.rmtIo <--> rmtIo;
}
