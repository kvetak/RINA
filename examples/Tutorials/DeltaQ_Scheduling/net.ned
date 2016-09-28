package rina.examples.Tutorials.DeltaQ_Scheduling;

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
        datarate = 200Mbps;
        delay = 10us;
}
channel myF2S extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
        delay = 10us;
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
        C: myRouter {
            @display("p=573,347");
        }
        E: myRouter {
            @display("p=455,238");
        }
        D: myRouter {
            @display("p=187,238");
        }
        F: myRouter {
            @display("p=324,124");
        }
        vdt_Listener: VDT_Listener {
            @display("p=84,63");
        }
    connections:
        A.medium++ <--> myT2F <--> D.medium++;
        B.medium++ <--> myT2F <--> D.medium++;
        C.medium++ <--> myT2F <--> E.medium++;
        D.medium++ <--> myF2S <--> F.medium++;
        E.medium++ <--> myF2S <--> F.medium++;
}
