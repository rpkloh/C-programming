/*
read input from user with scanf
*/

#include <stdio.h>
#include <stdlib.h>

int DEBUG = 1;

void main (int argc, char* argv[]){
	/*int i = 0;
	while (i < argc){
		if (DEBUG == 1)
			printf("argc = %d argv = %s\n", i, argv[i]);
		i++;
	}*/

	int a = 0;
	char b[20];
	printf ("Please enter a number:\n");
	scanf ("%d", &a);
	printf ("Input = %d\n", a);
	printf ("Please enter a name:\n");
	scanf ("%s", b);
	printf ("Input = %s\n", b);
}
