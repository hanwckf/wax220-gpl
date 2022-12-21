#ifndef __SWITCH_H__
#define __SWITCH_H__
#include "fwk/fwk.h"

#define SW_SPEED_FULL_TO_HALF(full_speed) ((full_speed) + 1)
#define DAI_WAN_PORT (0)
#define DAI_CPU_PORT (6)
#define DAI_CPU_PORT2 (5)

//common eth lan port
#define DAI_ALL_LAN (100)
#if defined(CUSTOMER_MODEL_WAX206)
#define MAX_PORT_NUM (4)
#define MAX_HAL_PORT_NUM (6)
#elif defined(CUSTOMER_MODEL_WAX202)
#define MAX_PORT_NUM (3)
#define MAX_HAL_PORT_NUM (6)
#elif defined(CUSTOMER_MODEL_WAX214v2)
#define MAX_PORT_NUM (3)
#define MAX_HAL_PORT_NUM (6)
#elif defined(CUSTOMER_MODEL_WAX220)
#define MAX_PORT_NUM (3)
#define MAX_HAL_PORT_NUM (6)
#else
#error "Should define the MAX_PORT_NUM and MAX_HAL_PORT_NUM!"
#endif

#define PORT_ALL_ITER(_port) \
    for ((_port) = 0; ((_port) <= 6) && ((_port) == DAI_WAN_PORT || (_port) == DAI_CPU_PORT || ((_port) >= 1 && (_port) <= MAX_PORT_NUM)); (_port)++)
#define PORT_ETH_ITER(_port) \
    for ((_port) = 0; ((_port) <= 6) && ((_port) == DAI_WAN_PORT || ((_port) >= 1 && (_port) <= MAX_PORT_NUM)); (_port)++)
#define PORT_LAN_ITER(_port) \
    for ((_port) = 1; (_port) <= MAX_PORT_NUM; (_port)++)

#define PORT_ALL_HAL_ITER(_port, _hal) \
    PORT_ALL_ITER(_port)               \
    if (((_hal) = dai_port2Sdk(_port)) <= MAX_HAL_PORT_NUM)
#define PORT_ETH_HAL_ITER(_port, _hal) \
    PORT_ETH_ITER(_port)               \
    if (((_hal) = dai_port2Sdk(_port)) <= MAX_HAL_PORT_NUM)
#define PORT_LAN_HAL_ITER(_port, _hal) \
    PORT_LAN_ITER(_port)               \
    if (((_hal) = dai_port2Sdk(_port)) <= MAX_HAL_PORT_NUM)

#define PORT_ALL_PBMP_ITER(_port, _pbmp)         \
    for ((_port) = 0; ((_port) <= 6); (_port)++) \
        if (_pbmp & (1 << (_port)))

typedef enum
{
    SW_STATS_TX_UCAST_PKTS,
    SW_STATS_TX_MCAST_PKTS,
    SW_STATS_TX_BCAST_PKTS,
    SW_STATS_TX_PKTS,
    SW_STATS_TX_OCTETS,
    SW_STATS_COLLISIONS,
    SW_STATS_RX_UCAST_PKTS,
    SW_STATS_RX_MCAST_PKTS,
    SW_STATS_RX_BCAST_PKTS,
    SW_STATS_RX_PKTS,
    SW_STATS_RX_OCTETS,
    SW_STATS_MAX
} SW_STATS_TYPE_T;

typedef enum
{
    SW_PORT_NEG_RESULT_10M_FULL = 10,
    SW_PORT_NEG_RESULT_10M_HALF = SW_SPEED_FULL_TO_HALF(10),
    SW_PORT_NEG_RESULT_100M_FULL = 100,
    SW_PORT_NEG_RESULT_100M_HALF = SW_SPEED_FULL_TO_HALF(100),
    SW_PORT_NEG_RESULT_1G = 1000,
    SW_PORT_NEG_RESULT_2P5G = 2500,
    SW_PORT_NEG_RESULT_5G = 5000,
    SW_PORT_NEG_RESULT_10G = 10000
} SW_PORT_NEG_RESULT_T;

typedef enum
{
    SW_PORT_LINK_STATUS_DOWN,
    SW_PORT_LINK_STATUS_UP
} SW_PORT_LINK_STATUS_T;

typedef enum
{
    SW_ETH_LED_MODE_NORMAL,
    SW_ETH_LED_MODE_FORCE_ON,
    SW_ETH_LED_MODE_FORCE_OFF,
    SW_ETH_LED_MODE_FORCE_BLINK,
    SW_ETH_LED_MODE_FORCE_NOBLINK,
    SW_ETH_LED_MODE_FORCE_LED0_ON,
    SW_ETH_LED_MODE_FORCE_LED1_ON,
    SW_ETH_LED_MODE_NUM
} SW_ETH_LED_MODE_T;

typedef enum
{
    SW_MIR_MODE_OFF = 0,
    SW_MIR_MODE_TX = 1,
    SW_MIR_MODE_RX = 2,
    SW_MIR_MODE_TXRX = 3,
    SW_MIR_MODE_NUM = 4,
} SW_MIR_MODE_T;

typedef enum
{
    SW_VLAN_PORT_MODE_USER,
    SW_VLAN_PORT_MODE_STACK,
    SW_VLAN_PORT_MODE_TRANSLATION,
    SW_VLAN_PORT_MODE_TRANSPARENT,
    SW_VLAN_PORT_MODE_NUM,
} SW_VLAN_PORT_MODE_T;

hal_port_t dai_port2Sdk(uint8_t port);
uint8_t dai_sdk2Port(hal_port_t halport);
hal_pbmp_t dai_pbmp2Sdk(uint32_t pbmp);
hal_pbmp_t dai_pbmp2TagSdk(uint32_t pbmp);
uint32_t dai_sdk2Pbmp(hal_pbmp_t halpbmp);
int dai_vlanPortsGet(uint16_t vlanid, uint32_t *portmap, uint32_t *uportmap);
int dai_vlanPortsSet(uint16_t vlanid, uint32_t portmap, uint32_t uportmap);
int dai_vlanPortAdd(uint16_t vlanid, uint8_t port, uint8_t tagged);
int dai_vlanPortRemove(uint16_t vlanid, uint8_t port);
int dai_vlanPortsAdd(uint16_t vlanid, uint32_t map, uint8_t tagged);
int dai_vlanPortsRemove(uint16_t vlanid, uint32_t map);
int dai_portPvidGet(uint8_t port);
int dai_portPvidSet(uint8_t port, uint16_t vlanid);
int dai_portStatsGet(uint8_t port, SW_STATS_TYPE_T type, uint64_t *value);
SW_PORT_NEG_RESULT_T dai_portNegResultGet(uint8_t port);
SW_PORT_LINK_STATUS_T dai_portLinkStatusGet(uint8_t port);
uint32_t dai_portLinkUpTimeGet(uint8_t port);
int dai_portEgressSet(uint8_t port, uint32_t map);
int dai_portEgressGet(uint8_t port, uint32_t *map);
int dai_ethLedModeSet(SW_ETH_LED_MODE_T mode);
int dai_portEnableSet(uint8_t port, int enable);
int dai_portEnableGet(uint8_t port);
int dai_statsClear(void);
int dai_macFidEntryPortGet(uint8_t *mac, uint8_t fid, uint32_t *port);
int dai_macVidEntryPortGet(uint8_t *mac, uint16_t vid, uint32_t *port);
int dai_mirrorSet(uint32_t src, uint32_t dst, SW_MIR_MODE_T mode);
int dai_portPbitSet(uint8_t port, uint8_t pbit);
int dai_portPbitGet(uint8_t port);
int dai_macCleanByVid(uint16_t vid);
int dai_macCleanByFid(uint8_t fid);
int dai_macCleanByPort(uint8_t port);
int dai_mirrorGet(uint32_t src, SW_MIR_MODE_T *mode);
int dai_vlanDelete(uint16_t vid);
int dai_vlanPortModeSet(uint8_t port, SW_VLAN_PORT_MODE_T mode);
SW_VLAN_PORT_MODE_T dai_vlanPortModeGet(uint8_t port);
int dai_hwnat_clear(void);
int dai_aclMulticastVlanInit(uint8_t enable);
void dai_readEthInterrupt();
void dai_ethInterruptInit();

#endif
