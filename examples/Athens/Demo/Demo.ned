
package rina.examples.Athens.Demo;

import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.InteriorRouter2Int;

network Demo
{
    @display("bgb=282,253");
    submodules:
        hostA: Host1AP {
            @display("p=42,90");
        }
        hostB: Host1AP {
            @display("p=223,90");
        }
        switch: InteriorRouter2Int {
            @display("p=132,90");
        }
    connections:
        hostA.medium <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> switch.medium[0];
        switch.medium[1] <--> DatarateChannel {  datarate = 100Mbps; delay = 100us; ber = 0; } <--> hostB.medium;
}
