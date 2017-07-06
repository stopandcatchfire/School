// ptr2.c

#include <stdio.h>

ChangeX(int a) { a = 500; }

Change0(int *p) { *p = 2; } // can change the value in the addr of what p has

Change1(int *p) { int i = 10; p = &i; } // can't change the addr p points to to i's

Change2(int **dog) { int i = 20; *dog = &i; } // unless p's addr is passed over

Change3(int *p) { *p = 30; } // can change value in the addr of what p has

Change4(int *p) { int i = 40; p = &i; } // can't change addr p points to to i's

Change5(int **p) { int i = 50; *p = &i; } // unless p's addr is passed over

int main() {
   int i, j, *p;

   i = 1; j = 2; p = &i;

   printf("Before: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);

// i = 1  j = 2  p = 4292067036  *p = 1

   ChangeX( i ); 
   
   printf("After ChangeX: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 1  j = 2  p = 4292067036  *p = 1

   Change0( p );
   printf("After Change0: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 2  j = 2  p = 4292067036  *p = 2

   Change1( p );
   printf("After Change1: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 2  j = 2  p = 4292067036  *p = 2

   Change2( &p );
   printf("After Change2: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 20  j = 2  p = 4292066996  *p = 20

// ********************************************************
   j=3; p=&j;	//p = address of j = 4292067032

   printf("Before: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 2  j = 3  p = 4292067032  *p = 3
	
   Change3( p );
   printf("After Change3: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 2  j = 30  p = 4292067032  *p = 30

   Change4( p );
   printf("After Change4: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 2  j = 30  p = 4292067032  *p = 30
   
   Change5( &p );
   printf("After Change5: *p=%u  p=%u  &p=%u\n\n", *p, p, &p);
// i = 2  j = 30  p = 4292066996  *p = 50
   

   return 0;
}

