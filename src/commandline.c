/* 
Template for reading command line arguments
also, printing them out
*/

#include <stdio.h>
#include <stdlib.h>

int DEBUG = 1;

void main (int argc, char* argv[]){
	int i = 0;
	while (i < argc){
		if (DEBUG == 1)
			printf("argc = %d argv = %s\n", i, argv[i]);
		i++;
	}
}
