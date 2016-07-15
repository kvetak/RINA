package rina.examples.UPC.INT9;

import ned.DatarateChannel;
import rina.src.Other.ONOFFInj.OFInjRouter;
import rina.src.Other.ONOFFInj.InjListener;

network net {
submodules:
N[9]:OFInjRouter;
listener: InjListener;

connections:
N[0].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.342ms; } <--> N[1].medium++;
N[0].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 913.0us; } <--> N[2].medium++;
N[1].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.303ms; } <--> N[2].medium++;
N[1].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.705ms; } <--> N[4].medium++;
N[2].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.33ms; } <--> N[3].medium++;
N[3].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 818.0us; } <--> N[4].medium++;
N[3].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 690.0us; } <--> N[5].medium++;
N[4].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.385ms; } <--> N[8].medium++;
N[5].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.4ms; } <--> N[6].medium++;
N[5].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 905.0us; } <--> N[7].medium++;
N[5].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 1.045ms; } <--> N[8].medium++;
N[6].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 278.0us; } <--> N[7].medium++;
N[7].medium++ <--> DatarateChannel {  datarate = 1.0Gbps;  delay = 700.0us; } <--> N[8].medium++;

}
