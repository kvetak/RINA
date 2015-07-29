RINA Simulator
====

###Version changelog

* May/June 2015 - Enrollment, (N-1)-data/management separation, MIT relicensing,
                  EFCPv4+ updates, separation of QoSCubes and QoS requirements,
                  change of QoSCube-id datatype, source code split between
                  policies and src, PDU headers for (N)-management frames,
                  multiple AEs within single AP communication 
* April 2015    - Routing policies prototypes, traceback packet file, CDAP redesign
* March 2015    - Slowdown/Pushupnotif congestion control, basic statistics,
                  flow lifecycle, AEStream/ExtendedPing
* February 2015 - After-Ghent release with FA policies
* January 2015  - Ghent meeting with EFCP, RMT, RA, PDUFTG and policies
* November 2014 - Brussels RV1 with AllNodes examples
* October 2014  - Madrid F2F meeting with working SimpleRelay and TwoCSs scenarios

###Links
* [OpenSourceProject Git with archived RINASim releases](https://opensourceprojects.eu/p/pristine/rinasimulator/rinasim/ci/b323f721944033c9f31924c02e2b67ba9c92c712/tree/)
* [VMWare Out-of-the-box virtual machine with RINASim](http://nes.fit.vutbr.cz/ivesely/vm/RINASim.zip)
* [PRISTINE webpage](http://ict-pristine.eu/)	 
* [Developer's mailing-list](https://www.fit.vutbr.cz/mailman/listinfo/rinasim)

###Directory structure

	/examples					... scenarios testing RINA stack
		/Basics					... simple testing scenarios
		/Congestion				... congestion control
		/Demos					... use-cases for tutorials and demo sessions
		/Routing				... routing in topologies
		
	/src						... source codes' folder
		/Common					... shared basic classes
		/CS						... computing system simulation nodes
		/DAF					... DAF components
		/DIF 					... DIF component
	
	/policies				    ... all programable RINA policies

###Available policies
	/DAF                           ... DAF policies
	/DIF                           ... DIF policies
	    /FA                        ... policies related to FA modules
	        /AllocateRetry             ... what happen when M_CREATE is resend by Flow Allocator
	            /LimitedRetries        ... when retransmit treshold is met, allocation is 
	            						   discontinued
	        /MultilevelQoS             ... when a flow request a new n-1 flow, how its requirements are 
	        							   mapped to n-1 requirements *not used yet
	        /NewFlowRequest            ... when new flow is being allocated, how are its 
	        							   requirements mapped to RA QoSCubes
	            /ScoreComparer         ... QoSCube with best score wins
	            /MinComparer           ... QoSCube with minimal feasibility wins
	    /RA                            ... policies related to RA modules
	        /AddressComparator         ... policy used for determining whether a PDU address
	        							   matches the IPCP's address  
	            /ExactMatch            ... exact matching
	            /PrefixMatch           ... matching based on address prefix
	        /PDUFG                     ... PDU Forwarding Generator providing data used by the 
	        							   PDU Forwarding policy 
	            /BiDomainGenerator     ... populates forwarding policy with entries on the form samePrefix.Id -> port and distinctPrefix.* -> port
	            /LatGenerator          ... inform of flow metrics to routing as latency (based on n-1 
	        							   QoS cube) instead of hops
	            /MSimpleGenerator      ... inform of flow metrics to routing as hops, populates forwarding
	        							   policy with all existing best next hops
	            /QoSDomainGenerator    ... populates forwarding policy with best next hop per dst + QoS
	            /SimpleGenerator       ... inform of flow metrics to routing as hops
	            /SingleDomainGenerator ... inform of flow metrics to routing as hops, 
	        							   variation using Domain based routing
	            /StaticGenerator       ... load forwarding information from XML configuration 
	        /QueueAlloc                ... (N-1)-port queue allocation strategy
	            /QueuePerNCU           ... one queue per (N)-Cherish/Urgency class
	            /QueuePerNFlow         ... one queue per (N)-flow 
	            /QueuePerNQoS          ... one queue per (N)-QoS cube
	            /SingleQueue           ... one queue for all
	        /QueueIDGen                ... companion policy to QueueAlloc; returns queue ID 
	        							   for given PDU or Flow object 
	            /IDPerNCU              ... used with QueueAlloc::QueuePerNCU
	            /IDPerNFlow            ... used with QueueAlloc::QueuePerNFlow
	            /IDPerNQoS             ... used with QueueAlloc::QueuePerNQoS
	            /SingleID              ... used with QueueAlloc::SingleQueue
	    /RMT                           ... policies related to RMT modules
	        /MaxQueue                  ... policy invoked when a queue size grows over its
	        							   threshold 
	            /DumbMaxQ              ... request drop probability to monitor, drop random on that.
	        							   used with "SmartMonitor"s 
	            /ECNMarker             ... if queue size >= threshold, apply ECN marking on 
	            						   new PDUs; if size >= max, drop
	            **/PortMaxQ              ...  to remove!!**
	            /ReadRateReducer       ... if queue size >= allowed maximum, stop receiving data
	            						   from input ports 
	            /REDDropper            ... used with Monitor::REDMonitor; Random Early Detection
	            					       implementation
	            /TailDrop              ... if queue size >= allowed maximum, drop new PDUs
	            /UpstreamNotifier      ... if queue size >= allowed maximum, send a notification 
	            						   to the PDU sender
	        /Monitor                   ... state-keeping policy invoked on various queue events 
	            /BEMonitor             ... Best-effort as SmartMonitor using multiple queues
	            /DLMonitor             ... Dela/Loss monitor implementation as SmartMonitor
	            /eDLMonitor            ... enhanced-Dela/Loss monitor implementation as SmartMonitor
	            /REDMonitor            ... used with MaxQueue::REDDropper; Random Early Detection 
	            					       implementation
	            /DummyMonitor          ... noop
	            /SmartMonitor          ... monitor interface for use with dumbMaxQ/dumbSch.
	        							   can be queried for drop probability and next queue
	        /PDUForwarding             ... policy used to decide where to forward a PDU
	            /DomainTabl            ... a table with {domain:{prefix, QoS} -> 
	        							   { Table:{dstAddr -> port}, default:port } }
	            /MiniTable             ... a table with {dstAddr -> port} mappings
	            /MultiMiniTable        ... a table with {dstAddr -> vectior<port>} mappings
	            /QoSTable              ... a table with {(dstAddr, QoS) -> port} mappings
	            /SimpleTable           ... a table with {(dstAddr, QoS) -> port} mappings
	        /Scheduler                 ... policy deciding which (N-1)-port queue should be 
	        							   processed next
	            /DumbSch               ... query the monitor for the next queue to serve.
	        							   used with "SmartMonitor"s
	            /LongestQFirst         ... pick the queue which contains the most PDUs 
	    /Routing                       ... routing policies
	        /DomainRouting	           ... routing policy based on domains. A domain is defined as a sub-set                                                    of the DIF, with its own metrics and routing algorithm.
	        	/DV	               ... simple distance vector algorithm for DomainRouting
	        	/LS                    ... simple link-state algorithm for DomainRouting
	        /DummyRouting              ... noop
	        /SimpleRouting
	            /SimpleDV              ... a simple distance vector-like protocol
	            /SimpleLS              ... a simple link-state-like protocol
	        
          
	
	
