/*
 * 
 * Tom Scott exercise
 * 
 * enter number
 * any number divisible by 3 prints out "fizz"
 * any number divisible by 5 prints out "buzz"
 * any number divisible by both prints out "fizzbuzz"
 * 
 */
 
#include <string.h>
#include <stdio.h>

void main(){
	int times = 0;
	printf("Enter a number:\n");
	scanf("%d", &times);
	printf("\nBeginning\n\n");
	int i = 0;
	
	while(i < times){
		//printf("times\n");
		char printout[20] = "";
		i++;
		if (i%3 == 0) strcat(printout, "fizz");
		if (i%5 == 0) strcat(printout, "buzz");
		if (strlen(printout) == 0) printf("%d\n", i);
		else printf("%s\n", printout);
		
	}
}

