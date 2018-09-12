#include "mycp.h"
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


char buffer[BUFFERSIZE];
int len;
size_t bytes;
	

char *fileName1;
char *fileName2;

char c;

int fileRead;
int file1;
int file2;



int main(int argc, char **argv) {
	const char *error = NULL;
	printf("%s\n", error[0]);
	
	if(argv[2] == NULL || argv[1] == NULL) {
		perror("missing file(s)\n");
		return 0;
	}

	copy(argv[1], argv[2]);


	return 0;
}



void copy(char* fileName1, char *fileName2) {
	
	file1 = open(fileName1, O_RDONLY);

	if(file1 == -1) {
		perror("Error opening file 1\n");
		return;
	}

	file2 = open(fileName2, O_WRONLY);

	if(file2 == -1) {
		file2 = open(fileName2, O_CREAT | O_RDWR, 0644);
	}

	else {
		printf("Would you like to overwrite %s?\n", fileName2);
 
		
	}

	fileRead = read(file1, buffer, BUFFERSIZE);
	
	write(file2 ,buffer, BUFFERSIZE);

	close(file1);
	close(file2);	

}


