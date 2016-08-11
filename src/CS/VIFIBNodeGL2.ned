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
        @display("i=device/router;bgb=662,564");
        @node;

    gates:
        inout medium[7];

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
            relay = true;
        }

        //Inter-Group Level IPCP
        IGIPC0: IPCProcess {
            @display("p=225,289;i=,#008000");
            relay = true;
        }
        IGIPC1: IPCProcess {
            @display("p=225,289;i=,#008000");
            relay = true;
        }

		//Group Level IPCP
        GIPC: IPCProcess {
            @display("p=89,289;i=,#008000");
            relay = true;
        }

        //Shim IPCPs

        ShimIPC0: IPCProcess {
            @display("p=50,358");
        }
        ShimIPC1: IPCProcess {
            @display("p=104,403");
        }
        ShimIPC2: IPCProcess {
            @display("p=170,358");
        }
        ShimIPC3: IPCProcess {
            @display("p=227,358");
        }
        ShimIPC4: IPCProcess {
            @display("p=291,358");
        }
        ShimIPC5: IPCProcess {
            @display("p=364,391");
        }
        ShimIPC6: IPCProcess {
            @display("p=420,358");
        }

    connections allowunconnected:

        // Static configuration for the connections.
        //
        GIPC.northIo++ <--> TenantIPC.southIo++;
        IGIPC0.northIo++ <--> TenantIPC.southIo++;
        IGIPC1.northIo++ <--> TenantIPC.southIo++;

//        for i=0..nofConn-1 {
//            ShimIPC[i].northIo++ <--> GIPC.southIo++;
//            ShimIPC[i].northIo++ <--> IGIPC[0].southIo++;
//            ShimIPC[i].northIo++ <--> IGIPC[1].southIo++;
//            ShimIPC[i].southIo++ <--> medium[i];
//        }


        ShimIPC0.southIo++ <--> medium[0];
        ShimIPC1.southIo++ <--> medium[1];
        ShimIPC2.southIo++ <--> medium[2];
        ShimIPC3.southIo++ <--> medium[3];
        ShimIPC4.southIo++ <--> medium[4];
        ShimIPC5.southIo++ <--> medium[5];
        ShimIPC6.southIo++ <--> medium[6];


        GIPC.southIo++ <--> ShimIPC0.northIo++;
        GIPC.southIo++ <--> ShimIPC1.northIo++;
        GIPC.southIo++ <--> ShimIPC4.northIo++;
        GIPC.southIo++ <--> ShimIPC5.northIo++;
        GIPC.southIo++ <--> ShimIPC6.northIo++;
        ShimIPC2.northIo++ <--> GIPC.southIo++;
        ShimIPC3.northIo++ <--> GIPC.southIo++;

        ShimIPC0.northIo++ <--> IGIPC0.southIo++;
        ShimIPC1.northIo++ <--> IGIPC0.southIo++;
        ShimIPC2.northIo++ <--> IGIPC0.southIo++;
        ShimIPC3.northIo++ <--> IGIPC0.southIo++;
        ShimIPC4.northIo++ <--> IGIPC0.southIo++;
        ShimIPC5.northIo++ <--> IGIPC0.southIo++;
        ShimIPC6.northIo++ <--> IGIPC0.southIo++;

        ShimIPC0.northIo++ <--> IGIPC1.southIo++;
        ShimIPC1.northIo++ <--> IGIPC1.southIo++;
        ShimIPC2.northIo++ <--> IGIPC1.southIo++;
        ShimIPC3.northIo++ <--> IGIPC1.southIo++;
        ShimIPC4.northIo++ <--> IGIPC1.southIo++;
        ShimIPC5.northIo++ <--> IGIPC1.southIo++;
        ShimIPC6.northIo++ <--> IGIPC1.southIo++;
        //for i=0..nofInterG-1, 
   //     for j=0..nofConn-1 {
            //for j =0..nofConn-1{
   //         IGIPC[0].southIo++ <--> ShimIPC[j].northIo++;
   //         IGIPC[1].southIo++ <--> ShimIPC[j].northIo++;
            //}
    //    }

}
