#ifndef __HAL_SYS_H__
#define __HAL_SYS_H__

#define HAL_FENV_MAC  "mac"
#define HAL_UENV_LANGUAGE  "language"

#define HAL_128MBFLASHMEMORY  128
#define HAL_256MBFLASHMEMORY  256

#define HAL_LED_POWER_STATE_RESET 2
#define HAL_LED_POWER_STATE_ON 1
#define HAL_LED_POWER_STATE_OFF 0


#define HAL_LED_CONTROL_SCRIPT "/sbin/led.sh"
#define HAL_LED_INIT_SCRIPT "/etc/init.d/led"
#define HAL_LED_COLORCONTROL_SCRIPT "/sbin/ledColorControl.sh"

#if defined(CUSTOMER_MODEL_WAX214v2)
#define GPIO_BASE 0
#elif defined(CUSTOMER_MODEL_WAX220)
#define GPIO_BASE 411
#else
#endif

int hal_sysGetFactoryEnv(const char *name, char *value, int valueLen);
int hal_sysSetFactoryEnv(const char *name, const char *value);

int hal_sysGetUserEnv(const char *name, char *value, int valueLen);
int hal_sysSetUserEnv(const char *name, const char *value);

int hal_sysRestoreFactory();
int hal_sysGetRestoreFactoryStatus();
int hal_sysIsOrNotRestoreStatus(void);
unsigned long hal_sysGetFlashMemory();
int hal_sysLedOn(const char *ledName, const char *color);
int hal_sysLedOff(const char *ledName, const char *color);
int hal_sysSetGreenLedOn(void);
int hal_sysSetRedLedOn(void);
int hal_sysLedBlink(const char *ledName, const char *color, int delayOn, int delayOff);
int hal_sysSyncLedCtrlMode(void);
int hal_gpioInit(UINT32 gpioNum);
int hal_setGpioDirection(const char* direction, UINT32 gpioNum);
int hal_getGpioValue(UINT32 gpioNum, int *gpioValue);
int hal_unExportGpio(UINT32 gpioNum);
void hal_sysGetLanInter(char *value, int valueLen);
void hal_sysGetModel(char *value, int valueLen);
int hal_sysGetGpio(const char *gpioName);
int hal_setMgmtVlanConfig(UBOOL8 mgmtVlanEnable, int mgmtVlan);

#endif
