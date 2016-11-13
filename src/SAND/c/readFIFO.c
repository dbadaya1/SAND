#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jni.h> 
#include <stdio.h> 
#include "../../../out/SAND_java_ReadFIFO.h"   

#define MAX_BUF 1024

char * myfifo1;
int fd1;
char buf[MAX_BUF];


void initializeReadFIFO(char * fileName) {
	myfifo1 = fileName;
while((fd1 = open(myfifo1, O_RDONLY)) <= 0 ) {
	//perror("Open ReadFIFO:");
	sleep(1);
	//printf("here \n");
}
}

char * readFIFO() {
memset(buf,'\0',MAX_BUF);
int l;
	while(!(l = read(fd1, buf, MAX_BUF))){
		sleep(1);
	}
	//printf("read length %d \n",l);
//fd = open(myfifo, O_RDONLY);
	//read(fd, buf, MAX_BUF);
	 //  perror("Read:"); //Very crude error check
//close(fd);
	printf("\n Reading FIFO: %s \n", buf);
    return buf;
}

void closeReadFIFO() {
	unlink(myfifo1);
}



JNIEXPORT void JNICALL Java_SAND_java_ReadFIFO_initializeReadFIFO(JNIEnv *env, jobject obj,jstring fileName)  {
const char *nativeString = (*env)->GetStringUTFChars(env, fileName, 0);
	initializeReadFIFO(nativeString);
}

JNIEXPORT jstring JNICALL Java_SAND_java_ReadFIFO_readFIFO(JNIEnv *env, jobject obj)  {
	readFIFO();
	jstring message = (*env)->NewStringUTF(env, buf);
    return message;
}


JNIEXPORT void JNICALL Java_SAND_java_ReadFIFO_closeReadFIFO(JNIEnv *env, jobject obj)  {
	closeReadFIFO();
}





