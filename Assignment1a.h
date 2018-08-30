#include <stdio.h>

typedef struct{

	char* artist;
	char* title;
	char* date;
	int runTime;
	mp3* next;
	mp3* prev;
}mp3;

void addMp3() {

	mp3 newMp3;

	printf("Please input the name of an MP3 you would like to add\n");
	scanf(%s,newMp3.title);


	printf("Who is the artist of the MP3?\n");
	scanf(%s, newMp3.artist);

	print("What is todays date in the form xx-xx-xxxx\n");
	scanf(%s, newMp3.date);

	printf("How long is the song in seconds?\n");
	scanf(%d, newMp3->runTime);
	

}


void deleteMp3() {


}












