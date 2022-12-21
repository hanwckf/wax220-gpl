#ifndef __UTIL_TASK_H__
#define __UTIL_TASK_H__

typedef void (*UTIL_TASK_FUNC)(void *arg);

VOS_RET_E UTIL_taskStart(UTIL_TASK_FUNC startFunc, void *arg, UTIL_TASK_FUNC finishFunc, void *msgHandle);
VOS_RET_E UTIL_taskFinish(const VosMsgHeader *msg);

#endif /* __UTIL_TASK_H__ */

