#ifndef __FOTA_NETGEAR_H__
#define __FOTA_NETGEAR_H__

typedef enum _FOTA_ACTION_TYPE{
    FOTA_AUTO_CHECK_DOWNLOAD_UPGRADE,
    FOTA_SOAP_CHECK_NEW_VERSION,
    FOTA_SOAP_DOWNLOAD_UPGRADE_IMAGE,
    FOTA_MANUAL_CHECK_NEW_VERSION,
    FOTA_MANUAL_DOWNLOAD_IMAGE,
    FOTA_MANUAL_UPGRADE_IMAGE,
    FOTA_MAX
}FOTA_ACTION_TYPE;

typedef struct
{
    int minute;           /* minutes: 0 - 59 */
    int hour;             /* hours:   0 - 23 */
    int weekday;          /* day of the month: 0 - 6 */
} FOTA_UPG_TIMESTAMP;

typedef struct
{
    char flag;
    uint8_t ver;
    char tag[16];
} FOTA_RELEASE_NOTE_INFO_T;

typedef struct
{
    uint16_t num;
    FOTA_RELEASE_NOTE_INFO_T array[0];
} FOTA_RELEASE_NOTE_ARRAY_T;
typedef struct
{
    char sectionName[64];
    char file[64];
    char md5[33];
    size_t size;
    void* data;
} FOTA_FILE_INFO_SECTION_T;
typedef struct
{
    uint16_t majorNum;
    uint16_t languageTableNum;
    FOTA_FILE_INFO_SECTION_T section[0];
} FOTA_FILE_INFO_T;


void removeAllLocalFile(void);
int clear_firmware(const char * pFw_name);
int change_led_color(void);
int save_firmware_to_flash(const char * pFw_name);
void NTGR_FwUpgradeMachine_HTTPS(FOTA_ACTION_TYPE action);
void NTGR_AutoUpgDeal(void);
void NTGR_FotaUpgInfoInit(void);

#endif

