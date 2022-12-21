#ifndef __DAI_VLAN__H
#define __DAI_VLAN__H

#include "fwk/fwk.h"

#define DAI_V_IF_MAGIC "WAXWAXWAX"

#define DAI_DEFAULT_CFG_VLAN (10)


typedef struct
{
    uint32_t br_inet_uni;
    uint32_t vlan_inet_uni;
    uint32_t br_inet_wlan;
    uint32_t vlan_inet_wlan;
} VLANCTL_INTERNET_MASK_T;

typedef struct
{
    uint16_t vlanid;
    uint8_t pbit;
    uint8_t enabled;
    uint32_t unimask;
    uint32_t wlanmask;
    char name[BUFLEN_64];
    VLANCTL_INTERNET_MASK_T inet;
} VLANCTL_INFO_T;

int dai_mask2String(uint32_t mask, char *string, uint32_t len);
uint8_t dai_getAllUniMask(void);
int dai_getVlanBridgeName(uint16_t vlanid, char *name, uint8_t len);
int dai_setBridgeVlan(uint16_t vlanid, uint8_t pbit, uint32_t unimask, uint32_t wlanmask);
int dai_enableVlan(const char *type, uint8_t enable);
int dai_getVlanEnable(void);
int dai_getBridgeVlanEnable(void);
int dai_getVlanMode(char *mode, int len);
int dai_getBridgeVlanId(void);
int dai_addVlan(uint16_t vlan, uint8_t pbit, const char *name, uint32_t unimask, uint32_t wlanmask);
int dai_getVlanInfo(const char *type, VLANCTL_INFO_T *info);
int dai_getNextVlanInfo(VLANCTL_INFO_T *info, char *contex, int len);
int dai_setColumnVlanEnable(uint8_t column, uint8_t enable);
uint8_t dai_getVlanCount(void);
int dai_setVlanMode(const char *mode);
uint32_t dai_getUniMask(const char *type, const char *uni);
int dai_getInternetUniMask(VLANCTL_INTERNET_MASK_T *mask);
int dai_deleteColumnVlan(uint8_t column);
int dai_setColumnVlanInfo(uint8_t column, VLANCTL_INFO_T *info);
int dai_setVlanInfo(const char *name, VLANCTL_INFO_T *info);
int dai_vlanFinalApply(void);
int dai_getVlanId(const char *type, uint16_t *vlanid);
int dai_getBridgeVlanId(void);
int dai_GetColumnVlanNum(uint8_t enable);
int dai_vlanFinalApply(void);
int dai_getVlanGlobalEnabled(void);
int dai_updateVlanCfg(void);
int dai_applyPortPbit(void);
int dai_clearRestoreVlan(uint8_t restore);
int dai_getBridgeVlanEnabled(void);
#endif