/*
Erick Diaz
CS3060-601 Fall 2015
Assignment 7

Promise of Originality
I promise that this source code file has, in it's entirety, been
written by myself and by no other person or persons. If at any time an
exact copy of this source code is found to be used by another person in
this term, I understand that both myself and the student that submitted
the copy will receive a zero on this assignment.
*/

#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addtabs(int depth) {
        int i;
        for (i = 0; i < depth; i++) {
                printf("\t");
        }
}

int readSub(char * dir, int depth) {
	struct stat sa;
	DIR * dp;
	struct dirent * de;
	int totalSize = 0;
	char * nextdir;
	int fSize;
	dp = opendir(dir);
	addtabs(depth);
	printf("dir %s\n", dir);

	if (dp == NULL) {
		perror("Literally can't");
		return -1;
	}
	for(de = readdir(dp); de != NULL; de = readdir(dp)) {
		if(de->d_name[0] != '.') {
			asprintf(&nextdir, "%s/%s", dir, de->d_name);
			lstat(nextdir, &sa);
			fSize = sa.st_size;
			if (S_ISDIR(sa.st_mode)) {
				totalSize = totalSize + readSub(nextdir, depth + 1);
				free(nextdir);
			}
			else if (S_ISREG(sa.st_mode)) {
				addtabs(depth + 1);
				printf("%d: %s\n", fSize, de->d_name);
				totalSize = totalSize +  fSize;
			}
		}
	}
	return totalSize;
}

int main(int argc, char * argv[]) {
	struct stat st;
	int ret = 0;
	char * openDir;
	if (argc > 1) {
		openDir = argv[1];
	}
	else {
		openDir = ".";
	}
		if(lstat(openDir, &st) == 0) {
			if(S_ISDIR(st.st_mode)) { 
				ret = readSub(openDir, 0);
			}
			else {
				printf("\nNot a directory\n\n");
				return -1;
			}
		}
		else {
			printf("\nFile not found\n\n");
			return -1;
		}
	printf("\nTotal file space used:  %d\n\n", ret);
	return 0;
}
