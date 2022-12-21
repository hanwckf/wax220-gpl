#ifndef __VOS_MEM_H__
#define __VOS_MEM_H__

#include "vos_defs.h"

/*!\file vos_mem.h
 * \brief Header file for the VOS Memory Allocation API.
 * This is in the vos_util library.
 */

/** zeroize the buffer before returning it to the caller. */
#define ALLOC_ZEROIZE          0x01

/** allocate memory in the shared memory region.  This should only bed
 * used by internal cmc_core and mdm libraries when creating nodes in
 * the MDM tree.
 */
#define ALLOC_SHARED_MEM       0x02

#define VOS_MALLOC(size)    vosMem_alloc(size, ALLOC_ZEROIZE, __FUNCTION__, __LINE__)
#define VOS_MALLOC_FLAGS(size, flags)    vosMem_alloc(size, flags, __FUNCTION__, __LINE__)
#ifndef PFM_ALLOW_MALLOC
//#undef malloc
//#define malloc    ("Please use VOS_MALLOC or VOS_MALLOC_FLAGS to replace malloc")
#endif /* PFM_ALLOW_MALLOC */

#define VOS_REALLOC(buf, size)    vosMem_realloc(buf, size, __FUNCTION__, __LINE__)
#ifndef PFM_ALLOW_REALLOC
//#undef realloc
//#define realloc    ("Please use VOS_REALLOC to replace realloc")
#endif /* PFM_ALLOW_REALLOC */

#define VOS_CALLOC(nmemb, size)    vosMem_alloc((nmemb) * (size), ALLOC_ZEROIZE, __FUNCTION__, __LINE__)
#ifndef PFM_ALLOW_CALLOC
//#undef calloc
//#define calloc    ("Please use VOS_CALLOC to replace calloc")
#endif /* PFM_ALLOW_CALLOC */

#define VOS_FREE(buf)    vosMem_free(buf, __FUNCTION__, __LINE__)
#ifndef PFM_ALLOW_FREE
//#undef free
//#define free    ("Please use VOS_FREE to replace free")
#endif /* PFM_ALLOW_FREE */

#define VOS_STRDUP(buf)    vosMem_strdup(buf, __FUNCTION__, __LINE__)
#define VOS_STRDUP_FLAGS(buf, flags)    vosMem_strdupFlags(buf, flags, __FUNCTION__, __LINE__)
#ifndef PFM_ALLOW_STRDUP
//#undef strdup
//#define strdup    ("Please use VOS_STRDUP or VOS_STRDUP_FLAGS to replace strdup")
#endif /* PFM_ALLOW_STRDUP */

#define VOS_STRNDUP(buf, maxlen)    vosMem_strndup(buf, maxlen, __FUNCTION__, __LINE__)
#define VOS_STRNDUP_FLAGS(buf, maxlen, flags)    vosMem_strndupFlags(buf, maxlen, flags, __FUNCTION__, __LINE__)
#ifndef PFM_ALLOW_STRNDUP
//#undef strndup
//#define strndup    ("Please use VOS_STRNDUP or VOS_STRNDUP_FLAGS to replace strndup")
#endif /* PFM_ALLOW_STRNDUP */


#define VOS_IS_ALLOCED_MEM(buf)    vosMem_isAllocedMem(buf, __FUNCTION__, __LINE__)


#ifdef __cplusplus
extern "C" {
#endif

/** allocate memory
 * @param size The number of bytes to allocate.
 * @param allocFlags See ALLOC_xxx for possible flags.
 * @return On succcess, a buffer of requested size is returned.
 * On error, NULL is returned.
 */
void *vosMem_alloc(UINT32 size, UINT32 allocFlags, const char *function, UINT32 line);


/** Increase buffer size of previously allocated memory.
 *
 * The same allocFlags that was used to allocate the original buffer
 * will be used to allocate the new buffer.
 * Note that unlike the LINUX realloc, vosMem_realloc cannot
 * take a NULL buffer.  If you have a null pointer and you want
 * to allocate a buffer, use vosMem_alloc instead.
 * Like the LINUX realloc, if size is 0, this function is equivalent
 * to vosMem_free.
 * In the future, if size is less than the original buffer size,
 * the buffer will be shrunk.  Currently, vosMem_realloc does not
 * shrink buffer size, it only increase buffer size.
 *
 * @param buf (IN) previously allocated buffer.
 * @param size (IN) The new buffer size.
 *
 * @return On succcess, a buffer of requested size is returned with
 *         the contents of the original buffer, which is freed.
 *         On error, NULL is returned but the original buffer is left unmodified.
 */
void *vosMem_realloc(void *buf, UINT32 size, const char *function, UINT32 line);


/** Free previously allocated memory
 * @param buf Previously allocated buffer.
 */
void vosMem_free(void *buf, const char *function, UINT32 line);


/** Free a buffer and set the pointer to null.
 */
#define VOS_MEM_FREE_BUF_AND_NULL_PTR(p) \
   do { \
      if ((p) != NULL) {VOS_FREE((p)); (p) = NULL;}   \
   } while (0)
   

/** Free the existing char pointer and set it to a copy of the specified string.
 */
#define VOS_MEM_REPLACE_STRING(p, s) \
   do {\
      if ((p) != NULL) {VOS_FREE((p));} \
      (p) = VOS_STRDUP((s)); \
   } while (0)


/** Free the existing char pointer and set it to a copy of the specified string
 *  and specify the way the string is allocated.
 */
#define VOS_MEM_REPLACE_STRING_FLAGS(p, s, f) \
   do {\
      if ((p) != NULL) {VOS_FREE((p));} \
      (p) = VOS_STRDUP_FLAGS((s), (f)); \
   } while (0)


/** Replace the existing string p if it is different than the new string s
 */
#define REPLACE_STRING_IF_NOT_EQUAL(p, s)    \
    if ((p) != NULL) { \
      if (util_strcmp((p), (s))) { VOS_FREE((p)); (p) = VOS_STRDUP((s)); } \
    } else { \
        (p) = VOS_STRDUP((s));                 \
    } 


/** Replace the existing string p if it is different than the new string s
 * and specify the way the string is allocated.
 */
#define REPLACE_STRING_IF_NOT_EQUAL_FLAGS(p, s, f)     \
    if ((p) != NULL) { \
      if (util_strcmp((p), (s))) {VOS_FREE((p)); (p) = VOS_STRDUP_FLAGS((s), (f)); } \
    } else { \
        (p) = VOS_STRDUP_FLAGS((s), (f));       \
    } 


/** If the source string pointer is not NULL, copy into destination buffer,
 *  otherwise, insert a 0 byte into the destination buffer so it becomes a
 *  null terminated string.
 */
#define STR_COPY_OR_NULL_TERMINATE(dst, src)                      \
   if ((dst) != NULL) {if ((src) != NULL) UTIL_STRNCPY(dst, src, sizeof(dst)); else *(dst) = 0;};


/** Duplicate a string.
 *
 * This function should be used only if the caller knows the string
 * is properly NULL terminated.  It should not be called on a buffer
 * whose contents cannot be trusted.  Consider using vosMem_strndup
 * instead.
 *
 * @param str (IN) string to duplicate.
 * @return On success, a duplicate of the given string will be returned.
 * Otherwise, NULL will be returned.  Caller must free the string by
 * calling vosMem_free().
 */
char *vosMem_strdup(const char *str, const char *function, UINT32 line);


/** Duplicate a string with ability to specify how memory is allocated.
 *
 * See vosMem_strdup.
 *
 * @param str (IN) string to duplicate.
 * @param flags (IN) flags to pass to the vosMem_alloc when allocating
 *                   storage for the duplicated string.
 * @return On success, a duplicate of the given string will be returned.
 * Otherwise, NULL will be returned.  Caller must free the string by
 * calling vosMem_free().
 */
char *vosMem_strdupFlags(const char *str, UINT32 flags, const char *function, UINT32 line);


/** Duplicate at most maxlen characters in the string.
 *
 * Use this function instead of strdup when you are not sure if the
 * string is NULL terminated.  If you use strdup and the string is not NULL
 * terminated, your program will crash.
 * 
 * maxlen does not include the NULL terminating character.
 * So if str is "abcde" and maxlen is 5, then this function will
 * allocate a buffer of length 6 and return a properly terminated 
 * string buffer containing "abcde" and the NULL terminating character.
 *
 * @param str (IN) string to duplicate.
 * @param maxlen (IN) maximum number of characters to copy.  The function
 *                    will allocate one extra byte for the NULL terminating
 *                    character if necessary.
 * @return On success, a duplicate of the given string will be returned.
 * Otherwise, NULL will be returned.  Caller must free the string by
 * calling vosMem_free().
 */
char *vosMem_strndup(const char *str, UINT32 maxlen, const char *function, UINT32 line);


/** Duplicate at most maxlen characters in the string with the ability to
 * specify how memory is allocated.
 *
 * See vosMem_strndup.
 *
 * @param str (IN) string to duplicate.
 * @param maxlen (IN) maximum number of characters to copy.  The function
 *                    will allocate one extra byte for the NULL terminating
 *                    character if necessary.
 * @param flags (IN) flags to pass to the vosMem_alloc when allocating storage
 *                   for the string.
 * @return On success, a duplicate of the given string will be returned.
 * Otherwise, NULL will be returned.  Caller must free the string by
 * calling vosMem_free().
 */
char *vosMem_strndupFlags(const char *str, UINT32 maxlen, UINT32 flags, const char *function, UINT32 line);


/** Return the length of the string, but constrained by maxlen
 *
 * This function works like strlen, except it will not look further
 * than maxlen bytes in the given string.
 *
 * @param str (IN) the string whose length we want to determine.
 * @param maxlen (IN) the maximum expected length of the string.
 * @param isTerminated (OUT) this is an optional pointer to a bool.
 *                           If this pointer is not null, then it will be
 *                           set to true if the string is maxlen or less.
 *
 * @return Number of bytes in the string, constrained by maxlen.
 */
UINT32 vosMem_strnlen(const char *str, UINT32 maxlen, UBOOL8 *isTerminated);


/*! \brief VOS Memory Statistics structure.
 *         Used in vosMem_getStats()
 */
typedef struct
{
   UINT32 shmAllocStart; /**< Start of shared memory alloc pool */
   UINT32 shmAllocEnd;   /**< End of shared memory alloc pool */
   UINT32 shmTotalBytes; /**< Total size of shm pool, in bytes */
   UINT32 shmBytesAllocd;/**< Number of bytes allocated/in-use from shm pool */
   UINT32 shmNumAllocs;  /**< Number of shared memory allocs */
   UINT32 shmNumFrees;   /**< Number of shared memory frees */
   UINT32 bytesAllocd;   /**< Number of private heap bytes alloc'ed */
   UINT32 numAllocs;     /**< Number of private heap allocs */
   UINT32 numFrees;      /**< Number of private heap frees */
} VosMemStats;


/** Get statistics on the memory allocator.
 *
 * @param stats (OUT) Pointer to a VOS Mem Stats structure.  This function
 *                    will fill in the structure.
 */
void vosMem_getStats(VosMemStats *stats);


/** Dump statistics on the memory allocator.
 *
 */
void vosMem_dumpMemStats(void);


/** Dump all memory leak allocation records.
 *
 */
void vosMem_dumpTraceAll(void);


/** Dump the most recent 50 memory leak allocation records.
 *
 */
void vosMem_dumpTrace50(void);


/** Dump leak allocation records that have 5 or more clones.
 *
 */
void vosMem_dumpTraceClones(void);


/** Initialize the shared memory allocator by giving it a chunk of shared
 *  memory to work with.
 *
 *  This function is only needed by MDM when it initially creates the
 *  piece of shared memory.
 *
 * @param addr (IN) Address where the shared memory allocator can start
 *                  using the memory.
 * @param len  (IN) Length of the memory buffer that the memory allocator has.
 */
void vosMem_initSharedMem(void *addr, UINT32 len);


/** Do secondary initialization of the shared memory allocator.
 *
 *  This function is only needed by MDM when the second, third, fourth, etc.
 *  applications attach themselves to the shared memory region.  The
 *  shared memory allocator has already been initialized by the first
 *  call to vosMem_initSharedMemory(), so this call just does minimal
 *  initialization needed to allow this application to also use the
 *  shared memory allocator.
 *
 * @param addr (IN) Address where the shared memory allocator can find
 *                  its data structures.
 * @param len  (IN) Length of the memory buffer that the memory allocator has.
 */
void vosMem_initSharedMemPointer(void *addr, UINT32 len);


/** Cleanup any state in the memory allocation sub-system.
 *
 */
void vosMem_cleanup(void);


/** Map a file to memory.
 *
 */
void *vomMem_mapFile2Mem(const char *fileName, UINT32 fileSize);

UBOOL8 vosMem_isAllocedMem(void *buf, const char *function, UINT32 line);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

/** How much debug information to put at the beginning of a malloc'd block,
 *  to keep track of original length and allocation flags (and also to
 *  detect buffer under-write).
 *
 * We allocate a header regardless of VOS_MEM_DEBUG.
 *
 * The memory code assumes this value is 12, so you'll need to modify
 * memory.c if you change this constant.
 */
#define VOS_MEM_HEADER_LENGTH   12


/** How much debug information to put at the end of a malloc'd block,
 *  (to detect buffer over-write) used only if VOS_MEM_DEBUG is defined.
 *
 * The memory code assumes this value is 8, so you'll need to modify
 * memory.c if you change this constant.
 */
#define VOS_MEM_FOOTER_LENGTH   8


/** Pattern put at the memory block footer (to detect buffer over-write).
 *
 * Used only if VOS_MEM_DEBUG is defined.
 * If allocation is not on 4 byte boundary, the bytes between the user
 * requested bytes and the 4 byte boundary are filled with the 
 * last byte of the VOS_MEM_FOOTER_PATTERN.
 */
#define VOS_MEM_FOOTER_PATTERN   0xfdfdfdfd


/** Pattern put in freshly allocated memory blocks, which do not have
 *  ALLOC_ZEROIZE flag set (to detect use before initialization.)
 *
 * Used only if VOS_MEM_DEBUG is defined.
 */
#define VOS_MEM_ALLOC_PATTERN    ((UINT8) 0x95)


/** Pattern put in freed memory blocks (to detect use after free.)
 *
 * Used only if VOS_MEM_DEBUG is defined.
 */
#define VOS_MEM_FREE_PATTERN     ((UINT8) 0x97)

#endif /* __VOS_MEM_H__ */
