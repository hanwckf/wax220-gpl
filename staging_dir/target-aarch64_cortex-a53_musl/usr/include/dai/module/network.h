#ifndef __NETWORK_H__
#define __NETWORK_H__
#include "fwk/fwk.h"

#define LUCIBWC "luci-bwc -i %s"
#define DELAYTIME  6

#define DEF_WAN_VLAN (4095)
#define DEF_LAN_VLAN (0)

#define INTERNATE_STATUS_UP    0
#define INTERNATE_STATUS_DOWN  1

#define WANUPTIMEFILE          "/tmp/wanlinkuptime"
#define WANDOWNTIMEFILE        "/tmp/wanlinkdowntime"

#define TRACEROUTE_RESULT_FILE "/tmp/diag_traceroute"
#define PING_RESULT_FILE "/tmp/diag_ping"
#define IPERF_RESULT_FILE "/tmp/diag_iperf"
#define NSLOOKUP_RESULT_FILE "/tmp/diag_nslookup"



typedef struct {
    char wanType[BUFLEN_16]; /* dhcp|static|pppoe|l2tp|pptp */
    unsigned char netType;
    unsigned char netpppType;
    unsigned char orangeiptv;
    unsigned char orangeusername[BUFLEN_64];
    char run_test[BUFLEN_8]; /* no|test */
    char domainName[BUFLEN_64];
    unsigned char ipv4enable;
    unsigned char wanAssign;
    char ipaddr[BUFLEN_32];
    char subnet[BUFLEN_32];
    char gateway[BUFLEN_32];
    unsigned char dnsAssign;
    char dnsaddr1[BUFLEN_32];
    char dnsaddr2[BUFLEN_32];
    char dnsaddr3[BUFLEN_32];
    char option_60[BUFLEN_64 + 1];
    char option_61[BUFLEN_64 + 1];
    unsigned char macClone;
    char macCloneAddr[BUFLEN_32];
    unsigned char dsLite;
    char dsLiteAddr[BUFLEN_128];
    unsigned char ndproxy;
    unsigned int mtu;
    unsigned int vlan;
    unsigned char priority;
    /* ppp | l2tp | pptp */
    char p_username[BUFLEN_64 + 1];
    char p_passwd[BUFLEN_64 + 1];
    char p_servername[BUFLEN_64];
    unsigned char p_dod;
    unsigned int pidle_time;
    char p_serv_ip[BUFLEN_64];
    char pptp_conn_id[BUFLEN_64];
}WanInternetConfig_T;

typedef struct {
    char dmzIp[BUFLEN_64];
    uint8_t enableDosAttack;
    uint8_t allowPing;
    uint8_t enableIgmpProxy;
    uint16_t mtu;
    char natFilter[BUFLEN_64];
    uint8_t enableSigAlg;
    uint8_t bt_igmp_value; // Todo
} WanSetupConfig_T;

typedef enum
{
    HAL_ETH_NEG_MODE_AUTO,
    HAL_ETH_NEG_MODE_10M_HALF,
    HAL_ETH_NEG_MODE_10M_FULL,
    HAL_ETH_NEG_MODE_100M_HALF,
    HAL_ETH_NEG_MODE_100M_FULL,
    HAL_ETH_NEG_MODE_1000M,
    HAL_ETH_NEG_MODE_10G
} HAL_ETH_NEG_MODE_E;

typedef struct
{
    UINT64 rxByte;
    UINT64 rxPacket;
    UINT64 rxError;
    UINT64 rxDrop;
    UINT64 rxUcast;
    UINT64 rxBcast;
    UINT64 rxMcast;
    UINT64 rxDiscard;
    UINT64 rxUnknowPro;
    UINT64 txByte;
    UINT64 txPacket;
    UINT64 txDrop;
    UINT64 txError;
    UINT64 txUcast;
    UINT64 txColls;
    UINT64 txMcast;
    UINT64 txDiscard;
} DAI_ETH_STATISTICS_T;


typedef enum
{
    DET_WAN_STATUS_NO_WAN,
    DET_WAN_STATUS_NOT_READY  = 9999,
    DET_WAN_STATUS_CHECK_PING = 10001,
    DET_WAN_STATUS_PPPOE      = 10002,
    DET_WAN_STATUS_PPTP       = 10007,
    DET_WAN_STATUS_L2TP       = 10010,
    DET_WAN_STATUS_IP_PROBLEM = 10003,
} DETECT_WAN_STATUS_E;

typedef enum
{
    WAN_PPP_TYPE_PPPOE,
    WAN_PPP_TYPE_PPTP,
    WAN_PPP_TYPE_L2TP              = 4,
    WAN_PPP_TYPE_ORANGE_PPPOE      = 6,
    WAN_PPP_TYPE_ORANGE_DHCP,
    WAN_PPP_TYPE_MOVI_SPAIN_PPPOE,
    WAN_PPP_TYPE_VODA_SPAIN_PPPOE,
    WAN_PPP_TYPE_SINGTEL_DHCP,
    WAN_PPP_TYPE_UNIFI_DHCP,
    WAN_PPP_TYPE_MAXIS_DHCP,
    WAN_PPP_TYPE_UNIFI_PPPOE,
    WAN_PPP_TYPE_MAXIS_PPPOE,
} WAN_PPP_TYPE_E;

#define MAX_ROUTE_RULE_NUM    32
typedef struct
{
    char dstAddr[BUFLEN_32];
    char netMask[BUFLEN_32];
    char gateWay[BUFLEN_32];
    char routeName[BUFLEN_32];
    char ifname[BUFLEN_32];
    UINT8 private;
    UINT8 active;
    UINT8 metric;
} STATIC_ROUTE_CFG_T;

/**
 * DAI API for get WAN Internete connect status 
 * @param status 
*/
void dai_getInternetConnectStatus(int *status);

/**
 * DAI API for get IPV4 WAN Internete config 
 * @param wanconfig 
*/
int dai_getWanInernet_config(WanInternetConfig_T *wanconfig);

/**
 * DAI API for set IPV4 WAN Internete config 
 * @param wanconfig 
*/
int dai_setWanInernet_config(WanInternetConfig_T *wanconfig);

int dai_getNetMode(char *mode, int len);
int dai_setNetMode(char *mode);
int dai_getDetWanStatus(int *status);
int dai_setDetWan();
int dai_getDetWanValid(int *status);


int dai_wanGetcfgProto(char *proto, int len);

int dai_wanGetcfgWanInternetType(unsigned char *type);

int dai_wanGetcfgWanInternetPppType(unsigned char *type);

int dai_wanGetcfgWanIpAssign(unsigned char *enable);

int dai_wanGetcfgWanIpAddress(unsigned char *ipaddr, int len);

int dai_wanGetcfgWanSubmask(unsigned char *submask, int len);

int dai_wanGetcfgWanGateway(unsigned char *gateway, int len);

int dai_wanGetcfgDnsAssign(unsigned char *enable);

int dai_wanGetcfgDnsAddr(int index, unsigned char *dnsAddr, int len);

int dai_wanGetcfgMaccloneEnable(unsigned char *enable);
int dai_uciBackup(const char *config, const char *section);
int dai_uciRestore(const char *config);

int dai_getNetDevName(uint8_t port, char *name, uint32_t len);

int dai_SetL2Mode(WanInternetConfig_T *cfg);

int dai_GetApModeGateway(char *gateway, int len);

int dai_SetDefRouterMode(void);
int dai_wanGetcfgMaccloneAddr(unsigned char *macAddr, int len);

int dai_wanGetcfgPppUsername(unsigned char *username, int len);

int dai_wanGetcfgPppPassword(unsigned char *password, int len);

int dai_wanGetcfgPppServerName(unsigned char *serverName, int len);

int dai_wanGetcfgPppDodType(unsigned char *dodType);

int dai_wanGetcfgPppDodTime(int *dodTime);

int dai_wanGetcfgPptpL2tpUsername(unsigned char *username, int len);

int dai_wanGetcfgPptpL2tpPassword(unsigned char *password, int len);

int dai_wanGetcfgPptpL2tpServerIp(unsigned char *serverIp, int len);

int dai_wanGetcfgPptpL2tpDodType(unsigned char *dodType);

int dai_wanGetcfgPptpL2tpDodTime(int *dodTime);

int dai_wanGetcfgPptpConnectID(unsigned char *connectID, int len);

int dai_wanGetcfgDhcpOption60(unsigned char *value, int len);

int dai_wanGetcfgDhcpOption61(unsigned char *value, int len);

int dai_wanGetcfgMtu(int *mtu);

int dai_wanSetcfgMtu(int mtu, int net_reset);

int dai_wanGetcfgdomainName(char *domain, int len);

VOS_RET_E dai_ethGetPortLinkMode(const char *ifName, HAL_ETH_NEG_MODE_E *mode);

VOS_RET_E dai_ethGetPortStats(const char *devName, DAI_ETH_STATISTICS_T *statistics);

int dai_ethGetStatsPortTraffic(const char *devName, uint64_t *rxByte, uint64_t *txByte);

int dai_wanGetUbusWanStatus(char *status, int len);

int dai_wanGetUbusVpnStatus(char *status, int len);

int dai_wanGetstatusWanIpAddress(char *ipaddr, int len);

int dai_wanGetstatusWanSubmask(char *submask, int len);

int dai_wanGetstatusWanGateway(char *gateway, int len);

int dai_wanGetPptpL2tpDhcpWanInfo(char *wanInfo, int len, char *attr);

int dai_wanGetstatusWanDns(int index, char *dns, int len);

int dai_wanGetstatusWanLeasetime(unsigned int *leasetime);

int dai_wanGetstatusWanUptime(unsigned int *uptime);

int dai_wanGetstatusWanPppUptime(unsigned int *uptime);

int dai_wanGetstatusDhcpServerAddress(char *ipaddr, int len);

int dai_getWdsIpProto(char *proto, int len);

int dai_setIgmpProxy(uint8_t enable);

int dai_getIgmpProxy(uint8_t *enable);

int dai_setSipAlgEnable(uint8_t enable);

int dai_getSipAlgEnable(uint8_t *enable);

int dai_setBtIgmpEnable(uint8_t enable);

int dai_getBtIgmpEnable(uint8_t *enable);

int dai_addStaticRouteCfg(STATIC_ROUTE_CFG_T *pStaticRouteCfg);

int dai_editStaticRouteCfg(STATIC_ROUTE_CFG_T *pStaticRouteCfg, int editNum);

int dai_delStaticRouteCfg(int delIdx);

int dai_getStaticRouteCfg(STATIC_ROUTE_CFG_T *pStRouteCfg, UINT8 idx);

int dai_GetWanLinkUpTime(int *time);
int dai_GetWanLinkDownTime(int *time);

int dai_reloadAclMulticastVlan(void);

int dai_doDiagPing(const char *addr, const char *pks, const char *pings);

int dai_doDiagTraceroute(const char *addr, const char *tracerouteType);

int dai_doDiagNslookup(const char *addr);

int dai_doDiagIperf(const char *addr, const char *timePeriod, const char *checkInterval, const char *port);

#endif
