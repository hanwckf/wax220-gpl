#ifndef SHA256_H
#define SHA256_H

#include <stddef.h>

#define SHA256_BLOCK_SIZE 32  /* SHA256 outputs a 32 byte digest */

typedef struct {
    unsigned char data[64];     /* current 512-bit chunk of message data, just like a buffer */
    unsigned int datalen;       /* sign the data length of current chunk */
    unsigned long long bitlen;  /* the bit length of the total message */
    unsigned int state[8];      /* store the middle state of hash abstract */
} sha256_ctx;

void sha256_init(sha256_ctx *ctx);
void sha256_update(sha256_ctx *ctx, const char data[], size_t len);
void sha256_final(sha256_ctx *ctx, char hash[]);

#endif