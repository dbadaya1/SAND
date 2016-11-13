#include "server.c"
#include "client.c"
#include <stdlib.h>



void test() {
			 system("cd /home/ubuntu/SAND/out;java SAND.java.Main");

}

void main() {
	pthread_t p1,p2,p3;
		pthread_create(&p1,NULL,server,NULL);
		//	sleep(2);

	//pthread_create(&p3,NULL,test,NULL);

			//initializeReadFIFO("/tmp/java");

//sleep(2);

	//sleep(5);
		pthread_create(&p2,NULL,client,NULL);

while(1);

}

