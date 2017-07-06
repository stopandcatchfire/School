///////////////////////////////////////
//
//
//
//
//
//
///////////////////////////////////////


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

//void setup




int main(int argc, const char* argv[]){

	unsigned char key[32];
	int len = 0, i;

	if(argc != 3){
		fprintf(stderr, "usage: %s arg\n", argv[0]);
		return EXIT_FAILURE;
	}

	len = strlen(argv[1]);
	strcpy(key, argv[1]);
	
	for(i=len; i<64; i++){
		strcat(key, '0');
	}

	printf("%s\n", key);
}
