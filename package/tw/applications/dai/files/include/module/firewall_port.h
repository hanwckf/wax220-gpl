#ifndef __FIREWALL_PORT_H__
#define __FIREWALL_PORT_H__
#include "fwk/fwk.h"


#define FOREWALL_PORT_FORWRAD_MAX_RULE 64
#define FOREWALL_PORT_TRIGGER_MAX_RULE 20

typedef struct{
    char service_name[BUFLEN_32];
    char protocol[BUFLEN_32];
    char exter_port[BUFLEN_256 + BUFLEN_1];
    char internal_port[BUFLEN_256 + BUFLEN_1];
    char dest_ip[BUFLEN_32];
    unsigned int use_same_range;
} FIREWALL_PORT_FORWARDING_T;

#define PORTTRIGGERING_TIMEOUT_DEFAULT 1200

typedef struct{
    UBOOL8  enabled;
    char    service_ip[BUFLEN_32];
    char    service_name[BUFLEN_128];
    UINT32  service_user;
    char    proto[BUFLEN_32];
    UINT32  trigger_port;
    UINT32  open_portstart;
    UINT32  open_portend;
    char    open_proto[BUFLEN_32];
} FIREWALL_PORT_TRIGGERING_T;


typedef struct{
    char name[BUFLEN_32];
    char proto[BUFLEN_32];
    char src[BUFLEN_32];
    char dest_port[BUFLEN_32];
    char target[BUFLEN_32];
   // add more
} FIREWALL_RULE_CONFIG_T;


typedef struct{
    char name[BUFLEN_32];
    char proto[BUFLEN_32];
    char src[BUFLEN_32];
    char dest[BUFLEN_32];
    char mac[BUFLEN_32];
    char target[BUFLEN_32];
} FIREWALL_ACCESS_CONTROL_CONFIG_T;


typedef enum
{
    NAT_FILTERING_TYPE_SECURED,
    NAT_FILTERING_TYPE_OPEN,
    NAT_FILTERING_TYPE_NUM,
} NAT_FILTERING_TYPE_T;

int dai_addPortForward_config(FIREWALL_PORT_FORWARDING_T *port_forwarding_cfg);
int dai_getPortForward_config(FIREWALL_PORT_FORWARDING_T *port_forwarding_cfg, int rulnum);
int dai_editPortForward_config(FIREWALL_PORT_FORWARDING_T *port_forwarding_cfg, int rulnum);
int dai_delPortForward_config(int devnum);
int dai_setDmzIpAddress(char *ip_str);
int dai_getDmzIp(char *ip, int len);
int dai_setNatFiltering(NAT_FILTERING_TYPE_T type);
NAT_FILTERING_TYPE_T dai_getNatFiltering(void);
int dai_setPort_forwardtrigger_webuse(int webuse);
int dai_getPort_forwardtrigger_webuse(int *webuse);
int dai_setfirewallRule(FIREWALL_RULE_CONFIG_T *firewallrlueconfig);
int dai_getfirewallRule(FIREWALL_RULE_CONFIG_T *firewallrlueconfig, int keynumber);
int dai_setAllowPing(const char *src_name, uint8_t enable);
int dai_getAllowPing(const char *src_name, uint8_t *enable);
int dai_setDosAttackEnable(int enableDosAttack);
int dai_getDosAttackEnable(int *enableDosAttack);

int dai_setfirewallAccessControlRule(FIREWALL_ACCESS_CONTROL_CONFIG_T *accesscontrolconfig);
int dai_getfirewallAccessControlRule(FIREWALL_ACCESS_CONTROL_CONFIG_T *accesscontrolconfig, int keynumber);
int dai_delfirewallAccessControlRule(int devnum);

void dai_firewallReload();

int dai_getTriggerCount(void);
int dai_enablePortTrigger(const char *type, UBOOL8 enable);
int dai_getTriggerEnable(UBOOL8 *enable);
int dai_getTriggering_timeout(int *timeout);
int dai_setTriggering_timeout(int timeout);
int dai_setColumnTriggerEnable(int column, UBOOL8 enable);
int dai_addPorttrigger_config(FIREWALL_PORT_TRIGGERING_T *port_triggering_cfg);
int dai_getPortTrigger_config(FIREWALL_PORT_TRIGGERING_T *port_triggering_cfg, int rulnum);
int dai_editPortTrigger_config(FIREWALL_PORT_TRIGGERING_T *port_triggering_cfg, int rulnum);
int dai_delPortTrigger_config(int devnum);

#endif
