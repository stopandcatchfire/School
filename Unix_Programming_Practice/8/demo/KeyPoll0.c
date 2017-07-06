// KeyPoll0.c
// set stdin echo off, non-block for check/read
// if key pressed, can know and read it in

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/time.h>

// set stdin non-block or return to default block (1 NBon, 0 NBoff)
void NonBlock(int NBon) {
    struct termios tty_attr;
 
    tcgetattr(0, &tty_attr); // get stdin (file # 0) terminal attributes
 
    if (NBon) {
        tty_attr.c_lflag &= ~(ICANON | ECHO); // canonical & echo mode off
        tty_attr.c_cc[VMIN] = 1;              // just 1 char arrival will do
    } else {
        tty_attr.c_lflag |= ICANON & ECHO;    // turn back on modes
    }

    tcsetattr(0, TCSANOW, &tty_attr);         // set stdin term attributes
}

// return 1 if a key pressed (before this called) and latched for read
int KeyHit() {
    struct timeval my_tv; // time value of poll
    fd_set my_fds;        // a set of fd (we use 1)

    my_tv.tv_sec = 0;     // cause no wait, poll time 0 whole sec
    my_tv.tv_usec = 0;    // cause no wait, poll time 0 microsec

    FD_ZERO(&my_fds);     // clear fd set
    FD_SET(0, &my_fds);   // or use STDIN_FILENO, same 0
    select(1, &my_fds, 0, 0, &my_tv); // 1 channel, two 0 null (or NULL)

    return FD_ISSET(0, &my_fds);      // test stdin (file # 0)
}

int main() {
   char ch;

   printf("Press a key, 'q' to quit:\n");

   NonBlock(1);            // set stdin won't block on KB input

   while(1) {
      if( KeyHit() ) {     // check if key pressed
         read(0, &ch, 1);  // read key-in as a char
         write(1, &ch, 1); // display 1 byte (char) to 1 (stdout)
         write(1, " pressed\n", 9); // msg has 9 bytes to write

         if ( ch == 'q' ) break;
      } else {
         write(1, "*", 1); // print a star to show it's looping
      }

      usleep(100000);      // pause .1 sec
   }

   NonBlock(0);            // set stdin back to block

   return 0;
}
