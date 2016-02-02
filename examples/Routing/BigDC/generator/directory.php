<?= '<?xml version="1.0"?>' ?> 

<DA>
	<Directory>
<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $t; $j++) {
?>
		<APN apn="0.<?= $i;?>.<?= $j;?>_DC">
<?php
			for($k = 0; $k < $f; $k++) {
?>
			<DIF difName="tf<?=$i;?>.<?=$j;?>.<?=$k;?>" ipcAddress="0" />
<?php
			}
?>
		</APN>
<?php
		}	
	}
?>


<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $f; $j++) {
?>
		<APN apn="1.<?= $i;?>.<?= $j;?>_DC">
<?php
			for($k = 0; $k < $t; $k++) {
?>
			<DIF difName="tf<?=$i;?>.<?=$k;?>.<?=$j;?>" ipcAddress="1" />
<?php
			}
			
			for($k = 0; $k < $s; $k++) {
?>
			<DIF difName="fs<?=$i;?>.<?=$j;?>.<?=$k;?>" ipcAddress="1" />
<?php
			}
?>
		</APN>
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $e; $i++) {
		for($j = 0; $j < $f; $j++) {
?>
		<APN apn="3.<?= $i;?>.<?= $j;?>_DC">
<?php
			for($k = 0; $k < $s; $k++) {
?>
			<DIF difName="es<?=$i;?>.<?=$j;?>.<?=$k;?>" ipcAddress="3" />
<?php
			}
?>
		</APN>
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $f; $i++) {
		for($j = 0; $j < $s; $j++) {
?>
		<APN apn="2.<?= $i;?>.<?= $j;?>_DC">
<?php
			for($k = 0; $k < $p; $k++) {
?>
			<DIF difName="fs<?=$k;?>.<?=$i;?>.<?=$j;?>" ipcAddress="2" />
<?php
			}
			
			for($k = 0; $k < $e; $k++) {
?>
			<DIF difName="es<?=$k;?>.<?=$i;?>.<?=$j;?>" ipcAddress="2" />
<?php
			}
?>
		</APN>
<?php
		}	
	}
?>
	</Directory>
</DA>