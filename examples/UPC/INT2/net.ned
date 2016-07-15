package rina.examples.UPC.INT2;

import rina.src.Other.EthChannel.EthChannel;
import rina.src.Other.ONOFFInj.OFInjRouter;
import rina.src.Other.ONOFFInj.InjListener;

network net {
submodules:
N[2]:OFInjRouter;
listener: InjListener;

connections:
N[0].medium++ <--> EthChannel {  datarate = 1.0Gbps;  delay = 1.0ms; header = 16B; ipg = 4B;} <--> N[1].medium++;
}