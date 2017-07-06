//CSc 60 assign7 message queues
//common.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/msg.h>

#include <string.h>

#define MAX_CHILD 10
#define MAX_GOAL 100

typedef struct {
	long int to_pid;
	int sib_order, num, goal, sum;
	char sem_video_str[20];
} msg_t;

#define MSG_SIZE (sizeof(msg_t) - sizeof(long int)) 

void ClearScr();
//	write(1, "\e[2J", 4);
//}

void FlashScr();/*
	write(1, "\e[?5h", 5);
	usleep(100000);
	write(1, "\e[5l", 5);
}*/

void CursorOn();/*{
	write(1, "\e[?25h", 6);
}*/

void CursorOff();/*{
	write(1, "\e[?25l", 6);
}*/
	
void CursorHome();/*{
	write(1, "\e[0;0H", 6);
}*/

void PutChar(int row, int col, char ch);/*{
	char str[20];

	sprintf(str, "\e[%d;%dH", row, col);
	write(1, str, strlen(str));
	write(1, &ch, 1);
}*/







