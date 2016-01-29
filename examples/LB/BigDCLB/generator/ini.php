[General]
network = BigDC
**.pduTracing = false
**.scalar-recording = false
**.vector-recording = false

seed-set = ${runnumber}

#DIF Allocator settings
**.difAllocator.directory.configData = xmldoc("directory.xml", "DA")

#Shim-Flows allocation
**.ra.preallocation = xmldoc("connectionset.xml", "ConnectionSet")
**.flowAllocator.newFlowReqPolicyType = "MinComparer"
**.isSelfEnrolled = true

##---Backbone---

#QoS settings
**.relayIpc.**.ra.qoscubesData = xmldoc("qoscube.xml", "QoSCubesSet")
**.relayIpc.**.ra.qosReqData = xmldoc("qosreq.xml", "QoSReqSet")

**.ipcProcess[*].**.ra.qoscubesData = xmldoc("qoscube.xml", "QoSCubesSet")
**.ipcProcess[*].**.ra.qosReqData = xmldoc("qosreq.xml", "QoSReqSet")


#DC DIF
**.relayIpc.difName = "DC"

<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $t; $j++) {
?>
**.T_<?=$i;?>_<?=$j;?>.relayIpc.ipcAddress = "0.<?=$i;?>.<?=$j;?>"
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $f; $j++) {
?>
**.F_<?=$i;?>_<?=$j;?>.relayIpc.ipcAddress = "1.<?=$i;?>.<?=$j;?>"
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $f; $i++) {
		for($j = 0; $j < $s; $j++) {
?>
**.S_<?=$i;?>_<?=$j;?>.relayIpc.ipcAddress = "2.<?=$i;?>.<?=$j;?>"
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $e; $i++) {
		for($j = 0; $j < $f; $j++) {
?>
**.E_<?=$i;?>_<?=$j;?>.relayIpc.ipcAddress = "3.<?=$i;?>.<?=$j;?>"
<?php
		}	
	}
?>



#shim DIF

**.T_**.ipcProcess[*].ipcAddress = "0"
**.F_**.ipcProcess[*].ipcAddress = "1"
**.S_**.ipcProcess[*].ipcAddress = "2"
**.E_**.ipcProcess[*].ipcAddress = "3"

<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $t; $j++) {
			for($k = 0; $k < $f; $k++) {
?>
**.T_<?=$i;?>_<?=$j;?>.ipcProcess[<?= $k;?>].difName = "tf<?=$i;?>.<?=$j;?>.<?=$k;?>"
<?php
			}
		}	
	}
?>


<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $f; $j++) {
			for($k = 0; $k < $t; $k++) {
?>
**.F_<?=$i;?>_<?=$j;?>.ipcProcess[<?= $k;?>].difName = "tf<?=$i;?>.<?=$k;?>.<?=$j;?>"
<?php
			}
			
			for($k = 0; $k < $s; $k++) {
?>
**.F_<?=$i;?>_<?=$j;?>.ipcProcess[<?= $k+$t;?>].difName = "fs<?=$i;?>.<?=$j;?>.<?=$k;?>"
<?php
			}
		}	
	}
?>

<?php
	for($i = 0; $i < $e; $i++) {
		for($j = 0; $j < $f; $j++) {
			for($k = 0; $k < $s; $k++) {
?>
**.E_<?=$i;?>_<?=$j;?>.ipcProcess[<?= $k;?>].difName = "es<?=$i;?>.<?=$j;?>.<?=$k;?>"
<?php
			}
		}	
	}
?>

<?php
	for($i = 0; $i < $f; $i++) {
		for($j = 0; $j < $s; $j++) {
			for($k = 0; $k < $p; $k++) {
?>
**.S_<?=$i;?>_<?=$j;?>.ipcProcess[<?= $k;?>].difName = "fs<?=$k;?>.<?=$i;?>.<?=$j;?>"
<?php
			}
			
			for($k = 0; $k < $e; $k++) {
?>
**.S_<?=$i;?>_<?=$j;?>.ipcProcess[<?= $k+$p;?>].difName = "es<?=$k;?>.<?=$i;?>.<?=$j;?>"
<?php
			}
		}	
	}
?>



**.defaultThreshQLength = 0
**.defaultMaxQLength =  10

**.efcp.maxPDUSize = 100000B
**.efcp.maxSDUSize = 100000B


**.ipcProcess[*].**.queueAllocPolicyName = "QueuePerNFlow"
**.ipcProcess[*].**.queueIdGenName = "IDPerNFlow"

**.ipcProcess[*].relayAndMux.maxQPolicyName = "TailDrop"
**.ipcProcess[*].relayAndMux.qMonitorPolicyName = "IterativeStopMonitor"
**.ipcProcess[*].relayAndMux.schedPolicyName = "IterativeScheduling"


**.relayIpc.**.queueAllocPolicyName = "QueuePerNQoS"
**.relayIpc.**.queueIdGenName = "IDPerNQoS"

**.relayIpc.relayAndMux.maxQPolicyName = "DumbMaxQ"
**.relayIpc.relayAndMux.qMonitorPolicyName = "ModularMonitor"
**.relayIpc.relayAndMux.schedPolicyName = "DumbSch"
**.relayIpc.relayAndMux.queueMonitorPolicy.outputOutSubModule_Type = "MM_DL_Out"
**.relayIpc.relayAndMux.queueMonitorPolicy.outputOutSubModule.data = xmldoc("modules.xml", "Configuration/DLOUT")

**.relayIpc.relayAndMux.queueMonitorPolicy.outputDropSubModule_Type = "MM_DQ_Drop"
**.relayIpc.relayAndMux.queueMonitorPolicy.outputDropSubModule.data = xmldoc("modules.xml", "Configuration/DQQueueDrop")

**.infection.pods = <?= $p; ?> 
**.infection.torXpod = <?= $t; ?> 
**.infection.fabricXpod = <?= $f; ?> 
**.infection.spineXfabric = <?= $s; ?> 
**.infection.edgeSets = <?= $e; ?> 

**.infection.qosId = "BE"

**.infection.iniTime = 100
**.infection.interTime = 1
**.infection.loop = 1
**.infection.toTors = true
**.infection.toFabric = true
**.infection.toSpines = true
**.infection.toEdges = true

**.flowListener.killCount = 5
**.flowListener.killTime = 50

[Config SimpleTable]

#Routing settings
**.relayIpc.resourceAllocator.pdufgPolicyName = "SimpleHopMEntries"
**.relayIpc.resourceAllocator.pduFwdGenerator.infinite = 32

**.relayIpc.relayAndMux.ForwardingPolicyName = "MultiMiniTable"

**.relayIpc.routingPolicyName = "TSimpleDV"



[Config DCForwarding]

#Routing settings
**.relayIpc.resourceAllocator.pdufgPolicyName = "SimpleDCGenerator"
**.relayIpc.resourceAllocator.pduFwdGenerator.infinite = 32

**.T**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleTORForwarding"
**.F**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleFabricForwarding"
**.S**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleSpineForwarding"
**.E**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleEdgeForwarding"

**.T**.relayIpc.relayAndMux.pduForwardingPolicy.upCount = <?= $f; ?> 
**.F**.relayIpc.relayAndMux.pduForwardingPolicy.upCount = <?= $s; ?> 
**.F**.relayIpc.relayAndMux.pduForwardingPolicy.downCount = <?= $t; ?> 
**.S**.relayIpc.relayAndMux.pduForwardingPolicy.upCount = <?= $e; ?> 
**.S**.relayIpc.relayAndMux.pduForwardingPolicy.downCount = <?= $p; ?>  
**.E**.relayIpc.relayAndMux.pduForwardingPolicy.downCount = <?= $s; ?> 

**.relayIpc.routingPolicyName = "TSimpleDV"



[Config MDCRouting]

#Routing settings
**.relayIpc.resourceAllocator.pdufgPolicyName = "VoidDCGenerator"
**.relayIpc.resourceAllocator.pduFwdGenerator.infinite = 32

**.T**.relayIpc.routingPolicyName = "TOR_Routing"
**.F**.relayIpc.routingPolicyName = "Fabric_Routing"
**.S**.relayIpc.routingPolicyName = "Spine_Routing"
**.E**.relayIpc.routingPolicyName = "Edge_Routing"

**.T**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleTORForwarding"
**.F**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleFabricForwarding"
**.S**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleSpineForwarding"
**.E**.relayIpc.relayAndMux.ForwardingPolicyName = "SimpleEdgeForwarding"

**.T**.relayIpc.relayAndMux.pduForwardingPolicy.upCount = <?= $f; ?> 
**.F**.relayIpc.relayAndMux.pduForwardingPolicy.upCount = <?= $s; ?> 
**.F**.relayIpc.relayAndMux.pduForwardingPolicy.downCount = <?= $t; ?> 
**.S**.relayIpc.relayAndMux.pduForwardingPolicy.upCount = <?= $e; ?> 
**.S**.relayIpc.relayAndMux.pduForwardingPolicy.downCount = <?= $p; ?> 
**.E**.relayIpc.relayAndMux.pduForwardingPolicy.downCount = <?= $s; ?> 

**.relayIpc.routingPolicy.pods = <?= $p; ?> 
**.relayIpc.routingPolicy.torXpod = <?= $t; ?> 
**.relayIpc.routingPolicy.fabricXpod = <?= $f; ?> 
**.relayIpc.routingPolicy.spineXfabric = <?= $s; ?> 
**.relayIpc.routingPolicy.edgeSets = <?= $e; ?> 
