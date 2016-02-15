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

package rina.examples.Routing.GDC;

import ned.DatarateChannel;
import rina.src.DAF.AE.AEData.AEData;
import rina.src.Other.FlowsListener.FlowListener;
import rina.src.Other.Infection.InfectedDCRouter;

network GDC
{
	submodules:
		T_0_0: InfectedDCRouter;
		T_0_1: InfectedDCRouter;
		T_0_2: InfectedDCRouter;
		T_0_3: InfectedDCRouter;
		T_1_0: InfectedDCRouter;
		T_1_1: InfectedDCRouter;
		T_1_2: InfectedDCRouter;
		T_1_3: InfectedDCRouter;
		T_2_0: InfectedDCRouter;
		T_2_1: InfectedDCRouter;
		T_2_2: InfectedDCRouter;
		T_2_3: InfectedDCRouter;
		T_3_0: InfectedDCRouter;
		T_3_1: InfectedDCRouter;
		T_3_2: InfectedDCRouter;
		T_3_3: InfectedDCRouter;

		F_0_0: InfectedDCRouter ;
		F_0_1: InfectedDCRouter ;
		F_0_2: InfectedDCRouter ;
		F_1_0: InfectedDCRouter ;
		F_1_1: InfectedDCRouter ;
		F_1_2: InfectedDCRouter ;
		F_2_0: InfectedDCRouter ;
		F_2_1: InfectedDCRouter ;
		F_2_2: InfectedDCRouter ;
		F_3_0: InfectedDCRouter ;
		F_3_1: InfectedDCRouter ;
		F_3_2: InfectedDCRouter ;

		S_0: InfectedDCRouter ;
		S_1: InfectedDCRouter ;
		S_2: InfectedDCRouter ;
		S_3: InfectedDCRouter ;
		S_4: InfectedDCRouter ;
		S_5: InfectedDCRouter ;
		S_6: InfectedDCRouter ;
		S_7: InfectedDCRouter ;
		S_8: InfectedDCRouter ;
		S_9: InfectedDCRouter ;

		E_0_0: InfectedDCRouter;
		E_0_1: InfectedDCRouter;
		E_0_2: InfectedDCRouter;
		E_1_0: InfectedDCRouter;
		E_1_1: InfectedDCRouter;
		E_1_2: InfectedDCRouter;

		O_0_0: InfectedDCRouter ;
		O_0_1: InfectedDCRouter ;
		O_0_2: InfectedDCRouter ;
		O_1_0: InfectedDCRouter ;
		O_1_1: InfectedDCRouter ;
		O_1_2: InfectedDCRouter ;
    
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
		T_0_3.medium++ <--> TF_Link <-->  F_0_0.medium++;
		T_0_3.medium++ <--> TF_Link <-->  F_0_1.medium++;
		T_0_3.medium++ <--> TF_Link <-->  F_0_2.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_0.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_1.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_2.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_0.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_1.medium++;
		T_1_3.medium++ <--> TF_Link <-->  F_1_2.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_0.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_1.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_2.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_0.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_1.medium++;
		T_2_3.medium++ <--> TF_Link <-->  F_2_2.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_0.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_1.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_2.medium++ <--> TF_Link <-->  F_3_2.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_0.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_1.medium++;
		T_3_3.medium++ <--> TF_Link <-->  F_3_2.medium++;
		E_0_0.medium++ <--> TF_Link <-->  O_0_0.medium++;
		E_0_0.medium++ <--> TF_Link <-->  O_0_1.medium++;
		E_0_0.medium++ <--> TF_Link <-->  O_0_2.medium++;
		E_0_1.medium++ <--> TF_Link <-->  O_0_0.medium++;
		E_0_1.medium++ <--> TF_Link <-->  O_0_1.medium++;
		E_0_1.medium++ <--> TF_Link <-->  O_0_2.medium++;
		E_0_2.medium++ <--> TF_Link <-->  O_0_0.medium++;
		E_0_2.medium++ <--> TF_Link <-->  O_0_1.medium++;
		E_0_2.medium++ <--> TF_Link <-->  O_0_2.medium++;
		E_1_0.medium++ <--> TF_Link <-->  O_1_0.medium++;
		E_1_0.medium++ <--> TF_Link <-->  O_1_1.medium++;
		E_1_0.medium++ <--> TF_Link <-->  O_1_2.medium++;
		E_1_1.medium++ <--> TF_Link <-->  O_1_0.medium++;
		E_1_1.medium++ <--> TF_Link <-->  O_1_1.medium++;
		E_1_1.medium++ <--> TF_Link <-->  O_1_2.medium++;
		E_1_2.medium++ <--> TF_Link <-->  O_1_0.medium++;
		E_1_2.medium++ <--> TF_Link <-->  O_1_1.medium++;
		E_1_2.medium++ <--> TF_Link <-->  O_1_2.medium++;

		F_0_0.medium++ <--> FS_Link <-->  S_0.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_1.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_2.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_3.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_4.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_5.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_6.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_7.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_8.medium++;
		F_0_0.medium++ <--> FS_Link <-->  S_9.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_0.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_1.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_2.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_3.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_4.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_5.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_6.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_7.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_8.medium++;
		F_0_1.medium++ <--> FS_Link <-->  S_9.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_0.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_1.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_2.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_3.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_4.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_5.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_6.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_7.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_8.medium++;
		F_0_2.medium++ <--> FS_Link <-->  S_9.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_0.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_1.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_2.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_3.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_4.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_5.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_6.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_7.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_8.medium++;
		F_1_0.medium++ <--> FS_Link <-->  S_9.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_0.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_1.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_2.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_3.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_4.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_5.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_6.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_7.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_8.medium++;
		F_1_1.medium++ <--> FS_Link <-->  S_9.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_0.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_1.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_2.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_3.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_4.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_5.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_6.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_7.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_8.medium++;
		F_1_2.medium++ <--> FS_Link <-->  S_9.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_0.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_1.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_2.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_3.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_4.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_5.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_6.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_7.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_8.medium++;
		F_2_0.medium++ <--> FS_Link <-->  S_9.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_0.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_1.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_2.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_3.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_4.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_5.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_6.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_7.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_8.medium++;
		F_2_1.medium++ <--> FS_Link <-->  S_9.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_0.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_1.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_2.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_3.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_4.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_5.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_6.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_7.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_8.medium++;
		F_2_2.medium++ <--> FS_Link <-->  S_9.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_0.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_1.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_2.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_3.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_4.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_5.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_6.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_7.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_8.medium++;
		F_3_0.medium++ <--> FS_Link <-->  S_9.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_0.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_1.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_2.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_3.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_4.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_5.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_6.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_7.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_8.medium++;
		F_3_1.medium++ <--> FS_Link <-->  S_9.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_0.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_1.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_2.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_3.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_4.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_5.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_6.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_7.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_8.medium++;
		F_3_2.medium++ <--> FS_Link <-->  S_9.medium++;

		O_0_0.medium++ <--> FS_Link <-->  S_0.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_1.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_2.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_3.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_4.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_5.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_6.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_7.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_8.medium++;
		O_0_0.medium++ <--> FS_Link <-->  S_9.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_0.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_1.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_2.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_3.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_4.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_5.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_6.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_7.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_8.medium++;
		O_0_1.medium++ <--> FS_Link <-->  S_9.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_0.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_1.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_2.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_3.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_4.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_5.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_6.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_7.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_8.medium++;
		O_0_2.medium++ <--> FS_Link <-->  S_9.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_0.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_1.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_2.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_3.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_4.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_5.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_6.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_7.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_8.medium++;
		O_1_0.medium++ <--> FS_Link <-->  S_9.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_0.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_1.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_2.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_3.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_4.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_5.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_6.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_7.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_8.medium++;
		O_1_1.medium++ <--> FS_Link <-->  S_9.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_0.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_1.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_2.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_3.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_4.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_5.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_6.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_7.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_8.medium++;
		O_1_2.medium++ <--> FS_Link <-->  S_9.medium++;

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
