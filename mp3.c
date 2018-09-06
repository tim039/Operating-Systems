#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"



/*typedef struct mp3 {

	char* artist;
	char* title;
	char* date;
	int runTime;
	struct mp3 * next;
	struct mp3 * prev;
}mp3_t;
*/

mp3_t *head = NULL;

char buffer[BUFFERSIZE];

int len;

int counter = 0;


int main() {

	char adding = 'y';

	while(adding == 'y') {
	counter++;
	mp3_t* newMp3 = (mp3_t *)malloc(sizeof(mp3_t));

		addMp3(newMp3);
	
		printf("Do you have another MP3 to add? (y/n) \n");
		scanf("%c", &adding);


	}

	printf("Your MP3's have been added\n");



}





void addMp3(mp3_t* newMp3) {	

	
	memset(buffer, 0, sizeof(buffer));


	if (counter >= 2) {
//	printf("Press Enter to continue\n");
	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3 = (mp3_t *) malloc(sizeof(mp3_t));
		newMp3->title = (char *) malloc(len);
		strcpy(newMp3->title, buffer);
	}
}
	


	
	printf("Please input the name of an MP3 you would like to add\n");
	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3 = (mp3_t *) malloc(sizeof(mp3_t));
		newMp3->title = (char *) malloc(len);
		strcpy(newMp3->title, buffer);
		printf("%s\n", newMp3->title);
	}
	

	
	printf("Who is the artist of the MP3?\n");
	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {

		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3 = (mp3_t *) malloc(sizeof(mp3_t));
		newMp3->artist = (char *) malloc(len);
		strcpy(newMp3->artist, buffer);
	}
	
	printf("What is todays date in the form xx-xx-xxxx\n");
	if(fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3 = (mp3_t *) malloc(sizeof(mp3_t));
		newMp3->date = (char *) malloc(len);
		strcpy(newMp3->date, buffer);

	}	
	


	printf("How long is the song in seconds?\n");
//	scanf("%o", &newMp3->runTime);

	if(fgets(buffer, BUFFERSIZE, stdin) != NULL) {
	//	int *newMp3Pt = &newMp3->runTime
		char *holder;
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3 = (mp3_t *) malloc(sizeof(mp3_t));
		holder = (char *) malloc(len);
		//newMp3->runTime = *buffer;
		strcpy(holder, buffer);
		newMp3->runTime = atoi(buffer);		
	}
	
		

	if(head == NULL) {
		newMp3->prev = NULL;
		newMp3->next = NULL;
		head = newMp3;
	}

	else {
	
		mp3_t *temp = head;
		
		while(temp->next != NULL) {
		
			temp = temp->next;

		}

		newMp3->next = NULL;
		newMp3->prev = temp;
		temp->next = newMp3;// CHECK

	}




}


void deleteMp3() {

	mp3_t *temp = head;

	char *deletedMp3;

	printf("Enter the title of the song you would like to delete\n");
	scanf("%s", deletedMp3);

	while(temp->title != deletedMp3) {
		if (temp->next != NULL) {	
			temp = temp->next;
		}

		else {
			printf("Mp3 not found\n");
			break;
		}
	}

	free(temp);

	
	/*if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {

		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		deletedMp3 = (mp3_t *) malloc(sizeof(mp3_t));
		deletedMp3->title = (char *) malloc(len);
		strcpy(newMp3->title, buffer);
	}
*/



}


void printBtoE() {



}


void printEtoB() {



}









