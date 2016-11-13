#include<stdio.h> //printf
#include<string.h>    //strlen
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<stdlib.h>
#define BUF_SIZE 2000 
void * receiveMessage(void * socket) {
 int sockfd, ret;
 char buffer[BUF_SIZE]; 
 sockfd = (int) socket;
 memset(buffer, 0, BUF_SIZE);  
 for (;;) {
  ret = recvfrom(sockfd, buffer, BUF_SIZE, 0, NULL, NULL); 
  if(ret == 0)
  {
    printf("Server disconnected\n");
    fflush(stdout);
    return;  

  } 
  if (ret < 0) {  
   printf("Error receiving data!\n"); 
    return;
   
  } else {
   printf("server: ");
   fputs(buffer, stdout);
   //printf("\n");
  }  
 }
}

int main(int argc , char *argv[])
{
    int sock,ret;
    struct sockaddr_in server;
    char message[1000] , server_reply[2000];
    pthread_t rThread;

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    server.sin_addr.s_addr = inet_addr("10.52.3.111");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8898 );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    puts("Connected\n");
    puts("Bienvenido al Chatroom, puedes empezar a escribir en la sala!");

    printf("Enter message: ");
    fgets(message, sizeof(message),stdin);
        //scanf("%s" , message);

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

    //keep communicating with server
    while(1)
    {
        //Receive a reply from the server
        /*if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
           break;
        }*/



        ret = pthread_create(&rThread, NULL, receiveMessage, (void *) sock);
         if (ret) {
          printf("ERROR: Return Code from pthread_create() is %d\n", ret);
          exit(1);
         }




        //printf("Server Reply: %s\n", server_reply);

        printf("Enter message: ");
        fgets(message, sizeof(message),stdin);
        //scanf("%s" , message);

        //Send some data
        if( send(sock , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
   
        //server_reply[0]='\0'; 
    }

    close(sock);
    return 0;
}
