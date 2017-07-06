// client.c
// this program takes the shared memory id created by the server and displays the same as server.
//
//
//

#include "common.h"

//main needs to take in 1 arg
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


int main(int argc, char*argv[]){
	int exit_ret, shm_id, place_count, i,  place[26];
	char str[30], sem_video_str[20];
	client_t *client;	
	sem_t *sem_video;

	
	if(argc > 2 || argc < 2){
		perror("Not enough arguments ");
		return 0;
	}

	shm_id = atoi( argv[1] );

	switch( fork() ) {

		case -1: perror( "fork: " ); return 0;
		case 0: execl( "./keypoll", "keypoll", (char *) NULL );
	}

	wait( &exit_ret );
	exit_ret <<= 16;
	exit_ret >>= 24;

	printf("You have chosen: %c\n", exit_ret);

	if( ( client = (client_t *)shmat( shm_id, NULL, 0 ) ) == (client_t *) -1 ) {
		perror( "shmat: " );
		return 0;
	}

	sprintf( sem_video_str, "%d", getpid() );  //create vbideo semaphore to try and prevent craziness...
	sem_video = sem_open( sem_video_str, O_CREAT, 0600, 1 );

	
		

	client->player_runner = exit_ret; //passes player selecttion to shm to break while loop

	place_count = 0;		//clear val

	InitScr();
	
	while( place_count < 26 ){
		for( i=0; i<26; i++){
			
			sem_wait( sem_video );
			PutChar( i+1, client->col[i], i+97);
			sem_post( sem_video );	

			if( client->col[i] == GOAL ){
 				place_count += 1;
				place[i] = place_count;

				if( place_count <= 5 ){
					if( exit_ret == ( i+97 ) ){
					}
					else 
						sprintf( str, "\e[%d;%dH <-- %d   $", i+1, GOAL+1, place_count );


				}
				
				else
					sprintf( str, "\e[%d;%dH <-- %d", i+1, GOAL+1, place_count );

				write( 1, str, strlen(str) );
			
			}
			
			else
				sem_wait( sem_video );
				PutChar( i+1, client->col[i], ' ' );
				sem_post( sem_video );
		}
		
	}
	
	FlashScr();
	printf("\e[40;50H\n");
	CursorOn();		
	
	return 0;	
}
