package rina.examples.Routing.GRE.LinDC;

import rina.src.Other.NetTest.NetTestRouter;
import rina.src.Other.NetTest.NetTestListener;

network net
{
    @display("bgb=754,547");
    submodules:
        N00: NetTestRouter {
            @display("p=81,268");
        }
        N10: NetTestRouter {
            @display("p=70,407");
        }
        N11: NetTestRouter {
            @display("p=70,479");
        }
        
        listener: NetTestListener {
            @display("p=638,127");
        }
    connections:

        N00.medium++ <--> N10.medium++;
        N10.medium++ <--> N11.medium++;
}
