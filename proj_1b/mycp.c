/*mycp.c
By: Timothy Louie
Written:9/10/2018
Updated: 9/14/2018
mycp.c copies an input file to an output file
*/

#include "mycp.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


char buffer[BUFFERSIZE];
int len;
size_t bytes;
char command[50];	

char *fileName1;
char *fileName2;

char c;

int fileRead;
int file1;
int file2;



int main(int argc, char **argv) {

	if(argv[2] == NULL || argv[1] == NULL) {
		perror("missing file(s)\n");
		return 0;
	}

	else if(argv[3] != NULL) {
		perror("too many files!\n");
		return 0;

	}

	copy(argv[1], argv[2]);


	return 0;
}


/*this function copies the contents of the first argument to the second argument*/
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
	
			execlp("cp","cp", "-i", fileName1, fileName2, NULL);
			
	}
	

	fileRead = read(file1, buffer, BUFFERSIZE);
	
	write(file2 ,buffer, BUFFERSIZE);

	close(file1);
	close(file2);	

}


