#ifndef __UTIL_FIL_H__
#define __UTIL_FIL_H__

#define KILOBYTE 1024

/*!\file util_fil.h
 * \brief Header file for file and directory utilities functions.
 */


/** Return true if the filename exists.
 *
 * @param filename (IN) full pathname to the file.
 *
 * @return TRUE if the specified file exists.
 */
UBOOL8 utilFil_isFilePresent(const char *filename);



/** Return the size of the file.
 *
 * @param filename (IN) full pathname to the file.
 *
 * @return -1 if the file does not exist, otherwise, the file size.
 */
SINT32 utilFil_getSize(const char *filename);



/** Copy the contents of the file to the specified buffer.
 *
 * @param filename (IN) full pathname to the file.
 * @param buf     (OUT) buffer that will hold contents of the file.
 * @bufSize    (IN/OUT) On input, the size of the buffer, on output
 *                      the actual number of bytes that was copied
 *                      into the buffer.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilFil_copyToBuffer(const char *filename, UINT8 *buf, UINT32 *bufSize);


/** Write the specified string into the specified proc file.
 *
 * @param procFile (IN) Name of the proc file.
 * @param s        (IN) String to write into the proc file.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilFil_writeToProc(const char *procFilename, const char *s);


/** Write the buffer into the specified file.
 *
 * @param filename (IN) Name of the file.
 * @param buf      (IN) Buffer to write.
 * @param bufLen   (IN) Length of buffer.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilFil_writeBufferToFile(const char *filename, const UINT8 *buf, UINT32 bufLen);



/** Write the string into the end of specified file.
 *
 * @param filename (IN) Name of the file.
 * @param buf      (IN) string to write.
 * @param bufLen   (IN) Length of buffer.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilFil_writeToFileEnd(const char *filename, const char *s);


/** Remove specified directory.  If there are any files or sub-dirs in the
 * directory, they will be silently removed.
 *
 * @param dirname (IN) Name of the directory to remove.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilFil_removeDir(const char *dirname);


VOS_RET_E utilFil_chownDir(const char *dirname, int useId);



/** Create the specified directory.
 *
 * @param dirname (IN) Name of the directory to create.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilFil_makeDir(const char *dirname);


/** convert the size into KiloBytes 
 *
 * @param nblks (IN) number of blocks.
 * @param blkSize (IN) size of each block in bytes.
 *
 * @return UINT32 (size in Kilo Bytes)
 */

UINT32 utilFil_scaleSizetoKB(long nblks, long blkSize);
#endif /* __UTIL_FIL_H__ */
