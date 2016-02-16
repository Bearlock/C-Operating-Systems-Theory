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

#include <stdio.h>
#include "assn5.h"

void shortRun(int count, int *procArray, int *durArray) {

        // Temps
        int clock = 0; 
        int time  = 0;
        int turn  = 0; 
        int wait  = 0;  
        
        // Totals/Counters
        int next_proc  = 0;
        int total_turn = 0; 
        int total_wait = 0; 
        int total_resp = 0; 
        int i;

        //  Flag/Indices
        int soon = -1; 
        int late = -1;
        int indy = 0; 
        int left = 0; 
        int flag = 0;
 
        // Arrays
        int respArray[count]; 
        int pull[count];
        int push[count];
        int done[count];
        

        // Initializes arrays
        for ( i = 0; i < count; i++) {
                pull[i] = durArray[i];  
                push[i] = -1;
                done[i] = -1; 
		respArray[i] = -1; 
        }

        while (next_proc < count) {
		
		// If conditions are met, push at current process, advance clock, increase index
                if (indy == 0) {
                        if (push[next_proc] == -1) { 
                                if (done[next_proc] == -1) {
                                        push[next_proc] = 1;  
                                        clock = procArray[next_proc];
                                        indy++;
                                }
                        }
                }

                soon = -1;  
		
		// Sets soon to the i index
                for (i = 0; i < count; i++) {
                        if (soon == -1) {
                                if (push[i] != -1) { 
                                        if (done[i] == -1) {
                                                soon = i;
                                        }
                                }
                        }
                        else if (push[i] != -1) {
                                if(durArray[i] < durArray[soon]) {
                                        if(done[i] == -1) {
                                                soon = i;
                                        } 
                                }
                        }
                }

                flag = 0;  
                time = clock + durArray[soon];

		// Process at largest index less than time, increment, shuffle, swap
                for ((late = soon + 1); procArray[late] <= time; late++) {
                        
			//Break if we go outside bounds
			if (late >= count) break;

                        left = time - procArray[late];
			
			// Do nothing
                        if (done[late] == 1 || push[late] == 1);

                        else if (durArray[late] == left) {

                                push[late] = 1;
                                indy++;
                        } 

                        else if (durArray[late] < left) {
                                
                                push[late] = 1;  
                                indy++;
                                respArray[soon] = clock - procArray[soon];      
                                durArray[soon] = left;  
                                clock = procArray[late];     
                                flag = 1;    
                                break;  
                        } 

                        else {
                                
                                push[late] = 1;
                                indy++;
                        }
                }
		
		// Do nothing
                if (flag);

                else {
			// Time is equal to the duration of the last finished process
                        time = clock + durArray[soon];

			// Set response for process to clock - submission time
                        if (respArray[soon] == -1) respArray[soon] = clock - procArray[soon];      

                        turn = time - procArray[soon];  
                        wait = turn - pull[soon];       

                        push[soon] = -1;    
                        done[soon] = 1;  
                        indy--;
			
			// Calculates totals
                        total_resp += respArray[soon];  
                        total_turn += turn;      
                        total_wait += wait;  
                        clock = time;
                        next_proc++;
                }
        }
	printf("Avg. Resp: %.2f, Avg. T.A: %.2f, Avg. Wait: %.2f\n", (double)total_resp / count, (double)total_turn / count, (double)total_wait / count);
}
