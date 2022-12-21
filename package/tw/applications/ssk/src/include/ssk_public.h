#ifndef __SSK_PUBLIC_H__
#define __SSK_PUBLIC_H__

#ifndef __KERNEL__
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <libubus.h>
#include "fwk/fwk.h"
#include "dai/dai.h"
#include <linux/if.h>
#include <syslog.h>
#include <errno.h>
#endif

#define SSK_UBUS_DHCP_ALLOC_IP_EVENT     "dnsmasq_dhcp_ack"
#define UBUS_EVENT_SYS_PORT_LINKSTATE    "sys_net_port_event"
#define SSK_UBUS_APCLI_LINK_STAT         "apcli_link_stat"
#define SSK_UBUS_UPNP_NAT_RULE_EVENT     "upnp_nat_rule"
#define SSK_UBUS_NTPD_SYNC_EVENT         "ntpd_sync_message"
#define UBUS_EVENT_DEVICE_LINK_CHANGE    "dev_probe_link"
#define UBUS_EVENT_MANAGESSID_UPDATE     "ssid_manage_update"

typedef enum
{
    SYSPORT_UBUS_NAME_EVENT_ATTR_PORT,
    SYSPORT_UBUS_NAME_EVENT_ATTR_STATE,
    SYSPORT_UBUS_NAME_EVENT_ATTR_LINK,
    SYSPORT_UBUS_NAME_EVENT_ATTR_MAXNUM
} SYSPORT_UBUS_NAME_EVENT_ATTR_E;

enum ssk_nl_id
{
    SSK_NL_ID_ETH_LINK,
    SSK_NL_ID_WPS_PEER,
    SSK_NL_ID_WPS_CREDENTIAL_INFO,
    SSK_NL_ID_INCORRECT_SECURITY_SETTING,
    SSK_NL_ID_MAX
};

struct ssk_nl_wifi_incorrect_security_info
{
    unsigned char macAddr[6];
};

struct ssk_nl_eth_link
{
    unsigned char port;
    unsigned char link;
};

struct ssk_nl_wps_peer
{
    unsigned char rfBand;
    unsigned char macAddr[6];
    char deviceName[32];
};

struct ssk_nl_wps_credential
{
    unsigned char rfBand;
    unsigned short authType;
    unsigned short encrType;
    unsigned short ssidLen;
    unsigned char ssid[32];
    unsigned short wpaPskLen;
    unsigned char wpaPsk[64];
};

struct ssk_nl_buf
{
    enum ssk_nl_id id;
    union
    {
        struct ssk_nl_eth_link elink;
        struct ssk_nl_wps_peer wpeer;
        struct ssk_nl_wps_credential wcrdl;
        struct ssk_nl_wifi_incorrect_security_info securityInfo;
    } u;
};

#endif
