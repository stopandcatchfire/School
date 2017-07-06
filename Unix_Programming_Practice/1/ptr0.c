// ptr0.c
//
// complete the code to print things and whenever an
// assignment occurs, and comment out as variable gets
// changed
//
// compile in 32-bit mode: gcc -m32 ptr0.c
//
// Nick Wantz
// CSC 60, ChangW, TuTh 5:30 - 6:45
// HW 1 / ptr0.c

#include <stdio.h> 

int main() {
   int i, j, *p, *q, **r;

   printf("Make sure it's 4 (bytes): size of int * is %i\n",
      sizeof(int *));

printf("addr: %u %u %u %u %u\n", &i, &j, &p, &q, &r);
// give p an address (p then points there),
// *p = 33 or *p = i are illegal, only p = 0 is valid to denote null
   i = 33;             // i = 33
   p = &i;             // p = ? (write actual runtime addr here, addr of i)

//
//addr: &i=4291363996, &j=4291363992, &p=4291363988, &q=4291363988, &r=4291363980 
//
// print *p = 4291363996
   printf("*p is %u\n", *p);
// print 2**P = 66
   printf("2**p is %u\n", 2**p);
// print p = 4291363996
   printf("p is %u\n", p);
// print &i = 4291363996
   printf("&i is %u\n", &i);
// print &p = 4291363988
   printf("&p is %u\n", &p);

   j = (int)p;         // j = address of p = 4291363996

// print j = 4291363988
   printf("j is %u\n", j);
// print *(int *)j = 33
   printf("*(int *)j is %u\n", *(int *)j);

   *p = 44;            // i = 44

// print *p = 44
   printf("*p is %u\n", *p);
// print p = 4291363996
   printf("p is %u\n", p);
// print &p = 4291363988
   printf("&p is %u\n", &p);

//**************************************************************************
   i = 5;              // i = 5 
   j = 7;              // j = 7
   q = p;              // q = address of i = 4291363996 

// print &i = 4291363996
   printf("&i is %u\n", &i);
// print q = 4291363996
   printf("q is %u\n", q);
// print &q = 4291363984
   printf("&q is %u\n", &q);
// print *q = 5
   printf("*q is %u\n", *q);


   r = &q;             // r = address of q = 4291363984

// print r = 4291363984
   printf("r is %u\n", r);
// print &r = 4291363980
   printf("&r is %u\n", &r);
// print *r = 4291363996
   printf("*r is %u\n", *r);
// print **r = 5
   printf("**r is %u\n", **r);

   *r = &j;            // r points to address of j = 4291363992

// print r = 4291363984
   printf("r is %u\n", r);
// print &r = 4291363980
   printf("&r is %u\n", &r); 
// print *r = 4291363992
   printf("*r is %u\n", *r);
// print **r = 7
   printf("**r is %u\n", **r);

// print &j = 4291363992
   printf("&j is %u\n", &j);
// print q = 4291363992
   printf("q is %u\n", q);
// print &q = 4291363984
   printf("&q is %u\n", &q);
// print *q = 7
   printf("*q is %u\n", *q);

   return 0;
}

