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
import rina.src.DAF.ApplicationProcess;
import rina.src.DAF.DA.DIFAllocator;
import rina.src.DIF.IPCProcess;
import rina.src.DAF.IRM.IPCResourceManager;

module VIFIBNode1
{
    parameters:
        @display("i=device/router;bgb=474,500");
        @node;

    //    int nofConn = default(3);
    //    int nofInterG = default(1);

    gates:
        inout medium[1];

    submodules:
        AP: ApplicationProcess {
            @display("p=134,53");
        }


        ipcResourceManager: IPCResourceManager {
            @display("p=50,133");
        }

		//Application Proces Level IPCP

        //Inter-Group Level IPCP
        IGIPC0: IPCProcess {
            @display("p=291,231;i=,#008000");
            relay = true;
        }

        ShimIPC0: IPCProcess {
            @display("p=50,358");
        }
        GIPC: IPCProcess {
            @display("p=157,231;i=,#FFB000");
            relay = true;
        }
        difAllocator: DIFAllocator {
            @display("p=65,53");
        }
        TenantIPC: IPCProcess {
            @display("p=235,145;i=,#FFB000");
            relay = true;
        }

    connections allowunconnected:

        // Static configuration for the connections.
        //
        // GIPC.northIo++ <--> TenantIPC.southIo++;
        IGIPC0.northIo++ <--> TenantIPC.southIo++;

       // for i=0..nofConn-1 {
          //  ShimIPC0.northIo++ <--> GIPC.southIo++;
            //ShimIPC1.northIo++ <--> GIPC.southIo++;
            //ShimIPC2.northIo++ <--> GIPC.southIo++;
      //      ShimIPC[i].northIo++ <--> IGIPC[0].southIo++;
            //ShimIPC0.southIo++ <--> medium[0];
            //ShimIPC1.southIo++ <--> medium[1];
            //ShimIPC2.southIo++ <--> medium[2];
     //   }


        ShimIPC0.southIo++ <--> medium[0];


        GIPC.southIo++ <--> ShimIPC0.northIo++;

        GIPC.northIo++ <--> TenantIPC.southIo++;


        ShimIPC0.northIo++ <--> IGIPC0.southIo++;


        //for i=0..nofInterG-1, 
   //     for j=0..nofConn-1 {
            //for j =0..nofConn-1{
   //         IGIPC[0].southIo++ <--> ShimIPC[j].northIo++;
   //         IGIPC[1].southIo++ <--> ShimIPC[j].northIo++;
            //}
    //    }

}
