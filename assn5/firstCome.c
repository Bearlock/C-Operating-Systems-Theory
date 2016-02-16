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

#include "assn5.h"
#include <stdio.h>

void firstCome(int count, int *procArray, int *durArray) {
	int clock = 0;
	int next_proc = 0;
	int turn = 0; // turn-around time
	int wait = 0; // wait ''
	int resp = 0; // response ''

	while (next_proc < count) {
		// Finding the next job and moving the clock forward as necessary
		if (procArray[next_proc] > clock) clock = procArray[next_proc];
		
		// Calculating response time (clock - submission)
		resp += clock - procArray[next_proc];
		
		// Finding the next event (end-of-job)
		int next_clock = clock + durArray[next_proc];

		// Calculating Turn-around (end-of-job 0 submission)
		turn += next_clock - procArray[next_proc];

		// Calculating wait (Turn-Around - runtime)
		wait += next_clock - procArray[next_proc] - durArray[next_proc]; // Same for other algorithms
		
		// Advance clock
		clock = next_clock;
		// Move to next process
		next_proc++;
	}
	
	printf("Avg. Resp: %.2f, Avg. T.A: %.2f, Avg. Wait: %.2f\n", (double)resp / count, (double)turn / count, (double)wait / count);
}
