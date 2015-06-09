package rina.examples.DublinSS.LatEx;
import rina.src.CS.*;

network LatEx
{
    @display("bgb=388,718");
    submodules:
        host1: HostNAP {
            @display("p=189,51");
        }
        host2: Host1AP {
            @display("p=189,626");
        }
        router1: InteriorRouterNInt {
            @display("p=189,178");
        }
        router2: InteriorRouterNInt {
            @display("p=97,315");
        }
        router3: InteriorRouterNInt {
            @display("p=278,315");
        }
        router4: InteriorRouterNInt {
            @display("p=189,463");
        }
    connections:
        host1.medium <--> router1.medium++;
        router1.medium++ <--> router2.medium++;
        router1.medium++ <--> router3.medium++;
        host2.medium <--> router4.medium++;
        router2.medium++ <--> router4.medium++;
        router3.medium++ <--> router4.medium++;
}
