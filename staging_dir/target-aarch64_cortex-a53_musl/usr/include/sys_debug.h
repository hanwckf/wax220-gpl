#ifndef __SYS_DEBUG_H__
#define __SYS_DEBUG_H__

#define COLORFUL_DBG_MSG	1
#if COLORFUL_DBG_MSG
#define SYS_LOG_LV_VBS  (1 << 0)
#define SYS_LOG_LV_INF  (1 << 1)
#define SYS_LOG_LV_DBG  (1 << 2)
#define SYS_LOG_LV_WRN  (1 << 3)
#define SYS_LOG_LV_ERR  (1 << 4)
#define SYS_LOG_MASK    (SYS_LOG_LV_VBS|SYS_LOG_LV_INF|SYS_LOG_LV_DBG|SYS_LOG_LV_WRN|SYS_LOG_LV_ERR)

#define SYS_LOG_FLAG_COLOR             (1 << 5)
#define SYS_LOG_FLAG_TIMESTAMP         (1 << 6)

#define SYS_Logv(fmt, ...) SYS_Log(SYS_LOG_LV_VBS, "<V> " fmt , ## __VA_ARGS__)
#define SYS_Logi(fmt, ...) SYS_Log(SYS_LOG_LV_INF, "<I> " fmt , ## __VA_ARGS__)
#define SYS_Logd(fmt, ...) SYS_Log(SYS_LOG_LV_DBG, "<D> [%s]" fmt , __func__, ## __VA_ARGS__)
#define SYS_Logw(fmt, ...) SYS_Log(SYS_LOG_LV_WRN, "<W> %s(). " fmt , __func__, ## __VA_ARGS__)
#define SYS_Loge(fmt, ...) SYS_Log(SYS_LOG_LV_ERR, "<E> %s:%d %s(). " fmt , __FILE__, __LINE__, __func__, ## __VA_ARGS__)

#define SYS_Logv_nf(fmt, ...) SYS_Log(SYS_LOG_LV_VBS, fmt , ## __VA_ARGS__)
#define SYS_Logi_nf(fmt, ...) SYS_Log(SYS_LOG_LV_INF, fmt , ## __VA_ARGS__)
#define SYS_Logd_nf(fmt, ...) SYS_Log(SYS_LOG_LV_DBG, fmt , ## __VA_ARGS__)

void SYS_Log(unsigned char lv, const char *fmt, ...);
void SYS_Log_SetFlag(const char *str, unsigned char flags);
#else
#define SYS_Logv(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#define SYS_Logi(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#define SYS_Logd(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#define SYS_Logw(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#define SYS_Loge(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)

#define SYS_Logv_nf(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#define SYS_Logi_nf(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#define SYS_Logd_nf(fmt, ...) fprintf(stderr, "[%s][%d]"fmt, __func__, __LINE__, ## __VA_ARGS__)
#endif

#endif  //__SYS_DEBUG_H__

