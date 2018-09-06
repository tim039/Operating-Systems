
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



void addMp3(mp3_t* newMp3);

void deleteMp3();

void printBtoE();

void printEtoB();


#endif
