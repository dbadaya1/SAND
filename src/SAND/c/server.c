// ...

/**
 *	TCP server side:
 *	socket() -> bind() -> listen() -> accept() -> read() -> write()
 */

#include "common.h"
#include "writeFIFO.c"
#include <stdio.h>



int server() {
		initializeWriteFIFO("/tmp/c");

char * delimiter = ";";
	
	sockaddr_in_t server_address, client_address;

	int sockfd, nsckfd = -1, i;
	socklen_t clen = sizeof(server_address);

	char *input = (char *)malloc(sizeof(char) * BUFLEN);
	int *pid = (int *)malloc(BUFLEN);

	int received_length;

	// create a UDP Server
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		commit_suicide("socket()");
	}
	// zero out the structure
	memset((char *)&server_address, 0, clen);

	// set family, address and port
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind socket to port
	if (bind(sockfd, (sockaddr_p_t)&server_address, clen) < 0) {
		commit_suicide("bind()");
	}

	// listen
	if (listen(sockfd, 6) < 0) {
		commit_suicide("listen()");
	}

	while (YES) {
		
		printf("Server [%s:%d] waiting...\n", inet_ntoa(server_address.sin_addr), ntohs(server_address.sin_port));

		
		// blocking call; try to get some data from the client?
		if ((nsckfd = accept(sockfd, (sockaddr_p_t)&client_address, &clen)) < 0) {
			commit_suicide("accept()");
		}

		*pid = fork();
		if (*pid == 0) {

			close(sockfd);
			while(1) {

			// read into buffer
			if ((received_length = read(nsckfd, input, BUFLEN)) < 0) {
				commit_suicide("read()"); // Some error here?
			}

			printf("Remote Host : %s \n", input);
    strcat(input,delimiter);
    strcat(input,inet_ntoa(client_address.sin_addr));
		//writeFIFO(input);

		}

			close(nsckfd);
			exit(0);

		} else if (*pid < 0) {
			commit_suicide("fork()");
		} else {
			close(nsckfd);
		}

	}

	close(nsckfd);
	close(sockfd);
	//closeWriteFIFO();

	return 0;
}