#ifndef __UTIL_SRPC_H__
#define __UTIL_SRPC_H__


#include "../fwk.h"


#define SRPC_IN
#define SRPC_EXPORT(x)
#define SRPC_UNEXPORT(x)
#define SRPC_SIZE(x)
#define SRPC_MSG(x)    (SRPC_MSG_ID_##x)

#define SRPC_MAX_TASK_PARAMS_NUM    (5)


typedef struct
{
    UINT32 retCode;
} SRPC_MSG_HEADER_T;

typedef VOS_RET_E (* SRPC_SERVER_HANDLE_T)(void *msgHandle, VosMsgHeader *msg);

typedef struct
{
    UINT16 tblSize;
    SRPC_SERVER_HANDLE_T *table;
    UINT32 minMsgId;
} SRPC_SERVER_TASK_PARAMS_T;


VOS_RET_E SRPC_msgProcess(void *msgHandle, const VosMsgHeader *msg);
VOS_RET_E SRPC_setTaskParams(VosEntityId eid, const SRPC_SERVER_TASK_PARAMS_T *taskParams);


#endif /* __UTIL_SRPC_H__ */
