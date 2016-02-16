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

void roundRob(int count, int *procArray, int *durArray) {
	int clock = 0;
	int next_proc = 0;
	// int * ready[]  for other algorithms
	int turn = 0; // turn-around time
	int wait = 0; // wait ''
	int resp = 0; // response ''
	int quan = 100;
	int i;
	int next_clock;
	int nothing;	

	int point[count];

	for(i = 0; i < count; i ++) {
		point[i] = 0;
	}

	while (next_proc < count) {
		for(i = 0; i < count; i++) {
			if(durArray[i] > quan) point[i] = 1;
		}

		// Finding the next job and moving the clock forward as necessary
		if (procArray[next_proc] > clock) clock = procArray[next_proc];

		// Calculating response time (clock - submission)
		resp += clock - procArray[next_proc];

		if (durArray[next_proc] > quan) {
			next_clock = clock + quan;
			durArray[next_proc] = durArray[next_proc] - quan;
		}

		else{
			// Finding the next event (end-of-job)
			 next_clock = clock + durArray[next_proc];
			// Calculating Turn-around (end-of-job 0 submission)
			turn += next_clock - procArray[next_proc];
			// Calculating wait (Turn-Around - runtime)
			wait += next_clock - procArray[next_proc] - durArray[next_proc]; // Same for other algorithms
		}

		// Advance clock
		clock = next_clock;

		for(i = 0; i < count; i++) {
			if(point[i] == 1 && (clock >= procArray[i])) {
			//	next_proc = i;
				break;
			}
			else {
				nothing = -1;
			}
		}	
		// Move to next process
		if (nothing == -1) next_proc++;
	}

	printf("Avg. Resp: %.2f,  Avg. T.A: %.2f,  Avg. Wait: %.2f\n", (double)resp / count, (double)turn / count, (double)wait / count);
}
