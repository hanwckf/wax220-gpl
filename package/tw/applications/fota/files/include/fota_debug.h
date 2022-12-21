#ifndef __FOTA_DEBUG_H__
#define __FOTA_DEBUG_H__

#if 0
#define DEBUG(fmt, args...) do { \
                syslog(LOG_NOTICE, "%s, %s, %d: ", __FILE__, __func__, __LINE__); \
                syslog(LOG_NOTICE, fmt, ## args); \
            } while (0)

#else
#define DEBUG(fmt, args...) do { \
        printf("%s, %s, %d: ", __FILE__, __func__, __LINE__); \
        printf(fmt, ## args); \
        syslog(LOG_NOTICE, "%s, %s, %d: ", __FILE__, __func__, __LINE__); \
        syslog(LOG_NOTICE, fmt, ## args); \
    } while (0)
#endif

#define RETURN_IF_NULL(p, ret) \
    if (!(p)) \
    { \
        DEBUG("'%s' is null pointer.\n", #p); \
        return ret; \
    } \
    else

#define RETURN_IF_EQUAL(result, value, ret) \
    if ((result) == (value)) \
    { \
        DEBUG("The value of '%s' is not OK.\n", #result); \
        return ret; \
    } \
    else

#define GOTO_IF_NULL(p, label) \
    if (!(p)) \
    { \
        DEBUG("'%s' is null pointer.\n", #p); \
        goto label; \
    } \
    else

#define GOTO_IF_NOT_EQUAL(result, value, label) \
    if ((result) != (value)) \
    { \
        DEBUG("The value of '%s' is not OK.\n", #result); \
        goto label; \
    } \
    else

#define GOTO_IF_EQUAL(result, value, label) \
    if ((result) == (value)) \
    { \
        DEBUG("The value of '%s' is not OK.\n", #result); \
        goto label; \
    } \
    else

#endif

