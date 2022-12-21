#ifndef __UTIL_NET_H__
#define __UTIL_NET_H__


#include "../fwk.h"

#define UTIL_SYSFS_CLASS_NET "/sys/class/net/"


typedef struct   {
	UINT8 mac_addr[6];
	UINT8 port_no;
	UINT8 is_local;
	UINT32 ageing_timer_value;
	UINT8 port_hi;
	UINT8 pad0;
#if defined(CONFIG_BCM_KF_VLAN_AGGREGATION) && defined(CONFIG_BCM_VLAN_AGGREGATION)
	UINT16 vid;
#else
	UINT16 unused;
#endif
}UTIL_FDB_ENTRY_T;


#define UTIL_NTOHS(num, buf)  num = ntohs(*(UINT16*)(buf)); (buf) += 2
#define UTIL_NTOHL(num, buf)  num = ntohl(*(UINT32*)(buf)); (buf) += 4
#define UTIL_HTONS(num, buf)  *(UINT16*)(buf) = htons(num); (buf) += 2
#define UTIL_HTONL(num, buf)  *(UINT32*)(buf) = htonl(num); (buf) += 4


VOS_RET_E UTIL_dnsDoQuery(const char *hostName,
                          const char *ifName,
                          const char *dnsIp,
                          char *hostIp,
                          UINT32 hostIpLen);


VOS_RET_E UTIL_dnsDoIpv6Query(const char *hostName,
                              const char *ifName,
                              const char *dnsIp,
                              char *hostIp,
                              UINT32 hostIpLen,
                              UBOOL8 toIpv6);

VOS_RET_E UTIL_getIfAddr6(const char *ifname, 
                                   UINT32 addrIdx,
                                   char *ipAddr, 
                                   UINT32 *ifIndex,
                                   UINT32 *prefixLen, 
                                   UINT32 *scope, 
                                   UINT32 *ifaFlags);

VOS_RET_E UTIL_getLinkLocalIfAddr6(const char *ifname, 
                                           char *ipAddr,
                                           UINT32 *prefixLen);

VOS_RET_E UTIL_getGloballyUniqueIfAddr6(const char *ifname, 
                                        char *ipAddr, 
                                        UINT32 *prefixLen);

UBOOL8 UTIL_areIpv6AddrEqual(const char *ip6Addr1, const char *ip6Addr2);

UBOOL8 UTIL_isHostInSameSubnet(const char *addrHost, const char *addrPrefix);

UBOOL8 UTIL_getIfMask(const char *devName, char* ip, UINT32 ipLen);

UBOOL8 UTIL_getIfSubnet(const char *devName, char* ipSubnet, UINT32 ipSubnetLen);

UBOOL8 UTIL_isInterfaceExisted(const char *ifName);

VOS_RET_E UTIL_setIfState(const char *ifName, UBOOL8 up);
VOS_RET_E UTIL_checkInterfaceUp(const char *devName, UBOOL8 *up);

UBOOL8 UTIL_getIfAddr(const char *devName, char* ip, UINT32 ipLen);

UBOOL8 UTIL_isAddressOnLanSide(const char *ipAddr);

VOS_RET_E UTIL_subnetLenToSubnetMask(const UINT32 subnetLen, char *subnetMask, UINT32 subnetMaskLen);

VOS_RET_E UTIL_getLanInterFace(const char *inMac, char *ifcName, UINT32 ifcNameLen);

UBOOL8 UTIL_getIfMacAddr(const char *ifname, char *mac);

int UTIL_getMacAddrFromArpByIp(const char *pIPAddr, char *pMacAddr, int iMacLen);

UINT32 UTIL_getIfIp(const char *devName);

UINT32 UTIL_getIfNetMask(const char *devName);

#endif    /* __UTIL_NET_H__ */

