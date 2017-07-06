//Nick Wantz
//child.c for assignment 5
//piping
//csc60
//prof Chang



#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void SigIntHandler(){

	printf("Child PID:%d gets num %d added to sum = %d\n", getpid(), play_num, sum);
}


int main(int argc, char * argv[]){

	int my_num, goal_num, pipe, play_num, sum=0;


	my_num = atoi(argv[1]);
	goal_num = atoi(argv[2]);
	pipe = argv[3];

	


	signal(SIGINT, SigIntHandler);

        play_num = read(pipe, &play_num, sizeof(int));
	sum+=play_num;
 	if(sum>=goal_num)
		exit(sum);
	
	while(1)pause();
}
