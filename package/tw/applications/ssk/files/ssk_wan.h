#ifndef __SSK_WAN_H__
#define __SSK_WAN_H__

#include "fwk/fwk.h"
#include "dai/dai.h"

void SSK_processWanLinkChange(SW_PORT_LINK_STATUS_T port_status, char *proto);
void SSK_processApupLinkChange(uint8_t port, SW_PORT_LINK_STATUS_T port_status, char *proto);
void SSK_processWdsUpLinkChange(const char *link_stat);
#endif /* __SSK_WAN_H__ */
