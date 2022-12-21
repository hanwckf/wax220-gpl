#ifndef __UPNP_H__
#define __UPNP_H__
#include "fwk/fwk.h"

#define UPNPMAXLEASESNUM     128

typedef struct{
    int enable_upnp;      // 1 开启upnp 0 关闭upnp
    int notify_interval;   //Advertisement Period
    int time_to_live;       //TODO
} UPNP_CONFIG_T;


typedef struct{
    char proto[BUFLEN_32];
    int  eport;
    char ip[BUFLEN_32];
    int  iport;
    int  timestamp;
    char desc[BUFLEN_32];
    char onlineStatus[BUFLEN_32];
} UPNP_LEASES_T;


int dai_getUpnpConfigParms(UPNP_CONFIG_T *upnp_cfg);
int dai_SetUpnpConfigParms(UPNP_CONFIG_T *upnp_cfg);
int dai_getUpnpLeasesinfo(UPNP_LEASES_T *upnpLeases_info,int *count);
#endif
