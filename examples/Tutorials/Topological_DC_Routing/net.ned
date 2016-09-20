package rina.examples.Tutorials.Topological_DC_Routing;

import rina.src.Addons.Channels.EthChannel.EthChannel;
import rina.src.Addons.Actions.FailureSimulation.FailureSimulation;
import rina.src.Addons.DataInjectors.ReachabilityTest.ReachabilityTest_Switch;
import rina.src.Addons.DataInjectors.ReachabilityTest.ReachabilityTest_Listener;

network net
{
    @display("bgb=1092,650");
    submodules:
        //Testers first -> Needs to be innitialized first!!
        listener: ReachabilityTest_Listener {
            @display("p=53,327");
        }
        fails: FailureSimulation {
            @display("i=device/clock;p=1050,316");
        }

        //Spine set 0
        _0_0: ReachabilityTest_Switch {
            @display("p=169,317");
        }
        _0_1: ReachabilityTest_Switch {
            @display("p=227,317");
        }
        _0_2: ReachabilityTest_Switch {
            @display("p=336,317");
        }
        _0_3: ReachabilityTest_Switch {
            @display("p=283,317");
        }

        //Spine set 1
        _1_0: ReachabilityTest_Switch {
            @display("p=492,317");
        }
        _1_1: ReachabilityTest_Switch {
            @display("p=550,317");
        }
        _1_2: ReachabilityTest_Switch {
            @display("p=606,317");
        }
        _1_3: ReachabilityTest_Switch {
            @display("p=659,317");
        }

        //Spine set 2
        _2_0: ReachabilityTest_Switch {
            @display("p=781,317");
        }
        _2_1: ReachabilityTest_Switch {
            @display("p=839,317");
        }
        _2_2: ReachabilityTest_Switch {
            @display("p=895,317");
        }
        _2_3: ReachabilityTest_Switch {
            @display("p=948,317");
        }


		//Pod 3
        _3_0: ReachabilityTest_Switch {
            @display("p=108,501");
        }
        _3_1: ReachabilityTest_Switch {
            @display("p=147,501");
        }
        _3_2: ReachabilityTest_Switch {
            @display("p=186,501");
        }
        _3_3: ReachabilityTest_Switch {
            @display("p=53,600");
        }
        _3_4: ReachabilityTest_Switch {
            @display("p=92,600");
        }
        _3_5: ReachabilityTest_Switch {
            @display("p=131,600");
        }
        _3_6: ReachabilityTest_Switch {
            @display("p=169,600");
        }
        _3_7: ReachabilityTest_Switch {
            @display("p=208,600");
        }
        _3_8: ReachabilityTest_Switch {
            @display("p=247,600");
        }

		//Pod 4
        _4_0: ReachabilityTest_Switch {
            @display("p=377,501");
        }
        _4_1: ReachabilityTest_Switch {
            @display("p=416,501");
        }
        _4_2: ReachabilityTest_Switch {
            @display("p=455,501");
        }
        _4_3: ReachabilityTest_Switch {
            @display("p=322,600");
        }
        _4_4: ReachabilityTest_Switch {
            @display("p=361,600");
        }
        _4_5: ReachabilityTest_Switch {
            @display("p=400,600");
        }
        _4_6: ReachabilityTest_Switch {
            @display("p=438,600");
        }
        _4_7: ReachabilityTest_Switch {
            @display("p=477,600");
        }
        _4_8: ReachabilityTest_Switch {
            @display("p=516,600");
        }

		//Pod 5
        _5_0: ReachabilityTest_Switch {
            @display("p=644,501");
        }
        _5_1: ReachabilityTest_Switch {
            @display("p=683,501");
        }
        _5_2: ReachabilityTest_Switch {
            @display("p=722,501");
        }
        _5_3: ReachabilityTest_Switch {
            @display("p=589,600");
        }
        _5_4: ReachabilityTest_Switch {
            @display("p=628,600");
        }
        _5_5: ReachabilityTest_Switch {
            @display("p=667,600");
        }
        _5_6: ReachabilityTest_Switch {
            @display("p=705,600");
        }
        _5_7: ReachabilityTest_Switch {
            @display("p=744,600");
        }
        _5_8: ReachabilityTest_Switch {
            @display("p=783,600");
        }

		//Pod 6
        _6_0: ReachabilityTest_Switch {
            @display("p=913,501");
        }
        _6_1: ReachabilityTest_Switch {
            @display("p=952,501");
        }
        _6_2: ReachabilityTest_Switch {
            @display("p=991,501");
        }
        _6_3: ReachabilityTest_Switch {
            @display("p=858,600");
        }
        _6_4: ReachabilityTest_Switch {
            @display("p=897,600");
        }
        _6_5: ReachabilityTest_Switch {
            @display("p=936,600");
        }
        _6_6: ReachabilityTest_Switch {
            @display("p=974,600");
        }
        _6_7: ReachabilityTest_Switch {
            @display("p=1013,600");
        }
        _6_8: ReachabilityTest_Switch {
            @display("p=1052,600");
        }


		//Pod 7
        _7_0: ReachabilityTest_Switch {
            @display("p=108,147");
        }
        _7_1: ReachabilityTest_Switch {
            @display("p=147,147");
        }
        _7_2: ReachabilityTest_Switch {
            @display("p=186,147");
        }
        _7_3: ReachabilityTest_Switch {
            @display("p=53,51");
        }
        _7_4: ReachabilityTest_Switch {
            @display("p=92,51");
        }
        _7_5: ReachabilityTest_Switch {
            @display("p=131,51");
        }
        _7_6: ReachabilityTest_Switch {
            @display("p=169,51");
        }
        _7_7: ReachabilityTest_Switch {
            @display("p=208,51");
        }
        _7_8: ReachabilityTest_Switch {
            @display("p=247,51");
        }

		//Pod 8
        _8_0: ReachabilityTest_Switch {
            @display("p=377,147");
        }
        _8_1: ReachabilityTest_Switch {
            @display("p=416,147");
        }
        _8_2: ReachabilityTest_Switch {
            @display("p=455,147");
        }
        _8_3: ReachabilityTest_Switch {
            @display("p=322,51");
        }
        _8_4: ReachabilityTest_Switch {
            @display("p=361,51");
        }
        _8_5: ReachabilityTest_Switch {
            @display("p=400,51");
        }
        _8_6: ReachabilityTest_Switch {
            @display("p=438,51");
        }
        _8_7: ReachabilityTest_Switch {
            @display("p=477,51");
        }
        _8_8: ReachabilityTest_Switch {
            @display("p=516,51");
        }

		//Pod 9
        _9_0: ReachabilityTest_Switch {
            @display("p=644,147");
        }
        _9_1: ReachabilityTest_Switch {
            @display("p=683,147");
        }
        _9_2: ReachabilityTest_Switch {
            @display("p=722,147");
        }
        _9_3: ReachabilityTest_Switch {
            @display("p=589,51");
        }
        _9_4: ReachabilityTest_Switch {
            @display("p=628,51");
        }
        _9_5: ReachabilityTest_Switch {
            @display("p=667,51");
        }
        _9_6: ReachabilityTest_Switch {
            @display("p=705,51");
        }
        _9_7: ReachabilityTest_Switch {
            @display("p=744,51");
        }
        _9_8: ReachabilityTest_Switch {
            @display("p=783,51");
        }

		//Pod a
        _a_0: ReachabilityTest_Switch {
            @display("p=913,147");
        }
        _a_1: ReachabilityTest_Switch {
            @display("p=952,147");
        }
        _a_2: ReachabilityTest_Switch {
            @display("p=991,147");
        }
        _a_3: ReachabilityTest_Switch {
            @display("p=858,51");
        }
        _a_4: ReachabilityTest_Switch {
            @display("p=897,51");
        }
        _a_5: ReachabilityTest_Switch {
            @display("p=936,51");
        }
        _a_6: ReachabilityTest_Switch {
            @display("p=974,51");
        }
        _a_7: ReachabilityTest_Switch {
            @display("p=1013,51");
        }
        _a_8: ReachabilityTest_Switch {
            @display("p=1052,51");
        }
    connections:

        _3_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _3_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _3_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _3_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _4_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _4_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _4_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _4_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _5_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _5_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _5_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _5_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _6_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _6_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _6_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _6_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _7_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _7_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _7_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _7_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _8_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _8_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _8_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _8_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _9_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _9_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _9_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _9_0.medium++ <--> EthChannel <--> _0_3.medium++;
        _a_0.medium++ <--> EthChannel <--> _0_0.medium++;
        _a_0.medium++ <--> EthChannel <--> _0_1.medium++;
        _a_0.medium++ <--> EthChannel <--> _0_2.medium++;
        _a_0.medium++ <--> EthChannel <--> _0_3.medium++;


        _3_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _3_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _3_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _3_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _4_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _4_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _4_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _4_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _5_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _5_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _5_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _5_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _6_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _6_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _6_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _6_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _7_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _7_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _7_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _7_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _8_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _8_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _8_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _8_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _9_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _9_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _9_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _9_1.medium++ <--> EthChannel <--> _1_3.medium++;
        _a_1.medium++ <--> EthChannel <--> _1_0.medium++;
        _a_1.medium++ <--> EthChannel <--> _1_1.medium++;
        _a_1.medium++ <--> EthChannel <--> _1_2.medium++;
        _a_1.medium++ <--> EthChannel <--> _1_3.medium++;


        _3_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _3_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _3_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _3_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _4_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _4_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _4_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _4_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _5_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _5_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _5_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _5_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _6_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _6_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _6_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _6_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _7_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _7_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _7_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _7_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _8_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _8_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _8_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _8_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _9_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _9_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _9_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _9_2.medium++ <--> EthChannel <--> _2_3.medium++;
        _a_2.medium++ <--> EthChannel <--> _2_0.medium++;
        _a_2.medium++ <--> EthChannel <--> _2_1.medium++;
        _a_2.medium++ <--> EthChannel <--> _2_2.medium++;
        _a_2.medium++ <--> EthChannel <--> _2_3.medium++;
        
        
        
        _3_3.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_3.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_3.medium++ <--> EthChannel <--> _3_2.medium++;
        _3_4.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_4.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_4.medium++ <--> EthChannel <--> _3_2.medium++;
        _3_5.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_5.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_5.medium++ <--> EthChannel <--> _3_2.medium++;
        _3_6.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_6.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_6.medium++ <--> EthChannel <--> _3_2.medium++;
        _3_7.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_7.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_7.medium++ <--> EthChannel <--> _3_2.medium++;
        _3_8.medium++ <--> EthChannel <--> _3_0.medium++;
        _3_8.medium++ <--> EthChannel <--> _3_1.medium++;
        _3_8.medium++ <--> EthChannel <--> _3_2.medium++;
        
        _4_3.medium++ <--> EthChannel <--> _4_0.medium++;
        _4_3.medium++ <--> EthChannel <--> _4_1.medium++;
        _4_3.medium++ <--> EthChannel <--> _4_2.medium++;
        _4_4.medium++ <--> EthChannel <--> _4_0.medium++;
        _4_4.medium++ <--> EthChannel <--> _4_1.medium++;
        _4_4.medium++ <--> EthChannel <--> _4_2.medium++;
        _4_5.medium++ <--> EthChannel <--> _4_0.medium++;
        _4_5.medium++ <--> EthChannel <--> _4_1.medium++;
        _4_5.medium++ <--> EthChannel <--> _4_2.medium++;
        _4_6.medium++ <--> EthChannel <--> _4_0.medium++;
        _4_6.medium++ <--> EthChannel <--> _4_1.medium++;
        _4_6.medium++ <--> EthChannel <--> _4_2.medium++;
        _4_7.medium++ <--> EthChannel <--> _4_0.medium++;
        _4_7.medium++ <--> EthChannel <--> _4_1.medium++;
        _4_7.medium++ <--> EthChannel <--> _4_2.medium++;
        _4_8.medium++ <--> EthChannel <--> _4_0.medium++;
        _4_8.medium++ <--> EthChannel <--> _4_1.medium++;
        _4_8.medium++ <--> EthChannel <--> _4_2.medium++;
        
        _5_3.medium++ <--> EthChannel <--> _5_0.medium++;
        _5_3.medium++ <--> EthChannel <--> _5_1.medium++;
        _5_3.medium++ <--> EthChannel <--> _5_2.medium++;
        _5_4.medium++ <--> EthChannel <--> _5_0.medium++;
        _5_4.medium++ <--> EthChannel <--> _5_1.medium++;
        _5_4.medium++ <--> EthChannel <--> _5_2.medium++;
        _5_5.medium++ <--> EthChannel <--> _5_0.medium++;
        _5_5.medium++ <--> EthChannel <--> _5_1.medium++;
        _5_5.medium++ <--> EthChannel <--> _5_2.medium++;
        _5_6.medium++ <--> EthChannel <--> _5_0.medium++;
        _5_6.medium++ <--> EthChannel <--> _5_1.medium++;
        _5_6.medium++ <--> EthChannel <--> _5_2.medium++;
        _5_7.medium++ <--> EthChannel <--> _5_0.medium++;
        _5_7.medium++ <--> EthChannel <--> _5_1.medium++;
        _5_7.medium++ <--> EthChannel <--> _5_2.medium++;
        _5_8.medium++ <--> EthChannel <--> _5_0.medium++;
        _5_8.medium++ <--> EthChannel <--> _5_1.medium++;
        _5_8.medium++ <--> EthChannel <--> _5_2.medium++;
        
        _6_3.medium++ <--> EthChannel <--> _6_0.medium++;
        _6_3.medium++ <--> EthChannel <--> _6_1.medium++;
        _6_3.medium++ <--> EthChannel <--> _6_2.medium++;
        _6_4.medium++ <--> EthChannel <--> _6_0.medium++;
        _6_4.medium++ <--> EthChannel <--> _6_1.medium++;
        _6_4.medium++ <--> EthChannel <--> _6_2.medium++;
        _6_5.medium++ <--> EthChannel <--> _6_0.medium++;
        _6_5.medium++ <--> EthChannel <--> _6_1.medium++;
        _6_5.medium++ <--> EthChannel <--> _6_2.medium++;
        _6_6.medium++ <--> EthChannel <--> _6_0.medium++;
        _6_6.medium++ <--> EthChannel <--> _6_1.medium++;
        _6_6.medium++ <--> EthChannel <--> _6_2.medium++;
        _6_7.medium++ <--> EthChannel <--> _6_0.medium++;
        _6_7.medium++ <--> EthChannel <--> _6_1.medium++;
        _6_7.medium++ <--> EthChannel <--> _6_2.medium++;
        _6_8.medium++ <--> EthChannel <--> _6_0.medium++;
        _6_8.medium++ <--> EthChannel <--> _6_1.medium++;
        _6_8.medium++ <--> EthChannel <--> _6_2.medium++;
        
        _7_3.medium++ <--> EthChannel <--> _7_0.medium++;
        _7_3.medium++ <--> EthChannel <--> _7_1.medium++;
        _7_3.medium++ <--> EthChannel <--> _7_2.medium++;
        _7_4.medium++ <--> EthChannel <--> _7_0.medium++;
        _7_4.medium++ <--> EthChannel <--> _7_1.medium++;
        _7_4.medium++ <--> EthChannel <--> _7_2.medium++;
        _7_5.medium++ <--> EthChannel <--> _7_0.medium++;
        _7_5.medium++ <--> EthChannel <--> _7_1.medium++;
        _7_5.medium++ <--> EthChannel <--> _7_2.medium++;
        _7_6.medium++ <--> EthChannel <--> _7_0.medium++;
        _7_6.medium++ <--> EthChannel <--> _7_1.medium++;
        _7_6.medium++ <--> EthChannel <--> _7_2.medium++;
        _7_7.medium++ <--> EthChannel <--> _7_0.medium++;
        _7_7.medium++ <--> EthChannel <--> _7_1.medium++;
        _7_7.medium++ <--> EthChannel <--> _7_2.medium++;
        _7_8.medium++ <--> EthChannel <--> _7_0.medium++;
        _7_8.medium++ <--> EthChannel <--> _7_1.medium++;
        _7_8.medium++ <--> EthChannel <--> _7_2.medium++;
        
        _8_3.medium++ <--> EthChannel <--> _8_0.medium++;
        _8_3.medium++ <--> EthChannel <--> _8_1.medium++;
        _8_3.medium++ <--> EthChannel <--> _8_2.medium++;
        _8_4.medium++ <--> EthChannel <--> _8_0.medium++;
        _8_4.medium++ <--> EthChannel <--> _8_1.medium++;
        _8_4.medium++ <--> EthChannel <--> _8_2.medium++;
        _8_5.medium++ <--> EthChannel <--> _8_0.medium++;
        _8_5.medium++ <--> EthChannel <--> _8_1.medium++;
        _8_5.medium++ <--> EthChannel <--> _8_2.medium++;
        _8_6.medium++ <--> EthChannel <--> _8_0.medium++;
        _8_6.medium++ <--> EthChannel <--> _8_1.medium++;
        _8_6.medium++ <--> EthChannel <--> _8_2.medium++;
        _8_7.medium++ <--> EthChannel <--> _8_0.medium++;
        _8_7.medium++ <--> EthChannel <--> _8_1.medium++;
        _8_7.medium++ <--> EthChannel <--> _8_2.medium++;
        _8_8.medium++ <--> EthChannel <--> _8_0.medium++;
        _8_8.medium++ <--> EthChannel <--> _8_1.medium++;
        _8_8.medium++ <--> EthChannel <--> _8_2.medium++;
        
        _9_3.medium++ <--> EthChannel <--> _9_0.medium++;
        _9_3.medium++ <--> EthChannel <--> _9_1.medium++;
        _9_3.medium++ <--> EthChannel <--> _9_2.medium++;
        _9_4.medium++ <--> EthChannel <--> _9_0.medium++;
        _9_4.medium++ <--> EthChannel <--> _9_1.medium++;
        _9_4.medium++ <--> EthChannel <--> _9_2.medium++;
        _9_5.medium++ <--> EthChannel <--> _9_0.medium++;
        _9_5.medium++ <--> EthChannel <--> _9_1.medium++;
        _9_5.medium++ <--> EthChannel <--> _9_2.medium++;
        _9_6.medium++ <--> EthChannel <--> _9_0.medium++;
        _9_6.medium++ <--> EthChannel <--> _9_1.medium++;
        _9_6.medium++ <--> EthChannel <--> _9_2.medium++;
        _9_7.medium++ <--> EthChannel <--> _9_0.medium++;
        _9_7.medium++ <--> EthChannel <--> _9_1.medium++;
        _9_7.medium++ <--> EthChannel <--> _9_2.medium++;
        _9_8.medium++ <--> EthChannel <--> _9_0.medium++;
        _9_8.medium++ <--> EthChannel <--> _9_1.medium++;
        _9_8.medium++ <--> EthChannel <--> _9_2.medium++;
        
        _a_3.medium++ <--> EthChannel <--> _a_0.medium++;
        _a_3.medium++ <--> EthChannel <--> _a_1.medium++;
        _a_3.medium++ <--> EthChannel <--> _a_2.medium++;
        _a_4.medium++ <--> EthChannel <--> _a_0.medium++;
        _a_4.medium++ <--> EthChannel <--> _a_1.medium++;
        _a_4.medium++ <--> EthChannel <--> _a_2.medium++;
        _a_5.medium++ <--> EthChannel <--> _a_0.medium++;
        _a_5.medium++ <--> EthChannel <--> _a_1.medium++;
        _a_5.medium++ <--> EthChannel <--> _a_2.medium++;
        _a_6.medium++ <--> EthChannel <--> _a_0.medium++;
        _a_6.medium++ <--> EthChannel <--> _a_1.medium++;
        _a_6.medium++ <--> EthChannel <--> _a_2.medium++;
        _a_7.medium++ <--> EthChannel <--> _a_0.medium++;
        _a_7.medium++ <--> EthChannel <--> _a_1.medium++;
        _a_7.medium++ <--> EthChannel <--> _a_2.medium++;
        _a_8.medium++ <--> EthChannel <--> _a_0.medium++;
        _a_8.medium++ <--> EthChannel <--> _a_1.medium++;
        _a_8.medium++ <--> EthChannel <--> _a_2.medium++;
}
