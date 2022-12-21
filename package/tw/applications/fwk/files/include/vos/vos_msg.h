#ifndef __VOS_MSG_H__
#define __VOS_MSG_H__


/*!\file vos_msg.h
 * \brief Public header file for messaging.
 * Code which need to handle messages must include this file.
 *
 * Here is a general description of how to use this interface.
 *
 * Early in application startup code, call vosMsg_init() with a pointer
 * to void *.
 *
 * To receive a message, call vosMsg_receive().  This returns a
 * pointer to a buffer that has a VosMsgHeader at the beginning
 * and optional data after the header.  Free this buffer when you
 * are done with it by calling vosMsg_free().
 *
 * To send a message, allocate a buffer big enough to hold a
 * VosMsgHeader and any optional data you need to send with the
 * message.  Fill in the buffer (header and data portion), and
 * call vosMsg_send().
 *
 * Before the application exits, call vosMsg_cleanup().
 */


/*!\enum VosMsgType
 * \brief  Enumeration of possible message types
 *
 * This is the complete list of message types.
 * By convention:
 * system event message types are from            0x10000250-0x100007ff
 * system request/response message types are from 0x10000800-0x10000fff
 * Voice event messages are from                  0x10002000-0x100020ff
 * Voice request/response messages are from       0x10002100-0x100021ff
 * GPON OMCI request/response messages are from   0x10002200-0x100022ff
 * Note that a message type does not specify whether it is a
 * request or response, that is indicated via the flags field of
 * VosMsgHeader.
 */
typedef enum 
{
    VOS_MSG_INVALID                                         = 0x00000000, /* INIT value or invalid value */

    /* S204 */
    VOS_MSG_SYSTEM_BASE                                     = 0x00000000,
    VOS_MSG_SYSTEM_DESTORY                                  = 0x00000003,
    VOS_MSG_SYSTEM_READY                                    = 0x00000005,
    VOS_MSG_SYSTEM_CLI_INFO                                 = 0x00000006,
    VOS_MSG_SYSTEM_APPL_READY                               = 0x00000008,
    VOS_MSG_SYSTEM_SRPC                                     = 0x0000000A,
    VOS_MSG_SYSTEM_STD_REDIRECT                             = 0x00000011,
    VOS_MSG_SYSTEM_STD_REVERT                               = 0x00000012,
    VOS_MSG_SYSTEM_TASK_FINISH                              = 0x00000013,


    VOS_MSG_SYS_BASE                                        = 0x00010000,

    VOS_MSG_SMD_BASE                                        = 0x00010100,
    VOS_MSG_SMD_INSTALL_APP                                 = 0x00010101,
    VOS_MSG_SMD_UNINSTALL_APP                               = 0x00010102,

    VOS_MSG_CLI_BASE                                        = 0x00010200,
    VOS_MSG_CLI_INITIALIZED                                 = 0x00010201,
    VOS_MSG_CLI_HANDLE_CMD                                  = 0x00010202,

    VOS_MSG_CONSOLED_BASE                                   = 0x00010300,

    VOS_MSG_TELNETD_BASE                                    = 0x00010400,

    VOS_MSG_CMC_BASE                                        = 0x00010500,
    VOS_MSG_CMC_MDM_INSTANCE_ADD                            = 0x00010501,
    VOS_MSG_CMC_MDM_INSTANCE_DEL                            = 0x00010502,
    VOS_MSG_CMC_MDM_PARAM_VALUE_CHANGED                     = 0x00010503,
    VOS_MSG_CMC_AUTH_CHECK                                  = 0x00010504,
    VOS_MSG_CMC_SAVE_CONFIG                                 = 0x00010505,
    VOS_MSG_CMC_RESET_CONFIG                                = 0x00010506,
    VOS_MSG_CMC_CTC_MNG                                     = 0x00010507,

    VOS_MSG_CMC_OAM_SET_WAN_PARAMETER                       = 0x00010508,
    VOS_MSG_CMC_OAM_GET_WAN_PARAMETER                       = 0x00010509,
    VOS_MSG_CMC_OAM_SET_WAN_MTU                             = 0x0001050A,
    VOS_MSG_CMC_OAM_GET_WAN_MTU                             = 0x0001050B,
    VOS_MSG_CMC_OAM_GET_ALL_WAN                             = 0x0001050C,
    VOS_MSG_CMC_OAM_SET_WIFI_RESTORE                        = 0x0001050D,
    VOS_MSG_CMC_OAM_SET_CLEAR_ALL_WAN                       = 0x0001050E,
    VOS_MSG_CMC_OAM_GET_WAN_INFO                            = 0x0001050F,
    VOS_MSG_CMC_OAM_SET_SSID_MAX_USER_CONNECT               = 0x00010510,
    VOS_MSG_CMC_OAM_GET_SSID_MAX_USER_CONNECT               = 0x00010511,
    VOS_MSG_CMC_OAM_SET_SSID_CONFIG                         = 0x00010512,
    VOS_MSG_CMC_OAM_GET_SSID_CONFIG                         = 0x00010513,
    VOS_MSG_CMC_OAM_SET_CLEAN_WANNAME                       = 0x00010514,
    VOS_MSG_CMC_OAM_SET_UPGRADE_FTP                         = 0x00010515,
    VOS_MSG_CMC_OAM_GET_UPGRADE_FTP                         = 0x00010516,
    VOS_MSG_CMC_OAM_SET_WIFI_ENABLE                         = 0x00010517,
    VOS_MSG_CMC_OAM_GET_WIFI_ENABLE                         = 0x00010518,
    VOS_MSG_CMC_OAM_GET_WIFI_VERSION                        = 0x00010519,
    VOS_MSG_CMC_OAM_SET_WIFI_CFG                            = 0x0001051A,
    VOS_MSG_CMC_OAM_GET_WIFI_CFG                            = 0x0001051B,
    VOS_MSG_CMC_LOGIN_SHELL                                 = 0x1001051C,

    VOS_MSG_CMC_GET_BCNTX_VSIE                              = 0x0001051D,
    VOS_MSG_CMC_GET_PRBRX_VSIE                              = 0x0001051E,
    VOS_MSG_CMC_FLUSH_PRBRX_VSIE                            = 0x0001051F,
    VOS_MSG_CMC_DEL_PRBRX_VSIE_RCD                          = 0x00010520,
    VOS_MSG_CMC_ADD_PRBRX_VSIE_RCD                          = 0x00010521,
    VOS_MSG_CMC_GET_ROAMING                                 = 0x00010522,
    VOS_MSG_CMC_FLUSH_STAINFO                               = 0x00010523,
    VOS_MSG_CMC_ADD_STAINFO                                 = 0x00010524,
    VOS_MSG_CMC_DEL_STAINFO                                 = 0x00010525,
    VOS_MSG_CMC_SET_STAINFO                                 = 0x00010526,
    VOS_MSG_CMC_GET_BSD                                     = 0x00010527,
    VOS_MSG_CMC_GET_ROAMING_FWDER                           = 0x00010528,
    VOS_MSG_CMC_UPDATE_DNSFILTER                            = 0x00010529,
    VOS_MSG_CMC_DEL_DNSFILTER                               = 0x00010530,
    VOS_MSG_CMC_UPDATE_LANHOST_ENTRY                        = 0x00010531,
    VOS_MSG_CMC_GET_DNSFILTER_BLOCKEDTIMES_ENTRY            = 0x00010532,
    VOS_MSG_CMC_ADD_FLOW                                    = 0x00010533,
    VOS_MSG_CMC_DEL_FLOW                                    = 0x00010534,
    VOS_MSG_CMC_GET_WIFI_STATUS_INFO                        = 0x00010535,
    VOS_MSG_CMC_GET_WIFI_INFO                               = 0x00010536,
    VOS_MSG_CMC_SET_BCNTX_VSIE_STATUS                       = 0x00010537,

    VOS_MSG_CMC_MDM_FULLPATH_TODESCRIPTOR                   = 0x00010538,
    VOS_MSG_CMC_MDM_SET_VALUES                              = 0x00010539,
    VOS_MSG_CMC_MDM_SAVE_CONFIG                             = 0x0001053a,
    VOS_MSG_CMC_MDM_GET_NEXT_PATH                           = 0x0001053b,
    VOS_MSG_CMC_MDM_GET_VALUES                              = 0x0001053c,
    VOS_MSG_CMC_MDM_GET_INFO                                = 0x0001053d,
    VOS_MSG_CMC_MDM_DESCRIPTOR_TO_FULLPATH                  = 0x0001053e,
    VOS_MSG_CMC_MDM_GET_PARAM_NAMES                         = 0x0001053f,
    
    VOS_MSG_CMC_UPDATE_CHANNEL_STATS                        = 0x00010540,
    VOS_MSG_CMC_ADD_8021XRULE                               = 0x00010541,
    VOS_MSG_CMC_DEL_8021XRULE                               = 0x00010542,
    VOS_MSG_CMC_GET_STAINDEX                                = 0x00010543,
    VOS_MSG_CMC_MDM_GET_ALL_OBJS                            = 0x00010544,
    VOS_MSG_CMC_MDM_GET_ANCESTOR                            = 0x00010545,
    VOS_MSG_CMC_MDM_GET_PARA_POINTER_LOCATION               = 0x00010546,
    VOS_MSG_CMC_MDM_SET_OBJ                                 = 0x00010547,
    VOS_MSG_CMC_MDM_ADD_OBJ                                 = 0x00010548,
    VOS_MSG_CMC_MDM_DEL_OBJ                                 = 0x00010549,
    VOS_MSG_CMC_MDM_CLEAR_OBJ                               = 0x00010550,


    VOS_MSG_SSK_BASE                                        = 0x00010600,
    VOS_MSG_SSK_PARENT_CTRL                                 = 0x00010601,
    VOS_MSG_SSK_AUTOUPGRADE_PERIOD_SET                      = 0x00010602,
    VOS_MSG_SSK_OAM_MACTABLE_RAISED                         = 0x00010603,
    VOS_MSG_SSK_OAM_MACTABLE_CLEAR                          = 0x00010604,
    VOS_MSG_SSK_NETLINK_BRCM_LINK_STATUS_CHANGED            = 0x00010605,
    VOS_MSG_SSK_SHOW_PORT_INFO                              = 0x00010606, /**< Send to ssk to show portvlaninfo(MTK). */

    VOS_MSG_HAL_BASE                                        = 0x00010700,
    VOS_MSG_HAL_WLAN_STA_ONLINE                             = 0x00010701,
    VOS_MSG_HAL_WLAN_STA_OFFLINE                            = 0x00010702,
    VOS_MSG_HAL_WLAN_STA_AUTH_FAIL                          = 0x00010703,

    VOS_MSG_TR69C_BASE                                      = 0x00010800,

    VOS_MSG_HTTPD_BASE                                      = 0x00010900,

    VOS_MSG_MMC_BASE                                        = 0x00010A00,

    VOS_MSG_JIS_BASE                                        = 0x00010B00,

    VOS_MSG_DBUSA_BASE                                      = 0x00010C00,
    VOS_MSG_DBUSA_STARSSI_LOW_ALARM                         = 0x00010C01,
    VOS_MSG_DBUSA_STARSSI_QUERY_RESP                        = 0x00010C02,
    VOS_MSG_DBUSA_APRSSI_QUERY_RESP                         = 0x00010C03,
    VOS_MSG_DBUSA_STA_BSSTRANS_RESP                         = 0x00010C04,
    VOS_MSG_DBUS_SYS_VOICE_EVENTS                           = 0x00010C05,
    VOS_MSG_DBUS_TO_WLCTDM                                  = 0x00010C06,
    VOS_MSG_DBUSA_COLLECT_WIFI_INFO                         = 0x00010C07,
    VOS_MSG_DBUSA_WIFI_CONN_FAILURE                         = 0x00010C09,
    VOS_MSG_DBUS_NOTICE_VPN_CONFIG_CHANGE                   = 0x00010C0A,

    VOS_MSG_MCPD_BASE                                       = 0x00010D00,

    VOS_MSG_VODSL_BASE                                      = 0x00010E00,

    VOS_MSG_MON_BASE                                        = 0x00010F00,
    VOS_MSG_MON_OUT                                         = 0x00010F01,

    VOS_MSG_WLAN_BASE                                       = 0x00011000,
    VOS_MSG_WLAN_VIRTUAL_WPS_PRESSED                        = 0x00011001,

    /*wlctdm msg*/
    VOS_MSG_WLCTDM_BASE                                     = 0x00011100,
    VOS_MSG_WLCTDM_COMMON_TYPE                              = 0x00011101,
    VOS_MSG_WLCTDM_COLLECT_WIFI_INFO                        = 0x00011102,
    VOS_MSG_WLCTDM_CHANNEL_COLLECT_REQUEST                  = 0x00011103,

    /* traffic monitor */
    VOS_MSG_TRAFFIC_MONITOR_BASE                            = 0x00011200,
    VOS_MSG_TRAFFIC_MONITOR_EDIT_ADDRESS                    = 0x00011201,

    /*omdiag msg*/
    VOS_MSG_OMDIAG_BASE                                     = 0x00011300,
    VOS_MSG_OMDIAG_EXCEED_THRESHOLD                         = 0x00011301,
    VOS_MSG_OMDIAG_GET_PROCESS                              = 0x00011302,

    VOS_MSG_DEV_PROBE_BASE                                  = 0x00011400,
    VOS_MSG_DEV_PROBE_ONLINE                                = 0x00011401,
    VOS_MSG_DEV_PROBE_OFFLINE                               = 0x00011402,

    /*ddns msg*/
    VOS_MSG_PHDDNS_BASE                                     = 0x00011500,
    VOS_MSG_PHDDNS_SEND_STATUS_MESSAGE                      = 0x00011501,
    VOS_MSG_PHDDNS_SEND_DOMAIN_MESSAGE                      = 0x00011502,

    /*cmc2 interface stack msg*/
    VOS_MSG_CMC2_INTFSTACK_BASE                             = 0x00011600,
    VOS_MSG_CMC2_INTFSTACK_LOWERLAYERS_CHANGED              = 0x00011601,
    VOS_MSG_CMC2_INTFSTACK_STATIC_ADDRESS_CONFIG            = 0x00011602,
    VOS_MSG_CMC2_INTFSTACK_ALIAS_CHANGED                    = 0x00011603,
    VOS_MSG_CMC2_INTFSTACK_PROPAGATE_STATUS                 = 0x00011604,
    VOS_MSG_CMC2_INTFSTACK_OBJECT_DELETED                   = 0x00011605,

    VOS_MSG_SYSTEM_BOOT                                     = 0x10000250, /**< system has booted, delivered to apps
                                                                            *   EIF_LAUNCH_ON_STARTUP set in their
                                                                            *   VosEntityInfo.flags structure.
                                                                            */
    VOS_MSG_APP_LAUNCHED                                    = 0x10000251, /**< Used by apps to confirm that launch succeeded.
                                                                            *   Sent from app to smd in vosMsg_init.
                                                                            */
    VOS_MSG_WAN_LINK_UP                                     = 0x10000252, /**< wan link is up (includes dsl, ethernet, etc) */
    VOS_MSG_WAN_LINK_DOWN                                   = 0x10000253, /**< wan link is down */
    VOS_MSG_WAN_CONNECTION_UP                               = 0x10000254, /**< WAN connection is up (got IP address) */
    VOS_MSG_WAN_CONNECTION_DOWN                             = 0x10000255, /**< WAN connection is down (lost IP address) */
    VOS_MSG_ETH_LINK_UP                                     = 0x10000256, /**< eth link is up (only if eth is used as LAN interface) */
    VOS_MSG_ETH_LINK_DOWN                                   = 0x10000257, /**< eth link is down (only if eth is used as LAN interface) */
    VOS_MSG_USB_LINK_UP                                     = 0x10000258, /**< usb link is up (only if eth is used as LAN interface) */
    VOS_MSG_USB_LINK_DOWN                                   = 0x10000259, /**< usb link is down (only if eth is used as LAN interface) */
    VOS_MSG_ACS_CONFIG_CHANGED                              = 0x1000025A, /**< ACS configuration has changed. */
    VOS_MSG_DELAYED_MSG                                     = 0x1000025B, /**< This message is delivered to when delayed msg timer expires. */
    VOS_MSG_TR69_ACTIVE_NOTIFICATION                        = 0x1000025C, /**< This message is sent to tr69c when one or more
                                                                            *   parameters with active notification attribute
                                                                            *   has had their value changed.
                                                                            */
    VOS_MSG_WAN_ERRORSAMPLES_AVAILABLE                      = 0x1000025D,/**< WAN connection has vectoring error samples available */
    VOS_MSG_WAN_ERRORSAMPLES_AVAILABLE_LINE1                = 0x1000025E,/**< WAN connection has vectoring error samples available for line 1, keep VOS_MSG_WAN_ERRORSAMPLES_AVAILABLE+1*/
    VOS_MSG_MDM_INIT_STATE                                  = 0x10000262, /**< Sent from ssk to smd when shmid is obtained. */
    VOS_MSG_MDM_INITIALIZED                                 = 0x10000263, /**< Sent from ssk to smd when MDM has been initialized. */
    VOS_MSG_DHCPC_STATE_CHANGED                             = 0x10000264, /**< Sent from dhcp client when state changes, see also DhcpcStateChangeMsgBody */
    VOS_MSG_PPPOE_STATE_CHANGED                             = 0x10000265, /**< Sent from pppoe when state changes, see also PppoeStateChangeMsgBody */
    VOS_MSG_DHCP6C_STATE_CHANGED                            = 0x10000266, /**< Sent from dhcpv6 client when state changes, see also Dhcp6cStateChangeMsgBody */
    VOS_MSG_PING_STATE_CHANGED                              = 0x10000267, /**< Ping state changed (completed, or stopped) */
    VOS_MSG_DHCPD_RELOAD		                                = 0x10000268, /**< Sent to dhcpd to force it reload config file without restart */
    VOS_MSG_DHCPD_DENY_VENDOR_ID	                          = 0x10000269, /**< Sent from dhcpd to notify a denied request with some vendor ID */
    VOS_MSG_DHCPD_HOST_INFO                                 = 0x1000026A, /**< Sent from dhcpd to ssk to inform of lan host add/delete */
    VOS_MSG_TRACERT_STATE_CHANGED                           = 0x1000026B, /**< Traceroute state changed (completed, or stopped) */
    VOS_MSG_DNSPROXY_RELOAD	                                = 0x10000270, /**< Sent to dnsproxy to force it reload config file without restart */
    VOS_MSG_SNTP_STATE_CHANGED 	                            = 0x10000271, /**< SNTP state changed */
    VOS_MSG_DNSPROXY_IPV6_CHANGED                           = 0x10000272, /**< Sent to dnsproxy to inform the DProxy IPv6 DNS server address */
    VOS_MSG_DNSPROXY_GET_STATS	                            = 0x10000273, /**< Sent to dnsproxy to get DNS query error statistic */
    VOS_MSG_DNSPROXY_QUERY                                  = 0x10000274, /**<Send from dns proxy to smd/ssk? for binding                                                       dns query **/
    VOS_MSG_MCPD_RELOAD	                                    = 0x10000276, /**< Sent to mcpd to force it reload config file without restart */
    VOS_MSG_MCPD_CTL   	                                    = 0x10000277, /**< Sent to mcpd to force it reload config file without restart */
    VOS_MSG_MCPD_MEM_TRACE   	                              = 0x10000278, /**< Sent to mcpd to show memory used info */
    VOS_MSG_MCPD_SHOW_RUNNING                               = 0x10000279, /**< Send to mcpd to show running info such as config, obj tree and so on. */
    VOS_MSG_CONFIG_WRITTEN                                  = 0x10000280, /**< Event sent when a config file is written. */
    VOS_MSG_CONFIG_UPLOAD_COMPLETE                          = 0x10000281, /**< Event sent when a remote configuration cycle has ended. */
    VOS_MSG_MCPD_MCAST_MEMBER_NUM                           = 0x10000282, /**< Sent to mcpd to get current member. */
    VOS_MSG_OMDIAG_UDP_ATTA                                 = 0x10000283,
    VOS_MSG_OMDIAG_TCP_ATTA                                 = 0x10000284,
    VOS_MSG_PING_LINK_STATE_CHANGED                         = 0x10000285,/*ct link maintenance ping state info. add by daizhiguo*/

    VOS_MSG_SET_PPP_UP                                      = 0x10000290, /* Sent to ppp when set ppp up manually */
    VOS_MSG_SET_PPP_DOWN                                    = 0x10000291, /* Sent to ppp when set ppp down manually */  

    VOS_MSG_DNSPROXY_DUMP_STATUS                            = 0x100002A1, /* Tell dnsproxy to dump its current status */
    VOS_MSG_DNSPROXY_DUMP_STATS                             = 0x100002A2, /* Tell dnsproxy to dump its statistics */
    VOS_MSG_RASTATUS6_INFO                                  = 0x100002A3, /**< Sent from rastatus6 when RA is received, see also RAStatus6MsgBody */
    VOS_MSG_IPV6_ROUTE_CHANGED                              = 0x100002A4, /**< Ipv6 Route changed*/
    VOS_MSG_DEF_GATEWAY_CHANGED                             = 0x100002A5, /**<Route changed*/

    VOS_MSG_WLAN_RESTART                                    = 0x10000297,
    VOS_MSG_WLAN_READ_ASSOC_DEV                             = 0x10000298,
    VOS_MSG_WLAN_READ_WPS_NVRAM                             = 0x10000299,
    VOS_MSG_WLAN_CHANGED                                    = 0x10000300,  /**< wlmngr jhc*/
    VOS_MSG_SNMPD_CONFIG_CHANGED                            = 0x10000301, /**< ACS configuration has changed. */
    VOS_MSG_MANAGEABLE_DEVICE_NOTIFICATION_LIMIT_CHANGED    = 0x10000302, /**< Notification Limit of number of management device. */
    VOS_MSG_SNMP_JUDGE_ISINBRIDGE                           = 0x10000303,

    VOS_MSG_STORAGE_ADD_PHYSICAL_MEDIUM                     = 0x10000310,
    VOS_MSG_STORAGE_REMOVE_PHYSICAL_MEDIUM                  = 0x10000311,
    VOS_MSG_STORAGE_ADD_LOGICAL_VOLUME                      = 0x10000312,
    VOS_MSG_STORAGE_REMOVE_LOGICAL_VOLUME                   = 0x10000313,

    /* mobile manage client */
    VOS_MSG_MOBILE_HEATBEAT_FOR_REG_TIMER_EVENT             = 0x10000400,
    VOS_MSG_MOBILE_HEATBEAT_TCP_TIMER_EVENT                 = 0x10000401,               
    VOS_MSG_MOBILE_TIMEOUT_TIMER_EVENT                      = 0x10000402,
    VOS_MSG_MOBILE_ERROR_TCP_TIMER_EVENT                    = 0x10000403,
    VOS_MSG_MOBILE_ERROR_UDP_TIMER_EVENT                    = 0x10000404,
    VOS_MSG_MOBILE_AUTH_FAIL_TIMER_EVENT                    = 0x10000405,
    VOS_MSG_MOBILE_GENERAL_FAIL_TIMER_EVENT                 = 0x10000406,
    VOS_MSG_MOBILE_UDP_RESPORT_TIMER_EVENT                  = 0x10000407,
    VOS_MSG_MOBILE_REPLY_TIMEOUT_TIMER_EVENT                = 0x10000408,
    VOS_MSG_MOBILE_UDP_RESPORT_FOR_REG_TIMER_EVENT          = 0x10000409,
    VOS_MSG_MOBILE_UDP_CYCLE_FOR_REG_TIMER_EVENT            = 0x10000410,
    VOS_MSG_MOBILE_TIMEOUT_FOR_DISTRIBUTE_TIMER_EVENT       = 0x10000411,
    VOS_MSG_MOBILE_HEATBEAT_FOR_REG_TIMER2_EVENT            = 0x10000412,   
    VOS_MSG_MOBILE_TIMEOUT_TIMER_DEF_FOR_DIST_EVENT         = 0x10000413,   
    VOS_MSG_MOBILE_TIMEOUT_TIMER_RND_FOR_DIST_EVENT         = 0x10000414,   
    VOS_MSG_MOBILE_TIMEOUT_TIMER_DEF_FOR_REG_EVENT          = 0x10000415,   
    VOS_MSG_MOBILE_TIMEOUT_TIMER_RND_FOR_REG_EVENT          = 0x10000416,   

    VOS_MSG_HTTP_TRAFFIC_MONITOR_BASE                       = 0x10000500,
    VOS_MSG_HTTP_TRAFFIC_MONITOR_EDIT_ADDRESS               = 0x10000501,

    VOS_MSG_DNSPROXY_BASE                                   = 0x10000600,
    VOS_MSG_DNSPROXY_SHOW_DNSFILTER_CONFIG                  = 0x10000601,
    VOS_MSG_DNSPROXY_SHOW_VPN_URL_CONFIG                    = 0x10000602,

    VOS_MSG_REGISTER_DELAYED_MSG                            = 0x10000800, /**< request a message sometime in the future. */
    VOS_MSG_UNREGISTER_DELAYED_MSG                          = 0x10000801, /**< cancel future message delivery. */
    VOS_MSG_REGISTER_EVENT_INTEREST                         = 0x10000802, /**< request receipt of the specified event msg. */
    VOS_MSG_UNREGISTER_EVENT_INTEREST                       = 0x10000803, /**< cancel receipt of the specified event msg. */
    VOS_MSG_DIAG                                            = 0x10000805, /**< request diagnostic to be run */
    VOS_MSG_TR69_GETRPCMETHODS_DIAG                         = 0x10000806, /**< request tr69c send out a GetRpcMethods */
    VOS_MSG_DSL_LOOP_DIAG_COMPLETE                          = 0x10000807, /**< dsl loop diagnostic completes */

    VOS_MSG_START_APP                                       = 0x10000808, /**< request smd to start an app; pid is returned in the wordData */
    VOS_MSG_RESTART_APP                                     = 0x10000809, /**< request smd to stop and then start an app; pid is returned in the wordData */
    VOS_MSG_STOP_APP                                        = 0x1000080A, /**< request smd to stop an app */
    VOS_MSG_IS_APP_RUNNING                                  = 0x1000080B, /**< request to check if the the application is running or not */
    VOS_MSG_APP_TERMINATED                                  = 0x1000080C, /**< register to smd for application termination info. */
    VOS_MSG_TERMINATE                                       = 0x1000080D,  /**< request app to terminate, a response means action has started. */
    VOS_MSG_RECOVER_APP                                     = 0x1000080E, /*< request smd to recover an app; pid is returned in the wordData */
    
    VOS_MSG_FTPD_STATE_CHANGE                               = 0X10000810, /*ftpd state change*/

    VOS_MSG_UPNPD_UPDATE_DEVICE                             = 0X10000815, /* from DLNA to SSK,  to update device info */

    VOS_MSG_VERSION_SWITCH                                  = 0X10000820,

    VOS_MSG_REQUEUE                                         = 0X10000830,
    VOS_MSG_REREQUEST                                       = 0X10000831,
    VOS_MSG_WATCHDOG_HEARTBEAT                              = 0X10000832,
    VOS_MSG_CLI_SET_WATCHDOG                                = 0X10000833,
    VOS_MSG_WATCHDOG_STOP                                   = 0X10000834,

    VOS_MSG_REBOOT_SYSTEM                                   = 0x10000850,  /**< request smd to reboot, a response means reboot sequence has started. */

    VOS_MSG_SET_LOG_LEVEL                                   = 0x10000860,  /**< request app to set its log level. */
    VOS_MSG_SET_LOG_DESTINATION                             = 0x10000861,  /**< request app to set its log destination. */
    VOS_MSG_REDIRECT_STD                                    = 0x10000862,  /**< request app to set its log destination. */
    VOS_MSG_REVERT_STD                                      = 0x10000863,  /**< request app to set its log destination. */

    VOS_MSG_MEM_DUMP_STATS                                  = 0x1000086A,  /**< request app to dump its memstats */
    VOS_MSG_MEM_DUMP_TRACEALL                               = 0x1000086B,  /**< request app to dump all of its mem leak traces */
    VOS_MSG_MEM_DUMP_TRACE50                                = 0x1000086C,  /**< request app to its last 50 mem leak traces */
    VOS_MSG_MEM_DUMP_TRACECLONES                            = 0x1000086D,  /**< request app to dump mem leak traces with clones */

    VOS_MSG_LOAD_IMAGE_STARTING                             = 0x10000870,  /**< notify smd that image network loading is starting. */
    VOS_MSG_LOAD_IMAGE_DONE                                 = 0x10000871,  /**< notify smd that image network loading is done. */
    VOS_MSG_GET_CONFIG_FILE                                 = 0x10000872,  /**< ask smd for a copy of the config file. */
    VOS_MSG_VALIDATE_CONFIG_FILE                            = 0x10000873,  /**< ask smd to validate the given config file. */
    VOS_MSG_WRITE_CONFIG_FILE                               = 0x10000874,  /**< ask smd to write the config file. */
    VOS_MSG_VENDOR_CONFIG_UPDATE                            = 0x10000875,  /**<  the config file. */

    VOS_MSG_GET_WAN_LINK_STATUS                             = 0x10000880,  /**< request current WAN LINK status. */
    VOS_MSG_GET_WAN_CONN_STATUS                             = 0x10000881,  /**< request current WAN Connection status. */
    VOS_MSG_GET_LAN_LINK_STATUS                             = 0x10000882,  /**< request current LAN LINK status. */

    VOS_MSG_WATCH_WAN_CONNECTION                            = 0x10000890,  /**< request ssk to watch the dsl link status and then change the connectionStatus for bridge, static MER and ipoa */
    VOS_MSG_WATCH_DSL_LOOP_DIAG                             = 0x10000891,  /**< request ssk to watch the dsl loop diag and then update the stats */

    VOS_MSG_MCAST_OAM_MCASTVLAN                             = 0x10000895,            // branch 0xc7,leaf 41
    VOS_MSG_MCAST_OAM_MCASTTAGOP                            = 0x10000896,            // branch 0xc7,leaf 42
    VOS_MSG_MCAST_OAM_MCASTSWITCH                           = 0x10000897,            // branch 0xc7,leaf 43       
    VOS_MSG_MCAST_OAM_MCASTMAXNUM                           = 0x10000898,            // branch 0xc7,leaf 45
    VOS_MSG_MCAST_OAM_SUPPORTFASTLEAVE                      = 0x10000899,            // branch 0xc7,leaf 46
    VOS_MSG_MCAST_OAM_ADMINFASTLEAVE                        = 0x1000089A,            // branch 0xc7,leaf 47
    VOS_MSG_MCAST_OAM_MCASTADDLIST                          = 0x1000089B,            // branch 0xc7,leaf 45 add entry
    VOS_MSG_MCAST_OAM_MCASTDELLIST                          = 0x1000089c,            // branch 0xc7,leaf 45 del entry
    VOS_MSG_MCAST_OAM_MCASTDELALL                           = 0x1000089d,            // branch 0xc7,leaf 41 del all  


    VOS_MSG_GET_LEASE_TIME_REMAINING                        = 0x100008A0,  /**< ask dhcpd how much time remains on lease for particular LAN host */
    VOS_MSG_GET_DEVICE_INFO                                 = 0x100008A1,  /**< request system/device's info */
    VOS_MSG_REQUEST_FOR_PPP_CHANGE                          = 0x100008A2,  /**< request for disconnect/connect ppp  */
    VOS_MSG_EVENT_SNTP_SYNC                                 = 0x100008A3,  /**< sntp send sync delta value */

    VOS_MSG_GET_WAN_VLANID_INFO                             = 0x100008A4,

    VOS_MSG_GET_LEASE_IP_TABLE                              = 0x100008A5,

    VOS_MSG_UPDATE_LAN_INTF_BIND_INFO                       = 0x100008A6, //change  by lqy 2013.5.2

    VOS_MSG_IGMPSNOOPING_ON                                 = 0x100008A7,  /*tell mcpd that igmp snooping is on*/
    VOS_MSG_IGMPSNOOPING_OFF                                = 0x100008A8,
    VOS_MSG_IGMP_OMCI_CONFIG                                = 0x100008A9,

    VOS_MSG_IGMP_OMCI_ADD_CONTROL_MULTICAST_GROUP           = 0x100008AA,
    VOS_MSG_IGMP_OMCI_DEL_CONTROL_MULTICAST_GROUP           = 0x100008AB,
    VOS_MSG_MCAST_UPDATE_SRC_FILTER_CFG                     = 0x100008AC,
    VOS_MSG_MCAST_UPDATE_SRC_FILTER_ENTRY                   = 0x100008AD,
    VOS_MSG_UPDATE_LAN_MCAST_RULE                           = 0x100008AE,
    
    //multicast flow can arrive in LAN side when mld snooping closed in web
    VOS_MSG_MLDSNOOPING_ON                                  = 0x100008B7,  /*tell mcpd that mld snooping is on*/
    VOS_MSG_MLDSNOOPING_OFF                                 = 0x100008B8,  /*tell mcpd that mld snooping is off*/

    VOS_MSG_QOS_DHCP_OPT60_COMMAND                          = 0x100008C0, /**< QoS Vendor Class ID classification command */
    VOS_MSG_QOS_DHCP_OPT77_COMMAND                          = 0x100008C1, /**< QoS User   Class ID classification command */

    VOS_MSG_GPON_WAN_LINK_INFO                              = 0x100008D0,  /**< GPON WAN LINK connection info */
    VOS_MSG_GPON_SET_VIRTUAL_ETH_LINK_INFO                  = 0x100008D1,  /**< Set GPON Virtual Eth If LINK connection info */
    VOS_MSG_OMCI_WAN_ME_CFG_SET                             = 0x100008D2,
    VOS_MSG_OMCI_ZYXEL_MIB_RESET                            = 0x100008D3, /*OLT execatue MIB reset handle, this is add for the ZYXEL private WAN ME*/
    VOS_MSG_OMCI_FILE_TRANS_TRIGGER                         = 0x100008D4,/*file transfer trigger*/
    VOS_MSG_OMCI_ZYXEL_RESET_ACTION                         = 0x100008D5,  /*zyxel reset default action*/
    VOS_MSG_OMCI_WAN_ME_CFG_2_SET                           = 0x100008D6,

    VOS_MSG_VOICE_CONFIG_CHANGED                            = 0x10002000, /**< Voice Configuration parameter changed private event msg. */
    VOS_MSG_VODSL_BOUNDIFNAME_CHANGED                       = 0x10002001, /**< vodsl BoundIfName param has changed. */
    VOS_MSG_SHUTDOWN_VODSL                                  = 0x10002002, /**< Voice shutdown request. */
    VOS_MSG_START_VODSL                                     = 0x10002003, /**< Voice start request. */
    VOS_MSG_REBOOT_VODSL                                    = 0x10002004, /**< Voice reboot request. This is for the voice reboot command */
    VOS_MSG_RESTART_VODSL                                   = 0x10002005, /**< Voice re-start request. This is to restart the call manager when the IP address changes*/
    VOS_MSG_INIT_VODSL                                      = 0x10002006, /**< Voice init request. */
    VOS_MSG_DEINIT_VODSL                                    = 0x10002007, /**< Voice init request. */
    VOS_MSG_RESTART_VODSL_CALLMGR                           = 0x10002008, /**< Voice call manager re-start request. */
    VOS_MSG_DEFAULT_VODSL                                   = 0x10002009, /**< Voice call manager set defaults request. */

    VOS_MSG_VOICE_NTR_CONFIG_CHANGED                        = 0x10002010, /**< Voice NTR Configuration parameter changed private event msg. */

    VOS_MSG_VOICE_GET_RTP_STATS                             = 0x10002011, /**< Voice get RTP PM stats msg (OMCI). */
    VOS_MSG_UPDATE_PORT_FIREWALL                            = 0x10002012, /**< Voice modify local port then send msg to ssk reset firewall. */
    VOS_MSG_START_VOIP_LINE_TEST                            = 0x10002013, /**< Start voip line test */


    VOS_MSG_VOICE_DIAG                                      = 0x10002100, /**< request voice diagnostic to be run */
    VOS_MSG_VOICE_STATISTICS_REQUEST                        = 0x10002101, /**< request for Voice call statistics */
    VOS_MSG_VOICE_STATISTICS_RESPONSE                       = 0x10002102, /**< response for Voice call statistics */
    VOS_MSG_VOICE_STATISTICS_RESET                          = 0x10002103, /**< request to reset Voice call statistics */
    VOS_MSG_VOICE_CM_ENDPT_STATUS                           = 0x10002104, /**< request for Voice Line obj */
    VOS_MSG_VODSL_IS_READY_FOR_DEINIT                       = 0x10002105, /**< query if the voice app is ready to deinit */

    /* add by litianbo on 20101102 for IAD Diagnostics State */
    VOS_MSG_VOICE_IADDIAGNOSTICS_STATE                      = 0x10002110, /**< IAD Diagnostics State */
    /* add end by litianbo */
    /* add by litianbo on 20101217 for Simulate Test */
    VOS_MSG_VOICE_SIMULATE_TESTS_STATE                      = 0x10002111, /**< Simulate Tests State */
    /* add end by litianbo */
    /* add by litianbo on 20101217 for Statistic information */
    VOS_MSG_VOICE_STATISTIC_INFORMATION                     = 0x10002112,  /**< Statistic information */
    /* add end by litianbo */
    /* add by hujf on 20140416 for CT GD Requirement: Record last register failure reason. */
    VOS_MSG_VOICE_LAST_REG_FAIL_INFORMATION                 = 0x10002113,  /**< get last reg fail information  */
    /* liuwc add end */
    VOS_MSG_VOICE_LINE_TEST_STATUS                          = 0x10002114,  /**< Line status test information */

    VOS_MSG_GET_GPON_OMCI_STATS                             = 0x10002200, /**< request GPON OMCI statistics */
    VOS_MSG_OMCI_COMMAND_REQUEST                            = 0x10002201, /**< GPON OMCI command message request */
    VOS_MSG_OMCI_COMMAND_RESPONSE                           = 0x10002202, /**< GPON OMCI command message response */
    VOS_MSG_OMCI_DEBUG_GET_REQUEST                          = 0x10002203, /**< GPON OMCI debug get message request */
    VOS_MSG_OMCI_DEBUG_GET_RESPONSE                         = 0x10002204, /**< GPON OMCI debug get message response */
    VOS_MSG_OMCI_DEBUG_SET_REQUEST                          = 0x10002205, /**< GPON OMCI debug set message request */
    VOS_MSG_OMCI_DEBUG_SET_RESPONSE                         = 0x10002206, /**< GPON OMCI debug set message response */
    VOS_MSG_OMCI_DEBUG_MKERR_SWDLERR1                       = 0x10002207, /**< GPON OMCI debug drop next section to cause missing section error */
    VOS_MSG_OMCI_DEBUG_MKERR_SWDLERR2                       = 0x10002208, /**< GPON OMCI debug drop final section of next window to cause no response on final window section error */
    VOS_MSG_OMCI_DEBUG_MKERR_SWDLERR3                       = 0x10002209, /**< GPON OMCI debug corrupt next section to cause CRC error on SW DL image */

    VOS_MSG_OMCI_MCPD_SEND_REPLY                            = 0x10002220, /**< MCPD to OMCID message to send and get reply IGMP message */
    VOS_MSG_OMCI_CAPTURE_STATE_ON                           = 0x10002230, /**< Start the capture of OMCI msgs from OLT */
    VOS_MSG_OMCI_CAPTURE_STATE_OFF                          = 0x10002231, /**< Stop the capture of OMCI msgs from OLT */
    VOS_MSG_OMCI_CAPTURE_REPLAY_ON                          = 0x10002232, /**< Start the playback of OMCI msgs */
    VOS_MSG_OMCI_CAPTURE_REPLAY_OFF                         = 0x10002233, /**< Start the playback of OMCI msgs */
    VOS_MSG_OMCI_CAPTURE_VIEW                               = 0x10002234, /**< Start the display OMCI msgs from a file */
    VOS_MSG_OMCI_CAPTURE_DOWNLOAD                           = 0x10002235, /**< Download internal OMCI msg capture file */
    VOS_MSG_OMCI_CAPTURE_UPLOAD                             = 0x10002236, /**< Upload a file of OMCI msgs to replace internal file */
    VOS_MSG_OMCI_PROMISC_SET_REQUEST                        = 0x10002240, /**< GPON OMCI Promisc set message request */
    VOS_MSG_OMCI_PROMISC_SET_RESPONSE                       = 0x10002241, /**< GPON OMCI Promisc set message response */
    VOS_MSG_OMCI_GPON_WAN_SERVICE_STATUS_CHANGE             = 0x10002250, /**< OMCI-->RG - Wan service status change notification */
    VOS_MSG_OMCI_RG_WAN_SERVICE_STAUTS_CHANGE               = 0x10002251, /**< RG-->OMCI - WAN service status change notification */
    VOS_MSG_OMCI_MCPD_MIB_RESET                             = 0x10002252, /**< OMCID to MCPD Mib Reset message to clean up  VLANCTL rules and CMF flows */
    VOS_MSG_OMCI_VOIP_MIB_RESET                             = 0x10002253, /**< OMCID to VOIP Mib Reset message to clean up Voice stack */

    VOS_MSG_RECEIVE_OMCI_PACKET                             = 0x10002254,
    VOS_MSG_TRANSMIT_OMCI_PACKET                            = 0x10002255,
    VOS_MSG_RANGING_STATE_CHANGE                            = 0x10002256,
    VOS_MSG_PLOAM_ASSIGN_ONU_ID                             = 0x10002257,
    VOS_MSG_PLOAM_ENCRYPTED_PORT_ID                         = 0x10002258,
    VOS_MSG_PLOAM_ASSIGN_ALLOC_ID                           = 0x10002259,
    VOS_MSG_PLOAM_CONFIGURE_PORT_ID                         = 0x1000225A,
    VOS_MSG_PON_CLI_PROCESS                                 = 0x1000225B,
    VOS_MSG_PLOAM_DOWNSTREAM_PACKET                         = 0X1000225C,
    VOS_MSG_IMAGE_DOWNLOAD                                  = 0X1000225D,
    VOS_MSG_OMCI_WAN_STATUS_CHANGE                          = 0x1000225E,
    VOS_MSG_OMCI_FILE_TRANS_STATUS_CHANGE                   = 0x1000225F,
    VOS_MSG_OMCI_ZYXEL_CFG_CHANGED_STATUS                   = 0x10002260,
    VOS_MSG_PON_LINKUP_UPDATE_INTERNET_LED_STATUS           = 0x10002261,
    VOS_MSG_CMF_SEND_REQUEST                                = 0x10002301, /**< CMF File Send message request */
    VOS_MSG_CMF_SEND_RESPONSE                               = 0x10002302, /**< CMF File Send message response */

    VOS_MSG_OMCIPMD_SYNC                                    = 0x10002400, /**< OMCIPMD command message request to re-sync timers and PMs. */
    VOS_MSG_OMCIPMD_DEBUG                                   = 0x10002401, /**< OMCIPMD command to turn debug on/off for specific PMs. */
    VOS_MSG_OMCIPMD_MIB_RESET                               = 0x10002402, /**< OMCIPMD command to execute MIB_RESET. */
    VOS_MSG_OMCIPMD_ALARM_SEQ_SET                           = 0x10002403, /**< OMCIPMD command to set OMCI Alarm Sequence Number. */
    VOS_MSG_OMCIPMD_ALARM_SEQ_GET                           = 0x10002404, /**< OMCIPMD command to get OMCI Alarm Sequence Number. */
    VOS_MSG_OMCIPMD_SYNC_MIB_ADMINSTATE                     = 0x10002405, /**< Make OMCIPMD to sync the admin states from CMC. */
    VOS_MSG_OMCIPMD_GET_STATS                               = 0x10002406, /**< OMCIPMD command to get OMCI PM stats for CLI. */

    VOS_MSG_OMCIPMD_MCAST_COUNTER_REQ                       = 0x10002410, /**< OMCIPMD command message request for multicast RX octets. */
    VOS_MSG_OMCIPMD_MCAST_COUNTER_RSP                       = 0x10002411, /**< OMCIPMD command message response for multicast RX octets. */

    VOS_MSG_OMCID_OMCIPMD_REQUEST                           = 0x10002420, /**< OMCIPMD command message request. */
    VOS_MSG_ENCAPSULATED_OMCI                               = 0x10002421, /**< OMCIPMD encapsulated OMCI raw frame. */

    VOS_MSG_REQUEST_DU_STATE_CHANGE                         = 0x10002500, /**< request Deployment Unit state change */
    VOS_MSG_REQUEST_EU_STATE_CHANGE                         = 0x10002501, /**< request Execution Unit state change */
    VOS_MSG_GET_FILE_FROM_SERVER                            = 0x10002502, /**< get file from file server */
    VOS_MSG_PUT_FILE_TO_SERVER                              = 0x10002503, /**< put file on file server */
    VOS_MSG_OSGI_EXE_ENV_STATUS_CHANGE                      = 0x10002504, /**< OSGI execution environment state change */
    VOS_MSG_REQUEST_BUNDLE_LIST                             = 0x10002505, /**< request for bundle list */
    VOS_MSG_GET_NTH_GPON_WAN_LINK_INFO                      = 0x10002506,  /**< Get GPON WAN LINK connection info */
    VOS_MSG_RESPONSE_DU_STATE_CHANGE                        = 0x10002507, /**< response Deployment Unit state change */
    VOS_MSG_GPON_LINK_STATUS_CHANGE                         = 0x10002508, /**< GPON Link Status Change */
    VOS_MSG_START_EE                                        = 0x10002509,
    VOS_MSG_STOP_EE                                         = 0x10002510,
    VOS_MSG_OSGI_MSG_DEBUG                                  = 0x10002511, /** Send debug message to felix */
    
    VOS_MSG_BMU_CLI                                         = 0x10002600, /**< Internal commands from command line interface */
    VOS_MSG_BMU_GET_STATUS                                  = 0x10002601, /**<  */

    VOS_MSG_OSGID_PRINT                                     = 0x10002654, /**< OSGID command to print debug info to console */

    VOS_MSG_SRPC_CMC                                        = 0x10002700,
    VOS_MSG_SRPC_HAL                                        = 0x10002701,
    VOS_MSG_SRPC_CMC_JIS                                    = 0x10002702,
    VOS_MSG_CMC_INTF                                        = 0x10002703,
    VOS_MSG_CMC_RPC                                         = 0x10002704,
    VOS_MSG_REMOTE_CLI_SET_MDM_OBJECT                       = 0x10002B00,
    VOS_MSG_REMOTE_CLI_SET_MDM_OBJECT_RT                    = 0x10002B01,
    VOS_MSG_REMOTE_CLI_SHOW_MDM_OBJECT                      = 0x10002B02,
    VOS_MSG_REMOTE_CLI_SHOW_MDM_OBJECT_RT                   = 0x10002B03,
    VOS_MSG_REMOTE_CLI_ADD_MDM_OBJECT                       = 0x10002B04,
    VOS_MSG_REMOTE_CLI_ADD_MDM_OBJECT_RT                    = 0x10002B05,
    VOS_MSG_REMOTE_CLI_DEL_MDM_OBJECT                       = 0x10002B06,
    VOS_MSG_REMOTE_CLI_DEL_MDM_OBJECT_RT                    = 0x10002B07,
    VOS_MSG_REMOTE_CLI_SHOW_MDM                             = 0x10002B08,
    VOS_MSG_REMOTE_CLI_SHOW_MDM_RT                          = 0x10002B09,
    VOS_MSG_REMOTE_CLI_SET_MDM_PATH_RT                      = 0x10002B0A,
    VOS_MSG_REMOTE_CLI_SHOW_MDM_PATH_RT                     = 0x10002B0B,
    VOS_MSG_REMOTE_CLI_ADD_MDM_PATH_RT                      = 0x10002B0C,
    VOS_MSG_REMOTE_CLI_DEL_MDM_PATH_RT                      = 0x10002B0D,
    VOS_MSG_REMOTE_CLI_SHOW_MDM_TREE                        = 0x10002B0E,
    VOS_MSG_REMOTE_CLI_SHOW_MDM_TREE_RT                     = 0x10002B0F,
    VOS_MSG_REMOTE_CLI_SHOW_OBJ_TRACE                       = 0x10002B10,
    VOS_MSG_TR69_WAN_CHANGE                                 = 0x10002C00,
    VOS_MSG_NET_DOWN                                        = 0x10002C02,
    VOS_MSG_VOICE_IFNAMECHANGED                             = 0x10002C03,
    VOS_MSG_DNS_CHANGED                                     = 0x10002C04,

    VOS_MSG_SET_WAN_CONN_ID                                 = 0X10002C05,
    VOS_MSG_CTMDW_WAN_CONNECTION_CHANGED                    = 0x10002C06,
    VOS_MSG_SET_LOG_SAVETOFLASH                             = 0x10002C07,
    VOS_MSG_SET_LOG_CLEARINFLASH                            = 0x10002C08,
    VOS_MSG_LOG_REQUEST_SAVE_TO_FLASH                       = 0x10002C09,
    VOS_MSG_LOG_REQUEST_READ_FROM_FLASH                     = 0x10002C0A,
    VOS_MSG_LOG_REQUEST_CLEAR_FLASH                         = 0x10002C0B,
    VOS_MSG_REQUEST_WRITE_IMAGE                             = 0x10002C0C,
    VOS_MSG_GET_IMAGE_FLASH_SIZE                            = 0x10002C0D,
    VOS_MSG_GET_IMAGE_TAG_SIZE                              = 0x10002C0E,
    VOS_MSG_GET_CONFIG_FLASH_SIZE                           = 0x10002C0F,

    VOS_MSG_SEND_NET_PARAM_TO_VTP                           = 0x10002D10,  /**< press apply and get interface status*/
    VOS_MSG_SEND_IFNAME_TO_VTP                              = 0x10002D11,
    VOS_MSG_RESET_ETH_PORT                                  = 0x10002D12,
    
    VOS_MSG_SEND_LINE_TEST_TO_VTP                           = 0x10002D13,
    
    VOS_MSG_CT_ALARM_CHANGED                                = 0x10003000,
    VOS_MSG_CT_MONITOR_CHANGED                              = 0x10003001,

    VOS_MSG_CT_USERINFO_CHANGED                             = 0x10003003, /**< Event sent when userinfo change.*/

    VOS_MSG_SEND_CT_INFORM_STATUS                           = 0x10003004,

    VOS_MSG_MONITORCOLLECTR_CHANGED                         = 0x10003005, /**< monitor collector config change */
    VOS_MSG_MONITORCOLLECTR_EMULATOR_CHANGED                = 0x10003006, /**< bridge mulator config change */
    VOS_MSG_MONITORCOLLECTR_EMULATOR_COMPLETE               = 0x10003007, /**< bridge mulator complete */
    
    VOS_MSG_UPNP_EVENT                                      = 0x10003009,
    VOS_MSG_UPNP_GETALL                                     = 0x10003010,

    VOS_MSG_UPNP_DEVICE_MONITOR                             = 0x10003012,   /** from TR69 to DLNA, to invoke action with less than 2 parameters */
    VOS_MSG_CT_REGISTER_DEVICE                              = 0x10003013, /*gpon request OLT device register. zhoumingming 20110426*/

    VOS_MSG_CT_USERINFO_RESETTIMES                          = 0x10003014, /* reset tr69 register times */
    VOS_MSG_LOID_REGISTER                                   = 0x10003015, /* Tr69c Loid Register Message; add by lqy 2013.1.14 */

    VOS_MSG_SIP_ALG_EXT_UPDATE                              = 0x10003016,
    VOS_MSG_STATIC_HOST_INFO                                = 0x10003018,
    VOS_MSG_CT_USERINFO_INFORM                              = 0x10003019,

    /* add by YangP on 20111025 for  T3884,add IMS TR069 function */
    /* add by YangP on 20111012 for T3776,add the function of EchoCancellationInUse */
    VOS_MSG_VOICE_EC_INUSE_STATUS                           = 0x10003134,
    /* add end */
    VOS_MSG_VOICE_IMS_UA_PROF                               = 0x10003145,
    /* add end */

    VOS_MSG_DHCPD_OPT125_CHANGE                             = 0x10003147, /**< DHCPD option 125 info change msg */
    VOS_MSG_SEND_CT_ACCOUNT_CHANGE                          = 0x10003148, /*maintain*/
    VOS_MSG_SET_LOG_SAVE_TO_FLASH                           = 0x10003149,
    VOS_MSG_SET_LOG_CLEAR_IN_FLASH                          = 0x1000314A,

    //VOS_MSG_SEND_INFORM_FOR_YUNNAN = 0x10003150,
    VOS_MSG_VOICE_PORT_QOS_DATA                             = 0x10003151,
    VOS_MSG_CT_JS_LOID_CHANGE                               = 0x10003152,
    VOS_MSG_CT_JS_NAME_CHANGE                               = 0x10003153,
    VOS_MSG_CLOSE_SERVER_LISTEN                             = 0x10003154,
    VOS_MSG_MDW_MODE_CHANGED                                = 0x10003155,
    VOS_MSG_MDW_ACTIVE_NOTIFICATION                         = 0x10003156,
    VOS_MSG_MDW_ACTIVE_NOTIFICATION_BAK                     = 0x10000294,
    VOS_MSG_ALL_ACTIVE_NOTIFICATION                         = 0x10003157,
    VOS_MSG_ALL_ACTIVE_NOTIFICATION_BAK                     = 0x10000295,
    VOS_MSG_VOICE_SNTP_ZONE_CHANGE                          = 0x10003158,
    VOS_MSG_CT_CHANGE_PPPOE_STATUS                          = 0x10003159,

    VOS_MSG_MCPD_MCAST_UPDATE                               = 0x10003200,
    VOS_MSG_CT_CHANGE_LOID_PASSWD                           = 0x10003500, /* change loid or password */

    VOS_MSG_CHANGE_EQUIPMENT_ID                             = 0x10003501,
    VOS_MSG_GET_EQUIPMENT_ID                                = 0x10003502,
    VOS_MSG_CHANGE_GPON_PASSWD                              = 0x10003503,
    VOS_MSG_ETH_LINK_STATUS_CHANGED                         = 0x10003504,

    VOS_MSG_ADD_GEM_PORT                                    = 0x10003600,
    VOS_MSG_DEL_GEM_PORT                                    = 0x10003601,
    VOS_MSG_VOICE_SNTP_STATE_CHANGED                        = 0x10003602, /* sntp state changed */
    VOS_MSG_IPTV_CHANGE                                     = 0x10003603,
    VOS_MSG_CT_CARDALARM                                    = 0x10003604,
    VOS_MSG_CT_RESETMDM                                     = 0x10003605,
    VOS_MSG_ADMIN_PASSWD_CHANGED                            = 0x10003606,
    VOS_MSG_SSK_DSLITE_WATCH                                = 0x10003607,
    VOS_MSG_CLI_TR69_SHOW_SOAP                              = 0x10003608,
    VOS_MSG_CLI_ADD_OBJ                                     = 0x10003609,
    VOS_MSG_CLI_DEL_OBJ                                     = 0x1000360A,
    VOS_MSG_CU_APPLY_UPGRADE                                = 0x1000360B,
    VOS_MSG_CLI_GET_VALUE                                   = 0x10003611,
    VOS_MSG_CLI_SET_VALUE                                   = 0x10003612,
    VOS_MSG_CLI_GET_NAME                                    = 0x10003613,
    VOS_MSG_CLI_GET_ATTRIBUTES                              = 0x10003614,
    VOS_MSG_CLI_SET_ATTRIBUTES                              = 0x10003615,
    VOS_MSG_CLI_DO_REBOOT                                   = 0x10003616,
    VOS_MSG_CLI_DO_RESET                                    = 0x10003617,
    VOS_MSG_CLI_SHOW_TR069_STATE                            = 0x10003618,
    VOS_MSG_CLI_SET_TR069_STATE                             = 0x10003619,
    VOS_MSG_CLI_SET_TR069_STATE_RT                          = 0x1000361A,
    VOS_MSG_ADD_ENTITY_INFO                                 = 0x10003620,
    VOS_MSG_DEL_ENTITY_INFO                                 = 0x10003621,
    VOS_MSG_CONFIG_IP_HOST                                  = 0x10003622,
    VOS_MSG_CLI_CLEAR_TR69_SOAP                             = 0x10003623,
    VOS_MSG_CLI_TR69_ENABLE_SOAP                            = 0x10003624,
    VOS_MSG_CONFIG_TR069_ACS                                = 0x10003625,
    VOS_MSG_GET_EID_FROM_NAME                               = 0x10003627,
    VOS_MSG_SET_SERVER_PORT                                 = 0x10003636,
    VOS_MSG_MME_CMM_SET_VAL_ACK                             = 0x10003700,
    VOS_MSG_MME_CMM_GET_NAME_ACK                            = 0x10003701,
    VOS_MSG_MME_GET_LINK_STATUS                             = 0x10003702,
    VOS_MSG_MME_GET_EOC_CHIP_INFO                           = 0x10003703,
    VOS_MSG_MME_SET_EOC_CHIP_INFO                           = 0x10003704,
    VOS_MSG_MME_UPG_UPGRADE_FAILED                          = 0x10003705,
    VOS_MSG_MME_CLI_PRINT_RX_DEBUG                          = 0x10003706,
    VOS_MSG_MME_CLI_PRINT_TX_DEBUG                          = 0x10003707,
    VOS_MSG_MME_CLI_TEST_LINK_STATUS                        = 0x10003708,
    VOS_MSG_MME_CLI_SEND_PACKET                             = 0x10003709,
    VOS_MSG_MME_CLI_PRINT_RX_NO_SPACE_DEBUG                 = 0x1000370A,
    VOS_MSG_UPDATE_IP_HOST                                  = 0x10003711,
    VOS_MSG_APPLY_VOIP                                      = 0x10003712,
    VOS_MSG_MCAST_ACTIVE_GROUP_CHANGED                      = 0x10003713,
    VOS_MSG_PON_LASER_ALWAYS_ON                             = 0x10003714,
    VOS_MSG_RESET_DEFAULT                                   = 0x10003715,
    VOS_MSG_CT_CONFIGD_ETECTION_PARAM                       = 0x10003716,
    VOS_MSG_CTCSTP_PORT_STATE_CHANGED                       = 0x10003717,
    VOS_MSG_CTCSTP_PORT_LOOBACK                             = 0x10003718,
    VOS_MSG_EPONMAC_BOOT_COMPLETE                           = 0x10003719,
    VOS_MSG_EPON_AUTH_STATUS_CHANGE                         = 0x10003720,
    VOS_MSG_TR69C_SET_VALUE                                 = 0x10003721,
    VOS_MSG_TR69C_GET_VALUE_LIST                            = 0x10003722,
    VOS_MSG_TR69C_GET_VALUE                                 = 0x10003723,
    VOS_MSG_CT_ALARM_STATE_CHANGED                          = 0x10003724,
    VOS_MSG_CTCSTP_PORT_STATE_LOOPBACK                      = 0x10003725,
    VOS_MSG_CERT_CHANGE                                     = 0x10003726,
    VOS_MSG_NOTICE_SNTP_WAN_CONN_CHANGE                     = 0x10003727,
    VOS_MSG_CT_MONITOR_STATE_CHANGED                        = 0x10003728,
    VOS_MSG_CLI_SHOW_PPP_INFO                               = 0x10003729,
    VOS_MSG_CLI_SET_PPP_INFO                                = 0x1000372A,
    VOS_MSG_CLI_SHOW_DHCP_POOL                              = 0x1000372B,
    VOS_MSG_CLI_SET_DHCP_POOL                               = 0x1000372C,
    VOS_MSG_CLI_SET_LAN_INFO                                = 0x1000372D,
    VOS_MSG_CLI_SHOW_WLAN_INFO                              = 0x1000372E,
    VOS_MSG_CLI_SET_WLAN_INFO                               = 0x1000372F,
    VOS_MSG_CLI_SHOW_WLAN_ENCRYPTION                        = 0x10003801,
    VOS_MSG_CLI_SET_WLAN_ENCRYPTION                         = 0x10003802,
    VOS_MSG_CLI_SHOW_WLAN_STATUS                            = 0x10003803,
    VOS_MSG_CLI_SET_WLAN_STATUS                             = 0x10003804,
    VOS_MSG_CLI_SHOW_WLAN_MODE                              = 0x10003805,
    VOS_MSG_CLI_SET_WLAN_MODE                               = 0x10003806,
    VOS_MSG_CLI_SHOW_LAN_IP                                 = 0x10003807,
    VOS_MSG_CLI_SET_WLAN_ENCRYPTION_OPEN                    = 0x10003808,
    VOS_MSG_CLI_TO_EPONAPP_OAM                              = 0x10003809,
    VOS_MSG_URLFILTERD_RELOAD                               = 0x10003900,
    VOS_MSG_URLFILTERD_UPDATE_MODE                          = 0x10003901,
    VOS_MSG_URLFILTERD_ADD_ENTRY                            = 0x10003902,
    VOS_MSG_URLFILTERD_DEL_ENTRY                            = 0x10003903,
    VOS_MSG_URLFILTERD_SHOW_CONFIG                          = 0x10003904,
    VOS_MSG_EPON_LINK_STATUS_CHANGE                         = 0x10003905,
    VOS_MSG_SIM_CARD_AUTO_REGISTER                          = 0x10003906,
    VOS_MSG_EPON_AUTO_CHANGE_FLAG                           = 0x10003907,
    VOS_MSG_RMS_OAM_URLSET                                  = 0x10003908,
    VOS_MSG_RMS_OAM_WANSET                                  = 0x10003909,
    VOS_MSG_EPON_UPLOAD                                     = 0x1000390A,
    VOS_MSG_STB_MAC_REPORT_TO_TR69C                         = 0x1000390B,
    VOS_MSG_EMLUATE_COMPLTETE_INFORM                        = 0x10004000, //Infor diagnotics complete message
    VOS_MSG_EMLUATE_ITV_DHCPC_PID                           = 0x10004001,   // itv emulate dhcpc pid
    VOS_MSG_WLAN_TOTAL_ASSOCIATION                          = 0x10004002,
    VOS_MSG_CT_STB_DHCP_OPT60                               = 0x10004003,
    VOS_MSM_SYSTEM_OFFLINE                                  = 0x10004004,
    VOS_MSG_CT_LONGRESET                                    = 0x10004005,
    VOS_MSG_MONITORDIAGNOSTICS_PING_START                   = 0x10004006,
    VOS_MSG_MONITORDIAGNOSTICS_PING_STOP                    = 0x10004007,
    VOS_MSG_MONITORDIAGNOSTICS_PING_CHANGE                  = 0x10004008,
    VOS_MSG_DIAG_PING_STATE_CHANGED                         = 0x10004009,
    VOS_MSG_NET_SNIFFER_CONTROL_EDIT                        = 0x10004100,
    VOS_MSG_NET_SNIFFER_CONTROL_DEL                         = 0x10004101,
    VOS_MSG_NET_SNIFFER_CONTROL_UPDATE                      = 0x10004102,
    VOS_MSG_NET_SNIFFER_CONSOLE                             = 0x10004103,
    VOS_MSG_NET_SNIFFER_FTP_SERVER_CHANGE                   = 0x10004104,
    VOS_MSG_OMCI_CONFIG_WAN_CONNECTION                      = 0x10004105,  /* omci config wan connection */
    VOS_MSG_MME_RESET_EOC                                   = 0x10004106,
    VOS_MSG_REBOOTSYSTEM                                    = 0x10004107,
    VOS_MSG_CONFIG_TR069_WAN                                = 0x10004108,
    VOS_MSG_CT_DOWNLOADDIAG_INFORM                          = 0x10004109,

    VOS_MSG_TR69_UPGRADE_POP                                = 0x10004110,
    VOS_MSG_PROCESS_ABNORMAL_SYSTEM_REBOOT                  = 0x10004111,
    VOS_MSG_CONFIG_SSHD_VLAN                                = 0x10004112,
    VOS_MSG_CONFIG_MULTICAST_VLAN                           = 0x10004113,
    VOS_MSG_DEL_MULTICAST_VLAN                              = 0x10004116,
    VOS_MSG_CONFIG_CTC_VLAN                                 = 0x10004115,

    VOS_MSG_TR069_CONFIG_VOIP_METHOD_USED                   = 0x10004114,

    VOS_MSG_SM_URLFILTERD_ADD_ENTRY                         = 0x10004125,
    VOS_MSG_SM_URLFILTERD_DEL_ENTRY                         = 0x10004126,
    VOS_MSG_SET_URL_STORY_PATH                              = 0x10004127,
    VOS_MSG_MMC_SET_CFG                                     = 0x10004128,
    
    VOS_MSG_SSK_SLOW_FLASH_POWER_LED                        = 0x10004129,

    VOS_MSG_SET_REMOTE_ACCESS                               = 0x10004130,
    VOS_MSG_TR69C_SET_PARAM_WRITABLE                        = 0x10004131,
    VOS_MSG_CMC_URLFILTERD_ADD_ENTRY                        = 0x10004132,
    VOS_MSG_CMC_URLFILTERD_DEL_ENTRY                        = 0x10004133,
    VOS_MSG_MMC_INFORM_WLAN_ACCESS                           = 0x10005000,
    VOS_MSG_MMC_INFORM_LAN_ACCESS                           = 0x10005001,
    VOS_MSG_MMC_ENABLE_INFORM_LAN_ACCESS                    = 0x10005002,
    VOS_MSG_MMC_SET_MSG_CENTER_INFO                         = 0x10005003,
    VOS_MSG_MMC_REQUEST_FROM_HTTPD                          = 0x10005004,
    VOS_MSG_MMC_RESPONSE_HTTPD                              = 0x10005005,
    VOS_MSG_REQUEST_DEVRND_TO_MMC                           = 0x10005007,
    VOS_MSG_MMC_SET_LAN_DEV_RATE_PUSH                       = 0x10005008,
    VOS_MSG_NOTICE_MMC_RESET_MODE                         = 0x10005009,
    VOS_MSG_MGT_URL_CHANGED                              = 0x1000500a,
    VOS_MSG_GET_CLOUD_STATUS                                = 0x1000500b,
    VOS_MSG_HOST_CONNECT_TO_NTWK_BUNDLE                     = 0x10006003,
    VOS_MSG_HOST_CONNECT_TO_ACS_BUNDLE                      = 0x10006004,
    VOS_MSG_SKIP_DIST_PLATFORM_REG                          = 0x10006005,
    VOS_MSG_SKIP_REG_PLATFORM_REG                           = 0x10006006,
    VOS_MSG_TIMERDEAL_TO_SSK_LED_ON                         = 0x10006007,
    VOS_MSG_TIMERDEAL_TO_SSK_LED_OFF                        = 0x10006008,
    VOS_MSG_TIMERDEAL_TO_SSK_WIFI_ON                        = 0x10006009,
    VOS_MSG_TIMERDEAL_TO_SSK_WIFI_OFF                       = 0x10006010,
    VOS_MSG_AVALANCHE_TEST_ENABLE                           = 0x1000600a,
    VOS_MSG_TIMERDEAL_TO_SSK_SSID_ON                        = 0x1000600b,
    VOS_MSG_TIMERDEAL_TO_SSK_SSID_OFF                       = 0x1000600c,
    VOS_MSG_TIMERDEAL_TO_SSK_USB_ON                         = 0x10006011,
    VOS_MSG_TIMERDEAL_TO_SSK_USB_OFF                        = 0x10006012,
    VOS_MSG_TIMERDEAL_TO_SSK_GW_ON                          = 0x10006013,
    VOS_MSG_TIMERDEAL_TO_SSK_GW_OFF                         = 0x10006014,
    VOS_MSG_USB_SERIAL_DEV_CONN                             = 0x10006015,
    VOS_MSG_USB_SERIAL_DEV_DISCONN                          = 0x10006016,
    VOS_MSG_TIMERDEAL_TO_SSK_WELCOME_ON                     = 0x10006017,
    VOS_MSG_TIMERDEAL_TO_SSK_WELCOME_OFF                    = 0x10006018,
    VOS_MSG_TIMERDEAL_TO_SSK_TRFFICTIMER                    = 0x1000601a,
    VOS_MSG_TIMERDEAL_TO_SSK_GUESTSSID_OFF                  = 0x1000601b,
    VOS_MSG_MMC_FOWARD_REQUEST_TO_NAS                       = 0x10007001,
    VOS_MSG_VPN_PPP_PID_TO_SSK                             = 0x10007002,
    VOS_MSG_SEND_MAC_FOR_ARP_DETECT                         = 0x10007003,
    VOS_MSG_DEBUG_OSGID_MSG                                 = 0x10007004,
    VOS_MSG_OSGID_MOUNT_JAMVM                               = 0x10007005,
    VOS_MSG_OSGID_UNMOUNT_JAMVM                             = 0x10007006,
    VOS_MSG_JIS_GET_PLUGIN_LIST                             = 0x10007007,
    VOS_MSG_JIS_ANALYZE_METHOD                              = 0x10007008,
    VOS_MSG_JIS_SMD_PROCESS_MSG                             = 0x10007009,
    VOS_MSG_JIS_OSGID_PROCESS_MSG                           = 0x1000700a,
    VOS_MSG_JIS_PLUGIN_PROCESS_MSG                          = 0x1000700b,
    VOS_MSG_NFC_LOID_REGIST                                 = 0x10009000,
    VOS_MSG_OPKGD_CMD_MSG                                   = 0x10009100,
    VOS_MSG_PLUGIN_JSON_CMD_MSG                             = 0x10009119,
    VOS_MSG_PLUGIN_HOLD                                     = 0x10009121,
    VOS_MSG_PLUGIN_RELEASE                                  = 0x10009122,
    VOS_MSG_PLUGIN_REGISTER                                 = 0x10009123,
    VOS_MSG_PLUGIN_UNREGISTER                               = 0x10009124,
    VOS_MSG_CPMCL_CMD_MSG                                   = 0x10009125,
    VOS_MSG_CPM_DOWNFILE_CMD_MSG                            = 0x10009126,
    VOS_MSG_CPM_INSTALL_CMD_MSG                             = 0X10009127,
    VOS_MSG_CPM_SETPARAM_CMD_MSG                            = 0X10009128,
    VOS_MSG_CPM_PRE_INSTALL_CMD_MSG                         = 0X10009129,
    VOS_MSG_CPM_RECOVER_CMD_MSG                             = 0x1000912a,
    VOS_MSG_SMD_CLEARBAK_CMD_MSG                            = 0x1000912b,
    VOS_MSG_PLUGIN_GET_CFG_DIR                              = 0x10009130, /* Get Plugin Data Cfg Dir Name */
    VOS_MSG_NOTIFY_HTTP_TRAFFIC_PROCESS                     = 0x1000913a,
    
    VOS_MSG_HOST_ONLINE_MSG                                 = 0x10009140,
    VOS_MSG_HOST_OFFLINE_MSG                                = 0x10009141,
    
    VOS_MSG_WLAN_LINK_STATUS_CHANGED                        = 0x10010000,
    VOS_MSG_FLUSH_DNS_CACHE_TO_DPROXY                       = 0x10010001,   
    VOS_MSG_ERR_REDIRECT_TO_DPROXY                          = 0x10010005,
    VOS_MSG_ERR_REDIRECT_TO_REDIRECT                        = 0x10010006,
    VOS_MSG_PLUGIN_PROXY_DEBUG_MODE                         = 0x10010007,
    VOS_MSG_PLUGIN_PROXY_EVENT                              = 0x10010008,
    VOS_MSG_PLUGIN_PROXY_SHOW_INFO                          = 0x10010009,
    VOS_MSG_USB_ACM_DEV_CONN                                = 0x1001000a,
    VOS_MSG_USB_ACM_DEV_DISCONN                             = 0x1001000b,
    VOS_MSG_EVENT_INFORM_TO_MMC                             = 0x1001000d,
    VOS_MSG_FACTORYRESET_APP                                = 0x1001000e,
    VOS_MSG_NOTICE_TIME_CHANGED                             = 0x1001000f,
    VOS_MSG_PLATFORM_STATUS_MSG                             = 0x10010010,
    VOS_MSG_PLUGIN_CONFIG_MSG                               = 0x10010011,
    VOS_MSG_USE_DPI_UPDATE_DEV_INFO                         = 0x10010012,
    VOS_MSG_CPULIMIT_RESET_MSG                              = 0x10010020,
    VOS_MSG_GET_PLATFORM_STATE                              = 0x10011001,
    VOS_MSG_ARP_START                                       = 0x10011003,
    VOS_MSG_TR69C_GET_NAME_LIST                             = 0x10011004,
    VOS_MSG_MODIFY_VOIPTYPE                                 = 0x10011005,
    VOS_MSG_SWITCH_VODSL                                    = 0x10011006,
    VOS_MSG_SWITCH_APP                                      = 0x10011007,
    VOS_MSG_MGT_ABILITY_CHANGED                             = 0x10011008,
    VOS_MSG_TR69C_SEND_BIND1_INFORM                         = 0x10011009,
    VOS_MSG_MMC_GET_SPEC_VERSION                            = 0x1001100A,
    VOS_MSG_TR69C_GET_SPEC_VERSION                          = 0x1001100B,
    VOS_MSG_CT_DNSLIMITALERT                                = 0x1001100C,
    VOS_MSG_SET_BSP_TIMER                                   = 0x1001100d,
    VOS_MSG_MONITORCOLLECTR_UPLOAD                          = 0x1001100e,
    VOS_MSG_CT_SECDDNSLIMITALERT                            = 0x1001100f,
 
    VOS_MSG_NEW_INTERNET_NOTIFY                             = 0x10011101,
    VOS_MSG_VOICE_PORT_SESSION_DATA                         = 0x10011103,
    VOS_MSG_SOFTWARE_UPGRADE_STATUS                         = 0x10011105,
    VOS_MSG_INTERNET_WAN_STATUS_CHANGE                      = 0x10011106,
    VOS_MSG_VOICE_PORT_CODEC_DATA                           = 0x10011107,
    VOS_MSG_RECEIVE_OMCI_CFG                                = 0x10011108,     /* PLOAM assigned, ONT unregisted*/
    VOS_MSG_REMOVE_OMCI_CFG                                 = 0x10011109,     /* PLOAM unassigned, ONT unregisted*/
    VOS_MSG_LASER_SIGNAL_LOS                                = 0x1001110A,      /*GPON PHY LINK DOWN*/
    VOS_MSG_LASER_SIGNAL_ACTIVE                             = 0x1001110B,    /*GPON PHY LINK UP*/
    VOS_MSG_TR69_BUSINESS_STATUS                            = 0x1001110C,
    VOS_MSG_CFG_OMCI_DOWNLOAD                               = 0x1001110D,
    VOS_MSG_CU_RMS_SPEED_TEST                               = 0x1001110F,
    VOS_MSG_CU_RMS_SPEED_TEST_COMPLETED                     = 0x10011110,
    VOS_MSG_CU_FACTORY_RESET_MODE                           = 0x10011111,

    VOS_MSG_DBUS_SET_ENABLE_STATUS                          = 0x20000005,
    VOS_MSG_RANDOM_VPN_INFO_GET                             = 0x20000006,
    VOS_MSG_CANCEL_RANDOM_VPN_TIMER                         = 0x20000007,
    VOS_MSG_UPLOAD_TROUBLE_LOCAT_INFO                       = 0x20000008,
    VOS_MSG_STOP_TIANYI_OPTICAL_LED                         = 0x20000009,
    VOS_MSG_VPN_PPPTUNNEL_CREATE_SUCCESS                    = 0x2000000a,
    VOS_MSG_DBUS_SET_DHCP_CFG                               = 0x2000000b,
    VOS_MSG_TO_SSK_START_ETH_DOWN_ALARM                     = 0x2000000c,
    VOS_MSG_TO_SSK_VOICE_STATUS_CHANGE                      = 0x2000000d,
    VOS_MSG_PPP_ALARM_TO_SSK                                = 0x2000000e,
    VOS_MSG_TO_SSK_UPDATE_PORT_BIND                         = 0x2000000f,
    VOS_MSG_TO_SSK_UPDATE_VLAN_BIND                         = 0x20000010,
    VOS_MSG_CMC_INITIALIZED                                 = 0x20000011,
    VOS_MSG_WAN_MULTI_PROPERTY_CHANGED                      = 0x20000012,
    VOS_MSG_PPP_GET_VPN_RANDOM_USER_INFO                    = 0x20000013,
    VOS_MSG_VPN_DEMANDVPN_TIMEOUT                           = 0x20000014,
    VOS_MSG_STAT_GET_ALL                                    = 0x20000020,
    VOS_MSG_STAT_CLEAR                                      = 0x20000021,
    VOS_MSG_SEND_ALARM_INFO                                 = 0x20000022,
    VOS_MSG_TO_SSK_ADD_OSGID_DEPLOYMENT_INFO                = 0x20000023,
    VOS_MSG_TO_SSK_DEL_OSGID_DEPLOYMENT_INFO                = 0x20000024,
    VOS_MSG_TO_SSK_ADD_OSGID_EXECUTION_INFO                 = 0x20000025,
    VOS_MSG_TO_SSK_DEL_OSGID_EXECUTION_INFO                 = 0x20000026,
    VOS_MSG_TO_SEND_OSGID_REQUESTED_STATE                   = 0x20000027,
    VOS_MSG_TO_SEND_OSGID_AUTO_START                        = 0x20000028,
    VOS_MSG_TO_SEND_OSGID_DU_PERMISSION_API                 = 0x20000029,
    VOS_MSG_CM_WL_DEVICE_ONLINE                             = 0x2000002A,
    VOS_MSG_CM_WL_DEVICE_OFFLINE                            = 0x2000002B,
    VOS_MSG_CM_ETH_DEVICE_ONLINE                            = 0x2000002C,
    VOS_MSG_CM_ETH_DEVICE_OFFLINE                           = 0x2000002D,
    VOS_MSG_URLFILTERD_ADD_MONITOR_DESTADDRESS              = 0x2000002E,
    VOS_MSG_URLFILTERD_DEL_MONITOR_DESTADDRESS              = 0x2000002F,
    VOS_MSG_URLFILTERD_GET_MONITOR_DESTADDRESS              = 0x20000030,
    VOS_MSG_CM_ETH_WLAN_DEVICE_REFUSED                      = 0x20000031,
    VOS_MSG_CM_ETH_LAN_DEVICE_REFUSED                       = 0x20000032,
    VOS_MSG_CM_VOICE_CALL_HISTORY                           = 0x20000033,
    VOS_MSG_CM_LAN_DEVICE_ONLINE_NOTICE_TR69C               = 0x20000034,
    VOS_MSG_PLUGIN_SUBSCRIBE_VOICE                          = 0x20000035,
    VOS_MSG_PLUGIN_UNSUBSCRIBE_VOICE                        = 0x20000036,
    VOS_MSG_WIFIDOG_MAXALLOWCLIENTS_CHANGED                 = 0x20000037,
    VOS_MSG_NSLOOKUP_STATE_CHANGED                          = 0x20000040,
    VOS_MSG_NSLOOKUP_DIAGNOSTICS_COMPLETE                   = 0x20000041,
    VOS_MSG_DNS_DIAG_STATE_CHANGED                          = 0x20000042,
    VOS_MSG_HTTP_DIAG_STATE_CHANGED                         = 0x20000043,
    VOS_MSG_HTTP_DIAG_DIAGNOSTICS_COMPLETE                  = 0x20000044,
    VOS_MSG_QOS_ENABLE_STATE_CHANGED                        = 0x20000045,
    //following four msg is used by EID_BUA
    VOS_MSG_CMC_GET_MODELID                                 = 0x20000046,
    VOS_MSG_CMC_GET_INTERFACE_INFO                          = 0x20000047,
    VOS_MSG_CMC_GET_INTERNET_CONNECTED_WAN_INFO             = 0x20000048,
    VOS_MSG_BUA_GISINFOB_GET                                = 0x20000049,
    VOS_MSG_CMC_MDM_ADD_INSTANCE                            = 0x2000004a,
    VOS_MSG_CMC_MDM_DEL_INSTANCE                            = 0x2000004b,
    VOS_MSG_CMC_REQUEST_OFFLINE_STATUS                      = 0x20000101,
    VOS_MSG_OMCI_RESTORE_DEFAULTS_ACTION                    = 0x20000102,
    VOS_MSG_OMCI_CATV_POWER_SET                             = 0x20000103,  /*catv power set on:1 off:0*/
    VOS_MSG_OMCI_WIFI_ME_COMMON_CFG_SET                     = 0x20000104,
    VOS_MSG_OMCI_WIFI_ME_SSID_CFG_SET                       = 0x20000105,
    VOS_MSG_OMCI_WIFI_ME_COMMON_CFG_CREATE                  = 0x20000106,
    VOS_MSG_OMCI_WIFI_ME_SSID_CFG_CREATE                    = 0x20000107,
    VOS_MSG_OMCI_WIFI_COMMON_STATUS_CHANGE                  = 0x20000108,
    VOS_MSG_OMCI_WIFI_SSID_STATUS_CHANGE                    = 0x20000109,
    VOS_MSG_WEB_RESTORE_CONFIG                              = 0x20000110,
    VOS_MSG_SNMP_DOT1x_AUTH_FAIL                            = 0x20000111,
} VosMsgType;

/* voice Register command words */
typedef struct  {
   int               lineId;
   union{
          int                           cmd;
          int               result;
   };
   unsigned char     data[32];
   unsigned char     len;
   unsigned char     mode;
} VOICE_REG_CMD;


/** This header must be at the beginning of every message.
 *
 * The header may then be followed by additional optional data, depending on
 * the message type.
 * Most of the fields should be self-explainatory.
 *
 */
typedef struct vos_msg_header
{
   VosMsgType  type;  /**< specifies what message this is. */
   VosEntityId src;   /**< VosEntityId of the sender; for apps that can have
                       *   multiple instances, use the MAKE_SPECIFI_EID macro. */
   VosEntityId dst;   /**< VosEntityId of the receiver; for apps that can have
                       *   multiple instances, use the MAKE_SPECIFI_EID macro. */
   union {
      UINT16 all;     /**< All 16 bits of the flags at once. */
      struct {
         UINT16 event:1;    /**< This is a event msg. */
         UINT16 request:1;  /**< This is a request msg. */
         UINT16 response:1; /**< This is a response msg. */
         UINT16 requeue:1;  /**< Tell smd to send this msg back to sender. */
         UINT16 bounceIfNotRunning:1; /**< Do not launch the app to receive this message if
                                       *  it is not already running. */
         UINT16 srpc:1;  /**< This is a srpc msg. */
         UINT16 cache:1;  /**< This is a need cache event msg. */
         UINT16 unused:9;  /**< For future expansion. */
      } bits;
   } flags;  /**< Modifiers to the type of message. */
   UINT16 sequenceNumber;     /**< "Optional", but read the explanation below.
                               *
                               * Senders of request or event message types
                               * are free to set this to whatever
                               * they want, or leave it unitialized.  Senders
                               * are not required to increment the sequence
                               * number with every new message sent.
                               * However, response messages must 
                               * return the same sequence number as the
                               * request message.
                               * 
                               */
   struct vos_msg_header *next;   /**< Allows VosMsgHeaders to be chained. */
   UINT32 wordData;   /**< As an optimization, allow one word of user
                       *   data in msg hdr.
                       *
                       * For messages that have only one word of data,
                       * we can just put the data in this field.
                       * One good use is for response messages that just
                       * need to return a status code.  The message type
                       * determines whether this field is used or not.
                       */
   UINT32 dataLength; /**< Amount of data following the header.  0 if no additional data. */
} VosMsgHeader;

#define flags_event        flags.bits.event      /**< Convenience macro for accessing event bit in msg hdr */
#define flags_request      flags.bits.request    /**< Convenience macro for accessing request bit in msg hdr */
#define flags_response     flags.bits.response   /**< Convenience macro for accessing response bit in msg hdr */
#define flags_requeue      flags.bits.requeue    /**< Convenience macro for accessing requeue bit in msg hdr */
#define flags_bounceIfNotRunning flags.bits.bounceIfNotRunning   /**< Convenience macro for accessing bounceIfNotRunning bit in msg hdr */
#define flags_srpc         flags.bits.srpc   /**< Convenience macro for accessing srpc bit in msg hdr */
#define flags_cache        flags.bits.cache   /**< Convenience macro for accessing cache bit in msg hdr */

#define EMPTY_MSG_HEADER   {VOS_MSG_INVALID, EID_INVALID, EID_INVALID, {0}, 0, NULL, 0, 0} /**< Initialize msg header to empty */


/** Data body for VOS_MSG_REGISTER_DELAYED_MSG.
 */
typedef struct
{
   UINT32  delayMs; /**< Number of milliseconds in the future to deliver this message. */

} RegisterDelayedMsgBody;


/** Data body for VOS_MSG_APP_TERMINATED message type.
 *
 */
typedef struct
{
   VosEntityId eid;      /**< Entity id of the exit process */
   SINT32 sigNum;        /**< signal number */   
   SINT32 exitCode;      /**< process exit code */   
} appTermiatedMsgBody;


/** Data body for CMS_MSG_GET_LEASE_TIME_REMAINING message type.
 *
 * The lease time remaing is returned in the wordData field of the
 * response message.  A -1 means the lease does not expire.
 * A 0 could mean the lease is expired, or that dhcpd has not record
 * of the mac address that was given.
 *
 */
typedef struct
{
   char ifName[CMS_IFNAME_LENGTH]; /**< brx which this host is on */
   char macAddr[MAC_STR_LEN + 1];    /**< mac address of the host */
   char ipAddr[MAC_STR_LEN];
} GetLeaseTimeRemainingMsgBody;


typedef struct
{
    UBOOL8 igmpEnable;
    UBOOL8 snoopingEnable;
    UBOOL8 proxyEnable;
} VOS_IPTV_CHANGE_MSGBODY;

typedef struct
{
    UINT16 portId;

    UINT16 maxSimultaneousGroups;
    UINT32 maxMcastBw;

    UINT8  bwEnforcement;
    UINT8  immediateLeave;
    UINT8  robustness;

    UINT32 usIgmpRate;
    
    UINT32 qerierIpAddr;
    UINT32 queryInterval;
    UINT32 queryMaxRespTime;
    UINT32 lastMemQueryInterval;
    UINT8  igmpVersion;
    UINT8  igmpFunc;
    UINT8  usIgmpTagControl;
    UINT16 usIgmpTci;
} VOS_IGMP_OMCI_CONFIG_MSGBODY;

typedef struct
{
    union
    {
        UINT8 addr[4];
        UINT32 saddr;
    } sin;
}IP_ADDRS;

typedef struct
{
    UINT8   uniPort;
    UINT16  vlanId;
    IP_ADDRS beginAddr;
    IP_ADDRS endAddr;
    UINT16  previewTime;
    UINT32  srcIp;
} VOS_IGMP_OMCI_CONTROL_GROUP_MSGBODY;

typedef struct
{
    UINT16 wanId;
    UINT8 connectionEn;
    UINT8 connectionType;
    UINT8 connectionSvcType;
    UINT8 natEn;
    UINT8 conLinkStatus;
    UINT16 mtu;
    UINT16 inactivityTime;
    UINT32 ipAddr;
    UINT32 mask;
    UINT32 gateway;
    UINT32 priDns;
    UINT32 secDns;
    UINT32 tagConInfo;
    UINT8 autoGetIpAddr;
    UINT8 brgPortBinding;
    char pppoeUsername1[25];
    char pppoeUsername2[25];
    char pppoePwd1[25];
    char pppoePwd2[25];
}VOS_WAN_CONNECTION_INFO_T;

typedef struct
{
    UINT16 wanId;
    char connName1[25];
    char connName2[25];
    UINT8 ipVersion;
    UINT8 ipv6Addr[16];
    UINT8 ipv6Prefix[16];
    UINT8 ipv6Gateway[16];
    UINT8 ipv6PrimDNS[16];
    UINT8 ipv62ndDNS[16];
    UINT8 autoGetIpv6Addr;
    UINT8 dhcpv6PrefixDel;
    UINT8 autoGetDnsAddr;
    char pppoeSerName1[25];
    char pppoeSerName2[25];
    UINT8 lanDHCP;
}VOS_WAN_CONNECTION_INFO_2_T;

typedef struct
{
  VOS_WAN_CONNECTION_INFO_T wanInfoPart1;
  VOS_WAN_CONNECTION_INFO_2_T wanInfoPart2;
}VOS_WAN_CONNECTION_ALL_INFO_T;

typedef struct
{
    UINT8 currStatus;
} VOS_MSG_FILE_TRANS_STATUS_T;

typedef enum
{
    VOS_MSG_FILE_TRANS_SUCCESSD = 0,   
    VOS_MSG_FILE_TRANS_ABORT,           //1
    VOS_MSG_FILE_DELETED,
    VOS_MSG_UNREACHABLE, 
    VOS_MSG_AUTHENTICATION_FAILURE, 
    VOS_MSG_FILE_TRANSFERING, 
    VOS_MSG_REMOTE_FAILURE,       
    VOS_MSG_LOCAL_FAILURE,
    //VOS_MSG_CONFIG_FILE_FAILURE
}VOS_MSG_FILE_TRANS_STATUS_E;

    

typedef struct
{
    UINT16 portId;
    UINT16 filterMode; /*3: join packets; 4: leave packets*/
    UINT16 vlanId;
    UINT32 srcIpAddr;
    UINT32 mcastDestIpAddr;
    UINT32 bestEffActBwEstimate;
    UINT32 clientIpAddr;
    UINT32 joinTime;
    UINT16 reserved;
} VOS_MCAST_ACTIVE_GROUP_TABLE_MSGBODY;

typedef struct
{
    UBOOL8 ipv4Enable;
    UBOOL8 ipv6Enable;
} VOS_TR69_WAN_CHANGE_MSGBODY_T;

typedef struct 
{
   UINT32 hops;
   char hopHost[256];
   char hopHostAddress[32];
   UINT32 hopErrorCode;
   char hopRTTimes[16];
   UINT32 respTime1;
   UINT32 respTime2;
   UINT32 respTime3;
}TraceRouteHops;

typedef struct
{
   char diagnosticsState[32];
   char interface[32];
   char host[32];
   UINT32 numberOfTries;
   UINT32 timeout;
   UINT32 dataBlokSize;
   UINT32 DSCP;
   UINT32 maxHopCount;
   UINT32 responseTime;
   UINT32 routeHopsNumberOfEntries;
   VosEntityId requesterId;
   TraceRouteHops traceRtHops[30];
}VOS_TRACEROUTE_MSGBODY;

typedef struct
{
    char equipmentid[24];
    char gponpasswd[24];
} VOS_EQUIPMENT_CHANGE_ID;

typedef enum
{
    VOS_MSG_SNTP_STATE_DISABLED = 0,       
    VOS_MSG_SNTP_STATE_UNSYNCHRONIZED,      
    VOS_MSG_SNTP_STATE_SYNCHRONIZED,
    VOS_MSG_SNTP_STATE_FAIL_TO_SYNCHRONIZE,
    VOS_MSG_SNTP_STATE_ERROR,
}VOS_MSG_SNTP_STAT_E;


typedef enum
{
    BCM_PPPOE_CLIENT_STATE_PADO    =    0,   /* waiting for PADO */
    BCM_PPPOE_CLIENT_STATE_PADS,   /* got PADO, waiting for PADS */
    BCM_PPPOE_CLIENT_STATE_CONFIRMED,   /* got PADS, session ID confirmed */
    BCM_PPPOE_CLIENT_STATE_DOWN,   /* totally down */
    BCM_PPPOE_CLIENT_STATE_UP,   /* totally up */
    BCM_PPPOE_SERVICE_AVAILABLE,   /* ppp service is available on the remote */
    BCM_PPPOE_AUTH_FAILED,
    BCM_PPPOE_RETRY_AUTH,
    BCM_PPPOE_REPORT_LASTCONNECTERROR,
    BCM_PPPOE_CLIENT_STATE_UNCONFIGURED, 
    BCM_PPPOE_CLIENT_IPV6_STATE_UP,
    BCM_PPPOE_CLIENT_IPV6_STATE_DOWN,
    PPPOE_SESSION_ID,
    BCM_PPPOE_REPORT_PEER_MRU,
}VOS_MSG_PPP_STAT_E;


typedef enum
{
    WAN_LINK_UP   = 0,
    WAN_LINK_INITIALIZING ,        
    WAN_LINK_ESTABLISHINGLINK ,    
    WAN_LINK_NOSIGNAL  ,           
    WAN_LINK_ERROR ,               
    WAN_LINK_DISABLED      
}VOS_WAN_LINK_STATUS;


#define LAN_LINK_UP                   0
#define LAN_LINK_DISABLED             1



#ifdef __cplusplus
extern "C" {
#endif

/** Initialize messaging system.
 *
 * This function should be called early in startup.
 * 
 * @param eid       (IN)  Entity id of the calling process.
 * @param msgHandle (OUT) On successful return, this will point
 *                        to a msg_handle which should be used in subsequent messaging calls.
 *                        The caller is responsible for freeing the msg_handle by calling
 *                        vosMsg_cleanup().
 *
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosMsg_init(VosEntityId eid, void **msgHandle);
VOS_RET_E vosMsg_initEasy(void **msgHandle);
VOS_RET_E vosMsg_initByName(const char *name, void **msgHandle);


/** Clean up messaging system.
 *
 * This function should be called before the application exits.
 * @param msgHandle (IN) This was the msg_handle that was
 *                       created by vosMsg_init().
 */
void vosMsg_cleanup(void **msgHandle);


/** Send a message (blocking).
 *
 * This call is potentially blocking if the communcation channel is
 * clogged up, but in practice, it will not block.  If blocking becomes
 * a real problem, we can create a non-blocking version of this function.
 *
 * @param msgHandle (IN) This was the msgHandle created by
 *                       vosMsg_init().
 * @param buf       (IN) This buf contains a VosMsgHeader and possibly
 *                       more data depending on the message type.
 *                       The caller must fill in all the fields.
 *                       The total length of the message is the length
 *                       of the message header plus any additional data
 *                       as specified in the dataLength field in the VosMsgHeader.
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosMsg_send(void *msgHandle, const VosMsgHeader *buf);


/** Send a reply/response message to the given request message.
 *
 * Same notes about blocking from vosMsg_send() apply.
 * Note that only a message header will be sent by this
 * function.  If the initial request message contains additional
 * data, this function will not send that data back.
 *
 * @param msgHandle (IN) This was the msgHandle created by
 *                       vosMsg_init().
 * @param msg       (IN) The request message that we want to send
 *                       a response to.  This function does not modify
 *                       or free this message.  Caller is still required
 *                       to deal with it appropriately.
 * @param retCode   (IN) The return code to put into the wordData
 *                       field of the return message.
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosMsg_sendReply(void *msgHandle, const VosMsgHeader *msg, VOS_RET_E retCode);


/** Send a message and wait for a simple response.
 *
 * This function starts out by calling vosMsg_send().
 * Then it waits for a response.  The result of the response is expected in
 * the wordData field of the response message.  The value in the wordData is
 * returned to the caller.  The response message must not have any additional
 * data after the header.  The response message is freed by this function.
 *
 * @param msgHandle (IN) This was the msgHandle created by
 *                       vosMsg_init().
 * @param buf       (IN) This buf contains a VosMsgHeader and possibly
 *                       more data depending on the message type.
 *                       The caller must fill in all the fields.
 *                       The total length of the message is the length
 *                       of the message header plus any additional data
 *                       as specified in the dataLength field in the VosMsgHeader.
 *
 * @return VOS_RET_E enum, which is either the response code from the recipient of the msg,
 *                      or a local error.
 */
VOS_RET_E vosMsg_sendAndGetReply(void *msgHandle, const VosMsgHeader *buf);


/** Send a message and wait up to a timeout time for a simple response.
 *
 * This function is the same as vosMsg_sendAndGetReply() except there
 * is a limit, expressed as a timeout, on how long this function will
 * wait for a response.
 *
 * @param msgHandle (IN) This was the msgHandle created by
 *                       vosMsg_init().
 * @param buf       (IN) This buf contains a VosMsgHeader and possibly
 *                       more data depending on the message type.
 *                       The caller must fill in all the fields.
 *                       The total length of the message is the length
 *                       of the message header plus any additional data
 *                       as specified in the dataLength field in the VosMsgHeader.
 * @param timeoutMilliSeconds (IN) Timeout in milliseconds.
 *
 * @return VOS_RET_E enum, which is either the response code from the recipient of the msg,
 *                      or a local error.
 */
VOS_RET_E vosMsg_sendAndGetReplyWithTimeout(void *msgHandle,
                                         const VosMsgHeader *buf,
                                         UINT32 timeoutMilliSeconds);


/** Send a message and wait up to a timeout time for a response that can
 *  have a data section.
 *
 * This function is the same as vosMsg_sendAndGetReply() except this
 * returns a vosMsgHeader and a data section if applicable.
 *
 * @param msgHandle (IN) This was the msgHandle created by
 *                       vosMsg_init().
 * @param buf       (IN) This buf contains a VosMsgHeader and possibly
 *                       more data depending on the message type.
 *                       The caller must fill in all the fields.
 *                       The total length of the message is the length
 *                       of the message header plus any additional data
 *                       as specified in the dataLength field in the VosMsgHeader.
 * @param replyBuf (IN/OUT) On entry, replyBuf is the address of a pointer to
 *                       a buffer that will hold the reply message.
 *                       The caller must allocate enough space in the replyBuf
 *                       to hold the message header and any data that might
 *                       come back in the reply message.  (This is a dangerous
 *                       interface!  This function does not verify that the
 *                       caller has allocated enough space to hold the reply
 *                       message.  Memory corruption will occur if the reply
 *                       message contains more data than the caller has
 *                       allocated.  Note there is also no reason for this
 *                       parameter to be address of pointer, a simple pointer
 *                       to replyBuf would have been sufficient.)
 *                       On successful return, replyBuf will point to a
 *                       VosMsgHeader possibly followed by more data if the
 *                       reply message contains a data section.
 *
 * @return VOS_RET_E enum, which is either the response code from the recipient of the msg,
 *                      or a local error.
 */
VOS_RET_E vosMsg_sendAndGetReplyBuf(void *msgHandle, 
                                 const VosMsgHeader *buf,
                                 VosMsgHeader **replyBuf);


/** Send a message and wait up to a timeout time for a response that can
 *  have a data section.
 *
 * This function is the same as vosMsg_sendAndGetReplyBuf() except there
 * is a limit, expressed as a timeout, on how long this function will
 * wait for a response.
 *
 * @param msgHandle (IN) This was the msgHandle created by
 *                       vosMsg_init().
 * @param buf       (IN) This buf contains a VosMsgHeader and possibly
 *                       more data depending on the message type.
 *                       The caller must fill in all the fields.
 *                       The total length of the message is the length
 *                       of the message header plus any additional data
 *                       as specified in the dataLength field in the VosMsgHeader.
 * @param replyBuf (IN/OUT) On entry, replyBuf is the address of a pointer to
 *                       a buffer that will hold the reply message.
 *                       The caller must allocate enough space in the replyBuf
 *                       to hold the message header and any data that might
 *                       come back in the reply message.  (This is a dangerous
 *                       interface!  This function does not verify that the
 *                       caller has allocated enough space to hold the reply
 *                       message.  Memory corruption will occur if the reply
 *                       message contains more data than the caller has
 *                       allocated.  Note there is also no reason for this
 *                       parameter to be address of pointer, a simple pointer
 *                       to replyBuf would have been sufficient.)
 *                       On successful return, replyBuf will point to a
 *                       VosMsgHeader possibly followed by more data if the
 *                       reply message contains a data section.
 *
 * @param timeoutMilliSeconds (IN) Timeout in milliseconds.
 *
 * @return VOS_RET_E enum, which is either the response code from the recipient of the msg,
 *                      or a local error.
 */
VOS_RET_E vosMsg_sendAndGetReplyBufWithTimeout(void *msgHandle, 
                                            const VosMsgHeader *buf,
                                            VosMsgHeader **replyBuf,
                                            UINT32 timeoutMilliSeconds);


/** Receive a message (blocking).
 *
 * This call will block until a message is received.
 * @param msgHandle (IN) This was the msgHandle created by vosMsg_init().
 * @param buf      (OUT) On successful return, buf will point to a VosMsgHeader
 *                       and possibly followed by more data depending on msg type.
 *                       The caller is responsible for freeing the message by calling
 *                       vosMsg_free().
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosMsg_receive(void *msgHandle, VosMsgHeader **buf);


/** Receive a message with timeout.
 *
 * This call will block until a message is received or until the timeout is reached.
 *
 * @param msgHandle (IN) This was the msgHandle created by vosMsg_init().
 * @param buf      (OUT) On successful return, buf will point to a VosMsgHeader
 *                       and possibly followed by more data depending on msg type.
 *                       The caller is responsible for freeing the message by calling
 *                       vosMsg_free().
 * @param timeoutMilliSeconds (IN) Timeout in milliseconds.  0 means do not block,
 *                       otherwise, block for the specified number of milliseconds.
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosMsg_receiveWithTimeout(void *msgHandle,
                                 VosMsgHeader **buf,
                                 UINT32 timeoutMilliSeconds);


/** Put a received message back into a temporary "put-back" queue.
 *
 * Since the RCL calls vosMsg_receive, it may get an asynchronous event
 * message that is intended for the higher level application.  So it needs
 * to preserve the message in the msgHandle so the higher level application
 * can detect and receive it.  This happens in two steps: first the message
 * is put in a temporary "put-back" queue in the msgHandle (this function),
 * and then all messages in the put-back queue are sent smd with the
 * requeue bit set.  Smd will send the message back to this app again
 * therefore allowing the upper level application to receive it.
 *
 * @param msgHandle (IN) This was the msgHandle created by vosMsg_init().
 * @param buf       (IN) The message to put back.
 */
void vosMsg_putBack(void *msgHandle, VosMsgHeader **buf);


/** Cause all messages in the put-back queue to get requeued in the 
 *  msgHandle's communications link.
 *
 * See the comments in vosMsg_putBack() for a description of how
 * this function works in conjunction with vosMsg_putBack().
 *
 * @param msgHandle (IN) This was the msgHandle created by vosMsg_init().
 */
void vosMsg_requeuePutBacks(void *msgHandle);

void vosMsg_receivePutBack(void *msgHandle, VosMsgHeader **buf);


/** Make a copy of the specified message, including any additional data beyond the header.
 *
 * @param  buf      (IN) The message to copy.
 * @return duplicate of the specified message.
 */
VosMsgHeader *vosMsg_duplicate(const VosMsgHeader *buf);



/** Get operating system dependent handle to detect available message to receive.
 *
 * This allows the application to get the operating system dependent handle
 * to detect a message that is available to be received so it can wait on the handle along
 * with other private event handles that the application manages.
 * In UNIX like operating systems, this will return a file descriptor
 * which the application can then use in select.
 * 
 * @param msgHandle    (IN) This was the msgHandle created by vosMsg_init().
 * @param eventHandle (OUT) This is the OS dependent event handle.  For LINUX,
 *                          eventHandle is the file descriptor number.
 * @return VOS_RET_E enum.
 */
VOS_RET_E vosMsg_getEventHandle(const void *msgHandle, void *eventHandle);


/** Get the eid of the creator of this message handle.
 * 
 * This function is used by the VOS libraries which are given a message handle
 * but needs to find out who the message handle belongs to.
 * 
 * @param msgHandle    (IN) This was the msgHandle created by vosMsg_init().
 * 
 * @return VosEntityId of the creator of the msgHandle.
 */
VosEntityId vosMsg_getHandleEid(const void *msgHandle);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif // __VOS_MSG_H__
