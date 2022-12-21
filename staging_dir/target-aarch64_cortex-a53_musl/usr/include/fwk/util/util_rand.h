#ifndef __UTIL_RAND_H__
#define __UTIL_RAND_H__


/*!\file util_rand.h
 * \brief Header file for various random number utility funcs in VOS.
 *
 */

#include "../fwk.h"


#define MAX_RANDSTRING_LEN   127

/** Get a random string of specified length.
 *
 * Before calling this function, the app should call srand() to
 * seed the random number generator.
 *
 * Note this function is not multi-thread safe because it uses
 * an internal static buffer.  A multi-thread safe version of this
 * function (_r) may be implemented if there is a need for it.
 *
 * @param minchars (IN)  Minimum number of chars in the string.  Must be
 *                       greater than 0.
 * @param maxchars (IN)  Maximum number of chars in the string.  Must be
 *                       equal to or greater than min chars and not more
 *                       than MAX_RANDSTRING_LEN
 *
 * @return pointer to random string or NULL on error.
 */
char *utilRand_getRandString(UINT32 minChars, UINT32 maxChars);

#endif  /* __UTIL_RAND_H__ */

