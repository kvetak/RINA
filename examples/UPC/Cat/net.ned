package rina.examples.UPC.Cat;

import ned.DatarateChannel;
import rina.src.Addons.DataInjectors.CS.Inf_Router;
import rina.src.Addons.DataInjectors.FlowsSimulation.Implementations.VDT.VDT_Listener;


module Router extends Inf_Router
{
    parameters:
        InjectorName = "VDT";
        @display("bgb=42,13");
}
channel chan extends DatarateChannel
{
    parameters:
        datarate = 1Gbps;
}

network net
{
    @display("bgb=830,650");
    submodules:

        _0: Router {
            @display("p=477,415");
        }
        _1: Router {
            @display("p=429,376");
        }
        _2: Router {
            @display("p=477,345");
        }
        _3: Router {
            @display("p=534,376");
        }
        _4: Router {
            @display("p=390,296");
        }
        _5: Router {
            @display("p=642,296");
        }
        _6: Router {
            @display("p=662,170");
        }
        _7: Router {
            @display("p=152,335");
        }
        _8: Router {
            @display("p=276,481");
        }
        _9: Router {
            @display("p=138,559");
        }
        _10: Router {
            @display("p=256,117");
        }
        vdt_Listener: VDT_Listener {
            @display("p=593,512");
        }
    connections:
        _0.medium++ <--> chan {  delay = 0.18ms; } <--> _1.medium++;
        _0.medium++ <--> chan {  delay = 0.14ms; } <--> _2.medium++;
        _0.medium++ <--> chan {  delay = 0.21ms; } <--> _3.medium++;
        _0.medium++ <--> chan {  delay = 0.59ms; } <--> _8.medium++;
        _1.medium++ <--> chan {  delay = 0.07ms; } <--> _2.medium++;
        _1.medium++ <--> chan {  delay = 0.18ms; } <--> _4.medium++;
        _1.medium++ <--> chan {  delay = 0.58ms; } <--> _8.medium++;
        _2.medium++ <--> chan {  delay = 0.54ms; } <--> _3.medium++;
        _2.medium++ <--> chan {  delay = 0.20ms; } <--> _6.medium++;
        _3.medium++ <--> chan {  delay = 0.27ms; } <--> _5.medium++;
        _4.medium++ <--> chan {  delay = 0.62ms; } <--> _6.medium++;
        _4.medium++ <--> chan {  delay = 0.72ms; } <--> _7.medium++;
        _4.medium++ <--> chan {  delay = 0.54ms; } <--> _10.medium++;
        _5.medium++ <--> chan {  delay = 0.22ms; } <--> _6.medium++;
        _6.medium++ <--> chan {  delay = 0.85ms; } <--> _10.medium++;
        _7.medium++ <--> chan {  delay = 0.54ms; } <--> _8.medium++;
        _7.medium++ <--> chan {  delay = 0.64ms; } <--> _9.medium++;
        _7.medium++ <--> chan {  delay = 0.77ms; } <--> _10.medium++;
        _8.medium++ <--> chan {  delay = 0.50ms; } <--> _9.medium++;
}
