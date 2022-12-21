#ifndef __SSK_PORT_H__
#define __SSK_PORT_H__

#include "dai/dai.h"

int SSK_porcessPortLink(uint8_t port, SW_PORT_LINK_STATUS_T port_status);

void SSK_broadcastPortLinkStatus(uint8_t port);

int SSK_porcessPortLinkByTimer(uint8_t port);

#endif /* __SSK_PORT_H__ */

