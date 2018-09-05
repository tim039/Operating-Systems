#include <stdio.h>
#include "Assignment1a.h"

int main() {

char* adding = "y";

char buffer[128];


while(adding == "y") {

	addMp3();
	printf("Do you have any more mp3's to add? (y/n) \n");
//	scanf("%c", &adding); 

	if(fgets(buffer,128, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len-1] = '\0';
		adding = (char *) malloc(sizeof(char*));
		adding = (char *) malloc(len);
		strcpy(adding, buffer);
	}
}
	printf("Your MP3's have been added\n");
}
