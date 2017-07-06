/* Initialize ctx. Key must be 16 or 32 bytes long. Length should be 16 or
 * 32 accordingly. Key should be random and kept secret. Nonce does not
 * need to be random or secret, but should be unique for each encryption
 * using the same key.
 */
void chacha20_setup(unsigned int ctx[16],
                    unsigned char key[],
                    unsigned int key_bytes,
                    unsigned char nonce[8]);
 
/* Write next 64-byte block to output. */
void chacha20_block(unsigned int ctx[16], unsigned char output[64]);
