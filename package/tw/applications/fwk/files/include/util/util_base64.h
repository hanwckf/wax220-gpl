#ifndef __UTIL_BASE64_H__
#define __UTIL_BASE64_H__

#include "../fwk.h"


/*!\file util_base64.h
 * \brief Header file for base64 to binary conversion functions.
 *
 * These functions allow callers to convert base64 encoded strings to
 * binary buffers and back.
 *
 */



/** Encode a binary buffer in ASCII base64 encoding.
 * 
 * @param src    (IN)  Input binary buffer.
 * @param srclen (IN)  Length of input binary buffer.
 * @param dest   (OUT) This function will allocate a buffer and put the
 *             null terminated base64 ASCII string in it.  The caller is
 *             responsible for freeing this buffer.
 *
 * @return VOS_RET_E enum.
 */ 
VOS_RET_E utilB64_encode(const unsigned char *src, UINT32 srclen, char **dest);


/** Decode a null terminated base64 ASCII string into a binary buffer.
 * 
 * @param base64Str (IN) Input base64 ASCII string.
 * @param binaryBuf (OUT) This function will allocate a buffer and put
 *                   the decoded binary data into the buffer.  The caller
 *                   is responsible for freeing the buffer.
 * @param binaryBufLen (OUT) The length of the binary buffer.
 * 
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilB64_decode(const char *base64Str, UINT8 **binaryBuf, UINT32 *binaryBufLen);

#endif /*__UTIL_BASE64_H__*/
