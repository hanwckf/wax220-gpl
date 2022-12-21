#ifndef TRAFFICMETER_H
#define TRAFFICMETER_H
#include <stdint.h>
#define TRAFFIC_MINBANKINDEX          0
#define TRAFFIC_DAYCOUNT              2
#define TRAFFIC_MAXMDAYCOUNT          32
#define TRAFFIC_MINCOUNT              (12 * 60)
#define TRAFFIC_HOURMAXCOUNT          (2 * TRAFFIC_MAXMDAYCOUNT * TRAFFIC_DAYCOUNT)

#define SAVEDDATA_TIME                (1000 * 5)
#define SAVEDDATA_MINTIME             (1000 * 60)

#define WAN_PORT                      0
#define LASTSWITCHDATA                "/tmp/lastswitchdata"
#define DAYSWITCHDATA                 "/tmp/dayswitchdata"
#define TRAFFICMETERDATA              "/tmp/trafficmeterdata" 
#define TRAFFICMCRCSIZE               (sizeof(struct trafficDataBytes) + sizeof(time_t))
#define TRAFFICPPPUPTIME              "/tmp/pppstarttime"
#define TRAFFICPPPCONNECTIONTIME      "/tmp/pppconnectiontime"
#define TRAFFICPPPDOWNTIME            "/tmp/pppdowntime"
#define TRAFFICBLOCKFILE              "/tmp/tarfficmeterblock"
#define TRAFFICWARNINGFILE            "/tmp/tarfficmeterwarning"

struct trafficDataBytes
{
    uint64_t tx;
    uint64_t rx;
    uint32_t second;
};

struct trafficM
{
    struct trafficDataBytes dataBytes;
    time_t time;
    uint32_t crc;
};
union uTrafficM
{
    unsigned char data[64];
    struct trafficM trafficm;
};
struct trafficMeterData
{
    struct trafficDataBytes today;
    struct trafficDataBytes yesterday;
    struct trafficDataBytes thisweek;
    struct trafficDataBytes lastmonth;
    struct trafficDataBytes thismonth;
};

enum TRAFFICLOG
{
    TRAFFICLOGWARNING = 1,
    TRAFFICLOGBLOCK,
};
//    option enable '0'       使能
//    option day '1'        天
//    option minutes '0'      多少分
//    option volumnTimeEnable '0'     连接时间
//    option limit '0'    控制方向  
//    option monVolumnLimit '0'      月流量
//    option monTimeLimit '0'     月时间  
//    option leftTimeVolumn '0'   剩余多少出告警信息
//    option roundUp '0'          数据卷
//    option trafficLed  '0'     led
//    option trafficBlock '0'   block
//    option restartTime 'Tue Jun  1 00:00:00 2021'   重置时间
struct trafficMeterConfig
{
    char enable;    //功能使能
    char led;       //led告警灯使能
    char block;     //网址功能
    char volumnTimeEnable;  // pppoe 连接时间控制
    char dirlimit;
    char blockNet;    //是否断开网络
    char logflag;   //0位表示 warning 1位表示 block
    int day;
    int minutes;    
    unsigned int roundUp;
    unsigned int leftTimeVolumn;
    unsigned int monVolumnLimit;
    unsigned int monTimeLimit;  //pppoe 连接时间限制
    char restartTime[BUFLEN_64];
    char blockTime[BUFLEN_64];
    char warningTime[BUFLEN_64];
};


void dai_sysGetTrafficMeterStartTime(int *day, int *mins);
void dai_sysGetTrafficMeterMinutes(int *mins);
void dai_sysGetTrafficMeterDay(int *day);
void dai_sysGetTrafficMeterEnable(int *enable);
void dai_sysGetTrafficMeterVolumnTimeEnable(int *enable);
void dai_sysGetTrafficMeterLimit(int *limit);
void dai_sysGetTrafficMeterMonVolumnLimit(unsigned int *limit);
void dai_sysGetTrafficMeterMonTimeLimit(unsigned int *limit);
void dai_sysGetTrafficMeterLeftTimeVolumn(unsigned int *volumn);
void dai_sysGetTrafficMeterRoundUp(unsigned int *roundUp);
void dai_sysGetTrafficMeterLed(int *led);
void dai_sysGetTrafficMeterBlock(int *block);
void dai_sysGetTrafficMeterRestartTime(char *data, int len);
void dai_sysGetTrafficConfig(struct trafficMeterConfig *tmc);

void dai_sysSetTrafficConfig(struct trafficMeterConfig *tmc);
void dai_sysSetTCRestartTime(char *restartTime);
void dai_sysSetTCBlockTime(char *blockTime);
void dai_sysSetTCBlockNet(int blockNet);


void dai_sysSetTrafficMeterByHour(int index,struct trafficM *trafficM);
int dai_sysGetTrafficMeterByHour(int index,struct trafficM *trafficM);
int dai_sysEraseTrafficMeterByHour(int index);
void dai_sysSetTrafficMeterByMin(int index,struct trafficM *trafficM);
int dai_sysGetTrafficMeterByMin(int index,struct trafficM *trafficM);
int dai_sysEraseTrafficMeterByMin(int index, int count);

int dai_setLastSwitchDataFile(struct trafficDataBytes *dataBytes);
int dai_getLastSwitchDataFile(struct trafficDataBytes *dataBytes);
int dai_setDaySwitchDataFile(struct trafficDataBytes *dataBytes);
int dai_getDaySwitchDataFile(struct trafficDataBytes *dataBytes);
int dai_setTrafficDataFile(struct trafficMeterData *trafficDataBytes);
int dai_getTrafficDataFile(struct trafficMeterData *trafficDataBytes);
int dai_getPPPStartTimeFile(int *time);
int dai_getPPPConnectionTimeFile(int *second);
int dai_GetPPPUpTime(int *time);

int dai_GetPPPDownTime(int *time);

int dai_GetTraffic_ShowPagerefreshTime(int *time);

int dai_SetTraffic_ShowPagerefreshTime(int time);
int dai_sysEraseTrafficMeterByThisMouth();
void dai_sysSetTCLogFlag(int flag);
void dai_sysSetTCWarningTime(char *warningTime);


#endif

