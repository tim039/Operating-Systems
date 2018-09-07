/*mp3.h
By: Timothy Louie
written: 9/1/2018
Updated: 9/7/2018
Mp3.h is the header file for mp3.c
*/
#ifndef mp3_h
#define mp3_h
#define BUFFERSIZE 128

typedef struct mp3 {

	char *artist;
	char *title;
	char *date;
	int runTime;
	struct mp3 *next;
	struct mp3 *prev;
}mp3_t;



void addMp3();

void deleteMp3();

void printBtoE();

void printEtoB();


#endif
