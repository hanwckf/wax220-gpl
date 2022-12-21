#!/bin/sh

RED='\033[0;31m'
NC='\033[0m'
echo -e "----- ${RED}EasyMesh SCRIPT${NC} -----"
check_default="$1"

mode="$2"

if [ -n "$mode" ]
then
	echo "input param2 is $mode"
else
	mode="0"
	echo "input param2 is null, set mode as router mode, mode=$mode"
fi

echo "param1 reserved"
echo "param2 mode=$mode"
echo "param2  0--> router mode on dev"
echo "param2  1--> bridge mode on dev"

ramips_board_name() {
	local name

	[ -f /tmp/sysinfo/board_name ] && name=$(cat /tmp/sysinfo/board_name)
	[ -z "$name" ] && name="unknown"

	echo "${name%-[0-9]*M}"
}

board=$(ramips_board_name)
platform=${board:0:6}
echo "##################################$platform"

clean()
{
	rm -rf /tmp/wapp_ctrl
	killall -15 mapd
	killall -15 wapp
	killall -15 p1905_managerd
	killall -15 bs20
	sleep 5
	rmmod mapfilter
	echo -e "----- ${RED}killed all apps ${NC} -----"
}
#call routine to decide operating mode
get_operating_mode()
{
	card0_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX0_profile_path |awk -F "[=;]" '{ print $2 }'`
	#MapEnable=`cat ${card0_profile_path} | grep MapEnable | awk -F "=" '{ print $2 }'`
	#MapTurnKey=`cat ${card0_profile_path} | grep MAP_Turnkey | awk -F "=" '{ print $2 }'`
	#BSEnable=`cat ${card0_profile_path} | grep BSEnable | awk -F "=" '{ print $2 }'`
	MapMode=`cat ${card0_profile_path} | grep MapMode | awk -F "=" '{ print $2 }'`
	LastMapMode=`cat /etc/map/mapd_default.cfg | grep LastMapMode | awk -F "=" '{ print $2 }'`
	if [ -z ${LastMapMode} ]
	then
	echo "fist start init last_map_mode ${MapMode}"
	LastMapMode="${MapMode}"
	fi
	echo "update last_map_mode ${MapMode}"
	sed -i "s/LastMapMode=.*/LastMapMode=${MapMode}/g" /etc/map/mapd_default.cfg
}
#Function reads interface name from the l1profile
prepare_ifname_card()
{
	echo "$card_idx"
	card_ext_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_ext_ifname |awk -F "=" '{ print $2 }'`
	echo $card_ext_ifname
	card_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_profile_path |awk -F "=" '{ print $2 }'`
	echo $card_profile_path
	card_apcli_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_apcli_ifname |awk -F "=" '{ print $2 }'`
	echo $card_apcli_ifname
	card_main_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname |awk -F "=" '{ print $2 }'`
	card_bssid_num=`cat ${card_profile_path} | grep BssidNum | awk -F "=" '{ print $2 }'`
	echo $card_bssid_num
	iwconfig ${card_main_ifname} | grep "Access Point"
	card_exist=$?
	echo $card_exist
	ifconfig | grep "br" > br_name
	bridge_name=`cat br_name | awk '{ print $1}'`
	if [ $card_exist == 0 ]
	then
		active_cards=`expr $active_cards + 1`
		bssid_num=0
		while [ $bssid_num -lt $card_bssid_num ]
		do
			if [ -z ${if_list} ]
			then
			if_list="${card_ext_ifname}${bssid_num}"
			else
			if_list="${if_list};${card_ext_ifname}${bssid_num}"
			fi
			brctl delif $bridge_name $card_ext_ifname$bssid_num
			brctl addif $bridge_name $card_ext_ifname$bssid_num
			bssid_num=`expr $bssid_num + 1`
		done
		if_list="${if_list};${card_apcli_ifname}0"
		echo ${card_main_ifname} >> main_ifname
		echo ${card_apcli_ifname}"0" >> apcli_ifname
		brctl delif $bridge_name $card_apcli_ifname"0"
		brctl addif $bridge_name $card_apcli_ifname"0"
	fi
	echo $if_list
}
prepare_ifame_band()
{
	card_ext_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_ext_ifname |awk -F "[=;]" '{ print $2 }'`
	echo $card_ext_ifname
	card_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_profile_path |awk -F "[=;]" '{ print $2 }'`
	echo $card_profile_path
	card_apcli_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_apcli_ifname |awk -F "[=;]" '{ print $2 }'`
	echo $card_apcli_ifname
	card_main_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname |awk -F "[=;]" '{ print $2 }'`
	card_bssid_num=`cat ${card_profile_path} | grep BssidNum | awk -F "=" '{ print $2 }'`
	MaxHT_BW2G=`cat $card_profile_path | grep HT_BW |awk -F "[=;]" '{ print $2 }' | awk 'NR==1'`
	echo $card_bssid_num
	iwconfig ${card_main_ifname} | grep "Access Point"
	card_exist=$?
	echo $card_exist
	ifconfig | grep "br" > br_name
	bridge_name=`cat br_name | awk '{ print $1}'`
	if [ $card_exist == 0 ]
	then
		active_cards=`expr $active_cards + 1`
		bssid_num=0
		while [ $bssid_num -lt $card_bssid_num ]
		do
			if [ -z ${if_list} ]
			then
				if_exist=`ifconfig | grep ${card_ext_ifname}${bssid_num}`
				if [ "$if_exist" != "" ]; then
					if_list="${card_ext_ifname}${bssid_num}"
					interface_available=$card_ext_ifname
				fi
			else
				if_exist=`ifconfig | grep ${card_ext_ifname}${bssid_num}`
				if [ "$if_exist" != "" ]; then
					if_list="${if_list};${card_ext_ifname}${bssid_num}"
					interface_available=$card_ext_ifname
				fi
			fi
			brctl delif $bridge_name $card_ext_ifname$bssid_num
			brctl addif $bridge_name $card_ext_ifname$bssid_num
			bssid_num=`expr $bssid_num + 1`
		done
		if [ $interface_available == $card_ext_ifname ]; then
			if_list="${if_list};${card_apcli_ifname}0"
			echo ${card_main_ifname} >> main_ifname
			echo ${card_apcli_ifname}"0" >> apcli_ifname
		fi
		brctl delif $bridge_name $card_apcli_ifname"0"
		brctl addif $bridge_name $card_apcli_ifname"0"
	fi
	echo $if_list
	card_ext_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_ext_ifname |awk -F "[=;]" '{ print $3 }'`
	echo $card_ext_ifname
	card_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_profile_path |awk -F "[=;]" '{ print $3 }'`
	echo $card_profile_path
	card_apcli_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_apcli_ifname |awk -F "[=;]" '{ print $3 }'`
	echo $card_apcli_ifname
	card_main_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname |awk -F "[=;]" '{ print $3 }'`
	card_bssid_num=`cat ${card_profile_path} | grep BssidNum | awk -F "=" '{ print $2 }'`
	MaxVHT_BW5G=`cat $card_profile_path | grep VHT_BW |awk -F "[=;]" '{ print $2 }' | awk 'NR==1'`
	MaxHT_BW5G=`cat $card_profile_path | grep HT_BW |awk -F "[=;]" '{ print $2 }' | awk 'NR==1'`
	echo $card_bssid_num
	iwconfig ${card_main_ifname} | grep "Access Point"
	card_exist=$?
	echo $card_exist
	if [ $card_exist == 0 ]
	then
		active_cards=`expr $active_cards + 1`
		bssid_num=0
		while [ $bssid_num -lt $card_bssid_num ]
		do
			if [ -z ${if_list} ]
			then
				if_exist=`ifconfig | grep ${card_ext_ifname}${bssid_num}`
				if [ "$if_exist" != "" ]; then
					if_list="${card_ext_ifname}${bssid_num}"
					interface_available=$card_ext_ifname
				fi
			else
				if_exist=`ifconfig | grep ${card_ext_ifname}${bssid_num}`
				if [ "$if_exist" != "" ]; then
					if_list="${if_list};${card_ext_ifname}${bssid_num}"
					interface_available=$card_ext_ifname
				fi
			fi
			brctl delif $bridge_name $card_ext_ifname$bssid_num
			brctl addif $bridge_name $card_ext_ifname$bssid_num
			bssid_num=`expr $bssid_num + 1`
		done
		if [ $interface_available == $card_ext_ifname ]; then
			if_list="${if_list};${card_apcli_ifname}0"
			echo ${card_main_ifname} >> main_ifname
			echo ${card_apcli_ifname}"0" >> apcli_ifname
		fi
		brctl delif $bridge_name $card_apcli_ifname"0"
		brctl addif $bridge_name $card_apcli_ifname"0"
	fi
	echo $if_list
}
prepare_bh_priority_card_if_list()
{
	card_ext_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_ext_ifname |awk -F "[=;]" '{ print $2 }'`
	echo $card_ext_ifname
	card_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_profile_path |awk -F "[=;]" '{ print $2 }'`
	echo $card_profile_path
	card_apcli_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_apcli_ifname |awk -F "[=;]" '{ print $2 }'`
	echo $card_apcli_ifname
	card_main_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname |awk -F "[=;]" '{ print $2 }'`
	card_bssid_num=`cat ${card_profile_path} | grep BssidNum | awk -F "=" '{ print $2 }'`
	echo $card_bssid_num
	iwconfig ${card_main_ifname} | grep "Access Point"
	card_exist=$?
	echo $card_exist
	if [ $card_exist == 0 ]
	then
		bssid_num=0
		while [ $bssid_num -lt $card_bssid_num ]
		do
			if [ -z ${bh_priority_list} ]
			then
				if_exist=`ifconfig -a | grep ${card_ext_ifname}${bssid_num}`
				if [ "$if_exist" != "" ]; then
					bh_priority_list="${card_ext_ifname}${bssid_num}"
				fi
			else
				if_exist=`ifconfig -a | grep ${card_ext_ifname}${bssid_num}`
				if [ "$if_exist" != "" ]; then
					bh_priority_list="${bh_priority_list};${card_ext_ifname}${bssid_num}"
				fi
			fi
			bssid_num=`expr $bssid_num + 1`
		done
		bh_priority_list="${bh_priority_list};${card_apcli_ifname}0"
	fi
	echo $bh_priority_list
}

prepare_bh_priority_if_list()
{
        card_ext_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_ext_ifname |awk -F "[=;]" '{ print $2 }'`
        echo $card_ext_ifname
        card_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_profile_path |awk -F "[=;]" '{ print $2 }'`
        echo $card_profile_path
        card_apcli_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_apcli_ifname |awk -F "[=;]" '{ print $2 }'`
        echo $card_apcli_ifname
        card_main_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname |awk -F "[=;]" '{ print $2 }'`
        card_bssid_num=`cat ${card_profile_path} | grep BssidNum | awk -F "=" '{ print $2 }'`
        echo $card_bssid_num
        iwconfig ${card_main_ifname} | grep "Access Point"
        card_exist=$?
        echo $card_exist
        if [ $card_exist == 0 ]
        then
                bssid_num=0
                while [ $bssid_num -lt $card_bssid_num ]
                do
                        if [ -z ${bh_priority_list} ]
                        then
                                if_exist=`ifconfig -a | grep ${card_ext_ifname}${bssid_num}`
                                if [ "$if_exist" != "" ]; then
                                        bh_priority_list="${card_ext_ifname}${bssid_num}"
                                fi
                        else
                                if_exist=`ifconfig -a | grep ${card_ext_ifname}${bssid_num}`
                                if [ "$if_exist" != "" ]; then
                                        bh_priority_list="${bh_priority_list};${card_ext_ifname}${bssid_num}"
                                fi
                        fi
                        bssid_num=`expr $bssid_num + 1`
                done
                bh_priority_list="${bh_priority_list};${card_apcli_ifname}0"
        fi
        echo $bh_priority_list
        card_ext_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_ext_ifname |awk -F "[=;]" '{ print $3 }'`
        echo $card_ext_ifname
        card_profile_path=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_profile_path |awk -F "[=;]" '{ print $3 }'`
        echo $card_profile_path
        card_apcli_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_apcli_ifname |awk -F "[=;]" '{ print $3 }'`
        echo $card_apcli_ifname
        card_main_ifname=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname |awk -F "[=;]" '{ print $3 }'`
        card_bssid_num=`cat ${card_profile_path} | grep BssidNum | awk -F "=" '{ print $2 }'`
        echo $card_bssid_num
        iwconfig ${card_main_ifname} | grep "Access Point"
        card_exist=$?
        echo $card_exist
        if [ $card_exist == 0 ]
        then
                bssid_num=0
                while [ $bssid_num -lt $card_bssid_num ]
                do
                        if [ -z ${bh_priority_list} ]
                        then
                                if_exist=`ifconfig -a | grep ${card_ext_ifname}${bssid_num}`
                                if [ "$if_exist" != "" ]; then
                                        bh_priority_list="${card_ext_ifname}${bssid_num}"
                                fi
                        else
                                if_exist=`ifconfig -a | grep ${card_ext_ifname}${bssid_num}`
                                if [ "$if_exist" != "" ]; then
                                        bh_priority_list="${bh_priority_list};${card_ext_ifname}${bssid_num}"
                                fi
                        fi
                        bssid_num=`expr $bssid_num + 1`
                done
                bh_priority_list="${bh_priority_list};${card_apcli_ifname}0"
        fi
        echo $bh_priority_list
}

prepare_ifname()
{
	card_idx=0
	active_cards=0
	rm -rf apcli_ifname main_ifname
	while [ $card_idx -le 2 ]
	do
		card=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}= | awk -F "=" '{ print $2 }'`
		echo "$card"
		if [ -z "$card" ]
		then
			echo "No card"
		else
			dbdc_detect=`cat /etc/wireless/l1profile.dat | grep INDEX${card_idx}_main_ifname= | awk -F ";" '{ print $2 }'`

			if [ -z "$dbdc_detect" ]
			then
				prepare_ifname_card
				prepare_bh_priority_card_if_list
			else
				echo "dbdc detected"
				prepare_ifame_band
				prepare_bh_priority_if_list
			fi
		fi
		card_idx=`expr $card_idx + 1`
	done
	lan_ifname=`uci get network.lan.device`
	echo $lan_ifname
	for i in 0 1 2
	do
		tmp_name=`uci get network.@device[$i].name`
		echo $tmp_name
		if [ "$lan_ifname" = "$tmp_name" ]; then
				lan_iface=`uci get network.@device[$i].ports`
				echo $lan_iface
				break
		fi
	done
}

#call routine for SDK specfic config preparation(ra_band/ bh_priority etc)
prepare_platform_variables()
{
	#prepare_ifname
	if [ $active_cards == "2" ]
	then
		radio_band="24G;5G;5G"
	elif [ $active_cards == "3" ]
	then
		radio_band="24G;5GH;5GL"
	fi
	wan_iface=`uci get network.wan.device`
#derive almac from br mac
	br0_mac=$(cat /sys/class/net/br-lan/address)
	ctrlr_al_mac=$br0_mac
	agent_al_mac=$br0_mac
}

R2_config_check() {
#MAP version check
		MapVer=`cat /etc/map/1905d.cfg | grep map_ver| awk -F "=" '{ print $2 }'`
		if [ "$MapVer" = "R1" ]; then
			echo "MAP version 1.0"
			loop_count=1
			while [ $loop_count -le $active_cards ]
			do
				if_name=`sed -n "${loop_count}"p ./main_ifname`
				iwpriv ${if_name} set mapR2Enable=0
				echo "iwpriv $if_name set mapR2Enable=0"
				iwpriv ${if_name} set mapTSEnable=0
				echo "iwpriv $if_name set mapTSEnable=0"
				loop_count=`expr $loop_count + 1`
			done
		elif [ "$MapVer" = "R2" ]; then
			echo "MAP version 2.0"
			loop_count=1
			while [ $loop_count -le $active_cards ]
			do
				if_name=`sed -n "${loop_count}"p ./main_ifname`
				iwpriv ${if_name} set mapR2Enable=1
				echo "iwpriv $if_name set mapR2Enable=1"
                                iwpriv ${if_name} set mapTSEnable=1
                                echo "iwpriv $if_name set mapTSEnable=1"
                                loop_count=`expr $loop_count + 1`
                        done
		else
			echo "MAP version 3.0"
			loop_count=1
			while [ $loop_count -le $active_cards ]
			do
				if_name=`sed -n "${loop_count}"p ./main_ifname`
				iwpriv ${if_name} set mapR3Enable=1
				echo "iwpriv $if_name set mapR3Enable=1"
				iwpriv ${if_name} set DppEnable=1
				echo "iwpriv $if_name set DppEnable=1"
				iwpriv ${if_name} set mapTSEnable=1
				echo "iwpriv $if_name set mapTSEnable=1"
				iwpriv ${if_name} set cp_support=1
				echo "iwpriv $if_name set cp_support=1"
				loop_count=`expr $loop_count + 1`
			done
		fi
}

disable_R2_config() {
	echo "disable_R2_config"
	loop_count=1
	while [ $loop_count -le $active_cards ]
	do
		if_name=`sed -n "${loop_count}"p ./main_ifname`
		iwpriv ${if_name} set mapR2Enable=0
		echo "iwpriv $if_name set mapR2Enable=0"
		iwpriv ${if_name} set mapTSEnable=0
		echo "iwpriv $if_name set mapTSEnable=0"
		loop_count=`expr $loop_count + 1`
	done
}

disable_R3_config() {
        echo "disable_R3_config"
        loop_count=1
        while [ $loop_count -le $active_cards ]
        do
                if_name=`sed -n "${loop_count}"p ./main_ifname`
                iwpriv ${if_name} set mapR3Enable=0
                echo "iwpriv $if_name set mapR3Enable=0"
		iwpriv ${if_name} set DppEnable=0
		echo "iwpriv $if_name set DppEnable=0"
                iwpriv ${if_name} set mapTSEnable=0
                echo "iwpriv $if_name set mapTSEnable=0"
                loop_count=`expr $loop_count + 1`
        done
}

#call routine to prepare wapp configuration files
#call routine to prepare 1905 config file
prepare_1905_config()
{
		DeviceRole=`cat /etc/map/mapd_cfg | grep DeviceRole | awk -F "=" '{ print $2 }'`
		wan_iface=`uci get network.wan.device`
		`ifconfig | grep "br" > br_name`
		bridge_name=`cat br_name | awk '{ print $1}'`
		####delete all lan= wan=
		sed -i '/lan=/d' /etc/map/1905d.cfg
		sed -i '/wan=/d' /etc/map/1905d.cfg
		lastlinestr='$a '
		lanstr='lan='
		wanstr='wan='
		br0_mac=$(cat /sys/class/net/br-lan/address)
		first_three_octets=${br0_mac:0:9}
		last_two_octets=${br0_mac:11}
		modified_octet=${br0_mac:9:2}
		let mac=0x$modified_octet
		sed -i "/lan=.*/d" /etc/ethernet_cfg.txt
		if [ $mode = "1" ];then
			sed -i "1i\lan=$lan_iface $wan_iface" /etc/ethernet_cfg.txt
		else
			sed -i "1i\lan=$lan_iface" /etc/ethernet_cfg.txt
		fi
		sed -i "/br_lan=.*/d" /etc/ethernet_cfg.txt
		sed -i "1i\br_lan=$bridge_name" /etc/ethernet_cfg.txt
		#lan0
		lan_per_iface=`echo $lan_iface | awk -F " " '{ print $1 }'`
		exist=`ifconfig $lan_per_iface|grep HWaddr`
		if [ $lan_per_iface ] && [ "$exist" != "" ]; then
			lan_insert_str=$lastlinestr$lanstr$lan_per_iface
			`sed -i "$lan_insert_str" /etc/map/1905d.cfg`
			let "mac_new=mac+16"
			mac_str=`printf "%02x" $mac_new`
			m_str=${mac_str:0-2}
			ifconfig $lan_per_iface down
			ifconfig $lan_per_iface hw ether $first_three_octets$m_str$last_two_octets
			ifconfig $lan_per_iface up
			#brctl addif $bridge_name $lan_per_iface
			echo $lan_per_iface
			echo $first_three_octets$m_str$last_two_octets
		fi
		#lan1
		lan_per_iface=`echo $lan_iface | awk -F " " '{ print $2 }'`
		exist=`ifconfig $lan_per_iface|grep HWaddr`
		if [ $lan_per_iface ] && [ "$exist" != "" ]; then
			lan_insert_str=$lastlinestr$lanstr$lan_per_iface
			`sed -i "$lan_insert_str" /etc/map/1905d.cfg`
			#brctl addif $bridge_name $lan_per_iface
			let "mac_new=mac+32"
			mac_str=`printf "%02x" $mac_new`
			m_str=${mac_str:0-2}
			ifconfig $lan_per_iface down
			ifconfig $lan_per_iface hw ether $first_three_octets$m_str$last_two_octets
			ifconfig $lan_per_iface up
			echo $lan_per_iface
			echo $first_three_octets$m_str$last_two_octets
		fi
		#lan2
		lan_per_iface=`echo $lan_iface | awk -F " " '{ print $3 }'`
		exist=`ifconfig $lan_per_iface|grep HWaddr`
		if [ $lan_per_iface ] && [ "$exist" != "" ]; then
			lan_insert_str=$lastlinestr$lanstr$lan_per_iface
			`sed -i "$lan_insert_str" /etc/map/1905d.cfg`
			#brctl addif $bridge_name $lan_per_iface
			let "mac_new=mac+48"
			mac_str=`printf "%02x" $mac_new`
			m_str=${mac_str:0-2}
			ifconfig $lan_per_iface down
			ifconfig $lan_per_iface hw ether $first_three_octets$m_str$last_two_octets
			ifconfig $lan_per_iface up
			echo $lan_per_iface
			echo $first_three_octets$m_str$last_two_octets
		fi
		#lan3
		lan_per_iface=`echo $lan_iface | awk -F " " '{ print $4 }'`
		exist=`ifconfig $lan_per_iface|grep HWaddr`
		if [ $lan_per_iface ] && [ "$exist" != "" ]; then
			lan_insert_str=$lastlinestr$lanstr$lan_per_iface
			`sed -i "$lan_insert_str" /etc/map/1905d.cfg`
			#brctl addif $bridge_name $lan_per_iface
			let "mac_new=mac+64"
			mac_str=`printf "%02x" $mac_new`
			m_str=${mac_str:0-2}
			ifconfig $lan_per_iface down
			ifconfig $lan_per_iface hw ether $first_three_octets$m_str$last_two_octets
			ifconfig $lan_per_iface up
			echo $lan_per_iface
			echo $first_three_octets$m_str$last_two_octets
		fi
		#lan4
		lan_per_iface=`echo $lan_iface | awk -F " " '{ print $5 }'`
		exist=`ifconfig $lan_per_iface|grep HWaddr`
		if [ $lan_per_iface ] && [ "$exist" != "" ]; then
			lan_insert_str=$lastlinestr$lanstr$lan_per_iface
			`sed -i "$lan_insert_str" /etc/map/1905d.cfg`
			#brctl addif $bridge_name $lan_per_iface
			let "mac_new=mac+80"
			mac_str=`printf "%02x" $mac_new`
			m_str=${mac_str:0-2}
			ifconfig $lan_per_iface down
			ifconfig $lan_per_iface hw ether $first_three_octets$m_str$last_two_octets
			ifconfig $lan_per_iface up
			echo $lan_per_iface
			echo $first_three_octets$m_str$last_two_octets
		fi
		#lan5
		lan_per_iface=`echo $lan_iface | awk -F " " '{ print $6 }'`
		exist=`ifconfig $lan_per_iface|grep HWaddr`
		if [ $lan_per_iface ] && [ "$exist" != "" ]; then
			lan_insert_str=$lastlinestr$lanstr$lan_per_iface
			`sed -i "$lan_insert_str" /etc/map/1905d.cfg`
			#brctl addif $bridge_name $lan_per_iface
			let "mac_new=mac+96"
			mac_str=`printf "%02x" $mac_new`
			m_str=${mac_str:0-2}
			ifconfig $lan_per_iface down
			ifconfig $lan_per_iface hw ether $first_three_octets$m_str$last_two_octets
			ifconfig $lan_per_iface up
			echo $lan_per_iface
			echo $first_three_octets$m_str$last_two_octets
		fi

		#if [ `grep -c "lan=$lan_iface" /etc/map/1905d.cfg` -ne '0' ]; then
		#elif [ `grep -c "lan=" /etc/map/1905d.cfg` -ne '0' ]; then
		sed -i "s/radio_band=.*/radio_band=${radio_band}/g" /etc/map/1905d.cfg
		sed -i "s/map_controller_alid=.*/map_controller_alid=${ctrlr_al_mac}/g" /etc/map/1905d.cfg
		sed -i "s/map_agent_alid=.*/map_agent_alid=${agent_al_mac}/g" /etc/map/1905d.cfg
		if [ $DeviceRole = "1" ]
		then
			sed -i "s/map_agent=.*/map_agent=0/g" /etc/map/1905d.cfg
			sed -i "s/map_root=.*/map_root=1/g" /etc/map/1905d.cfg
		else
			sed -i "s/map_agent=.*/map_agent=1/g" /etc/map/1905d.cfg
			sed -i "s/map_root=.*/map_root=0/g" /etc/map/1905d.cfg
		fi

		#######mode
		if [ $mode = "1" ]; then
			echo "prepare_1905_config bridge mode"
			wan_insert_str=$lastlinestr$wanstr$wan_iface
			`sed -i "$wan_insert_str" /etc/map/1905d.cfg`
			brctl addif $bridge_name $wan_iface
		else
			brctl delif $bridge_name $wan_iface
		fi
}
reset_lan_interface()
{
	br0_mac=$(cat /sys/class/net/br-lan/address)
	lan_per_iface=`echo $lan_iface | awk -F " " '{ print $1 }'`
	if [ $lan_per_iface ]; then
		ifconfig $lan_per_iface down
		ifconfig $lan_per_iface hw ether $br0_mac
		ifconfig $lan_per_iface up
	fi
	lan_per_iface=`echo $lan_iface | awk -F " " '{ print $2 }'`
	if [ $lan_per_iface ]; then
		ifconfig $lan_per_iface down
		ifconfig $lan_per_iface hw ether $br0_mac
		ifconfig $lan_per_iface up
	fi
	lan_per_iface=`echo $lan_iface | awk -F " " '{ print $3 }'`
	if [ $lan_per_iface ]; then
		ifconfig $lan_per_iface down
		ifconfig $lan_per_iface hw ether $br0_mac
		ifconfig $lan_per_iface up
	fi
	lan_per_iface=`echo $lan_iface | awk -F " " '{ print $4 }'`
	if [ $lan_per_iface ]; then
		ifconfig $lan_per_iface down
		ifconfig $lan_per_iface hw ether $br0_mac
		ifconfig $lan_per_iface up
	fi
	lan_per_iface=`echo $lan_iface | awk -F " " '{ print $5 }'`
	if [ $lan_per_iface ]; then
		ifconfig $lan_per_iface down
		ifconfig $lan_per_iface hw ether $br0_mac
		ifconfig $lan_per_iface up
	fi
}
prepare_logging_config()
{
echo "
/tmp/log/log.mapd {
	size 64K
	copytruncate
	rotate 2
}
" > /etc/logrotate.d/mapd.log.conf
}

#preapre config file for map steering parameters
prepare_mapd_strng_configs()
{
	if [ ! -f "/etc/mapd_strng.conf" -o "$check_default" = "default" ];then
		echo "Make mapd_strng.conf"
echo "LowRSSIAPSteerEdge_RE=40
CUOverloadTh_2G=70
CUOverloadTh_5G_L=80
CUOverloadTh_5G_H=80
MetricPolicyChUtilThres_24G=70
MetricPolicyChUtilThres_5GL=80
MetricPolicyChUtilThres_5GH=80
ChPlanningChUtilThresh_24G=70
ChPlanningChUtilThresh_5GL=80
ChPlanningEDCCAThresh_24G=200
ChPlanningEDCCAThresh_5GL=200
ChPlanningOBSSThresh_24G=200
ChPlanningOBSSThresh_5GL=200
ChPlanningR2MonitorTimeoutSecs=300
ChPlanningR2MonitorProhibitSecs=900
ChPlanningR2MetricReportingInterval=10
ChPlanningR2MinScoreMargin=20
MetricRepIntv=10
MetricPolicyRcpi_24G=100
MetricPolicyRcpi_5GL=100
MetricPolicyRcpi_5GH=100
BTMStrForbidTime=15
ForceStrForbidTime=15
BTMStrBlockTime=45
ForceStrBlockTime=90        
RSSISteeringEdge_DG=30
RSSISteeringEdge_UG=30
" > /etc/mapd_strng.conf
	fi
}
#call routines for mapd_cfg.txt preparation
prepare_mapd_config()
{
	need_loop=1
	line_count=1
	cp /etc/map/mapd_default.cfg /etc/map/mapd_cfg
	if [ "$check_default" = "default" ];then
		need_loop=0
		cat "###!UserConfigs!!!" > /etc/map/mapd_user.cfg
	fi
	sed -i "s/lan_interface=.*/lan_interface=${lan_iface}/g" /etc/map/mapd_cfg
	sed -i "s/wan_interface=.*/wan_interface=${wan_iface}/g" /etc/map/mapd_cfg
	while [ $need_loop == "1" ]
	do
		line=`sed -n "$line_count"p /etc/map/mapd_user.cfg`
		echo $line
		if [ -z $line ]
		then
			need_loop=0
		else
			key=`echo ${line} | awk -F "=" '{ print $1 }'`
			value=`echo ${line} | awk -F "=" '{ print $2 }'`
			echo "Key = ${key}, value = ${value}"
			datconf -f /etc/map/mapd_cfg set $key "${value}"
		fi
		line_count=`expr $line_count + 1`
	done
	enhanced_logging=`cat /etc/map/mapd_cfg | grep "EnhancedLogging" | awk -F "=" '{ print $2 }'`
	if [ $enhanced_logging = "1" ]
	then
		prepare_logging_config
	fi
	sed -i "s/bss_config_priority=.*/bss_config_priority=${bh_priority_list}/g" /etc/map/mapd_cfg
	echo MaxVHT_BW5G=${MaxVHT_BW5G} >> /etc/map/mapd_cfg
	echo MaxHT_BW5G=${MaxHT_BW5G} >> /etc/map/mapd_cfg
	echo MaxHT_BW2G=${MaxHT_BW2G} >> /etc/map/mapd_cfg
	prepare_mapd_strng_configs
}

cert_switch_changes()
{
	card_gsw_setting=`cat /proc/device-tree/ethernet@1b100000/mdio-bus/switch@0/compatible`
	echo $card_gsw_setting
	if [ "$card_gsw_setting" = "mediatek,mt7531" ] ;then
		echo "found green card with MT7531 switch"
		switch reg w 34 8160816
		switch reg w 4 60
		switch reg w 10 ffffffff
	fi
	#card_gsw_setting=`cat /proc/device-tree/rtkgswsys@1b100000/compatible`
	#echo $card_gsw_setting
	#if [ "$card_gsw_setting" = "mediatek,rtk-gsw" ] ;then
	#	echo "found red card with switch RTL8367S"
	#fi
}
disconnect_all_sta()
{
	need_loop=1
	loop_count=1
	while [ $loop_count -le $active_cards ]
	do
		if_name=`sed -n "${loop_count}"p ./main_ifname`
		`iwpriv ${if_name} set DisConnectAllSta=`
		loop_count=`expr $loop_count + 1`
	done
}

ApCliIntfUpForCert()
{
        need_loop=1
        loop_count=1
        while [ $loop_count -le $active_cards ]
        do
                if_name=`sed -n "${loop_count}"p ./apcli_ifname`
                `ifconfig | grep "br" > br_name`
                bridge_name=`cat br_name | awk '{ print $1}'`
                `ifconfig ${if_name} up`
                `brctl addif ${bridge_name} ${if_name}`
                `iwpriv ${if_name} set mapEnable=4`
                `iwpriv ${if_name} set ApCliEnable=0`
                loop_count=`expr $loop_count + 1`
        done
        sleep 2
}

ApCliIntfUp()
{
	need_loop=1
	loop_count=1
	while [ $loop_count -le $active_cards ]
	do
		if_name=`sed -n "${loop_count}"p ./apcli_ifname`
		`ifconfig | grep "br" > br_name`
		bridge_name=`cat br_name | awk '{ print $1}'`
		`ifconfig ${if_name} up`
		`brctl addif ${bridge_name} ${if_name}`
		`iwpriv ${if_name} set mapEnable=1`
		`iwpriv ${if_name} set ApCliEnable=0`
		loop_count=`expr $loop_count + 1`
	done
	sleep 2
}

ApCliIntfDown()
{
	need_loop=1
	loop_count=1
	while [ $loop_count -le $active_cards ]
	do
		if_name=`sed -n "${loop_count}"p ./apcli_ifname`
		`ifconfig | grep "br" > br_name`
		bridge_name=`cat br_name | awk '{ print $1}'`
		`ifconfig ${if_name} down`
		`brctl addif ${bridge_name} ${if_name}`
		`iwpriv ${if_name} set ApCliEnable=0`
		loop_count=`expr $loop_count + 1`
	done
	sleep 2
}

DHCP_INIT()
{
	DeviceRole=`cat /etc/map/mapd_cfg|\
		grep DeviceRole|awk -F "=" '{print $2}'`
	echo "DeviceRole: $DeviceRole (0: Auto 1:Controller 2:Agent)"
	DHCP_CTRL=`cat /etc/map/mapd_cfg|\
		grep DhcpCtl| awk -F "=" '{print $2}'`
	ThrdPrtCon=`cat /etc/map/mapd_cfg|grep ThirdPartyConnection\
		|awk -F "=" '{print $2}'`
	echo "DHCP Server setting: $DeviceRole $DHCP_CTRL $ThrdPrtCon $mode ($mode == "1")"
	if [ $DHCP_CTRL != "1" ];then
		return 0
	fi
		
	if [ $ThrdPrtCon == "1" -a "${MapMode}" = "1"  ];then
	echo "Role($DeviceRole ) ThrdPrtCon($ThrdPrtCon):\
	Disable DHCP Server!"
		uci set dhcp.lan.ignore=1
		uci commit
		/etc/init.d/dnsmasq reload
	else
	if [ $mode != "1" ];then
		echo "Role($DeviceRole ) ThrdPrtCon($ThrdPrtCon):\
		Enable DHCP Server!"
			if [ -z "$(uci -q get network.lan.ipaddr)" ];then
				echo "no IP, reload network ip to 192.168.1.1"
				uci -q set network.lan.ipaddr=192.168.1.1;
				`ifconfig ${bridge_name} 192.168.1.1 up`
				uci set dhcp.lan.ignore=\"\"
				uci commit
				/etc/init.d/dnsmasq reload
				/etc/init.d/network reload
			 else
				br_ip=`uci -q get network.lan.ipaddr`
				echo "br_ip: $br_ip"
				`ifconfig ${bridge_name} $br_ip up`
				uci set dhcp.lan.ignore=\"\"
				uci commit
				/etc/init.d/dnsmasq reload
			fi
		fi
	fi
	sleep 1

	if [ $mode == "1" ];then
		echo "bridge mode"
		uci set network.wan.proto=none
		uci commit
		#Disable DHCP Server
		uci set dhcp.lan.ignore=1
		uci commit
		/etc/init.d/dnsmasq reload
		udhcpc -i ${bridge_name} &
		br_ip=`uci -q get network.lan.ipaddr`
		sleep 1
		`ifconfig ${bridge_name} $br_ip`
	else
		echo "router mode"
		uci set network.wan.proto=dhcp
		uci commit
	fi
	
	return 1
}

Traffic_Separation_Init()
{
	for index in 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	do
		iwpriv ra$index set VLANTag=1
		iwpriv rax$index set VLANTag=1
		iwpriv rai$index set VLANTag=1
		iwpriv ra$index set VLANPolicy=0:4
		iwpriv rax$index set VLANPolicy=0:4
		iwpriv rai$index set VLANPolicy=0:4
		iwpriv ra$index set VLANPolicy=1:2
		iwpriv rai$index set VLANPolicy=1:2
		iwpriv rai$index set VLANPolicy=1:2
	done
	iwpriv apcli0 set VLANTag=1
	iwpriv apcli0 set VLANPolicy=0:4
	iwpriv apcli0 set VLANPolicy=1:2
	iwpriv apclix0 set VLANTag=1
	iwpriv apclix0 set VLANPolicy=0:4
	iwpriv apclix0 set VLANPolicy=1:2
	iwpriv apclii0 set VLANTag=1
	iwpriv apclii0 set VLANPolicy=0:4
	iwpriv apclii0 set VLANPolicy=1:2
}

Traffic_Separation_Init_Cert()
{
	iwpriv ra0 set VLANEn=0
	iwpriv rax0 set VLANEn=0
	iwpriv rai0 set VLANEn=0
}

StartStandAloneBS()
{
	sleep 3
	echo "WAPP starting..."
	wapp_openwrt.sh > /dev/null
	sleep 3
	echo "BS2.0 Daemon starting..."
	bs20 &
	sleep 3
	disconnect_all_sta
	echo "Stand Alone BS2.0 is ready"
}

StartMapTurnkey()
{
#	SwitchSetting
#	echo $lan_iface > /sys/kernel/debug/hnat/hnat_ppd_if

	R2_config_check
	ulimit -c unlimited
	#Controller
    DeviceRole=`cat /etc/map/mapd_cfg|\
	grep DeviceRole|awk -F "=" '{ print $2 }'`
   	echo $DeviceRole
	echo "dhcp starting..."
	DHCP_INIT
	Traffic_Separation_Init
	echo "WAPP starting..."
	wapp_openwrt.sh > /dev/null
	echo "1905 starting..."
	if [ $DeviceRole = "1" ]
	then
		p1905_managerd -r0 -f "/etc/map/1905d.cfg" -F "/etc/map/wts_bss_info_config" > /dev/console&
	else
		p1905_managerd -r1 -f "/etc//map/1905d.cfg" -F "/etc/map/wts_bss_info_config" > /dev/console&
	fi
	sleep 2
	echo "MAP Daemon starting..."
	if [ $enhanced_logging = "1" ]
	then
		mapd -I "/etc/map/mapd_cfg" -O "/etc/mapd_strng.conf" > /tmp/log/log.mapd&
	else
		mapd -I "/etc/map/mapd_cfg" -O "/etc/mapd_strng.conf" > /dev/console&
	fi
#	ModifySwitchReg
	sleep 3
	echo -e "----- ${RED}MAP DEVICE STARTED${NC} -----"
}

clean
sync
prepare_ifname
sync
get_operating_mode
sync
prepare_platform_variables
sync
prepare_mapd_config
sync
prepare_1905_config
sync
disable_R2_config
sync
disable_R3_config
sync

echo "kill fwdd daemon and remove mtfwd module"
#Enable QuickChChange feature.

ulimit -c unlimited

if [ "${MapMode}" = "0" ];
	then
		echo "Enable QoSR1"
		datconf -f /tmp/mtk/wifi/2860 set QoSR1Enable 1
		datconf -f /tmp/mtk/wifi/rtdev set QoSR1Enable 1
		datconf -f /tmp/mtk/wifi/wifi3 set QoSR1Enable 1

	echo "dhcp starting..."
	if [ "${LastMapMode}" = "1" ]
	then
	echo "default dhcp server enable..."
	sync
	DHCP_INIT
	sync
	echo "defautl ApCliIntfDown..."
	sync
	ApCliIntfDown
	sync
	echo "defautl dat apcli disable..."
	nvram_set 2860 ApCliEnable 0
	nvram_set rtdev ApCliEnable 0
	nvram_set wifi3 ApCliEnable 0
	fi
	echo "Non MAP mode"
	need_loop=1
	loop_count=1
	while [ $loop_count -le $active_cards ]
	do
		if_name=`sed -n "${loop_count}"p ./main_ifname`
		iwpriv ${if_name} set mapEnable=0
		loop_count=`expr $loop_count + 1`
	done
	sync
	reset_lan_interface
	sync
	wapp_openwrt.sh
	sync
	modprobe mtfwd
	sleep 1
	fwdd -p ra0 apcli0 -p rai0 apclii0 -p rax0 apclix0 -p wlan0 wlan-apcli0 -e eth0 5G&
	sync
elif [ ${MapMode} = "2" ];
	then
	rmmod mapfilter
	echo "BS2.0 mode"
	while [ $loop_count -le $active_cards ]
	do
		if_name=`sed -n "${loop_count}"p ./main_ifname`
		iwpriv ${if_name} set mapEnable=2
		loop_count=`expr $loop_count + 1`
	done
	sleep 1
	StartStandAloneBS
	modprobe mtfwd
	sleep 1
	fwdd -p ra0 apcli0 -p rai0 apclii0 -p rax0 apclix0 -p wlan0 wlan-apcli0 -e eth0 5G&
elif [ ${MapMode} = "4" ];
	then
	killall -15 fwdd
	sleep 1
	rmmod mtfwd
	echo "Certification"
#	Cert_switch_config
	cert_switch_changes
	mkdir /libmapd
	cp /usr/lib/libmapd_interface_client.so /libmapd/
	modprobe mapfilter
	ApCliIntfUpForCert
	sync
	map_config_agent.lua start
	echo 458752 > /proc/sys/net/core/rmem_max
	Traffic_Separation_Init_Cert
	R2_config_check
else
	if [ "${MapMode}" = "1" ];
	then
		echo "TurnKeyMode"
		echo "Disable QoSR1"
		datconf -f /tmp/mtk/wifi/2860 set QoSR1Enable 0
		datconf -f /tmp/mtk/wifi/rtdev set QoSR1Enable 0
		datconf -f /tmp/mtk/wifi/wifi3 set QoSR1Enable 0

		killall -15 fwdd
		sleep 1
		rmmod mtfwd
		mkdir /libmapd
		cp /usr/lib/libmapd_interface_client.so /libmapd/
		modprobe mapfilter
		sync
		ApCliIntfUp
		sync
		#need_loop=1
		#loop_count=1
		#while [ $loop_count -le $active_cards ]
		#do
		#	if_name=`sed -n "${loop_count}"p ./main_ifname`
		#	iwpriv ${if_name} set mapEnable=1
		#	loop_count=`expr $loop_count + 1`
		#done
		sleep 1
		sync
		StartMapTurnkey
		sync
	fi
fi
/etc/init.d/easymesh stop
