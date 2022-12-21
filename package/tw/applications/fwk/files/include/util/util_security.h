#ifndef __UTIL_SECURITY_H__
#define __UTIL_SECURITY_H__

#include "../fwk.h"

/**
 * Random generate
 * @param pBuff the buffer for random
 * @param len the random size wanted to get
*/
void srand_random(char *pBuff, int len);

/**
 * Decryption using the private key
 * @param in Encrypt the data in the buffer
 * @param inLen The length of the buffer in which the data is encrypted.Normally it should be fixed at 256
 * @param out A buffer for storing decrypted data
 * @param outLen The actual length stored in out
 * @param pfxPath The PFX file path is the default PFX file when NULL
 * @param pfxPasswd Password for PFX files
*/
VOS_RET_E UTIL_RsaPrivateKeyDecrypt(char *in, int inLen, char *out, int* outLen, char *pfxPath, char* pfxPasswd);

/**
 * Encrypt the data with the  private key
 * @param in A buffer for unencrypted data
 * @param inLen The length of the buffer for unencrypted data.
 * @param out The buffer that holds the encrypted data
 * @param outLen The actual length stored in out. Normally it should be fixed at 256
 * @param pfxPath The PFX file path is the default PFX file when NULL
 * @param pfxPasswd Password for PFX files
*/
VOS_RET_E UTIL_RsaPrivateKeyEcrypt(char *in, int inLen, char *out, int* outLen, char *pfxPath, char* pfxPasswd);

/**
 * Encrypt the data with the public key
 * @param in A buffer for unencrypted data
 * @param inLen The length of the buffer for unencrypted data.
 * @param out The buffer that holds the encrypted data
 * @param outLen The actual length stored in out. Normally it should be fixed at 256
 * @param pfxPath The PFX file path is the default PFX file when NULL
 * @param pfxPasswd Password for PFX files
*/
VOS_RET_E UTIL_RsaPulicKeyEcrypt(char *in, int inLen, char *out, int* outLen, char *pfxPath, char* pfxPasswd);

/**
 * Decryption using the public key
 * @param in Encrypt the data in the buffer
 * @param inLen The length of the buffer in which the data is encrypted.Normally it should be fixed at 256
 * @param out A buffer for storing decrypted data
 * @param outLen The actual length stored in out
 * @param pfxPath The PFX file path is the default PFX file when NULL
 * @param pfxPasswd Password for PFX files
*/
VOS_RET_E UTIL_RsaPublicKeyDecrypt(char *in, int inLen, char *out, int *outLen, char *pfxPath, char* pfxPasswd);

/**
 * Calculates the sha1 value of the data in the buffer
 * @param in buffer
 * @param len The length of the buffer
 * @param out Hold the sha1 value in a buffer, fixed to 20
*/
VOS_RET_E UTIL_sha1FromBuffer(const char* in, int len, char* out);

/**
 * The total stream reads the data and calculates its sha1 value
 * @param in input stream 
 * @param out Hold the sha1 value in a buffer, fixed to 20
*/
VOS_RET_E UTIL_sha1FromStream(int inFd, char* out);

/**
 * Calculates the sha256 value of the data in the buffer
 * @param in buffer
 * @param len The length of the buffer
 * @param out Hold the sha1 value in a buffer, fixed to 32
*/
VOS_RET_E UTIL_sha256FromBuffer(const char* in, int len, char* out);

/**
 * The total stream reads the data and calculates its sha256 value
 * @param in input stream 
 * @param out Hold the sha1 value in a buffer, fixed to 32
*/
VOS_RET_E UTIL_sha256FromStream(int inFd, char* out);

/**
 * Using aes128-cbc encryption will decrypt the data in the buffer
 * @param key key
 * @param iv iv
 * @param src input
 * @param srcLen input len
 * @param dest output
 * @param destLen Actual output length
 * @param encrypt Encrypt or decrypt
*/
VOS_RET_E UTIL_aes128CbcBufferEncrypt(const char* key, char* iv, const char* src, int srcLen, char* dest, int *destLen, UBOOL8 encrypt);

/**
 * Using aes128-cbc encryption will decrypt the data in the stream
 * @param key key
 * @param iv iv
 * @param infd input
 * @param outfd output
 * @param encrypt Encrypt or decrypt
*/
VOS_RET_E UTIL_aes128CbcStreamEncrypt(const char* key, char* iv, int inFd, int outFd, UBOOL8 encrypt);

/**
 * Calculates the sha256 value of the data in the buffer
 * @param in buffer
 * @param inlen The length of the buffer
 * @param out Hold the sha256 value in a buffer
 * @param outlen The length of the out
*/
VOS_RET_E UTIL_hmacSHA256FromBuffer(char *key, const char *in, int inlen, char *out, int *outlen);

/**
 * Mess up the data.The scrambled data is called again and restored to the original data
 * @param in origin data
 * @param inlen origin data len
 * @param out Processed data
 * @param outlen out buffer len
*/
VOS_RET_E UTIL_bufferMessUp(const char *in, size_t inlen, char *out, size_t outlen);
#endif
