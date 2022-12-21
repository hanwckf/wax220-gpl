#ifndef __UTIL_MISC_H__
#define __UTIL_MISC_H__

typedef struct 
{
    char totalName[BUFLEN_24];  
    UINT32 memTotal;
    char freeName[BUFLEN_24];  
    UINT32 memFree;
    char buffersName[BUFLEN_24];  
    UINT32 buffers;
    char cachedName[BUFLEN_24];  
    UINT32 cached;
}UTIL_MEM_OCCUPY_T;

typedef struct 
{
    char name[BUFLEN_24];  
    unsigned long long user; 
    unsigned long long nice; 
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
    unsigned long long steal_time;
    unsigned long long guest;
}UTIL_CPU_OCCUPY_T;

int UTIL_getCpuOccupy(UTIL_CPU_OCCUPY_T *cpust);
int UTIL_calCpuOccupy(UTIL_CPU_OCCUPY_T *o, UTIL_CPU_OCCUPY_T *n);
int UTIL_getMemOccupy(UTIL_MEM_OCCUPY_T *memStat);

#endif /* __UTIL_MISC_H__*/
