#ifndef __WIFI_H__
#define __WIFI_H__

#include "fwk/fwk.h"
#include "lan.h"
typedef enum{
    WIFI_CONF_MODE_AP        = 0x00,
    WIFI_CONF_MODE_ROUTER    = 0x01,
    WIFI_CONF_MODE_EXT       = 0x02,
    WIFI_CONF_MODE_BRIDGE    = 0x03
}WIFI_CONF_MODE;

typedef enum{
    WIFI_BAND_STEERING_FORCE_5G      = 1,
    WIFI_BAND_STEERING_PREFER_5G    = 2,
    WIFI_BAND_STEERING_BALANCE       = 3
}WIFI_BAND_STEERING_TYPE;


/*---------------------------Basic struct-------------------------*/
typedef struct
{
    UBOOL8 isEanble;
    char ssid[BUFLEN_64];
    char wirelessBand[BUFLEN_64];
    UBOOL8 isBroadcast;
    char security[BUFLEN_32];
    char password[BUFLEN_128];
    UINT32 wepAuthType;
    char auth_server[BUFLEN_128];
    UINT32 auth_port;
    char auth_secret[BUFLEN_128 + 1];
    UBOOL8 clientIsolation;
    UBOOL8 vlanIsolation;
    UINT32 vlanId;
    UBOOL8 l2Isolation;
    UBOOL8 allowToWired;
    UBOOL8 fastRoaming;
    UBOOL8 bandSteerEn;
    UBOOL8 guest_network;
    char bandSteerTpye[BUFLEN_16];
    char bandSteerRssi[BUFLEN_16];
    char l2IsolationMac[3][BUFLEN_32];
    UINT32 radioLiveTime;
    UINT32 rekey;
}WLAN_IF_CONFIG_T;

typedef struct
{
    int cfgIdx;
    WLAN_IF_CONFIG_T wlanIfconfig2G;
    WLAN_IF_CONFIG_T wlanIfconfig5G;
    char filter[BUFLEN_32];
    char allow[BUFLEN_1024];
    char deny[BUFLEN_1024];
} WLAN_ALL_IF_CONFIG_T;

typedef struct
{
    int smartConnect;
    UINT32 mode;
    UBOOL8 mu_Mimo;
    UBOOL8 fastLane;
    char  fastLaneBand[BUFLEN_8];
    UBOOL8 oneWifiName;
    UBOOL8 syncConfigFromNtgrRouter;
    UINT32 wlFrag;
    UINT32 bandSteerEn;
    UINT32 bandSteerType;
    UINT32 bandSteerRssi;
    UINT32 bandSteerPersent;
    char wireless1radio[BUFLEN_8];
    char wireless2radio[BUFLEN_8];
    char wireless3radio[BUFLEN_8];
    char wireless4radio[BUFLEN_8];
    char deviceName[BUFLEN_128];
    UINT32 mgmtVlan;
    UBOOL8 mgmtVlanEnable;
}WLAN_COMMON_CONFIG_T;

typedef struct
{
    UINT32 channel;
    UINT32 channelStatus;
    UINT32 channelGroup;
    char channelist[BUFLEN_32];
    UINT32 enableCoexist;
    char htMode[BUFLEN_32];
    char hwMode[BUFLEN_32];
    char wirelssMode[BUFLEN_32];
    char wifiCountryCode[BUFLEN_8];
    char macAddress[BUFLEN_32];
    UINT32 ofdma;
    UINT32 wlRts;
    UINT32 axEnable;
    UINT32 preambleMode;
    UINT32 enableRfRadioOn;
    UINT32 enableAutoRf;
    UINT32 txPower;
    UINT32 minSupportRateEnable;
    UINT32 minSupportRate;
    UINT32 beaconPeriod;
    UINT32 dtimPeriod;
    UINT32 mumimo;
    UINT32 txbf;
    UINT32 pmf;
    UINT32 wpsConfStatus;
    UINT32 clientLimitEnable;
    UINT32 clientLimitNumber;
    UBOOL8 igmpsnenable;
}WLAN_DEV_CONFIG_T;

typedef struct
{
    WLAN_DEV_CONFIG_T wifi2GDevCfg;
    WLAN_DEV_CONFIG_T wifi5GDevCfg;
} WLAN_ALL_DEV_CONFIG_T;

/*---------------------------Basic struct-------------------------*/


/* ----------------for function self  defintion-------------------*/
typedef struct
{
    WLAN_COMMON_CONFIG_T  wifiAdvCommonCfg;
    WLAN_IF_CONFIG_T      wlanIfConfig1;
    WLAN_IF_CONFIG_T      wlanIfConfig2;
    WLAN_IF_CONFIG_T      wlanIfConfig3;
    char ssidIsolation[BUFLEN_32];
}WIFI_CONFIG_SET_T;

typedef struct
{
    UINT32 enable2GSchedule;
    UINT32 enable5GSchedule;
} WLAN_SCH_CONFIG_T;

typedef struct 
{
    WLAN_IF_CONFIG_T      wifi2GIfCfg1;
    WLAN_IF_CONFIG_T      wifi2GIfCfg2;
    WLAN_IF_CONFIG_T      wifi2GIfCfg3;
    WLAN_IF_CONFIG_T      wifi2GIfCfg4;
    WLAN_IF_CONFIG_T      wifi2GIfCfgMgmt;    
    WLAN_IF_CONFIG_T      wifi5GIFCfg1;
    WLAN_IF_CONFIG_T      wifi5GIFCfg2;
    WLAN_IF_CONFIG_T      wifi5GIFCfg3;
    WLAN_IF_CONFIG_T      wifi5GIFCfg4;
}WIFI_IF_GROUP_CONFIG_T;


typedef struct 
{
    WLAN_COMMON_CONFIG_T    wifiAdvCommonCfg;
    WLAN_DEV_CONFIG_T       wifi2GDevCfg;
    WLAN_DEV_CONFIG_T       wifi5GDevCfg;
    WIFI_IF_GROUP_CONFIG_T  wifiIfGroupCfg;
    WLAN_SCH_CONFIG_T       wifiScheduleCfg;
    NETLAN_CONFIG_T         lanConfig;
}LAN_WIFI_SETTING_CONFIG_T;

typedef enum{
    ENCRYPTION_NONE     = 0x00,
    ENCRYPTION_WEP      = 0x05,
    ENCRYPTION_WPAPSK   = 0x01,
    ENCRYPTION_WPA2PSK  = 0x02,
    ENCRYPTION_WPA      = 0x04,
    ENCRYPTION_WPA2     = 0x08,
    ENCRYPTION_WPA3PSK  = 0x10,
    //ENCRYPTION_WPA3SAE  = 0x20,
    ENCRYPTION_WPAPR    = 0x20,
    ENCRYPTION_WPA2PR   = 0x40,
    ENCRYPTION_WPA3PR   = 0x80,
    ENCRYPTION_WPA3     = 0x100,
}WLAN_ENCRYPTTYPE_E;

/*
  b^00000001  - TKIP
  b^00000010  - AES
  b^00000100  - SAE
*/
typedef enum{
    CIPHER_TKIP      = 0x01,
    CIPHER_AES       = 0x02,
    CIPHER_SAE       = 0x04,
}WLAN_CIPHERTYPE_E;

typedef struct
{
    char ifName[BUFLEN_32];
    char ssid[BUFLEN_64];
    char bssid[BUFLEN_32];
    char channel[BUFLEN_8];
    WLAN_ENCRYPTTYPE_E encryption;
    char cipher[BUFLEN_32];
    char authSuites[BUFLEN_32];
    char signal[BUFLEN_32];
    char mode[BUFLEN_32];
    char bw[BUFLEN_32];
    char vie[256];
    char vieHex[128];
    int  ngrExtAvailable;
    int  hopCnt;
    int  iInValid;
}WLAN_SCANRET_T;

#define WLAN_SCANRET_MAX (128)

/* ----------------for function self  datil-----------------------*/

typedef enum
{
    WLAN_2G = 1,
    WLAN_5G,
} WLAN_BAND_E;

#define WLAN_ENABLE  TRUE
#define WLAN_DISABLE FALSE

#define WIRELESS_1              1
#define WIRELESS_2              2
#define WIRELESS_3              3
#define WIRELESS_4              4
#define WIRELESS_MGMT    5


#define WLAN1_2G_INDEX                  0
#define WLAN2_2G_INDEX                  1
#define WLAN3_2G_INDEX                  2
#define WLAN4_2G_INDEX                  3
#define WLAN5_2G_MGMT_INDEX             4
#define WLAN1_5G_INDEX                  5
#define WLAN2_5G_INDEX                  6
#define WLAN3_5G_INDEX                  7
#define WLAN4_5G_INDEX                  8
#define WLAN5_5G_MGMT_INDEX             9

#define WLAN1_2G5G_INDEX                1
#define WLAN2_2G5G_INDEX                2
#define WLAN3_2G5G_INDEX                3
#define WLAN4_2G5G_INDEX                4
#define WLAN5_2G5G_MGMT_INDEX           5


#define WIRELESS_NUM 10    //2.4G+5G的总数量

#define WLAN_5G_2_2G_IDX_DAT          (WLAN1_5G_INDEX - WLAN1_2G_INDEX)


#define WPA3_PASS_PHRASE_LENGTH 63

#define WLAN_2G_DEV "wireless.2g"
#define WLAN_5G_DEV "wireless.5g"
#define WLAN_2G_APCLI_DEV "wireless.apcli_2g"
#define WLAN_5G_APCLI_DEV "wireless.apcli_5g"
#define WLAN_2G_FIRST_IF "wireless.@wifi-iface[0]"
#define WLAN_2G_SECOND_IF "wireless.@wifi-iface[1]"
#define WLAN_2G_THIRD_IF "wireless.@wifi-iface[2]"
#define WLAN_5G_FIRST_IF "wireless.@wifi-iface[3]"
#define WLAN_5G_SECOND_IF "wireless.@wifi-iface[4]"
#define WLAN_5G_THIRD_IF "wireless.@wifi-iface[5]"
#define WLAN_2G5G_DEV "wireless.2g_5g"

#define STR_SECURITY_NONE                        "None"
#define STR_SECURITY_OWE                         "OWE"
#define STR_SECURITY_WPA2SAE                     "WPA2-Personal"
#define STR_SECURITY_WPASAE_WPA2SAE              "WPA/WPA2-Personal"
#define STR_SECURITY_WPA_WPA2_ENTERPRISE         "WPA/WPA2-Enterprise"
#define STR_SECURITY_WPA2_ENTERPRISE             "WPA2-Enterprise"
#define STR_SECURITY_WPA3_ENTERPRISE             "WPA3-Enterprise"
#define STR_SECURITY_WPA3SAE                     "WPA3-Personal"
#define STR_SECURITY_WPA2SAE_WPA3SAE             "WPA2/WPA3-Personal"
#define STR_SECURITY_WPA2_WPA3_ENTERPRISE        "WPA2/WPA3-Enterprise"

#define MAXSTANUM "64"


typedef enum{
    SECURITY_NONE                 = 0x01,
    SECURITY_WPA2SAE              = 0x04,
    SECURITY_WPASAE_WPA2SAE       = 0x05,
    SECURITY_WPA_WPA2_ENTERPRISE  = 0x06,
    SECURITY_WPA3SAE              = 0x07,
    SECURITY_WPA2SAE_WPA3SAE      = 0x08,
}WLAN_ENCRYPTTYPE_CGI_E;

#define DAI_WIFI_CONFIG_SET_INT(uciName, key) \
    do{\
        char tmpBuf[BUFLEN_128] = {0}; \
        UTIL_SNPRINTF(tmpBuf, sizeof(tmpBuf), "%d", key);\
        wifiConfigSet(uciName, tmpBuf); \
    }while(0)



static inline void wifiIfConfigGet(int ssidIdx, const char *keySuffix, char *value, UINT32 valueLen)
{
#ifdef UCI
    char getStr[BUFLEN_256] = {0};

    memset(value, 0, valueLen);

    UTIL_SNPRINTF(getStr, sizeof(getStr), "wireless.@wifi-iface[%d].%s", ssidIdx, keySuffix);
    ucix_get(getStr, value, valueLen);
#endif
}

static inline void wifiIfConfigSet(int ssidIdx, const char *keySuffix, char *value)
{
#ifdef UCI

    char setStr[BUFLEN_1024] = {0};

    UTIL_SNPRINTF(setStr, sizeof(setStr), "wireless.@wifi-iface[%d].%s=%s", ssidIdx, keySuffix, value);
    ucix_set(setStr);
#endif
}

static inline void wifiConfigSet(const char *keySuffix, char *value)
{
#ifdef UCI
    char setStr[BUFLEN_128] = {0};

    UTIL_SNPRINTF(setStr, sizeof(setStr), "wireless.2g_5g.%s=%s", keySuffix, value);

    ucix_set(setStr);
#endif
}

static inline void wifiConfigGet(const char *keySuffix, char *value, UINT32 valueLen)
{
#ifdef UCI
    char getStr[BUFLEN_128] = {0};

    memset(value, 0, valueLen);

    UTIL_SNPRINTF(getStr, sizeof(getStr), "wireless.2g_5g.%s", keySuffix);
    ucix_get(getStr, value, valueLen);
#endif
}

static inline void wifiDevConfigGet(int band, const char *keySuffix, char *value, UINT32 valueLen)
{
#ifdef UCI
    char getStr[BUFLEN_128] = {0};

    memset(value, 0, valueLen);
    if (WLAN_2G == band)
    {
        UTIL_SNPRINTF(getStr, sizeof(getStr), "wireless.2g.%s", keySuffix);
    }
    else
    {
        UTIL_SNPRINTF(getStr, sizeof(getStr), "wireless.5g.%s", keySuffix);
    }
    ucix_get(getStr, value, valueLen);
#endif
}

static inline void wifiDevConfigSet(int band, const char *keySuffix, char *value)
{
#ifdef UCI
    char setStr[BUFLEN_128] = {0};

    if (WLAN_2G == band)
    {
        UTIL_SNPRINTF(setStr, sizeof(setStr), "wireless.2g.%s=%s", keySuffix, value);
    }
    else
    {
        UTIL_SNPRINTF(setStr, sizeof(setStr), "wireless.5g.%s=%s", keySuffix, value);
    }
    ucix_set(setStr);
#endif
}

static inline void wifiApcliConfigGet(int band, const char *keySuffix, char *value, UINT32 valueLen)
{
#ifdef UCI
    char getStr[BUFLEN_128] = {0};

    memset(value, 0, valueLen);
    if (WLAN_2G == band)
    {
        UTIL_SNPRINTF(getStr, sizeof(getStr), "wireless.apcli_2g.%s", keySuffix);
    }
    else
    {
        UTIL_SNPRINTF(getStr, sizeof(getStr), "wireless.apcli_5g.%s", keySuffix);
    }
    ucix_get(getStr, value, valueLen);
#endif
}

static inline void wifiApcliConfigSet(int band, const char *keySuffix, char *value)
{
#ifdef UCI
    char setStr[BUFLEN_128] = {0};

    if (WLAN_2G == band)
    {
        UTIL_SNPRINTF(setStr, sizeof(setStr), "wireless.apcli_2g.%s=%s", keySuffix, value);
    }
    else
    {
        UTIL_SNPRINTF(setStr, sizeof(setStr), "wireless.apcli_5g.%s=%s", keySuffix, value);
    }
    ucix_set(setStr);
#endif
}

int dai_getWirelessInterfaceInfo(int index, WLAN_IF_CONFIG_T *wlanIfConfig);
int dai_setWirelessInterfaceInfo(int ifIdx, WLAN_IF_CONFIG_T *wlanIfConfig);
int dai_setWirelessInfo(WIFI_CONFIG_SET_T *wlanConfig);
int dai_getSmartConnect();
int dai_setSmartConnect(int enable);
int dai_getAvailableExtChannel(UINT32 band, char *extChanel, int len, int wlanIdx, int *bw);
int dai_wifiDevConfigGet(int band, const char *keySuffix, char *value, UINT32 valueLen);
int dai_wifiConfigGet(const char *keySuffix, char *value, UINT32 valueLen);
int dai_ht160Enable();
int dai_setWirelessSettingInfo(LAN_WIFI_SETTING_CONFIG_T *wlanSettingConfig);
uint32_t dai_getWlanLinkUpTime(int band);
int dai_getWirelessInterfaceParamValue(int wirelessIndex, const char *key, char *value, int valueLen);
int dai_getAvailableChannel(UINT32 band, char *chanel, int len, int wlanIdx, int *bw);
int dai_setChannel(UINT32 band, int chanel, int wlanIdx);
int dai_wifiIfConfigGet(int ifIdx, const char *keySuffix, char *value, UINT32 valueLen);
int dai_wifiIfConfigSet(int ifIdx, const char *keySuffix, char *value);
int dai_wifiApcliConfigGet(int band, const char *keySuffix, char *value, UINT32 valueLen);
int dai_wifiApcliConfigSet(int band, const char *keySuffix, char *value);
void dai_wifiDevConfigSet(int band, const char *keySuffix, char *value);
void dai_wifiReload();
void dai_setSsidClientIsolation();
int dai_wifiSwitchApcliSync(int enable);
void dai_countryCodeToRegion(char *pCountryCode, int pCountryCode_len, char *pRegion, int pRegion_len,
                             char *pRegionCode, int pRegionCode_len);
void dai_getWiFiInfStatus(UINT32 band, int wlanIdx, int* status);
void dai_getWirelessInterfaceStatus(int index, int* status);
void dai_uciCommit(const char* pConfig, UBOOL8 bOverWrite);
void dai_wifiReloadRfRadioOn(int lastRadioOnFlag2G, int currentRadioOnFlag2G, int lastRadioOnFlag5G, int currentRadioOnFlag5G);
void dal_setAllowToWired();
int dai_backUpWifiRadioStatus();
int dai_recoverWifiRadioStatus();
int dai_getApcliRate(int *rate);
void dai_wifiUci2Dat();
void dai_onlyWifiReloadAndRfRadioOn(int lastRadioOnFlag2G, int currentRadioOnFlag2G, int lastRadioOnFlag5G, int currentRadioOnFlag5G);
int dai_setWirelessEncrytion(WLAN_IF_CONFIG_T wlanIfconfig2G, WLAN_IF_CONFIG_T wlanIfconfig5G, int wlanIdx);
int dai_setWirelessSupportRate(WLAN_DEV_CONFIG_T *wlanIfconfig2G, WLAN_DEV_CONFIG_T *wlanIfconfig5G);
int dai_getHtmodeByWirelessMode(char *htMode, const char *wirelessMode);
int dai_setWirelessChannel(WLAN_DEV_CONFIG_T wifi2GDevCfg, WLAN_DEV_CONFIG_T wifi5GDevCfg);
int dai_setWirelessBandSteering(WLAN_COMMON_CONFIG_T *wifiAdvCommonCfg);
int dai_getSsidByIfName(const char *ifName, char *ssid, int ssidLen);
int dai_wifiGetScanRet(UINT32 band, WLAN_SCANRET_T *scanRet);
int dai_wifiStartScan(UINT32 band);
int dai_setWizardWirelessSetting(const char *ssid, const char *password, const char *country);
int dai_backupAllRadioStatus();
int dai_disableAllRadioStatus();
int dai_recoverAllRadioStatus();
int dai_setWifiDriverLedTxBlinkMode(UBOOL8 enable, UBOOL8 reverPolarity, UINT32 band, UINT32 txBlinkMode);
int dai_setWifiDriverLedOnOff(UBOOL8 off, UBOOL8 reverPolarity, UINT32 band);
int dai_getWirelessMacFilter(int wlanIdx, char *filter, int filterLen, char *allow, int allowLen, char *deny, int denyLen);
int dai_setWirelessMacFilter(int wlanIdx, char *filter, char *allow, char *deny);
int dai_addWirelessMacFilterDeny(int wlanIdx, const char *mac);
int dai_wifiGetDevName(char *value, int valueLen);
int dai_getFirstAvailableWifiMac(int band, char *value, UINT32 valueLen);
int dai_getWirelessRadio(const int index, int *radioEnable);
int dai_wifiIfStatusGet();
#endif
