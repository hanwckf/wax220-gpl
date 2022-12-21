#ifndef __SSK_H__
#define __SSK_H__

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <libubus.h>
#include "fwk/fwk.h"
#include "dai/dai.h"
#include <syslog.h>
#include <errno.h>

struct ubus_context *ssk_mainCtx(void);
int ssk_ubusInit(void);
int SSK_ubusDelTimer(struct uloop_timeout *timeout);
int SSK_ubusAddTimer(struct uloop_timeout *timeout, int mescs);
struct blob_attr *SSK_ubusGetBlobmsg(struct blob_attr *msg, char * name);
int ssk_nlInit(void);
int ssk_systemInit(void);
void SSK_wifiInit(void);

#endif