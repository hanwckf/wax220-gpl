#ifndef __TELNETENABLED_H__
#define __TELNETENABLED_H__

#define LOG_LEVEL_DEBUG    LOG_DEBUG
#define LOG_LEVEL_WARNING  LOG_WARNING
#define LOG_LEVEL_ERROR    LOG_ERR

#define TELENTENABLED_LOG(level, fmt, ...) \
    do { \
        syslog(level, "[%s:%d]: "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while (0)

#define TELENT_PORT (23)
#define TELENTENABLED_PERFIX "AMBIT_TELNET_ENABLE+"
#define TELENT_BIND_IFNAME "br-lan"
struct pkt_payload
{
    char signature[0x10];
    char mac[0x10];
    char username[0x10];
    char password[0x10];
    char reserved[0x40];
};
#endif