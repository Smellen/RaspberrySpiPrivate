<?php

function runMotion(){ 
	exec( "/var/www/RaspberrySpi/stop.sh"); 
}


if (isset($_POST['motion'])) {

	runMotion();

}
else{
	echo "Somethings wrong";
}

?>
