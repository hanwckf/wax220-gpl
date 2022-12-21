#ifndef __SPEED_TEST_H__
#define __SPEED_TEST_H__

#define SPEED_TEST_HISTORY_MAX 10

typedef enum speedtestHistoryStatus
{
    DAI_SPEEDTEST_HISTORY_STATUS_NOT_RUN,
    DAI_SPEEDTEST_HISTORY_STATUS_RUNING,
    DAI_SPEEDTEST_HISTORY_STATUS_END,
    DAI_SPEEDTEST_HISTORY_STATUS_OVERTIME,
    DAI_SPEEDTEST_HISTORY_STATUS_ERROR,
    DAI_SPEEDTEST_HISTORY_STATUS_LAST,
} DAI_SPEEDTEST_HISTORY_STATUS_E;

typedef struct speedtestHistory
{
    UINT32 download; // byte/s
    UINT32 upload;   // byte/s
    double latency;  // ms
    double jitter;   // ms
    DAI_SPEEDTEST_HISTORY_STATUS_E status;
    char timestamp[32];
} DAI_SPEEDTEST_HISTORY_T;

/**
 * @brief 
 * Converts the status to a description string
 * @param status  DAI_SPEEDTEST_HISTORY_STATUS_E
 * @param statusStr Returns the result
 * @param bufSize statusStr‘s size
 * @return statusStr 
 */
char* dai_speedTestConvStatusToStr(DAI_SPEEDTEST_HISTORY_STATUS_E status, char* statusStr, size_t bufSize);

/**
 * @brief 
 * Converts a state description string to an enumeration
 * @param statusStr state description string
 * @return DAI_SPEEDTEST_HISTORY_STATUS_E 
 */
DAI_SPEEDTEST_HISTORY_STATUS_E dai_speedTestConvStrToStatus(const char* statusStr);

/**
 * @brief 
 * Added a speed test history. The maximum number of history entries is defined by SPEED_TEST_HISTORY_MAX.
 * The maximum number of entries is exceeded.The earliest records will be deleted
 * @param speedtestHistory 
 * @return 0 or -1
 */
int dai_speedTestAppendHistory(const DAI_SPEEDTEST_HISTORY_T *speedtestHistory);

/**
 * @brief 
 * Gets a historical record based on the index
 * @param speedtestHistory The return value to save the history
 * @param idx The index of the history
 * @return UCI STATE
 */
int dai_speedTestGetHistory(DAI_SPEEDTEST_HISTORY_T *speedtestHistory, int idx);

/**
 * @brief 
 * Get the speedtest history.
 * 
 * @param speedtestHistory 
 * Pointer to receive the result.The memory is allocated by the interface. 
 * You need to manually release the memory after using the memory.
 * The history pointer will point to NULL if there is no speed gauge
 * 
 * @param limit 
 * Maximum number of entries. 0 means no limit
 * 
 * @return The number of entries actually obtained.
 */
size_t dai_speedTestdumpHistory(DAI_SPEEDTEST_HISTORY_T **speedtestHistory, size_t limit);

#endif