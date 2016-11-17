package rina.examples.UPC.Unreliable;

import ned.DatarateChannel;
import rina.src.Addons.DataInjectors.CS.Inf_Router;
import rina.src.Addons.DataInjectors.CS.Inf_Switch;
import rina.src.Addons.DataInjectors.CS.Inf_EndPoint;
import rina.src.Addons.DataInjectors.CS.HomeRouter;

import rina.src.Addons.DataInjectors.FlowsSimulation.Implementations.VDT.VDT_Listener;
import rina.src.Addons.Channels.ChangingErrorChannel.ChangingErrorChannel;
import rina.src.Addons.Channels.ChangingErrorChannel.ChangerErrorChannel;

module Router extends Inf_Switch
{
    parameters:
        InjectorName = "VDT";
        @display("bgb=42,13");
}

module Server extends Inf_Router
{
    parameters:
        InjectorName = "VDT";
        @display("bgb=42,13");
}


network net
{
    @display("bgb=833,486");
    submodules:
        echanger: ChangerErrorChannel {
            @display("p=739,50");
        }
        listener: VDT_Listener {
            @display("p=64,44");
        }

        C_1: Server {
            @display("p=70,267");
        }
        C_2: Server {
            @display("p=726,267");
        }
        R_1: Router {
            @display("p=175,267");
        }
        R_2: Router {
            @display("p=611,267");
        }
        S: Server {
            @display("p=317,172");
        }
    connections:
        C_1.medium++ <--> ChangingErrorChannel {  datarate = 12Mbps; delay = 0.01ms; } <--> R_1.medium++;
        C_2.medium++ <--> ChangingErrorChannel {  datarate = 12Mbps; delay = 0.01ms; } <--> R_2.medium++;
        R_1.medium++ <--> DatarateChannel {  datarate = 100Mbps; delay = 5ms; } <--> R_2.medium++;
        R_1.medium++ <--> DatarateChannel {  datarate = 100Mbps; delay = 20ms; } <--> S.medium++;
        R_2.medium++ <--> DatarateChannel {  datarate = 100Mbps; delay = 30ms; } <--> S.medium++;
}
