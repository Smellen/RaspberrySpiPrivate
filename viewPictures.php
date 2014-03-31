<html>
<head>
<meta http-equiv="Content-Type" content="text/html">
<title> All currently saved motion pictures</title>
<link href="css/main.css" rel="stylesheet" type="text/css">
<link rel="shortcut icon" href="raspberrySpi.ico">
<link rel="apple-touch-icon" href="raspberrySpi.ico">

</head>
<body>
<div id="wrap">
    <div class="logo">
        <img src="img/raspberrySPY.png" alt="Raspberry SPY" />
    </div>

<form action="index.html">
<input type ="submit" value="   &larr;   " style = "position: absolute; left: 500px; top: 100px;">
</form>




	<h2>Images captured during motion detection</h2> 
<?php
$picFolder = 'photos/motionPictures/';
$PNG = '*.png*';
$photos = glob($picFolder.$PNG);
$count = count($photos);
echo '<table>';
for ($index = 0; $index < $count; $index++) {
    echo '<tr><td>';
    echo '<a name="'.$index.'"><img src="'.$photos[$index].'" /></a>';
    //echo substr($photos[$index],strlen($picFolder),strpos($photos[$index], '.')-strlen($picFolder));
    echo $photos[$index];
	echo '</td></tr>';
}
echo '</table>';
?>

<div id="footer">
        <p> <a href="/help.html">Help Page</a> </p>
<div>

