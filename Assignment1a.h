#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct mp3 {

	char* artist;
	char* title;
	char* date;
	int runTime;
	struct mp3 * next;
	struct mp3 * prev;
}mp3_t;


void addFirst() {



}


void addMp3() {

	mp3_t newMp3;

	printf("Please input the name of an MP3 you would like to add\n");
	scanf("%s",newMp3.title);


	printf("Who is the artist of the MP3?\n");
	scanf("%s", newMp3.artist);

	printf("What is todays date in the form xx-xx-xxxx\n");
	scanf("%s", newMp3.date);

	printf("How long is the song in seconds?\n");
	scanf("%d",&(newMp3.runTime));
	

}


void deleteMp3() {


}


void test() {

printf("heiie\n");

}









