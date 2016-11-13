
#include "writeFIFO.c"
#include <stdio.h>

void main() {
	initializeWriteFIFO();
	int i = 0;
	char a[10] = "hhhyh";
	a[5] = '\0';

	while(1) {
		a[0] = i + '0';
		writeFIFO(a);
		sleep(1);
		printf("%d\n",i++);
	}

	closeWriteFIFO();


}