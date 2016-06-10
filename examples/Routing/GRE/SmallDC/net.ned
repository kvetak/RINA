package rina.examples.Routing.GRE.SmallDC;

import rina.src.Other.NetTest.NetTestRouter;
import rina.src.Other.NetTest.NetTestListener;

network net
{
    @display("bgb=754,547");
    submodules:
        N30: NetTestRouter {
            @display("p=70,407");
        }
        N31: NetTestRouter {
            @display("p=159,407");
        }
        N32: NetTestRouter {
            @display("p=242,407");
        }
        N33: NetTestRouter {
            @display("p=70,479");
        }
        N34: NetTestRouter {
            @display("p=242,479");
        }
        N35: NetTestRouter {
            @display("p=159,479");
        }


        N40: NetTestRouter {
            @display("p=301,407");
        }
        N41: NetTestRouter {
            @display("p=390,407");
        }
        N42: NetTestRouter {
            @display("p=473,407");
        }
        N43: NetTestRouter {
            @display("p=301,479");
        }
        N44: NetTestRouter {
            @display("p=473,479");
        }
        N45: NetTestRouter {
            @display("p=390,479");
        }


        N50: NetTestRouter {
            @display("p=523,407");
        }
        N51: NetTestRouter {
            @display("p=612,407");
        }
        N52: NetTestRouter {
            @display("p=695,407");
        }
        N53: NetTestRouter {
            @display("p=523,479");
        }
        N54: NetTestRouter {
            @display("p=695,479");
        }
        N55: NetTestRouter {
            @display("p=612,479");
        }


        N00: NetTestRouter {
            @display("p=81,268");
        }
        N02: NetTestRouter {
            @display("p=159,268");
        }
        N01: NetTestRouter {
            @display("p=120,268");
        }


        N10: NetTestRouter {
            @display("p=322,268");
        }
        N12: NetTestRouter {
            @display("p=400,268");
        }
        N11: NetTestRouter {
            @display("p=361,268");
        }


        N20: NetTestRouter {
            @display("p=547,268");
        }
        N22: NetTestRouter {
            @display("p=625,268");
        }
        N21: NetTestRouter {
            @display("p=586,268");
        }


        listener: NetTestListener {
            @display("p=638,127");
        }
    connections:
        
        N00.medium++ <--> N30.medium++;
        N00.medium++ <--> N40.medium++;
        N00.medium++ <--> N50.medium++;
        N01.medium++ <--> N30.medium++;
        N01.medium++ <--> N40.medium++;
        N01.medium++ <--> N50.medium++;
        N02.medium++ <--> N30.medium++;
        N02.medium++ <--> N40.medium++;
        N02.medium++ <--> N50.medium++;
        
        N10.medium++ <--> N31.medium++;
        N10.medium++ <--> N41.medium++;
        N10.medium++ <--> N51.medium++;
        N11.medium++ <--> N31.medium++;
        N11.medium++ <--> N41.medium++;
        N11.medium++ <--> N51.medium++;
        N12.medium++ <--> N31.medium++;
        N12.medium++ <--> N41.medium++;
        N12.medium++ <--> N51.medium++;
        
        N20.medium++ <--> N32.medium++;
        N20.medium++ <--> N42.medium++;
        N20.medium++ <--> N52.medium++;
        N21.medium++ <--> N32.medium++;
        N21.medium++ <--> N42.medium++;
        N21.medium++ <--> N52.medium++;
        N22.medium++ <--> N32.medium++;
        N22.medium++ <--> N42.medium++;
        N22.medium++ <--> N52.medium++;
        
        N30.medium++ <--> N33.medium++;
        N30.medium++ <--> N34.medium++;
        N30.medium++ <--> N35.medium++;
        N31.medium++ <--> N33.medium++;
        N31.medium++ <--> N34.medium++;
        N31.medium++ <--> N35.medium++;
        N32.medium++ <--> N33.medium++;
        N32.medium++ <--> N34.medium++;
        N32.medium++ <--> N35.medium++;

        N40.medium++ <--> N43.medium++;
        N40.medium++ <--> N44.medium++;
        N40.medium++ <--> N45.medium++;
        N41.medium++ <--> N43.medium++;
        N41.medium++ <--> N44.medium++;
        N41.medium++ <--> N45.medium++;
        N42.medium++ <--> N43.medium++;
        N42.medium++ <--> N44.medium++;
        N42.medium++ <--> N45.medium++;

        N50.medium++ <--> N53.medium++;
        N50.medium++ <--> N54.medium++;
        N50.medium++ <--> N55.medium++;
        N51.medium++ <--> N53.medium++;
        N51.medium++ <--> N54.medium++;
        N51.medium++ <--> N55.medium++;
        N52.medium++ <--> N53.medium++;
        N52.medium++ <--> N54.medium++;
        N52.medium++ <--> N55.medium++;
}
