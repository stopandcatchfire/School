//Nick Wantz
//child.c for assignment 5
//piping
//csc60
//prof Chang



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>

sem_t *sem_video;
int sum, pipe_num, goal_num, my_num;


void CursorHome(){
	write(1, "\e[0;0H", 6);
}

void CursorOff(){
	write(1, "\e[?25l", 6);
}

void CursorOn(){
	write(1, "\[?25h", 6);
}

void ClearScr(){
	write(1, "\e[2J", 4);
}

void FlashScr(){
	//char str[20];

	write(1, "\e[?5h", 5);

	usleep(100000);

	write(1, "\e[?5l", 5);

}

void PutChar(int row, int col, char ch){
	char str[20];
	
	sprintf(str, "\e[%d;%dH", row, col);
	write(1, str, strlen(str));
	write(1, &ch, 1);
} 


void SigIntHandler(){

	int num;
	static int sum = 0;


	read(pipe_num, &num, 4);
	sum += num;

	sem_wait(sem_video);
	PutChar(my_num+1, sum, my_num+48);
	sem_post(sem_video);

	//printf("Child PID:%d gets num %d added to sum = %d\n", getpid(), num, sum);

	if(sum >= goal_num){
		printf("\n\n\n\n\n");
		exit(sum);
	}
}


int main(int argc, char * argv[]){

	


	my_num = atoi(argv[1]);
	goal_num = atoi(argv[2]);
	pipe_num = atoi(argv[3]);
	
	printf("child is here PID:%d\n child number = %d \n goal_num passed = %d\n pipe_num passed = %d\n", getpid(), my_num, goal_num, pipe_num);

	
	sem_video = sem_open(argv[4], 0);

	signal(SIGINT, SigIntHandler);

        	
	while(1)
		pause();
}
