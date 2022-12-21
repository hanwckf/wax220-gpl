#ifndef __LAN_H__
#define __LAN_H__
#include "fwk/fwk.h"


#define ATTACH_DEV_MAX     256
#define BR_DEV              "br-lan"
#define BR_ETH_DEV          "eth"
#define BR_2G_DEV           "ra0"
#define BR_2G_GUEST_DEV     "ra1"
#define BR_5G_DEV           "rax0"
#define BR_5G_GUEST_DEV     "rax1"
#define BR_EXD_DEV          "extender"
#define BR_EXD_WAN_PRE      "apcli"

typedef enum
{
    CONN_TYPE_WIRED,
    CONN_TYPE_WIFI
} CONN_TYPE_E;


typedef struct
{
    char status[BUFLEN_32];         // 连接状态, 取值范围 'Online' / 'Offline'
    char connType[BUFLEN_32];       // 连接类型, 取值范围 'wired' / '2.4G' / '5G' / '5G-2'
    char deviceName[BUFLEN_64];     // 设备名称 比如 'Jack-iPhone' // 1. 如果用户设置了设备名，就用用户设置的2. 如果用户没有指定名称，就用系统自动获取到的3. 如果用户没有指定，且系统没有自动获取到，为 'unknown'
    char ip[BUFLEN_32];             // IP地址 '192.168.1.100'
    char mac[BUFLEN_32];            // MAC地址 '00:11:22:33:AA:BB'
    char ifname[BUFLEN_32];               //当前连接的接口eth 、ra0等
    char deviceType[BUFLEN_32];     // 设备类型      PC/Mobile/STB
    int deviceTypeNum;
    char deviceModel[BUFLEN_64];    
    //以下暂未用到
    UINT32 rate;                    // 连接速率 单位 Mbps
    char rssi[BUFLEN_32];           // 无线设备RSSI, 比如: -46
    int attachType;
    int priority;
    unsigned long connection_time;
} LAN_DEVICE_INFO;

typedef struct
{
   char mac[BUFLEN_32] ;
   char deviceType[BUFLEN_64];
   char deviceModel[BUFLEN_64];
   char deviceName[BUFLEN_64];
   char remoteIp[BUFLEN_32];
   char localIp[BUFLEN_32];
   unsigned long connTime;
}VPN_DEVICE_INFO;


typedef struct{
    char lanIpAddr[BUFLEN_64];
    char lanSubnet[BUFLEN_64];
    char lanGateway[BUFLEN_64];
    char lanIfName[BUFLEN_128];
    int  guestNetwork[BUFLEN_4];
    union
    {
        char dnsaddr[3][BUFLEN_32];
        struct
        {
            char dnsaddr1[BUFLEN_32];
            char dnsaddr2[BUFLEN_32];
            char dnsaddr3[BUFLEN_32];
        } dns_s;
    } dns_u;
    char proto[BUFLEN_16]; //network.lan.proto,br-lan的地址是dhcp还是static
    char dhcplanIpstart[BUFLEN_64];
    char dhcplanIpend[BUFLEN_64];
    char dhcplanOP[BUFLEN_64];
    unsigned int lanDhcpleasetime;
    char landhcpproto[BUFLEN_16];//指下挂设备获取地址是dhcp还是static
    char rip_direction[BUFLEN_16];
    char rip_version[BUFLEN_16];
} NETLAN_CONFIG_T;


typedef struct{
    char reservation_ipaddr[BUFLEN_32];
    char rsv_mac[BUFLEN_32];
    char dev_name[BUFLEN_32];
} LANDHCP_STATICLEASES_T;


typedef struct{
    char mac[BUFLEN_32];
    char dev_type[BUFLEN_32];
    char dev_priority[BUFLEN_32];
    char dev_name[BUFLEN_128];
    char dev_model[BUFLEN_128];
} LAN_EDIT_ATTACH_DEV__T;

/**
 * DAI API for set IPV4 LAN  ip config 
 * @param dhcp 
*/
int dai_getLanIpPara_config(NETLAN_CONFIG_T *lanIpPara);
int dai_getUciLanIpPara_config(NETLAN_CONFIG_T *lanIpPara);
int dai_getGuestIpPara_config(NETLAN_CONFIG_T *lanIpPara);
int dai_getMgmtIpPara_config(NETLAN_CONFIG_T *lanIpPara);
int dai_setLanIpPara_config(NETLAN_CONFIG_T *lanIpPara);
int dai_setGuestIpPara_config(NETLAN_CONFIG_T *lanIpPara);
int dai_refreshLanDev();
uint8_t dai_isIfStatic(const char *if_name);
int dai_getApStatusDnsAdress(int index, char *dns, int dnsLen);
int dai_getApstatusGateway(char *gateway, int len);
int dai_getApstatusIpAddress(char *ipaddr, int len);
int dai_getApstatusSubmask(char *submask, int len);

/**
 * DAI API for set IPV4 LAN  Static leases config 
 * @param dhcp 
*/
int dai_getLanDhcpStaticleases(LANDHCP_STATICLEASES_T *lanStaticLeasespara, int devnum);
int dai_addLanDhcpStaticleases(LANDHCP_STATICLEASES_T *lanStaticLeasespara);
int dai_editLanDhcpStaticleases(LANDHCP_STATICLEASES_T *lanStaticLeasespara, int devnum);
int dai_delLanDhcpStaticleases(int devnum);

int dai_getLanDeviceInfo(LAN_DEVICE_INFO *dev_info, int* count);
int dai_getVPNDeviceInfo(VPN_DEVICE_INFO *vpn_info, int* count);
void dai_getInternetConnectStatus(int *status);
int dai_getSupportQos(void);
void dai_getLinkSpeed(int *up,int *down);
int dai_procIsExist(char *procName);
int dai_udhcpcPID();
int dai_getLanIfName(char * name, int len);
int dai_getEthPortIdByMac(char *ifName, uint8_t *mac, uint32_t *port);
int dai_del_section_byoption(const char* pConfigPath, const char* pSectionType, const char* pOptionName, const char* pOptionValue);
int dai_getEthPortLinkStatus(uint8_t port);
VOS_RET_E dai_getLanIpInfo(char *lanIp, UINT32 lanIpLen, char *lanIpMask, UINT32 lanIpMaskLen);
int dai_getWlanIfName(UINT32 band, char *ifName, int ifNameLen, int wlanIdx);
int dai_getDevTraffic(const char *mac, const char *ifName,
                                            long long unsigned int *rxFlow, long long unsigned int *txFlow,
                                            long long unsigned int *rxFlowPkts, long long unsigned int *txFlowPkts);
int dai_getWifiClientNum(UINT32 *num2g, UINT32 *num5g);
#endif
