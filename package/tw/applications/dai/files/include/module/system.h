#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "fwk/fwk.h"
#include <hiredis/hiredis.h>
#include <sys/ioctl.h>
//#include <linux/wireless.h>

#define IMAGE_LOCALPATH "/tmp/image.bin"
#define FIRMWARE "/tmp/firmware.img"

#define DAI_FENV_MAC  "mac"
#define DAI_FENV_SN  "sn"
#define DAI_FENV_MODEL  "model"
#define DAI_FENV_PIN  "pin"
#define DAI_FENV_REGION  "region"
#define DAI_FENV_HARDWARE  "hardware"
#define DAI_FENV_FACTORY_MODE  "factory_mode"
#define DAI_FENV_DEFAULT_REGION  "default_region"
#define DAI_FENV_SSID  "ssid"
#define DAI_FENV_PASSPHRASE  "passphrase"
#define DAI_FENV_AXMODEL  "axmodel"
#define DAI_FENV_PCBA_SN  "pcba_sn"

#define DAI_UENV_LANGUAGE  "language"

#define DAI_INSTALL_METHOD_UNKNOWN  "unknown"
#define DAI_INSTALL_METHOD_APP      "APP"
#define DAI_INSTALL_METHOD_GUI      "GUI"

#define GUI_INSTALL_HIJACK_NA                          "NA"
#define GUI_INSTALL_HIJACK_PAGE_SEEN                   "Page Seen"
#define GUI_INSTALL_HIJACK_CONTINUE_GUI_INSTALL        "Continue GUI install"

#define SOAP_CONF_FILE    "/etc/soap/soap.conf"

#define DAI_LED_NAME_POWER  "power"
#define DAI_LED_NAME_NET  "net"
#define DAI_LED_NAME_WIFIN  "wifin"
#define DAI_LED_NAME_WIFIA  "wifia"

//#define DAI_LED_NAME_RLINK  "rlink"
//#define DAI_LED_NAME_CLINK  "clink"
//#define DAI_LED_NAME_WPS  "wps"
#define DAI_LED_ALL "all"

#define DAI_LED_COLOR_AMBER "amber"
#define DAI_LED_COLOR_MIXED "mixed"
#define DAI_LED_COLOR_RED "red"
#define DAI_LED_COLOR_GREEN "green"
#define DAI_LED_COLOR_BLUE "blue"


#define TELNET_STATUS_FILE "/tmp/enable_telnet_debug"
#define MIRROR_STATUS_FILE "/tmp/enable_mirror_debug"
#define WANLANCAPTURE_STATUS_FILE "/tmp/enable_WanLanCapture_debug"
#define COLLECTDEBUG_STATUS_FILE "/tmp/enable_collect_debug"
#define CPULOAD_FILE_PATH    "/tmp/cpuLoadFile"
#define NET_DEV_FILE "/proc/net/dev"

#define DAI_MTD_PART_PRELOADER_NAME "Preloader"
#define DAI_MTD_PART_ATF_NAME "ATF"
#define DAI_MTD_PART_BOOT_NAME "Bootloader"
#define DAI_MTD_PART_CONFIG_NAME "Config"
#define DAI_MTD_PART_FACTORY_NAME "Factory"
#define DAI_MTD_PART_KERNEL1_NAME "Kernel"
#define DAI_MTD_PART_KERNEL2_NAME "kernel"
#define DAI_MTD_PART_ROOTFS_NAME "rootfs"
#define DAI_MTD_PART_ROOTFS_DATA_NAME "rootfs_data"
#define DAI_MTD_PART_KERNEL_BACKUP_NAME  "Kernel_backup"
#define DAI_MTD_PART_CFG_NAME "CFG"
#define DAI_MTD_PART_RAE_NAME "RAE"
#define DAI_MTD_PART_POT_NAME "POT"
#define DAI_MTD_PART_LANG_NAME "Language"
#define DAI_MTD_PART_TRAFFIC_NAME "Traffic"
#define DAI_MTD_PART_CERT_NAME "Cert"
#define DAI_MTD_PART_NTGR_CRYPT_K_NAME "NTGRcryptK"
#define DAI_MTD_PART_NTGR_CRYPT_D_NAME "NTGRcryptD"
#define DAI_MTD_PART_LOG_NAME "LOG"
#define DAI_MTD_PART_USER_DATA_NAME  "User_data"

#define UH_USER_HIJACK_SUCCESS    "99"

#define GPIO_SYS_PATH "/sys/class/gpio"
#define GPIO_SYS_EXPORT "/sys/class/gpio/export"
#define GPIO_SYS_UNEXPORT "/sys/class/gpio/unexport"

typedef enum
{
    POWER_TYPE_UNKNOW = 0,
    POWER_TYPE_ADAPTOR = 1,  /* 采用电源是配置直接供电 */
    POWER_TYPE_POE_AF = 2,   /* 采用poe 供电，af状态 */
    POWER_TYPE_POE_AT = 3    /* 采用poe供电，at状态 */
} POWER_TYPE_E;

typedef enum
{
    CONTROL_MODE_NORMAL = 0,     /* 正常亮灭 */
    CONTROL_MODE_FACTORY_ALLON,  /* 工厂产测所有开 */
    CONTROL_MODE_FACTORY_ALLOFF, /* 工厂产测所有关 */
    CONTROL_MODE_ALLNOTBLINK,    /* 节能模式1 正常亮灭但是不闪烁 */
    CONTROL_MODE_ALLOFF_POWER,    /* 节能模式2 除POWER所有都灭 */
    CONTROL_MODE_FACTORY_ALLGREENON,  /* 工厂产测所有绿灯开 */
    CONTROL_MODE_FACTORY_ALLREDON,  /* 工厂产测所有红灯开 */
} DAI_LED_CONTROL_MODE;

typedef enum
{
    DAI_NETMODE_ROUTER,
    DAI_NETMODE_AP,
    DAI_NETMODE_BRIDGE,
    DAI_NETMODE_WDS = DAI_NETMODE_BRIDGE,
    DAI_NETMODE_NUM,
} DAI_NETMODE_T;

typedef enum
{
    REBOOT_UNKNOWN = 0,
    REBOOT_KERNEL_CRASH,
    REBOOT_BUTTON,
    REBOOT_BUTTON_FACTORY,
    REBOOT_GUI_FACTORY,
    REBOOT_GUI,
    REBOOT_UPGRADE,
    REBOOT_IMPORT_CONFIG,
    REBOOT_SOAP
} DAI_REBOOT;

typedef enum
{
    DAI_AFU_FLAG_PROD,
    DAI_AFU_FLAG_BETA,
    DAI_AFU_FLAG_QA
} DAI_AFU_FLAG_E;

typedef struct {
    char answer[BUFLEN_128];
    int  type;
} ANSWER_CONFIG_T;

typedef struct {
    unsigned int total;
    unsigned free;
} DAI_MEM_INFO;

typedef struct {
    unsigned int all;
    unsigned idle;
} DAI_CPU_INFO;

typedef struct {
    char rxByte[BUFLEN_16];
    char rxPacket[BUFLEN_16];
    char rxErr[BUFLEN_16];
    char rxDrop[BUFLEN_16];
    char txByte[BUFLEN_16];
    char txPacket[BUFLEN_16];
    char txErr[BUFLEN_16];
    char txDrop[BUFLEN_16];
} DAI_DEV_STATISTICS;

typedef struct
{
    char    fwLastUpateTime[BUFLEN_32];
    char    fwLastCheckTime[BUFLEN_32];
    char    fwLastAutoUpgradeTime[BUFLEN_32];
    char    fwEventType[BUFLEN_32];
    char    fwUpgradeTriggered[BUFLEN_32];
    char    fwDownloadUrl[BUFLEN_128];
    char    fwDownloadUrlFromCloud[BUFLEN_128];
    char    fwConfigSetting[BUFLEN_128];
    char    routerCurrentVersion[BUFLEN_32];
    char    routerNewVersion[BUFLEN_32];
    char    fwCheckResult[BUFLEN_32];
    char    fwUpgradeMethod[BUFLEN_16];
    char    fwUpgradeLog[BUFLEN_128];
    UBOOL8  fwUpgRebootFlag;
    UBOOL8  fwAutoUpgradeEnable;
    UBOOL8  fwUpgradeLatest;
} DAI_UPG_INFO_T;

typedef struct
{
    char ntpResult[BUFLEN_16];
    char ntpFailReason[BUFLEN_128];
    char ntpPortNumber[BUFLEN_16];
    char timeZoneConfig[BUFLEN_16];
    char timeZoneOffset[BUFLEN_16];
} DAI_NTP_INFO;

typedef enum
{
    NET_WIZARD_STATE_BLANK,
    NET_WIZARD_STATE_NETWORK_CREATED,
    NET_WIZARD_STATE_CONFIGURED
} NET_WIZARD_STATE_E;

typedef enum
{
    DAI_SYS_NET_MODE_ROUTER,
    DAI_SYS_NET_MODE_AP,
    DAI_SYS_NET_MODE_BRIDGE,
    DAI_SYS_NET_MODE_NUM
} DAI_SYS_NET_MODE_T;

/**
 * \brief          AES context structure
 */
typedef struct
{
    unsigned long erk[64];     /*!< encryption round keys */
    unsigned long drk[64];     /*!< decryption round keys */
    int nr;                    /*!< number of rounds      */
} aes_context_t;

#define RSA_SIGN_BUF_SIZE 256 /*2048 bit rsa sign size*/
#define RSA_PKCS1_PADDING_SIZE  11
#define RSA_SIGN_ORI_DATA_MAX_SIZE (RSA_SIGN_BUF_SIZE - RSA_PKCS1_PADDING_SIZE)

typedef struct _rsaSignData
{
    char imageHeadDigest[32];
    char plaintextDigest[32];
} RSA_SIGN_DATA;

typedef  struct _image_head
{
    char model[32];        /*model name*/
    char region[32];       /*region*/
    char version[64];      /*version*/
    char dateTime[64];     /*date*/
    char reserved[64];    /*reserved space, if add struct member, please adjust this reserved size to keep the head total size is 512 bytes*/
    char sign[RSA_SIGN_BUF_SIZE];       /*2048 bit rsa sign*/
} __attribute__((__packed__)) IMAGE_HEAD;

typedef  struct _image_tail
{
    char checkSum[4];       /*checkSum crc*/
} __attribute__((__packed__)) IMAGE_TAIL;

#define REDIS_UNIX_SOCK "/tmp/.redis.sock"

typedef struct
{
    char field[BUFLEN_64];
    char *value;
} REDIS_FIELD_ELEMENT_T;

typedef struct 
{
    char name[32];
    char version[32];
    UINT32 size;
    UINT32 crc;
    char padding[56];
    char data[0];
} __attribute__((__packed__)) DAI_LANGUAGE_PARTITION_T;

typedef struct
{
    int idx;
} DAI_GET_LANG_TABLE_CONTEXT_T;

#define LANGUAGE_TABLE_BLOCK_SIZE (256 * 1024)
#define LANGUAGE_TABLE_BUF_MAX_SIZE (LANGUAGE_TABLE_BLOCK_SIZE - sizeof(DAI_LANGUAGE_PARTITION_T))
#define MANUALCLOCK "/tmp/manual_clock"
#define NTP_SYNC_OK "/tmp/ntp_sync_ok"

typedef struct
{
    UINT8 logSiteAllowed;
    UINT8 logSiteBlock;
    UINT8 logLoginWeb;
    UINT8 logRouterOp;
    UINT8 logDos;
    UINT8 logPort;
    UINT8 logWireConn;
    UINT8 logWireSche;
    UINT8 logVpn;
    UINT8 logServiceBlock;
} LOGS_MASK_T;

typedef enum{
    LOG_SITE_ALLOWED,
    LOG_SITE_BLOCK,
    LOG_SERVICE_BLOCK,
    LOG_LOGIN_WEB,
    LOG_ROUTER_OP,
    LOG_DOS,
    LOG_PORT,
    LOG_WIRE_CONN,
    LOG_WIRE_SCHE,
    LOG_VPN,
    LOG_AWAYS,
} LOG_MODULE_E;

typedef enum{
    WDS_UPLINKMODE_2G = 0,
    WDS_UPLINKMODE_5G,
    WDS_UPLINKMODE_ALL,
} WDS_UPLINKMODE_E;

#define NTG_MAX_LOG_ENTRIES        1024
#define NTG_MAX_LOG_LINE_BYTES     128
#define LOG_TIME_FLAG              "TIME::"
#define LOG_TIME_SIZE              64

typedef struct
{
    UINT8 email_notify_enabled;   /* 0, 1 */
    UINT8 send_alert_immediately; /* 0, 1 */
    char email_addr[128];
    char email_smtp[128];
    UINT32 email_port;
    UINT8 email_endis_auth;       /* 0, 1 */
    char auth_user[128];
    char auth_pwd[128];
    UINT8 block_site;             /* 0, 1 */
    char cfAlert_Select[16];      /* full, Hourly, Daily, Weekly, None */
    UINT8 cfAlert_Day;
    UINT8 cfAlert_Hour;
    char cfAlert_am[8];           /* am, pm */
} EMAIL_NOTI_CFG_T;

typedef struct
{
    UINT8 emailStatus;            /* 0, 1 */
    char em_from[BUFLEN_128];
    char em_to[BUFLEN_128];
    char em_subject[BUFLEN_128];
    char em_username[BUFLEN_128];
    char em_password[BUFLEN_128];
    char em_smtp_server[BUFLEN_64];
    UINT32 em_smtp_port;
    UINT8 em_security;            /* 0:None, 1:SSL/TLS, 2:STARTTLS */
} EMAIL_ALERT_CFG_T;

typedef struct
{
    UINT8 http_rmenable;   /* 0, 1 */
    char rm_access[64];    /* ip_single, ip_range, all */
    UINT32 http_rmport;    /* default 8443 */
    char ip_list[128];
    char ip_start[32];
    char ip_end[32];
} HTTPS_REMOTE_CFG_T;

#if defined(CUSTOMER_MODEL_WAX220)
#define MAX_NUMBER_OF_MAC 544
#else
#define MAX_NUMBER_OF_MAC 128
#endif
#define RTPRIV_IOCTL_GET_DEV_COUNT_INFO              (SIOCIWFIRSTPRIV + 0x06)
#define RTPRIV_IOCTL_GET_MAC_TABLE_STRUCT            (SIOCIWFIRSTPRIV + 0x1F)

typedef struct _RT_802_11_COUNT_INFO_ENTRY{
	unsigned char  ApIdx;
	unsigned char  Addr[MAC_ADDR_LEN];
	UINT16 Aid;
	UINT64 TxBytes;
	UINT64 RxBytes;
	UINT64 TxPackets;
	UINT64 RxPackets;
}RT_802_11_COUNT_INFO_ENTRY;

typedef struct _RT_802_11_COUNT_INFO { 
	unsigned long  Num;
	RT_802_11_COUNT_INFO_ENTRY Entry[MAX_NUMBER_OF_MAC];
} RT_802_11_COUNT_INFO;


typedef union _HTTRANSMIT_SETTING {
    struct
    {
        unsigned short MCS : 6; // MCS
        unsigned short rsv : 1;
        unsigned short BW : 2; //channel bandwidth 20MHz or 40 MHz
        unsigned short ShortGI : 1;
        unsigned short STBC : 1; //SPACE
        unsigned short eTxBF : 1;
        unsigned short iTxBF : 1;
        unsigned short MODE : 3; // Use definition MODE_xxx.
    } field;
    unsigned short word;
} HTTRANSMIT_SETTING;

typedef struct _RT_802_11_MAC_ENTRY
{
    unsigned char ApIdx;
    unsigned char Addr[6];
    unsigned char Aid;
    unsigned char Psm;    // 0:PWR_ACTIVE, 1:PWR_SAVE
    unsigned char MimoPs; // 0:MMPS_STATIC, 1:MMPS_DYNAMIC, 3:MMPS_Enabled
    signed char AvgRssi0;
    signed char AvgRssi1;
    signed char AvgRssi2;
    signed char AvgRssi3;
    unsigned int ConnectedTime;
    HTTRANSMIT_SETTING TxRate;
    unsigned int LastRxRate;
    short StreamSnr[3];
    short SoundingRespSnr[3];
} RT_802_11_MAC_ENTRY;

typedef struct _RT_802_11_MAC_TABLE
{
    unsigned long Num;
    RT_802_11_MAC_ENTRY Entry[MAX_NUMBER_OF_MAC]; //MAX_LEN_OF_MAC_TABLE = 128
} RT_802_11_MAC_TABLE;


typedef struct
{
    char checkSum[4];
    char tag[32];
    int partSize;
    char reserve[24];
}__attribute__((__packed__)) PARTITION_HEADER_T;

#define MTD_BOOT_TAG               "MTD_BOOT_TAG"
#define MTD_IMAGEA_TAG              "MTD_IMAGEA_TAG"
#define MTD_IMAGEB_TAG              "MTD_IMAGEB_TAG"
#define NAND_BLOCK_SIZE		0x20000
#define WAX206_IMAGE_OFFSET	0x220000
#define WAX202_IMAGE_OFFSET	0x1A0000
#define WAX214v2_IMAGE_OFFSET	0x1A0000

int dai_getWebLoginUsername(char *username, int len);
int dai_getWebLoginPassword(char *password, int len);
UBOOL8 dai_verifyWebLoginPassword(char *password);
int dai_setWebLoginUserPasswd(char *username, char *password);
int dai_setSystemLoginPasswd(char *username, char *password);
int dai_setSystemUserPasswd(char *username, char *password, char *unencpasswd);
int dai_getWebLoginRememberMe(char *rememberMe);
int dai_setWebLoginRememberMe(char *rememberMe);
int dai_getUserPasswdEnable(char *enable, int len);
int dai_setUserPasswdEnable(char *enable, int len);
int dai_getUserAnswerType(int *answer1type, int *answer2type);
int dai_checkAnswerEmpty(int *answer1, int *answer2);
int dai_setUserAnswerConfig(ANSWER_CONFIG_T *answer1, ANSWER_CONFIG_T *answer2);
UBOOL8 dai_verifyAnswerConfig(char *answer1, char *answer2);

time_t dai_getPasswordRecoveredTimestamp();
int dai_setPasswordRecoveredTimestamp(time_t ts);

int dai_sysGetLanguage(char* lang, int len);
int dai_sysSetLanguage(const char* lang);

int dai_sysSetLanguagesetLedEnable(UBOOL8 enable);
UBOOL8 dai_sysGetLanguagesetLedEnable();

int dai_sysCreateBackup(const char* path);

int dai_sysRestoreBackup(const char* path);

int dai_sysSetLedControlMode(int mode);

int dai_sysGetLedControlMode(int *mode);

int dai_sysSetLedOn(const char *ledName, const char *color);

int dai_sysSetLedOff(const char *ledName, const char *color);

int dai_sysSetLedBlink(const char *ledName, const char *color, int delayOn, int delayOff);
/*Netgear POT api*/
int dai_sysSetPotValue(void);

int dai_sysGetPotValue(unsigned int *potvalue);

int dai_sysSetPotStamac(const char *stamac);

int dai_sysGetPotStamac(char *stamac);

int dai_sysSetPotNtptime(void);

int dai_sysGetPotNtptime(char *ntptime);

void dai_sysSetNtpSuccessFlag(void);

unsigned int dai_sysGetPotMaxValue(void);

UBOOL8 dai_sysGetScheduleEnable();

int dai_sysGetLanguageSelection(char *value, int valueLen);

int dai_sysSetLanguageSelection(char *value);

int dai_sysGetGuiRegion(char *value, int valueLen);

int dai_sysSetGuiRegion(char *value);

int dai_sysGetModel(char *value, int valueLen);

int dai_sysGetModelInfo(char *value, int valueLen);

int dai_sysGetRegion(char *value, int valueLen);

int dai_sysGetBaseLanMac(char *value, int valueLen);

int dai_sysGetBaseWanMac(char *value, int valueLen);

int dai_sysGetSN(char *sn, int len);
int dai_sysGetSsid(char *value, int valueLen);
int dai_sysGetPassPhrase(char *value, int valueLen);

int dai_sysGetFactoryEnv(const char *name, char *value, int valueLen);

int dai_sysSetFactoryEnv(const char *name, const char *value);

int dai_sysGetUserEnv(const char *name, char *value, int valueLen);

int dai_sysSetUserEnv(const char *name, const char *value);

int dai_sysRestoreFactory();

int dai_sysGetRestoreFactoryStatus();

int dai_sysIsOrNotRestoreStatus();

int dai_sysGetBootSeconds();

int dai_sysGetMemInfo(DAI_MEM_INFO *info);

int dai_sysGetCpuInfo(DAI_CPU_INFO *info, int idx);

int dai_setNetRaeAnalyticsInfoCfg(DAI_UPG_INFO_T *upgInfo);

int dai_getNetRaeAnalyticsInfoCfg(DAI_UPG_INFO_T *upgInfo);

int dai_getNtpInfo(DAI_NTP_INFO *ntp);

int dai_sysGetSoftwareVersion(char *ver, int len);

int dai_sysGetLanguageVersion(char *value, int valueLen);

int dai_sysGetCpuLoad(float *cpuAveByCores, int len, int idx);

int dai_sysGetCpuNum(int *cpunum);

int dai_sysStartRealTimeProcess();

int dai_sysGetMemUsage(unsigned long *memUsed, unsigned long *memTotal);

void dai_sysGetMemStatistics(const char *name, char *value, int len);

int dai_sysGetFlashUsage(char *flashUsage, int len);

int dai_sysGetNetworkSessionUsage(char *NetworkSessionUsage, int len);

int dai_sysGetBootSeconds();

void dai_sysGetLocalTime(char *value, int len);

UBOOL8 dai_sysGetManageByGuiStatus(void);

int dai_sysSetManageByGuiStatus(UBOOL8 status);

UBOOL8 dai_sysGetManageByAppStatus(void);

int dai_sysSetManageByAppStatus(UBOOL8 status);

int dai_getGuiInstallHijack(char *method, int len);

int dai_setGuiInstallHijack(const char *method);

int dai_sysGetInstallMethod(char *method, int len);

int dai_sysSetInstallMethod(const char *method);

UBOOL8 dai_getInstallByWPS(void);

int dai_setInstallByWPS(UBOOL8 status);

int dai_sysSetFirstSetup(UBOOL8 firstSetup);

UBOOL8 dai_sysGetIsFirstSetup();

int dai_sysSetCaFinish(UBOOL8 caFinish);

UBOOL8 dai_sysGetCaFinish();

int dai_sysSetnetFirstSetRegion(UBOOL8 netFirstSetRegion);

UBOOL8 dai_sysGetnetFirstSetRegion();

int dai_sysSetAgreeCollectTC(UBOOL8 agree);

UBOOL8 dai_sysGetAgreeCollectTC();

int dai_sysSetNetWizardState(NET_WIZARD_STATE_E state);

NET_WIZARD_STATE_E dai_sysGetNetWizardState();

int dai_sysSetRegisterFlag(UBOOL8 state);

UBOOL8 dai_sysGetRegisterFlag();

int dai_sysGetRebootTime();

int dai_sysGetHostName(char *devName, int len);

int dai_sysSetHostName(char *devName);

int dai_sysGetProductFamily(char *model, int len);

int dai_sysGetSoapVersion(char *soapVer, int len);

int dai_sysGetSoapLoginMethod(char *soapLoginMethod, int len);

void dai_sysReboot(DAI_REBOOT reboot, int delay);

int dai_setAfuFlag(DAI_AFU_FLAG_E afuFlag);

DAI_AFU_FLAG_E dai_getAfuFlag();

UBOOL8 dai_getProdFirmwareFlag();

int dai_setFwLastUpateTime(char *upateTime);

int dai_getFwLastUpateTime(char *upateTime, int len);

int dai_setFwLastCheckTime(char *checkTime);

int dai_getFwLastCheckTime(char *checkTime, int len);

int dai_setLastFwAvailabilityCheckTime();

int dai_getLastFwAvailabilityCheckTime(char *checkTime, int len);

int dai_setFwLastAutoUpgradeTime(char *upgradeTime);

int dai_getFwLastAutoUpgradeTime(char *upgradeTime, int len);

int dai_setFwEventType(char *eventType);

int dai_getFwEventType(char *eventType, int len);

int dai_setFwUpgradeTriggerStatus(char *trigger);

int dai_getFwUpgradeTriggerStatus(char *trigger, int len);

int dai_getFwDownloadUrl(char *url, int len);

int dai_setFwConfigSetting(char *setting);

int dai_getFwConfigSetting(char *setting, int len);

int dai_setFwCurrentVersion(char *version);

int dai_getFwCurrentVersion(char *version, int len);

int dai_setFwNewVersion(char *version);

int dai_getFwNewVersion(char *version, int len);

int dai_setFwCheckResult(char *result);

int dai_getFwCheckResult(char *result, int len);

int dai_setFwUpgradeMethod(char *fwUpgradeMethod);

int dai_getFwUpgradeMethod(char *fwUpgradeMethod, int len);

int dai_setFwUpgradeLog(char *log);

int dai_getFwUpgradeLog(char *log, int len);

int dai_setFwUpgRebootFlag(UBOOL8 rebootFlag);

int dai_getFwUpgRebootFlag(char *rebootFlag, int len);

int dai_setAutoUpgrade(UBOOL8 enable);

int dai_getAutoUpgrade(char *enable, int len);

int dai_setFwUpgradeLatest(UBOOL8 fwUpgradeLatest);

int dai_setPopupFlag(UBOOL8 enable);

int dai_getPopupFlag(char *enable, int len);

int dai_setFotaParametersChangeFlag(UBOOL8 changeFlag);

int dai_getFotaParametersChangeFlag(char *changeFlag, int len);

int dai_getNewFwReleaseDate(char *date, int len);

UBOOL8 dai_isHaveNewFwVersion();

void dai_getNewSwExStatus(UINT32 *pdwStatus, UINT32 *pdwCheckTime);

void dai_getNewSwExVerion(char *varValue);

void dai_getUpgradeInfo(char *varValue);

int dai_getDlPercent(char *percent);

int dai_checkImage(void);

int dai_decryptImage(void);

int dai_cleanupSysMem(void);

int tbsMatch(const char *pszString, const char *pszPattern);

int dai_sysSetDefaultRegion(char *region);

int dai_sysGetDefaultRegion(char *region, int regionLen);

int dai_sysSetDebugBootUpEnable(UBOOL8 enable);

UBOOL8 dai_sysGetDebugBootUpEnable();

int dai_sysSetCollectDebugEnable(UBOOL8 enable);

UBOOL8 dai_sysGetCollectDebugEnable();

int dai_sysSetWanLanCaptureEnable(UBOOL8 enable);

UBOOL8 dai_sysGetWanLanCaptureEnable();

int dai_sysCollectDebugLog();

int dai_sysSetTelnetEnable(UBOOL8 enable);

UBOOL8 dai_sysGetTelnetEnable();

int dai_sysSetCliEnable(UBOOL8 enable);

int dai_sysGetCliEnable(char *status, int len);

int dai_sysSetSshEnable(UBOOL8 enable);

int dai_sysGetSshEnable(char *status, int len);

int dai_sysSetWanMirrorToLanPort1(UBOOL8 enable);

UBOOL8 dai_sysGetMirrorEnable();

unsigned int dai_calcSingleByteCrc32(char data, unsigned int preCrc);

int dai_sysGetFirmwareUpgStatus();

int dai_sysSetFirmwareUpgStatus(char *upgradeStatus);

int dai_sysGetFirmwareMd5CheckStatus();

int dai_sysSetFirmwareMd5CheckStatus(char *md5CheckStatus);

int dai_sysGetFirmwareImgStatus();

int dai_sysSetFirmwareImgStatus(char *imageStatus);

/**
 * @brief Create or return a rediscontext
 * 
 * @return redisContext* 
 */
redisContext* dai_redisConnectInit();

/**
 * Release the context for DAI_REDISXXX.
 * Note: Redis context should be reused throughout the service life cycle.
*/
int dai_redisFree();

/**
 * CMD> GET key
 * @param key redis key
 * @param value value
 * @param len  vaule length
*/
int dai_redisGet(char *key, char *value, int len);

/**
 * CMD> SET key value
 * CMD> EXPIRE key seconds
 * @param key redis key
 * @param value value
 * @param timeout timeout
*/
int dai_redisSet(char *key, char *value, int timeout);

/**
 * CMD> DEL key
 * @param key redis key
*/
int dai_redisDelete(char *key);

/**
 * CMD> HMGET key filed [field ...]
 * @param num        -- field num
 * @param fieldTable -- field, need to free the value.
 * @param key        -- redis key
 * @param ...        -- the other fields
*/
int dai_redisHmget(int num, REDIS_FIELD_ELEMENT_T *fieldTable, char *key, ...);

/**
 * Free the field value
 * @param num        -- field num
 * @param fieldTable -- field, need to free the value.
*/
void dai_redisFreeField(int num, REDIS_FIELD_ELEMENT_T *fieldTable);

/**
 * CMD> HMSET key filed value [field value ...]
 * @param num        -- (field, value) num
 * @param key        -- redis key
*/
int dai_redisHmset(int num, char *key, ...);

/**
 * CMD> HDEL key filed [field ...]
 * @param num        -- field num
 * @param key        -- redis key
*/
int dai_redisHdel(int num, char *key, ...);

/**
 * CMD> LPUSH key element
*/
int dai_redisPushList(char *key, char *value);

/**
 * CMD> LLEN key
*/
int dai_redisGetListLen(char *key, int *len);

/**
 * CMD> LRANGE key start stop
 * @param buf_ext_len   -- alloc ext memory size
*/
int dai_redisGetListRange(char *key, char **array, int array_size, int start, int stop, int buf_ext_len);

/**
 * CMD> LSET key index element
*/
int dai_redisListSet(char *key, int index, char *value);

/**
 * CMD> LTRIM key start stop
*/
int dai_redisListTrim(char *key, int start, int stop);

/**
 * CMD> MULTI
*/
int dai_redisMulti();

/**
 * CMD> EXEC
*/
int dai_redisExec();

int dai_sysGetSsoRegistrationStatus(char *ssoRegStatus, int len);
int dai_getNetMode(char *mode, int len);
int dai_setNetMode(char *mode);
int dai_updateNetMode(char *mode);
DAI_NETMODE_T dai_getNetModeE(void);
uint8_t dai_getUnDevEnable(void);
int dai_sysSetHijackConfigStatus(char *status);
int dai_sysGetHijackConfigStatus(char *status, int len);
UBOOL8 dai_sysGetHijackLanguageEnable();
int dai_sysSetHijackLanguageEnable(UBOOL8 enabled);
int dai_sysGetHijackRefreshCounter(int *counter, int increase);
int dai_sysSetHijackRefreshCounter(int counter);
int dai_sysSetFromNowanRetry(char *val);
int dai_sysGetFromNowanRetry(int *val);
int dai_sysSetFromSetting(char *val);
int dai_sysGetFromSetting(int *val);
int dai_sysGetPasswdTryTimes(int tryPasswd);
int dai_sysSetPasswdTryTimes(char *times);
int dai_sysGetEnterSnAgain();
int dai_sysSetEnterSnAgain(char *times);
int dai_sysGetEnterAnswerAgain();
int dai_sysSetEnterAnswerAgain(char *times);
int dai_sysGetLastErrorAns(int num, char *ans, int len);
int dai_sysSetLastErrorAns(int num, char *ans);
int dai_sysGetPasswdRecoveryTime(char *recoveryTime, int len);
int dai_sysSetPasswdRecoveryTime(char *recoveryTime);
int dai_sysGetPasswdRecoveryEnable(char *recoveryEnable, int len);
int dai_sysSetPasswdRecoveryEnable(UBOOL8 enable);
int dai_sysGetNetportStatsRefreshTime(char *refreshTime, int len);
int dai_sysSetNetportStatsRefreshTime(char *refreshTime);
int dai_sysSetLogsMask(LOGS_MASK_T mask);
UBOOL8 dai_sysGetLogModelEnabled(LOG_MODULE_E mode);
int dai_sysSaveLog(LOG_MODULE_E model, const char *format, ...);
int dai_sysGetLog(char **array, int array_size);
int dai_sysGetSysInitLog(char *log, int size);
UBOOL8 dai_isLoginWebFromLanSide(char *accessIp);
int dai_sysSetEmailNotiCfg(EMAIL_NOTI_CFG_T *pEmailNotiCfg);
int dai_sysSetEmailAlertCfg(EMAIL_ALERT_CFG_T *pEmailAlertCfg);
int dai_sysGetEmailAlertCfg(EMAIL_ALERT_CFG_T *pEmailAlertCfg);
int dai_sysGetEmailCfg(EMAIL_NOTI_CFG_T *pEmailNotiCfg);
int dai_sysGetEmailPasswd(char *passwd, int len);
void dai_sysEmailLogSetup();
void dai_sysSetRemoteManageCfg(void *data);
int dai_sysGetRemoteManageCfg(HTTPS_REMOTE_CFG_T *pRemoteCfg);
int dai_redisGetKeys(char *key, char **array, int array_size, int buf_ext_len);
void dai_stringHashSha256(char *in,  char *out);
int dai_sysGetIfStatistics(const char *devName, DAI_DEV_STATISTICS *statistics);
/**
 * Gets the MTD device path corresponding to the partition name
 * @param partitionName The partition name
 * @param mtdPath Returns the MTD device path for the partition
 * @param len mtdPath buf len
 * @return Returns 0 on success, -1 on other cases
*/
int dai_getMtdDevPath(const char* partitionName, char *mtdPath, size_t len);

/**
 * Gets the length of the partition
 * @param partitionName The partition name
 * @return Length of the partition. Returns 0 on failure
*/
UINT32 dai_getMtdSize(const char* partitionName);

/**
 * Check the validity of the string table.
 * @param langTable Contains language table information and data
 * @return Return TRUE or False
*/
UBOOL8 dai_sysCheckLanguageTable(const DAI_LANGUAGE_PARTITION_T* langTable);

/**
 * Writes information and data from the language table to the specified sector of the language partition.
 * @param langTable Contains language table information and data
 * @param partIdx Sector index of a language table.
 * @return Returns 0 on success, -1 on other cases
*/
int dai_writeLanguageTable(const DAI_LANGUAGE_PARTITION_T* langTable, UINT8 partIdx);

/**
 * Writes language table data to the rotating language sector.
 * @param langTable Contains language table information and data
 * @return Returns 0 on success, -1 on other cases
*/
int dai_writeRotationLanguageTable(const DAI_LANGUAGE_PARTITION_T* langTable);

/**
 * Reads the contents of the specified sector of the language partition
 * @param langTable A secondary pointer, whose value, if successful, points to partitioned table information.Release after use
 * @param partIdx Sector index of a language table.
 * @return Returns 0 on success, -1 on other cases
*/
int dai_readLanguageTable(DAI_LANGUAGE_PARTITION_T** langTable, UINT8 partIdx);

/**
 * Reads the rotational sector information for the language partition table
 * @param langTable A secondary pointer, whose value, if successful, points to partitioned table information.Release after use
 * @return Returns 0 on success, -1 on other cases
*/
int dai_readRotationLanguageTable(DAI_LANGUAGE_PARTITION_T** langTable);

/**
 * Gets the next matched language table.
 * If not found.Both LangTable and Context are automatically released and return NULL.
 * Usually you do not need to release these two parameters manually, triggering an exit during the traversal, which must be released via VOS_FREE
 * @param name Full name of the language table
 * @param context The context of the search process is automatically released when the next language table cannot be found.Otherwise, you need to release it manually. Its structure may send changes, but an int at the beginning always stands for IDX
 * @param langTable The language table found is automatically released when the next language table cannot be found. Otherwise, manual release is required
 * 
 * @return Returns 0 on success, -1 on error. 
 * 
*/
int dai_getNextLanguageTable(const char* name, DAI_GET_LANG_TABLE_CONTEXT_T** context, DAI_LANGUAGE_PARTITION_T** langTable);
/**
 * Create a backup file
 * @param path The location of the backup file
*/
int dai_sysCreateBackup(const char* path);

/**
 * Apply configuration backup file
 * @param path The location of the backup file
*/
int dai_sysRestoreBackup(const char* path);

/**
 * reset default
*/
int dai_sysResetDefault();

/**
 * for netMode bridge to uplink apcli (0:2g 1:5g 2:all)
*/
int dai_getNetMode_Wds(int *clientMode);

/**
 * for netMode bridge to uplink apcli (0:2g 1:5g 2:all)
*/
int dai_setNetMode_Wds(int clientMode);

void dai_gpioInit(UINT32 gpioNum);
int dai_getStaCountINFO(const char *ifName, RT_802_11_COUNT_INFO *staTable);
int dai_getStaInfo(const char *ifName, RT_802_11_MAC_TABLE *staTable);
void dai_setGpioDirection(const char* direction, UINT32 gpioNum);
UBOOL8 dai_checkPoePlus();
UBOOL8 dai_checkAdaptor();
void dai_unExportGpio(UINT32 gpioNum);
int dai_sendLldpPacket();
int dai_setLldpTxRxMode(UBOOL8 txEnable, UBOOL8 rxEnable);
VOS_RET_E dai_catFile(UBOOL8 reverse, const char *fileName, char *catResult, UINT32 catSize);
int dai_getFileSize(const char *fileName);
int dai_needEscapeForPing();
void dai_sysGetEthLinkChange(UINT32 gpioNum, int *gpioValue);
int dai_setNetLed(char *colour, int mode);
UBOOL8 dai_sysFunctionSupport(const char *functionSting);
int dai_sysGetGpio(const char *gpioName);
int dai_setPowerType(POWER_TYPE_E type);
int dai_getPowerType(POWER_TYPE_E *type);
int dai_sysSetAllLed(UBOOL8 on);
int dai_sysSetSignleLed(UBOOL8 on, char *name, char *colour);
int dai_checkProcessVoslogAccessByEid(VosEntityId eid);
int dai_checkProcessVoslogAccessByName(const char *name);
int dai_sysGetLogLevelByEid(VosEntityId eid, VosLogLevel *level);
int dai_sysGetLogDestByEid(VosEntityId eid, VosLogDestination *destination);
int dai_sysGetLogLevelByName(const char *name, VosLogLevel *level);
int dai_sysGetLogDestByName(const char *name, VosLogDestination *destination);
int dai_sysSetLogLevelByName(const char *name, VosLogLevel level);
int dai_sysSetLogDestByName(const char *name, VosLogDestination destination);
int dai_sysRestartProcess(const char *name);
int dai_logInit(VosEntityId eid);
int dai_updateLogLevelAndDestFromConfig(VosEntityId eid);
int dai_setLedInfo(UBOOL8 power, UBOOL8 other);
int dai_getLedInfo(UBOOL8 *power, UBOOL8 *other);
int dai_sysGetVoslogSupportProcess(char *process, int processLen);


#endif /* __SYSTEM_H__ */
