/* 
Erick Diaz
CS3060-601 Fall 2015
Assignment 3

Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

#include<stdio.h>
#include<pthread.h>
#include<stdint.h>

// Function declaration and some global variables
void *sumFunc(void *array);
int count;
int sums;

int main(int argc, char *argv[]) {
	
	// Array of up to 100 numbers along with a default thread id and attribute
	FILE *fp;
	int numArray[100];
	pthread_t threadID;
	void * total;	

	fp = stdin;
	count = 0;
	
	// If there is more than 1 argument, open the second argument
	// as a file stream and read from it. If its null, print 
	// ambigious error, return -1, high five yourself for messing up
	if(argc > 1) {
		fp = fopen(argv[1], "r");
		if(fp == NULL) {
			perror("File is null for some reason");
			return -1;
		}
		
		// While-loop that uses fscanf to read from the passed in file until end of file
		// increments counter variable and then creates the child thread with a passed in 
		// thread id, attribute, void function, and array reference, waits for
		// child thread to return with 0, and then continues on with the rest of the program
		while(EOF != fscanf(fp, "%d", &numArray[count])) {
			count++;
		}

		pthread_create(&threadID, NULL, sumFunc, &numArray);
		pthread_join(threadID, &total);

	}
	else {
		// Does the same thing as the loop above, but with stdin as opposed to a file
		while(EOF != fscanf(fp, "%d", &numArray[count])){
			count++;
		}

		pthread_create(&threadID, NULL, sumFunc, &numArray);
		pthread_join(threadID, &total);
	}

	// Prints sum and counter
	int sum = (*(int *)total);
	printf("\nSum of %d numbers is %d\n", count, sum);
	return 0;
}

void *sumFunc(void *args){
	int i;
	int * duh;

	// Casts passed in void pointer to int pointer (array)
	int * numArray = (int *)args;

	// Sets sum to 0, loops through array and adds the values to sum, exits
	sums = 0;
	for(i = 0; i < count; i++)
	{
		sums += numArray[i];
	}
	duh = &sums;
	return (void *)duh;
}
