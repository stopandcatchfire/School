//Assignment 6 Semaphores
//Nick Wantz
//Prof. Chang
//CSC 60 T/Th 5:30-6:45
//4/7/15


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define MAX_ROW 12
#define MAX_COL 30
#define USEC 100000


void PutChar(int row, int col, char ch){		//prints character to screen

	char str[20];

	sprintf(str, "\e[%d;%dH", row, col);
	write(1, str, strlen(str));
	write(1, &ch, 1);
}

void InitScr(){						//sets screen to initial view
	int i;

	write(1, "\e[?25l", 6);
	write(1, "\e[2j", 4);

	for(i=1; i<=MAX_ROW; i++)
		PutChar(i, MAX_COL+1, '|');

	for(i=1; i<=MAX_COL+1; i++)
		PutChar(MAX_ROW+1, i, '-');
}

void FlashScr(){					//makes screen flash

	char str[20];

	write(1, "\e[?5h", 5);
	usleep(100000);
	write(1, "\e[?5l", 5);

	sprintf(str, "\e[%d;%dH", MAX_ROW+3, 1);

	write(1, str, strlen(str));

	write(1, "\e[?25h", 6);
}

int main(){

	int i, j;
	char str[] = "Hello Werld!";

	InitScr();

	for(i=1; i<=MAX_ROW; i++){
		for(j=1; j<=MAX_COL; j++){
			PutChar(i, j, 'A');
			usleep(USEC / 5);
			PutChar(i, j, ' ');
		}
	}

	write(1, "\e[H", 3);

	printf("\n\n\n\n");
	printf("		Hello, Werld!\n");
	printf("	     Hello, Werld!\n");
	printf("	Hello, Werld!\n");
	printf("     Hello, Werld!\n");
	printf("  Hello, Werld!\n");

	for(i=0; i<20; i+=2){
		for(j=0; j<strlen(str); j++){
			PutChar(j+1, i+j+1, str[j]);
			usleep(USEC);
			PutChar(j+1, i+j+1, ' ');
		}
	}

	FlashScr();

	return 0;

}
