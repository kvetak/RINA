#RINA Simulator
====

###Version changelog
* February 2017 - Refactored examples, towards OMNeT++ 5.1 compatibility
* October 2016 - Socket and CDAP API added, compilable on OMNeT++ 5.0
* August 2016 - The last release compatible with OMNeT++ 4.6
* October 2015-February 2016 - Trento meeting version, Fragmentation/Concatenation in Delimiting, 
								DAF level Enrollment, scenario split
* July-September 2015 - RIBd notifiers, pre-EFCPv6 updates, CDAPProcessingBase interface,
						merging partner's contribution (namely routing and congestion control),
						added Hop Count to PDU header  
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

###Resources
* [RINASim official project webpage](http://rinasim.omnetpp.org)
* [VMWare Out-of-the-box virtual machine with RINASim](http://nes.fit.vutbr.cz/ivesely/vm/RINASim.zip)
* [Doxygen source code documentation](http://nes.fit.vutbr.cz/ivesely/doxy/)
* [Developer's mailing-list](https://www.fit.vutbr.cz/mailman/listinfo/rinasim)
* [Deliverable 2.4 describing RINASim January 2015 functionality](http://ict-pristine.eu/wp-content/uploads/2013/12/pristine-d24-rinasim-v1_0.pdf)
* [Deliverable 2.6 describing RINASim December 2015 functionality](http://ict-pristine.eu/wp-content/uploads/2013/12/pristine-d26-rina_sim-draft.pdf)
* [PRISTINE webpage](http://ict-pristine.eu/)	 
* [OpenSourceProject Git with archived RINASim releases](https://opensourceprojects.eu/p/pristine/rinasimulator/rinasim/)

###Papers

* VESELY, Vladimir. A NEW DAWN OF NAMING, ADDRESSING AND ROUTING ON THE INTERNET. Brno, 2016. Available from: http://www.fit.vutbr.cz/study/DP/PD.php?id=515. PhD. Thesis. Brno University of Technology, Faculty of Information Technology. 2016-04-12. Supervisor Sveda Miroslav.
* S. L. Gaixas, J. Perello, D. Careglio, E. Grasa, N. Davies and P. Thompson. Assuring Absolute QoS Guarantees for Heterogeneous Services in RINA Networks with delta-Q. IEEE NetCloud 2016, December 2016.
* E. Elahi, J. Barron, M. Crotty, M. Ponce de Leon, R. Mijumbi, S. Davy, D. Staessens and S. Vrijders. On Load Management in Service Oriented Networks. IEEE Cloudnet 2016, October 2016.
* P. Teymoori et al., Congestion control in the recursive InterNetworking Architecture (RINA), 2016 IEEE International Conference on Communications (ICC), Kuala Lumpur, 2016, pp. 1-7. doi: 10.1109/ICC.2016.7510818. Available from: http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7510818&isnumber=7510595
* F. Hrizi, A. Laouiti and H. Chaouchi, SFR: Scalable forwarding with RINA for distributed clouds, Network of the Future (NOF), 2015 6th International Conference on the, Montreal, QC, 2015, pp. 1-6. doi: 10.1109/NOF.2015.7333311. Available from: http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=7333311&isnumber=7333276
* VESELY Vladimir, MAREK Marcel, HYKEL TomaS, RYSAVY Ondrej, LICHTNER Ondrej and JERABEK Kamil. Deliverable 2.6: RINASim - advanced functionality. Brno, 2015. Available from: http://ict-pristine.eu/wp-content/uploads/2013/12/pristine-d26-rina_sim-draft.pdf.
* VESELY Vladimir, MAREK Marcel, HYKEL Tomas and RYSAVY Ondrej. Skip This Paper - RINASim: Your Recursive InterNetwork Architecture Simulator. In: Proceedings of 2nd OMNeT++ Community Summit. Ithaca, NY: Cornell University Library, 2015, pp. 1-4. ISSN 2331-8422. Available from: https://arxiv.org/abs/1509.03550
* VESELY Vladimir, MAREK Marcel, HYKEL TomaS, RYSAVY Ondrej and LICHTNER Ondrej. Deliverable 2.4: RINASim - basic functionality. Brno, 2015. Available from: http://ict-pristine.eu/wp-content/uploads/2013/12/pristine-d24-rinasim-v1_0.pdf

###Directory structure

	/examples					... scenarios testing RINA stack
		/Basics					... simple testing scenarios
		/Congestion				... congestion control
		/Demos					... use-cases for tutorials and demo sessions
		/LB						... load-balancing
		/Routing				... routing in topologies
		
	/playground					... unsupported/obsolete scenarios
		
	/src						... source codes' folder
		/Common					... shared basic classes
		/CS						... computing system simulation nodes
		/DAF					... DAF components
		/DIF 					... DIF component
		/Other					... non-essential user-requested core components
	
	/policies				    ... all programable RINA policies
	
	/scripts
		fingerprints.sh			... batch for checking/updating fingerprints
		slocstats.sh			... counts source lines of code

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
	        /DomainRouting	           ... routing policy based on domains. A domain is defined as a sub-set
	        							   of the DIF, with its own metrics and routing algorithm.
	        	/DV                    ... simple distance vector algorithm for DomainRouting
	        	/LS                    ... simple link-state algorithm for DomainRouting
	        /DummyRouting              ... noop
	        /SimpleRouting
	            /SimpleDV              ... a simple distance vector-like protocol
	            /SimpleLS              ... a simple link-state-like protocol
	        
          
	
	
