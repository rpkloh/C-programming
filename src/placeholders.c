/*
placeholders for printf
*/
#include <stdio.h>
#include <stdlib.h>

int DEBUG = 1;

void main (int argc, char* argv[]){
	int a = 10l;
	long b = 2147483647;
	float c = 999.23123;
	double d = 10910234934.00123;
	double e = 23523423423;
	char f = 'f';
	char g[20] = "test";
	int h = 2906;
	
	printf ("int %%d = %d\n", a);
	printf ("long %%ld = %ld\n", b);
	printf ("float %%f = %f\n", c);
	printf ("double %%10.10lf = %10.10lf\n",d);
	printf ("double %%lf = %lf\n", e);
	printf ("char %%c = %c\n", f);
	printf ("string %%s = %s\n", g);
	printf ("hex %%x = %x\n", h);
	printf ("oct %%o = %o\n", h);
	printf ("ptr g %%p = %p\n", g);
	printf ("sci notation d %%e = %e\n", d);
	printf ("%%\n");

}
