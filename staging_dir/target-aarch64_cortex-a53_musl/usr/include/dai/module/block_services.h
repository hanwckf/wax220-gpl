#ifndef __BLOCK_SERVICES_H__
#define __BLOCK_SERVICES_H__

#define ADD_IPTABLES_RULE     "ADD_IPTABLES_RULE"
#define EDIT_IPTABLES_RULE    "EDIT_IPTABLES_RULE"
#define DEL_IPTABLES_RULE     "DEL_IPTABLES_RULE"

typedef struct
{
    char userdefined[BUFLEN_32];
    char service_type[BUFLEN_32];
    char protocol[BUFLEN_32];
    char portstart[BUFLEN_32];
    char portend[BUFLEN_32];
    char iptype[BUFLEN_32];
    char iprange_start[BUFLEN_32];
    char iprange_end[BUFLEN_32];
    char only_ip[BUFLEN_32];
    char iplist[BUFLEN_64];
} BLOCK_SERVICES_T;

int dai_addBlockServiceRule(BLOCK_SERVICES_T *pBlockService);
int dai_getBlockServiceRule(BLOCK_SERVICES_T *pBlockService, int keynumber);
int dai_editBlockServiceRule(BLOCK_SERVICES_T *pBlockService, int num);
int dai_delBlockServiceRule(int devnum);
int dai_setBlockingOption(char *option);
int dai_getBlockingOption(char *option, int len);
void dai_updateBlockServicesIpAddr();
#endif
