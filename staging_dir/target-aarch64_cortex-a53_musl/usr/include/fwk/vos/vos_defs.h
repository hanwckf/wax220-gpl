#ifndef __VOS_DEFS_H__
#define __VOS_DEFS_H__


#include <unistd.h>  /* for getopt */
#include <stdio.h>   /* for snprintf */
#include <stdint.h>  /* for the various integer types */
#include <stdlib.h>  /* for NULL */
#include <string.h>  /* for strlen, strncpy */
#include <ctype.h>   /* for isdigit */
#include <syslog.h>  /* for syslog */
#include <stdarg.h>  /* for va_list */


/*!\file vos_defs.h
 * \brief Various commonly used, but OS dependent definitions are defined here.
 *
 *  This file is for Linux.
 */
 
#ifndef SIGNED_TYPES_ALREADY_DEFINED
#define SIGNED_TYPES_ALREADY_DEFINED

/** Signed 64 bit integer.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008
 */
typedef int64_t    SINT64;

/** Signed 32 bit integer. */
typedef int32_t    SINT32;

/** Signed 16 bit integer. */
typedef int16_t    SINT16;

/** Signed 8 bit integer. */
typedef int8_t     SINT8;

#endif /* SIGNED_TYPES_ALREADY_DEFINED */

#ifndef UNSIGNED_TYPES_ALREADY_DEFINED
#define UNSIGNED_TYPES_ALREADY_DEFINED

/** Unsigned 64 bit integer.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008
 */
typedef uint64_t   UINT64;

/** Unsigned 32 bit integer. */
typedef uint32_t   UINT32;

/** Unsigned 16 bit integer. */
typedef uint16_t   UINT16;

/** Unsigned 8 bit integer. */
typedef uint8_t    UINT8;

#endif /* UNSIGNED_TYPES_ALREADY_DEFINED */


#ifndef BOOL_TYPE_ALREADY_DEFINED
#define BOOL_TYPE_ALREADY_DEFINED

/**Boolean type; use 1 byte only, possible values are TRUE(1) or FALSE(0) only.
 *
 * TRUE/FALSE defined in ../fwk.h
 */
typedef uint8_t    UBOOL8;

#endif /* BOOL_TYPE_ALREADY_DEFINED */


#ifndef STRING_TYPE_ALREADY_DEFINED
#define STRING_TYPE_ALREADY_DEFINED

/** Base64 encoded string representation of binary data.
 *
 * This is to support TR69 data types.
 */
typedef char *     BASE64;


/** Hex encoded string representation of binary data.
 * This data type was introduced in TR-106 Issue 1, Admendment 2, Sept. 2008
 *
 * This is to support TR69 data types.
 */
typedef char *     HEXBINARY;


/** String representation of date and time.
 *
 * This is to support TR69 data types.
 */
typedef char *     DATETIME;


/** String representation of IPv4/6 address.
 *
 * This is to support TR69 data types.
 */
typedef char *     IPADDRESS;


/** String representation of MAC address.
 *
 * This is to support TR69 data types.
 */
typedef char *     MACADDRESS;

typedef uint8_t hal_port_t;

typedef uint32_t hal_pbmp_t;

#endif /* STRING_TYPE_ALREADY_DEFINED */


/*!\enum VOS_RET_E
 * \brief Return codes for all external functions, and some internal functions too.
 *
 * Codes from 9000-9799 are reserved for TR69C return values.
 * All Broadcom return codes should start at 9800.
 */
typedef enum
{
   VOS_RET_SUCCESS              = 0,     /**<Success. */
   VOS_RET_METHOD_NOT_SUPPORTED = 9000,  /**<Method not supported. */
   VOS_RET_REQUEST_DENIED       = 9001,  /**< Request denied (no reason specified). */
   VOS_RET_INTERNAL_ERROR       = 9002,  /**< Internal error. */
   VOS_RET_INVALID_ARGUMENTS    = 9003,  /**< Invalid arguments. */
   VOS_RET_RESOURCE_EXCEEDED    = 9004,  /**< Resource exceeded.
                                        *  (when used in association with
                                        *  setParameterValues, this MUST not be
                                        *  used to indicate parameters in error)
                                        */
   VOS_RET_INVALID_PARAM_NAME   = 9005,  /**< Invalid parameter name.
                                        *  (associated with set/getParameterValues,
                                        *  getParameterNames,set/getParameterAtrributes)
                                        */
   VOS_RET_INVALID_PARAM_TYPE   = 9006,  /**< Invalid parameter type.
                                        *  (associated with set/getParameterValues)
                                        */
   VOS_RET_INVALID_PARAM_VALUE  = 9007,  /**< Invalid parameter value.
                                        *  (associated with set/getParameterValues)
                                        */
   VOS_RET_SET_NON_WRITABLE_PARAM = 9008,/**< Attempt to set a non-writable parameter.
                                        *  (associated with setParameterValues)
                                        */
   VOS_RET_NOTIFICATION_REQ_REJECTED = 9009, /**< Notification request rejected.
                                            *  (associated with setParameterAttributes)
                                            */
   VOS_RET_DOWNLOAD_FAILURE     = 9010,  /**< Download failure.
                                         *  (associated with download or transferComplete)
                                         */
   VOS_RET_UPLOAD_FAILURE       = 9011,  /**< Upload failure.
                                        *  (associated with upload or transferComplete)
                                        */
   VOS_RET_FILE_TRANSFER_AUTH_FAILURE = 9012,  /**< File transfer server authentication
                                              *  failure.
                                              *  (associated with upload, download
                                              *  or transferComplete)
                                              */
   VOS_RET_UNSUPPORTED_FILE_TRANSFER_PROTOCOL = 9013,/**< Unsupported protocol for file
                                                    *  transfer.
                                                    *  (associated with upload or
                                                    *  download)
                                                    */
   VOS_RET_FILE_TRANSFER_UNABLE_JOIN_MULTICAST = 9014,/**< File transfer failure,
                                                    *  unable to join multicast
                                                    *  group.
                                                    */
   VOS_RET_FILE_TRANSFER_UNABLE_CONTACT_FILE_SERVER = 9015,/**< File transfer failure,
                                                    *  unable to contact file server.
                                                    */
   VOS_RET_FILE_TRANSFER_UNABLE_ACCESS_FILE = 9016,/**< File transfer failure,
                                                    *  unable to access file.
                                                    */
   VOS_RET_FILE_TRANSFER_UNABLE_COMPLETE = 9017,/**< File transfer failure,
                                                    *  unable to complete download.
                                                    */
   VOS_RET_FILE_TRANSFER_FILE_CORRUPTED = 9018,/**< File transfer failure,
                                                    *  file corrupted.
                                                    */
   VOS_RET_FILE_TRANSFER_FILE_AUTHENTICATION_ERROR = 9019,/**< File transfer failure,
                                                    *  file authentication error.
                                                    */
   VOS_RET_FILE_TRANSFER_FILE_TIMEOUT = 9020,/**< File transfer failure,
                                                    *  download timeout.
                                                    */
   VOS_RET_FILE_TRANSFER_FILE_CANCELLATION_NOT_ALLOW = 9021,/**< File transfer failure,
                                                    *  cancellation not permitted.
                                                    */
   VOS_RET_INVALID_UUID_FORMAT = 9022,/**< Invalid UUID Format
                                                    * (associated with ChangeDUState)
                                                    */
   VOS_RET_UNKNOWN_EE = 9023,/**< Unknown Execution Environment
                                                    * (associated with ChangeDUState)
                                                    */

   VOS_RET_EE_DISABLED = 9024,/**< Execution Environment disabled
                                                    * (associated with ChangeDUState)
                                                    */
   VOS_RET_DU_EE_MISMATCH = 9025,/**< Execution Environment and Deployment Unit mismatch
                                                    * (associated with ChangeDUState:install/update)
                                                    */
   VOS_RET_DU_DUPLICATE = 9026,/**< Duplicate Deployment Unit
                                                    * (associated with ChangeDUState:install/update)
                                                    */
   VOS_RET_SW_MODULE_SYSTEM_RESOURCE_EXCEEDED = 9027,/**< System resources exceeded
                                                    * (associated with ChangeDUState:install/update)
                                                    */
   VOS_RET_DU_UNKNOWN = 9028,/**< Unknown Deployment Unit
                                                    * (associated with ChangeDUState:update/uninstall)
                                                    */
   VOS_RET_DU_STATE_INVALID = 9029,/**< Invalid Deployment Unit State
                                                    * (associated with ChangeDUState:update)
                                                    */
   VOS_RET_DU_UPDATE_DOWNGRADE_NOT_ALLOWED = 9030,/**< Invalid Deployment Unit Update, downgrade not permitted
                                                    * (associated with ChangeDUState:update)
                                                    */
   VOS_RET_DU_UPDATE_VERSION_NOT_SPECIFIED = 9031,/**< Invalid Deployment Unit Update, version not specified
                                                    * (associated with ChangeDUState:update)
                                                    */

   VOS_RET_DU_UPDATE_VERSION_EXISTED= 9032,/**< Invalid Deployment Unit Update, version already exists
                                                    * (associated with ChangeDUState:update)
                                                    */
   VOS_RET_SUCCESS_REBOOT_REQUIRED = 9800, /**< Config successful, but requires reboot to take effect. */
   VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED = 9801,  /**<Success, but some unrecognized data was ignored. */
   VOS_RET_SUCCESS_OBJECT_UNCHANGED = 9802,  /**<Success, furthermore object has not changed, returned by STL handler functions. */
   VOS_RET_FAIL_REBOOT_REQUIRED = 9803,  /**<Config failed, and now system is in a bad state requiring reboot. */
   VOS_RET_NO_MORE_INSTANCES = 9804,     /**<getnext operation cannot find any more instances to return. */
   VOS_RET_MDM_TREE_ERROR = 9805,         /**<Error during MDM tree traversal */
   VOS_RET_WOULD_DEADLOCK = 9806, /**< Caller is requesting a lock while holding the same lock or a different one. */
   VOS_RET_LOCK_REQUIRED = 9807,  /**< The MDM lock is required for this operation. */
   VOS_RET_OP_INTR = 9808,      /**<Operation was interrupted, most likely by a Linux signal. */
   VOS_RET_TIMED_OUT = 9809,     /**<Operation timed out. */
   VOS_RET_DISCONNECTED = 9810,  /**< Communications link is disconnected. */
   VOS_RET_MSG_BOUNCED = 9811,   /**< Msg was sent to a process not running, and the
                                 *   bounceIfNotRunning flag was set on the header.  */
   VOS_RET_OP_ABORTED_BY_USER = 9812,  /**< Operation was aborted/discontinued by the user */
   VOS_RET_RECURSION_ERROR = 9817,     /**< too many levels of recursion */
   VOS_RET_OPEN_FILE_ERROR = 9818,     /**< open file error */
   VOS_RET_KEY_GENERATION_ERROR = 9830,     /** certificate key generation error */
   VOS_RET_INVALID_CERT_REQ = 9831,     /** requested certificate does not match with issued certificate */
   VOS_RET_INVALID_CERT_SUBJECT = 9832,     /** certificate has invalid subject information */
   VOS_RET_OBJECT_NOT_FOUND = 9840,     /** failed to find object */

   VOS_RET_INVALID_FILENAME = 9850,  /**< filename was not given for download */
   VOS_RET_INVALID_IMAGE = 9851,     /**< bad image was given for download */
   VOS_RET_INVALID_CONFIG_FILE = 9852,  /**< invalid config file was detected */
   VOS_RET_CONFIG_PSI = 9853,         /**< old PSI/3.x config file was detected */
   VOS_RET_IMAGE_FLASH_FAILED = 9854, /**< could not write the image to flash */
   VOS_RET_RESOURCE_NOT_CONFIGURED = 9855, /**< requested resource is not configured/found */
   VOS_RET_CARD_STATUS_FAILED = 9856,
   VOS_RET_LAN_SPEED_FAILED = 9857,
   VOS_RET_FILE_INVALID = 9858,
   VOS_RET_CONFIG_GET_FAILED = 9859,
   VOS_RET_WAN_CONNTYPE_NOT_IPROUTE = 9860,
   VOS_RET_GET_ROUTE_WAN_FAILED = 9861,
   VOS_RET_PLUGIN_NOT_EXIST  = 9862,
   VOS_RET_INVALID_TUNNEL_NAME = 9863,
   VOS_RET_INVALID_TUNNEL_USER_ID = 9864,
   VOS_RET_SOCK_WRITE_ERR_EAGAIN = 9865,
   VOS_RET_LOCAL_AUTH_FAIL = 9866,
   VOS_RET_UPDATRE_VERSION_INCORRET = 9867,
   VOS_RET_UPDATRE_VERSION_AS_CURRENT = 9868,
   VOS_RET_PMD_CALIBRATION_FILE_SUCCESS = 9869, /**<Success. PMD Calibration file was uploaded.*/
   VOS_RET_PMD_TEMP2APD_FILE_SUCCESS = 9870, /**<Success. PMD Temp2Apd file was uploaded.*/
   VOS_RET_PMD_JSON_FILE_SUCCESS = 9871 /**<Success. PMD JSON file was uploaded.*/
} VOS_RET_E;


/** Check if the VOS_RET_E code is either SUCCESS or SUCCESS_REBOOT_REQUIRED.
 * VOS_RET_SUCCESS_REBOOT is returned in two scenarios:
 * 1. During a set, the RCL handler function has accepted the new value but
 *    is unable to change the system configuration at run-time, so a reboot
 *    is needed before the change can take effect.
 * 2. During a AddObject or DeleteObject.  The MDM object tree has been
 *    successfully updated, but the RCL handler function is unable to change
 *    the system configuration at run-time, so a reboot is needed before the
 *    change can take effect.
 * Be very careful if you add any other return codes to this macro.
 * Make sure you understand what you are doing.  Specifically,
 * do not add VOS_RET_SUCCESS_UNRECOGNIZED_DATA_IGNORED or
 * VOS_RET_SUCCESS_OBJECT_UNCHANGED to this macro.  These return codes are
 * used in different contexts.
 */
#define IS_VOS_RET_A_SUCCESS_VARIANT(r) (((r) == VOS_RET_SUCCESS) || \
                                        ((r) == VOS_RET_SUCCESS_REBOOT_REQUIRED))

/** Check if the VOS_RET_E code is a TR69c recognized value.
 */
#define IS_VOS_RET_A_TR69C_VARIANT(r) (((r) == VOS_RET_SUCCESS) ||        \
                                      (((r) >= 9000) && ((r) < 9800)))



#ifndef TRUE
/** TRUE = 1
 */
#define TRUE  1
#endif

#ifndef FALSE
/** FALSE = 0
 */
#define FALSE 0
#endif

/** Maximum value for a UINT64 */
#define MAX_UINT64 18446744073709551615ULL

/** Maximum value for a SINT64 */
#define MAX_SINT64 9223372036854775807LL

/** Minimum value for a SINT64 */
#define MIN_SINT64 (-1 * MAX_SINT64 - 1)

/** Maximum value for a UINT32 */
#define MAX_UINT32 4294967295U

/** Maximum value for a SINT32 */
#define MAX_SINT32 2147483647

/** Minimum value for a SINT32 */
#define MIN_SINT32 (-2147483648)

/** Maximum value for a UINT16 */
#define MAX_UINT16  65535

/** Maximum value for a SINT16 */
#define MAX_SINT16  32767

/** Minimum value for a SINT16 */
#define MIN_SINT16  (-32768)

#define CMS_IFNAME_LENGTH  32
#define MAC_STR_LEN  17

#define BIT(nr) (1UL << (nr))
#define BIT_ULL(nr) (1ULL << (nr))
#define BIT_MASK(nr) (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr) ((nr) / BITS_PER_LONG)
#define BIT_ULL_MASK(nr) (1ULL << ((nr) % BITS_PER_LONG_LONG))
#define BIT_ULL_WORD(nr) ((nr) / BITS_PER_LONG_LONG)
#define BITS_PER_BYTE 8

typedef enum 
{
   VOS_WAN_TYPE_PPPOE               = 0,
   VOS_WAN_TYPE_PPPOA               = 1,
   VOS_WAN_TYPE_DYNAMIC_IPOE        = 2,
   VOS_WAN_TYPE_BRIDGE              = 3,
   VOS_WAN_TYPE_PPPOE_RELAY         = 4,
   VOS_WAN_TYPE_IPOA                = 5,
   VOS_WAN_TYPE_STATIC_IPOE         = 6,   
   
   VOS_WAN_TYPE_STATIC_ETHERNET_IP  = 10,
   VOS_WAN_TYPE_DYNAMIC_ETHERNET_IP = 11,
   VOS_WAN_TYPE_ETHERNET_PPPOE      = 12,
   VOS_WAN_TYPE_ETHERNET_BRIDGE     = 13,
   VOS_WAN_TYPE_L2TP                = 14,   
   VOS_WAN_TYPE_UNDEFINED           = 99
} VosWanConnectionType;


#define GPON_WAN_PHYSICAL_INTERFACE_NAME "gpon0"
#define GPON_WAN_ANI_INTERFACE_NAME "gpon0.ani"
#define GPON_WAN_LAYER2_VEIP_INTERFACE_NAME "veip0"
#define GPON_WAN_PHYSICAL_MULTICAST_INTERFACE_NAME "gponm"
#define GPON_WAN_ANI_MUTICAST_INTERFACE_NAME "gponm.ani"
#define VEIP_PHY_ID  0
#define GPON_HASHLIMIT_FILE "udpT.veip0."

#define EPON_HASHLIMIT_FILE "udpT.epon0."
#define EPON_WAN_LAYER2_EPON_INTERFACE_NAME "epon0"
#define EOC_WAN_LAYER2_INTERFACE_NAME "eth0"
#define EOC_WAN_LAYER2_INTERFACE_NAME_BSTAR "eth1"


#endif /* __VOS_DEFS_H__ */
