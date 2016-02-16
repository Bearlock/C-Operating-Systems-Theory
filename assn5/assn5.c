/* 
Erick Diaz
CS3060-601 Fall 2015
Assignment 5

Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

#include<stdio.h>
#include<stdlib.h>
#include"assn5.h"

#define MAX_PROC (100)

int main(int argc, char *argv[]) {
	
	FILE *fp;
	int procArray[MAX_PROC];
	int durArray[MAX_PROC];
	int count = 0;

	fp = stdin;
	
	// Checks if file argument has been passed in, changes file pointer to provided argument
	if (argc > 1) {
		fp = fopen(argv[1], "r");
		if (fp == NULL) {
			perror("Something happened");
			return -1;
		}
	}
	
	// Reads in numbers from file pointer, drops the value into number
	// Every even interval of a read in number gets pushed into proc	
	while(fscanf(fp, "%d %d", &procArray[count], &durArray[count]) == 2) count++;
				
	firstCome(count, procArray, durArray);	
	shortJob(count, procArray, durArray);
	shortRun(count, procArray, durArray);
	roundRob(count, procArray, durArray);
	return 0;
}
