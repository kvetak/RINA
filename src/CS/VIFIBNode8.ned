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

module VIFIBNode8
{
    parameters:
        @display("i=device/router;bgb=552,515");
        @node;

    //    int nofConn = default(3);
    //    int nofInterG = default(1);

    gates:
        inout medium[8];

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
        ShimIPC1: IPCProcess {
            @display("p=104,403");
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
        ShimIPC2: IPCProcess {
            @display("p=170,358");
        }
        ShimIPC3: IPCProcess {
            @display("p=264,409");
        }
        ShimIPC4: IPCProcess {
            @display("p=364,391");
        }
        ShimIPC5: IPCProcess {
            @display("p=432,391");
        }
        ShimIPC6: IPCProcess {
            @display("p=517,430");
        }
        ShimIPC7: IPCProcess {
            @display("p=525,491");
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
        ShimIPC1.southIo++ <--> medium[1];
        ShimIPC2.southIo++ <--> medium[2];
        ShimIPC3.southIo++ <--> medium[3];
        ShimIPC4.southIo++ <--> medium[4];
        ShimIPC5.southIo++ <--> medium[5];
        ShimIPC6.southIo++ <--> medium[6];
        ShimIPC7.southIo++ <--> medium[7];


        GIPC.southIo++ <--> ShimIPC0.northIo++;
        GIPC.southIo++ <--> ShimIPC1.northIo++;
        GIPC.southIo++ <--> ShimIPC4.northIo++;
        GIPC.southIo++ <--> ShimIPC5.northIo++;
        GIPC.southIo++ <--> ShimIPC6.northIo++;
        GIPC.southIo++ <--> ShimIPC7.northIo++;

        GIPC.northIo++ <--> TenantIPC.southIo++;
        ShimIPC2.northIo++ <--> GIPC.southIo++;
        ShimIPC3.northIo++ <--> GIPC.southIo++;


        ShimIPC0.northIo++ <--> IGIPC0.southIo++;
        ShimIPC1.northIo++ <--> IGIPC0.southIo++;
        ShimIPC2.northIo++ <--> IGIPC0.southIo++;
        ShimIPC3.northIo++ <--> IGIPC0.southIo++;
        ShimIPC4.northIo++ <--> IGIPC0.southIo++;
        ShimIPC5.northIo++ <--> IGIPC0.southIo++;
        ShimIPC6.northIo++ <--> IGIPC0.southIo++;
        ShimIPC7.northIo++ <--> IGIPC0.southIo++;


        //for i=0..nofInterG-1, 
   //     for j=0..nofConn-1 {
            //for j =0..nofConn-1{
   //         IGIPC[0].southIo++ <--> ShimIPC[j].northIo++;
   //         IGIPC[1].southIo++ <--> ShimIPC[j].northIo++;
            //}
    //    }

}
