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

package rina.DAF.CDAP;

module CommonDistributedApplicationProtocol
{
    parameters:
        @display("bgb=331,308;i=block/circle");

    gates:
        inout southIo;

    submodules:
        cace: CACE {
            @display("p=59,137");
        }
        auth: Auth {
            @display("p=159,138");
        }
        cdap: CDAP {
            @display("p=256,138");
        }
        cdapSplitter: CDAPSplitter {
            @display("p=159,234");
        }

        cdapMsgLog: CDAPMsgLog {
            @display("p=207,58");
        }
    connections allowunconnected:
        cace.splitterIo <--> cdapSplitter.caceIo;
        cdapSplitter.authIo <--> auth.splitterIo;
        cdapSplitter.cdapIo <--> cdap.splitterIo;
        //cdapSplitter.irmIo <--> southIo++;
        cdapSplitter.irmIo <--> southIo;
}
