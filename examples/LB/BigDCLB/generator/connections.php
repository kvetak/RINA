<?= '<?xml version="1.0"?>' ?> 
<ConnectionSet>
	<!-- Allocate N-1 flows. -->
	<SimTime t="0">
<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $t; $j++) {
			for($k = 0; $k < $f; $k++) {
?>
		<Connection src="0.<?=$i;?>.<?=$j;?>_DC" dst="1.<?=$i;?>.<?=$k;?>_DC" qosReq="1"/>
<?php
			}
		}	
	}
?>

<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $f; $j++) {
			for($k = 0; $k < $s; $k++) {
?>
		<Connection src="1.<?=$i;?>.<?=$j;?>_DC" dst="2.<?=$j;?>.<?=$k;?>_DC" qosReq="1"/>
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
		<Connection src="3.<?=$i;?>.<?=$j;?>_DC" dst="2.<?=$j;?>.<?=$k;?>_DC" qosReq="1"/>
<?php
			}
		}	
	}
?>
	</SimTime>
</ConnectionSet>