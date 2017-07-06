//Nick Wantz
//parent.c for assignment 5
//piping
//csc60 
//prof Chang





#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define MAX_CHILD 10
#define MAX_GOAL  100


void sigChldHandler(){
	
	int pid, exit_num;

	pid = wait(&exit_num);
	pid <<= 16;
	pid >>= 24;

	printf("Parent: child pid %d wins with sum = %d exiting...\n", pid, exit_num);

	kill(0, SIGQUIT);
}

int main(int argc, char * argv[]){


	int num_children = atoi(argv[1]);
	int goal_num = atoi(argv[2]);
	char i_str[3];//null terminating that;s why there are 3
	int my_pipe[2];
	int i, randnum;
	int child_pid[10];

	if( -1 == pipe( my_pipe )){
		perror("pipe: ");
		exit(1);
	}

	for(i=0; i<num_children; i++){
		switch( fork() ){
		
		case -1:
			perror("fork: ");
			exit(2);
		
		case 0:	
			sprintf(i_str, "%d",i);	
			execl("./child", "babs", i_str, goal_num, &my_pipe[0], (char *) 0);
		}
		child_pid[i] = getpid();
	}

	sleep(1);
	signal(SIGCHLD, sigChldHandler);	
	srand(getpid());
	while(1){
		for(i=0; i<num_children; i++){
			randnum = rand() % 10;
			write(my_pipe[1], &randnum, sizeof(int));
			kill(child_pid[i], SIGINT);
			sleep(1);
		}
	}
	close my_pipe[0];
	close my_pipe[1];
	exit(6);
}	
