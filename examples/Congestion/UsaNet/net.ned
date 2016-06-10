package rina.examples.Congestion.UsaNet;

import ned.DatarateChannel;
import rina.src.Other.Infection.T2InfectedRouter;
import rina.src.Other.Infection.IListener;
import rina.src.DAF.AE.AEConstant.AEConstantListener;

network net
{
    submodules:
        N0: T2InfectedRouter {
            @display("p=100,100");
        }
        N1: T2InfectedRouter {
            @display("p=100,200");
        }
        N2: T2InfectedRouter {
            @display("p=150,780");
        }
        N3: T2InfectedRouter {
            @display("p=100,900");
        }
        N4: T2InfectedRouter {
            @display("p=350,1150");
        }
        N5: T2InfectedRouter {
            @display("p=780,680");
        }
        N6: T2InfectedRouter {
            @display("p=550,980");
        }
        N7: T2InfectedRouter {
            @display("p=1150,680");
        }
        N8: T2InfectedRouter {
            @display("p=1400,1000");
        }
        N9: T2InfectedRouter {
            @display("p=1150,1300");
        }
        N10: T2InfectedRouter {
            @display("p=1730,500");
        }
        N11: T2InfectedRouter {
            @display("p=1800,650");
        }
        N12: T2InfectedRouter {
            @display("p=1600,1200");
        }
        N13: T2InfectedRouter {
            @display("p=1470,1470");
        }
        N14: T2InfectedRouter {
            @display("p=1730,1420");
        }
        N15: T2InfectedRouter {
            @display("p=2220,480");
        }
        N16: T2InfectedRouter {
            @display("p=2410,700");
        }
        N17: T2InfectedRouter {
            @display("p=2350,900");
        }
        N18: T2InfectedRouter {
            @display("p=2450,1130");
        }
        N19: T2InfectedRouter {
            @display("p=2610,1680");
        }
        N20: T2InfectedRouter {
            @display("p=2560,520");
        }
        N21: T2InfectedRouter {
            @display("p=2730,960");
        }
        N22: T2InfectedRouter {
            @display("p=2820,730");
        }
        N23: T2InfectedRouter {
            @display("p=3020,400");
        }
        N24: T2InfectedRouter {
            @display("p=3030,550");
        }
        listener: IListener;
    connections:
        N0.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 780.0us; } <--> N1.medium++;
        N0.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 6.971ms; } <--> N5.medium++;
        N1.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 4.541ms; } <--> N2.medium++;
        N2.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.014ms; } <--> N3.medium++;
        N2.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 3.281ms; } <--> N4.medium++;
        N3.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.758ms; } <--> N4.medium++;
        N4.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.047ms; } <--> N6.medium++;
        N4.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 6.349ms; } <--> N9.medium++;
        N5.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.949ms; } <--> N6.medium++;
        N5.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.886ms; } <--> N7.medium++;
        N7.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 3.167ms; } <--> N8.medium++;
        N7.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 4.737ms; } <--> N10.medium++;
        N8.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 3.046ms; } <--> N9.medium++;
        N8.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.206ms; } <--> N12.medium++;
        N10.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.291ms; } <--> N11.medium++;
        N10.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 3.825ms; } <--> N15.medium++;
        N11.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 4.565ms; } <--> N12.medium++;
        N11.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 3.534ms; } <--> N15.medium++;
        N12.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.337ms; } <--> N13.medium++;
        N12.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.993ms; } <--> N14.medium++;
        N12.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 6.301ms; } <--> N17.medium++;
        N13.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.065ms; } <--> N14.medium++;
        N14.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 7.157ms; } <--> N19.medium++;
        N15.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.267ms; } <--> N16.medium++;
        N15.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.67ms; } <--> N20.medium++;
        N16.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.629ms; } <--> N17.medium++;
        N16.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.828ms; } <--> N20.medium++;
        N17.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.956ms; } <--> N18.medium++;
        N18.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 4.468ms; } <--> N19.medium++;
        N18.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.555ms; } <--> N21.medium++;
        N20.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.607ms; } <--> N22.medium++;
        N20.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 3.708ms; } <--> N23.medium++;
        N21.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.926ms; } <--> N22.medium++;
        N22.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 2.157ms; } <--> N24.medium++;
        N23.medium++ <--> DatarateChannel {  datarate = 100.0Gbps; delay = 1.173ms; } <--> N24.medium++;

}
