
package rina.examples._DublinBackup.UseCase2;

import ned.DatarateChannel;
import rina.src.CS.TestHost1AP;

network UseCase2
{
    @display("bgb=342,157");
    submodules:
        hostA: TestHost1AP {
            @display("p=98,65");
        }
        hostB: TestHost1AP {
            @display("p=230,65");
        }
    connections:
        hostA.medium <--> DatarateChannel {delay = 0.4s; ber = 0; datarate = 10Mbps; } <--> hostB.medium;
}
