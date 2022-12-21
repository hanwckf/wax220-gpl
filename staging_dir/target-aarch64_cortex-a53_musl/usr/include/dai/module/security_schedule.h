#ifndef __SECURITY_SCHEDULE_H__
#define __SECURITY_SCHEDULE_H__
#include "fwk/fwk.h"

typedef struct{
    char daysofweek[BUFLEN_64];
    char starttime[BUFLEN_32];
    char stoptime[BUFLEN_32];
    char days_to_block[BUFLEN_64];
    int  block_all_day;
} SECURITY_SCHEDULE_T;


int dai_getSchedule_days_to_block(char *days_to_block, int len);
int dai_getSchedule_all_day(char *block_all_day, int len);
int dai_getSchedule_start_block_time(char *start_block_time, int len);
int dai_getSchedule_end_block_time(char *end_block_time, int len);
int dai_setsecurity_schedule_cfg(SECURITY_SCHEDULE_T *pSecurityschedule);

#endif
