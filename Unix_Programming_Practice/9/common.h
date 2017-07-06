// common.h
// AlphaDerby - Shared Memory

#define SERVER_IP "130.86.67.249\0" //Titan
#define GOAL  70       // # of columns across
#define USEC  70000    // # of microsec sleep, to usleep(1/2/3 * USEC)
#define SIZE  28 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>    // write() needs this
#include <string.h>    // strlen() needs this
#include <time.h>      // time() call to help get unique #
#include <wait.h>      // wait() call to help get unique #

#include <fcntl.h>     // O_CREAT flag (semaphores)
#include <semaphore.h> // sem_open(), etc.

#include <sys/shm.h>   // for shared mem

#include <netdb.h>     // for sockerts, struct sockaddr_in, etc
#include <sys/socket.h> 	//socket calls
#include <arpa/inet.h>	// inet_ntoa()

// each letter symbol process needs one below
typedef struct {
   int sib_order;            // given sib order by server
   char sem_video_str[20];   // access to video display
   int col;                  // current progress, feedback to server
} data_t;

typedef struct {
   int col[26];
   char player_runner;
} client_t;

//***************************************************************************
// common routines
//***************************************************************************
void ClearScr();
void FlashScr();
void CursorOn();
void CursorOff();
void CursorHome();
void PutChar(int, int, char);
void InitScr();

