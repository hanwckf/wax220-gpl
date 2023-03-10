#ifndef __UTIL_PSP_H__
#define __UTIL_PSP_H__


/*!\file util_psp.h
 * \brief Header file for the VOS Persistent Scratch Pad API.
 *  This is in the vos_util library.
 *
 * Persistent storage can be reserved and used by applications on a
 * first-come-first-served basis, meaning if applications request
 * more scratch pad area then available on the system, the later
 * requests will be denied.  
 *
 * On "top-boot" systems, there is 8KB of persistent scratch pad area
 * available.  On "bottom-boot" systems, there is no scratch pad area
 * available.  
 */

#include "../fwk.h"




/** Write data to persistent scratch pad.
 *
 * This function can be called multiple times for the same key.  If
 * a subsequent call with the same key has a larger data buffer,
 * the region in the scratch pad is grown if there is enough space.
 * If a subsequent call with the same key has a smaller data buffer,
 * the region in the scratch pad is shrunk and the extra data from
 * the previous, larger set is freed.  To delete the key and its
 * storage area from the scratch pad, call this function with the
 * key name with len set to 0.
 *
 * @param key (IN)  A string identifying the scratch pad area.  The key can
 *                  have a maximum of 15 characters.
 * @param buf (IN)  The data to write to the scratch pad.
 * @param bufLen (IN)  Length of Data.
 *
 * @return VOS_RET_E.
 */
VOS_RET_E utilPsp_set(const char *key, const void *buf, UINT32 bufLen);


/** Read data from persistent scratch pad.
 *
 * @param key (IN)  A string identifying the scratch pad area.  The key can
 *                  have a maximum of 15 characters.
 * @param buf (IN/OUT) User allocates a buffer to hold the read results and
 *                     passes it into this function.  On successful return,
 *                     the buffer contains data that was read.
 * @param bufLen (IN)  Length of given buffer.
 *
 * @return On success, the number of bytes returned to caller.
 *         If the key was not found or there is some other erro, 0 will be returned.
 *         If the key was found but the user provided
 *         buffer is not big enough to hold the data, a negative number will
 *         be returned and the caller's buffer is not modified at all;
 *         the absolute value of the negative number is the 
 *         number of bytes needed to hold the data.
 */
SINT32 utilPsp_get(const char *key, void *buf, UINT32 bufLen);


/** Get a list of all keys in the persistent scratch pad.
 *
 * @param buf (IN/OUT) User allocates a buffer to hold the read results and
 *                     passes it into this function.  On successful return,
 *                     the buffer contains a list of all keys in the 
 *                     persistent scratch pad.  Each key is terminated by
 *                     a NULL byte.
 *                     
 * @param bufLen (IN)  Length of given buffer.
 *
 * @return On success, the number of bytes returned to caller.
 *         If the persistent scratch pad is empty, 0 will be returned.
 *         If the user provided buffer is not big enough to hold all the keys,
 *         a negative number will be returned and the caller's buffer is not modified at all;
 *         the absolute value of the negative number is the 
 *         number of bytes needed to hold the data.
 */
SINT32 utilPsp_list(char *buf, UINT32 bufLen);


/** Zeroize all keys from scratch pad area.
 *
 * This has the effect of clearing the entire scratch pad.
 * Use with extreme caution.
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E utilPsp_clearAll(void);


#endif /* __UTIL_PSP_H__ */
