#ifndef __UTIL_DEFS_H__
#define __UTIL_DEFS_H__


/** Invalid file descriptor number */
#define UTIL_INVALID_FD  (-1)


/** Invalid process id.
 *
 * Management entities should not need to use this constant.  It is used
 * by OS dependent code in the OAL layer.  But I put this constant here
 * to make it easier to find.
 */
#define UTIL_INVALID_PID   0


/**
 * This is common used string length types.
 */
#define BUFLEN_1       1     //!< buffer length 1
#define BUFLEN_4        4     //!< buffer length 4
#define BUFLEN_6        6     //!< buffer length 8
#define BUFLEN_8        8     //!< buffer length 8
#define BUFLEN_12       12    //!< buffer length 12
#define BUFLEN_16       16    //!< buffer length 16
#define BUFLEN_18       18    //!< buffer length 18 -- for ppp session id
#define BUFLEN_24       24    //!< buffer length 24 -- mostly for password
#define BUFLEN_32       32    //!< buffer length 32
#define BUFLEN_40       40    //!< buffer length 40
#define BUFLEN_48       48    //!< buffer length 48
#define BUFLEN_64       64    //!< buffer length 64
#define BUFLEN_80       80    //!< buffer length 80
#define BUFLEN_128      128   //!< buffer length 128
#define BUFLEN_256      256   //!< buffer length 256
#define BUFLEN_264      264   //!< buffer length 264
#define BUFLEN_512      512   //!< buffer length 512
#define BUFLEN_1024     1024  //!< buffer length 1024
#define BUFLEN_1518     1518  //!< buffer length 1518
#define BUFLEN_2048     2048  //!< buffer length 2048
#define BUFLEN_4096     4096  //!< buffer length 4096


#define IIDSTACK_BUF_LEN  40  //!< good length to use for mdm_dumpIidStack
#define MAC_ADDR_LEN    6     //!< Mac address len in an array of 6 bytes
#define MAC_STR_LEN     17    //!< Mac String len with ":". eg: xx:xx:xx:xx:xx:xx
#define VPI_MIN         0     //!< VPI min
#define VPI_MAX         255   //!< VPI max
#define VCI_MIN         32    //!< VCI min
#define VCI_MAX         65535 //!< VCI max

#define PPP_CONNECT_ERROR_REASON_LEN 48

#define UTIL_LOG_TMP_FILE_PATH  "/var/config/tmp_log"
#define UTIL_FTP_TMP_FILE_PATH    "/var/log/tmp_ftp"
#define UTIL_MAX_FILE_PATH_LENGTH 128
#define UTIL_IFNAME_LENGTH  32   //!< broadcom interface name length
#define UTIL_MAX_ACS_URL_LENGTH   260   //!< max acs url from dhcp server, specified in TR-181 as max length 256
#define UTIL_MAX_ACS_PROVISIONING_CODE_LENGTH 68  //!< max acs provisioning code, TR-181 max length is 64

#define UTIL_AFTR_NAME_LENGTH   256     //!< max aftr name from dhcpv6 server

/*add for tr69c*/
#define TR69C_INTERNET_PVC_LENGTH   16
#define TR69C_USERNAME_LENGTH   256
#define TR69C_PASSWORD_LENGTH   256
#define TR69C_PERIODIC_INFORM_TIME_LENGTH   16
#define TR69C_PARAMETER_KEY_LENGTH   32
#define TR69C_CARD_NUM_LENGTH   32
#define TR69C_LOG_LEVEL_LENGTH   16
#define TR69C_LOG_DESTINATION_LENGTH   32
#define TR69C_ALARM_PARAM_NAME_LENGTH   512
#define TR69C_PARAM_FULL_PATH_LENGTH    512
#define TR69C_PARAM_VALUE_LENGTH   512
#define TR69C_ORIG_VALUE_LENGTH   256
#define TR69C_PARAM_TYPE_LENGTH   16
#define TR69C_PARAM_SET_ATTR_ARRAY   32
#define TR69C_PARAM_SET_VALUE_ARRAY   32
#define TR69C_PARAM_GET_VALUE_ARRAY   64*20
#define TR69C_PARAM_GET_NAME_ARRAY   256
#define TR69C_PARAM_GET_ATTR_ARRAY   16
#define TR69C_PATH_LENGTH      258
#define TR69C_DOWNLOAD_DIAG_STATE 32
#define TR69C_DOWNLOAD_DIAG_INTERFACE 256
#define TR69C_DOWNLOAD_DIAG_URL 256
#define TR69C_UPLOAD_DIAG_STATE 32
#define TR69C_UPLOAD_DIAG_INTERFACE 256
#define TR69C_UPLOAD_DIAG_URL 256

typedef enum
{
    NONE = 0,
    REQUESTED,
    COMPLETED,
    INIT_CONNECTION_FAILED,
    NORESPONSE,
    TRANSFER_FAILED,
    PASSWORD_REQUEST_FAILED,
    LOGIN_FAILED,
    NO_TRANSFER_MODE,
    NO_PASV,
    INCORRECT_SIZE,
    TIMEOUT_ERROR,
    NO_CWD,
    NO_STOR,
    NO_TRAN_COMP,
} DOWNLOAD_DIAG_STATE;

/* add for snmp */
#define SNMP_STATUS_LENGTH   16
#define SNMP_COMMMUNITY   128
#define SNMP_SYSTEM_NAME_LENGTH   128
#define SNMP_SYSTEM_LOCATION_LENGTH   128
#define SNMP_SYSTEM_CONTACT_LENGTH   256
#define SNMP_IP_ADDR_LENGTH   64
#define SNMP_WAN_CON_SERVICE_NAME   32
#define SNMP_WAN_CON_INF_NAME   32
#define SNMP_PPP_CON_USERNAME    64
#define SNMP_PPP_CON_PASSWORD    64
#define SNMP_PPP_CON_AUTH_PROTOCOL  64
#define SNMP_PPP_CON_TYPE 20

/* add for httpd */
#define UTIL_LOGIN_USERNAME_MAX_LEN 16
#define UTIL_LOGIN_PASSWORD_MAX_LEN 24
#define UTIL_LOGIN_PASSWORD_HASH_MAX_LEN 128
#define UTIL_DDNS_HOST_NAME_MAX_LEN  128
#define UTIL_DDNS_INTERFACE_MAX_LEN  32
#define UTIL_DDNS_USERNAME_MAX_LEN   32
#define UTIL_DDNS_PASSWORD_MAX_LEN   32
#define UTIL_DDNS_PROVIDER_NAME_MAX_LEN 64
#define UTIL_DDNS_SERVICE_PORT_MAX_LEN  8
#define UTIL_DIAG_INTERFACE_MAX_LEN  64
#define UTIL_FIREWALL_SERVICE_MAX_LEN 16
#define UTIL_FIREWALL_PROTOCOL_MAX_LEN 16
#define UTIL_PORT_MAPPING_SRV_NAME_MAX_LEN      32
#define UTIL_PORT_MAPPING_INTERNAL_CLIENT_MAX_LEN  64
#define UTIL_PORT_MAPPING_PROTOCOL_DESCRIPTION_MAX_LEN 256
#define UTIL_PORT_MAPPING_MAX_NUM 32
#define UTIL_UPNP_BLOCK_DEL_LIST_MAX_LEN 128
#define UTIL_SUBMASK_LEN        16
#define UTIL_ROUTE_POLICY_RT_NAME_MAX_LEN  64
#define UTIL_ROUTE_DYNAMIC_RIPVER_MAX_LEN  8
#define UTIL_ROUTE_IPV6_DEV_NAME_MAX_LEN    48

#define UTIL_LOID_ID_MAX_LEN 24
#define UTIL_LOID_PASSWORD_MAX_LEN 24

#define UTIL_IP_FILTER_NAME_MAX_LEN   64
#define UTIL_IP_VERSION_MAX_LEN     8
#define UTIL_PROTOCOL_MAX_LEN       16
#define UTIL_WAN_IFNAME_MAX_LEN     32

#define UTIL_LAN_MAX_NUM            8
#define UTIL_WAN_CONN_MAX_NUM            16
#define UTIL_LAN_SITE_PREFIX_LEN      32
#define UTIL_LAN_IPV6_SITE_PREFIX_CONFIG_TYPE_MAX_LEN   32
#define UTIL_LAN_IPV6_DNS_TYPE 32
#define UTIL_LAN_DHCP6S_DUID_MAX_LEN   256
#define UTIL_LAN_DEV_TYPE_LEN    8
#define UTIL_BRNAME_MAX_LEN    8
#define UTIL_LAN_LINK_STATUS_MAX_LEN 9

#define UTIL_QOS_PLAN_MAX_LEN  16
#define UTIL_QOS_RULE_MODE_MAX_LEN  32
#define UTIL_QOS_APP_NAME_MAX_LEN   8
#define UTIL_QOS_CLASSIFY_TYPE_MAX_LEN  16
#define UTIL_WAN_LINK_NAME_MAX_LEN  40
#define UTIL_QOS_MIN_VALUE_MAX_LEN  256
#define UTIL_QOS_MAX_VALUE_MAX_LEN  256
#define UTIL_QOS_SPDLMT_RULE_MAX_LEN  256

#define UTIL_WAN_PPP_USERNAME_MAX_LEN  256
#define UTIL_WAN_PPP_PASSWORD_MAX_LEN  64
#define UTIL_WAN_PPP_SERVER_NAME_MAX_LEN 40
#define UTIL_WAN_SERVICE_MODE_MAX_LEN  128
#define UTIL_WAN_L2_IFNAME_MAX_LEN  32
#define UTIL_WAN_CONNECTION_TYPE_MAX_LEN 16
#define UTIL_WAN_LAN_INTERFACE_MAX_LEN  512
#define UTIL_WAN_IP_ROUTE_MODE_MAX_LEN  8
#define UTIL_IPV4_ADDR_LEN  16
#define UTIL_IPV6_ADDR_LEN  64
#define UTIL_DOMAIN_LEN   256
#define UTIL_MAC_ADDR_LENGTH   MAC_STR_LEN + 1    //!< Mac String length with ":" and '\0'.
#define UTIL_DEV_TYPE_MAX_LEN 32
#define UTIL_IPV4_ADDR_DNS_SERVER_LEN  32           
#define UTIL_IPV6_ADDR_DNS_SERVER_LEN 256
#define UTIL_WAN_DHCPC_OPTION60_VID_MAX_LEN 256
#define UTIL_WAN_DHCPC_OPTION61_DUID_MAX_LEN 256
#define UTIL_WAN_DHCPC_OPTION61_IAID_MAX_LEN 16
#define UTIL_WAN_CT_LAN_VLAN_LIST_MAX_LEN  256
#define UTIL_WAN_CONN_STATUS_MAX_LEN  16
#define UTIL_WAN_REOUTE_PROTOCOL_RX_MAX_LEN 16

#define UTIL_SNTP_SERVER_MAX_LEN  64
#define UTIL_SNTP_TIME_ZONE_MAX_LEN  8
#define UTIL_SNTP_TIME_ZONE_NAME_MAX_LEN  64
#define UTIL_SNTP_DAY_LIGHT_MAX_LEN  64
#define UTIL_SNTP_CURRENT_TIME_MAX_LEN 64

#define UTIL_VOIP_USER_NUMBER_MAX_LEN 33
#define UTIL_VOIP_USER_AUTH_MAX_LEN 128
#define UTIL_VOIP_USER_AUTH_KEY_MAX_LEN 128
#define UTIL_VOIP_DIAL_PLAN_MAX_LEN   4672
#define UTIL_VOIP_SPECIAL_NUM_MAX_LEN 256
#define UTIL_VOIP_INSIDE_LINE_DIGIT_MAP_MAX_LEN 1024
#define UTIL_VOIP_DECODE_MAX_LEN 8

#define UTIL_VOIP_SECURITY_MAX_LEN 16
#define UTIL_VOIP_PRECONDITION_MAX_LEN 16
#define UTIL_VOIP_EARLY_MEDIA_MAX_LEN 16
#define UTIL_VOIP_TEL_URL_MAX_LEN 32
#define UTIL_VOIP_CONFERENCE_URI_MAX_LEN 256
#define UTIL_VOIP_HOT_LINE_URI_MAX_LEN 256
#define UTIL_VOIP_RING_WAVE_MAX_LEN 16
#define UTIL_VOIP_PROTOCOL_MAX_LEN 9
#define UTIL_VOIP_LINE_PREFIX_MAX_LEN 20
#define UTIL_VOIP_REG_STAT_MAX_LEN 16
#define UTIL_VOIP_TOTAL_TALK_TIME_LEN 9
#define UTIL_VOIP_PACK_CYCLE_LEN 3
#define UTIL_VOIP_AKA_AUTH_OP_MAX_LEN 64
#define UTIL_VOIP_ACCESS_NET_INFO_MAX_LEN 64
#define UTIL_VOIP_DIST_RING_LIST_MAX_LEN 64
#define UTIL_VOIP_FSK_MODE_MAX_LEN 16
#define UTIL_VOIP_DTMF_METHOD_MAX_LEN 16
#define UTIL_VOIP_CALL_ID_MODE_MAX_LEN 16
#define UTIL_VOIP_MODEM_NUM_LIST_MAX_LEN 16
#define UTIL_VOIP_JITTER_BUF_MODE_MAX_LEN 16
#define UTIL_VOIP_CONTROL_TYPE_MAX_LEN 16
#define UTIL_VOIP_LINE_SUM 2
#define UTIL_VOIP_LINE_STATUS_MAX_LEN 16

#define UTIL_VOIP_ENCODE_TYPE_MAX_LEN 8
#define UTIL_VOIP_MG_NAME_MAX_LEN 128
#define UTIL_VOIP_MGC_SERVER_ADDR_MAX_LEN 256
#define UTIL_VOIP_RTP_PREFIX_MAX_LEN 128
#define UTIL_VOIP_PHY_TERM_ID_MAX_LEN 256
#define UTIL_VOIP_PHY_TERM_PREFIX_MAX_LEN  32
#define UTIL_VOIP_REG_STATE  32
#define UTIL_VOIP_MODEM_NUM_MAX_LEN 16
#define UTIL_VOIP_LOCAL_NAME_LEN 4
#define UTIL_VOIP_PHY_PREFIX_MAX_LEN 256
#define UTIL_VOIP_LOCAL_LIST_MAX_LEN 512

#define UTIL_SYS_SRV_NAME_MAX_LEN  8 

#define UTIL_SYS_MANUFACTURER_OUI_LEN  8
#define UTIL_SYS_MANUFACTURER_LEN  64
#define UTIL_SYS_DBUSINTERFACEVERSION_LEN  16
#define UTIL_SYS_PRODUCT_NAME_MAX_LEN 64
#define UTIL_SYS_SN_MAX_LEN  64
#define UTIL_SYS_SSN_MAX_LEN  (UTIL_SYS_SN_MAX_LEN + 7)
#define UTIL_SYS_HW_VERSION_MAX_LEN  64
#define UTIL_SYS_SW_VERSION_MAX_LEN  64
#define UTIL_SYS_ADDITIONAL_HW_VERSION_MAX_LEN 32
#define UTIL_SYS_ADDITIONAL_SW_VERSION_MAX_LEN 32
#define UTIL_SYS_SW_BUILD_TIME_MAX_LEN 32
#define UTIL_SYS_DSL_PHY_DRV_VERSION_MAX_LEN  64
#define UTIL_SYS_VOICE_SERVICE_VERSION_MAX_LEN 64
#define UTIL_SYS_SPEC_VERSION_MAX_LEN  16
#define UTIL_SYS_MODLE_NAME_MAX_LEN   128
#define UTIL_SYS_DESCRIPTION_MAX_LEN  64
#define UTIL_SYS_DEVICE_TYPE_MAX_LEN  16
#define UTIL_SYS_ACCESS_TYPE_MAX_LEN  16

#define UTIL_USB_REMOTE_URL_MAX_LEN    128
#define UTIL_USB_STORAGE_DIR_MAX_LEN    32
#define UTIL_USERNAME_MAX_LEN  32
#define UTIL_PASSWORD_MAX_LEN   32    
#define UTIL_URL_MAX_LEN  512

#define UTIL_VOIP_LOG_LEVEL_LEN 32
#define UTIL_VOIP_LOG_LEVEL_LIST_MAX_LEN 128
#define UTIL_VOIP_LIST_MAX_LEN  128
#define UTIL_VOIP_SIP_AGENT_MAX_LEN 128
#define UTIL_VOIP_SIP_TRANSPORT_LEN 16
#define UTIL_VOIP_SIP_ANONYMOUS_MODE_LEN 32

#define UTIL_CERT_NAME_MAX_LEN 64
#define UTIL_CERT_SUBJECT_LEN  512
#define UTIL_CERT_TYPE_LEN  32
#define UTIL_CERT_PRIVKEY_LEN 1024
#define UTIL_CERT_REQPUB_LEN 1024
#define UTIL_CERT_CONTENT_MAX_LEN  10240
#define UTIL_CERT_PWD_LEN   32
#define UTIL_DMS_MEDIA_PATH_LEN 256
#define UTIL_DMS_BRNAME_LEN 64

#define UTIL_IPADDR_LENGTH  64          //!< IP address length to hold IPv6 in CIDR notation (match INET6_ADDRSTRLEN)
#define UTIL_PING_COUNT_LENGTH 4

#define UTIL_VLAN_LENGTH     8
#define UTIL_TCP_SESSION_LENGTH      8
#define UTIL_MAX_DEFAULT_GATEWAY     8  //!< max default gateways allowed in L3 X_BROADCOM_COM_DefaultConnectionServices
#define UTIL_MAX_DNSIFNAME           8  //!< max dns wan interface names in X_BROADCOM_Networking.DNSIfName
#define UTIL_MAX_ACTIVE_DNS_IP       4  //!< max active dns ip (in resolv.conf) 


#define UTIL_CARD_MAC_LEN 13
#define UTIL_CARD_SN_LNE 21
/* mobile manage */
#define UTIL_MOBILE_URL_LEN 256
#define UTIL_MOBILE_VERSION_LEN 16
#define UTIL_SYS_TELECOM_VENDOR 64
#define UTIL_MOBILE_APPMODEL_LEN 4
#define UTIL_MGT_PLAT_URL_LEN 256
#define UTIL_MGT_PLAT_CONN_LEN 256

/**add  for wireless **/
#define BAND_A                   1
#define BAND_B                   2
#define WL_CHANSPEC_2G           2
#define WL_CHANSPEC_5G           5
#define MCS_TABLE_SIZE           33
#define WL_MID_SIZE_MAX          32
#define WL_LG_SIZE_MAX           1024

#define WL_BAND_NUM_24G              0  //for tianyi 3.0, RFBand 0 is 2.4GHz, 1 is 5GHz 
#define WL_BAND_NUM_5G               1

#define WL_BAND_STR_24G              "2.4G"  //for tianyi 3.0 
#define WL_BAND_STR_5G               "5G"

#define WL_PHY_TYPE_A    "a"
#define WL_PHY_TYPE_B    "b"
#define WL_PHY_TYPE_G    "g"
#define WL_PHY_TYPE_N    "n"
#define WL_PHY_TYPE_LP   "l"
#define WL_PHY_TYPE_AC   "v"

#define WL_LEGACY_MSSID_NUMBER   2
#define WLAN_VIRT_SSID_NUM       4
#define MAX_WLAN_ADAPTER         4

#define WL_MODE_G_AUTO           1
#define WL_MODE_G_PERFORMANCE    4
#define WL_MODE_G_LRS            5
#define WL_MODE_B_ONLY           0

#define WL_IFNAME_SSID1     "wl0"
#define WL_IFNAME_SSID5     "wl1"

#define WLAN_RATE_PRIORITY_BACKUP_FILE  "/var/config/ratePriorityBackup"

#if 0
#pleae use HAL_sysGetWlanSSIDNum   HAL_sysGetWlanPortNum  CMC_wlanGetAllBandFirstIdx
#define WL_FIRST_SSID_INDEX       1
#define WL_FIRST_SSID_INDEX24     1
#define WL_LAST_SSID_INDEX24      4
#define WL_FIRST_SSID_INDEX58     5
#define WL_LAST_SSID_INDEX58      8
#define WL_LAST_SSID_INDEX        8
#endif

#define WL_WPS_MODE_PBC       "0" 
#define WL_WPS_MODE_STA_PIN   "1" 
#define WL_WPS_MODE_AP_PIN    "2" 

#define WL_AP_ISOLATION       "TRUE"
#define WL_AP_NOT_ISOLATION   "FALSE"

/** end  for wireless **/


#define UTIL_WLAN_BEACON_TYPE_MAX_LEN           16
#define UTIL_WLAN_BASIC_ENCRY_MODE_MAX_LEN      16
#define UTIL_WLAN_BASIC_AUTHENT_MODE_MAX_LEN    32
#define UTIL_WLAN_SSID_MAX_LEN                  33
#define UTIL_WLAN_COUNTRY_MAX_LEN               32
#define UTIL_WLAN_RATE_MAX_LEN                  64
#define UTIL_WLAN_PROTECT_MAX_LEN               32
#define UTIL_WLAN_PREAMBLE_TYPE_MAX_LEN         64
#define UTIL_WLAN_MODE_MAX_LEN                  40
#define UTIL_WLAN_ABURN_ENABLE_MAX_LEN          40
#define UTIL_WLAN_FRAME_BURST_MAX_LEN           40
#define UTIL_WLAN_PHY_TYPE_MAX_LEN              2
#define UTIL_WLAN_BASIC_RATE_MAX_LEN            16
#define UTIL_WLAN_MDM_BASIC_RATE_MAX_LEN        64
#define UTIL_WLAN_N_MODE_MAX_LEN                32
#define UTIL_WLAN_BASE_VERSION_MAX_LEN          32
#define UTIL_WLAN_IFNAME_MAX_LEN                32
#define UTIL_WLAN_N_PROTECTION_MAX_LEN          32
#define UTIL_WLAN_AUTH_MODE_MAX_LEN             16
#define UTIL_WLAN_BEACON_TYPE_MAX_LEN           16
#define UTIL_WLAN_WPA_PSK_MAX                   64
#define UTIL_WLAN_WPA_PSK_LEN                   (UTIL_WLAN_WPA_PSK_MAX + 1)    //Note: Reserve 1 byte for '\0'
#define UTIL_WLAN_WEP_MAX_LEN                   16
#define UTIL_WLAN_WPA_MAX_LEN                   16
#define UTIL_WLAN_WSC_CONFIG_MAX_LEN            16
#define UTIL_WLAN_WSC_MODE_MAX_LEN              16
#define UTIL_WLAN_KEY_MAX_LEN                   32
#define UTIL_WLAN_SUM_OF_WLKEY                  4
#define UTIL_WLAN_STA_NAME_MAX_LEN              32
#define UTIL_WLAN_STA_MAX_NUM                   32
#define HAL_WLAN_STA_TABLE_MAX_LEN              128
#define UTIL_WLAN_POINT_TYPE_MAX_LEN            4

#define UTIL_MAX_FULLPATH_LEN                   BUFLEN_1024

#define UTIL_REQUESTED_STATE_LEN                16
#define UTIL_AUTO_STAART_LEN                    16

#define UTIL_WLAN_GUEST_INVALID_TIME            99


#define UTIL_MONITOR_DESTADDRESS_LEN            1024*256

/**
 * L2TP
 */
#define UTIL_L2TP_TUNNEL_NAME_MAX_LEN  64
#define UTIL_L2TP_SERVER_ADDRESS_MAX_LEN 64


/**
 * Values for network protocol
 */
#define PROTO_PPPOE        0  //!< PPPoE protocol
#define PROTO_PPPOA        1  //!< PPPoA protocol
#define PROTO_MER          2  //!< MER protocol
#define PROTO_BRIDGE       3  //!< bridge protocol
#define PROTO_PPPOE_RELA   4  //!< PPPoE relay protocol
#define PROTO_IPOA         5  //!< ip over atm protocol
#define PROTO_IPOWAN       6  //!< ip over wan protocol
#define PROTO_NONE         10 //!< invalid protocol

#define IFC_WAN_MAX        16  //!< Max WAN Connection in the system.
#define IFC_VLAN_MAX       8  //!< Max VLAN on single PVC
#define ATM_QUEUE_MAX      8  //!< Max ATM queues


/*!\enum WanIfcType
 * \brief Enumerated values of WAN interface types.
 */
typedef enum {
   WAN_IFC_ATM=0,       /**< ATM */
   WAN_IFC_PPPOA=1,     /**< PPPoA */
   WAN_IFC_IPOA=2,      /**< IPoA */
   WAN_IFC_ETH=3,       /**< Eth */
   WAN_IFC_PTM=4,       /**< Ptm */
   WAN_IFC_WIFI=5,      /**< Wifi */
   WAN_IFC_ETHLAG=6,    /**< EthLAG */      
   WAN_IFC_NONE=10      /**< undefined/invalid */
} WanIfcType;


#define BRIDGE_PROTO_STR      "Bridge"
#define UTIL_BR_NAME          "br0"
#define UTIL_OTHER_BR_NAME    "br1"
#define IPOA_PROTO_STR        "IPoA"
#define IPOE_PROTO_STR        "IPoE"
#define PPPOE_PROTO_STR       "PPPoE"
#define PPPOA_PROTO_STR       "PPPoA"
#define IPOW_PROTO_STR        "IPoW"

#define ETH_IFC_STR           "eth"
#define USB_IFC_STR           "usb"
#define WLAN_IFC_STR          "wl"
#define MOCA_IFC_STR          "moca"
#ifdef SUPPORT_MTK_PLFM
#define GPON_IFC_STR          "pon"
#define EPON_IFC_STR          "pon"
#else
#define GPON_IFC_STR          "gpon"
#define EPON_IFC_STR          "epon"
#endif
#define ATM_IFC_STR           "atm"
#define PTM_IFC_STR           "ptm"
#define BRIDGE_IFC_STR        "br"
#define IPOA_IFC_STR          "ipoa"
#define IPOE_IFC_STR          "ipoe"
#define PPP_IFC_STR           "ppp"
#define PPPOE_IFC_STR         "pppoe"
#define PPPOA_IFC_STR         "pppoa"
#define IPA_IFC_STR           "ipa"
#define BRIDGE_SMUX_STR       "bridge"
#ifdef SUPPORT_MTK_PLFM
#define VEIP_IFC_STR          "pon"
#else
#define VEIP_IFC_STR          "veip"
#endif


/*iptables user-defined chain name*/
#define UTIL_MCAST_NAT_PRE_CHAIN        "nat_pre_mcast"
#define UTIL_MCAST_IN_CHAIN             "in_mcast"
#define UTIL_MCAST_FWD_CHAIN            "fwd_mcast"
#define UTIL_MCAST_OUT_CHAIN            "out_mcast"
#define UTIL_L2TPCOUNT_FWD_CHAIN     "fwd_l2tpcount"

//voip
#define UTIL_VOIP_NAT_PRE_CHAIN           "nat_pre_voip"
#define UTIL_VOIP_IN_CHAIN                "in_voip"

#define UTIL_ACL_NAT_PRE_CHAIN           "nat_pre_acl"
#define UTIL_ACL_IN_CHAIN                "in_acl"

#define UTIL_DMZ_FWD_CHAIN               "fwd_dmz"
#define UTIL_DMZ_NAT_PRE_CHAIN           "nat_pre_dmz"
#define UTIL_DMZ_NAT_POST_CHAIN          "nat_post_dmz"

#define UTIL_VS_FWD_CHAIN                "fwd_virtual_server"
#define UTIL_VS_NAT_PRE_CHAIN            "nat_pre_virtual_server"
#define UTIL_VS_NAT_POST_CHAIN           "nat_post_virtual_server"

#define UTIL_FIREWALL_FWD_CHAIN          "fwd_firewall"
#define UTIL_FIREWALL_IN_CHAIN           "in_firewall"

#define UTIL_ALG_IN_CHAIN                "in_alg"
#define UTIL_ALG_SIP_IN_CHAIN            "in_alg_sip"
#define UTIL_ALG_FWD_CHAIN               "fwd_alg"
#define UTIL_ALG_SIP_FWD_CHAIN           "fwd_alg_sip"
#define UTIL_ALG_NAT_PRE_CHAIN           "nat_pre_alg"
#define UTIL_ALG_SIP_PRE_CHAIN           "pre_alg_sip"

#define UTIL_INCOMING_FILTER_IN_CHAIN    "in_incoming_filter"

#define UTIL_URL_FILTER_FWD_CHAIN        "fwd_url_filter"

#define UTIL_IP_FILTER_IN_IN_CHAIN       "in_ip_filter_in"
#define UTIL_IP_FILTER_IN_FWD_CHAIN      "fwd_ip_filter_in"
#define UTIL_IP_FILTER_OUT_FWD_CHAIN     "fwd_ip_filter_out"

#define UTIL_WAN_CONN_NAT_PRE_CHAIN      "nat_pre_wan_conn"
#define UTIL_WAN_CONN_NAT_POST_CHAIN     "nat_post_wan_conn"
#define UTIL_WAN_CONN_FWD_CHAIN          "fwd_wan_conn"


#define UTIL_IPMAP_NAT_PRE_CHAIN      "nat_pre_ipmap"
#define UTIL_IPMAP_NAT_POST_CHAIN     "nat_post_ipmap"
#define UTIL_IPMAP_FWD_CHAIN          "fwd_ipmap"


#define UTIL_ANTI_SCAN_IN_CHAIN          "in_anti_scan"
#define UTIL_ANTI_DOC_IN_CHAIN           "in_anti_dos"
#define UTIL_ANTI_DOC_SYN_IN_CHAIN       "in_anti_dos_syn"
#define UTIL_ANTI_SCAN_NAT_PRE_CHAIN     "nat_pre_anti_scan"
#define UTIL_ANTI_DOC_NAT_PRE_CHAIN      "nat_pre_anti_dos"
#define UTIL_ANTI_DOC_SYN_NAT_PRE_CHAIN  "nat_pre_anti_dos_syn"
#define UTIL_ANTI_DOC_FWD_CHAIN          "fwd_anti_dos"

#define UTIL_APP_IN_CHAIN                "in_app"
#define UTIL_APP_FWD_CHAIN               "fwd_app"
#define UTIL_APP_NAT_PRE_CHAIN           "nat_pre_app"

#define UTIL_WEB_FORCE_NAT_PRE_CHAIN     "nat_pre_redirect"
#define UTIL_WEB_FORCE_NAT_DIAG_CHAIN     "nat_pre_diagnose"
#define UTIL_WEB_FORCE_FILTER_CHAIN      "in_redirect"
#define UTIL_WEB_FILTER_CHAIN      "in_web_force_filter"

#define UTIL_VPN_IP_FILTER_CHAIN      "in_vpn_ip_bind"

#define UTIL_HOST_DETECT_NAT_PRE_CHAIN       "nat_pre_host_detect" /* Detect The host packet */
#define UTIL_HOST_DETECT_FWD_CHAIN       "fwd_host_detect" /* Detect The host packet */
#define UTIL_HOST_DETECT_IN_CHAIN       "in_host_detect" /* Detect The host packet */

#define UTIL_HOST_CONN_DETECT_FWD_CHAIN       "fwd_host_conn_detect" /* Host Connection Detect */
#define UTIL_SM_FWD_URL_CTL_CHAIN          "fwd_url_ctl"
#define UTIL_EBT_INPUT_HOST_CONN_CHAIN          "in_host_conn"

#define UTIL_DNS_SPEED_LIMIT_IN_CHAIN "in_dns_speed_limit"
#define UTIL_DNS_SPEED_LIMIT_FWD_CHAIN "fwd_dns_speed_limit"

#define UTIL_IPV6_MATCH_PREFIX_FWD_CHAIN "fwd_v6_match_prefix"

#define UTIL_IP_FORWARD_OUT_CHAIN       "out_ip_forward"

/*FOR OSGI STREAM REDIRECT*/
#define UTIL_MAC_FORWARD_RULE_CHAIN     "in_mac_mark"
#define UTIL_OSGI_NAT_PRE_CHAIN         "nat_pre_osgi_redirect"

/*FOR OSGI TRAFFIC MIRROR*/
#define UTIL_TACMIRROR_NAT_PRE_CHAIN    "fwd_traffic_mirror"
#define CMC_TRAFFIC_MIRROR_FORCE_MASK   0x1000

/*end*/
#define UTIL_RIP_ZEBRA_FWD_CHAIN          "fwd_rip_zebra"
#define UTIL_RIP_ZEBRA_IN_CHAIN           "in_rip_zebra"

#define UTIL_FLOW_FWD_CHAIN               "fwd_flow_conn"

#define UTIL_DHCP_OPT_FWD_CHAIN           "fwd_dhcp_opt"

#define UTIL_DHCP_OPT_FWD_CHAIN           "fwd_dhcp_opt"

#define UTIL_LOCAL_SWITCH_FWD_CHAIN          "fwd_local_swicth_conn"

#define UTIL_DETECT_HOSTTYPE_MASK        0x20000000
#define UTIL_HOST_CONN_DETECT_MASK       0x40000000
#define UTIL_URL_REDIRECT_MARK           0x80000000
#define UTIL_WIFI_DOG_DETECT_MASK        0x100

#define UTIL_VOIP_DEFAULT_USERNAME    "admin"
#define UTIL_VOIP_DEFAULT_PASSWORD    "admin"

#define UTIL_DNS_NUM_SPEEDLIMIT          (16)
#define UTIL_DNS_SPEED_LIMIT_DOMAIN_MAX_LEN  (1024)
#define UTIL_DNS_SPEED_LIMIT_HGW_INFO_MAX_LEN  (64)
#define UTIL_DNS_SPEED_LIMIT_DEVICE_INFO_MAX_LEN  (1024)

#define UTIL_WLAN_STA_TABLE_MAX_LEN              128

/* for interface group with routed pvc */
#define RT_TABLES_BASE	200

typedef enum
{
   ATM=0,          /**< WanDev is used for DSL ATM  */               
   PTM=1,          /**< WanDev is used for DSL PTM  */     
   Ethernet=2      /**< WanDev is used for Ethernet  */
}WanLinkType;


typedef enum
{
   CMC_CONNECTION_MODE_DEFAULT=0,      /**< Default connection mdoe - single wan service over 1 connection */          
   CMC_CONNECTION_MODE_VLANMUX=1,      /**< Vlan mux connection mdoe - multiple vlan service over 1 connection */          
   CMC_CONNECTION_MODE_MSC=2,          /**< MSC connection mdoe - multiple wan service over 1 connection */           
} ConnectionModeType;
   

typedef enum
{
   ATM_EOA=0,        /**< WanDev is used for DSL ATM  */               
   ATM_IPOA=1,       /**< WanDev is used for DSL ATM IPOA */
   ATM_PPPOA=2,      /**< WanDev is used for DSL ATM PPPoA */
   PTM_EOA=3         /**< WanDev is used for DSL PTM  */     
   
}Layer2IfNameType;

/* RAM size defines */
#define SZ_8MB          0x800000
#define SZ_16MB         0x1000000
#define DELETE_ALL      0x80000000


#define MAX_PERSISTENT_WAN_PORT     39       /**< Max Ethernet ports can be configured as WAN ports */

#define DNSINFO_CONF  "/var/dnsinfo.conf"   /**< This file is created by S304 when there is a WAN connection status change and is used
                                               * by dnsproxy and can be used by other applications for the finding the WAN dns info. 
                                               * and has the following fields,  WAN Interface; Subnet/Mask; dns1, dns2..; app1, app2.. :
                                               * eg. atm1;172.0.0.1/32;10.7.2.8,20.1.2.5;tr69c    -- WAN service for TR69
                                               * 1). WAN interface name. eg. ppp0, atm0, etc.
                                               * 2)  subnet/mask in cidr format (bind to this WAN)
                                               * 3) dns list for this WAN 
                                               * 4) process name list uses this WAN
                                               */

/* for Gpon */
typedef enum
{
    OMCI_FLOW_NONE = 0,
    OMCI_FLOW_UPSTREAM,
    OMCI_FLOW_DOWNSTREAM,
    OMCI_FLOW_BOTH,
} OmciFLowDirection;


/* using for print to console */
#define LOGFILE "/dev/console"
#define DBG_MSG_TO_CONSOLE(fmt, arg...) do { FILE *log_fp = fopen(LOGFILE, "w+"); \
   if(log_fp)  \
   { \
   UtilTimestamp ts; \
   utilTms_get(&ts); \
   fprintf(log_fp, "%s():%d:%u.%03u:" fmt "\n",__func__, __LINE__, ts.sec%1000, ts.nsec/NSECS_IN_MSEC, ##arg); \
   fclose(log_fp); \
   } \
  } while(0)


#endif /* __UTIL_DEFS_H__ */
