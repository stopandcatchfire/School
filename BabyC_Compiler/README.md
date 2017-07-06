# BabyC_Compiler
This is a simple compiler that I wrote for a compiler course Fall 2016.


/*December 2016*/


BabyC Compiler


Included are all of the source files needed to compile the compiler.

All tasks were completed on @titan.ecs.csus.edu school server.

To compile, put all source files in single directory, makefile does the work, just "make" and hit return.
bcc is the output of all the files.

Use this to print ILOC to console:
Usage: 

	"bcc filename.bc"
   


If you want to create an ILOC file with the instructions, I just created an empty filename.ILOC file with vi, then run:
	
	bcc filename.bc >> filename.ILOC

It should be automated I know, output wasn't specified so I figured this would do.

I tried to test it with all of the requirements, it should run fine with no errors, infinite virtual registers
are assumed.  No optimizations were included, however I would like to continue expanding on this.  It was actually
really interesting and fun to get this working.
