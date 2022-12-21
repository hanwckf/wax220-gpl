#ifndef __UTIL_PWD_H__
#define __UTIL_PWD_H__

/*!\file util_pwd.h
 * \brief Header file for password utilities
 */

#include "../fwk.h"


/** create salt for use with util_pwCrypt
 *
 * @return pointer to salt
 */
char *util_cryptMakeSalt(void);


/** create hashed password
 *
 * @param clear (IN) clear text password
 * @param salt  (IN) salt for password hashing
 *
 * @return pointer to hashed password
 */
char *util_pwEncrypt(const char *clear, const char *salt);

#endif /* __UTIL_PWD_H__ */

