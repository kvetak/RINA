package rina.examples.AdminAppReplaces;
import ned.DatarateChannel;
import rina.src.CS.*;

network AdminAppReplaces
{
    @display("bgb=609,634");
    submodules:
        HA: Host1AP_Adm {
            @display("p=57,95");
        }
        HB: Host1AP_Adm {
            @display("p=543,95");
        }
        HC: Host1AP_Adm {
            @display("p=57,560");
        }
        HD: Host1AP_Adm {
            @display("p=543,560");
        }

        Man: Shim_M_Adm {
            @display("p=306,56");
        }

        R00: InteriorRouterNInt_Adm {
            @display("p=140,160");
        }
        R01: InteriorRouterNInt_Adm {
            @display("p=253,160");
        }
        R02: InteriorRouterNInt_Adm {
            @display("p=359,160");
        }
        R03: InteriorRouterNInt_Adm {
            @display("p=450,160");
        }
        R10: InteriorRouterNInt_Adm {
            @display("p=140,267");
        }
        R11: InteriorRouterNInt_Adm {
            @display("p=253,267");
        }
        R20: InteriorRouterNInt_Adm {
            @display("p=140,374");
        }
        R21: InteriorRouterNInt_Adm {
            @display("p=253,374");
        }
        R22: InteriorRouterNInt_Adm {
            @display("p=359,374");
        }
        R23: InteriorRouterNInt_Adm {
            @display("p=450,374");
        }
        R12: InteriorRouterNInt_Adm {
            @display("p=359,267");
        }
        R13: InteriorRouterNInt_Adm {
            @display("p=450,267");
        }
        R30: InteriorRouterNInt_Adm {
            @display("p=140,481");
        }
        R31: InteriorRouterNInt_Adm {
            @display("p=253,481");
        }
        R32: InteriorRouterNInt_Adm {
            @display("p=359,481");
        }
        R33: InteriorRouterNInt_Adm {
            @display("p=450,481");
        }
    connections:
        R00.medium++ <--> DatarateChannel{delay = 1ms;} <--> R10.medium++;
        R10.medium++ <--> DatarateChannel{delay = 1ms;} <--> R20.medium++;
        R20.medium++ <--> DatarateChannel{delay = 1ms;} <--> R30.medium++;
        R01.medium++ <--> DatarateChannel{delay = 1ms;} <--> R11.medium++;
        R11.medium++ <--> DatarateChannel{delay = 1ms;} <--> R21.medium++;
        R21.medium++ <--> DatarateChannel{delay = 1ms;} <--> R31.medium++;
        R02.medium++ <--> DatarateChannel{delay = 1ms;} <--> R12.medium++;
        R12.medium++ <--> DatarateChannel{delay = 1ms;} <--> R22.medium++;
        R22.medium++ <--> DatarateChannel{delay = 1ms;} <--> R32.medium++;
        R03.medium++ <--> DatarateChannel{delay = 1ms;} <--> R13.medium++;
        R13.medium++ <--> DatarateChannel{delay = 1ms;} <--> R23.medium++;
        R23.medium++ <--> DatarateChannel{delay = 1ms;} <--> R33.medium++;
        R00.medium++ <--> DatarateChannel{delay = 1ms;} <--> R01.medium++;
        R01.medium++ <--> DatarateChannel{delay = 1ms;} <--> R02.medium++;
        R02.medium++ <--> DatarateChannel{delay = 1ms;} <--> R03.medium++;
        R10.medium++ <--> DatarateChannel{delay = 1ms;} <--> R11.medium++;
        R11.medium++ <--> DatarateChannel{delay = 1ms;} <--> R12.medium++;
        R12.medium++ <--> DatarateChannel{delay = 1ms;} <--> R13.medium++;
        R20.medium++ <--> DatarateChannel{delay = 1ms;} <--> R21.medium++;
        R21.medium++ <--> DatarateChannel{delay = 1ms;} <--> R22.medium++;
        R22.medium++ <--> DatarateChannel{delay = 1ms;} <--> R23.medium++;
        R30.medium++ <--> DatarateChannel{delay = 1ms;} <--> R31.medium++;
        R31.medium++ <--> DatarateChannel{delay = 1ms;} <--> R32.medium++;
        R32.medium++ <--> DatarateChannel{delay = 1ms;} <--> R33.medium++;

        HA.medium <--> DatarateChannel{delay = 1ms;} <--> R00.medium++;
        HB.medium <--> DatarateChannel{delay = 1ms;} <--> R03.medium++;
        HC.medium <--> DatarateChannel{delay = 1ms;} <--> R30.medium++;
        HD.medium <--> DatarateChannel{delay = 1ms;} <--> R33.medium++;

        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R00.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R01.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R02.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R03.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R10.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R11.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R12.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R13.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R20.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R21.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R22.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R23.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R30.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R31.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R32.medium++;
        Man.medium++ <--> DatarateChannel{delay = 1ms;} <--> R33.medium++;
}
