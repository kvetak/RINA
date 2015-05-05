package rina.examples.CongestedNode;
import ned.DatarateChannel;
import rina.CS.HostNAP;
import rina.CS.InteriorRouter2Int;

network CongestedNode {
	submodules:
		host1 : HostNAP;
		host2 : HostNAP;
		router : InteriorRouter2Int;
	connections:
		host1.medium <--> DatarateChannel {  datarate = 11138Mbps; } <--> router.medium[0];
		host2.medium <--> DatarateChannel {  datarate = 11138Mbps; } <--> router.medium[1];
}
