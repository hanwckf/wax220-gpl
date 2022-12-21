#ifndef __WPS_H__
#define __WPS_H__
#include "fwk/fwk.h"

#define WPS_CLIENT_NAME_FILE "/tmp/wps_client_name"
#define WPS_CLIENT_MACADDR_FILE "/tmp/wps_client_macaddr"

/*============================mt_wifi wsc.h Start copying===========================================*/
/* Wsc status code */
#define	STATUS_WSC_NOTUSED						0
#define	STATUS_WSC_IDLE							1
#define STATUS_WSC_FAIL							2		/* WSC Process Fail */
#define	STATUS_WSC_LINK_UP						3		/* Start WSC Process */
#define	STATUS_WSC_EAPOL_START_RECEIVED			4		/* Received EAPOL-Start */
#define	STATUS_WSC_EAP_REQ_ID_SENT				5		/* Sending EAP-Req(ID) */
#define	STATUS_WSC_EAP_RSP_ID_RECEIVED			6		/* Receive EAP-Rsp(ID) */
#define	STATUS_WSC_EAP_RSP_WRONG_SMI			7		/* Receive EAP-Req with wrong WSC SMI Vendor Id */
#define	STATUS_WSC_EAP_RSP_WRONG_VENDOR_TYPE	8		/* Receive EAPReq with wrong WSC Vendor Type */
#define	STATUS_WSC_EAP_REQ_WSC_START			9		/* Sending EAP-Req(WSC_START) */
#define	STATUS_WSC_EAP_M1_SENT					10		/* Send M1 */
#define	STATUS_WSC_EAP_M1_RECEIVED				11		/* Received M1 */
#define	STATUS_WSC_EAP_M2_SENT					12		/* Send M2 */
#define	STATUS_WSC_EAP_M2_RECEIVED				13		/* Received M2 */
#define	STATUS_WSC_EAP_M2D_RECEIVED				14		/* Received M2D */
#define	STATUS_WSC_EAP_M3_SENT					15		/* Send M3 */
#define	STATUS_WSC_EAP_M3_RECEIVED				16		/* Received M3 */
#define	STATUS_WSC_EAP_M4_SENT					17		/* Send M4 */
#define	STATUS_WSC_EAP_M4_RECEIVED				18		/* Received M4 */
#define	STATUS_WSC_EAP_M5_SENT					19		/* Send M5 */
#define	STATUS_WSC_EAP_M5_RECEIVED				20		/* Received M5 */
#define	STATUS_WSC_EAP_M6_SENT					21		/* Send M6 */
#define	STATUS_WSC_EAP_M6_RECEIVED				22		/* Received M6 */
#define	STATUS_WSC_EAP_M7_SENT					23		/* Send M7 */
#define	STATUS_WSC_EAP_M7_RECEIVED				24		/* Received M7 */
#define	STATUS_WSC_EAP_M8_SENT					25		/* Send M8 */
#define	STATUS_WSC_EAP_M8_RECEIVED				26		/* Received M8 */
#define	STATUS_WSC_EAP_RAP_RSP_ACK				27		/* Processing EAP Response (ACK) */
#define	STATUS_WSC_EAP_RAP_REQ_DONE_SENT		28		/* Processing EAP Request (Done) */
#define	STATUS_WSC_EAP_RAP_RSP_DONE_SENT		29		/* Processing EAP Response (Done) */
#define STATUS_WSC_EAP_FAIL_SENT                30      /* Sending EAP-Fail */
#define STATUS_WSC_ERROR_HASH_FAIL              31      /* WSC_ERROR_HASH_FAIL */
#define STATUS_WSC_ERROR_HMAC_FAIL              32      /* WSC_ERROR_HMAC_FAIL */
#define STATUS_WSC_ERROR_DEV_PWD_AUTH_FAIL      33      /* WSC_ERROR_DEV_PWD_AUTH_FAIL */
#define STATUS_WSC_CONFIGURED					34
#define	STATUS_WSC_SCAN_AP						35		/* Scanning AP */
#define	STATUS_WSC_EAPOL_START_SENT				36
#define STATUS_WSC_EAP_RSP_DONE_SENT			37
#define STATUS_WSC_WAIT_PIN_CODE                38
#define STATUS_WSC_START_ASSOC					39
#define STATUS_WSC_IBSS_WAIT_NEXT_SMPBC_ENROLLEE	40
#define STATUS_WSC_IBSS_NEW_RANDOM_PIN			41
#define STATUS_WSC_IBSS_FIXED_PIN				42

/* All error message dtarting from 0x0100 */
#define	STATUS_WSC_PBC_TOO_MANY_AP				0x0101		/* Too many PBC AP avaliable */
#define	STATUS_WSC_PBC_NO_AP					0x0102		/* No PBC AP avaliable */
#define	STATUS_WSC_EAP_FAIL_RECEIVED			0x0103		/* Received EAP-FAIL */
#define	STATUS_WSC_EAP_NONCE_MISMATCH			0x0104		/* Receive EAP with wrong NONCE */
#define	STATUS_WSC_EAP_INVALID_DATA				0x0105		/* Receive EAP without integrity (Hmac mismatch) */
#define STATUS_WSC_PASSWORD_MISMATCH			0x0106		/* Error PIN Code (R-Hash mismatch) */
#define	STATUS_WSC_EAP_REQ_WRONG_SMI			0x0107		/* Receive EAP-Req with wrong WPS SMI Vendor Id */
#define	STATUS_WSC_EAP_REQ_WRONG_VENDOR_TYPE	0x0108		/* Receive EAPReq with wrong WPS Vendor Type */
#define	STATUS_WSC_PBC_SESSION_OVERLAP			0x0109		/* AP PBC session overlap */
#define	STATUS_WSC_SMPBC_TOO_MANY_REGISTRAR		0x010a		/* Too many SMPBC Registrars avaliable */
#define STATUS_WSC_EMPTY_IPV4_SUBMASK_LIST		0x010b		/* Empty available IPv4 Submask list */
#define	STATUS_WSC_SMPBC_NO_AP					0x010c		/* No SMPBC AP avaliable */
/*===============================Finish copying========================================*/

typedef enum
{
    HAL_WLAN_WPS_SETUP_METHOD_PBC,
    HAL_WLAN_WPS_SETUP_METHOD_PEER_PIN,/*sta pin*/
    HAL_WLAN_WPS_SETUP_METHOD_LOCAL_PIN,/*ap pin*/
    HAL_WLAN_WPS_SETUP_METHOD_DISABLED = 255
} HAL_WLAN_WPS_SETUP_METHOD_E;

typedef struct{
    char ifName[BUFLEN_16];
    char pinNumber[BUFLEN_12];
    HAL_WLAN_WPS_SETUP_METHOD_E method;
    unsigned char needRestart;
} WPS_CONFIG_T;

/**
 * DAI API for start WPS process 
 * @param wps 
*/
void dai_wpsStartProcess(WPS_CONFIG_T *wpsConfig, SINT32 band, SINT32 wlanIdx);
void dai_wpsStopProcess(SINT32 band, SINT32 wlanIdx);
int dai_wpsGetEnable(unsigned char *wpsEnable);
void dai_wpsGetStatus(unsigned char *wpsStatus);
int dai_wpsGetClientName(char * wpsClientName, int wpsClientNameLen);
int dai_wpsSetClientName(char *wpsClientName);
void dai_wpsGetConfStatus(SINT32 band, int * wpsConfStatus);
void dai_wpsSetConfStatus(SINT32 band, int * wpsConfStatus);
int dai_wpsSetClientMacAddr(char * wpsClientMacAddr);
int dai_wpsGetClientMacAddr(char * wpsClientMacAddr, int wpsClientMacAddrLen);
void dai_wpsSyncDeviceName(char *devName);
void dai_wpsGetPinNum(char * pinNum);
void dai_porcessWpsCrdlMessage(uint8_t rfBand, unsigned short authType, unsigned short encrType, 
                               unsigned short ssidLen, unsigned char * ssid, unsigned short wpaPskLen, unsigned char * wpaPsk);
void dai_wpsSetProfile(int *wps2GConfStatus, int *wps5GConfStatus);

#endif
