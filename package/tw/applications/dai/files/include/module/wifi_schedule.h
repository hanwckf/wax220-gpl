#ifndef __WIFI_SCHEDULE_H__
#define __WIFI_SCHEDULE_H__

#include "fwk/fwk.h"

typedef enum
{
    ACT_ADD = 0,
    ACT_DEL,
    ACT_EDIT
} ACTION_TYPE_E;

typedef enum
{
    RADIO_2G = 0,
    RADIO_5G
} WIFI_SCHEDULE_RADIO_E;

typedef enum
{
    ACTION_STOP = 0,
    ACTION_START
} WIFI_SCHEDULE_ACTION_E;

typedef struct{
    int daily;
    char day_week[BUFLEN_128];
    int op; /* 0: add; 1: del; 2: edit */
    int radio;
    int rule_idx;
    char start_time[BUFLEN_32];
    char stop_time[BUFLEN_32];
} WIFI_SCHEDULE_RULE_T;

#define WEEK_DAYS 7
#define WEEK_TIME_POINTS 48

int dai_wifiScheduleEnableGet(int radio, char *value, UINT32 len);
int dai_wifiScheduleEnableSet(int radio, int val);
int dai_wifiScheduleRuleAdd(WIFI_SCHEDULE_RULE_T *rule);
int dai_wifiScheduleRuleGet(WIFI_SCHEDULE_RULE_T *rule);
int dai_wifiScheduleRuleEdit(WIFI_SCHEDULE_RULE_T *rule);
int dai_wifiScheduleRuleDel(int radio, int index);
int dai_wifiScheduleTime2IndexTrans(char *time, int *index);
int dai_wifiScheduleIndex2TimeTrans(int index, char *time);
int dai_wifiScheduleWeekday2IndexTrans(char *weekday, char *index);
int dai_wifiScheduleIndex2WeekdayTrans(char *index, char *weekday);
int dai_wifiScheduleRuleHandle(WIFI_SCHEDULE_RULE_T *rule);
void dai_wifiScheduleAction();
void dai_wifiScheduleSync2GTo5G();
int dai_wifiScheduleRebootStatusGet(char *value, UINT32 len);
int dai_wifiScheduleRebootStatusSet(char *value);
int dai_wifiScheduleRebootDayGet(char *value, UINT32 len);
int dai_wifiScheduleRebootDaySet(char *value);
int dai_wifiScheduleRebootTimeGet(char *value, UINT32 len);
int dai_wifiScheduleRebootTimeSet(char *value);
int dai_wifiScheduleAutoRebootOn();
int dai_wifiScheduleAutoRebootOff();
int dai_wifiScheduleStatusEnableGet(char *value, UINT32 len);
int dai_wifiScheduleStatusEnableSet(char *value);
int dai_wifiScheduleTemplatesGet(char *value, UINT32 len);
int dai_wifiScheduleDaySwitchGet(char *value, UINT32 len, int ifaceId, int day);
int dai_wifiScheduleDaySwitchSet(char *value, int ifaceId, int day);
int dai_wifiScheduleStartTimeGet(char *value, UINT32 len, int ifaceId, int day);
int dai_wifiScheduleStartTimeSet(char *timeStart, int ifaceId, int day);
int dai_wifiScheduleEndTimeGet(char *value, UINT32 len, int ifaceId, int day);
int dai_wifiScheduleEndTimeSet(char *endTime, int ifaceId, int day);
int dai_updateWifiSchedule(int ifaceId);
int dai_updateWifiScheduleTaskCfg(UBOOL8 scheduleEnableOld, UBOOL8 scheduleEnable, int ifaceId, int templatesId);
#endif
