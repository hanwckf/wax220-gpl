#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <lua.h>							   /* Always include this */
#include <lauxlib.h>						   /* Always include this */
#include <lualib.h>							/* Always include this */
/* MAP related includes */
#include "mapd_interface_ctrl.h"

#define dump_file_path "/tmp/dump.txt"

/* MAP related function declarations */
int triggerMandateSteeringOnAgent(lua_State *L);
int triggerBackhaulSteeringOnAgent(lua_State *L);
int triggerWpsFhAgent(lua_State *L);
int triggerMultiApOnBoarding(lua_State *L);
int triggerUplinkApSelection(lua_State *L);
int getRuntimeTopology(lua_State *L);
int getClientCapabilities(lua_State *L);
int getApCapabilities(lua_State *L);
int getDeviceRole(lua_State *L);
int getBhConnectionStatus(lua_State *L);
int applyApSteerRssiTh(lua_State *L);
int applyChannelUtilizationTh(lua_State *L);
int applyBssConfigRenew(lua_State *L);
int getApBhInfList(lua_State *L);
int getApFhInfList(lua_State *L);
int applyWifiBhPriority(lua_State *L);
int applyForceChSwitch(lua_State *L);
int applyUserPreChannel(lua_State *L);
int triggerChPlanningR2(lua_State *L);
int triggerDeDump(lua_State *L);
int getDataElement(lua_State *L);
int triggerChannelScan(lua_State *L);
int getChannelStats(lua_State *L);
int getChannelPlanningScore(lua_State *L);
int getUserPreferredChannel(lua_State *L);


#ifdef MAP_R3

int getSpRuleList(lua_State *L);
int delSpRule(lua_State *L);
int reorderSpRule(lua_State *L);
int moveSpRule(lua_State *L);
int addSpRule(lua_State *L);
int applySpConfig(lua_State *L);
#endif
/* Logging facility */
void log_c(int line, char *fmt,...);
#define LOG_C(...) log_c(__LINE__, __VA_ARGS__ )
int logDisable = 1;

int luaopen_map_helper(lua_State *L)
{
	lua_register(L,"c_get_device_role",getDeviceRole);
	lua_register(L,"c_trigger_mandate_steering_on_agent",triggerMandateSteeringOnAgent);
	lua_register(L,"c_trigger_back_haul_steering_on_agent",triggerBackhaulSteeringOnAgent);
	lua_register(L,"c_trigger_wps_fh_agent",triggerWpsFhAgent);
	lua_register(L,"c_trigger_multi_ap_on_boarding",triggerMultiApOnBoarding);
	lua_register(L,"c_trigger_uplink_ap_selection",triggerUplinkApSelection);
	lua_register(L,"c_get_runtime_topology",getRuntimeTopology);
	lua_register(L,"c_get_client_capabilities",getClientCapabilities);
	lua_register(L,"c_get_bh_connection_status",getBhConnectionStatus);
	lua_register(L,"c_apply_ap_steer_rssi_th",applyApSteerRssiTh);
	lua_register(L,"c_apply_channel_utilization_th",applyChannelUtilizationTh);
	lua_register(L,"c_apply_bss_config_renew",applyBssConfigRenew);
	lua_register(L,"c_get_ap_bh_inf_list",getApBhInfList);
	lua_register(L,"c_get_ap_fh_inf_list",getApFhInfList);
	lua_register(L,"c_apply_wifi_bh_priority",applyWifiBhPriority);
	lua_register(L,"c_apply_force_ch_switch",applyForceChSwitch);
	lua_register(L,"c_apply_user_preferred_channel",applyUserPreChannel);
	lua_register(L,"c_trigger_channel_planning_r2",triggerChPlanningR2);
	lua_register(L,"c_trigger_de_dump",triggerDeDump);
	lua_register(L,"c_get_data_element",getDataElement);
	lua_register(L,"c_trigger_channel_scan",triggerChannelScan);
	lua_register(L,"c_get_channel_stats",getChannelStats);
	lua_register(L,"c_get_channel_planning_score",getChannelPlanningScore);
	lua_register(L,"c_get_user_preferred_channel",getUserPreferredChannel);

#ifdef MAP_R3
	lua_register(L,"c_get_sp_rule_list",getSpRuleList);
	lua_register(L,"c_del_sp_rule",delSpRule);
	lua_register(L,"c_sp_rule_reorder",reorderSpRule);
	lua_register(L,"c_sp_rule_move",moveSpRule);
	lua_register(L,"c_sp_rule_add",addSpRule);
	lua_register(L,"c_sp_config_done",applySpConfig);
#endif
	return 0;
}

void log_c(int line, char *fmt,...)
{
	va_list list;
	FILE *fp;
	char *p, *r;
	int e;

	if (logDisable == 1){
		return;
	}
	fp = fopen("/tmp/log_ui_map","a+");
	if(fp == NULL){
		return;
	}

	fprintf(fp,"[%d] ",line);
	va_start(list, fmt);

	for(p = fmt; *p; ++p){
		if(*p != '%'){
			fputc(*p,fp);
		}
		else{
			switch (*++p){
				/* string */
				case 's':
					r = va_arg(list, char*);
					fprintf(fp, "%s", r);
					continue;
				/* integer */
				case 'd':
					e = va_arg(list, int);
					fprintf(fp, "%d", e);
					continue;
				default:
					fputc(*p, fp);
			}
		}
	}
	va_end(list);
	fputc('\n', fp);
	fclose(fp);
}

int triggerMandateSteeringOnAgent(lua_State *L)
{
	const char *mac_addr = luaL_checkstring(L, 1);
	const char *bssid = luaL_checkstring(L, 2);
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;

	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_mandate_steer(ctrl, mac_addr, bssid);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_mandate_steer API Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_mandate_steer API Failed \n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int triggerBackhaulSteeringOnAgent(lua_State *L)
{
	const char *bh_mac_addr = luaL_checkstring(L, 1);
	const char *bh_target_mac_addr = luaL_checkstring(L, 2);
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;

	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_bh_steer(ctrl, bh_mac_addr, bh_target_mac_addr);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_bh_steer API Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_bh_steer API Failed \n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int triggerWpsFhAgent(lua_State *L)
{
	const char *fh_mac_addr = luaL_checkstring(L, 1);
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;

	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_trigger_map_wps(ctrl, fh_mac_addr);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_trigger_map_wps API returned -1!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_trigger_map_wps API Failed \n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int triggerMultiApOnBoarding(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *ifmed = luaL_checkstring(L, 1);
	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_trigger_onboarding(ctrl, ifmed); /* ifmed: 1 - Wireless and 0 - Ethernet */
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_trigger_onboarding API returned -1!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_trigger_onboarding API returned -1\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int triggerUplinkApSelection(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	lua_newtable(L);
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	ret = mapd_interface_select_best_ap(ctrl);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int getRuntimeTopology(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	char bufStr[128] = {0};
	char cmd[100] = {0};
	char *reply = NULL;
	const int reply_size = 40960;
	size_t len = sizeof(reply);
	int ret = 0, index = 1;
	int fsize = 0, fread_ret = 0;
	FILE *fptr = NULL;
	char *topo_buf = NULL;

	lua_newtable(L);
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);
	if (!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		goto out;
	}

	reply = (char *)malloc(reply_size);
	if (!reply)
		goto out;

	memset(reply, 0, reply_size);

	snprintf(cmd, sizeof(cmd), "dump_topology_v1 %d %s", index, dump_file_path);
	ret = mapd_interface_ctrl_request(ctrl, cmd, strlen(cmd), reply, &len, NULL);
	if (ret < 0) {
		goto out;
	}

	fptr = fopen(dump_file_path, "r");
	if (fptr == NULL) {
		log_c(__LINE__, "fptr is null\n");
		goto out;
	}

	fseek(fptr, 0, SEEK_END);
	fsize = ftell(fptr);
	if (fsize <= 0) {
		fclose(fptr);
		goto out;
	}

	size_t buf_len = fsize + 1;
	topo_buf = (char *)malloc(buf_len);

	if (!topo_buf) {
		perror("Memory allocation failed");
		fclose(fptr);
		goto out;
	}
	
	fseek(fptr, 0, SEEK_SET);
	fread_ret = fread(topo_buf, fsize, 1, fptr);
	if (!fread_ret) {
		log_c(__LINE__, "Failed to read MAP topology information\n");
		fclose(fptr);
		goto out;
	}
	fclose(fptr);

	lua_pushstring(L, "status");  /* push key */
	lua_pushstring(L, "SUCCESS");  /* push value */
	lua_settable(L, -3);
	lua_pushstring(L, "luaTopologyInfo");  /* push key */
	lua_pushstring(L, topo_buf);  /* push value */
	lua_settable(L, -3);
	snprintf(bufStr, sizeof(bufStr), "%d", fsize);
	lua_pushstring(L, "luaTopologyInfoLen");  /* push key */
	lua_pushstring(L, bufStr);  /* push value */
	lua_settable(L, -3);
	log_c(__LINE__, "[map_helper] %s SUCCESS: %s \n\n", __FUNCTION__, topo_buf);

out:
	if (ctrl)
		mapd_interface_ctrl_close(ctrl);
	if (reply)
		free(reply);
	if (topo_buf)
		free(topo_buf);
	
	return 1;
}

int triggerDeDump(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *almac = luaL_checkstring(L, 1);
	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_trigger_de_dump(ctrl, almac);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int getDataElement(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	char bufStr[512] = {0};
	size_t buf_len = 102400;
	char *data_element_buf = (char *)calloc(buf_len, sizeof(char));
	if (!data_element_buf) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	lua_newtable(L);
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);

		goto out;
	}
	ret = mapd_interface_get_de_dump(ctrl, data_element_buf, &buf_len, NULL);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == 0){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		lua_pushstring(L, "luaDataElementInfo");  /* push key */
		lua_pushstring(L, data_element_buf);  /* push value */
		lua_settable(L, -3);
		snprintf(bufStr, sizeof(bufStr), "%zu",buf_len);
		lua_pushstring(L, "luaDataElementInfoLen");  /* push key */
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS: %s \n\n", __FUNCTION__, data_element_buf);
	}
	else{
		snprintf(bufStr, sizeof(bufStr), "Error: %d",ret);
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s fail  error: %d \n\n", __FUNCTION__, ret);
	}
	mapd_interface_ctrl_close(ctrl);
out:
	free(data_element_buf);
	return 1;
}

int getClientCapabilities(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	struct client_db *cli_dbs = NULL;
	int num_clis, cli_idx, max_bw_idx, bit_idx;
	char bufStr[128] = {0};
	char tmpStr[128] = {0};
	size_t cli_db_buf_len = 15360;
	char *cli_db_buf = (char *)calloc(cli_db_buf_len, sizeof(char));
	if (!cli_db_buf) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_newtable(L);
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);

		goto out;
	}
	num_clis = mapd_interface_get_client_db(ctrl, (struct client_db*)cli_db_buf, &cli_db_buf_len);
	if(num_clis < 0){
		lua_newtable(L);
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);

		goto out;
	}
	else if(num_clis == 0){
		lua_newtable(L);
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "No Clients Available");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s No Clients Available\n\n", __FUNCTION__);

		goto out;
	}
	else{
		lua_newtable(L);
		lua_pushstring(L, "num_clis");  /* push key */
		snprintf(bufStr, sizeof(bufStr), "%d", num_clis);
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "cli_db");  /* push key */

		/* Create parent table of size as num_clis sub-tables */
		lua_createtable(L, 0, num_clis);

		cli_dbs = (struct client_db*)cli_db_buf;

		for(cli_idx=0; cli_idx < num_clis; cli_idx++){
			snprintf(bufStr, sizeof(bufStr), "%d", cli_idx);
			lua_pushstring(L, bufStr);

			/* Create child non-sequence table of size as per struct client_db */
			lua_createtable(L, 0, 9);

			// MAC Address
			snprintf(bufStr, sizeof(bufStr), "%02X:%02X:%02X:%02X:%02X:%02X",
			cli_dbs[cli_idx].mac[0], cli_dbs[cli_idx].mac[1],
			cli_dbs[cli_idx].mac[2], cli_dbs[cli_idx].mac[3],
			cli_dbs[cli_idx].mac[4], cli_dbs[cli_idx].mac[5]);
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "MAC");

			// BSSID
			snprintf(bufStr, sizeof(bufStr), "%02X:%02X:%02X:%02X:%02X:%02X",
			cli_dbs[cli_idx].bssid[0], cli_dbs[cli_idx].bssid[1],
			cli_dbs[cli_idx].bssid[2], cli_dbs[cli_idx].bssid[3],
			cli_dbs[cli_idx].bssid[4], cli_dbs[cli_idx].bssid[5]);
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "BSSID");

			// Capability
			bufStr[0] = '\0';
			for(bit_idx=0; bit_idx < 4; bit_idx++){
				if(cli_dbs[cli_idx].capab & (1 << bit_idx)){
					switch(bit_idx){
						case 0:
							strncat(bufStr,
									"DOT11K_SUPPORTED, ",
									sizeof(bufStr) - strlen(bufStr) - 1);
						break;
						case 1:
							strncat(bufStr,
									"DOT11V_SUPPORTED, ",
									sizeof(bufStr) - strlen(bufStr) - 1);
						break;
						case 2:
							strncat(bufStr,
									"DOT11R_SUPPORTED, ",
									sizeof(bufStr) - strlen(bufStr) - 1);
						break;
						case 3:
						default:
							strncat(bufStr,
									"MBO_SUPPORTED, ",
									sizeof(bufStr) - strlen(bufStr) - 1);
						break;
					}
				}
			}
			if(bufStr[0] == '\0'){
				snprintf(bufStr, sizeof(bufStr), "N/A");
			}
			else{
				bufStr[strlen(bufStr) - 2] = '\0'; //Remove last comma and space character
			}
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "Capability");

			// Phy Mode
			switch(cli_dbs[cli_idx].phy_mode){
				case 0:
					snprintf(bufStr, sizeof(bufStr), "CCK");
				break;
				case 1:
					snprintf(bufStr, sizeof(bufStr), "OFDM");
				break;
				case 2:
					snprintf(bufStr, sizeof(bufStr), "HTMIX");
				break;
				case 3:
					snprintf(bufStr, sizeof(bufStr), "GREENFIELD");
				break;
				case 4:
					snprintf(bufStr, sizeof(bufStr), "VHT");
				break;
				default:
					snprintf(bufStr, sizeof(bufStr), "N/A");
			}
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "Phy Mode");

			// Max. Bandwidth 0 and Max. Bandwidth 1
			for(max_bw_idx=0; max_bw_idx < 2; max_bw_idx++){
				switch(cli_dbs[cli_idx].max_bw[max_bw_idx]){
					case 0:
						snprintf(bufStr, sizeof(bufStr), "20");
					break;
					case 1:
						snprintf(bufStr, sizeof(bufStr), "40");
					break;
					case 2:
						snprintf(bufStr, sizeof(bufStr), "80");
					break;
					case 3:
						snprintf(bufStr, sizeof(bufStr), "160");
					break;
					case 4:
						snprintf(bufStr, sizeof(bufStr), "10");
					break;
					case 5:
						snprintf(bufStr, sizeof(bufStr), "5");
					break;
					case 6:
						snprintf(bufStr, sizeof(bufStr), "8080");
					break;
					default:
						snprintf(bufStr, sizeof(bufStr), "N/A");
				}
				lua_pushstring(L, bufStr);
				snprintf(bufStr, sizeof(bufStr), "Max. Bandwidth %d",max_bw_idx);
				lua_setfield(L, -2, (const char*)bufStr);
			}

			// Spatial Stream
			snprintf(bufStr, sizeof(bufStr), "%d", cli_dbs[cli_idx].spatial_stream);
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "Spatial Stream");

			// Known Band
			bufStr[0] = '\0';
			for(bit_idx=0; bit_idx < 2; bit_idx++){
				if(cli_dbs[cli_idx].know_band & (1 << bit_idx)){
					switch(bit_idx){
						case 0:
							strncat(bufStr,
									"2GHz, ",
									sizeof(bufStr) - strlen(bufStr) - 1);
						break;
						case 1:
						default:
							strncat(bufStr,
									"5GHz, ",
									sizeof(bufStr) - strlen(bufStr) - 1);
						break;
					}
				}
			}
			if(bufStr[0] == '\0'){
				snprintf(bufStr, sizeof(bufStr), "N/A");
			}
			else{
				bufStr[strlen(bufStr) - 2] = '\0'; //Remove last comma and space character
			}
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "Known Band");

			// Known Channels
			bufStr[0] = '\0';
			for (bit_idx = 0; bit_idx < 38; bit_idx++) {
				if (cli_dbs[cli_idx].know_channels[bit_idx / 8] & (1 << (bit_idx % 8))) {
					if (bit_idx >= 0 && bit_idx <= 13){
						snprintf(tmpStr, sizeof(tmpStr), "%d, ", bit_idx + 1);
						strncat(bufStr,
								tmpStr,
								sizeof(bufStr) - strlen(bufStr) - 1);
					}
					else if (bit_idx >= 14 && bit_idx <= 21){
						snprintf(tmpStr, sizeof(tmpStr), "%d, ", 36 + ((bit_idx - 14) * 4));
						strncat(bufStr,
								tmpStr,
								sizeof(bufStr) - strlen(bufStr) - 1);
					}
					else if (bit_idx >= 22 && bit_idx <= 32){
						snprintf(tmpStr, sizeof(tmpStr), "%d, ", 100 + ((bit_idx - 22) * 4));
						strncat(bufStr,
								tmpStr,
								sizeof(bufStr) - strlen(bufStr) - 1);
					}
					else if (bit_idx >= 33 && bit_idx <= 37){
						snprintf(tmpStr, sizeof(tmpStr), "%d, ", 149 + ((bit_idx -33) * 4));
						strncat(bufStr,
								tmpStr,
								sizeof(bufStr) - strlen(bufStr) - 1);
					}
				}
			}
			if(bufStr[0] == '\0'){
				snprintf(bufStr, sizeof(bufStr), "N/A");
			}
			else{
				bufStr[strlen(bufStr) - 2] = '\0'; //Remove last comma and space character
			}
			lua_pushstring(L, bufStr);
			lua_setfield(L, -2, "Known Channels");

			lua_settable(L, -3);
			log_c(__LINE__, "[map_helper] %s SUCCESS  bufStr: %s\n\n", __FUNCTION__, bufStr);
		}
		lua_settable(L, -3);
	}
out:
	if (ctrl)
		mapd_interface_ctrl_close(ctrl);
	free(cli_db_buf);
	return 1;
}

int getDeviceRole(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int devRole;
	char devRoleStr[2] = {0};
	int ret;
	lua_newtable(L);
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	if(!ctrl){
		lua_pushstring(L, "mapDevRole");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	ret = mapd_interface_get_role(ctrl,&devRole);
	if(ret == -1){
		lua_pushstring(L, "mapDevRole");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "mapDevRole");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		snprintf(devRoleStr, sizeof(devRoleStr), "%d", devRole);
		lua_pushstring(L, "mapDevRole");  /* push key */
		lua_pushstring(L, devRoleStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s success devRole: %d\n\n", __FUNCTION__, devRole);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int getBhConnectionStatus(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	char conStatus[2] = {0};
	int ret;
	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);
	
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	ret = mapd_interface_bh_ConnectionStatus(ctrl, conStatus);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "conStatus");  /* push key */
		if((int)conStatus[0] == 1){
			lua_pushstring(L, "Connected");  /* push value */
		}
		else{
			lua_pushstring(L, "Disconnected");  /* push value */
		}
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int applyApSteerRssiTh(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *rssi = luaL_checkstring(L, 1);
	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_set_rssi_thresh(ctrl, rssi);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int applyChannelUtilizationTh(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *channelUtilTh2G = luaL_checkstring(L, 1);
	const char *channelUtilTh5GL = luaL_checkstring(L, 2);
	const char *channelUtilTh5GH = luaL_checkstring(L, 3);
	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_set_ChUtil_thresh(ctrl, channelUtilTh2G, channelUtilTh5GL, channelUtilTh5GH);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int applyBssConfigRenew(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_set_renew(ctrl);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int getApBhInfList(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	/* MAX_VIF * MAX_BAND *SIZEOF(MAC_ADDRESS_STRING) + MAX_VIF_NUMBER_OF_SEMI_COLON + NULL CHARACTER
	* 16 * 3 * 17 + 16 + 1 = 833 Bytes. Rounding to 900 Bytes
	*/
	char mac_buf[900]={0};
	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_get_bh_ap(ctrl, mac_buf);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		lua_pushstring(L, "macList");  /* push key */
		lua_pushstring(L, mac_buf);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  mac_buf: %s\n\n", __FUNCTION__, mac_buf);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int getApFhInfList(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	/* MAX_VIF * MAX_BAND *SIZEOF(MAC_ADDRESS_STRING) + MAX_VIF_NUMBER_OF_SEMI_COLON + NULL CHARACTER
	* 16 * 3 * 17 + 16 + 1 = 833 Bytes. Rounding to 900 Bytes
	*/
	char mac_buf[900]={0};
	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_get_fh_ap(ctrl, mac_buf);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		lua_pushstring(L, "macList");  /* push key */
		lua_pushstring(L, mac_buf);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  mac_buf: %s\n\n", __FUNCTION__, mac_buf);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}


int applyWifiBhPriority(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *BhPriority2G = luaL_checkstring(L, 1);
	const char *BhPriority5GL = luaL_checkstring(L, 2);
	const char *BhPriority5GH = luaL_checkstring(L, 3);

	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_set_bh_priority(ctrl, BhPriority2G, BhPriority5GL, BhPriority5GH);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int applyForceChSwitch(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *almac = luaL_checkstring(L, 1);
	const char *channel1 = luaL_checkstring(L, 2);
	const char *channel2 = luaL_checkstring(L, 3);
	const char *channel3 = luaL_checkstring(L, 4);
	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_forceChSwitch(ctrl, almac, channel1, channel2, channel3);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int applyUserPreChannel(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *channel = luaL_checkstring(L, 1);
	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_user_preferred_channel(ctrl, channel);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int triggerChPlanningR2(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *band = luaL_checkstring(L, 1);
	lua_newtable(L);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_trigger_ch_plan_R2(ctrl, band);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else if(ret == -3){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Try again!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Try Again\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int triggerChannelScan(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	const char *almac = luaL_checkstring(L, 1);
	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ret = mapd_interface_trigger_ch_scan(ctrl, almac);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == -2){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Timed-out!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Timed-out\n\n", __FUNCTION__);
	}
	else if(ret == -3){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Try again!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Try Again\n\n", __FUNCTION__);
	}
	else{
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS  \n\n", __FUNCTION__);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int getChannelStats(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	char bufStr[128] = {0};
	size_t buf_len = 24576;
	char *channel_stats_buf = (char *)calloc(buf_len, sizeof(char));
	if (!channel_stats_buf) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	lua_newtable(L);
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);

		goto out;
	}
	ret = mapd_interface_get_ch_scan_dump(ctrl, channel_stats_buf, &buf_len, NULL);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == 0){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		lua_pushstring(L, "luaChannelStatsInfo");  /* push key */
		lua_pushstring(L, channel_stats_buf);  /* push value */
		lua_settable(L, -3);
		snprintf(bufStr, sizeof(bufStr), "%zu",buf_len);
		lua_pushstring(L, "luaChannelStatsInfoLen");  /* push key */
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS: %s \n\n", __FUNCTION__, channel_stats_buf);
	}
	else{
		snprintf(bufStr, sizeof(bufStr), "Error: %d",ret);
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s fail  error: %d \n\n", __FUNCTION__, ret);
	}
	mapd_interface_ctrl_close(ctrl);
out:
	free(channel_stats_buf);
	return 1;
}

int getChannelPlanningScore(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	int ret;
	char bufStr[128] = {0};
	size_t buf_len = 10240;
	char *channel_planning_buf = (char *)calloc(buf_len, sizeof(char));
	if (!channel_planning_buf) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	lua_newtable(L);
	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);
	if(!ctrl){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);

		goto out;
	}
	ret = mapd_interface_get_ch_score_dump(ctrl, channel_planning_buf, &buf_len, NULL);
	if(ret == -1){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	}
	else if(ret == 0){
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		lua_pushstring(L, "luaChannelPlanningInfo");  /* push key */
		lua_pushstring(L, channel_planning_buf);  /* push value */
		lua_settable(L, -3);
		snprintf(bufStr, sizeof(bufStr), "%zu",buf_len);
		lua_pushstring(L, "luaChannelPlanningInfoLen");  /* push key */
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS: %s \n\n", __FUNCTION__, channel_planning_buf);
	}
	else{
		snprintf(bufStr, sizeof(bufStr), "Error: %d",ret);
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s fail  error: %d \n\n", __FUNCTION__, ret);
	}
	mapd_interface_ctrl_close(ctrl);
out:
	free(channel_planning_buf);
	return 1;
}


int getUserPreferredChannel(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	struct mapd_inteface_skip_channel_list *lists = NULL;
	char conStatus[2] = {0};
	char bufStr[128] = {0};
	int ret;

	size_t buf_len = 10240;
	char *buf = (char *)calloc(buf_len, sizeof(char));
	if (!buf) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		goto out;
	}
	
	ret = mapd_interface_get_skip_list(ctrl, (struct mapd_inteface_skip_channel_list*)buf);
	lists = (struct mapd_inteface_skip_channel_list*)buf;
	
	log_c(__LINE__, "[map_helper] %s preferredListNum: %d  \n\n", __FUNCTION__, lists->preferredListNum);
	log_c(__LINE__, "[map_helper] %s AutoChannelSkipListNum: %d  \n\n", __FUNCTION__, lists->AutoChannelSkipListNum);

	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "AutoChannelSkipListNum");  /* push key */
		snprintf(bufStr, sizeof(bufStr), "%d", lists->AutoChannelSkipListNum);
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "AutoChannelSkipList");  /* push key */
		lua_newtable(L);
		for (int bit_idx = 0; bit_idx < lists->AutoChannelSkipListNum; bit_idx++) {

			snprintf(bufStr, sizeof(bufStr), "%s%d", "Channel", bit_idx);
			lua_pushstring(L, bufStr);  /* push key */
			snprintf(bufStr, sizeof(bufStr), "%d", lists->AutoChannelSkipList[bit_idx]);
			lua_pushstring(L, bufStr);  /* push value */
			lua_settable(L, -3);
		}
		lua_settable(L, -3);

		lua_pushstring(L, "preferredListNum");  /* push key */
		snprintf(bufStr, sizeof(bufStr), "%d", lists->preferredListNum);
		lua_pushstring(L, bufStr);  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "preferredList");  /* push key */
		lua_newtable(L);
		for (int bit_idx = 0; bit_idx < lists->preferredListNum; bit_idx++) {
			snprintf(bufStr, sizeof(bufStr), "%s%d", "Channel", bit_idx);
			lua_pushstring(L, bufStr);  /* push key */
			snprintf(bufStr, sizeof(bufStr), "%d", lists->preferredList[bit_idx]);
			lua_pushstring(L, bufStr);  /* push value */
			lua_settable(L, -3);
		}
		lua_settable(L, -3);

		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
out:
	free(buf);
	return 1;
}

#ifdef MAP_R3

int getSpRuleList(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	char conStatus[2] = {0};
	int ret;

	size_t buf_len = 10240;
	char *buf = (char *)calloc(buf_len, sizeof(char));
	if (!buf) {
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	lua_newtable(L);
	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		goto out;
	}
	ret = mapd_interface_sp_get_rule(ctrl, 0, buf, &buf_len);
	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);

		lua_pushstring(L, "rules");  /* push key */
		lua_pushstring(L, buf);

		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);

out:
	free(buf);
	return 1;
}

int delSpRule(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	const char *c_index = luaL_checkstring(L, 1);
	char conStatus[2] = {0};
	int index = 0;
	int ret;

	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	index = atoi(c_index);

	if (index < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "wrong index!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	ret = mapd_interface_sp_rm_rule(ctrl, index);
	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int reorderSpRule(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	const char *c_index_org = luaL_checkstring(L, 1);
	const char *c_index_new = luaL_checkstring(L, 2);
	char conStatus[2] = {0};
	int index_org = 0, index_new = 0;
	int ret;

	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	index_org = atoi(c_index_org);
	index_new = atoi(c_index_new);

	if (index_org < 0 || index_new < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "wrong index!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	ret = mapd_interface_sp_reorder_rule(ctrl, index_org, index_new);
	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int moveSpRule(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	const char *c_index_org = luaL_checkstring(L, 1);
	const char *c_action = luaL_checkstring(L, 2);
	char conStatus[2] = {0};
	int index_org = 0, action = 0;
	int ret = 0;

	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	index_org = atoi(c_index_org);
	action = atoi(c_action);

	if (index_org < 0 || action < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "wrong index!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}

	if (action == 0)
		ret = mapd_interface_sp_move_rule_forward(ctrl, index_org);
	else if (action == 1)
		ret = mapd_interface_sp_move_rule_backward(ctrl, index_org);

	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int addSpRule(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	const char *str_rule = luaL_checkstring(L, 1);
	char conStatus[2] = {0};
	int rule_len = 0;
	int ret;

	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	rule_len = strlen(str_rule);

	ret = mapd_interface_sp_add_rule(ctrl, str_rule, rule_len);

	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}

int applySpConfig(lua_State *L)
{
	struct mapd_interface_ctrl *ctrl = NULL;
	char conStatus[2] = {0};
	int ret;

	log_c(__LINE__, "[map_helper] %s enter\n", __FUNCTION__);

	ctrl = mapd_interface_ctrl_open("/tmp/mapd_ctrl");
	if (!ctrl) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "mapd_interface_ctrl_open failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s mapd_interface_ctrl_open failed\n\n", __FUNCTION__);
		return 1;
	}
	ret = mapd_interface_sp_config_done(ctrl);

	if (ret < 0) {
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "Command Failed!");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s Command Failed\n\n", __FUNCTION__);
	} else {
		conStatus[1] = '\0';
		lua_pushstring(L, "status");  /* push key */
		lua_pushstring(L, "SUCCESS");  /* push value */
		lua_settable(L, -3);
		log_c(__LINE__, "[map_helper] %s SUCCESS conStatus: %d \n\n", __FUNCTION__, conStatus[0]);
	}
	mapd_interface_ctrl_close(ctrl);
	return 1;
}
#endif
