#ifndef __UTIL_MSG_H__
#define __UTIL_MSG_H__


#include "../fwk.h"


VOS_RET_E UTIL_sendMsg(void *msgHandle,
                                  VosEntityId eid,
                                  VosMsgType msgType,
                                  UINT32 wordData,
                                  const void *msgData,
                                  UINT32 msgDataLen);


VOS_RET_E UTIL_sendRequest(void *msgHandle,
                                  VosEntityId eid,
                                  VosMsgType msgType,
                                  UINT32 wordData,
                                  const void *msgData,
                                  UINT32 msgDataLen);


VOS_RET_E UTIL_sendEventMsg(void *msgHandle,
                                VosEntityId eid,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen,
                                UBOOL8 isEvent);


VOS_RET_E UTIL_sendRequestToSmd(void *msgHandle,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen);

VOS_RET_E UTIL_sendEventToSmd(void *msgHandle,
                              VosMsgType msgType,
                              UINT32 wordData,
                              const void *msgData,
                              UINT32 msgDataLen);

VOS_RET_E UTIL_sendHeartbeat(void *msgHandle);

VOS_RET_E UTIL_stopWatchdog(void *msgHandle);


VOS_RET_E UTIL_sendRequestToSsk(void *msgHandle,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen);

VOS_RET_E UTIL_sendEventToSsk(void *msgHandle,
                              VosMsgType msgType,
                              UINT32 wordData,
                              const void *msgData,
                              UINT32 msgDataLen);

VOS_RET_E UTIL_registerEvent(void *msgHandle,
                             VosMsgType eventType,
                             const void *matchData,
                             UINT32 matchDataLen);

VOS_RET_E UTIL_unregisterEvent(void *msgHandle,
                               VosMsgType eventType,
                               const void *matchData,
                               UINT32 matchDataLen);

VOS_RET_E UTIL_reboot(void *msgHandle);


VOS_RET_E UTIL_addEntityInfo(VosEntityInfoMsg *eInfo, void *msgHandle);


VOS_RET_E UTIL_delEntityInfo(const char *appName, void *msgHandle);


VosEntityId UTIL_getEidByAppName(const char *appName, void *msgHandle);


VOS_RET_E UTIL_sendRequestToGponproxy(void *msgHandle,
                                VosMsgType msgType,
                                UINT32 wordData,
                                const void *msgData,
                                UINT32 msgDataLen);

VOS_RET_E UTIL_sendRequestToEponapp(void *msgHandle,
                                      VosMsgType msgType,
                                      UINT32 wordData,
                                      const void *msgData,
                                      UINT32 msgDataLen);                                


VOS_RET_E UTIL_sendRequestToSnmpd(void *msgHandle,
                                      VosMsgType msgType,
                                      UINT32 wordData,
                                      const void *msgData,
                                      UINT32 msgDataLen);

VOS_RET_E UTIL_sendRequestAndGetReplyBuf(void *msgHandle,
                                                                  VosEntityId eid,
                                                                  VosMsgType msgType,
                                                                  UINT32 wordData,
                                                                  const void *msgData,
                                                                  char *replyData,
                                                                  UINT32 msgDataLen,
                                                                  UINT32 replyDataLen);

#endif    /* __UTIL_MSG_H__ */

