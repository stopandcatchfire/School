//Nick Wantz
//CSC60 t, th 5:30-5:45
//3/6/15
//assignment 4 child
//
//this is the child program called for each child from the parent.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//#define playgame(goal, sum) while(sum<goal)

void MySigIntHandler(){

	sum += rand() % 10;		
}


void MyExitHandler(){
	printf("Child#: %d (PID %d)  is  exiting with sum = %d...\n", child_num, getpid(), sum);
	 
}


int main(int argc, char *argv[]){

	int child_num, goal_num, pid, sum;

	goal_num = argv[1];
	child_num = arv[2];

	if(argc !=3){
		printf("Child didn't get enough args!(3)\n");
		exit(1);
	}

	srand(getpid());
	 
	signal(SIGINT, MySigIntHandler);

	if(sum>49)
		signal(SIGQUIT, MyExitHandler);

	atexit(MyExitHandler);

	while(1) pause();
}
