/*
 * Author: Ethan Trott
 * Purpose: A primitive, character-based, LIFO Stack
 * Language: C
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAP 20						//the capacity of the stack

int push(char* val, char a[], int size, int capacity){
	/* Purpose: Push a new character to the stack
	 * Parameters:	val- the character to be pushed
	 * 		a- the array to hold the value
	 * 		size- the current stack size
	 * 		capacity- the stack's capacity
	 * Return Value: the size of the stack after insertion
	 */

	for (int i=0; i<strlen(val); i++){		//for each character entered:
		if (size == capacity){			//if the array is full
			//display the overflow warning
			printf("Overflow: nothing will happen\n");
			break;
		}else{
			size++;				//increase the size
		
			a[size-1] = val[i];		//set the last index to the newest value
		}
	}
	return size;					//return the new size
}

int pop(char a[], int size){
	/* Purpose: Get the last element off the stack and remove it
	 * Parameters:	a- the array to get the value from
	 * 		size- the current size of the stack
	 * Return Value: the size after popping
	 */

	if (size < 1){		//if there's less than one elment, display warning and do nothing
	       	printf("No element to pop.\n");
	}
	else{
		char value = a[size-1];			//the value to be popped
		size--;					//reduce the size
		printf("popped: %c\n", value);		//display the popped value
	}

	return size;		//return the new size
}

void print(char a[], int size){
	/* Purpose: Print the contents of the stack
	 * Parameters:	a- the array to hold the values
	 * 		size- the size of the stack
	 * Return Value: none
	 */

	for (int i=size-1; i>=0; i--){		//for each item from newest to oldest:
		printf("%c\n", a[i]);			//print it to the bottom
	}
}

void getEntered(char *cmd, char *val){
	/* Purpose: separate the entered command and value
	 * Parameters:	*cmd- the pointer to hold the command
	 * 		*val- the pointer to hold the value(s)
	 * Return Value: none
	 */

	char enteredString[50];				//buffer to hold the entered string
	fgets(enteredString, 50, stdin);		//store the entered string

	//if there is a space, store all the characters after it, and other spaces, in val (except \n)
	if (strchr(enteredString, ' ')){		//if there is a space in the command:
		const char token[2] = " ";			//the separator for the string
		char* subCmd = strtok(enteredString, token);	//the substring before the space
		strcpy(cmd, subCmd);				//store the substring
	
		char subVal[50]="";				//the characters to add to the stack
		char* add = strtok(NULL, token);		//the first part to add to the stack
		while (add != NULL){				//until there's no more groups of chars left:
			strcat(subVal, add);			//add the new part to subVal
			strcat(subVal, " ");			//add the space between the parts
			add = strtok(NULL, token);		//get the next part to add
		}
		
		const char newline[2] = "\n";			//the separator for the string
		char* finVal = strtok(subVal, newline);		//get the substring before the new line

		strcpy(val, finVal);				//store the substring in val
			
	}else{							//if there's no space:
		const char token[2] = "\n";
		char *subCmd = strtok(enteredString, token);	//get the string before the new line
		strcpy(cmd, subCmd);				//store the substring
	}
}

int main(){
	char a[CAP] = {};					//the array to hold the stack values
	int size = 0;						//the size of the stack
	
	char enteredCmd[10];					//the last command entered
	char enteredVal[20];					//the last value(s) entered

	//---Input, Processing, and Output---
	printf("Enter command (push, print, or quit): ");	//prompt for input
	getEntered(enteredCmd, enteredVal);			//get input
	while (strcmp(enteredCmd, "quit")){			//until quit is entered:
		if (!strcmp(enteredCmd, "push")) 		//if push is entered:
			//push the value(s) and get the new size
			size = push(enteredVal, a, size, CAP);	
		
		else if (!strcmp(enteredCmd, "pop"))		//if pop is entered:
			//pop the value(s) and get the new size
			size = pop(a, size);

		else if (!strcmp(enteredCmd, "print"))		//if print is entered:
		       	print(a, size);				//print the stack
		
		else 						//if an unknown command is entered:
			//display a warning and move on
			printf("Unrecognized command, please try push, print, or quit.\n");

		printf("Enter command (push, print, or quit): ");	//prompt for input
		getEntered(enteredCmd, enteredVal);			//get input
	}

	return 0;
}
