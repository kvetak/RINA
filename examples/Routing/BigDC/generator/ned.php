//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

<?php

class C {
	static $p;
	static $t;
	static $f;
	static $s;
	static $e;
	
	static $w;
	static $wt;
	static $wf;
	static $ws;
	static $we;
	
	static $mt;
	static $mf;
	static $ms;
	static $me;
	
	static function iniVals($p, $t, $f, $s, $e) {
		C::$p = $p;
		C::$t = $t;
		C::$f = $f;
		C::$s = $s;
		C::$e = $e;
		
		$tc = $p*($t+1)-1;
		$fc = $p*($f+1)-1;
		$sc = $f*($s+1)-1;
		$ec = $e*($f+1)-1;
		
		$mc = max($tc, $fc, $sc, $ec);
		C::$w = $mc * 60;
		C::$wt = C::$w/$tc;
		C::$wf = C::$w/$fc;
		C::$ws = C::$w/$sc;
		C::$we = C::$w/$ec;
		
		C::$mt = 45 + 30*$mc/$tc;
		C::$mf = 45 + 30*$mc/$fc;
		C::$ms = 45 + 30*$mc/$sc;
		C::$me = 45 + 30*$mc/$ec;
		
	}
	
	static function X() {
		return C::$w+60;
	}
	
	static function TX($i, $j) {
		return C::$mt+C::$wt*($i*(C::$t+1)+$j);
	}
	static function FX($i, $j) {
		return C::$mf+C::$wf*($i*(C::$f+1)+$j);
	}
	static function SX($i, $j) {
		return C::$ms+C::$ws*($i*(C::$s+1)+$j);
	}
	static function EX($i, $j) {
		return C::$me+C::$we*($i*(C::$f+1)+$j);
	}
}
C::iniVals($p, $t, $f, $s, $e);

?>


package rina.examples.Routing.BigDC;

import ned.DatarateChannel;
import rina.src.DAF.AE.AEData.AEData;
import rina.src.Other.FlowsListener.FlowListener;
import rina.src.Other.Infection.InfectedDCRouter;

network BigDC
{
    @display("bgb=<?= C::X();?>,500");
	submodules:
<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $t; $j++) {
?>
		T_<?=$i;?>_<?=$j;?>: InfectedDCRouter {
            @display("p=<?=C::TX($i,$j);?>,400");
        }
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $f; $j++) {
?>
		F_<?=$i;?>_<?=$j;?>: InfectedDCRouter {
            @display("p=<?=C::FX($i,$j);?>,300");
        }
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $f; $i++) {
		for($j = 0; $j < $s; $j++) {
?>
		S_<?=$i;?>_<?=$j;?>: InfectedDCRouter {
            @display("p=<?=C::SX($i,$j);?>,200");
        }
<?php
		}	
	}
?>

<?php
	for($i = 0; $i < $e; $i++) {
		for($j = 0; $j < $f; $j++) {
?>
		E_<?=$i;?>_<?=$j;?>: InfectedDCRouter {
            @display("p=<?=C::EX($i,$j);?>,100");
        }
<?php
		}	
	}
?>

        
        flowListener: FlowListener { @display("p=60,30");  }
       
    connections:
<?php
	for($i = 0; $i < $p; $i++) {
		for($j = 0; $j < $t; $j++) {
			for($k = 0; $k < $f; $k++) {
?>
		T_<?=$i;?>_<?=$j;?>.medium++ <--> TF_Link <-->  F_<?=$i;?>_<?=$k;?>.medium++;
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
		F_<?=$i;?>_<?=$j;?>.medium++ <--> FS_Link <-->  S_<?=$j;?>_<?=$k;?>.medium++;
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
		E_<?=$i;?>_<?=$j;?>.medium++ <--> ES_Link <-->  S_<?=$j;?>_<?=$k;?>.medium++;
<?php
			}
		}	
	}
?>

}


channel TF_Link extends DatarateChannel {
    parameters:
        datarate = 1Gbps;
        delay = 0;
        per = 0;
        ber = 0;
}

channel FS_Link extends DatarateChannel {
    parameters:
        datarate = 10Gbps;
        delay = 0;
        per = 0;
        ber = 0;
}

channel ES_Link extends DatarateChannel {
    parameters:
        datarate = 10Gbps;
        delay = 0;
        per = 0.00;
        ber = 0.0;
}

