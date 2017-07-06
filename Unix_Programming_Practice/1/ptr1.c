// ptr1.c
// array can be accessed like pointer
//
// x[i] and *(x+i) are the same memory location
// as parameter of subroutine, "int x[]" is the same as "int *x"

#include <stdio.h>
#include <stdlib.h>

#define N 10           // size of array (why fixed?)

void Sub1(int []);
void Sub2(int *);

int main() {
//     int y[1]; // int *y; y = (int *)malloc(sizeof(int));
   int i;
   int x[] = {40, 51, 62, 73, 84, 95, 106, 117, 128, 139};   //inputing elements (10) into array x[].
   int *p, *q;

   printf("0. %d\n", sizeof(int [1]));   //size of int [1] = 4
   printf("1. %d\n", sizeof(int [N]));   //size of int [N] = 40

   p = x;    // p = 4287324748 addr of x[0]
   printf("ps is %u.\n", p);

   q = p;    // q = 4287324748

   printf("2. *x is %d, x is %u\n", *x, x);    //*x = 40, x = 4287324748 

   printf("3. value of q is %u, as addr q points at %d\n", q, *q);	//q = 4287324748, *q = 40

   q = &x[0];  //q = address of first element in x[] = 4287324748
   
   *q = 10;	//q points to first element in x[] which is now equal to 10.

   printf("4. value %d  x+1 is %u\n", *(x+1), x+1);	//x[1] = 51 and address is 4287324752
   printf("5. value %d  p+1 is %u\n", *(p+1), p+1);	//ditto from above
   printf("6. value %d  q+1 is %u\n", *(q+1), q+1);	//ditto from above

   for(i=0; i<N; i++)
      printf("7. main: value %d in addr %u\n", q[i], q+i);

   for(i=0; i<N; i++)
      printf("8. main: value %d in addr %u\n", x[i], x+i);

   Sub1(x);	//x[0] now equals 999

   for(i=0; i<N; i++)
      printf("9. main: value %d in addr %u\n", *(x+i), x+i);

   Sub2(x);	//x[3] now equals 222.

   return 0;
}

void Sub1(int y[N]) {
   int j;

   for(j=0; j<N; j++)
      printf("A. Sub1: value %d in addr %u\n", *(y+j), y+j);

   y[0] = 999;   	//x[0] now equals 999.
}

void Sub2(int *z) {
   int k;

   *(z+3) = 222; //x[3] now equals 222.  //address of x is passed into *z by reference, therefore,
		 			 // when *(z+3) is reassigned, points to 4 element in array x[].

   for(k=0; k<N; k++)
      printf("B. Sub2: value %d in addr %u\n", *(z+k), z+k);

   printf("C. z[3] is %d\n", z[3]);
}

