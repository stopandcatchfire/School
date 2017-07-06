////////////////////////////////////////////////////
//Written by Nick Wantz
//CSC152 Cryptography
//Prof. Krovetz
//
//HW2-1 chacha_encrypt 
//
//This program is intended to take command line args
//for a key and nonce and read from a txt file thus
//encrypting the text file.
//
//
//
////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include "chacha20.h"
#include <string.h>

#define BUFSIZE 64 



int hex_to_bytes(unsigned char result[], const char hex[], unsigned int hex_len){
	unsigned int i;
	if(hex_len % 2 == 1)
		return 0;
	for(i=0; i<hex_len/2; i++){
		char b, c = hex[2*i];
		if (c >= '0' && c <= '9') b = c - '0';
		else if (c >= 'A' && c <= 'F') b = c - 'A' + 10;
		else if (c >= 'a' && c <= 'f') b = c - 'a' + 10;
		else	break;

		b = b<<4;
		c = hex[2*i+1];
		
		if (c >= '0' && c <= '9') b += c - '0';
		else if (c >= 'A' && c <= 'F') b += c - 'A' + 10;
		else if (c >= 'a' && c <= 'f') b += c - 'a' + 10;
		else	break;
		result[i] = (unsigned char)b;
	}
	return i;
}

void chacha(const char inputKey[32], unsigned char nonceIn[8], unsigned len, unsigned char *out){

	unsigned int i;			//for loop to add "0" bytes 
	unsigned int context[16];	//ctx[16] for chacha
	unsigned char key[32];		//for storing key after hex conversion
	//unsigned char nonce[8];

	//length of key from command line
	unsigned int length = strlen(inputKey);	

		
	//convert ascii to bytes, returns length in bytes from 4-bit hex symbols 
	unsigned int lenKey = hex_to_bytes(key, inputKey, length);
	
	//adding hex 0's to fill in remaining 32-lenKey bytes	
	for(i=lenKey; i<32; i++){
		key[i] = 0x00;
	}
	
	//sending ctx buffer, key, 32 byte request, and nonce
	chacha20_setup(context, key, 32, nonceIn);
	//writing to out for xor encryption
	chacha20_block(context, out);

	
}

int main(int argc, const char* argv[]) {

	unsigned char buf[BUFSIZE];
	size_t bytes_read = 0;
	unsigned char out[BUFSIZE];
	unsigned char xor[BUFSIZE];
	unsigned char nonce[8];
	unsigned int i;

	//assuming specs only take in 3 args, (in order) chacha_encrypt, key, nonce
	if(argc != 3){
		fprintf(stderr, "usage: %s arg\n", argv[0]);
		return EXIT_FAILURE;
	}

	//print nonce to beginning of ciphertext file	
	fprintf(stdout, "%s", argv[2]);	

	//since it is assumed that nonce is guaranteed to be 16 bytes, I decided to do
	//the conversion here, since the chacha "signature" for nonce is 8 bytes	
	unsigned int a = hex_to_bytes(nonce, argv[2], 16);

	//using fread to take in BUFSIZE(64) bytes at a time from input, if bytes were read,
	//call chacha and loop through the plaintext and chacha cypher bytes xor ing them
	//and storing in xor, followed by a print to stdout 
	do {
		bytes_read = fread(buf, 1, BUFSIZE, stdin);
		if(bytes_read>0){
			chacha(argv[1], nonce, bytes_read, out);
			for(i=0; i<bytes_read; i++){
				xor[i] = (char)(buf[i] ^ out[i]);
				fprintf(stdout, "%c", xor[i]);
				//fprintf(stdout, "%c", out[i]);
			}
			
		}
	}while(bytes_read == BUFSIZE);
			 

	return EXIT_SUCCESS;
}
