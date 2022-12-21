#ifndef __UTIL_HEXBINARY_H__
#define __UTIL_HEXBINARY_H__



/*!\file util_hexbinary.h
 * \brief Header file for HexBinary to Binary conversion functions.
 *
 * These functions allow callers to convert HexBinary strings to
 * binary buffers and back.
 *
 */


/** Convert binary buffer to hex encoding.
 * 
 * @param binaryBuf    (IN)  Input binary buffer.
 * @param binaryBufLen (IN)  Length of input binary buffer.
 * @param hexStr   (OUT) This function will allocate a buffer and put the
 *                       null terminated hex string in it.  The caller is
 *                       responsible for freeing this buffer.
 *
 * @return VOS_RET_E enum.
 */ 
VOS_RET_E util_binaryBufToHexString(const UINT8 *binaryBuf, UINT32 binaryBufLen, char **hexStr);


/** Convert a null terminated hex string into a binary buffer.
 * 
 * @param hexStr (IN) Input hex string. There must be an even number of
 *                    characters in the string.  This means if the first
 *                    value is less than 128, it must have a preceding 0.
 * @param binaryBuf (OUT) This function will allocate a buffer and put
 *                   the decoded binary data into the buffer.  The caller
 *                   is responsible for freeing the buffer.
 * @param binaryBufLen (OUT) The length of the binary buffer.
 * 
 * @return VOS_RET_E enum.
 */
VOS_RET_E util_hexStringToBinaryBuf(const char *hexStr, UINT8 **binaryBuf, UINT32 *binaryBufLen);



#endif  /* __UTIL_HEXBINARY_H__ */
