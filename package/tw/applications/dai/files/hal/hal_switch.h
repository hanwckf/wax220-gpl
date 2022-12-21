#ifndef __HAL_SWITCH_H__
#define __HAL_SWITCH_H__

#include "fwk/fwk.h"

#define PORT2SDK dai_port2Sdk
#define SDK2PORT dai_sdk2Port
#define PBMP2SDK dai_pbmp2Sdk
#define SDK2PBMP dai_sdk2Pbmp
#define PBMP_PORT_ADD(pbmp, port) ((pbmp) |= (1 << (port)))
#define PBMP_IS_MEMBER(pbmp, port) ((pbmp) & (1 << (port)))
#define HAL_MAX_PORT_COUNT (7)
#define HAL_MAX_PORT_NUM (6)
#define PBMP_ITER(pbmp, port)                               \
    for ((port) = 0; (port) < HAL_MAX_PORT_COUNT; (port)++) \
        if (PBMP_IS_MEMBER((pbmp), (port)))

#define ACL_MAX_ACL_LEN (16)

typedef enum
{
    HAL_STATS_TDPC = 0x0,  // TX Drop Packet Counter of Port
    HAL_STATS_TCRC,        // TX CRC Packet Counter of Port
    HAL_STATS_TUPC,        // TX Unicast Packet Counter of Port
    HAL_STATS_TMPC,        // TX Multicast Packet Counter of Port
    HAL_STATS_TBPC,        // TX Broadcast Packet Counter of Port
    HAL_STATS_TCEC,        // TX Collision Event Counter of Port
    HAL_STATS_TSCEC,       // TX Single Collision Event Counter of Port
    HAL_STATS_TMCEC,       // TX Multiple Collision Event Counter of Port
    HAL_STATS_TDEC,        // TX Deferred Event Counter of Port
    HAL_STATS_TLCEC,       // TX Late Collision Event Counter of Port
    HAL_STATS_TXCEC,       // TX excessive Collision Event Counter of Port
    HAL_STATS_TPPC,        // TX Pause Packet Counter of Port
    HAL_STATS_TL64PC,      // TX packet Length in 64-byte slot Packet Counter of Port
    HAL_STATS_TL65PC,      // TX packet Length in 65-byte slot Packet Counter
    HAL_STATS_TL128PC,     // TX packet Length in 128-byte slot Packet Counter
    HAL_STATS_TL256PC,     // TX packet Length in 256-byte slot Packet Counter
    HAL_STATS_TL512PC,     // TX packet Length in 512-byte slot Packet Counter
    HAL_STATS_TL1024PC,    // TX packet Length in 1024-byte slot Packet Counter
    HAL_STATS_TOCL,        // TX Octet Counter Low double word of Port
    HAL_STATS_TOCH,        // TX Octet Counter High double word of Por
    HAL_STATS_RDPC = 0x18, // RX from 0x18, RX Drop Packet Counter of Port
    HAL_STATS_RFPC,        // RX Filtering Packet Counter of Port
    HAL_STATS_RUPC,        // RX Unicast Packet Counter of Port
    HAL_STATS_RMPC,        // RX Multicast Packet Counter of Port
    HAL_STATS_RBPC,        // RX Broadcast Packet Counter of Port
    HAL_STATS_RAEPC,       // RX Alignment Error Packet Counter of Port
    HAL_STATS_RCEPC,       // RX CRC(FCS) Error Packet Counter of Port
    HAL_STATS_RUSPC,       // RX Undersize Packet Counter of Port
    HAL_STATS_RFEPC,       // RX Fragment Error Packet Counter of Port
    HAL_STATS_ROSPC,       // RX Oversize Packet Counter of Port
    HAL_STATS_RJEPC,       // RX Jabber Error Packet Counter of Port
    HAL_STATS_RPPC,        // RX Pause Packet Counter of Port
    HAL_STATS_RL64PC,      // RX packet Length in 64-byte slot Packet Counter
    HAL_STATS_RL65PC,      // RX packet Length in 65-byte slot Packet Counter
    HAL_STATS_RL128PC,     // RX packet Length in 128-byte slot Packet Counter
    HAL_STATS_RL256PC,     // RX packet Length in 256-byte slot Packet Counter
    HAL_STATS_RL512PC,     // RX packet Length in 512-byte slot Packet Counter
    HAL_STATS_RL1024PC,    // RX packet Length in 1024-byte slot Packet Counter
    HAL_STATS_ROCL,        // RX Octet Counter Low double word of Port
    HAL_STATS_ROCH,        // Rx Octet Counter High double word of Port
    HAL_STATS_RDPC_CTRL,   // RX CTRL Drop Packet Counter of Port
    HAL_STATS_RDPC_ING,    // RX Ingress Drop Packet Counter of Port
    HAL_STATS_RDPC_ARL,    // RX ARL Drop Packet Counter of Port
    HAL_STATS_MAX
} HAL_STATS_TYPE_T;

typedef enum {
    HAL_PORT_SPEED_NONE = 0,
    HAL_PORT_SPEED_10M  = 10,
    HAL_PORT_SPEED_100M = 100,
    HAL_PORT_SPEED_1G   = 1000,
    HAL_PORT_SPEED_2P5G = 2500,
    HAL_PORT_SPEED_5G   = 5000,
    HAL_PORT_SPEED_10G  = 10000,
    HAL_PORT_SPEED_40G  = 40000,
    HAL_PORT_SPEED_100G = 100000
} HAL_PORT_SPEED_T;

typedef enum
{
    HAL_PORT_DUPLEX_HALF,
    HAL_PORT_DUPLEX_FULL
} HAL_PORT_DUPLEX_T;

typedef enum
{
    HAL_PORT_LINK_STATUS_DOWN,
    HAL_PORT_LINK_STATUS_UP
} HAL_PORT_LINK_STATUS_T;

typedef enum
{
    HAL_GLB_PORT_LED_CONTROL_FORCE_OFF = 0x1,
    HAL_GLB_PORT_LED_CONTROL_LINK_ACTIVE = 0x2,
    HAL_GLB_PORT_LED_CONTROL_LINK_ACTIVE_SPEED_MODE1 = 0x4, // In MTK 7531, led0:1000, led1:100
    HAL_GLB_PORT_LED_CONTROL_LINK_ACTIVE_SPEED_MODE2 = 0x8, // In MTK 7531, led0:1000, led1:100/10
    HAL_GLB_PORT_LED_CONTROL_FORCE_BLINK = 0x10,
    HAL_GLB_PORT_LED_CONTROL_FORCE_NOBLINK = 0x20,
    HAL_GLB_PORT_LED_CONTROL_FORCE_LED0_ON = 0x40,
    HAL_GLB_PORT_LED_CONTROL_FORCE_LED1_ON = 0x80,
    HAL_GLB_PORT_LED_CONTROL_FORCE_ON = HAL_GLB_PORT_LED_CONTROL_FORCE_LED0_ON | HAL_GLB_PORT_LED_CONTROL_FORCE_LED1_ON,
} HAL_GLB_PORT_LED_CONTROL_T;

typedef enum
{
    HAL_ACL_SLICE_L2,
    HAL_ACL_SLICE_L2_PAD,
    HAL_ACL_SLICE_L3,
    HAL_ACL_SLICE_L3_PAD,
    HAL_ACL_SLICE_L4,
    HAL_ACL_SLICE_L4_PAD,
    HAL_ACL_SLICE_IP6_L3,
    HAL_ACL_SLICE_NUM,
} HAL_ACL_SLICE_T;

typedef enum
{
    HAL_EG_TAG_ATTR_SYS = 0,
    HAL_EG_TAG_ATTR_CON = 1,
    HAL_EG_TAG_ATTR_UNTAG = 4,
    HAL_EG_TAG_ATTR_SWAP = 5,
    HAL_EG_TAG_ATTR_TAG = 6,
    HAL_EG_TAG_ATTR_STACK = 7,
    HAL_EG_TAG_ATTR_MAX,
} HAL_EG_TAG_ATTR_T;

typedef enum
{
    halAclActionDrop,
    halAclActionRate,
    halAclActionTrapToCpu,
    halAclActionCopyToCpu,
    halAclActionRedirect,
    halAclActionEgTagAttr,
    halAclActionVlanLeaky,
    halAclActionNum,
} HAL_ACL_ACTION_T;

typedef enum
{
    halAclStepFirst,
    halAclStepData0 = halAclStepFirst,
    halAclStepData1,
    halAclStepData2,
    halAclStepData3,
    halAclStepData4,
    halAclStepData5,
    halAclStepData6,
    halAclStepData7,
    halAclStepDataEnd = halAclStepData7,
    halAclStepMask,
    halAclStepRuleAction,
    halAclStepRateAction,
    halAclStepNum,
} HAL_ACL_STEP_T;

typedef enum
{
    HAL_ACL_IDX_DNS = 0,
    HAL_ACL_IDX_DOS_PROTECT = 2,
    HAL_ACL_IDX_NEXT = 3,
} HAL_ACL_IDX_T;

typedef enum
{
    HAL_ATA_CLEAN_CMD_MAC,
    HAL_ATA_CLEAN_CMD_DIP,
    HAL_ATA_CLEAN_CMD_SIP,
    HAL_ATA_CLEAN_CMD_ALL,
    HAL_ATA_CLEAN_CMD_DY_MAC,
    HAL_ATA_CLEAN_CMD_DY_DIP,
    HAL_ATA_CLEAN_CMD_STATIC_MAC,
    HAL_ATA_CLEAN_CMD_STATIC_DIP,
    HAL_ATA_CLEAN_CMD_SPECIAL_SIP_DIP,
    HAL_ATA_CLEAN_CMD_SPECIAL_SIP_SIP,
    HAL_ATA_CLEAN_CMD_BY_VID,
    HAL_ATA_CLEAN_CMD_BY_FID,
    HAL_ATA_CLEAN_CMD_BY_PORT,
    HAL_ATA_CLEAN_CMD_NUM,
} HAL_ATA_CLEAN_CMD_T;

typedef struct
{
    int vawd1;
    int vawd2;
    int vawd3;
    int vawd4;
    int vawd5;
    int vawd6;
    int vawd7;
    int vawd8;
    int vtcr;
} HAL_ACL_ITER_T;

typedef enum HAL_VLAN_PORT_MODE_E
{
    HAL_VLAN_PORT_MODE_USER,
    HAL_VLAN_PORT_MODE_STACK,
    HAL_VLAN_PORT_MODE_TRANSLATION,
    HAL_VLAN_PORT_MODE_TRANSPARENT,
    HAL_VLAN_PORT_MODE_NUM,
} HAL_VLAN_PORT_MODE_T;

typedef HAL_ACL_ITER_T halAclI_t[halAclStepNum];

typedef struct
{
    HAL_ACL_ITER_T iter[halAclStepNum];
    uint64_t map;
    int mask_tbl;
} HAL_ACL_T;

#if !defined(__x86_64__) && !defined(__i386__)
int hal_vlanPortsGet(uint16_t vlanid, hal_pbmp_t *portmap, hal_pbmp_t *uportmap);
int hal_vlanPortsSet(uint16_t vlanid, hal_pbmp_t portmap, hal_pbmp_t uportmap);
int hal_vlanPortAdd(uint16_t vlanid, hal_port_t port, hal_port_t tagged);
int hal_vlanPortRemove(uint16_t vlanid, hal_port_t port);
int hal_vlanPortsAdd(uint16_t vlanid, hal_pbmp_t map, uint8_t tagged);
int hal_vlanPortsRemove(uint16_t vlanid, hal_pbmp_t map);
int hal_portPvidGet(hal_port_t port);
int hal_portPvidSet(hal_port_t port, uint16_t vlanid);
uint32_t hal_rawStatsGet(hal_port_t port, HAL_STATS_TYPE_T type);
int hal_portLinkStatusGet(hal_port_t port, HAL_PORT_LINK_STATUS_T *link_status);
int hal_portNegResultGet(hal_port_t port, HAL_PORT_SPEED_T *speed, HAL_PORT_DUPLEX_T *duplex);
int hal_portsLinkUpTimeGet(uint32_t *upsec, uint8_t count);
int hal_globalPortLedControlSet(HAL_GLB_PORT_LED_CONTROL_T control);
int hal_portEgressSet(hal_port_t port, hal_pbmp_t egr_map);
int hal_portEgressGet(hal_port_t port, hal_pbmp_t *egr_map);
int hal_portEnableSet(hal_port_t port, uint8_t enable);
int hal_portEnableGet(hal_port_t port, uint8_t *enable);
int hal_statsClear(void);
int hal_macVidEntryFind(uint8_t *mac, uint16_t vid, uint8_t *fid, hal_pbmp_t *halpbmp);
int hal_macFidEntryFind(uint8_t *mac, uint8_t fid, uint16_t *vid, hal_pbmp_t *halpbmp);
int hal_mirrorEnableSet(hal_port_t halport, uint8_t dir_rx, uint8_t enable);
int hal_mirrorDestSet(hal_port_t halport, uint8_t enable);
int hal_aclExample(void);
int hal_portPbitSet(hal_port_t port, uint8_t pbit);
int hal_portPbitGet(hal_port_t port);
int hal_addrTableCleanByVid(uint16_t vid);
int hal_addrTableCleanByFid(uint16_t fid);
int hal_addrTableCleanByPort(hal_port_t halport);
int hal_mirrorEnableGet(hal_port_t halport, uint8_t dir_rx, uint8_t *enable);
int hal_vlanDelete(uint16_t vid);
int hal_vlanPortModeSet(hal_port_t port, HAL_VLAN_PORT_MODE_T mode);
HAL_VLAN_PORT_MODE_T hal_vlanPortModeGet(hal_port_t port);
int hal_hwnat_clear(void);
int hal_aclMulticastVlanInit(uint8_t enable);
int hal_readEthInterrupt();
int hal_ethInterrupt();
#endif

#endif