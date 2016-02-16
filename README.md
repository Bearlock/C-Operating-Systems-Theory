# Operating Systems Theory
This is the repository for an Operating Systems Theory class I took. All the code within is written in C and was compiled on a 64 bit linux architecture. 

Links to program synopses:

[assn2](#assn2)

[assn3](#assn3)

[assn4](#assn4)

[assn5](#assn5)

[assn6](#assn6)

[assn7](#assn7)

### <a id='assn2'></a>
## assn2

Assignment 2 was an exercise is using fork and exec and knowing when and how to execute them properly. The program has 3 different scenarios for 0, 1, and many arguments being passed; it uses the proper exec call accordingly. The program will fork a new child process and exec whatever commands are passed as arguments. 

Example 1: Running the program with no arguments

```bash
$ ./assn2

PARENT process initiated, waiting for 92932 . . .

No arguments provided, CHILD terminating . . .

PARENT resumed. CHILD process complete, PARENT terminating. . .
```

Example 2: Running the program with 1 argument

```bash
$ ./assn2

PARENT process initiated, waiting for 92975 . . .

CHILD process initiated, one argument passed. Calling execlp() . . .
Makefile  assn2  assn2.c

PARENT resumed. CHILD process complete, PARENT terminating. . .

```

Example 3: Running the program with multiple arguments

```bash
$ ./assn2 ls -l -ah

PARENT process initiated, waiting for 93032 . . .

CHILD process initiated, more than one argument passed. Calling execvp() . . .
total 20K
drwxr-xr-x  6 erickdiaz staff  204 Feb 16 12:17 .
drwxr-xr-x 11 erickdiaz staff  374 Feb 16 12:25 ..
drwxr-xr-x 13 erickdiaz staff  442 Feb  9 09:32 .git
-rw-r--r--  1 erickdiaz staff   71 Sep  7 21:54 Makefile
-rwxr-xr-x  1 erickdiaz staff 8.9K Feb 16 12:13 assn2
-rw-r--r--  1 erickdiaz staff 1.9K Feb 16 12:13 assn2.c

PARENT resumed. CHILD process complete, PARENT terminating. . .
```

### <a id='assn3'></a>
## assn3

Assignment 3 is a multi-threaded program that can take up to 100 numbers and sums them all together. It takes a file as an argument, it can have input piped in, or take it directly from stdin. It specifically uses pthreads.

Example 1: File argument

```bash
$ ./assn3 numbers.txt

Sum of 97 numbers is 4753
```

Example 2: Piped output
```bash
$ echo {1..50} | ./assn3

Sum of 50 numbers is 1275
```

Example 3: Stdin
```bash
$ ./assn3
1
2
3
123
3
2
1
321
^D
Sum of 8 numbers is 456
```

### <a id='assn4'></a>
## assn4

Assignment 4 is similar to assignment 3, the biggest difference being that it no longer has a constraint of 100 numbers. The program should read in as many numbers as are desired, put numbers into a structure, and have those summed up 20 at a time. The program is multi-threaded and solves the core issues involved by implementing a buffered producer/consumer that takes advantages of semaphores. As above, it can take a file as an argument, have input piped in, or take it directly from stdin. 


Example 1: File argument

```bash
$ ./assn4 numbers.txt

Sum of 1000 numbers is 500500
```

Example 2: Piped input

```bash
$ echo {1..500..2} | ./assn4

Sum of 250 numbers is 62500
```

Example 3: Stdin

```bash
$ ./assn4
92
31
314
5
54
3543
6
5465
^D
The sum of 8 numbers is 9510
```

### <a id='assn5'></a>
## assn5

Assignment 5 was an exercise in simulating 4 different CPU scheduling algorithms; specifically Round Robin, First Come First Served, Shortest Job First, Shortest Run Time First. The program reads in a text file emulating different burst times, wait times, etc, and acts upon those emulated jobs accordingly. It outputs the time it would take to process the processes according to the algorithms. 

### <a id='assn6'></a>
## assn6

Assignment 6 was similar to assignment 5, but instead of CPU scheduling algorithms, it simulated block access algorithms. It specifically used Circular Look, Shortest Seek Time First, Look, and First Come First Served. The program reads in a text file emulating memory, and acts accordingly upon those emulated jobs. It outputs the time it would take to access memory according to the algorithms.


```bash

$ ./assn6 block.txt

Assignment 6: Block Access Algorithm
By: Erick Diaz

FCFS Total Seek: 1594
SSFT Total Seek: 287
LOOK Total Seek: 269
C-LOOK Total Seek: 477
```

### <a id='assn7'></a>
## assn7

Assignment 7 is a program that recurses into all of the directories within a specified directory and outputs the contents of aforementioned directories. It does some pretty formatting as well. 

Example 1: With a directory argument

```bash
$ ./assn7 ~/school/CS3060/
dir /Users/erickdiaz/school/CS3060/
	dir /Users/erickdiaz/school/CS3060//assn2
		1918: assn2.c
		71: Makefile
	dir /Users/erickdiaz/school/CS3060//assn3
		2264: assn3.c
		80: Makefile
		282: numbers.txt
	dir /Users/erickdiaz/school/CS3060//assn4
		2637: assn4.c
		80: Makefile
	11841: assn4.tar.gz
	dir /Users/erickdiaz/school/CS3060//assn5
		1218: assn5.c
		229: assn5.h
		1446: firstCome.c
		170: Makefile
		1997: roundRob.c
		2719: shortJob.c
		4914: shortRun.c
	dir /Users/erickdiaz/school/CS3060//assn6
		13688: assn6
		5681: assn6.c
		dir /Users/erickdiaz/school/CS3060//assn6/assn6.dSYM
			dir /Users/erickdiaz/school/CS3060//assn6/assn6.dSYM/Contents
				634: Info.plist
				dir /Users/erickdiaz/school/CS3060//assn6/assn6.dSYM/Contents/Resources
					dir /Users/erickdiaz/school/CS3060//assn6/assn6.dSYM/Contents/Resources/DWARF
						12276: assn6
		71: Makefile
		69: text.txt
	dir /Users/erickdiaz/school/CS3060//assn7
		9288: assn7
		1866: assn7.c
		71: Makefile
	4200: README.md

Total file space used:  79710
```

Example 2: Without argument

```bash
$ ./assn7
dir .
	9288: assn7
	1866: assn7.c
	71: Makefile

Total file space used:  11225
```

