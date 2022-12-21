#ifndef __FOTA_COMMON_H__
#define __FOTA_COMMON_H__

#include "fwk/fwk.h"

#define CA_CERT_FILE                    "/etc/cacert.pem"
#define ONLINE_CHECK_FINISH_FLAG        "/var/online_check_finish_flag"
#define STRINGTABLE_FLAG_LOCALPATH      "/var/release_note_flag_file"
#define STRINGTABLE_HTM_LOCALPATH       "/var/release_notes.htm"
#define STRINGTABLE_SOAP_HTM_LOCALPATH  "/etc/release_notes.htm"
#define TMP_STRINGTABLE_LOCALPATH       "/var/tmp_stringtable.dat"
#define NEW_SW_VERSION_LOCALPATH        "/tmp/fota_upg_new_version"
#define QUERY_NO_NEW_VERSION_FLAG_PATH  "/tmp/upg_no_new_version_cause"  /* 10000: No internet. 10001: No new version. 10002: Download file fail. 10003: download file incorrect */
#define TMP_PERCENT_LOCALPATH           "/tmp/percent"
#define TMP_IMG_PERCENT_LOCALPATH       "/tmp/percent_img"
#define TMP_IMG_SIZE_LOCALPATH          "/tmp/fota_img_size"
#define TMP_LANG_PERCENT_LOCALPATH      "/tmp/percent_lang"
#define FILEINFO_LOCALPATH              "/var/fileinfo.txt"
#define STRINGTABLE_LOCALPATH           "/var/stringtable.dat"
#define FOTA_LANGTABLE_LOCALPATH        "/tmp/langtable.tar.gz"
#define IMAGE_DOWNLOAD_STATUS           "/var/image_download_status"  /* 0: success. 1: download fw fail. 2: download fw incorrect. */
#define IMAGE_DECRYPT_TEMP_LOCALPATH    "/var/image_decrypt_temp.bin"
#define IMAGE_DECRYPT_LOCALPATH         "/var/image_decrypt.bin"

#define FOTA_NEW_LANG_VER_REDIS_KEY          "FOTA::UPG_NEW_LANG_VERSION"
#define FOTA_EACH_POWER_CYCLE_UPG_FLAG       "FOTA::EACH_POWER_CYCLE_UPG_FLAG"

#define UNREGISTERED 0
#define REGISTERED 1
#define FOTA_QUERY_LIMITS  3
#define CURLINFO_RESPONSE_CODE_200 200  /*HTTPS返回有效*/
#define CURLINFO_RESPONSE_CODE_226 226  /*FTP返回有效*/

#define FREE_POINTER(p) \
    if (p) \
    { \
        free(p); \
        p = NULL; \
    }

extern int iVerbose;
extern char * pCacert;
extern int iConnect_timeout;

struct fota_message
{
    const char * pMsg_code;
    const char * pMsg_message;
    const char * pMsg_description;
};

struct DID
{
    char * pDevice_id;
};

struct version
{
    char sMajor[BUFLEN_8];
    char sMinor[BUFLEN_8];
    char sRevision[BUFLEN_8];
};

struct fota_client_info
{
    char sModel_name[BUFLEN_32];
    char sSeries_name[BUFLEN_32];
    char sHardware_version[BUFLEN_32];
    char sGrant_type[BUFLEN_32];
    char sUser_name[BUFLEN_32];
    char sLanguage[BUFLEN_32];
    char sServer_domain[BUFLEN_128];
    char sNtp_server[BUFLEN_128];
    char sTZ_location[BUFLEN_128];
    char * pClient_id;
    char * pClient_secret;
    char * pRefresh_token;
    char * pAccess_token;
    char * pFw_variant;
    int iNtp_enable;
    long iLifetime_of_access_token;
    long iReference_time;
    struct DID password;
    struct version fw_version;
};


struct fota_client_info_2
{
    char sSeries_name[BUFLEN_32];
    char sModel_name[BUFLEN_32];
    char sHardware_version[BUFLEN_32];
    char sFw_variant[BUFLEN_32];
    char sLanguage[BUFLEN_32];
    char sServer_domain[BUFLEN_128];
    struct version fw_version;
};

enum http_chunk_type
{
    /* save http data to dynamic memory */
    CHUNK_TYPE_MEM = 1,
    /* save http data to file */
    CHUNK_TYPE_FILE
};

struct http_chunk
{
    enum http_chunk_type iType;
    int iStatus_code;
    size_t iSize;
    void * pData;
};

enum fota_option_type
{
    OPTION_TYPE_STRING,
    OPTION_TYPE_INT,
    OPTION_TYPE_STRING2,
    OPTION_TYPE_FILE,
    OPTION_TYPE_MAX
};

struct fota_option
{
    const char * pName;
    enum fota_option_type iType;
    void * pAddr;
    void * * pAddr2;
    size_t iBuf_len;
};

#define CONSTRUCT_FOTA_CLIENT_OPTION(config_option, pClient_config) \
struct fota_option config_option[] = \
{ \
    /* configuration of fota client */ \
\
    {"factory-mac", OPTION_TYPE_STRING, \
        pClient_config->sUser_name, \
        NULL, sizeof (pClient_config->sUser_name)}, \
    {"model-name", OPTION_TYPE_STRING, \
        pClient_config->sModel_name, \
        NULL, sizeof (pClient_config->sModel_name)}, \
    {"language", OPTION_TYPE_STRING, \
        pClient_config->sLanguage, \
        NULL, sizeof (pClient_config->sLanguage)}, \
    {"server-domain", OPTION_TYPE_STRING, \
        pClient_config->sServer_domain, \
        NULL, sizeof (pClient_config->sServer_domain)}, \
    {"ntp-enable", OPTION_TYPE_INT, \
        &pClient_config->iNtp_enable, \
        NULL}, \
    {"ntp-server", OPTION_TYPE_STRING, \
        pClient_config->sNtp_server, \
        NULL, sizeof (pClient_config->sNtp_server)}, \
    {"TZ-location", OPTION_TYPE_STRING, \
        pClient_config->sTZ_location, \
        NULL, sizeof (pClient_config->sTZ_location)}, \
    {"client-id", OPTION_TYPE_STRING2, NULL, \
        (void * *)&pClient_config->pClient_id}, \
    {"client-secret", OPTION_TYPE_STRING2, NULL, \
        (void * *)&pClient_config->pClient_secret}, \
    {"refresh-token", OPTION_TYPE_FILE, NULL, \
        (void * *)&pClient_config->pRefresh_token}, \
    {"access-token", OPTION_TYPE_FILE, NULL, \
        (void * *)&pClient_config->pAccess_token}, \
    {"fw-variant", OPTION_TYPE_STRING2, NULL, \
        (void * *)&pClient_config->pFw_variant}, \
    {"device-id", OPTION_TYPE_STRING2, NULL, \
        (void * *)&pClient_config->password.pDevice_id}, \
    {"fw-major-version", OPTION_TYPE_STRING, \
        pClient_config->fw_version.sMajor, \
        NULL, sizeof (pClient_config->fw_version.sMajor)}, \
    {"fw-minor-version", OPTION_TYPE_STRING, \
        pClient_config->fw_version.sMinor, \
        NULL, sizeof (pClient_config->fw_version.sMinor)}, \
    {"fw-revision-version", OPTION_TYPE_STRING, \
        pClient_config->fw_version.sRevision, \
        NULL, sizeof (pClient_config->fw_version.sRevision)}, \
\
    /* configuration only for unencrypted firmware */ \
\
    {"series-name", OPTION_TYPE_STRING, \
        pClient_config->sSeries_name, \
        NULL, sizeof (pClient_config->sSeries_name)}, \
    {"hardware-version", OPTION_TYPE_STRING, \
        pClient_config->sHardware_version, \
        NULL, sizeof (pClient_config->sHardware_version)}, \
    {NULL, 0, NULL, NULL, 0} \
}

int fota_get_file_content(const char * pFile_name,
                            void * * pBuf_addr,
                            size_t * iLen);

int execute_pause(int iSeconds);

int get_http_response_code(int * pCode,
                            struct http_chunk * pHttp_header);

size_t handle_recv_data(void * pPtr,
                            size_t iSize,
                            size_t iNmemb,
                            void * pUser_info);

int fota_parse_config_file(
                        const char * pConfig_file,
                        struct fota_option * pConfig);
int free_device_info(struct fota_client_info * pDevice_info);


#endif

