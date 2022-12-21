#ifndef __HAL_WIFI_H__
#define __HAL_WIFI_H__

#include "fwk/fwk.h"
#include <linux/wireless.h> 
#include "../include/module/wifi.h"

#define SIOCIWFIRSTPRIV 0x8BE0
#define RT_PRIV_IOCTL               (SIOCIWFIRSTPRIV + 0x0E)
#define RT_OID_802_11_WSC_QUERY_PROFILE          0x0750

#define RT_OID_SYNC_RT61                            0x0D010750
#define RT_OID_WSC_QUERY_STATUS                  ((RT_OID_SYNC_RT61 + 0x01) & 0xffff)
#define RT_OID_WSC_QUERY_SETUP_LOCK              ((RT_OID_SYNC_RT61 + 0x0D) & 0xffff)

#define RT_PRIV_IOCTL (SIOCIWFIRSTPRIV + 0x0E)
#define OID_GEN_MEDIA_CONNECT_STATUS    0x060B
#define OID_GET_REPEATE_MAC             0x0719

typedef struct
{
    unsigned char channels[64];
} CHANNEL_LIST_T;

#define SKIP_LINE_NUM_MAX 3

void hal_uci2datAndWifiReload();
void hal_getWlanIfName(UINT32 band, char *ifName, int ifNameLen, int wlanIdx );
int hal_getExtChannel(const char *ifName, char *channelExt, int len, int *wirelessBw);
int hal_getWlanLinkUpTime(unsigned int *upsec);
int hal_getChannel(const char *ifName, char *channel, int len, int *wirelessBw);
int hal_setChannel(const char *ifName, int channel);
int hal_disconnectSta(const char *ifName);
void hal_setSsidClientIsolation();
void hal_getWiFiInfStatus(char* ifname, int* status);
void hal_uci2datWifiReloadRfRadioOn(int lastRadioOnFlag2G, int currentRadioOnFlag2G, int lastRadioOnFlag5G, int currentRadioOnFlag5G);
void hal_setAllowToWired(char *tmpValueStr, char *ifName2G, char *ifName5G, char *ifNameEth);
void hal_startWps(UINT32 method, char *pinNum, char *ifName);
int hal_getWscStatus(char *ifName);
void hal_wpsSyncDeviceName(char *devName);
void hal_setWpsConfStatus(UINT32 band, int confStatus);
void hal_setWpsDefaultSSID(UINT32 band, char * wscDefaultSSID);
int hal_getApcliLinkRate(char *ifName, int *rate);
void hal_uci2dat();
void hal_onlyWifiReload(void);
void hal_setRfRadioOn(int lastRadioOnFlag2G, int currentRadioOnFlag2G, int lastRadioOnFlag5G, int currentRadioOnFlag5G);
void hal_setBlackList(int enable, char *devMac, int infIdx);
int hal_wlanScanResultsAll(UINT32 band, WLAN_SCANRET_T *scanRet, int maxBss);
int hal_wlanStartScan(UINT32 band);
int hal_getWifiChannelList(int band, char *country, unsigned char *channelList, int listLen);
int hal_setWIfiLedSetting(const char *ledSettingValue, const char *ifName);
int hal_setNetLed(char *colour, int mode);

#endif
