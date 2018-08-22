/*
 * Playing around with structs and linked lists
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAMESIZE 256

int DEBUG = 1;
int DEBUG_NODE = 1;
int TESTSTRUCT = 1;

typedef struct{
	int id;
	char initial;
	char lastname[30];
	struct node * next;
}node;

//node pointers
node * startptr;
node * currentptr;
node * endptr;
	
node * createNode(int id, char initial, char * lastname){
	node * nodeptr;
	
	if(DEBUG_NODE) printf("Inputs: %d %c %s\n", id, initial, lastname);
	
	//allocate memory for new node
	nodeptr = (node *)malloc(sizeof(node));
	
	//start assigning values to node
	nodeptr->id = id;
	nodeptr->initial = initial;
	strcpy(nodeptr->lastname, lastname);
	return nodeptr;	
}

void printStruct(node *n){
	printf("\nStruct->id = %d\n", n->id);
	printf("Struct->initial = %c\n", n->initial);
	printf("Struct->lastname = %s\n", n->lastname);
	
}

node * constructList(FILE *infilep, FILE *outfilep){
	node * head;
	node * tempnode;
	int id = 0;
	char initial = 't';
	char lastname[30] = "test";
	
	if(DEBUG) printf("\n\nConstructing list\n");
	//read in first data node, construct, and point pointers to the right place
	//fscanf(infilep, "%d %c %s", &id, &initial, &lastname);
	//create a placeholder node
	head = createNode(id, initial, lastname);
	
	currentptr = head;
	
	while(1){
		
		int check = fscanf(infilep, "%d %c %s", &id, &initial, &lastname);
		if(check == 3){
			if(DEBUG) printf("Inputs: %d %c %s\n", id, initial, lastname);
			tempnode = createNode(id, initial, lastname);
			currentptr->next = tempnode;
			endptr = tempnode;
		}
		else if(check == EOF){
			printf("Done\n");
			break;
		}
		else{
			printf("fscanf error\n");
			break;
		}
		
	}
	//test node creation and printing
	if(DEBUG) printStruct(head);
	
	return head;
}

int main(){
	//file pointers for input and output
	FILE *infileptr;
	FILE *outfileptr;
	
	
	//char ch;
	//char holding[256];
	
	//try to open input file "data.txt"
	infileptr = fopen("data.txt", "r");
	if (infileptr == NULL){
		printf("\nUnable to open file \"%s\"\n", "data.txt");
		return 0;
	}
	//open outfile pointer 1
	outfileptr = fopen("linkedlist.txt", "w");
	if (outfileptr == NULL){
		printf("\nUnable to open file \"%s\"\n", "linkedlist.txt");
		return 0;
	}
	
	/*//test node creation and printing
	if(DEBUG){
		startptr = createNode(12121,'t', "test");
		printStruct(startptr);
	}*/
	
	
	//read data.txt and convert to linked list
	startptr = constructList(infileptr, outfileptr);
	
	//print linked list
	
	return 0;
}
