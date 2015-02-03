RINA Simulator
====

###Version progress

* February 2015 version - After-Ghent release with FA policies
* January 2015 version - Ghent meeting with EFCP, RMT, RA, PDUFTG and policies
* November 2014 version - Brussels RV1 with AllNodes examples
* October 2014 version - Madrid F2F meeting with working SimpleRelay and TwoCSs scenarios

###Directory structure

	/examples					... scenarios testing RINA stack
		/AllNodes				... communication across all types of devices
		/SimpleRelay			... two CSs exchanging data through an interior router 
		/SingleCS				... single computing system with two applications
		/SmallNetwork			... communication across a small network
		/TwoCSs					... two directly connected CSs
		/TwoCSsSimple			... two directly connected CSs with only one IPC
		/TwoCSsWithDelay		... delayed channel testing scenario
		/SmallRandNet			... small randomly generated symmetric topology 
		/BigRandNet				... big randomly generated symmetric topology
		/FatTreeTopology		... scenario for testing D-V routing policy
	/src						... source codes' folder
		/Common					... shared basic classes
		/CS						... computing system simulation nodes
		/DAF					... DAF components
		/DIF 					... DIF components
		/policies				... all programable RINA policies
			/DAF				... policies related to DAF components
			/DIF 				... policies related to DIF components

