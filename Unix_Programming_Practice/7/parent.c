//Assignment 7
//Nick Wantz
//CSC60
//Prof Chang



#include "common.h"


int main(int argc, char *argv[]){
	int pids[10], sums[10], turns[10];
	int i, max_child, goal, count_done, turn, dummy, pid;

	sem_t *sem_video;
	msg_t msg;
	int qid;
	char qid_str[20];
		
	


	if(argc != 3){
		printf("This program requires 3 arguments to run.\n Try again...\n");
		exit(2);
	}

	max_child = atoi(argv[1]);
	goal = atoi(argv[2]);

	if(max_child>MAX_CHILD || goal>MAX_GOAL){
		printf("Max children = 10, max goal number = 100.\n Please try again...\n");
		exit(2);
	}
	

	sprintf(msg.sem_video_str, "%d", getpid());

	sem_video = sem_open(msg.sem_video_str, O_CREAT, 0600, 1);

	qid = msgget(getpid(), 0600 | IPC_CREAT);


	sprintf(qid_str, "%d", qid);

	for(i = 0; i < max_child; i++){
		pid = fork();

		if(pid == -1){
			perror("fork: ");
			exit(3);
		}

		if(pid == 0){
			//printf("about to execl!\n");			
			if( -1 == execl("./child.out", "child", qid_str, (char *) NULL)){
				perror( "execl" ); return 0;
			}
		}

		pids[i] = pid;
	}

	ClearScr();
	CursorHome();
	for(i=0; i<max_child; i++)
		write(1, "\n", 1);
	for(i=0; i<goal; i++)
		write(1, ">", 1);


	sleep(1);

	//printf("sending messages!\n");

	for(i=0; i<max_child; i++){
		msg.to_pid = (long int)pids[i];
		msg.sib_order = i;
		msg.goal = goal;
		//string to request sem_video???
		
		if( -1 == msgsnd(qid, (void *)&msg, MSG_SIZE, 0)){
			perror( "msgsnd"); return 0;
		}
		
		sums[i] = 0;
		turns[i] = 0;
	}

	sleep(1);

	srand(getpid());

	count_done = 0;
	turn = 0;
	

	//printf("about to take turns!\n");
	
	while(count_done < max_child){
		turn++;

		for( i=0; i<max_child; i++){
			if(sums[i] >= goal) continue;

			msg.to_pid = (long int)pids[i];
			msg.num = rand() % 10;
	
			if( -1 == msgsnd(qid, (void *)&msg, MSG_SIZE, 0)){
				perror( "msgsnd2" ); return 0;
			}
			if( -1 == msgrcv(qid, (void *)&msg, MSG_SIZE, getpid(), 0)){
				perror( "msgrcv" ); return 0;
			}	

			if(msg.sum >= goal){
				sums[i] = msg.sum;
				turns[i] = turn;
				count_done++;
			}
			
			sleep(1);

		}
	}

	printf("\n\n\n\n\n\n\n\n\n***********THE END************\n");

	for(i=0; i<max_child; i++){
		printf("Child #%d, PID: %d, final sum = %d, turns = %d\n", i, pids[i], sums[i], turns[i]);
	}

	
	FlashScr();
	
	for( i=0; i<max_child; i++){
		wait(&dummy); 
	}

	sem_unlink(msg.sem_video_str);
	msgctl(qid, IPC_RMID, 0);

	exit(4);
}















