/*
Erick Diaz
CS3060-601 Fall 2015
Assignment 6

Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

#include<stdio.h>
#include<stdlib.h>

// function that returns the absolute value of a number
int absVal(int val) {
	if (val < 0) {
		val = (val * -1);
		return val;
	}
	else {
		return val;
	}
}

int FCFS (int * valArray, int count) {
	int i;
	int tempArray[100];

	// Copy the passed in array to a new array
	for (i = 0; i < count; i++) {
		tempArray[i] = valArray[i];
	}

	int accu = 0;
	for (i = 0; i < count - 1; i++) {
		accu += absVal(tempArray[i] - tempArray[i + 1]);
	}
	return accu;	
}

int SSTF (int * valArray, int count) {
	int i;
	int j;
        int tempArray[100];
	int otherArray[100];

	// Copy the passed in array to 2 new arrays
        for (i = 0; i < count; i++) {
                tempArray[i] = valArray[i];
		otherArray[i] = valArray[i];
        }
	
	int accu = 0;
	int track = 0;
	int start = tempArray[0];
	
	for ( i = 0; i < count; i++) {
		int smallest = tempArray[0] * 10;
		for (j = 1; j < count; j++) {
			if (otherArray[j] != -1) {
				int diff = absVal(start - tempArray[j]);
				if (diff < smallest) { 
					if (diff != 0) {
						smallest = diff;
						track = j;
					}
				}	
			}
		}

		if(smallest == tempArray[0] * 10) smallest = 0;

		accu += smallest;
		start = tempArray[track];
		otherArray[track] = -1;
	}
	return accu;
}

int LOOK (int * valArray, int count) {
	int i;
        int j;
        int temp;
        int tempArray[100];

	// Copy passed in array to new array
        for (i = 0; i < count; i++) {
                tempArray[i] = valArray[i];
        }
	
	// Sort array in ascending order (bubble sort)
        for (i = 0; i < count; i++) {
                for (j = i + 1; j < count; j++) {
                        if (tempArray[i] > tempArray[j]) {
                                temp = tempArray[i];
                                tempArray[i] = tempArray[j];
                                tempArray[j] = temp;
                        }
                }
        }
	
	int track = 0;

	// Keeping track of where to start
	for (i = 0; i < count; i++) {
		if (valArray[0] == tempArray[i]) track = i;
	}	

	int start = valArray[0];
	int diff = 0;
	j = track + 1;
	
	// LOOK in the positive direction
	while (j < count) {
		diff += absVal(start - tempArray[j]);
		start = tempArray[j];
		j++;
	}

	int final1 = diff;
	diff = 0;
	j = track - 1;
	start = tempArray[count - 1];
	
	// After hitting the uppermost memory block, LOOK in the negative direction
	while (j >= 0) {
		diff += absVal(start - tempArray[j]);
		start = tempArray[j];
		j--;
	}

	int final2 = diff;
	return (final1 + final2);
}


int C_LOOK (int * valArray, int count) {
        int i;
        int j;
        int temp;
        int tempArray[100];

        // Copy passed in array to new array
        for (i = 0; i < count; i++) {
                tempArray[i] = valArray[i];
        }

        // Sort array in ascending order (bubble sort)
        for (i = 0; i < count; i++) {
                for (j = i + 1; j < count; j++) {
                        if (tempArray[i] > tempArray[j]) {
                                temp = tempArray[i];
                                tempArray[i] = tempArray[j];
                                tempArray[j] = temp;
                        }
                }
        }

        int track = 0;

        // Keeping track of where to start
        for (i = 0; i < count; i++) {
                if (valArray[0] == tempArray[i]) track = i;
        }

        int start = valArray[0];
        int diff = 0;
        j = track + 1;

        // LOOK in the positive direction
        while (j < count) {
                diff += absVal(start - tempArray[j]);
                start = tempArray[j];
                j++;
        }

	int final1 = diff;
        diff = 0;
        j = 0;
        start = tempArray[count - 1];

	// After hitting the uppermost memory block, circle back to the 0th index, LOOK positive
	while (j < track) {
		diff += absVal(start - tempArray[j]);
                start = tempArray[j];
                j++;
	}
	
	int final2 = diff;
	return (final1 + final2);
}



int main(int argc, char *argv[]) {

        FILE *fp;
        int numArray[100];
	int count;

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
	}

     	// While-loop that uses fscanf to read from the passed in file until end of file
	// Keeps track of count
      	while(EOF != fscanf(fp, "%d", &numArray[count])) {
     		count++;
     	}
	
	// Get result ints, print them out.	
	int fcfsResult = FCFS(numArray, count);
	int sstfResult = SSTF(numArray, count);
	int lookResult = LOOK(numArray, count);
	int c_lookResult = C_LOOK(numArray, count);
	printf("Assignment 6: Block Access Algorithm\nBy: Erick Diaz\n\n");
	printf("FCFS Total Seek: %d\n", fcfsResult);
	printf("SSFT Total Seek: %d\n", sstfResult);
	printf("LOOK Total Seek: %d\n", lookResult);
	printf("C-LOOK Total Seek: %d\n\n", c_lookResult);
	return 0;

}
