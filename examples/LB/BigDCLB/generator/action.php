<?php
$type = -1;
$download = false;

if(isset($_GET['show'])) {
	$type = $_GET['show'];
} else if(isset($_GET['download'])) {
	$type = $_GET['download'];
	$download = true;
}


$p = 1;
$t = 1;
$f = 1;
$s = 1;
$e = 0;

if(isset($_GET['pods']) 
   && filter_input(INPUT_GET, 'pods', FILTER_VALIDATE_INT)  !== false
   && $_GET['pods'] >= 1) {
	$p = $_GET['pods'];
} else { $type = -1; }
if(isset($_GET['tors']) 
   && filter_input(INPUT_GET, 'tors', FILTER_VALIDATE_INT) !== false
   && $_GET['tors'] >= 1) {
	$t = $_GET['tors'];
} else { $type = -1; }
if(isset($_GET['fabrics']) 
   && filter_input(INPUT_GET, 'fabrics', FILTER_VALIDATE_INT) !== false
   && $_GET['fabrics'] >= 1) {
	$f = $_GET['fabrics'];
} else { $type = -1; }
if(isset($_GET['spines']) 
   && filter_input(INPUT_GET, 'spines', FILTER_VALIDATE_INT) !== false
   && $_GET['spines'] >= 1) {
	$s = $_GET['spines'];
} else { $type = -1; }
if(isset($_GET['edges']) 
   && filter_input(INPUT_GET, 'edges', FILTER_VALIDATE_INT) !== false
   && $_GET['edges'] >= 0) {
	$e = $_GET['edges'];
} else { $type = -1; }

switch($type) {
	case 'NED':
		header('Content-Type: text/ned');
		if($download) {
			header('Content-disposition: attachment; filename="BigDC.ned"');
		}
		include 'ned.php';
		break;
	case 'INI':
		header('Content-Type: text/ini');
		if($download) {
			header('Content-disposition: attachment; filename="omnetpp.ini"');
		}
		include 'ini.php';
		break;
	case 'Connections':
		header('Content-Type: text/xml');
		if($download) {
			header('Content-disposition: attachment; filename="connectionset.xml"');
		}
		include 'connections.php';
		break;
		
	case 'Directory':
		header('Content-Type: text/xml');
		if($download) {
			header('Content-disposition: attachment; filename="directory.xml"');
		}
		include 'directory.php';
		break;
	default:
		echo 'Incorrect Input';
}

?>
