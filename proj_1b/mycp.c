#include "mycp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char buffer[128];
int len;

int main() {

	char *fileName1;
	char *fileName2;
	

	printf("Enter the name of the first file: \n");
	if (fgets(buffer, 128, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		fileName1 = malloc(len);
		strcpy(fileName1, buffer);

	}


	printf("Enter the name of the second file: \n");
	if (fgets(buffer, 128, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		fileName2 = malloc(len);
		strcpy(fileName2, buffer);
	}



	printf("%s\n", fileName1);
	printf("%s\n", fileName2);

	free(fileName1);
	free(fileName2);


}

