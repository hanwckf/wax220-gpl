#ifndef __QOS_H__
#define __QOS_H__
#include "fwk/fwk.h"

typedef enum {
  DYNAMIC_QOS_BANDWIDTH_TYPE_AUTO = 0,
  DYNAMIC_QOS_BANDWIDTH_TYPE_MANUAL = 1,
  DYNAMIC_QOS_BANDWIDTH_TYPE_MAX
} DYNAMIC_QOS_BANDWIDTH_TYPE_E;

typedef enum {
  DYNAMIC_QOS_IMPROVE_SERVICE_DISABLED = 0,
  DYNAMIC_QOS_IMPROVE_SERVICE_ENABLED = 1,
  DYNAMIC_QOS_IMPROVE_SERVICE_NOT_SELECT = 2,
  DYNAMIC_QOS_IMPROVE_SERVICE_MAX
} DYNAMIC_QOS_IMPROVE_SERVICE_E;

int dai_getQosStatus(int *qosEnable);
int dai_setDynamicQosEnable(UBOOL8 enable, UBOOL8 commit);
UBOOL8 dai_getDynamicQosEnable();
int dai_setDynamicQosBandwidthType(DYNAMIC_QOS_BANDWIDTH_TYPE_E type, UBOOL8 commit);
DYNAMIC_QOS_BANDWIDTH_TYPE_E dai_getDynamicQosBandwidthType();
int dai_setDynamicQosUplink(UINT32 uplink, UBOOL8 commit);
UINT32 dai_getDynamicQosUplink();
int dai_setDynamicQosDownlink(UINT32 downlink, UBOOL8 commit);
UINT32 dai_getDynamicQosDownlink();
int dai_setDynamicQosAutoUpdateEnable(UBOOL8 enable, UBOOL8 commit);
UBOOL8 dai_getDynamicQosAutoUpdateEnable();
int dai_setDynamicQosUpdateAgreement(UBOOL8 agreement, UBOOL8 commit);
UBOOL8 dai_getDynamicQosUpdateAgreement();
int dai_setDynamicQosFirstFlag(int firstFlag, UBOOL8 commit);
int dai_getDynamicQosFirstFlag();
int dai_setDynamicQosImproveService(DYNAMIC_QOS_IMPROVE_SERVICE_E improveService, UBOOL8 commit);
DYNAMIC_QOS_IMPROVE_SERVICE_E dai_getDynamicQosImproveService();
int dai_setSpeedTestLatest_test_time(time_t ts, UBOOL8 commit);
time_t dai_getSpeedTestLatest_test_time();
int dai_commitDynamicQos();

#endif
