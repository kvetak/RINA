package rina.examples.Tutorials.Topological_DC_Routing;

import rina.src.Addons.Channels.EthChannel.EthChannel;
import rina.src.Addons.Actions.FailureSimulation.FailureSimulation;
import rina.src.Addons.DataInjectors.ReachabilityTest.ReachabilityTest_Switch;
import rina.src.Addons.DataInjectors.ReachabilityTest.ReachabilityTest_Listener;
import rina.src.CS.Manager;

network net
{
    @display("bgb=1091.89,872.69");
    submodules:
        //Testers first -> Needs to be innitialized first!!
        listener: ReachabilityTest_Listener {
            @display("p=50.69,417.85");
        }
        fails: FailureSimulation {
            @display("i=device/clock;p=1048.05,406.89");
        }

        //Spine set 0
        _0_0: ReachabilityTest_Switch {
            @display("p=167.14,408.26");
        }
        _0_1: ReachabilityTest_Switch {
            @display("p=224.68001,408.26");
        }
        _0_2: ReachabilityTest_Switch {
            @display("p=334.28,408.26");
        }
        _0_3: ReachabilityTest_Switch {
            @display("p=280.85,408.26");
        }

        //Spine set 1
        _1_0: ReachabilityTest_Switch {
            @display("p=490.46,408.26");
        }
        _1_1: ReachabilityTest_Switch {
            @display("p=548,408.26");
        }
        _1_2: ReachabilityTest_Switch {
            @display("p=604.17,408.26");
        }
        _1_3: ReachabilityTest_Switch {
            @display("p=657.6,408.26");
        }

        //Spine set 2
        _2_0: ReachabilityTest_Switch {
            @display("p=779.53,408.26");
        }
        _2_1: ReachabilityTest_Switch {
            @display("p=837.07,408.26");
        }
        _2_2: ReachabilityTest_Switch {
            @display("p=893.24,408.26");
        }
        _2_3: ReachabilityTest_Switch {
            @display("p=945.3,408.26");
        }


		//Pod 3
        _3_0: ReachabilityTest_Switch {
            @display("p=105.49,591.84");
        }
        _3_1: ReachabilityTest_Switch {
            @display("p=145.22,591.84");
        }
        _3_2: ReachabilityTest_Switch {
            @display("p=183.58,591.84");
        }
        _3_3: ReachabilityTest_Switch {
            @display("p=50.69,690.48");
        }
        _3_4: ReachabilityTest_Switch {
            @display("p=90.42,690.48");
        }
        _3_5: ReachabilityTest_Switch {
            @display("p=128.78,690.48");
        }
        _3_6: ReachabilityTest_Switch {
            @display("p=167.14,690.48");
        }
        _3_7: ReachabilityTest_Switch {
            @display("p=205.5,690.48");
        }
        _3_8: ReachabilityTest_Switch {
            @display("p=245.23,690.48");
        }

		//Pod 4
        _4_0: ReachabilityTest_Switch {
            @display("p=375.38,591.84");
        }
        _4_1: ReachabilityTest_Switch {
            @display("p=413.74,591.84");
        }
        _4_2: ReachabilityTest_Switch {
            @display("p=453.47,591.84");
        }
        _4_3: ReachabilityTest_Switch {
            @display("p=320.58,690.48");
        }
        _4_4: ReachabilityTest_Switch {
            @display("p=358.94,690.48");
        }
        _4_5: ReachabilityTest_Switch {
            @display("p=397.3,690.48");
        }
        _4_6: ReachabilityTest_Switch {
            @display("p=435.66,690.48");
        }
        _4_7: ReachabilityTest_Switch {
            @display("p=475.39,690.48");
        }
        _4_8: ReachabilityTest_Switch {
            @display("p=513.75,690.48");
        }

		//Pod 5
        _5_0: ReachabilityTest_Switch {
            @display("p=642.53,591.84");
        }
        _5_1: ReachabilityTest_Switch {
            @display("p=680.89,591.84");
        }
        _5_2: ReachabilityTest_Switch {
            @display("p=720.62,591.84");
        }
        _5_3: ReachabilityTest_Switch {
            @display("p=586.36,690.48");
        }
        _5_4: ReachabilityTest_Switch {
            @display("p=626.09,690.48");
        }
        _5_5: ReachabilityTest_Switch {
            @display("p=664.45,690.48");
        }
        _5_6: ReachabilityTest_Switch {
            @display("p=702.81,690.48");
        }
        _5_7: ReachabilityTest_Switch {
            @display("p=742.54,690.48");
        }
        _5_8: ReachabilityTest_Switch {
            @display("p=780.9,690.48");
        }

		//Pod 6
        _6_0: ReachabilityTest_Switch {
            @display("p=911.05,591.84");
        }
        _6_1: ReachabilityTest_Switch {
            @display("p=949.41003,591.84");
        }
        _6_2: ReachabilityTest_Switch {
            @display("p=989.14,591.84");
        }
        _6_3: ReachabilityTest_Switch {
            @display("p=856.25,690.48");
        }
        _6_4: ReachabilityTest_Switch {
            @display("p=894.61,690.48");
        }
        _6_5: ReachabilityTest_Switch {
            @display("p=934.34,690.48");
        }
        _6_6: ReachabilityTest_Switch {
            @display("p=971.33,690.48");
        }
        _6_7: ReachabilityTest_Switch {
            @display("p=1011.06,690.48");
        }
        _6_8: ReachabilityTest_Switch {
            @display("p=1049.42,690.48");
        }


		//Pod 7
        _7_0: ReachabilityTest_Switch {
            @display("p=105.49,238.38");
        }
        _7_1: ReachabilityTest_Switch {
            @display("p=145.22,238.38");
        }
        _7_2: ReachabilityTest_Switch {
            @display("p=183.58,238.38");
        }
        _7_3: ReachabilityTest_Switch {
            @display("p=50.69,142.48");
        }
        _7_4: ReachabilityTest_Switch {
            @display("p=90.42,142.48");
        }
        _7_5: ReachabilityTest_Switch {
            @display("p=128.78,142.48");
        }
        _7_6: ReachabilityTest_Switch {
            @display("p=167.14,142.48");
        }
        _7_7: ReachabilityTest_Switch {
            @display("p=205.5,142.48");
        }
        _7_8: ReachabilityTest_Switch {
            @display("p=245.23,142.48");
        }

		//Pod 8
        _8_0: ReachabilityTest_Switch {
            @display("p=375.38,238.38");
        }
        _8_1: ReachabilityTest_Switch {
            @display("p=413.74,238.38");
        }
        _8_2: ReachabilityTest_Switch {
            @display("p=453.47,238.38");
        }
        _8_3: ReachabilityTest_Switch {
            @display("p=320.58,142.48");
        }
        _8_4: ReachabilityTest_Switch {
            @display("p=358.94,142.48");
        }
        _8_5: ReachabilityTest_Switch {
            @display("p=397.3,142.48");
        }
        _8_6: ReachabilityTest_Switch {
            @display("p=435.66,142.48");
        }
        _8_7: ReachabilityTest_Switch {
            @display("p=475.39,142.48");
        }
        _8_8: ReachabilityTest_Switch {
            @display("p=513.75,142.48");
        }

		//Pod 9
        _9_0: ReachabilityTest_Switch {
            @display("p=642.53,238.38");
        }
        _9_1: ReachabilityTest_Switch {
            @display("p=680.89,238.38");
        }
        _9_2: ReachabilityTest_Switch {
            @display("p=720.62,238.38");
        }
        _9_3: ReachabilityTest_Switch {
            @display("p=586.36,142.48");
        }
        _9_4: ReachabilityTest_Switch {
            @display("p=626.09,142.48");
        }
        _9_5: ReachabilityTest_Switch {
            @display("p=664.45,142.48");
        }
        _9_6: ReachabilityTest_Switch {
            @display("p=702.81,142.48");
        }
        _9_7: ReachabilityTest_Switch {
            @display("p=742.54,142.48");
        }
        _9_8: ReachabilityTest_Switch {
            @display("p=780.9,142.48");
        }

		//Pod a
        _a_0: ReachabilityTest_Switch {
            @display("p=911.05,238.38");
        }
        _a_1: ReachabilityTest_Switch {
            @display("p=949.41003,238.38");
        }
        _a_2: ReachabilityTest_Switch {
            @display("p=989.14,238.38");
        }
        _a_3: ReachabilityTest_Switch {
            @display("p=856.25,142.48");
        }
        _a_4: ReachabilityTest_Switch {
            @display("p=894.61,142.48");
        }
        _a_5: ReachabilityTest_Switch {
            @display("p=934.34,142.48");
        }
        _a_6: ReachabilityTest_Switch {
            @display("p=971.33,142.48");
        }
        _a_7: ReachabilityTest_Switch {
            @display("p=1011.06,142.48");
        }
        _a_8: ReachabilityTest_Switch {
            @display("p=1049.42,142.48");
        }

        //Managers
        _3_FD: Manager {
            @display("p=105.49,801.45");
        }
        _3_FE: Manager {
            @display("p=205.5,801.45");
        }
        _4_FD: Manager {
            @display("p=358.94,801.45");
        }
        _4_FE: Manager {
            @display("p=458.95,801.45");
        }
        _5_FD: Manager {
            @display("p=620.61,801.45");
        }
        _5_FE: Manager {
            @display("p=720.62,801.45");
        }
        _6_FD: Manager {
            @display("p=889.13,801.45");
        }
        _6_FE: Manager {
            @display("p=989.14,801.45");
        }
        _7_FD: Manager {
            @display("p=105.49,52.06");
        }
        _7_FE: Manager {
            @display("p=205.5,52.06");
        }
        _8_FD: Manager {
            @display("p=375.38,52.06");
        }
        _8_FE: Manager {
            @display("p=475.39,52.06");
        }
        _9_FD: Manager {
            @display("p=642.53,52.06");
        }
        _9_FE: Manager {
            @display("p=742.54,52.06");
        }
        _a_FD: Manager {
            @display("p=911.05,52.06");
        }
        _a_FE: Manager {
            @display("p=1011.06,52.06");
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
        
        _3_3.medium++ <--> EthChannel <--> _3_FE.medium++;
        _3_4.medium++ <--> EthChannel <--> _3_FD.medium++;
        _4_3.medium++ <--> EthChannel <--> _4_FE.medium++;
        _4_4.medium++ <--> EthChannel <--> _4_FD.medium++;
        _5_3.medium++ <--> EthChannel <--> _5_FE.medium++;
        _5_4.medium++ <--> EthChannel <--> _5_FD.medium++;
        _6_3.medium++ <--> EthChannel <--> _6_FE.medium++;
        _6_4.medium++ <--> EthChannel <--> _6_FD.medium++;
        _7_3.medium++ <--> EthChannel <--> _7_FE.medium++;
        _7_4.medium++ <--> EthChannel <--> _7_FD.medium++;
        _8_3.medium++ <--> EthChannel <--> _8_FE.medium++;
        _8_4.medium++ <--> EthChannel <--> _8_FD.medium++;
        _9_3.medium++ <--> EthChannel <--> _9_FE.medium++;
        _9_4.medium++ <--> EthChannel <--> _9_FD.medium++;
        _a_3.medium++ <--> EthChannel <--> _a_FE.medium++;
        _a_4.medium++ <--> EthChannel <--> _a_FD.medium++;
}
