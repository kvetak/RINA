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

package rina.src.CS;
import rina.src.Common.Test;
import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;
import rina.src.DAF.IRM.IPCResourceManager;

module VIFIBNodeGL2
{
    parameters:
        @display("i=device/router;bgb=384,485");
        @node;

        int nofConn = default(7);
        int nofInterG = default(2);

    gates:
        inout medium[nofConn];

    submodules:
        AP: ApplicationProcess {
            @display("p=95,43");
        }

        difAllocator: DIFAllocator {
            @display("p=216,43;i=,grey");
        }

        ipcResourceManager: IPCResourceManager {
            @display("p=50,133");
        }

		//Application Proces Level IPCP
        TenantIPC: IPCProcess {
            @display("p=162,172;i=,#0080FF");
        }

        //Inter-Group Level IPCP
        IGIPC[nofInterG]: IPCProcess {
            @display("p=225,289;i=,#008000");
        }

		//Group Level IPCP
        GIPC: IPCProcess {
            @display("p=89,289;i=,#008000");
        }

        //Shim IPCPs
        ShimIPC[nofConn]: IPCProcess {
            @display("p=162,417;i=,#800000");
        }


    connections allowunconnected:

        // Static configuration for the connections.
        //
        GIPC.northIo++ <--> TenantIPC.southIo++;
        IGIPC[0].northIo++ <--> TenantIPC.southIo++;
        IGIPC[1].northIo++ <--> TenantIPC.southIo++;
        
        for i=0..nofConn-1 {
            ShimIPC[i].northIo++ <--> GIPC.southIo++;
            ShimIPC[i].northIo++ <--> IGIPC[0].southIo++;
            ShimIPC[i].northIo++ <--> IGIPC[1].southIo++;
            ShimIPC[i].southIo++ <--> medium[i];
        }

            
        //for i=0..nofInterG-1, 
   //     for j=0..nofConn-1 {
            //for j =0..nofConn-1{
   //         IGIPC[0].southIo++ <--> ShimIPC[j].northIo++;
   //         IGIPC[1].southIo++ <--> ShimIPC[j].northIo++;
            //}
    //    }

}
