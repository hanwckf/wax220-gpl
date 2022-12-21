#ifndef __HAL_NETWORK_H__
#define __HAL_NETWORK_H__

#include "fwk/fwk.h"


#define IPV6_ADDR_PATH "/proc/net/if_inet6"
#define DNS_PATH       "/tmp/resolv.conf.auto"


int hal_GetIpV6Addr(char *tmpStr, char *ifName,int *prefixLen, int len);
int hal_GetIpV6Dns(char *dns1, char *dns2, int len);
int hal_GetIpV6Gateway(char *gateway, int len);

#endif

