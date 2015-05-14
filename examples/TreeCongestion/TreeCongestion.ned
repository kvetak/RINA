package rina.examples.TreeCongestion;
import ned.DatarateChannel;
import rina.src.CS.Host1AP;
import rina.src.CS.HostNAP;
import rina.src.CS.InteriorRouterNInt;

network TreeCongestion {
	submodules:
		router_1 : InteriorRouterNInt;
		router_2 : InteriorRouterNInt;
		hostS_0 : HostNAP;
		hostS_1 : HostNAP;
		hostS_2 : HostNAP;
		hostS_3 : HostNAP;
		hostR_0_0 : Host1AP;
		hostR_0_1 : Host1AP;
		hostR_0_2 : Host1AP;
		hostR_0_3 : Host1AP;
		hostR_1_0 : Host1AP;
		hostR_1_1 : Host1AP;
		hostR_1_2 : Host1AP;
		hostR_1_3 : Host1AP;
		hostR_2_0 : Host1AP;
		hostR_2_1 : Host1AP;
		hostR_2_2 : Host1AP;
		hostR_2_3 : Host1AP;
		hostR_3_0 : Host1AP;
		hostR_3_1 : Host1AP;
		hostR_3_2 : Host1AP;
		hostR_3_3 : Host1AP;
	connections:
		router_1.medium++ <--> DatarateChannel {  datarate = 1600Mbps; } <--> router_2.medium++;
		hostS_0.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostS_1.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostS_2.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostS_3.medium <--> DatarateChannel {  datarate = 300Mbps; } <--> router_1.medium++;
		hostR_0_0.medium <--> router_2.medium++;
		hostR_0_1.medium <--> router_2.medium++;
		hostR_0_2.medium <--> router_2.medium++;
		hostR_0_3.medium <--> router_2.medium++;
		hostR_1_0.medium <--> router_2.medium++;
		hostR_1_1.medium <--> router_2.medium++;
		hostR_1_2.medium <--> router_2.medium++;
		hostR_1_3.medium <--> router_2.medium++;
		hostR_2_0.medium <--> router_2.medium++;
		hostR_2_1.medium <--> router_2.medium++;
		hostR_2_2.medium <--> router_2.medium++;
		hostR_2_3.medium <--> router_2.medium++;
		hostR_3_0.medium <--> router_2.medium++;
		hostR_3_1.medium <--> router_2.medium++;
		hostR_3_2.medium <--> router_2.medium++;
		hostR_3_3.medium <--> router_2.medium++;
}
