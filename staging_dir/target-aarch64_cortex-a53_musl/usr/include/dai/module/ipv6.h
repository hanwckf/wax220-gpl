#ifndef __IPV6_H__
#define __IPV6_H__

typedef enum
{
    DAI_WAN_CONN_V6_DISABLED,
    DAI_WAN_CONN_V6_6TO4,
    DAI_WAN_CONN_V6_6RD,
    DAI_WAN_CONN_V6_PASS,
    DAI_WAN_CONN_V6_STATIC,
    DAI_WAN_CONN_V6_DHCP,
    DAI_WAN_CONN_V6_AUTO,
    DAI_WAN_CONN_V6_PPPOE,
    DAI_WAN_CONN_V6_AUTO_DETECT,
} DAI_WAN_CONN_TYPE_V6_E;

typedef enum
{
    DAI_WAN_FW_V6_SECURED,
    DAI_WAN_FW_V6_OPEN,
} DAI_WAN_FW_MODE_V6_E;

typedef enum
{
    DAI_LAN_ADDR_V6_DHCP,
    DAI_LAN_ADDR_V6_AUTO,
} DAI_LAN_ADDR_MODE_V6_E;

typedef struct
{
    char ipAddr[128];
    unsigned int prefixLen;
    char gateway[128];
    char dns1[128];
    char dns2[128];
} DAI_WAN_ADDR_CONF_V6_T;

typedef struct
{
    char prefix[128];
    unsigned int prefixLen;
    char relayAddr[16];
    unsigned int relayMaskLen;
} DAI_WAN_6RD_CONF_T;

typedef struct
{
    int oneSession;
    char username[64];
    char password[64];
    char serviceName[64];
} DAI_WAN_PPPOE_CONF_V6_T;

typedef struct
{
    char ipAddr[128];
    unsigned int prefixLen;
} DAI_LAN_ADDR_CONF_V6_T;

int dai_wanSetConnTypeV6(DAI_WAN_CONN_TYPE_V6_E type);
int dai_wanGetConnTypeV6(DAI_WAN_CONN_TYPE_V6_E *type);

int dai_wanGetConnMode(DAI_WAN_CONN_TYPE_V6_E *type);

int dai_wanSetAddrConfV6(const DAI_WAN_ADDR_CONF_V6_T *addrConf);
int dai_wanGetAddrConfV6(DAI_WAN_ADDR_CONF_V6_T *addrConf);

int dai_wanGetGatewayV6(char *gateway, int len);

int dai_wanSetDnsV6(DAI_WAN_CONN_TYPE_V6_E mode, int autoMode, const char *dns1, const char *dns2);
int dai_wanGetDnsV6(DAI_WAN_CONN_TYPE_V6_E mode, int *autoMode, char *dns1, char *dns2);

int dai_wanSetDhcpUserClassV6(const char *userClass);
int dai_wanGetDhcpUserClassV6(char *userClass, unsigned int userClassLen);

int dai_wanSetDhcpDomainNameV6(const char *domainName);
int dai_wanGetDhcpDomainNameV6(char *domainName, unsigned int domainNameLen);

int dai_wanSet6to4RelayAddr(int autoMode, const char *addr);
int dai_wanGet6to4RelayAddr(int *autoMode, char *addr);

int dai_wanSet6rdConf(const DAI_WAN_6RD_CONF_T *conf);
int dai_wanGet6rdConf(DAI_WAN_6RD_CONF_T *conf);

int dai_wanSetPppoeConfV6(const DAI_WAN_PPPOE_CONF_V6_T *conf);
int dai_wanGetPppoeConfV6(DAI_WAN_PPPOE_CONF_V6_T *conf);

int dai_wanSetFwModeV6(DAI_WAN_FW_MODE_V6_E mode);
int dai_wanGetFwModeV6(DAI_WAN_FW_MODE_V6_E *mode);

int dai_wanGetIpV6Addr(char *tmpStr, int *prefixLen, int len);
int dai_wanGetLeaseV6(unsigned int *leaseTime, unsigned int *upTime);

int dai_lanGetIpV6Addr(char *tmpStr, int *prefixLen, int len);

int dai_lanSetAddrModeV6(DAI_LAN_ADDR_MODE_V6_E mode);
int dai_lanGetAddrModeV6(DAI_LAN_ADDR_MODE_V6_E *mode);

int dai_lanSetAddrConfV6(const DAI_LAN_ADDR_CONF_V6_T *addrConf);
int dai_lanGetAddrConfV6(DAI_LAN_ADDR_CONF_V6_T *addrConf);

int dai_lanSetIfIdV6(int autoMode, const char *ifId);
int dai_lanGetIfIdV6(int *autoMode, char *ifId, unsigned int ifIdLen);

int dai_applyV6(void);

#endif  /* __IPV6_H__ */
