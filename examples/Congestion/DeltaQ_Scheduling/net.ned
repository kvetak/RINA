package rina.examples.Congestion.DeltaQ_Scheduling;

import ned.DatarateChannel;
import rina.src.Addons.DataInjectors.CS.Inf_Router;
import rina.src.Addons.DataInjectors.FlowsSimulation.Implementations.VDT.VDT_Listener;


module myRouter extends Inf_Router
{
    parameters:
        InjectorName = "VDT";
        @display("bgb=42,13");
}

channel myT2F extends DatarateChannel
{
    parameters:
        datarate = 100Mbps;
        delay = 0us;
}

network net
{
    @display("bgb=712,443");
    submodules:

        A: myRouter {
            @display("p=108,347");
        }
        B: myRouter {
            @display("p=235,347");
        }
        vdt_Listener: VDT_Listener {
            @display("p=84,63");
        }
    connections:
        A.medium++ <--> myT2F <--> B.medium++;
}
