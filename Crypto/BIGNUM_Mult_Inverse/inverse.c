/////////////////////////////////////////////////////////////
//Written by Nick Wantz
//CSC152 Cryptography
//Prof. Krovetz
//
//HW5 inverse.c
//
//This program is inteneded to take two command line args
//(x,y), x<y, and determine the multiplicative inverse
//of x.  Of the form x^-1 mod y.  prints -1 if no inverse.
////////////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>







void egcd(BIGNUM *result, BIGNUM *x, BIGNUM *y, BN_CTX *ctx){

	BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *c = BN_new();
	BIGNUM *tmpY = BN_new();
	BIGNUM *tmp = BN_new();	
	BIGNUM *tmpX = BN_new();

	BN_copy(tmpX, x);
	BN_copy(tmpY, y);	
	BN_zero(b);
	BN_one(c);


	while(! BN_is_zero(tmpY)){
	

		//store y in tmp for swap	
		BN_copy(tmp,tmpY);

		//a gets x/y(multiplied durring reconciling later), tmpY gets x%y(to be used as remainder 
		//in next iteration).
		BN_div(a,tmpY,tmpX,tmpY,ctx);
		
		//swapping egcd(x,y) for 
		BN_copy(tmpX,tmp);
		BN_copy(tmp,b);

		//reconciling linear combos as we go
		BN_mul(b,b,a,ctx);
		BN_sub(b,c,b);

		BN_copy(c,tmp);

	}


	 
	if(BN_is_negative(c)){
		BN_add(c,c,y);
	}

	BN_copy(result,c);

	BN_free(a);
	BN_free(b);
	BN_free(c);
	BN_free(tmp);
	BN_free(tmpY);
}


/*
void setup(const char x[20], const char y[20], unsigned char a[20], unsigned char b[20]){

	//int i=0;

	*a =(unsigned char) atoi(x);
	*b =(unsigned char) atoi(y);
	//for(i;i<20;i++){
	//	a[i] = x[i]-'0';
	//	b[i] = y[i]-'0';
	//}



}
*/


int main(int argc, const char* argv[]){

	//unsigned char a[20] = {0x00};
	//unsigned char b[20] = {0x00};


	BIGNUM *BN_new();
	BN_CTX *ctx = BN_CTX_new();


	BIGNUM *bna = NULL;
	BIGNUM *bnb = NULL;
	BIGNUM *result = BN_new();
	
	if(argc != 3){
		fprintf(stderr, "usage: %s insufficient args\n", argv[0]);
		return EXIT_FAILURE;
	}


	//printf("x:%d, y:%d.\n",*a,*b);
	//printf("arg1:%s, arg2:%s\n",argv[1],argv[2]);	
	//setup(argv[1],argv[2],a,b);
	//*a = (unsigned char) atoi(argv[1]);
	//*b = (unsigned char) atoi(argv[2]);

	//printf("x;%d, y:%d\n",*a,*b);

	//if(argv[1]>=argv[2]){
	//	fprintf(stderr, "usage: %s y must be greater than x\n", argv[0]);
	//	return EXIT_FAILURE;
	//}


	//BIGNUM *bna = BN_dec2bn(a, sizeof(a), NULL);
	//BIGNUM *bnb = BN_dec2bn(b, sizeof(b), NULL);


	//since no rhobustness check
	BN_dec2bn(&bna,argv[1]);
	BN_dec2bn(&bnb,argv[2]);
	

	//Could have implemented your version of this in the bn.txt file, but it is just a rhobustness check
	BN_gcd(result,bna,bnb,ctx);

	char *checkFlg = BN_bn2dec(result); 
	
	checkFlg = atoi(checkFlg);

	//if x and y inputs are not relatively prime, print -1 and fail.
	if(checkFlg!=1){
		fprintf(stderr,"-1\n");
		return EXIT_FAILURE;
	}

	//printf("bna:%d, bnb:%d after BIGNUMConversiong\n",*bna,*bnb);
	
	

	
	egcd(result, bna, bnb, ctx);


	//printf("x:%d, y:%d\n",*a,*b);	


	char *aString = BN_bn2dec(bna);
	char *bString = BN_bn2dec(bnb);
	char *resultString = BN_bn2dec(result);


	//printf("Multiplicative inverse of %s mod %s is %s.\n", aString,bString,resultString);
	printf("%s\n",resultString);

	BN_free(result);
	BN_free(bna);
	BN_free(bnb);


	return EXIT_SUCCESS;




}
