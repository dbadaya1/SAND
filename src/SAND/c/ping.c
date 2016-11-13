/*****************************************************************************/
/*** myping.c                                                              ***/
/***                                                                       ***/
/*** Use the ICMP protocol to request "echo" from destination.             ***/
/*****************************************************************************/

//#include <resolv.h>
//#include <netinet/in.h>
//#include <errno.h>
#include<string.h>
#include<stdlib.h>
#include<strings.h>
#include<stdio.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>

#define PACKETSIZE	64

struct packet
{
    struct icmphdr hdr;
	char msg[PACKETSIZE-sizeof(struct icmphdr)];
};

int pid=-1;
struct protoent *proto=NULL;

/*--------------------------------------------------------------------*/
/*--- checksum - standard 1s complement checksum                   ---*/
/*--------------------------------------------------------------------*/
unsigned short checksum(void *b, int len)
{	unsigned short *buf = b;
	unsigned int sum=0;
	unsigned short result;

	for ( sum = 0; len > 1; len -= 2 )
		sum += *buf++;
	if ( len == 1 )
		sum += *(unsigned char*)buf;
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	result = ~sum;
	return result;
}

/*--------------------------------------------------------------------*/
/*--- display - present echo info                                  ---*/
/*--------------------------------------------------------------------*/
void display(void *buf, int bytes)
{	int i;
	struct iphdr *ip = buf;
	struct icmphdr *icmp = buf+ip->ihl*4;

	printf("----------------\n");
	printf("%d bytes received\n", bytes);
/*	for ( i = 0; i < bytes; i++ )
	{
		if ( !(i & 15) ) printf("\nX:%d  ", i);
		printf("X :%d", ((unsigned char*)buf)[i]);
	}*/
	printf("\n");
	printf("IPv%d: hdr-size=%d pkt-size=%d protocol=%d TTL=%d src=%-15s ",ip->version, ip->ihl*4, ntohs(ip->tot_len), ip->protocol,ip->ttl, inet_ntoa(*(struct in_addr *)&ip->saddr));
	printf("dst=%-15s\n", inet_ntoa(*(struct in_addr *)&ip->daddr));
	if ( icmp->un.echo.id == pid )
	{
		printf("ICMP: type[%d/%d] checksum[%d] id[%d] seq[%d]\n",
			icmp->type, icmp->code, ntohs(icmp->checksum),
			icmp->un.echo.id, icmp->un.echo.sequence);
	}
}

/*--------------------------------------------------------------------*/
/*--- listener - separate process to listen for and collect messages--*/
/*--------------------------------------------------------------------*/
void listener(void)
{	int sd;
	struct sockaddr_in addr;
	unsigned char buf[1024];

	sd = socket(PF_INET, SOCK_RAW, proto->p_proto);
	if ( sd < 0 )
	{
		perror("socket");
		exit(0);
	}
	while(1)
	{	int bytes, len=sizeof(addr);

		bzero(buf, sizeof(buf));
		bytes = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
		if ( bytes > 0 )
			display(buf, bytes);
		else
			perror("recvfrom");
	}
	exit(0);
}

/*--------------------------------------------------------------------*/
/*--- ping - Create message and send it.                           ---*/
/*--------------------------------------------------------------------*/
int ping(struct sockaddr_in *addr)
{	const int val=255;
	int i, j, sd, cnt=1;
	struct packet pckt;
	struct sockaddr_in r_addr;

	sd = socket(PF_INET, SOCK_RAW, proto->p_proto);
	if ( sd < 0 )
	{
		perror("socket");
		return;
	}
	if ( setsockopt(sd, SOL_IP, IP_TTL, &val, sizeof(val)) != 0)
		perror("Set TTL option");
	if ( fcntl(sd, F_SETFL, O_NONBLOCK) != 0 )
		perror("Request nonblocking I/O");

	
	if ( sendto(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)addr, sizeof(*addr)) <= 0 )
			perror("sendto");
	char * ad;
	for(j=0;j<3;j++)
	{
		int len=sizeof(r_addr);

		//printf("Msg #%d\n", cnt);
		if ( recvfrom(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)&r_addr, &len) > 0 )
		{	
			printf("%s ", inet_ntoa(addr->sin_addr));
			return 1;
		}
		bzero(&pckt, sizeof(pckt));
		pckt.hdr.type = ICMP_ECHO;
		pckt.hdr.un.echo.id = pid;
		for ( i = 0; i < sizeof(pckt.msg)-1; i++ )
			pckt.msg[i] = i+'0';
		pckt.msg[i] = 0;
		pckt.hdr.un.echo.sequence = cnt++;
		pckt.hdr.checksum = checksum(&pckt, sizeof(pckt));

		if ( sendto(sd, &pckt, sizeof(pckt), 0, (struct sockaddr*)addr, sizeof(*addr)) <= 0 )
			perror("sendto");

		usleep(500);

	}

	return 0;

	
}
/*--------------------------------------------------------------------*/
/*--- main - look up host and start ping processes.                ---*/
/*--------------------------------------------------------------------*/
int main(int count, char *strings[])
{	struct hostent *hname;
	struct sockaddr_in addr;
	int i;
	if ( count < 2 )
	{
		printf("usage: %s <addr> <addr>\n", strings[0]);
		exit(0);
	}

	for(i=1;i<count;i++)
	{
		if ( count > 1 )
		{
			pid = getpid();
			proto = getprotobyname("ICMP");
			hname = gethostbyname(strings[i]);
			bzero(&addr, sizeof(addr));
			addr.sin_family = hname->h_addrtype;
			addr.sin_port = 0;
			addr.sin_addr.s_addr = *(long*)hname->h_addr;
			ping(&addr);
/*			if ( fork() == 0 )
			{
				printf("In fork()==0\n");
				listener();
			}
			
			else
			{
				printf("Fork not 0");
				ping(&addr);
			}
			wait(0);
*/
		}
		else
			printf("usage: myping <hostname>\n");
	}
	return 0;
}

