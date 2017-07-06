//Nick Wantz
//Assignment 3
//CSc 60
//
//
//





#include <stdio.h>
#include <stdlib.h>


int main(){

   int child_pid, wait_pid, exit_code;

   child_pid = fork(); //creates a child

   if(child_pid == -1) {
      perror("fork");
      exit(1);
   }
   
   if(child_pid == 0){
      printf("Child here (PID %d).\n", getpid());
      sleep(3);
      printf("Child here (PID %d) about to exit(77).\n", getpid());
      exit(77);
   }

   printf("Parent here (PID %d), forked child (PID %d).\n", getpid(), child_pid);

   wait_pid = wait(&exit_code);  //waits for child to exit

   exit_code <<= 16;
   exit_code >>= 24;

   printf("Parent here (PID %d), wait returns child PID %d, exit status %d.\n", getpid(), wait_pid, exit_code);

   return 99;
}
