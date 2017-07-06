//Nick Wantz
//Programming Assingment 9
//
//client.c
//AlphaDerby - Sockets

#include "common.h"

int main(int argc, char *argv[]){
	char chosen, str[100];
	int i,						//for loops
		col[26], 				//26 columns to be recved
		old[26], 				//to compare
		place_count, place[26],			//store place of each runner
		points,
		pid, exit_code,
		len_recv, my_session, port_num;

	struct sockaddr_in my_server_sock_addr;
	struct hostent *my_server;

	if( argc != 2 ){
		printf( "Usage: %s <port #>\n", argv[0] );
		return 0;
	}

	port_num = atoi( argv[1] );

	my_session = socket( AF_INET, SOCK_STREAM, 0 );	//get descriptor
	my_server = gethostbyname( SERVER_IP );			//get entry by IP
	
	//prepare my_sock_addr
	memcpy( &my_server_sock_addr.sin_addr.s_addr, my_server->h_addr, my_server->h_length );
	my_server_sock_addr.sin_family = AF_INET;
	my_server_sock_addr.sin_port = htons( port_num );

	//connect service described in my_server_sock_addr -> enable my_session
	if( connect( my_session, (struct sockaddr *)&my_server_sock_addr, sizeof(struct sockaddr) ) < 0 ){
		perror( "connect" );
		return 0;
	}
	
	switch( fork() ) {
		case -1: perror( "fork: " ); return 0;
		case 0: execl( "./keypoll", "keypoll", (char *) NULL );
	}

	wait( &exit_code );
	exit_code <<= 16;
	exit_code >>= 24;
	
	chosen = exit_code;
	printf("You have chosen: %c\n", chosen );

	send( my_session, &exit_code, sizeof(int), 0 );	//send chosen runner

	ClearScr();

	InitScr();

	//show place of chosen runner
	sprintf( str, "\e[%d;%dH <--         Good Luck", exit_code-96, GOAL+1 );
	write( 1, str, strlen(str) );

	//each place[sib#] will be given placement # when goal reached
	//old[] for old positions to compare for proper display
	for( i=0; i<26; i++)
		old[i] = place[i] = 0;
	
	place_count = 0;
	i = 0;

	while( place_count <26 ){
		len_recv = recv( my_session, &i, sizeof(int), 0 );
		len_recv = recv( my_session, &col[i], sizeof(int), 0 );
		
		if( len_recv == 0 ) break;
		//shoudl do error checking if( len_recv == 0 ){
		
		PutChar( i+1, old[i], ' ' );
		PutChar( i+1, col[i], i+97 );
		old[i] = col[i];
			
		if( col[i] == GOAL && place[i] == 0 ){
			place_count += 1;
			place[i] = place_count;

			if( place_count < 6 ){
				sprintf( str, "\e[%d;%dH <--   $", i+1, GOAL+1 );
				write( 1, str, strlen(str) );
			}
		}
	}

	len_recv = recv( my_session, &points, sizeof(int), 0 );

	sleep(1);
	FlashScr();
	printf("\e[40;50H\n");
	CursorOn();
	
	printf("You earned %d points this game...\n", points);

	close( my_session );
	return 0;

}
		
