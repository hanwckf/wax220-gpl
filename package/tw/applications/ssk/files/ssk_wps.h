#ifndef __SSK_WAN_H__
#define __SSK_WAN_H__

#include "fwk/fwk.h"
#include "dai/dai.h"

void SSK_porcessWpsPeerMessage(uint8_t rfband, unsigned char * macAddr, char * deviceName);
void SSK_porcessWpsCrdlMessage(uint8_t rfBand, unsigned short authType, unsigned short encrType, 
                               unsigned short ssidLen, unsigned char * ssid, unsigned short wpaPskLen, unsigned char * wpaPsk);

#endif /* __SSK_WAN_H__ */
