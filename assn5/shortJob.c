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

void shortJob(int count, int *procArray, int *durArray) {

    // Totals/Counters
    int clock = 0;
    int turn  = 0;
    int wait  = 0;
    int resp  = 0;
    int point = 0;
    int next_proc = 0;
    int i;

    // Arrays
    int remaining[(count * 10)];
    int done[(count * 10)];

    //Initializes arrays
    for (i = 0; i < count; i++) {
        remaining[i] = 0;
        done[i] = 0;
    }

    while(next_proc < count) {
        point = 1;

        // Advance clock
        if(clock < procArray[next_proc]) clock = procArray[next_proc];

        // Calculating response time (clock - submission)
        resp += clock - procArray[next_proc];

        // Finding the next event and incrementing clock (end-of-job)
        clock += durArray[next_proc];

        // Calculating the Turn-around time (end-of-job - submission)
        turn += clock - procArray[next_proc];

        // Calculating the wait time (Turn-around - runtime)
        wait += clock - procArray[next_proc] - durArray[next_proc];

        // Essentially sets a flag so that we know not to process this job again.
        done[next_proc] = 1;
        remaining[next_proc] = 0;

        // For-loop to check if there are more jobs to process
        for (i = 0; i < count; i++) {
            if (done[i] == 0 && procArray[i] < clock) {
                remaining[i] = 1;
                next_proc = i;
                point = 0;
            }
        }

        // Select the next job to process
        if (point == 0) {
            for (i = 0; i < count; i++) {
                if (remaining[i] == 1 && durArray[i] < durArray[next_proc]) {
                    next_proc = i;
                }
            
            }
        }

        else {
            point = 1;
            i = 0;

            // Loop to check done jobs and get us to the next process (especially if there's a gap)
            while (done[i] == 1 && i < count) i++;

            // Advances the clock forward if there's a gap
            if (done[i] == 0) {
                next_proc = i;
                point = 0;
                clock = procArray[i];
            }
        }
    }

        printf("Avg. Resp: %.2f, Avg. T.A: %.2f, Avg. Wait: %.2f\n", (double)resp / count, (double)turn / count, (double)wait / count);
}
