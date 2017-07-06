/////////////////////////////////
//Written by Nick Wantz
//CSc 152 Cryptography
//HW3- aes256_ctr_decrypt.c
//Prof. Krovetz
//
//This program is used to decrypt
//the cypher text created using
//aes256_ctr_encrypt.c.
//Uses EVP instruction set from 
//openSSL.
//
//
//
/////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define BUFSIZE 16



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

void setup(const char inputKey[64], unsigned char key[32]){
	
	//length of input key from command line	
	unsigned int length = strlen(inputKey);
	
	//length of key coming out of hex to byte conversion
	unsigned int lenKey = hex_to_bytes(key, inputKey, length);

}




int main(int argc, const char* argv[]){

	unsigned char buf[BUFSIZE];
	int bytes_read = 0;			//changed to type int because thats what EVP expects and I feel its safer than direct cast.
	unsigned char out[BUFSIZE];
	unsigned char nonce[16] = {0}; 
	unsigned char key[32] = {0};
	unsigned int i;
	
	//new with EVP SSL implementation
	EVP_CIPHER_CTX ctx;
	


	//checks input, only args for decrypt should be key
	if(argc !=2){
		fprintf(stderr, "usage: %s insufficient args\n", argv[0]);
		return EXIT_FAILURE;
	}

	fread(nonce, 1, 8, stdin);//reads first 8 bytes
	//setup for key, nonce already read in.
	setup(argv[1], key);
	
	
	
	//ctx = EVP_CIPHER_CTX_new();
	EVP_CIPHER_CTX_init(&ctx);
	//assuming checks on nonce and key sizes already done
	EVP_CipherInit_ex(&ctx, EVP_aes_256_ctr(), NULL, key, nonce, 0);
	
	//Reads 16 byte buffer in, checks if 0 or less.  Runs EVP_CipherUpdate 
	do{
		bytes_read = fread(buf, 1, BUFSIZE, stdin);
		if(bytes_read<=0) break;
		EVP_CipherUpdate(&ctx, out, &bytes_read, buf, bytes_read);
		fwrite(out, 1, bytes_read, stdout);
	}while(bytes_read == BUFSIZE);

	//Runs EVP_CipherFinal execution, if it fails frees ctx and exits.
	EVP_CipherFinal_ex(&ctx, out, &bytes_read);
	fwrite(out, 1, bytes_read, stdout);

	//cleans up ctx variables that could potentially leak information.
	EVP_CIPHER_CTX_cleanup(&ctx);

	return EXIT_SUCCESS;
}



