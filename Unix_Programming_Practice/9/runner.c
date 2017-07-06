// Assignment 8
// Runner.c
// Nick Wantz
//


#include "common.h"



int main(int argc, char*argv[]) {

	sem_t *sem_video;
	int my_row;
	char my_symbol;
	int shmid, i;
	data_t *my_data;

	shmid = atoi( argv[1] );
	
	if( ( my_data = shmat( shmid, 0, 0 ) ) == (char *) -1 ){
		perror( "shmat: " );
		return 0;
	}
	
	//printf("one child\n");


	sem_video = sem_open( my_data->sem_video_str, O_CREAT, 0600, 1 );
	
	srand( getpid() );
	
	my_row = my_data->sib_order + 1;
	my_symbol = my_data->sib_order + 97; //adjust for proper character.

	for( i = my_data->col; my_data->col<GOAL; my_data->col++ ){
		sem_wait( sem_video );
		PutChar( my_row, my_data->col, my_symbol );
		sem_post( sem_video );

		usleep( USEC * ( rand() % 3) );

		if( i == GOAL ) break;

		sem_wait( sem_video );
		PutChar( my_row, my_data->col, ' ' );
		sem_post( sem_video );
	}

	return 0;
}
