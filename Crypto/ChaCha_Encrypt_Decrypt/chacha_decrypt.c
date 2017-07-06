/////////////////////////////////
//Written by Nick Wantz
//CSc 152 Cryptography
//HW2 chacha_decrypt.c
//Prof. Krovetz
//
//This program is used to decrypt
//the cypher text created using
//chacha_encrypt.c
//
//
//
/////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chacha20.h"

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
                else    break;

                b = b<<4;
                c = hex[2*i+1];

                if (c >= '0' && c <= '9') b += c - '0';
                else if (c >= 'A' && c <= 'F') b += c - 'A' + 10;
                else if (c >= 'a' && c <= 'f') b += c - 'a' + 10;
                else    break;
                result[i] = (unsigned char)b;
        }
        return i;
}
	

void chacha(const unsigned char key[32], unsigned char nonceIn[8], unsigned len, unsigned char *out){
	
	unsigned int i;
	unsigned int context[16];
	unsigned char tmp[32];
	//unsigned char nonce[8];

	unsigned int length = strlen(key);


	unsigned int lenKey = hex_to_bytes(tmp, key, length); 	
	
	for(i=lenKey; i<32; i++){
		tmp[i] = 0x00;
	}
	
	
	chacha20_setup(context, tmp, 32, nonceIn);
	
	chacha20_block(context, out);
	
}




int main(int argc, const char* argv[]){

	unsigned char buf[BUFSIZE];
	size_t bytes_read = 0;
	unsigned char out[BUFSIZE];
	unsigned char xor[BUFSIZE];
	unsigned char nonce[8]; 
	unsigned char nonceRead[16];
	unsigned int i;

	if(argc !=2){
		fprintf(stderr, "usage: %s arg\n", argv[0]);
		return EXIT_FAILURE;
	}

	fread(nonceRead, 1, 16, stdin);//reads first 16 bytes
	unsigned int a = hex_to_bytes(nonce, nonceRead, 16);
	
	do{
		bytes_read = fread(buf, 1, BUFSIZE, stdin);
		if(bytes_read>0){
			chacha(argv[1], nonce, bytes_read, out);
			for(i=0; i<bytes_read; i++){
				xor[i] = (char)(buf[i] ^ out[i]);
				printf("%c", xor[i]);
			//	printf("%c", out[i]);
			}
		}
	}while(bytes_read == BUFSIZE);

	return EXIT_SUCCESS;
}




