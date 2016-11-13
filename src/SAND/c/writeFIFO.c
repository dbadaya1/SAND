#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <jni.h> 
#include <stdio.h> 
#include "../../../out/SAND_java_WriteFIFO.h"   

char * myfifo;



void initializeWriteFIFO(char * fileName) {
	myfifo = fileName;
	if(mkfifo(myfifo, 0666) < 0){
		//perror("MKFIFO Write: ");
	}
}

void writeFIFO(char * message) {
	//printf("start \n");
	//int fd = open(myfifo, O_WRONLY);
	int fd;
	while((fd = open(myfifo, O_WRONLY)) <= 0 ) {
	//perror("Open WriteFIFO:");
	sleep(1);
}
//("here1 \n");
		//perror("Open writeFIFO :");

	if(write(fd, message, strlen(message)) < 0)
		//perror("Write:");


	//	perror("Write:");


	printf("Writing FIFO %s \n",message);
	close(fd);

}

void closeWriteFIFO() {
	unlink(myfifo);
}


JNIEXPORT void JNICALL  Java_SAND_java_WriteFIFO_initializeWriteFIFO(JNIEnv *env, jobject obj,jstring fileName)  {
 const char *nativeString = (*env)->GetStringUTFChars(env, fileName, 0);
	initializeWriteFIFO(nativeString);
}

JNIEXPORT void JNICALL   Java_SAND_java_WriteFIFO_writeFIFO(JNIEnv *env, jobject obj,jstring message)  {
   const char *nativeString = (*env)->GetStringUTFChars(env, message, 0);
	writeFIFO(nativeString);
}


JNIEXPORT void JNICALL Java_SAND_java_WriteFIFO_closeWriteFIFO(JNIEnv *env, jobject
	obj)  {
	closeWriteFIFO();
}

