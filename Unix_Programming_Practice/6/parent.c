//Nick Wantz
//parent.c for assignment 5
//piping
//csc60 
//prof Chang





#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAX_CHILD 10
#define MAX_GOAL  100

int pid, randnum;
//sem_t *sem_video;


void ClearScr(){
	write(1, "\e[2J", 4);
}


void sigChldHandler(){
	
	int exit_num = 0;
	pid_t cPid;
	cPid = wait(&exit_num);
	exit_num <<= 16;
	exit_num >>= 24;

	//printf("Parent: child pid %d wins with sum = %d exiting...\n", cPid, exit_num);

	kill(0, SIGQUIT);
}

int main(int argc, char * argv[]){


	int num_children, goal_num, i, execRet;
	char i_str[3];//null terminating that;s why there are 3
	int my_pipe[2];
	int child_pid[MAX_CHILD];
	char goal_str[4];
	char pipe_str[3];
	char sem_video_str[8];
	sem_t *sem_video;

	sprintf(sem_video_str, "%d", getpid());
	sem_video = sem_open(sem_video_str, O_CREAT, 0600, 1);

	num_children = atoi(argv[1]);
	goal_num = atoi(argv[2]);
	//goal_str = argv[2];
		
	sprintf(goal_str, "%d", goal_num);
	

	if( -1 == pipe( my_pipe )){
		perror("pipe: ");
		exit(1);
	}
	
	for(i=0; i<num_children; i++){
		pid = fork();
	

		if(pid == -1){
			perror("fork: ");
			exit(2);
		}
		else if(pid == 0){
			printf("child %d here! about to execl! pid:%d\n", i, getpid());	
			sprintf(i_str, "%d", i);	
			sprintf(pipe_str, "%d", my_pipe[0]);
			execRet = execl("./child.out", "child", i_str, goal_str, pipe_str, sem_video_str, (char *) NULL);
			//execRet = execl("./child.out", "child", "hello", (char *) NULL);
			if(execRet == -1){
				perror("error at execl");

			}
			_exit(0);
		}
			 	
		child_pid[i] = pid;
	}

	sleep(1);

	ClearScr();

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
	
	//signal(SIGCHLD, sigChldHandler);
	
	
	for(i=0; i<num_children; i++)
		printf(" Pid# %d i = %d \n", child_pid[i], i);
	printf("got there\n");
	close(my_pipe[0]);
	close(my_pipe[1]);
	exit(6);
}	
