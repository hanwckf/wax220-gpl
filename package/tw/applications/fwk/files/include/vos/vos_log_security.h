#ifndef __VOS_LOG_SECURITY_H__
#define __VOS_LOG_SECURITY_H__


/*!\enum VosLogSecurityLogIDs
 * \brief Security VosLog identifiers.
 * 
 */
typedef enum
{
    VOS_LOG_SECURITY_CUSTOM = 0,            /**< Used for custom strings, blank default text */
    VOS_LOG_SECURITY_PWD_CHANGE_SUCCESS = 1,/**< Password change successful */
    VOS_LOG_SECURITY_PWD_CHANGE_FAIL,       /**< Password change failed */
    VOS_LOG_SECURITY_AUTH_LOGIN_PASS,       /**< An authorized user successfully logged in. */
    VOS_LOG_SECURITY_AUTH_LOGIN_FAIL,       /**< An authorized user failed login. */
    VOS_LOG_SECURITY_AUTH_LOGOUT,           /**< An authorized user has logged out. */
    VOS_LOG_SECURITY_LOCKOUT_START,         /**< Security lockout added */
    VOS_LOG_SECURITY_LOCKOUT_END,           /**< Security lockout removed. */
    VOS_LOG_SECURITY_AUTH_RESOURCES,        /**< Authorized attempt to access resources. */
    VOS_LOG_SECURITY_UNAUTH_RESOURCES,      /**< Unauthorized attempt to access resources. */
    VOS_LOG_SECURITY_SOFTWARE_MOD,          /**< Software update occurred. */
    VOS_LOG_SECURITY_MAX,                   /**< Used for range checking */
} VosLogSecurityLogIDs;


/** Max number of ms to wait for a MDM read lock. */
#define VOS_LOG_LOCK_TIMEOUT  (3 * MSECS_IN_SEC)

#define VOS_LOG_SEC_EMPTY_SECURITY_LOG_DATA { 0, 0, NULL, NULL, NULL, 0, 0 }

#define VOS_LOG_SEC_COUNT_FLAG    (1 << 0)
#define VOS_LOG_SEC_PORT_FLAG     (1 << 1)
#define VOS_LOG_SEC_SRC_IP_FLAG   (1 << 2)
#define VOS_LOG_SEC_USER_FLAG     (1 << 3)
#define VOS_LOG_SEC_LEVEL_FLAG    (1 << 4)
#define VOS_LOG_SEC_APP_NAME_FLAG (1 << 5)

#define VOS_LOG_SEC_SET_COUNT(p, d)   {(p)->count = (d); (p)->data_flags |= VOS_LOG_SEC_COUNT_FLAG;}
#define VOS_LOG_SEC_SET_PORT(p, d)    {(p)->port = (d);  (p)->data_flags |= VOS_LOG_SEC_PORT_FLAG;}
#define VOS_LOG_SEC_SET_SRC_IP(p, d)  {(p)->ipAddr = (d); (p)->data_flags |= VOS_LOG_SEC_SRC_IP_FLAG;}
#define VOS_LOG_SEC_SET_APP_NAME(p, d) {(p)->appName = (d); (p)->data_flags |= VOS_LOG_SEC_APP_NAME_FLAG;}
#define VOS_LOG_SEC_SET_USER(p, d)    {(p)->user = (d);  (p)->data_flags |= VOS_LOG_SEC_USER_FLAG;}
#define VOS_LOG_SEC_SET_LEVEL(p, d)   {(p)->security_level = (d);  (p)->data_flags |= VOS_LOG_SEC_LEVEL_FLAG;}

/** security log length */
#define SECURITY_LOG_RD_OFFSET   (0)
#define SECURITY_LOG_RD_SIZE     (sizeof(uint32_t))
#define SECURITY_LOG_WR_OFFSET   (4)
#define SECURITY_LOG_WR_SIZE     (sizeof(uint32_t))
#define SECURITY_LOG_DATA_OFFSET (8)
#define SECURITY_LOG_DATA_SIZE   (4 * 1024)
#define SECURITY_LOG_FILE_NAME  "/data/securitylog"


/** Structure to hold relevant data regarding security log events.
 *
 */
typedef struct
{
    UINT32 count;
    UINT32 port;
    char *appName;
    char *ipAddr;
    char *user;
    UINT32 security_level;
    UINT32 data_flags;
} VosLogSecurityLogData;


/** Security log file structure 
 *
 */
typedef struct
{
    unsigned long read_offset;      /** offset of oldest log */
    unsigned long write_offset;     /** offset of newest log */
    char log[SECURITY_LOG_DATA_SIZE];    /** security log strings */
} VosLogSecurityLogFile;


/** Log a security log in the system.
 *
 * This function logs security logs into flash for non-volatile storage.
 * There are a specified list of logs that can be used, or the user may 
 * add their own string.
 *
 * @param id (IN) Predefined security log message string.
 * @param pdata (IN) Structure containing relevant log information. 
 * @param fmt (IN) The message string.
 *
 * @return VOS_RET_SUCCESS on success, otherwise an error occurred.
 */
VOS_RET_E vosLog_security(VosLogSecurityLogIDs id, VosLogSecurityLogData * pdata,
                           const char *fmt, ... );


/** Retrieve the security log from the system.
 *
 * @param log (OUT) Pointer to VosLogSecurityLogFile structure. 
 *                  Memory must be allocated by the caller.
 *
 * @return VOS_RET_SUCCESS on success, otherwise an error occurred.
 */
VOS_RET_E vosLog_getSecurityLog(VosLogSecurityLogFile * log);


/** Print the security log to stdout.
 *
 * @param log (OUT) Pointer to VosLogSecurityLogFile structure. 
 *                  Memory must be allocated by the caller.
 *
 * @return None
 */
void vosLog_printSecurityLog(VosLogSecurityLogFile * log);


/** Reset and clear all entries in the security log in the system.
 *
 * @return VOS_RET_SUCCESS on success, otherwise an error occurred.
 */
VOS_RET_E vosLog_resetSecurityLog(void);


#endif /* VOS_SECURITY_LOG */
