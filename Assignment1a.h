#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BUFFERSIZE 128



typedef struct mp3 {

	char* artist;
	char* title;
	char* date;
	int runTime;
	struct mp3 * next;
	struct mp3 * prev;
}mp3_t;


mp3_t *head = NULL;
//head = malloc(sizeof(mp3_t));

char buffer[BUFFERSIZE];

void addMp3() {

	mp3_t* newMp3 = (mp3_t *)malloc(sizeof(mp3_t));

	
	printf("Please input the name of an MP3 you would like to add\n%s", newMp3->title);
	//scanf("%s",newMp3->title);
	fgets(newMp3->title, BUFFERSIZE, stdin);


	printf("Who is the artist of the MP3?\n%s", newMp3->artist);
	//scanf("%s",newMp3->artist);
	fgets(newMp3->artist, BUFFERSIZE, stdin);

	printf("What is todays date in the form xx-xx-xxxx\n");
	scanf("%s", newMp3->date);

	printf("How long is the song in seconds?\n");
	scanf("%d",&(newMp3->runTime));
	

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



}


void printBtoE() {



}


void printEtoB() {



}




void test() {

printf("heiie\n");

}









