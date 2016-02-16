/* 
Erick Diaz
CS3060-601 Fall 2015
Assignment 4

Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

// Size of the buffer being passed around
#define BUFFER_SIZE (20)

// Struct that holds buffer, semaphores and sum 
struct toPass {
	int buffer[BUFFER_SIZE];
	sem_t full, empty;
	int sum;
};


void * producer(void *ptr) {
	// Sets sum and array index to 0
	int sum = 0;
	int end = 0;

	// Casts pointer to struct type
	struct toPass *pPtr = (struct toPass *)ptr;

	while(1) {

		sem_wait(&pPtr->full);
		
		// If we get a number 0 or less, we are done reading in numbers
		// Sums up numbers from the buffer, unlocks
		if(pPtr->buffer[end] <=  0) break;		
		sum += pPtr->buffer[end];	
		sem_post(&pPtr->empty);

		// Accesses array within the defined 20 spaces
		end = (end + 1) % BUFFER_SIZE;
	}

	pPtr->sum = sum;
	return ptr;	
}

int main(int argc, char *argv[]) {
	
	// Inits variables, count is the array index, numin is the number being read in
	// number is a counter keeping track of how many numbers have been read in
	// child is the thread handle, pPtr is a pointer to toPass struct	
	FILE *fp;
	pthread_t child;
	int count = 0;
	int numin;
	int number = 0;

	struct toPass *pPtr = malloc(sizeof(struct toPass));

	fp = stdin;
	
	// Checks if file argument has been passed in, changes file pointer to provided argument
	if (argc > 1) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			perror("Something happened");
			return -1;
		}
	}
	
	// Initializes semaphores and creates thread
	sem_init(&pPtr->empty, 0, BUFFER_SIZE);
	sem_init(&pPtr->full, 0, 0);
	pthread_create(&child, NULL, producer, pPtr);
	
	// While we still have numbers to read in, put the values in numin,
	// Lock empty, put the value of numin into buffer at the array index(count)
	// Post to full, increment and mod array index, increment count
	while(EOF != fscanf(fp, "%d", &numin)) {
		
		sem_wait(&pPtr->empty);
		pPtr->buffer[count] = numin;
		sem_post(&pPtr->full);

		count = (count + 1) % BUFFER_SIZE;
		number++;
	}
	
	// set the current buffer number at the array index to 0
	sem_wait(&pPtr->empty);
	pPtr->buffer[count] = 0;
	sem_post(&pPtr->full);

	pthread_join(child, NULL);
	
	printf("\nThe sum of %d numbers is %d\n", number, pPtr->sum);
	return 0;
}
