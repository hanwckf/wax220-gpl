#ifndef __RAE_H__
#define __RAE_H__

#include "fwk/fwk.h"

typedef struct
{
    UBOOL8 raeEnable;
    char raeVersion[BUFLEN_24];
    char raeStage[BUFLEN_16];
    char termsOfServiceVersion[BUFLEN_32];  // 服务条款版本号
} DAI_RAE_CONFIG;


int dai_getRaeConfig(DAI_RAE_CONFIG *cfg);
int dai_setRaeConfig(const DAI_RAE_CONFIG *cfg);

#endif /* __RAE_H__ */