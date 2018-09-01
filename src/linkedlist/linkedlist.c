/*
 * Playing around with structs and linked lists
 * 
 * Reads each line (id, initial, lastname) from file 'data.txt':

10 B Bear 
11 C Cat
13 D Dog
16 F Fox 
1 A Aardvark 
25 G Goose 
14 E Elephant 
35 H Horse

 * constructs a node for each line and inserts it
 * into an ordered linked list by 'id'
 * 
 * writes out the ordered list into file 'llist.txt'
 * deallocates memory when completed
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILENAMESIZE 256

//debugging and testing switches
int DEBUG = 0;
int DEBUG_NODE = 0;
int DEBUG_LIST = 0;
int TESTSTRUCT = 0;

typedef struct node{
	int id;
	char initial;
	char lastname[30];
	struct node * next;
}node;

typedef struct{
	node * front;
	int size;
}llist;

//node pointers
node * startptr;
node * currentptr;
node * endptr;
	
node * createNode(int id, char initial, char * lastname){
	node * nodeptr;
	
	if(DEBUG_NODE) printf("\ncreatenode: %d %c %s\n", id, initial, lastname);
	
	//allocate memory for new node
	nodeptr = (node *)malloc(sizeof(node));
	
	//start assigning values to node
	nodeptr->id = id;
	nodeptr->initial = initial;
	strcpy(nodeptr->lastname, lastname);
	nodeptr->next = NULL;
	if(DEBUG_NODE) printf("createnode done\n\n");
	return nodeptr;	
}

void printStruct(node *n){
	printf("\nStruct->id = %d\n", n->id);
	printf("Struct->initial = %c\n", n->initial);
	printf("Struct->lastname = %s\n", n->lastname);
	
}

void printList(node *n){
	node * currentp = n;
	node * temp = NULL;
	printf("\nPrinting list\n");
	while(currentp != NULL){
		printStruct(currentp);
		currentp = currentp->next;
		//currentp = temp;
	}
	printf("\nEnd list\n\n");
}

void writeList(FILE *outfileptr, llist * oldlist){
	node * currentp = oldlist->front;
	while(currentp != NULL){
		fprintf(outfileptr, "%d %c %s\n", currentp->id, currentp->initial, currentp->lastname);
		currentp = currentp->next;
	}
}

llist * insertNodeInOrder(llist * oldlist, int id, char initial, char * lastname){
	node * oldnode = oldlist->front;
	node * currentnode = oldnode;
		
	llist * newlist = oldlist;
	int size = oldlist->size;
	node * newnode = createNode(id, initial, lastname);
	if(DEBUG) printf("\nInsert size = %d\n", size);
	if(DEBUG_NODE) printf("newnode: %d %c %s\n", id, initial, lastname);
	if((DEBUG_NODE)&&(oldnode != NULL)) printf("Insert oldnode %d\n", oldnode->id);
	
	//base case, no nodes in linked list
	if(size == 0){
		if(DEBUG) printf("Insert 0\n");
		oldlist->front = newnode;
		newlist = oldlist;
		newlist->size = size + 1;
		if(DEBUG) printf("Insert 0 done %d\n\n", newlist->size);
		if(DEBUG_LIST) printList(newlist->front);
	}else{	//otherwise there are other nodes to consider
		if(DEBUG) printf("Other nodes1\n");
		//case 1:id is greater that current node id in list, keep going through the list
		//case 2:new id is less than or equal to current node id in list, insert before the current list node and exit
		while(currentnode != NULL){	//check to see if we've reached the end of the list
			if(newnode->id > currentnode->id){
				if(DEBUG) printf("Inch along\n");
				oldnode = currentnode;
				currentnode = currentnode->next;	//inch along the list
			}else{
				if(DEBUG) printf("Insert lesser\n");
				if((DEBUG_NODE)&&(oldnode != NULL)) printf("oldnode %d\n", oldnode->id);
				if((DEBUG_NODE)&&(currentnode != NULL)) printf("currentnode %d\n", currentnode->id);
				//if we are at the start, we need some special action
				if(oldnode == currentnode){
					if(DEBUG) printf("Insert start\n");
					newlist->front = newnode;
					newnode->next = oldnode;
					newlist->size = size + 1;
					if(DEBUG_LIST) printList(newlist->front);
					
					return newlist;
					
				}else{
					if(DEBUG) printf("Insert other\n");
					oldnode->next = newnode;
					newnode->next = currentnode;		//insert between the two list pointers
					newlist->size = size + 1;
					if(DEBUG_LIST) printList(newlist->front);
					return newlist;
				}
			}
			currentnode = oldnode->next;
		
		}
		if(DEBUG) printf("Other nodes2\n");
		oldnode->next = newnode;	//insert at the end of list
		newlist->size = size + 1;
		if(DEBUG_LIST) printList(newlist->front);
		return newlist;
	}
	return newlist;
}

llist * constructList(FILE *infilep, FILE *outfilep){
	node * tempnode = NULL;
	
	int id = 0;
	char initial = 't';
	char lastname[30] = "test";
	
	llist * newlist = (llist *)malloc(sizeof(llist));
	newlist->front = NULL;
	newlist->size = 0;
	
	while(1){
		
		int check = fscanf(infilep, "%d %c %s", &id, &initial, &lastname);
		if(check == 3){
			if(DEBUG) printf("Inputs: %d %c %s\n", id, initial, lastname);
			tempnode = createNode(id, initial, lastname);
			if(DEBUG_NODE) printf("tempnode: %d %c %s\n", tempnode->id, tempnode->initial, tempnode->lastname);
			newlist = insertNodeInOrder(newlist, tempnode->id, tempnode->initial, tempnode->lastname);
			//if(DEBUG_LIST) printList(newlist->front);
			if(DEBUG) printf("Inputs done %d\n", newlist->size);
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
	
	if(DEBUG_LIST) printList(newlist->front);
	
	return newlist;
}

//recursive call to deallocate memory from nodes
void freeNode(node * currentp){
	node * tempnode = currentp;
	if(currentp != NULL){
		tempnode = currentp->next;
		freeNode(tempnode);
		if(DEBUG){
			printf("\nDeallocating node:\n");
			printStruct(currentp);
			free(currentp);
		}
	}
}

void deallocList(llist * oldlist){
	node * currentp = oldlist->front;
	if(DEBUG){
		printf("Deallocating list:\n");
		freeNode(currentp);
		free(oldlist);
	}
}

int main(){
	//file pointers for input and output
	FILE *infileptr;
	FILE *outfileptr;
	
	
	//char ch;
	//char holding[256];
	node * tempn1; 
	node * tempn2; 
	llist * newlist;
	
	/* Test of node and list building
	tempn1 = createNode(1, 'y', "yak");
	tempn2 = createNode(2, 'z', "zebra");
	tempn1->next = tempn2;
	startptr = tempn1;
	if(DEBUG_LIST) printList(startptr);
	*/
	
	//try to open input file "data.txt"
	infileptr = fopen("data.txt", "r");
	if (infileptr == NULL){
		printf("\nUnable to open file \"%s\"\n", "data.txt");
		return 0;
	}
	//open outfile pointer 
	outfileptr = fopen("llist.txt", "w");
	if (outfileptr == NULL){
		printf("\nUnable to open file \"%s\"\n", "llist.txt");
		return 0;
	}

	
	
	//read data.txt and convert to linked list
	newlist = constructList(infileptr, outfileptr);
	
	//print linked list
	printList(startptr);
	
	//write list to file "llist.txt"
	writeList(outfileptr, newlist);
	deallocList(newlist);
	return 0;
}
