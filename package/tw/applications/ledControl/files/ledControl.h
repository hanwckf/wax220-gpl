#ifndef __LEDCONTROL_H__
#define __LEDCONTROL_H__

enum ledstate{
    LED_STATE_OFF,
    LED_STATE_GREEN_ON,
    LED_STATE_GREEN_OFF,
    LED_STATE_GREEN_BLIK,
    LED_STATE_BLUE_ON,
    LED_STATE_BLUE_OFF,
    LED_STATE_BLUE_BLIK,
    LED_STATE_AMBER_ON,
    LED_STATE_AMBER_OFF,
    LED_STATE_AMBER_BLIK,
    LED_STATE_LAN_RED_ON,
    LED_STATE_LAN_RED_OFF,
    LED_STATE_LAN_RED_BLIK,
    LED_STATE_GREEN_ON_BLUE_BLIK,
    LED_STATE_MAX
};

typedef struct Lan_RedLed_Stat_
{
    char name[8];
    int port;
    int led_stat;
    unsigned long int trans_package_count;
} Lan_RedLed_Stat;

#define WAX202_LAN_PORT_MAX	3


#endif
