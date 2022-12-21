#ifndef __UTIL_NFC_H__
#define __UTIL_NFC_H__


#define UTIL_NFC_NDEF_HEAD_LEN        4
#define UTIL_NFC_NDEF_HEAD_POS        2
#define UTIL_NFC_NDEF_TYPE_LEN_POS        3
#define UTIL_NFC_NDEF_PAYLOAD_LEN_POS     4
#define UTIL_NFC_NDEF_RECORD_TYPE_POS     5

#define UTIL_NFC_NDEF_LEN_POS    26

#define UTIL_NFC_WIFI_AUTH_MODE_LEN    6
#define UTIL_NFC_WIFI_ENCRYPT_TYPE_LEN    6

#define UTIL_NFC_RECORD_TYPE_URI    0x55
#define UTIL_NFC_RECORD_TYPE_TEXT    0x54

#define UTIL_NFC_MEM_PUSH(pos, value, len)    memcpy(pos, value, len); pos+=len;

typedef struct
{
    UINT16 ndefLen;
    UINT8 head;
    UINT8 typeLen;
    UINT8 payloadLen;
}UTIL_NFC_NDEF_HEAD_T;


typedef struct
{
    UINT16 type;
    UINT16 len;
}UTIL_NFC_WSC_DATA_T;


typedef enum
{
    UTIL_NFC_WSC_DATA_TYPE_VERSION = 0x104a,
    UTIL_NFC_WSC_DATA_TYPE_CREDENTIAL = 0x100e,
    UTIL_NFC_WSC_DATA_TYPE_NETWORK_INDEX = 0x1026,
    UTIL_NFC_WSC_DATA_TYPE_SSID = 0x1045,
    UTIL_NFC_WSC_DATA_TYPE_AUTH_MODE = 0x1003,
    UTIL_NFC_WSC_DATA_TYPE_ENCRYPT_TYPE = 0x100f,
    UTIL_NFC_WSC_DATA_TYPE_WLAN_KEY = 0x1027,
    
}UTIL_NFC_WSC_DATA_TYPE_E;


void UTIL_nfcGenWifiNdefData(const char *ssid, const char *secType, const char *encryptType, const char *wlanKey, char **value, UINT32 *len);

void UTIL_nfcGenTextNdefData(const char *text, char **value);

void UTIL_nfcGenUrlNdefData(const char *url, char **value, UINT32 *len);

void UTIL_nfcGetNdefPayload(const char *ndefAppData, char *payload, UINT32 *payloadLen, UINT8 *recordTypeLen, char *recordType);

void UTIL_nfcPrintNdefData(const char *ndefData, UINT32 len);


#endif /* __UTIL_NFC_H__ */
