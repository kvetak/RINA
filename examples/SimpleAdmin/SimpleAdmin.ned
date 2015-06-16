package rina.examples.SimpleAdmin;
import ned.DatarateChannel;
import rina.src.CS.*;

network SimpleAdmin
{
    @display("bgb=609,634");
    submodules:
        Man: Shim_M_Adm {
            @display("p=306,56");
        }

        C1: InteriorRouterNInt_Adm {
            @display("p=253,160");
        }
        C2: InteriorRouterNInt_Adm {
            @display("p=359,160");
        }
        R1_1: InteriorRouterNInt {
            @display("p=140,160");
        }
        R1_2: InteriorRouterNInt {
            @display("p=140,160");
        }
        R1_3: InteriorRouterNInt {
            @display("p=140,160");
        }
        R1_4: InteriorRouterNInt {
            @display("p=140,160");
        }
        R2_1: InteriorRouterNInt {
            @display("p=450,160");
        }
        R2_2: InteriorRouterNInt {
            @display("p=450,160");
        }
        R2_3: InteriorRouterNInt {
            @display("p=450,160");
        }
        R2_4: InteriorRouterNInt {
            @display("p=450,160");
        }
    connections:
        C1.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R1_1.medium++;
        C2.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R2_1.medium++;
        
        C1.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R1_2.medium++;
        C2.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R2_2.medium++;
        
        C1.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R1_3.medium++;
        C2.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R2_3.medium++;
        
        C1.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R1_4.medium++;
        C2.medium++ <--> DatarateChannel {  delay = 1ms; } <--> R2_4.medium++;
        
        C1.medium++ <--> DatarateChannel {  delay = 1ms; } <--> C2.medium++;
        
        Man.medium++ <--> DatarateChannel {  delay = 1ms; } <--> C1.medium++;
        Man.medium++ <--> DatarateChannel {  delay = 1ms; } <--> C2.medium++;
}
