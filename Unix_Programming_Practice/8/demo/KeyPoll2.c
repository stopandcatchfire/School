// KeyPoll2.c
// detect KB pressed in sub of main(), nonblock, no echo

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
 
// returns 1 if any key pressed, or 0 none
int KeyHit(struct timeval my_tv) {   // my_tv will get changed
   fd_set my_fds;
 
// set 0 (stdin file descriptor #) as target
   FD_ZERO( &my_fds );
   FD_SET( 0, &my_fds );

// poll stdin for my_tv (time value) period
   select( 1, &my_fds, 0, 0, &my_tv ); // 1 channel, two 0 null

// if flag in my_fds set, a key was pressed
   return FD_ISSET( 0, &my_fds );      // change/flag occurred in fd stdin
}

int main() {
   struct termios oldt, newt; // old and new term-I/O attr
   struct timeval my_tv;      // time value
   char ch;

   printf("Press different keys, 'q' to quit:\n");

   my_tv.tv_sec = 0;
   my_tv.tv_usec = 100000;    // .1 sec poll

// change mode
   tcgetattr( 0, &oldt );     // get attr of stdin
   newt = oldt;               // make copy to use below
   newt.c_lflag &= ~( ICANON | ECHO ); // disable ECHO
   tcsetattr( 0, TCSANOW, &newt );     // set new attr to stdin

   while(1) {
      if( KeyHit(my_tv) ) {         // if return true
         read(0, &ch, 1);           // read 1 byte (char) from 0 (stdin)
         write(1, &ch, 1);          // display 1 byte (char) to 1 (stdout)
         write(1, " pressed\n", 9); // msg has 9 bytes to write

         if ( ch == 'q' || ch == 'Q' ) break;
      } else {
         write(1, "*", 1);          // print a star to indicate loop
      }
   }
//   tcsetattr( 0, TCSANOW, &oldt );  // recover term I/O mode of stdin

   return 0;
}
