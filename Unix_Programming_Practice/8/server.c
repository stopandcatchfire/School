//Server.c Assignmekt 8
//Nick Wantz
//CSc 60
//Prof Chang 



#include "common.h"

void InitScr(){
	int i;
	ClearScr();
	CursorOff();
	for(i=1; i<27; i++){
		PutChar(i, GOAL, '.');
	}
	for(i=1; i<GOAL; i++){
		PutChar( 27, i, '_');
	}
}

int main(){
	char sem_video_str[20], shmid_str[20], str[30], player_runner;
	int i, exit_ret, place_count, place[26]; 

	sem_t *sem_video;
	int shmid[27];
	data_t *data[26];
	client_t *client;	


	/*	
	switch( fork() ) {

		case -1: perror( "fork: " ); return 0;
		case 0: execl( "./keypoll", "keypoll", (char *) NULL );
		
	}

	wait(&exit_ret);
	exit_ret <<= 16;
	exit_ret >>= 24;
	printf("%d\n", exit_ret);
	player_runner = exit_ret;
	printf("%d\n", player_runner);
	*/
	

	sprintf( sem_video_str, "%d", getpid() );                   //create sem_video string from pid for sem creation
	sem_video = sem_open( sem_video_str, O_CREAT, 0600, 1 );    //create semaphore

	srand(getpid());					    //seed rand for random shared memory key
	
	for(i=0; i<26; i++){
		
		shmid[i] = shmget( rand(), SIZE, IPC_CREAT | 0600 );  //create shared memory segments pass id's io arr
		if( shmid[i]<0 ){
			perror( "shmget: " );
			return 0;
	}

		if( ( data[i] = (data_t *)shmat( shmid[i], NULL, 0 ) ) == (data_t *) -1 ){   //redundant checking of type cast return var
			perror( "shmat: " );
			return 0;
		}
		
		data[i]->sib_order = i;				     

		strcpy( data[i]->sem_video_str, sem_video_str );   //copyh string into runner's mem segment

		data[i]->col = 0;
	}
	
	//make new shared memory for client
	shmid[27] = shmget( rand(), SIZE, IPC_CREAT | 0600 );
	
	if( shmid[27]<0 ){
		perror( "shmat: " );
		return 0;
	}

	if( ( client = (client_t *)shmat( shmid[27], NULL, 0 ) ) == (client_t *) -1 ){
		perror( "shmat: " );
		return 0;
	}

	
	printf("Open new terminal and run: 'client %d'\n", shmid[27]);

	while( client->player_runner < 97 || client->player_runner > 122 ) {
		
	}
	
	InitScr();

	for(i=0; i<26; i++){
	      
		client->col[i] = 0;	
		 
		sprintf( shmid_str, "%d", shmid[i] );	
		
		//if( -1 == fork()){
		switch( fork() ) {
		
			case -1: perror( "fork: " ); return 0;
			case 0: execl( "./runner", "runner", shmid_str, (char *) 0 ); 
		}	
		//printf("execl %d\n", i);
	
		place[i] = 0;

	}
	

	place_count = 0;

	while( place_count<26 ){
		for( i=0; i<26; i++ ){
		
			client->col[i] = data[i]->col;	//updates client col for print.	
	
			if( data[i]->col == GOAL && place[i] == 0 ){
				place_count += 1;		
				place[i] = place_count;
			 //do i need to enclose following statements in thsi if >? based on skeleton.
				
				
			
				
				if( place_count <= 5 ){
					if( player_runner == ( data[i]->sib_order+97 ) ){
						sprintf( str, "\e[%d;%dH <-- Congratulations! You finished at #%d, your prize is $%d.00", data[i]->sib_order+1, GOAL+1, place_count, ( (place_count%5)*15+5 ) );
					
					}
					else
						sprintf( str, "\e[%d;%dH <-- %d   $", data[i]->sib_order+1, GOAL+1, place_count);
				   	//if( player_runner == ( data[i]->sib_order+97 ) ) //if cchosen player is same as winner print diff message
				}
				
					
				else {
					sprintf( str, "\e[%d;%dH <-- %d", data[i]->sib_order+1, GOAL+1, place_count);
				}

				sem_wait(sem_video);
				write( 1, str, strlen(str) );
				sem_post(sem_video);
			}
		}
	}

	

	FlashScr();
 	printf("\e[40;50H\n");
	CursorOn();

	sem_close(sem_video);	
	sem_unlink(sem_video_str);  //possibly semvideostring

	for( i=0; i<26; i++){
		wait(&exit_ret);
		shmctl( getpid(), IPC_RMID, 0 ); //pid or return value? 
	}
	
	return 0;
//end
}













