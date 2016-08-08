package rina.examples.UPC.DCa;

import rina.src.Other.EthChannel.EthChannel;
import rina.src.Other.ConnectivityTest.ConnectivityTestSwitch;
import rina.src.Other.ConnectivityTest.ConnectivityTestListener;
import rina.src.Other.FailureTest.FailureTest;

network net
{
    @display("bgb=833,343");
    submodules:
//Testers first -> Needs to be innitialized first!!
        listener: ConnectivityTestListener {
            @display("p=64,44");
        }
        fails: FailureTest {
            @display("i=device/clock");
        }
//Next nodes
        _0_0: ConnectivityTestSwitch {
            @display("p=161,55");
        }
        _0_1: ConnectivityTestSwitch {
            @display("p=258,55");
        }
        _1_1: ConnectivityTestSwitch {
            @display("p=665,55");
        }
        _1_0: ConnectivityTestSwitch {
            @display("p=568,55");
        }
        _2_0: ConnectivityTestSwitch {
            @display("p=161,172");
        }
        _2_1: ConnectivityTestSwitch {
            @display("p=258,172");
        }
        _3_0: ConnectivityTestSwitch {
            @display("p=568,172");
        }
        _3_1: ConnectivityTestSwitch {
            @display("p=665,172");
        }
        _2_2: ConnectivityTestSwitch {
            @display("p=64,271");
        }
        _2_3: ConnectivityTestSwitch {
            @display("p=161,271");
        }
        _2_4: ConnectivityTestSwitch {
            @display("p=258,271");
        }
        _2_5: ConnectivityTestSwitch {
            @display("p=355,271");
        }
        _3_2: ConnectivityTestSwitch {
            @display("p=471,271");
        }
        _3_3: ConnectivityTestSwitch {
            @display("p=568,271");
        }
        _3_4: ConnectivityTestSwitch {
            @display("p=665,271");
        }
        _3_5: ConnectivityTestSwitch {
            @display("p=762,271");
        }
    connections:
        _2_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _2_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _3_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _3_0.medium++ <--> EthChannel <--> _0_1.medium++;

        _2_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _2_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _3_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _3_1.medium++ <--> EthChannel <--> _1_1.medium++;

        _2_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _2_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _2_3.medium++ <--> EthChannel <--> _2_0.medium++;
        _2_3.medium++ <--> EthChannel <--> _2_1.medium++;
        _2_4.medium++ <--> EthChannel <--> _2_0.medium++;
        _2_4.medium++ <--> EthChannel <--> _2_1.medium++;
        _2_5.medium++ <--> EthChannel <--> _2_0.medium++;
        _2_5.medium++ <--> EthChannel <--> _2_1.medium++;

        _3_2.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_2.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_3.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_3.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_4.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_4.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_5.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_5.medium++ <--> EthChannel <--> _3_1.medium++;
}
