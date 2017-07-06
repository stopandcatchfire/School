//assign7 common.c
//


#include "common.h"

void ClearScr(){
	write(1, "\e[2J", 4);
}

void FlashScr(){
	write(1, "\e[?5h", 5);
	usleep(100000);
	write(1, "\e[?5l", 5);
}

void CursorOn(){
	write(1, "\e[?25h", 6);
}

void CursorOff(){
	write(1, "\e[?25l", 6);
}

void CursorHome(){
	write(1, "\e[0;0H", 6);
}

void PutChar(int row, int col, char ch){
	char str[20];
	sprintf(str, "\e[%d;%dH", row, col);
	write(1, str, strlen(str));
	write(1, &ch, 1);

}


