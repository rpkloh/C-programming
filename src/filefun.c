/*
 * opening and reading files
 * 
 * this program will produce 3 text files from the user defined text file that is specified:
 * 
 * - a direct copy, character by character: "same.txt"
 * - a reverse copy where each line is reversed: "reverse.txt"
 * - a completely inverted file using recursion: "recursion.txt"
 */

#include <stdio.h>
#include <string.h>

#define FILENAMESIZE 256

int DEBUG = 1;

	
void recursiveRead(FILE *infilep, FILE *outfilep){
	char ch;
	ch = getc(infilep);
	//if not the EOF, read the file until it is found
	if(ch != EOF){
		
		recursiveRead(infilep, outfilep);
		if (DEBUG) printf("recursive ch = %c\n", ch);
		//if the EOF is found, then the calling function is allowed to 
		//write the character into the file
		putc(ch, outfilep);
		
	}
}

int main(void){
	char  holding[FILENAMESIZE];
	//file names
	char inputname[FILENAMESIZE];
	char output1[FILENAMESIZE] = "same.txt";
	char output2[FILENAMESIZE] = "reverse.txt";
	char output3[FILENAMESIZE] = "recursion.txt";
	
	//reading files by one character at a time
	char ch;
	
	//this is a short string needed to append each character to the 
	//onto the holding string
	char chs [1];
	
	//file pointers for input and output
	FILE *infilep1;
	FILE *infilep2;
	FILE *outfilep1;
	FILE *outfilep2;
	FILE *outfilep3;
	
	//prompt user for input filename
	printf("Enter the name of the input file: ");
	scanf("%s", inputname);
	
	//try to open input file
	infilep1 = fopen(inputname, "r");
	if (infilep1 == NULL){
		printf("\nUnable to open file \"%s\"\n", inputname);
		return 0;
	}
	//open outfile pointer 1
	outfilep1 = fopen(output1, "w");
	if (outfilep1 == NULL){
		printf("\nUnable to open file \"%s\"\n", output1);
		return 0;
	}
	//open outfile pointer 2
	outfilep2 = fopen(output2, "w");
	if (outfilep2 == NULL){
		printf("\nUnable to open file \"%s\"\n", output2);
		return 0;
	}
	//open outfile pointer 3
	outfilep3 = fopen(output3, "w");
	if (outfilep3 == NULL){
		printf("\nUnable to open file \"%s\"\n", output3);
		return 0;
	}
	//read in entire file while not EOF
	while(ch != EOF){
		//scan character
		ch = getc(infilep1);
		if(DEBUG) printf("%c", ch);
		
		//write character directly into same.txt
		putc(ch, outfilep1);
		
		//return character detected, write holding string to file
		if(ch == '\n'){
			if(DEBUG) printf("ch = %c", ch);
			//start at the back of the holding string, write character to reverse.txt, keep moving until start of string
			for (int j = strlen(holding); j >= 0; j--){
				putc(holding[j], outfilep2);
				holding[j] = '\0';	//reset holding string
			}
			putc('\n', outfilep2);
		} else {	//not empty space, add to holding string
			if(DEBUG) printf("%c\n", ch);
			chs [0] = ch;
			chs [1] = '\0';
			if(DEBUG) printf("%s\n", chs);
			if(strlen(holding) < FILENAMESIZE) strcat(holding, chs);
			if(DEBUG) printf("%s\n", holding);
		}
	}
	
	//try to open input file again, sincw we got to the end of file last time
	infilep2 = fopen(inputname, "r");
	if (infilep2 == NULL){
		printf("\nUnable to open file \"%s\"\n", inputname);
		return 0;
	}
	
	//try the recursive approach
	recursiveRead(infilep2, outfilep3);
	
	if(DEBUG) printf("DONE\n");
	return 0;
}
