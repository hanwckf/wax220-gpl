#ifndef __UTIL_IMAGE_H__
#define __UTIL_IMAGE_H__


/** Minimum size for image uploads.
 *  Config file uploads can be less than 2K.
 */
#define  VOS_IMAGE_MIN_LEN    2048

/** Safety margin to use when determining if an image will fit into the flash.
 */
#define  VOS_IMAGE_OVERHEAD          256

/** Minimum length needed to detect if a buffer could be a config file.
 */
#define VOS_CONFIG_FILE_DETECTION_LENGTH 64



/*!\enum CmsImageFormat
 * \brief cms image formats that we recognize.
 */
 
typedef enum
{
	VOS_FLASH_PARTITION_NONE,
    VOS_FLASH_PARTITION_BOOT,
    VOS_FLASH_PARTITION_IMAGE,
    VOS_FLASH_PARTITION_WHOLE,
} VOS_IAMGE_FORMAT;


void vosImg_sendLoadStartingMsg(void *msgHandle, const char *connIfName);

void vosImg_sendLoadDoneMsg(void *msgHandle);

void util_saveLogToFlash(void *msgHandle);

UBOOL8 vosImg_isConfigFileLikely(const char *buf);

VOS_RET_E cmc_sysSaveIfNameFromSocket(SINT32 socketfd, char *connIfName);

UBOOL8 vosImg_isAppRunning(void *msgHandle, VosEntityId eid);
const char *vosImg_getSoftFeatureCfg(void);
const char *vosImg_getVarSoftFeatureCfg(void);
const char *vosImg_getFactoryCfg(void);
const char *vosImg_getDefaultCfg(void);
const char *vosImg_getVarDefaultCfg(void);


#endif  /* __UTIL_IMAGE_H__ */
