////////////////////////////////////////////////////
//Written by Nick Wantz
//CSC152 Cryptography
//Prof. Krovetz
//
//HW3-1 aes256_ctr_encrypt 
//
//This program is intended to take command line args
//for a key and nonce and read from a txt file thus
//encrypting the text file.
//Uses AES with 256-bit key and ctr mode encryption.
//
//
////////////////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wmmintrin.h>

#define BUFSIZE 16

#define EXPAND_ASSIST(v1,v2,v3,v4,shuff_const,aes_const)                    \
    v2 = _mm_aeskeygenassist_si128(v4,aes_const);                           \
    v3 = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(v3),              \
                                         _mm_castsi128_ps(v1), 16));        \
    v1 = _mm_xor_si128(v1,v3);                                              \
    v3 = _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(v3),              \
                                         _mm_castsi128_ps(v1), 140));       \
    v1 = _mm_xor_si128(v1,v3);                                              \
    v2 = _mm_shuffle_epi32(v2,shuff_const);                                 \
    v1 = _mm_xor_si128(v1,v2)




static void AES_256_Key_Expansion(const unsigned char userkey[32], __m128i key[15])
{
    __m128i x0,x1,x2,x3;
    key[0] = x0 = _mm_loadu_si128((__m128i*)userkey   );
    key[1] = x3 = _mm_loadu_si128((__m128i*)(userkey+16));
    x2 = _mm_setzero_si128();
    EXPAND_ASSIST(x0,x1,x2,x3,255,1);  key[2]  = x0;
    EXPAND_ASSIST(x3,x1,x2,x0,170,1);  key[3]  = x3;
    EXPAND_ASSIST(x0,x1,x2,x3,255,2);  key[4]  = x0;
    EXPAND_ASSIST(x3,x1,x2,x0,170,2);  key[5]  = x3;
    EXPAND_ASSIST(x0,x1,x2,x3,255,4);  key[6]  = x0;
    EXPAND_ASSIST(x3,x1,x2,x0,170,4);  key[7]  = x3;
    EXPAND_ASSIST(x0,x1,x2,x3,255,8);  key[8]  = x0;
    EXPAND_ASSIST(x3,x1,x2,x0,170,8);  key[9]  = x3;
    EXPAND_ASSIST(x0,x1,x2,x3,255,16); key[10] = x0;
    EXPAND_ASSIST(x3,x1,x2,x0,170,16); key[11] = x3;
    EXPAND_ASSIST(x0,x1,x2,x3,255,32); key[12] = x0;
    EXPAND_ASSIST(x3,x1,x2,x0,170,32); key[13] = x3;
    EXPAND_ASSIST(x0,x1,x2,x3,255,64); key[14] = x0;
}


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

void setup(const char inputKey[64], const char nonceIn[16], unsigned char key[32], unsigned char nonce[16]){

	int i;			//for loop to add "0" bytes 
	
	//length of key from command line
	unsigned int length = strlen(inputKey);	
		
	//convert ascii to bytes, returns length in bytes from 4-bit hex symbols 
	unsigned int lenKey = hex_to_bytes(key, inputKey, length);

	//handles nonce, writes to output file
	//NOTE: since using ctr mode encryption, initializing nonce[16]={0}
	//last 8 bytes of array will be the counter, first 8 will
	//be used to hold nonce.  
	unsigned int grbg = hex_to_bytes(nonce, nonceIn, 16);
	
	//Writes original nonce to file
	for(i=0; i<8; i++){
		fprintf(stdout, "%c", nonce[i]);
	}


}

void AES_round(__m128i key[15], unsigned char block[16], unsigned char *out){
	int i;
	__m128i block_reg = _mm_loadu_si128((__m128i *)block); 	//loads plaintext block into register

	//initial xor with key[0]
	block_reg ^= key[0];	

	//loop to do 13 rounds with key and block 15th round done with aesenclast...
	for(i=1; i<14; i++){
		block_reg = _mm_aesenc_si128(block_reg, key[i]);	
	}
	block_reg = _mm_aesenclast_si128(block_reg, key[14]);		//final round skips mixColumns so separate
	_mm_storeu_si128((__m128i *)out, block_reg);			//Store result of all rounds in out to be written to file as ciphertext
}


//Tried a few different implementations of how to do the counter.
//Found this online (modified to fit constraints)
//http://www.vbforums.com/showthread.php?565448-RESOLVED-Increment-byte-by-0x01
//Originally tried to use a for loop and then shift the index if it hit the limit,
//But this does it recursively and looks cleaner (plus accounts for endianess and pretty similar to how EVP does it in 
//their specs).  Should add a catch if a file to encrypt is too large if going into production.
void ctrLoop(unsigned char ctr[16], int index){
	
	if(index>7){	
		if(ctr[index] == 255){
			ctr[index] = 0;
			if(index>0){
				ctrLoop(ctr, index-1);
			}
		}
		else{
			ctr[index]++;
		}
	}
}

int main(int argc, const char* argv[]) {

	unsigned char buf[BUFSIZE];
	size_t bytes_read = 0;
	unsigned char out[BUFSIZE];
	unsigned char xor[BUFSIZE];
	unsigned char nonce[16] = {0};		//0ing out to ensure easy inc handling
	unsigned char key[32] = {0};		//for storing key after hex conversion
	unsigned int i;

	//new with aes implementation
	__m128i expansion_key[15];

	//assuming specs only take in 3 args, (in order) aes256_encrypt_ctr, key, nonce
	if(argc != 3){
		fprintf(stderr, "usage: %s insufficient args\n", argv[0]);
		return EXIT_FAILURE;
	}

	//check for oversized keys/nonces/bad user input


	//setup for key and nonce from stdin, size casting prevents overflow, 
	setup(argv[1], argv[2], key, nonce);

	//takes user inputted key and stores it in an array of SSE registers.
	AES_256_Key_Expansion(key, expansion_key);
	memset(key, 0, sizeof(key));		//0 out key to hide info in memory
	  	
	//using fread to take in BUFSIZE(16) bytes at a time from input, if bytes were read,
	//call chacha and loop through the plaintext and chacha cypher bytes xor ing them
	//and storing in xor, followed by a print to stdout 
	do {
		bytes_read = fread(buf, 1, BUFSIZE, stdin);
		if(bytes_read>0){
			//writes to out bytes to be printed
			AES_round(expansion_key, nonce, out);					
			for(i=0; i<bytes_read; i++){
				out[i] ^= buf[i];			//By using nonce and expansion keys run threough AES
				fprintf(stdout, "%c", out[i]);		//to xor the plaintext, no padding is ever needed
			}
			//TODO: increment ctr portion of nonce.
			ctrLoop(nonce, 15);
		}
	}while(bytes_read == BUFSIZE);
			 

	return EXIT_SUCCESS;
}
