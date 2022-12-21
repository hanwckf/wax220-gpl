#ifndef __OPENVPN_H__
#define __OPENVPN_H__
#include "fwk/fwk.h"

typedef enum
{
    OPENVPN_DEV_TUN = 0,
    OPENVPN_DEV_TAP,
    OPENVPN_DEV_UNKNOWM,
} OPENVPN_DEV_E;


typedef enum
{
    OPENVPN_PROTO_UDP = 0,
    OPENVPN_PROTO_TCP,
    OPENVPN_PROTO_UNKNOWM,
} OPENVPN_PROTO_E;

typedef enum
{
    OPENVPN_CON_ACCESS_AUTO = 0,
    OPENVPN_CON_ACCESS_ALL,
    OPENVPN_CON_ACCESS_HOMENET,
    OPENVPN_CON_INVALID,
} OPENVPN_CON_ACCESS_E;

typedef struct {
    int                     b_enable;
    int                     tun_port;
    int                     ta_port;
    OPENVPN_DEV_E           dev;
    OPENVPN_PROTO_E         tun_proto;
    OPENVPN_PROTO_E         ta_proto;
    OPENVPN_CON_ACCESS_E    access_mode;
} OPENVPN_CONFIG_T;


int dai_openvpnGetEnable(char *value, int len);
int dai_openvpnSetEnable(char *value);
#if 0
int dai_openvpnGetDev(char *value, int len);
int dai_openvpnSetDev(char *value);
int dai_openvpnGetRunningPort(char *value, int len);
int dai_openvpnSetRunningPort(char *value);
int dai_openvpnGetRunningProto(char *value, int len);
int dai_openvpnSetRunningProto(char *value);
#endif
int dai_openvpnGetTunPort(char *value, int len);
int dai_openvpnSetTunPort(char *value);
int dai_openvpnGetTunProto(char *value, int len);
int dai_openvpnSetTunProto(char *value);
int dai_openvpnGetTapPort(char *value, int len);
int dai_openvpnSetTapPort(char *value);
int dai_openvpnGetTapProto(char *value, int len);
int dai_openvpnSetTapProto(char *value);
int dai_openvpnGetAccessMode(char *value, int len);
int dai_openvpnSetAccessMode(char *value);

int dai_openvpnCreateClientConf(const char* filename, const char* filetype);


void dai_openvpnReload();
int dai_setOpenvpnParms(OPENVPN_CONFIG_T *openvpnParms);

int dai_vpnclientGetEnable(char *value, int len);
int dai_vpnclientSetEnable(char *value);
int dai_vpnclientGetVpnProvider(char *value, int len);
int dai_vpnclientSetVpnProvider(char *value);
int dai_vpnclientGetVpnProto(char *value, int len);
int dai_vpnclientSetVpnProto(char *value);
int dai_vpnclientGetVpnCountry(char *value, int len);
int dai_vpnclientSetVpnCountry(char *value);
int dai_vpnclientGetCity(char *value, int len);
int dai_vpnclientSetCity(char *value);
int dai_vpnclientGetUserName(char *value, int len);
int dai_vpnclientSetUserName(char *value);
int dai_vpnclientGetPassword(char *value, int len);
int dai_vpnclientSetPassword(char *value);

#endif
