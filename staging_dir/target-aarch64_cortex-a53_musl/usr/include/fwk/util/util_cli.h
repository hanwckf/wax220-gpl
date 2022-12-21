#ifndef __UTIL_CLI_H__
#define __UTIL_CLI_H__


#include "../fwk.h"


#define UTIL_CLI_REMOTE_RESULT_FILE    "/tmp/cli_remote_result"
#define UTIL_CLI_VERSION_RESULT_FILE    "/show_version"
#define UTIL_CLI_NAT_RESULT_FILE    "/proc/net/ip_conntrack"

typedef VOS_RET_E (*UTIL_CLI_REMOTE_FUNC)(int argc, const char **argv, FILE *file);


VOS_RET_E UTIL_processRemoteCli(void *msgHandle,
                                const VosMsgHeader *msg,
                                UTIL_CLI_REMOTE_FUNC func);

VOS_RET_E UTIL_cliHandleCmd(void *msgHandle, const VosMsgHeader *msg);

#endif    /* __UTIL_CLI_H__ */
