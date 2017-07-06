//hw2 macros using the ?
//Nick Wantz
//CSC60 T/Th 5:30-6:45
//
//
//This program is used to show knowledge of C macros, using the conditional operator ("?"),
//and bitwise operator;
//
//


#include <stdio.h>
#include <string.h>

//#define FIRST_LETTER(x) x=0? len_str[j]=1 : return;
//#define FIRST_LETTERTWO(x) x=0? len_str[j]=0 : return;

//PARTA
//
//

main()  {

int i, j, len, count;
char name[20];
char len_str[10];


	count = 0;
	write(1, "Please enter your last name: ", 29);
	len = read(0, name, 20);	
	len--; //removes enter key
	
	write(1, "The name you entered is: ", 25);
	write(1, name, len);
	write(1, "\n", 1);

//	TO_BINARY(len, name, j, i, count, len_str);
	
		
	for(i = 0; i<len; i++){
		int binary = 128;
		int decimal = name[i];
		printf("%c  ", decimal);
		fflush(stdout);	 
		for(j = 0; j<8; j++){
		   if((decimal + 1) > binary){
		      write(1, "1 ", 2);
		      decimal -= binary;
		   }
		   else{
		      write(1, "0 ", 2);
		   }
		   binary = binary/2;
		}
		write(1, "\n", 1);
	}
			
}
//PARTB




	




