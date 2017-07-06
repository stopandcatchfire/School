//Nick Wantz
//Assignment 3
//CSc 60
//2/23/15


#include <stdio.h>
#include <stdlib.h>


//#define CREATE_CHILD




int child_game(int x, char  goal){
	int sum, pid;
	pid = getpid();

	srand(pid);
	
	sum = 0;

	while(sum<goal){
		sleep(1);
		sum += rand() % 10 ;
		printf("Child %d here %d, sum is now %d.\n", x, getpid(), sum);
	}

	exit(sum);
}

//argc = 3 
void main(int argc, char *argv[]){

	int i, pid, num_children, exit_code, goal_num;
	
//	printf("argv[0] = %c, argv[1] = %c, argv[2] = %c\n", *argv[0], *argv[1], *argv[2]);
	//start of game w/pid
	printf("Parent here %d, about to fork...\n", getpid());

	goal_num = atoi(argv[2]);	//converts string number to int number
	num_children = atoi(argv[1]);	//equals first argument
	for(i=0; i<num_children; i++){	//forks a child for amount enter
		pid = fork();
		
		if(pid==-1){		//error checking
			perror("fork");
			exit(1);
		}
	
		if(pid==0){		

			exit_code = child_game(i, goal_num);	//calls child returns exit code
     	
		}
	}
	//gives parent process wait command and outputs parent's id and child's id and final score of child.
	for(i=0; i<num_children; i++){
		pid = wait(&exit_code);
		exit_code <<= 16;	//shifts bits to retrieve correct area of memory.
		exit_code >>= 24;
		printf("Parent here %d, child exited %d, exit code %d\n", getpid(), pid, exit_code);	
	}
}



