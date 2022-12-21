/*
 * This header file contains all the functions exported by the
 * OS Adaptation Layer (OAL).  The OAL functions live under the
 * directory with the name of the OS, e.g. linux, ecos.
 * The Make system will automatically compile the appropriate files
 * and link them in with the final executable based on the TARGET_OS
 * variable, which is set by make menuconfig.
 */

#ifndef __UTIL_PASSWD_OAL_H__
#define __UTIL_PASSWD_OAL_H__

#include "../fwk.h"


/* in oal_passwd.c */
extern char * oalPass_crypt(const char *clear, const char *salt);


#endif /* __UTIL_PASSWD_OAL_H__ */
