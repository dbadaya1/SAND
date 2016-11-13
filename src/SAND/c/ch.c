#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include <string.h> /* memset */
#include <unistd.h> /* close */

//#include<readFIFO.c>


#define PORT 4567
#define BUF_SIZE 2000
#define CLADDR_LEN 100

void receiveChat(int sockfd,int connfd)
{

printf("in receive chat %d\n",getpid());
	//close(sockfd);
	char *buf;
	memset(buf,'\0',sizeof(buf));
	//read(connfd,buf,sizeof(buf));
	recvfrom(connfd, buf, sizeof(buf), 0, NULL, NULL); 
	
	//if(sizeof(buf)!=8)
	printf("\nWriting in fifo: %s", buf);
	//writeFIFO(buf);
}

void *connectServer()
{
printf("Inside connectserver\n");

	struct sockaddr_in addr, cl_addr;
 int sockfd, len, ret, newsockfd;
 char buffer[BUF_SIZE];
 pid_t childpid;
 char clientAddr[CLADDR_LEN];
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
  printf("Error creating socket!\n");
  exit(1);
 }
 printf("Socket created...\n");
 
 //memset(addr, 0, sizeof(addr));
 addr.sin_family = AF_INET;
 addr.sin_addr.s_addr = INADDR_ANY;
 addr.sin_port = PORT;
 
 ret = bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
 if (ret < 0) {
  printf("Error binding!\n");
  exit(1);
 }
 printf("Binding done...\n");

 printf("Waiting for a connection...\n");
 listen(sockfd, 5);


 len = sizeof(cl_addr);
 while(newsockfd = accept(sockfd, (struct sockaddr *) &cl_addr, &len))
 {
    if (newsockfd < 0) {
    printf("Error accepting connection!\n");
    exit(1);
   } 

   inet_ntop(AF_INET, &(cl_addr.sin_addr), clientAddr, CLADDR_LEN);
   printf("Connection accepted from %s...\n", clientAddr); 
   
   memset(buffer, '\0', sizeof(buffer));
	
	
	
	
	
	
	printf("gfg %d \n",getpid());
	if(fork()==0)	
	
	
	
	   for(;;)
	   {

	   	receiveChat(sockfd,newsockfd);
	   	
	   }
	   
   }
	
}






void sendChat(int sockfd, int ret, struct sockaddr_in cl_addr)//,char * buf)
{
	//close(sockfd);
	char *buf;
	printf("\nSend chat: ");
	scanf(" %s", buf);
	//write(ret, buf, sizeof(buf));
	int len = sizeof(cl_addr);
	sendto(ret, buf, sizeof(buf), 0, (struct sockaddr *) &cl_addr, len);
		
}

void *connectClient(void * ip1)
{
char* ip = (char*)ip1;
printf("IP inside client: %s\n", ip);
	struct sockaddr_in addr, cl_addr;  
 int sockfd, ret;  
 char buffer[BUF_SIZE]; 
 char * serverAddr;
 pthread_t rThread;	//call the file reading thread

 
 serverAddr = ip; 
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);  
 if (sockfd < 0) {  
  printf("Error creating socket!\n");  
  exit(1);  
 }  
 printf("Socket created...\n");   

 //memset(&addr, 0, sizeof(addr));  
 addr.sin_family = AF_INET;  
 addr.sin_addr.s_addr = inet_addr(serverAddr);
 addr.sin_port = PORT;     

 ret = connect(sockfd, (struct sockaddr *) &addr, sizeof(addr));  
 if (ret < 0) {  
  printf("Error connecting to the server!\n");  
  exit(1);  
 }  
 char *fromFIFO;
 printf("Connected to the server...\n");  
 for(;;)
 {
 	//fromFIFO=readFIFO();
  	sendChat(sockfd,ret, cl_addr);//,fromFIFO);
 }

//memset(buffer, 0, sizeof(buffer));

}




int main()
{

char* ip="127.0.0.1";
pthread_t server, client;
printf("Before\n");
pthread_create(&server, NULL, connectServer, NULL);
printf("Server thread created\n");
pthread_create(&client, NULL, connectClient, (void *)ip);
printf("Client thread created\n");

while(1);

/*
pid_t pid;
for(;;)
{
	int connfd=accept(fd,(struct sockaddr *) &cadd,&cli_len);
	if(pid=fork()==0)
	{
		close(fd);
		read(connfd,&num,sizeof(int));
		printf("%d",num);
		int r=num*num;
		write(connfd,&r,sizeof(int));
		close(connfd);
		exit(0);
	}
	close(connfd);
}
*/
return 0;
}
