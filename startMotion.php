<?php

    function runMotion(){ 
        exec( "/var/www/RaspberrySpi/start.sh"); 
    }



if (isset($_POST['motion'])) {
	runMotion();

}
else{
    echo "Somethings wrong";
}


?>
