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
		/DIF 					... DIF component
	
	/policies				... all programable RINA policies

###Policies
	/DAF                           ... DAF policies
	/DIF                           ... DIF policies
	    /FA                        ... policies related to FA modules
	        /AllocateRetry             ... what happen when M_CREATE is resend by Flow Allocator
	            /LimitedRetries        ... when retransmit treshold is met, allocation is discontinued
	        /NewFlowRequest            ... when new flow is being allocated, how are its requirements mapped to RA QoSCubes
	            /ScoreComparer         ... QoSCube with best score wins
	            /MinComparer           ... QoSCube with minimal feasibility wins
	    /RA                            ... policies related to RA modules
	        /AddressComparator         ... policy used for determining whether a PDU address matches the IPCP's address  
	            /ExactMatch            ... exact matching
	            /PrefixMatch           ... matching based on address prefix
	        /PDUFG                     ... PDU Forwarding Generator providing data used by the PDU Forwarding policy 
	            /BiDomainGenerator     
	            /QoSDomainGenerator    
	            /SimpleGenerator       
	            /SingleDomainGenerator 
	            /StaticGenerator       ... load forwarding information from XML configuration 
	        /QueueAlloc                ... (N-1)-port queue allocation strategy
	            /QueuePerNCU           
	            /QueuePerNFlow         ... one queue per (N)-flow 
	            /QueuePerNQoS          ... one queue per (N)-QoS cube
	            /SingleQueue           ... one queue for all
	        /QueueIDGen                ... companion policy to QueueAlloc; returns queue ID for given PDU or Flow object 
	            /IDPerNCU              ... used with QueueAlloc::QueuePerNCU
	            /IDPerNFlow            ... used with QueueAlloc::QueuePerNFlow
	            /IDPerNQoS             ... used with QueueAlloc::QueuePerNQoS
	            /SingleID              ... used with QueueAlloc::SingleQueue
	    /RMT                           ... policies related to RMT modules
	        /MaxQueue                  ... policy invoked when a queue size grows over its threshold 
	            /ECNMarker             ... if queue size >= threshold, apply ECN marking on new PDUs; if size >= max, drop
	            /PortMaxQ              
	            /ReadRateReducer       ... if queue size >= allowed maximum, stop receiving data from input ports 
	            /REDDropper            ... used with Monitor::REDMonitor; Random Early Detection implementation
	            /TailDrop              ... if queue size >= allowed maximum, drop new PDUs
	            /UpstreamNotifier      ... if queue size >= allowed maximum, send a notification to the PDU sender
	        /Monitor                   ... state-keeping policy invoked on various queue events 
	            /BEMonitor
	            /DLMonitor
	            /REDMonitor            ... used with MaxQueue::REDDropper; Random Early Detection implementation
	            /SimpleMonitor         ... noop
	            /SmartMonitor
	        /PDUForwarding             ... policy used to decide where to forward a PDU
	            /DomainTable
	            /MiniTable             ... a table with {dstAddr -> port} mappings
	            /QoSTable
	            /SimpleTable           ... a table with {(dstAddr, QoS) -> port} mappings
	        /Scheduler                 ... policy deciding which (N-1)-port queue should be processed next
	            /DL 
	            /LongestQFirst         ... pick the queue which contains the most PDUs 
	    /Routing                       ... routing policies
	        /DomainRouting
	        /DummyRouting              ... noop
	        /SimpleRouting
	            /SimpleDV              ... a simple distance vector-like protocol
	            /SimpleLS              ... a simple link-state-like protocol
	        
	           
	
	
