// ...

/**
 *	TCP from client side
 *	socket() -> connect() -> read() -> write()
 */

#include "common.h"
#include "readFIFO.c"

#define SERVER "127.0.0.1"


int client () {
			 			initializeReadFIFO("/tmp/java");
	
	sockaddr_in_t server_address;
	
	int sockfd, i;
	socklen_t slen = sizeof(server_address);
	
	int *pid = (int *)malloc(BUFLEN);
	
	// create a UDP server
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		commit_suicide("socket()");
	}
	// zero out the structure
	memset((char *)&server_address, 0, slen);
	
	// set family and port
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr(SERVER);
	
	// get address
	if (connect(sockfd, (sockaddr_p_t)&server_address, slen) < 0) {
		commit_suicide("connect()");
	}

	while(1) {

	//printf("Enter the number: ");
	//scanf(" %d", input);
		char * result = readFIFO();
	//if(result != NULL) {
	// try sending some data to the server
	if (write(sockfd, result, BUFLEN) < -1) {
		commit_suicide("write()");
	}
	printf("Sending TCP %s \n",result);
//	}

	sleep(1);
	

	}
	close(sockfd);

	return 0;
}

