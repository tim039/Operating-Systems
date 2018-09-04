#include <stdio.h>
#include "Assignment1a.h"

int main() {

char * adding = "y";

while(adding == "y") {

	addMp3();
	printf("Do you have any more mp3's to add? (y/n) \n");
	scanf("%s", adding); 

}
	printf("Your MP3's have been added\n");
}
