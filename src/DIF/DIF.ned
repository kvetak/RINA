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

package rina.DIF;

network DIF
{
    submodules:
        iface: Iface {
            @display("p=147,244");
        }
        cace: CACE {
            @display("p=194,52");
        }
        cdap: CDAP {
            @display("p=257,52");
        }
        dtcp: DTCP {
            @display("p=108,52");
        }
        dtp: DTP {
            @display("p=45,52");
        }
        forwardingTable: ForwardingTable {
            @display("p=337,223");
        }
        rib: RIB {
            @display("p=337,136");
        }
        rmt: RMT {
            @display("p=147,151");
        }
    connections:
        iface.rmt <--> rmt.iface;
        dtp.rmt <--> rmt.dtp;
        dtcp.rmt <--> rmt.dtcp;
        cace.rmt <--> rmt.cace;
        cdap.rmt <--> rmt.cadp;
}
