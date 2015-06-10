package rina.examples._DublinBackup.UseCase3;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;

network UseCase3
{
    @display("bgb=338,200");
    submodules:
        hostA: Host1AP {
            @display("p=66,98");
        }
        hostB: Host1AP {
            @display("p=270,98");
        }
        switch: InteriorRouter2Int {
            @display("p=167,98");
        }
    connections:
        hostA.medium <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> switch.medium[0];
        switch.medium[1] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> hostB.medium;
}
