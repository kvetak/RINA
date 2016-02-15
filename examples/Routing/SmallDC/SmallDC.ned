//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 



package rina.examples.Routing.SmallDC;

import ned.DatarateChannel;
import rina.src.DAF.AE.AEData.AEData;
import rina.src.Other.FlowsListener.FlowListener;
import rina.src.Other.Infection.InfectedDCRouter;

network SmallDC
{
    @display("bgb=960,500");
	submodules:
		T_0_0: InfectedDCRouter {
            @display("p=75,400");
        }
		T_0_1: InfectedDCRouter {
            @display("p=135,400");
        }
		T_0_2: InfectedDCRouter {
            @display("p=195,400");
        }
		T_1_0: InfectedDCRouter {
            @display("p=315,400");
        }
		T_1_1: InfectedDCRouter {
            @display("p=375,400");
        }
		T_1_2: InfectedDCRouter {
            @display("p=435,400");
        }
		T_2_0: InfectedDCRouter {
            @display("p=555,400");
        }
		T_2_1: InfectedDCRouter {
            @display("p=615,400");
        }
		T_2_2: InfectedDCRouter {
            @display("p=675,400");
        }
		T_3_0: InfectedDCRouter {
            @display("p=795,400");
        }
		T_3_1: InfectedDCRouter {
            @display("p=855,400");
        }
		T_3_2: InfectedDCRouter {
            @display("p=915,400");
        }

		F_0_0: InfectedDCRouter {
            @display("p=75,300");
        }
		F_0_1: InfectedDCRouter {
            @display("p=135,300");
        }
		F_0_2: InfectedDCRouter {
            @display("p=195,300");
        }
		F_1_0: InfectedDCRouter {
            @display("p=315,300");
        }
		F_1_1: InfectedDCRouter {
            @display("p=375,300");
        }
		F_1_2: InfectedDCRouter {
            @display("p=435,300");
        }
		F_2_0: InfectedDCRouter {
            @display("p=555,300");
        }
		F_2_1: InfectedDCRouter {
            @display("p=615,300");
        }
		F_2_2: InfectedDCRouter {
            @display("p=675,300");
        }
		F_3_0: InfectedDCRouter {
            @display("p=795,300");
        }
		F_3_1: InfectedDCRouter {
            @display("p=855,300");
        }
		F_3_2: InfectedDCRouter {
            @display("p=915,300");
        }

		S_0_0: InfectedDCRouter {
            @display("p=77.142857142857,200");
        }
		S_0_1: InfectedDCRouter {
            @display("p=141.42857142857,200");
        }
		S_0_2: InfectedDCRouter {
            @display("p=205.71428571429,200");
        }
		S_0_3: InfectedDCRouter {
            @display("p=270,200");
        }
		S_1_0: InfectedDCRouter {
            @display("p=398.57142857143,200");
        }
		S_1_1: InfectedDCRouter {
            @display("p=462.85714285714,200");
        }
		S_1_2: InfectedDCRouter {
            @display("p=527.14285714286,200");
        }
		S_1_3: InfectedDCRouter {
            @display("p=591.42857142857,200");
        }
		S_2_0: InfectedDCRouter {
            @display("p=720,200");
        }
		S_2_1: InfectedDCRouter {
            @display("p=784.28571428571,200");
        }
		S_2_2: InfectedDCRouter {
            @display("p=848.57142857143,200");
        }
		S_2_3: InfectedDCRouter {
            @display("p=912.85714285714,200");
        }

		E_0_0: InfectedDCRouter {
            @display("p=85.909090909091,100");
        }
		E_0_1: InfectedDCRouter {
            @display("p=167.72727272727,100");
        }
		E_0_2: InfectedDCRouter {
            @display("p=249.54545454545,100");
        }
		E_1_0: InfectedDCRouter {
            @display("p=413.18181818182,100");
        }
		E_1_1: InfectedDCRouter {
            @display("p=495,100");
        }
		E_1_2: InfectedDCRouter {
            @display("p=576.81818181818,100");
        }
		E_2_0: InfectedDCRouter {
            @display("p=740.45454545455,100");
        }
		E_2_1: InfectedDCRouter {
            @display("p=822.27272727273,100");
        }
		E_2_2: InfectedDCRouter {
            @display("p=904.09090909091,100");
        }

        
        flowListener: FlowListener { @display("p=60,30");  }
       
    connections:
		T_0_0.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_0.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_0.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_1.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_2.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_2.medium++;

		F_0_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2_3.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_0.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_1.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_2.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0_3.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_0.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_1.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_2.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1_3.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_0.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_1.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_2.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2_3.medium++;

		E_0_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_0_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_0_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_0_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_1_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_1_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_1_2.medium++ <--> ES_Link <-->  S_2_3.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_0.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_1.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_2.medium++;
		E_2_0.medium++ <--> ES_Link <-->  S_0_3.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_0.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_1.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_2.medium++;
		E_2_1.medium++ <--> ES_Link <-->  S_1_3.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_0.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_1.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_2.medium++;
		E_2_2.medium++ <--> ES_Link <-->  S_2_3.medium++;

}


channel TF_Link extends DatarateChannel {
    parameters:
        datarate = 1Gbps;
        delay = 0;
        per = 0;
        ber = 0;
}

channel FS_Link extends DatarateChannel {
    parameters:
        datarate = 10Gbps;
        delay = 0;
        per = 0;
        ber = 0;
}

channel ES_Link extends DatarateChannel {
    parameters:
        datarate = 10Gbps;
        delay = 0;
        per = 0.00;
        ber = 0.0;
}

