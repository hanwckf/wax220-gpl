#ifndef __FOTA_H__
#define __FOTA_H__

#include "fota_debug.h"
#include "fota_common.h"


#define FOTA_CONFIG_FILE "/tmp/fota.cfg"
#define TMP_FW "/tmp/fota_firmware.img"
#define TMP_RELEASE_DATE_FILE "/tmp/release_date"

#define DEFAULT_CONNECT_TIMEOUT 15

enum fota_progress_type
{
    /* Update the progress by percentage */
    PROGRESS_TYPE_PERCENT = 1,
    /* Update the progress by time */
    PROGRESS_TYPE_TIME
};

enum fota_msg_type
{
    CMS_MSG_FOTA_UPG_AUTO                 = 0x1,  /* auto upgrade fw online */
    CMS_MSG_FOTA_UPG_MANUAL_QUERY         = 0x2,  /* manual upgrade, query fw info */
    CMS_MSG_FOTA_UPG_MANUAL_DOWNLOAD      = 0x3,  /* manual upgrade, download fw */
    CMS_MSG_FOTA_UPG_MANUAL_UPGRADE       = 0x4,  /* manual upgrade, upgrade fw */
    CMS_MSG_FOTA_UPG_MANUAL_CANCLE        = 0x5,  /* manual upgrade, cancle upgrade fw */
    CMS_MSG_FOTA_SOAP_CHECK_NEW_FW        = 0x6,  /* soap check new firmware and download */
    CMS_MSG_FOTA_SOAP_UPGRADE_NEW_FW_YES  = 0x7,  /* soap update new firmware enable */
    CMS_MSG_FOTA_SOAP_UPGRADE_NEW_FW_NO   = 0x8,  /* soap update new firmware disable */
    CMS_MSG_FOTA_UPG_INFO_NOTICE          = 0x9,  /* tell other module that upgrade info changes */
    CMS_MSG_FOTA_UPG_REBOOT_NOTICE        = 0xA,  /* tell other module that upgrade reboot occurs */
};

struct fota_progress_measure
{
    enum fota_progress_type iType;
    /* 
      * Update the progress by per 'iPercent' percentage,
      * used by 'percentage' method
    */
    int iPercent;
    /*
      * Update the progress by per 'iInterval' seconds,
      * used by 'time' method
    */
    int iInterval;
    /* Real-time progress output */
    FILE * pProgress;
};

struct fota_progress_config
{
    char * pProgress_file;
    int iProgress_type;
    int iProgress_percent;
    int iProgress_time;
};

struct fota_fw_info
{
    char * pUrl;
    char * pChecksum;
    char * pRelease_note;
    /*
      * Unix timestamp: the number of seconds since the Epoch,
      * 1970-01-01 00:00:00 +0000 (UTC).
    */
    long iSeconds;
    int iExist;
    struct version fw_version;
};

struct fota_upgrade_config
{
    int iEvent_notification_enable;
    int iUpgrade_notification_enable;
    int iAuto_query_enable;
    int iAuto_download_enable;
    int iAuto_update_enable;
    int iBeta_fw_enable;
};

struct fota_config
{
    char * pConfig_file;
    char * pPid_file;
    char * pAction;
    char * pCacert;
    char * pFw_url;
    char * pFw_path;
    int iFw_encrypt_flag;
    int iDaemonize;
    int iEnable_stdio;
    int iHelp;
    int iVerbose;
    int iConnect_timeout;
    struct fota_progress_config progress_config;
    struct fota_upgrade_config upgrade_config;
    struct fota_client_info client_info;
};

#define CONSTRUCT_FOTA_UPGRADE_OPTION(config_option, pUpgrade_config) \
struct fota_option config_option[] = \
{ \
    /* configuration of upgrade */ \
\
    {"event-notification-enable", OPTION_TYPE_INT, \
        &pUpgrade_config->iEvent_notification_enable, \
        NULL}, \
    {"auto-update-notification-enable", OPTION_TYPE_INT, \
        &pUpgrade_config->iUpgrade_notification_enable, \
        NULL}, \
    {"auto-query-enable", OPTION_TYPE_INT, \
        &pUpgrade_config->iAuto_query_enable, \
        NULL}, \
    {"auto-download-enable", OPTION_TYPE_INT, \
        &pUpgrade_config->iAuto_download_enable, \
        NULL}, \
    {"auto-update-enable", OPTION_TYPE_INT, \
        &pUpgrade_config->iAuto_update_enable, \
        NULL}, \
    {"beta-firmware-enable", OPTION_TYPE_INT, \
        &pUpgrade_config->iBeta_fw_enable, \
        NULL}, \
    {NULL, 0, NULL, NULL, 0} \
}

#define fotaMem_free(ptr) \
    do { \
        free(ptr); \
        (ptr) = NULL; \
    } while(0);

#define fotaMem_malloc(ptr, type, size) \
    do { \
        (ptr) = (type)malloc(size); \
        if (!ptr) \
            vosLog_error("Failed to allocate memory of length %d.", size); \
    } while(0);

#endif

