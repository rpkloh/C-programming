#include <string.h>
#include <stdio.h>

char teststring[100];
char firststring[100]="This is the first string.";
char secondstring[100]="This is the second string.";
char samestring[100]="This is the first string.";

void resetStrings (){
	strcpy(firststring, "This is the first string.");
	strcpy(secondstring, "This is the second string.");
	strcpy(samestring, "This is the first string.");
	printf("\nStrings reset\n");
}

void printStrings(){
	printf("\nfirststring = %s\n", firststring);
	printf("secondstring = %s\n", secondstring);
}

int main(int argc, char *argv[]) {
    //char buffer[100];
    //strcpy(buffer, argv[1]);
    //printf("Done!\n");
    printf("\nOriginal strings\n");
    printStrings();
    //strncpy
    strncpy(firststring, secondstring, 18);
    printf("\nstrncpy\n");
    printStrings();
    resetStrings(firststring, secondstring);
    
    //strcat
    strcat(firststring, secondstring);
    printf("\nstrcat\n");
    printStrings();
    resetStrings(firststring, secondstring);
    
    //strncat
    strncat(firststring, secondstring, 18);
    printf("\nstrncat\n");
    printStrings();
    resetStrings(firststring, secondstring);
    
    //strcmp
    printf("\nstrcmp\n");
    int compare_value = strcmp(firststring, samestring);
    if(compare_value == 0){	//strings are equal
		printf("\nfirststring and samestring are equal\n");
	}else{
		printf("\nstrings are not equal\n");
	}
   
	compare_value = strcmp(firststring, secondstring);
	if(compare_value == 0){	//strings are equal
		printf("\nfirststring and secondstring are equal\n");
	}else{
		printf("\nstrings are not equal. compare_value = %d\n", compare_value);
	}
	
	
    //strncmp
    printf("\nstrncmp\n");
    printf("\nstrlen(firststring) = %d\n", strlen(firststring));
    printf("strlen(secondstring) = %d\n", strlen(secondstring));
    
    for (int i = 0; i < strlen(firststring) && i < strlen(secondstring); i++){
		compare_value = strncmp(firststring, secondstring, i);
		if(compare_value == 0){	//strings are equal
			printf("firststring and secondstring are equal for index = %d\n", i);
		}else{
			printf("strings are not equal at index = %d\n", i);
			return(0);
		}
	}
	
	//another way to do the same thing, just in case we change the strings somewhere
	int len1 = strlen(firststring);
	int len2 = strlen(secondstring);
	int total_len = 0;
	if (len1 >= len2)
		total_len = len2;
	else
		total_len = len1;
	
	for (int j = 0; j < total_len; j++){
		compare_value = strncmp(firststring, secondstring, j);
		if(compare_value == 0){	//strings are equal
			printf("firststring and secondstring are equal for index = %d\n", j);
		}else{
			printf("strings are not equal at index = %d\n", j);
			return(0);
		}
	}
	return(0);
}
