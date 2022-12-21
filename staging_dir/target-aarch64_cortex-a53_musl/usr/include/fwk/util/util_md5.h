/*
 ***********************************************************************
 ** util_md5.h -- header file for implementation of MD5               **
 ** RSA Data Security, Inc. MD5 Message-Digest Algorithm              **
 ** Created: 2/17/90 RLR                                              **
 ** Revised: 12/27/90 SRD,AJ,BSK,JT Reference C version               **
 ** Revised (for MD5): RLR 4/27/91                                    **
 **   -- G modified to have y&~z instead of y&z                       **
 **   -- FF, GG, HH modified to add in last register done             **
 **   -- Access pattern: round 2 works mod 5, round 3 works mod 3     **
 **   -- distinct additive constant for each step                     **
 **   -- round 4 added, working mod 7                                 **
 ***********************************************************************
 */

/*
 ***********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved.  **
 **                                                                   **
 ** License to copy and use this software is granted provided that    **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message-     **
 ** Digest Algorithm" in all material mentioning or referencing this  **
 ** software or this function.                                        **
 **                                                                   **
 ** License is also granted to make and use derivative works          **
 ** provided that such works are identified as "derived from the RSA  **
 ** Data Security, Inc. MD5 Message-Digest Algorithm" in all          **
 ** material mentioning or referencing the derived work.              **
 **                                                                   **
 ** RSA Data Security, Inc. makes no representations concerning       **
 ** either the merchantability of this software or the suitability    **
 ** of this software for any particular purpose.  It is provided "as  **
 ** is" without express or implied warranty of any kind.              **
 **                                                                   **
 ** These notices must be retained in any copies of any part of this  **
 ** documentation and/or software.                                    **
 ***********************************************************************
 */

#ifndef __UTIL_MD5_H__
#define __UTIL_MD5_H__

#include "../fwk.h"

/* Data structure for MD5 (Message-Digest) computation */
typedef struct {
  UINT32 i[2];                   /* number of _bits_ handled mod 2^64 */
  UINT32 buf[4];                                    /* scratch buffer */
  unsigned char in[64];                              /* input buffer */
  unsigned char digest[16];     /* actual digest after UTIL_md5Final call */
} UTIL_MD5_CTX_T;

void UTIL_md5Init (UTIL_MD5_CTX_T *mdContext);
void UTIL_md5Update (UTIL_MD5_CTX_T *mdContext, unsigned char *inBuf, unsigned int inLen);
void UTIL_md5Final (unsigned char hash[], UTIL_MD5_CTX_T *mdContext);

#endif /* __UTIL_MD5_H__ */
