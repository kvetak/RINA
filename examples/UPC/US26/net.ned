package rina.examples.UPC.US26;

import ned.DatarateChannel;
import rina.src.Other.ONOFFInj.OFInjRouter;
import rina.src.Other.ONOFFInj.InjListener;

network net {
submodules:
N[26]:OFInjRouter;
listener: InjListener;

connections:
N[0].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.375ms; } <--> N[2].medium++;
N[0].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.391ms; } <--> N[4].medium++;
N[1].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 684.0us; } <--> N[2].medium++;
N[1].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 477.0us; } <--> N[3].medium++;
N[1].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.415ms; } <--> N[5].medium++;
N[2].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.209ms; } <--> N[4].medium++;
N[3].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 763.0us; } <--> N[4].medium++;
N[3].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.177ms; } <--> N[5].medium++;
N[4].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 770.0us; } <--> N[11].medium++;
N[5].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.135ms; } <--> N[6].medium++;
N[5].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.349ms; } <--> N[7].medium++;
N[6].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 440.0us; } <--> N[7].medium++;
N[6].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 481.0us; } <--> N[8].medium++;
N[6].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.093ms; } <--> N[11].medium++;
N[6].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.257ms; } <--> N[16].medium++;
N[7].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 646.0us; } <--> N[21].medium++;
N[8].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 454.0us; } <--> N[10].medium++;
N[8].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 723.0us; } <--> N[15].medium++;
N[9].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 816.0us; } <--> N[10].medium++;
N[9].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 702.0us; } <--> N[12].medium++;
N[10].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.093ms; } <--> N[11].medium++;
N[10].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 478.0us; } <--> N[15].medium++;
N[12].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 367.0us; } <--> N[13].medium++;
N[12].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 507.0us; } <--> N[14].medium++;
N[12].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 523.0us; } <--> N[15].medium++;
N[13].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 462.0us; } <--> N[15].medium++;
N[13].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 496.0us; } <--> N[16].medium++;
N[13].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 552.0us; } <--> N[17].medium++;
N[14].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 118.0us; } <--> N[17].medium++;
N[16].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 665.0us; } <--> N[20].medium++;
N[16].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 430.0us; } <--> N[23].medium++;
N[17].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 834.0us; } <--> N[19].medium++;
N[17].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 618.0us; } <--> N[25].medium++;
N[18].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 293.0us; } <--> N[19].medium++;
N[18].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 374.0us; } <--> N[22].medium++;
N[18].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 430.0us; } <--> N[25].medium++;
N[19].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 290.0us; } <--> N[22].medium++;
N[20].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 457.0us; } <--> N[23].medium++;
N[20].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 667.0us; } <--> N[25].medium++;
N[21].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 853.0us; } <--> N[23].medium++;
N[21].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.327ms; } <--> N[24].medium++;
N[23].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.203ms; } <--> N[24].medium++;

}
