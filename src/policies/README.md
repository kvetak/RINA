RINA Simulator Policies
====

###Version progress

* April 2015    - *****

###Policies
	/DAF					... DAF policies
	/DIF					... DIF policies
		/FA                     ... Policies related to FA modules
		    /AllocateRetry
		        /LimitedRetries
		    /NewFlowRequest
		        /NewFlowRequest
		/RA                     ... Policies related to RA modules
		    /AddressComparator
		        /ExactMatch
		        /PrefixMatch
		    /PDUFG
		        /BiDomainGenerator
		        /QoSDomainGenerator
		        /SimpleGenerator
		        /SingleDomainGenerator
		        /StaticGenerator
		    /QueueAlloc
		        /QueuePerNCU
		        /QueuePerNFlow
		        /QueuePerNQoS
		        /SingleQueue
		    /QueueIDGen
		        /IDPerNCU
		        /IDPerNFlow
		        /IDPerNQoS
		        /SingleID
		/RMT                    ... Policies related to RMT modules
		    /MaxQueue
		        /ECNMarker
		        /PortMaxQ
		        /ReadRateReducer
		        /REDDropper
		        /TailDrop
		        /UpstreamNotifier
		    /Monitor
		        /BEMonitor
		        /DLMonitor
		        /REDMonitor
		        /SimpleMonitor
		        /SmartMonitor
		    /PDUForwarding
		        /DomainTable
		        /MiniTable
		        /QoSTable
		        /SimpleTable
		    /Scheduler
		        /LongestQFirst
		        /DumbSch
		/Routing                ... Routing policies
		    /DomainRouting
		    /DummyRouting
		    /SimpleRouting
		    
