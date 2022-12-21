#ifndef __LOG_H__
#define __LOG_H__
#include "fwk/fwk.h"

#define LOGREAD_RESULT_FILE "/tmp/sysLogread"

typedef struct
{
    char enable[BUFLEN_16];
    char logType[BUFLEN_16];
    char remoteEnable[BUFLEN_16];
    char trafficEnable[BUFLEN_16];
    char remoteIp[BUFLEN_16];
    char remotePort[BUFLEN_16];
} DAI_LOG_CFG_T;

VOS_RET_E dai_getLogCfg(DAI_LOG_CFG_T *logCfg);

VOS_RET_E dai_setLogCfg(DAI_LOG_CFG_T logCfg);

VOS_RET_E dai_doLogread(UINT32 type, UBOOL8 isComplete);

VOS_RET_E dai_doClearSystemLog();

VOS_RET_E dai_createSystemLogTargz(const char *fileName, char *path, UINT32 pathLen);

VOS_RET_E dai_trafficLogControl(UBOOL8 enable);
#endif
