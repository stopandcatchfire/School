//Child. c 
//assigment 7
//
//
//
//Nick Wantz


#include "common.h"


int main(int argc, char *argv[]){
	sem_t *sem_video;
	int qid;
	msg_t msg;
	int sib_order, goal, sum;

	if(argc != 2){
		perror("Requires only 2 arguments");
		exit(0);
	}

	//printf("made it into child!\n");

	qid = atoi(argv[1]);
	
	if( -1 == msgrcv(qid, (void *)&msg, MSG_SIZE, getpid(), 0)){
		perror( "msgrcv" ); return 0;
	}

	//printf("child received message!\n");
	//printf("num = %d\n", msg.num);


	sem_video = sem_open(msg.sem_video_str, O_CREAT, 0600, 1);

	sib_order = msg.sib_order;
	
	goal = msg.goal;

	sum = 0;
	
	//printf("child here aboutr to play!\n");

	while(1){
		if( -1 == msgrcv(qid, (void *)&msg, MSG_SIZE, getpid(), 0)){
			perror( "msgrcv" ); return 0;
		}
	
		sum += msg.num;

		sem_wait(sem_video);
		PutChar(sib_order+1, sum, sib_order+48);
		sem_post(sem_video);
		
		msg.sum = sum;
		msg.to_pid = getppid();
	
		if( -1 == msgsnd(qid, (void *)&msg, MSG_SIZE, 0)){
			perror( "msgsend" ); return 0;
		}
		
		
		if(sum >= goal){
			//printf("child wins\n");
			break;
		}
		
	}

	exit(0);

}

		
