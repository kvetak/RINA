package rina.examples.DC;

import rina.CS.DC_VM;
import rina.CS.DC_Server;
import rina.CS.DC_TOR;
import rina.CS.DC_AS;
import rina.CS.DC_CR;

network DC
{
    @display("bgb=1000,250");

    submodules:

        CR0 : DC_CR {
            @display("p=825.000000,100.000000");
        }

        AS1 : DC_AS {
            @display("p=550.000000,50.000000");
        }

        AS2 : DC_AS {
            @display("p=550.000000,175.000000");
        }

        TOR3 : DC_TOR {
            @display("p=450.000000,50.000000");
        }

        TOR4 : DC_TOR {
            @display("p=450.000000,175.000000");
        }

        SRV5 : DC_Server {
            @display("p=200.000000,25.000000");
        }

        SRV6 : DC_Server {
            @display("p=200.000000,150.000000");
        }

        VM7 : DC_VM {
            @display("p=100.000000,25.000000");
        }

        VM8 : DC_VM {
            @display("p=100.000000,150.000000");
        }


    connections:

        CR0.medium++ <--> AS1.medium++;
        AS1.medium++ <--> AS2.medium++;
        AS1.medium++ <--> TOR3.medium++;
        AS2.medium++ <--> TOR4.medium++;
        TOR3.medium++ <--> SRV5.medium++;
        TOR4.medium++ <--> SRV6.medium++;
        SRV5.medium++ <--> VM7.medium;
        SRV6.medium++ <--> VM8.medium;
}
