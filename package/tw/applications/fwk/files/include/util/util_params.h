#ifndef __UTIL_PARAMS_H__
#define __UTIL_PARAMS_H__


/** Address where the shared memory region is attached.
 *
 * Every process must attach to the shared memory at the same address
 * because the data structures inside the shared memory region contain
 * pointers to other areas in the shared memory.
 */
#define MDM_SHM_ATTACH_ADDR  0x58800000



/** This shmId value means its uninitialized */
#define UNINITIALIZED_SHM_ID  -1


/** Base amount of shared memory to allocate.
 *
 */
#define MDM_SHM_BASE_SIZE         (160 * 1024)


/** Amount of shared memory to allocate if WLAN feature is enabled.
 *
 */
#define MDM_SHM_WLAN_EXTRA        (128 * 1024)


/** Amount of shared memory to allocate if VOIP feature is enabled.
 *
 */
#define MDM_SHM_VOIP_EXTRA        (128 * 1024)


/** Amount of shared memory to allocate if L2TP feature is enabled.
 *
 */
#define MDM_SHM_L2TP_EXTRA        (256 * 1024)


/** Amount of shared memory to allocate if GPON feature is enabled.
 *
 */
#define MDM_SHM_GPON_EXTRA        (128 * 1024)

/** Amount of shared memory to allocate if extra large DSL data is enabled.
 *
 */
#define MDM_SHM_DSL_BIG_DATA_EXTRA  (256 * 1024)

/** The "key" to use when requesting a semaphore from the Linux OS.
 *
 * This is used to implement low level MDM transation locks.
 * The only time this will need to be modified is when other code
 * is using the same key.
 */
#define MDM_LOCK_SEMAPHORE_KEY 0x5ed7


/** This is the Unix Domain Socket address for communications with smd used
 *  by the messaging library.
 *
 * Note two different addresses are defined, one for modem and one for DESKTOP_LINUX testing.
 *  It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define SMD_MESSAGE_ADDR  "./smd_messaging_server_addr"
#else
#define SMD_MESSAGE_ADDR  "/var/smd_messaging_server_addr"
#endif


/** This is the number of fully connected connections that can be queued
 *  up at the SMD message server socket.
 *
 *  It is highly unlikely that this needs to be changed.
 */
#define SMD_MESSAGE_BACKLOG  3


/** Special hack for the smd dynamic launch service, when it launches a server app, the
 *  server app will find its server fd at this number.
 *
 * It is highly unlikely that this needs to be changed.
 */
#define VOS_DYNAMIC_LAUNCH_SERVER_FD  3

#define VOS_DYNAMIC_LAUNCH_SERVER_FD_2 4



/** This is the port ftpd listens on.
 * 
 * Note two different ports are defined, one for modem and one for DESKTOP_LINUX testing.
 * It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define FTPD_PORT       44421
#else
#define FTPD_PORT       21
#endif


/** This is the port tftpd listens on.
 * 
 * Note two different ports are defined, one for modem and one for DESKTOP_LINUX testing.
 * It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define TFTPD_PORT      44469
#else
#define TFTPD_PORT      69
#endif


/** This is the port sshd listens on.
 * 
 * Note two different ports are defined, one for modem and one for DESKTOP_LINUX testing.
 * It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define SSHD_PORT       44422
#else
#define SSHD_PORT       22
#endif


/** The amount of idle time, in seconds, before sshd exits.
 *
 * Make this relatively long because the user might be configuring something,
 * then gets confused and have to look up some manual.
 * If 0, then no timeout.
 */
#define SSHD_EXIT_ON_IDLE_TIMEOUT  600


/** This is the port telnetd listens on.
 * 
 * Note two different ports are defined, one for modem and one for DESKTOP_LINUX testing.
 * It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define TELNETD_PORT    44423
#else
#define TELNETD_PORT    23
#endif


/** The amount of idle time, in seconds, before telnetd exits.
 *
 * Make this relatively long because the user might be configuring something,
 * then gets confused and have to look up some manual.
 * If 0, then no timeout.
 */
#define TELNETD_EXIT_ON_IDLE_TIMEOUT  600


/** This is the port httpd listens on.
 * 
 * Note two different ports are defined, one for modem and one for DESKTOP_LINUX testing.
 * It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define HTTPD_SSL_PORT  44443
#define HTTPD_DEF_PORT  44480
#define HTTPD_PORT      44480
#else
#define HTTPD_SSL_PORT      443
#define HTTPD_DEF_PORT      80
#define HTTPD_BACKUP_PORT   8080
//#define HTTPD_PORT      (SF_FEATURE_SUPPORT_HTTPD_SSL ? HTTPD_SSL_PORT : HTTPD_BACKUP_PORT)
#define HTTPD_PORT      (SF_FEATURE_SUPPORT_HTTPD_SSL ? HTTPD_SSL_PORT : (SF_FEATURE_SUPPORT_DBUS ? HTTPD_BACKUP_PORT : HTTPD_DEF_PORT))
#endif


/** The amount of idle time, in seconds, before httpd exits.
 *
 * Make this relatively long because the user might be configuring something,
 * then gets confused and have to look up some manual.
 */
#define HTTPD_EXIT_ON_IDLE_TIMEOUT  (600)


/** The amount of idle time, in seconds, before consoled exits.
 *
 * Make this relatively long because the user might be configuring something,
 * then gets confused and have to look up some manual.
 * If 0, then no timeout.
 */
#define CONSOLED_EXIT_ON_IDLE_TIMEOUT  600


/** This is the port snmpd listens on.
 * 
 * Note two different ports are defined, one for modem and one for DESKTOP_LINUX testing.
 * It is highly unlikely that this needs to be changed.
 */
#ifdef DESKTOP_LINUX
#define SNMPD_PORT      44161
#else
#define SNMPD_PORT      161
#endif

/** This is the port tr64c listens on.
* LGD_TODO: Due to the time limit, it still have one DESKTOP_LINUX version TR64C, 
* in the future will add it.
*/
#define TR64C_HTTP_CONN_PORT     49431


/** This is the port tr69c listens on for connection requests from the ACS.
 * 
 */
#define TR69C_CONN_REQ_PORT      30005


/** This is the path part of the URL for tr69c connection requests from the ACS.
 * 
 */
#define TR69C_CONN_REQ_PATH      "/"


/** The amount of idle time, in seconds, before tr69c exits.
 *
 * This value does not need to be very large because the ACS is usually running
 * a script so it will do all the actions it needs back-to-back and then be
 * completely done.  So if we see no more requests from the ACS for 30 seconds,
 * that probably means the ACS is completely done.  However, if response time
 * is very important, and you do not want the tr69c client to exit, then you
 * can set this to a very large value (e.g. 2160356, which is one year).
 */
#define TR69C_EXIT_ON_IDLE_TIMEOUT       30 


/** Maximum number of Layer 2 bridges supported.
 * 
 * If this value is changed, be sure to also modify the default value in
 * the data model.
 */
#define MAX_LAYER2_BRIDGES                16


/** Maximum depth of objects in the Data Model that we can support.
 *  If the data model has a greater actual depth than what is defined here,
 *  mdm_init() will fail.
 */
#define MAX_MDM_INSTANCE_DEPTH    6


/** Maximum length of a parameter name in the Data Model that we can support.
 *  If the data model has a greater actual param name length than what is defined here,
 *  mdm_init() will fail.
 */
#define MAX_MDM_PARAM_NAME_LENGTH   55

/** DNS Probing parameters for both dnsprobe and dproxy. They probe every
 * 30 seconds. Timeout is 3 seconds and only retry 2 more times. */
#define DNS_PROBE_INTERVAL 30
#define DNS_PROBE_TIMEOUT 3 
#define DNS_PROBE_MAX_TRY 3


/** Max length of a line in a file in the CMS_EID_DIR
 */
#define MAX_EID_LINE_LENGTH      512


/** Max length of a full path name.
 *
 * Linux and various filesystems is usually 4096, but we limit it to save
 * some memory.
 */
#define MAX_FULLPATH_LENGTH     1024


/** Max length of a file name.
 *
 * Linux and various filesystems is around 1024, but we limit it to save
 * some memory.
 */
#define MAX_FILENAME_LENGTH     257


typedef enum
{
    MDM_UNINITIALIZED,
    MDM_INIT_SHM,
    MDM_INIT_OK,
} MDM_INIT_STATE_E;


typedef struct mdm_info
{
    SINT32 shmId;
    MDM_INIT_STATE_E state;
} MDM_INIT_INFO_T;


#endif  /* __UTIL_PARAMS_H__ */
