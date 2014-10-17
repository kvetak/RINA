package rina.DIF.FA;

import rina.DIF.NSM.NameSpaceManager;


module FlowAllocator
{
    parameters:
        @display("i=block/fork;bgb=387,318");

    gates:

    submodules:
        fa: FA {
            @display("p=96,64");
        }

        faiTable: FAITable {
            @display("p=265,64");
        }

    connections:


}
