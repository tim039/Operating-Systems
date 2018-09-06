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

		addMp3();
	
		printf("Do you have another MP3 to add? (y/n) \n");
		scanf("%c", &adding);


	}

	printf("Your MP3's have been added\n");

	printBtoE();
	deleteMp3();
	printEtoB();
}





void addMp3() {	

	mp3_t* newMp3 =malloc(sizeof(mp3_t));


	
	memset(buffer, 0, sizeof(buffer));

	if (counter >= 2) {

		if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		}
	}
	


	
	printf("Please input the name of an MP3 you would like to add\n");
	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3->title =  malloc(len);
		strcpy(newMp3->title, buffer);
	}

	
	printf("Who is the artist of the MP3?\n");
	if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {

		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3->artist =  malloc(len);
		strcpy(newMp3->artist, buffer);
	}
	
	printf("What is todays date in the form xx-xx-xxxx\n");
	if(fgets(buffer, BUFFERSIZE, stdin) != NULL) {
	
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		newMp3->date =  malloc(len);
		strcpy(newMp3->date, buffer);
	
	}	
	


	printf("How long is the song in seconds?\n");

	if(fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		char *holder;
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		holder =  malloc(len);
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

//		free(newMp3->title);
//		free(newMp3->artist);
//		free(newMp3->date);
	//	free(holder);
//		free(newMp3);
		
}


void deleteMp3() {

	memset(buffer, 0, sizeof(buffer));	


	mp3_t *temp = head;

//	temp->title = malloc(sizeof(temp->title));


	char *deletedMp3;
	
		if (fgets(buffer, BUFFERSIZE, stdin) != NULL) {
		}
	
	

	printf("Enter the title of the song you would like to delete\n");
	if(fgets(buffer, BUFFERSIZE, stdin) != NULL) {
	
		len = (int) strlen(buffer);
		buffer[len - 1] = '\0';
		deletedMp3 =  malloc(len);
		strcpy(deletedMp3, buffer);
	}	

	
	while(strcmp(temp->title, deletedMp3) != 0) {

		if (temp->next != NULL) {	
			temp = temp->next;
	
		}

		else {
	
			printf("Mp3 not found\n");
				break;
		}
	}

	mp3_t *tempNext = temp->next;
	mp3_t *tempPrev = temp->prev;
	
	tempPrev->next = tempNext;
	tempNext->prev = tempPrev;

	free(temp); 

	




}


void printBtoE() {

	mp3_t* temp = (mp3_t *)malloc(sizeof(mp3_t));

	temp = head;
	
	printf("\n\n\n\n");

	printf("Printing from beginning to end of list");

	printf("\n\n\n\n");

	while(temp->next != NULL) {
		printf("Title: %s\n", temp->title);
		printf("Artist: %s\n", temp->artist);
		printf("Date: %s\n", temp->date);
		printf("runTime: %d\n\n\n\n", temp->runTime);
		temp = temp->next;
	}
		printf("Title: %s\n", temp->title);
		printf("Artist: %s\n", temp->artist);
		printf("Date: %s\n", temp->date);
		printf("runTime: %d\n", temp->runTime);


}


void printEtoB() {

	mp3_t* temp = (mp3_t *)malloc(sizeof(mp3_t));

	temp = head;
	
	printf("\n\n\n\n");

	printf("Printing from end to beginning of list");

	printf("\n\n\n\n");


	while(temp->next != NULL) {
		temp = temp->next;
	}
	
	while(temp->prev != NULL) {
		printf("Title: %s\n", temp->title);
		printf("Artist: %s\n", temp->artist);
		printf("Date: %s\n", temp->date);
		printf("runTime: %d\n\n\n\n", temp->runTime);
		temp = temp->prev;	
	}
	
		printf("Title: %s\n", temp->title);
		printf("Artist: %s\n", temp->artist);
		printf("Date: %s\n", temp->date);
		printf("runTime: %d\n", temp->runTime);





}









