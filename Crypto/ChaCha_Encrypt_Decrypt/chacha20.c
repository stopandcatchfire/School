/* This code assumes 32-bit ints.  Here's a simple check for this. */
#include <limits.h>
#if (UINT_MAX == 65535U) || (UINT_MAX != 4294967295U)
#error -- this implementation requires "unsigned int" to be 32 bits
#endif
 
unsigned int rotate_left(unsigned int v, unsigned n) {
    return (v << n) | (v >> (32 - n));
}
 
unsigned int read_little_endian(unsigned char p[]) {
    return ((unsigned int)(p[0]) <<  0) | ((unsigned int)(p[1]) <<  8) |
           ((unsigned int)(p[2]) << 16) | ((unsigned int)(p[3]) << 24);
}
 
void write_little_endian(unsigned char b[], unsigned int i) {
    b[0] = (unsigned char)(i >>  0);
    b[1] = (unsigned char)(i >>  8);
    b[2] = (unsigned char)(i >> 16);
    b[3] = (unsigned char)(i >> 24);
}
 
void chacha20_setup(unsigned int ctx[16],
                    unsigned char key[],
                    unsigned int key_bytes,
                    unsigned char nonce[8])
{
    char *constants = (key_bytes == 32) ? "expand 32-byte k" : "expand 16-byte k";
    ctx[0] = read_little_endian((unsigned char *)constants + 0);
    ctx[1] = read_little_endian((unsigned char *)constants + 4);
    ctx[2] = read_little_endian((unsigned char *)constants + 8);
    ctx[3] = read_little_endian((unsigned char *)constants + 12);
    ctx[4] = read_little_endian(key + 0);
    ctx[5] = read_little_endian(key + 4);
    ctx[6] = read_little_endian(key + 8);
    ctx[7] = read_little_endian(key + 12);
    ctx[8] = read_little_endian(key + 16 % key_bytes);
    ctx[9] = read_little_endian(key + 20 % key_bytes);
    ctx[10] = read_little_endian(key + 24 % key_bytes);
    ctx[11] = read_little_endian(key + 28 % key_bytes);
    ctx[12] = 0;
    ctx[13] = 0;
    ctx[14] = read_little_endian(nonce+0);
    ctx[15] = read_little_endian(nonce+4);
}
 
#define QUARTERROUND(x, a, b, c, d)                    \
    x[a] += x[b]; x[d] = rotate_left(x[d] ^ x[a], 16); \
    x[c] += x[d]; x[b] = rotate_left(x[b] ^ x[c], 12); \
    x[a] += x[b]; x[d] = rotate_left(x[d] ^ x[a], 8);  \
    x[c] += x[d]; x[b] = rotate_left(x[b] ^ x[c], 7);
 
void chacha20_block(unsigned int ctx[16], unsigned char output[64])
{
    unsigned int i, temp[16];
    for (i = 0; i < 16; i++)
        temp[i] = ctx[i];
    for (i = 0; i < 10; i++) {
        QUARTERROUND(temp, 0, 4, 8, 12)
        QUARTERROUND(temp, 1, 5, 9, 13)
        QUARTERROUND(temp, 2, 6, 10, 14)
        QUARTERROUND(temp, 3, 7, 11, 15)
        QUARTERROUND(temp, 0, 5, 10, 15)
        QUARTERROUND(temp, 1, 6, 11, 12)
        QUARTERROUND(temp, 2, 7, 8, 13)
        QUARTERROUND(temp, 3, 4, 9, 14)
    }
    for (i = 0; i < 16; ++i)
        write_little_endian(output+4*i, temp[i] + ctx[i]);
    if (!++ctx[12] && !++ctx[13] && !++ctx[14]) ++ctx[15];
}
