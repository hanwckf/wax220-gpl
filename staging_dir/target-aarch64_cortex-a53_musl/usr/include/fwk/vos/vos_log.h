#ifndef __VOS_LOG_H__
#define __VOS_LOG_H__
#include "vos_eid.h"

#define VOS_LOG_MAX_CACHE_LEN  (80)
#define VOS_LOG_MAX_CACHE_NUM  (32)

#ifndef DESKTOP_LINUX
#define VOS_LOG_KEY_FILE_PREFIX  "/tmp/logKey"
#else
#define VOS_LOG_KEY_FILE_PREFIX  "./logKey"
#endif

#define VOS_LAST_PTY_NAME_FILE "/tmp/last_pty"


/*!\file vos_log.h
 * \brief Public header file for Broadcom DSL CPE Management System VosLogging API.
 * Applications which need to call VosLogging API functions must
 * include this file.
 *
 * Here is a general description of how to use this interface.
 *
 */

/*!\enum VosLogLevel
 * \brief VosLogging levels.
 * These correspond to LINUX log levels for convenience.  Other OS's
 * will have to map these values to their system.
 */
typedef enum
{
   VOS_LOG_LEVEL_SILENT  = 1, /**< Message at silent level. */
   VOS_LOG_LEVEL_PRINT   = 2,
   VOS_LOG_LEVEL_ERR     = 3, /**< Message at error level. */
   VOS_LOG_LEVEL_WARNING = 4, /**< Message at waring level. */
   VOS_LOG_LEVEL_NOTICE  = 5, /**< Message at notice level. */
   VOS_LOG_LEVEL_INFO    = 6, /**< Message at info level. */
   VOS_LOG_LEVEL_DEBUG   = 7, /**< Message at debug level. */
   VOS_LOG_LEVEL_DEVEL   = 9  /**< Message at develop level. */
} VosLogLevel;


/*!\enum VosLogDestination
 * \brief identifiers for message logging destinations.
 */
typedef enum
{
   VOS_LOG_DEST_CONSOLE = 1,  /**< Message output to console. */
   VOS_LOG_DEST_STDERR  = 2,  /**< Message output to stderr. */
   VOS_LOG_DEST_SYSLOG  = 3,  /**< Message output to syslog. */
   VOS_LOG_DEST_TELNET  = 4,   /**< Message output to telnet clients. */
   VOS_LOG_DEST_LOGCAT  = 5,
   VOS_LOG_DEST_LOGFILE = 6
} VosLogDestination;


typedef struct
{
    VosLogLevel logLevel;
    VosLogDestination logDestination;
    char cache[VOS_LOG_MAX_CACHE_NUM][VOS_LOG_MAX_CACHE_LEN];
    UINT32 location;
    UINT32 logMaxSize;
} VOS_LOG_SHARED_MEM_T;


/** Show application name in the log line. */
#define VOS_LOG_HDRMASK_APPNAME    0x0001 

/** Show log level in the log line. */
#define VOS_LOG_HDRMASK_LEVEL      0x0002 

/** Show timestamp in the log line. */
#define VOS_LOG_HDRMASK_TIMESTAMP  0x0004

/** Show location (function name and line number) level in the log line. */
#define VOS_LOG_HDRMASK_LOCATION   0x0008 
 

/** Default log level is error messages only. */
#define DEFAULT_LOG_LEVEL        VOS_LOG_LEVEL_ERR

/** Default log destination is standard error */
#define DEFAULT_LOG_DESTINATION  VOS_LOG_DEST_STDERR

/** Default log header mask */
#define DEFAULT_LOG_HEADER_MASK (VOS_LOG_HDRMASK_APPNAME|VOS_LOG_HDRMASK_LEVEL|VOS_LOG_HDRMASK_TIMESTAMP|VOS_LOG_HDRMASK_LOCATION)


/** Maxmimu length of a single log line; messages longer than this are truncated. */
#define MAX_LOG_LINE_LENGTH      1024 * 10


/** Macros Definition.
 * Applications should use these macros for message logging, instead of
 * calling the log_log function directly.
 */
#define LOG_LEVEL_DEBUG    LOG_DEBUG
#define LOG_LEVEL_WARNING  LOG_WARNING
#define LOG_LEVEL_ERROR    LOG_ERR

#define log(level, args, ...) \
    do { \
        syslog(level, "[%s:%d]: "args, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while(0)

/*#if defined(VOS_LOG0)
#define vosLog_print(args...)  log_log(VOS_LOG_LEVEL_PRINT, __FUNCTION__, __LINE__, args)
#define vosLog_error(args...)
#define vosLog_notice(args...)
#define vosLog_debug(args...)
#define vosLog_devel(args...)

#elif defined(VOS_LOG2)*/
#define vosLog_silent(args...)
#define vosLog_print(args...)  log_log(VOS_LOG_LEVEL_PRINT, __FUNCTION__, __LINE__, args)
#define vosLog_error(args...)  log_log(VOS_LOG_LEVEL_ERR, __FUNCTION__, __LINE__, args)
#define vosLog_warn(args...)   log_log(VOS_LOG_LEVEL_WARNING, __FUNCTION__, __LINE__, args)
#define vosLog_notice(args...) log_log(VOS_LOG_LEVEL_NOTICE, __FUNCTION__, __LINE__, args)
#define vosLog_info(args...)   log_log(VOS_LOG_LEVEL_INFO, __FUNCTION__, __LINE__, args)
#define vosLog_debug(args...)  log_log(VOS_LOG_LEVEL_DEBUG, __FUNCTION__, __LINE__, args)
#define vosLog_devel(args...)  //log_log(VOS_LOG_LEVEL_DEVEL, __FUNCTION__, __LINE__, args)



/*#else
#define vosLog_print(args...)  //log_log(VOS_LOG_LEVEL_PRINT, __FUNCTION__, __LINE__, args)
#define vosLog_error(args...)  log(LOG_LEVEL_ERROR, args)
#define vosLog_notice(args...) log(LOG_LEVEL_WARNING, args)
#define vosLog_debug(args...)  log(LOG_LEVEL_DEBUG, args)
#define vosLog_devel(args...)  //log_log(VOS_LOG_LEVEL_DEVEL, __FUNCTION__, __LINE__, args)
#endif*/


/** Internal message log function; do not call this function directly.
 *
 * NOTE: Applications should NOT call this function directly from code.
 *       Use the macros defined in vos_log.h, i.e.
 *       vosLog_error, vosLog_notice, vosLog_debug.
 *
 * This function performs message logging based on two control
 * variables, "logLevel" and "logDestination".  These two control
 * variables are local to each process.  Each log message has an
 * associated severity level.  If the severity level of the message is
 * numerically lower than or equal to logLevel, the message will be logged to
 * either stderr or syslogd based on logDestination setting.
 * Otherwise, the message will not be logged.
 * 
 * @param level (IN) The message severity level as defined in "sysvos_log.h".
 *                   The levels are, in order of decreasing importance:
 *                   VOS_LOG_EMERG (0)- system is unusable 
 *                   VOS_LOG_ALERT (1)- action must be taken immediately
 *                   VOS_LOG_CRIT  (2)- critical conditions
 *                   VOS_LOG_ERR   (3)- error conditions 
 *                   VOS_LOG_WARNING(4) - warning conditions 
 *                   VOS_LOG_NOTICE(5)- normal, but significant, condition
 *                   VOS_LOG_INFO  (6)- informational message 
 *                   VOS_LOG_DEBUG (7)- debug-level message
 * @param func (IN) Function name where the log message occured.
 * @param lineNum (IN) Line number where the log message occured.
 * @param fmt (IN) The message string.
 *
 */
void log_log(VosLogLevel level, const char *func, unsigned int lineNum, const char *fmt, ... );

/** Message log initialization.
 * This function initializes the message log utility.  The openlog
 * function is called to open a connection to syslogd for the
 * process.  The process name string identified by entityId will
 * be prepended to every message logged by the system logger syslogd.
 *
 * @param eid (IN) The entity ID of the calling process.
 */
void vosLog_init(VosEntityId eid);
  
/** Message log cleanup.
 * This function performs all the necessary cleanup of the message
 * log utility. The closelog function is called to close the
 * descriptor being used to write to the system logger syslogd.
 *
 */
void vosLog_cleanup(void);
  
/** Set process message logging level.
 * This function sets the logging level of a process.
 *
 * @param level (IN) The logging level to set.
 */
void vosLog_setLevel(VosLogLevel level);

/** Get process message logging level.
 * This function gets the logging level of a process.
 *
 * @return The process message logging level.
 */
VosLogLevel vosLog_getLevel(void);

/** Set process message logging destination.
 * This function sets the logging destination of a process.
 *
 * @param dest (IN) The process message logging destination.
 */
void vosLog_setDestination(VosLogDestination dest);

/** Get process message logging destination.
 * This function gets the logging destination of a process.
 *
 * @return The process message logging destination.
 */
VosLogDestination vosLog_getDestination(void);

/** Set process message log header mask which determines which pieces of
 * info are included in each log line.
 *
 * @param mask (IN) Bitmask of VOS_LOG_HDRMASK_xxx
 */
void vosLog_setHeaderMask(unsigned int headerMask);

/** Get process message log header mask.
 *
 * @return The process message log header mask.
 */
unsigned vosLog_getHeaderMask(void);

void vosLog_setMaxSize(UINT32 kbytes);
UINT32 vosLog_getMaxSize(void);

void vosLog_printf(VosLogLevel logLevel, VosLogDestination logDestination, UBOOL8 newLine, const char *buf);


/** indicate first read */
#define BCM_SYSLOG_FIRST_READ           -2

/** indicates error */
#define BCM_SYSLOG_READ_BUFFER_ERROR    -1

/** indicates last line was read */
#define BCM_SYSLOG_READ_BUFFER_END      -3

/** max log buffer length */
#define BCM_SYSLOG_MAX_LINE_SIZE        255


/** Legacy method for reading the system log line by line.
 *
 * @param ptr     (IN) Current line to read.
 * @param buffer (OUT) Line that was read.
 * @return new ptr value for next read.
 */

VOS_RET_E vosSyslog_info(const char *fmt, ...);


/** redirect all printf to the tty
 *
 * @param ptr     the tty
 * @
 * @
 */
VOS_RET_E vosLog_stdRedirect(const char *tty);
VOS_RET_E vosLog_stdRevert(void);
VOS_RET_E vosLog_saveLastPty(const char *pty_name);
VOS_RET_E vosLog_stdToLastPty(void);
void vosLog_hexDump(const void *buf, UINT32 length);
__attribute__((format(printf, 1, 2))) void vosLog_out(const char *format, ...);

void vosLog_show(VosEntityId eid);
void vosLog_clear(VosEntityId eid);

#endif /* __VOS_LOG_H__ */
