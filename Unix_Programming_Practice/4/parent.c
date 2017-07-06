//Nick Wantz
//CSC60 t,th 5:30-6:45
//3/6/15
//assignment4
//
//this program runs the child parent game//using signal handlers to create a fair game environment
//


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


#define StopSign(X, Y) kill(X, Y)


void MySigChldHandler(){

	int pid, exit_code;
	pid = wait(&exit_code);
	exit_code<<=16;
	exit_code>>=24;
	printf("Parent: child (PID %d) exited with code %d.\n", pid, exit_code);

	exit(3);
	
}

void MyExitHandler(){

	printf("Parent and child exiting\n");
	StopSign(pid, SIGQUIT);
	exit(0);
}


int main(int argc, char *argv[]){

	int num_children = atoi(argv[1]);
	int goal_num = atoi(argv[2]);
	int i, pid, exit_code;
	
	if(argc != 3){
		printf("Usage: %s child_number (1~10) goal_number (10~100)\n", argv[0]);
		exit(1);
	}
	
	signal(SIGCHLD, MySigChldHandler);

	printf("****Parent (PID %d): forks...\n\n", getpid());

	for(i=0; i<num_children; i++){
		pid = fork();
		switch(pid){
			case -1:
				perror("fork");
				exit(1);
			case 0:
				execl("./4", "child", goal_num, i, NULL);        //passing necessary variables for 
				break;
				
		}			
	}
	
	sleep(1);

	printf("\n****Parent (PID %d): loops to signal children..\n", getpid());


	while(1){
		for(i=0 ; i<num_children; i++){
			printf("Parent sending signal to child #%d (PID#%d)", i, getpid());
			StopSign(pid, SIGHUP);

			sleep(1);
		}
				
		atexit(MyExitHandler);
	}

}
		
	
