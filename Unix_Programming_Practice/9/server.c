//Nick Wantz
//Programming Assignment 9
//
//server.c
//AlphaDerby - Sockets (SingleRemoteClient)


#include "common.h"

int main() {

	int true, my_sock_desc, session; //socket vars
	struct sockaddr_in my_sock_addr, client_sock_addr;  //socket use
	unsigned int sock_size;


	sem_t *sem_video;  	//video/stdout mutex
	data_t *data[26]; 	//26 runner pointers to user defined data type
	char chosen, sem_video_str[10], shmid_str[10], str[100];
	
	int port_num, i, len_recv,	//random port #, loop index, len_rec=recv()
		shmid[26],		//26 shared data_t areas
		place_count, place[26],	//place count, mark down runner places
		points, old[26],	//26 old col to compare with data[26]_>col
		exit_ret;

	srand( getpid());	//seed random

	port_num = getpid()%(9999-1024) + 1023;		//establish port
	printf( "run 'client %d' on another Linux host.\n", port_num);	//print to let user know how to run client

	sprintf( sem_video_str, "%d", getpid() );	//create sem_video string for sem creation

	sem_video = sem_open( sem_video_str, O_CREAT, 0600, 1 );	//create semaphore

	for( i=0; i<26; i++ ){
		shmid[i] = shmget( rand(), SIZE, IPC_CREAT | 0600 );	//create shared mem segments
		
		if( shmid[i]<0 ){
			perror( "shmget: : " );
			return 0;
		}
									//attatch mem id  to data pointer
		if( ( data[i] = (data_t *)shmat( shmid[i], 0, 0 ) ) == (data_t *) -1 ){	
			perror( "shmat: " );
			return 0;
		}

		data[i]->sib_order = i;

		strcpy( data[i]->sem_video_str, sem_video_str );	//copy string into runner's mem segment

		data[i]->col = 0;
	}


	//open socket and bind: calls of socket() and setsockopt()
	if( -1 == ( my_sock_desc = socket( AF_INET, SOCK_STREAM, 0 ) ) ){
		perror( "socket: " );
		return 0;
	}

	if( -1 == setsockopt( my_sock_desc, SOL_SOCKET, SO_REUSEADDR, &true, sizeof( int ) ) ){
		perror( "setsockopt: " );
		return 0;
	}

	my_sock_addr.sin_family = AF_INET;
	my_sock_addr.sin_port = htons( port_num );
	my_sock_addr.sin_addr.s_addr = INADDR_ANY;
	bzero( &my_sock_addr.sin_zero, 8 ); 	//8 bytes or sizeof(my_sock_addr.sin_zero)

	//bind server socket to Internet addr: call of bind()
	if( -1 == bind(my_sock_desc, (struct sockaddr *)&my_sock_addr, sizeof(struct sockaddr) ) ){
		perror( "bind: " );
		return 0;
	}

	if( -1 == listen( my_sock_desc, 5 ) ){
		perror( "listen: " );
		return 0;
	}

	//listening for clients
	printf( "	Listening at port %d...\n", port_num );
	sock_size = sizeof( struct sockaddr_in );
	//wait/accept client connection
	session = accept( my_sock_desc, (struct sockaddr *)&client_sock_addr, &sock_size );
	
	//client IP and Port # (ntoa - Netdata To Addr, ntoh - Netdata TO Host Service
	printf( "	Got client from IP %s, Port %d..\n", inet_ntoa( client_sock_addr.sin_addr ), ntohs( client_sock_addr.sin_port ) );

	//recv what's 'chosen' from client: call of recv()
	len_recv = recv( session, &chosen, 2, 0 );
	str[ len_recv ] = 0;  //add null to end string

	printf( "\e[28;1HRunner Chosen: %c \n", chosen );
	sleep(2);

	InitScr();
	
	for( i=0; i<26; i++ ){
		sprintf( shmid_str, "%d", shmid[i] );
		if( 0 == fork() ) 
			execl( "./runner", "runner", shmid_str, (char *) 0 );
	
	old[i] = place[i] = 0;
	}

	points = 6;
	place_count = 0;
	while( place_count < 26 ){
		for( i=0; i<26; i++ ){
			if( data[i]->col != old[i] ){
				send( session, &data[i]->sib_order, sizeof(int), 0 );
				send( session, &data[i]->col, sizeof(int), 0 );
			
				old[i] = data[i]->col;
			
		
				if( data[i]->col == 70 && place[i] == 0 ){
					place_count += 1;
					place[i] = place_count;
				}
			
				if( place_count > 25 ){
					if( chosen == ( data[i]->sib_order+97 ) ){
						points = points - place_count;
						sprintf( str, "\e[%d;%dH <-- Congratulation! You finished at #%d, your prize is $%d.00", data[i]->sib_order+1, GOAL+1, place_count, points );
					}
					else
						sprintf( str, "\e[%d;%dH <-- %d   $", data[i]->sib_order+1, GOAL+1, place_count);
				}
				else{
					sprintf( str, "\e[%d;%dH <-- %d", data[i]->sib_order+1, GOAL+1, place[i] );
				}

				sem_wait(sem_video);
				write( 1, str, strlen(str) );
				sem_post(sem_video);
			}
		}
	}
		
	FlashScr();
	printf("\e[40;1H You earned %d points\n", points); //fix cursor placement
	CursorOn();
	//might need a wait to not mess up client's
	send( session, &points, sizeof(int), 0 );
	sleep(1);

	sem_close(sem_video);
	sem_unlink(sem_video_str);

	for( i=0; i<26; i++){
		wait(&exit_ret);
		shmctl( getpid(), IPC_RMID, 0 );
	}

	return 0;

}
 

		 


		






