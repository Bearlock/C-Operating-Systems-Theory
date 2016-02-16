/*
Erick Diaz
CS3060-601 Fall 2015
Assignment 2

Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
	
	// Immediately forks the current process and assigns that pid to the var 'p'
	pid_t p = fork();
	
	// 'p' would equal zero only if it was the child process. If p isn't zero
	// print that parent has started and wait for the child process to start
	if (p != 0) {	
		printf("\nPARENT process initiated, waiting for %d . . .\n", p);
		wait(NULL);
		printf("\nPARENT resumed. CHILD process complete, PARENT terminating. . . \n");
	}
	
	// When child process starts, check number of arguments. If one argument passed
	// call execlp, if more than one call execvp, if none, return.	
	else {
		if (argc  == 2) {
			printf("\nCHILD process initiated, one argument passed. Calling execlp() . . .\n");
			execlp(argv[1], argv[1], (char *) NULL);
		}
		// Had to get creative here. Created a for loop to copy over the argv array except
		// the first array element (./assn2) so that command  gets called properly. After array
		// is copied, have to null terminate it. Then, execvp can be called with the new array. 
		else if (argc > 2) {
			int i;
			int j = 0;
			char *modarg[argc - 1];
			for(i = 1; i < argc; i++) {
				modarg[j] = argv[i];
				j++;
			}
			modarg[j] = NULL;
			printf("\nCHILD process initiated, more than one argument passed. Calling execvp() . . .\n");
			execvp(modarg[0],  modarg);
		}
		else {
			printf("\nNo arguments provided, CHILD terminating . . .\n");
		}
	}
	return 0;
}
