RINA Simulator
====

###Version progress

* April 2015    - Routing policies prototypes, traceback packet file, CDAP redesign
* March 2015    - Slowdown/Pushupnotif congestion control, basic statistics,
			      flow lifecycle, AEStream/ExtendedPing
* February 2015 - After-Ghent release with FA policies
* January 2015  - Ghent meeting with EFCP, RMT, RA, PDUFTG and policies
* November 2014 - Brussels RV1 with AllNodes examples
* October 2014  - Madrid F2F meeting with working SimpleRelay and TwoCSs scenarios

###Directory structure

	/examples					... scenarios testing RINA stack
		/AllNodes				... communication across all types of devices
		/BigRandNet				... big network for testing distance-vector routing
		/ExtendedPingTwoCs		... CACE module testing scenario distance-vector routing		
		/FatTreeTopology		... DC-like environment for testing distance-vector routing
		/SimpleRelay			... two CSs exchanging data through an interior router
		/SimpleRelayCongestion	... same scenario as above demonstrating congestion control
		/SingleCS				... single computing system with two applications		
		/SmallNetwork			... communication across a small network
		/SmallNetworkRouting	... same as above for testing distance-vector routing
		/SmallRandNetwork		... small randomly generated network
		/TwoCSs					... two directly connected CSs
		/TwoCSsSimple			... two directly connected CSs with only one IPC
		/TwoCSsWithDelay		... delayed channel testing scenario
	/src						... source codes' folder
		/Common					... shared basic classes
		/CS						... computing system simulation nodes
		/DAF					... DAF components
		/DIF 					... DIF components
		/policies				... all programable RINA policies
			/DAF				... policies related to DAF components
			/DIF 				... policies related to DIF components


