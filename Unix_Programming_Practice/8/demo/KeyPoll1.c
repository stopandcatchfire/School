// KeyPoll1.c
// get character as sub of main(), a space means none pressed
// nonblock, no echo, using sub

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
 
// returns char pressed or ' ' (as if space pressed)
char KeyPoll() {
   struct termios oldt, newt; // old termio, new termio
   struct timeval my_tv;      // time value
   fd_set my_fds;             // a set of file descriptors
   char ch;                   // char pressed

   my_tv.tv_sec = 0;          // no whole seconds
   my_tv.tv_usec = 50000;     // microseconds, .05 sec

// change mode
   tcgetattr( 0, &oldt );     // 0 stdin file descriptor #
   newt = oldt;               // new copy to use
   newt.c_lflag &= ~( ICANON | ECHO ); // disable buffering and ECHO
   tcsetattr( 0, TCSANOW, &newt );     // set new term attr of stdin

// set stdin to be the target
   FD_ZERO( &my_fds );        // clear them out 1st
   FD_SET( 0, &my_fds );      // add 0 stdin into it

// poll stdin, this will change my_fds and my_tv
// select: 1 channel to poll, a set of read-fds, a set of write-fds,
// a set of except-fds, and time value
   select( 1, &my_fds, 0, 0, &my_tv );

// if flag in my_fds set, a key was pressed
   if(FD_ISSET( 0, &my_fds )) read(0, &ch, 1);
   else ch = ' ';                             // space if nothing pressed

// change mode back with original old termio
   tcsetattr( 0, TCSANOW, &oldt ); // set term attr of stdin back

   return ch;
}

int main() {
   char ch;

   printf("Press different keys, 'q' to quit:\n");

   while(1) {
      ch = KeyPoll();
      if(ch != ' ') printf("got key %c...\n", ch);
      if ( ch == 'q' ) break;
   }

   return 0;
}

