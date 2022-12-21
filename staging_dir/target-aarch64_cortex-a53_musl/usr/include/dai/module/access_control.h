#ifndef __ACCESS_CONTROL_H__
#define __ACCESS_CONTROL_H__
#include "fwk/fwk.h"
#include "json-c/json.h"
#include "json-c/json_inttypes.h"
#include "json-c/json_object.h"
#include "json-c/json_tokener.h"
#include "json-c/json_util.h"

#define ACCESS_CONTROL_FIREWALL_RULE_NAME   "tw_accesscontrolRule"
#define ACCESS_CONTROL_DEVICE_LIST_BUF_SIZE    524288
#define ACCESS_CONTROL_EBTABLE_FWD_CHAIN   "access_control_fwd"

typedef enum
{
    ONLINE_DEVICE_LIST,
    OFFLINE_ALLOWED_DEVICE_LIST,
    OFFLINE_BLOCKED_DEVICE_LIST,
    ONLINE_DEVICE_VPN_LIST,
} ATTACH_DEVICE_ACTION_E;

typedef enum
{
    ATTACH_DEVICE_PRIORITY_LOW,
    ATTACH_DEVICE_PRIORITY_MEDIUM,
    ATTACH_DEVICE_PRIORITY_HIGH,
    ATTACH_DEVICE_PRIORITY_HIGHEST
} ATTACH_DEVICE_PRIORITY;

typedef struct{
    int access_control_enable;      // 1 开启访问控制 0 关闭访问控制
    char control_type[BUFLEN_32];   //Block:新上线设备拒绝访问，Allow:新上线设备可以访问
} ACCESS_CONTROL_T;

typedef struct{
    char ip[BUFLEN_32];         //下挂设备的ip地址
    char mac[BUFLEN_32];        //下挂设备的mac地址
    char devname[BUFLEN_64];    //下挂设备名称
    char connType[BUFLEN_32];   //连接类型, 取值范围 'wired' / '2.4G' / '5G' / '5G-2'
    char ifname[BUFLEN_24];     //连接的接口 如ra0 eth0.0
    char status[BUFLEN_32];     //当前设备是否允许连接或不允许连接 Allowed or Blocked
    char deviceType[BUFLEN_32]; //当前设备连接类型
    int  deviceTypeNum;          // 当前设备连接NUM,NETGEAR定义
    char deviceModel[BUFLEN_64]; //当前设备连接mode,NETGEAR定义
    char customName[BUFLEN_128];
    char customModel[BUFLEN_128];
    UINT32 customTypeNum;
    char onlineStatus[BUFLEN_32];
    ATTACH_DEVICE_PRIORITY priority;
    UINT32 downSpeed; //Shows past 30 seconds average internet download speed for each device. (平均每秒字节数)
    UINT32 upSpeed; //Shows past 30 seconds average internet upload speed for each device. (平均每秒字节数)
} ACCESS_CONTROL_ATTACH_DEV_LIST_T;

//修改当前在线设备Allowed or Blocked
typedef struct{
    int access_control_enable;    // 1 开启访问控制 0 关闭访问控制
    char control_type[BUFLEN_32]; //Block:新上线设备拒绝访问，Allow:新上线设备可以访问
    char maclist[5120];    // cgi 传入的的mac列表 如:08:57:00:EF:D5:12#C8:5B:76:B2:09:E2
    char status[BUFLEN_32];       // Allowed or Blocked
} ACCESS_CONTROL_MODIFY_ATTACH_DEV__T;

//修改在访问控制列表中设备Allowed or Blocked和devname
typedef struct{
    char edit_type[BUFLEN_32];  //在线设备:connect_device         或者:allow、block
    char edit_mac[BUFLEN_32];   //修改的mac地址
    char devname[BUFLEN_64];    //设备名称
    char status[BUFLEN_32];    //Allowed or Blocked
    char new_mac[BUFLEN_32];    //修改之后的mac
} ACCESS_CONTROL_EDIT_DEV__T;

/*
    访问控制开始和关闭以及黑白名单
    dai_setAccessControlParms
    dai_getAccessControlParms
*/
int dai_setAccessControlParms(ACCESS_CONTROL_T *access_control_cfg);
int dai_getAccessControlParms(ACCESS_CONTROL_T *access_control_cfg);

int dai_addAclDev(ACCESS_CONTROL_ATTACH_DEV_LIST_T *userData);
int dai_delAclDev(const char *mac);
int dai_editAclDevStatusAndDevname(const char *mac, const char *devstatus, const char *devname);
int dai_modifyAclDevStatus(const char *mac, const char *devstatus);
int dai_editAclDevCustomInfo(const char *mac, const char *devname, const char *devModel, int devTypeNum, ATTACH_DEVICE_PRIORITY priority);
int dai_getAclDev(const char *mac, ACCESS_CONTROL_ATTACH_DEV_LIST_T *userData);
int dai_getDeviceList(ATTACH_DEVICE_ACTION_E action, ACCESS_CONTROL_ATTACH_DEV_LIST_T **devListRef, int *num);
int dai_getAclDev_withIp(const char *ip, ACCESS_CONTROL_ATTACH_DEV_LIST_T *userData);
/*
   根据访问控制mac列表，设置防火墙规则
*/
int dai_setAccessControlfirewallRule();

char *dai_Str2DoSystemConversion(char *src, char *dst, int length);

#endif
