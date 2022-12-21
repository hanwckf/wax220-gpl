#ifndef __SSK_SYSTEM_H__
#define __SSK_SYSTEM_H__

#include "dai/dai.h"

UBOOL8 ssk_getCpuloadEnable();

int sysControl_Handle(void);

int ssk_sysGetCpuloadFromCmd(int cpunum, float * cpuLoadAll, float * cpuLoadIdle);

int sysCpuLoadrateUpdate(void);

int ssk_sysEventHandlerInit(void);

#endif /* __SSK_SYSTEM_H__ */