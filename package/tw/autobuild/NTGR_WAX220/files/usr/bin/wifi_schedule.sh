#!/bin/sh
# Copyright (c) 2016, prpl Foundation
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with or without
# fee is hereby granted, provided that the above copyright notice and this permission notice appear
# in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
# FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#
# Author: Nils Koenig <openwrt@newk.it>
# Editor: Daniel

SCRIPT=$0
LOCKFILE=/tmp/wifi_schedule.lock
LOGFILE=/tmp/log/wifi_schedule.log
LOGGING=0 #default is off
PACKAGE=wifi_schedule
GLOBAL=${PACKAGE}.@global[0]
RF=$2

TW_RF=$2
TW_TIME=$4
TW_DOW=$5
TW_ACTION=$3

_log()
{
    if [ ${LOGGING} -eq 1 ]; then
        local ts=$(date)
        echo "$ts $@" >> ${LOGFILE}
    fi
}

_exit()
{
    local rc=$1
    lock -u ${LOCKFILE}
    exit ${rc}
}

_cron_restart()
{
    /etc/init.d/cron restart > /dev/null
}

_add_cron_script()
{
    (crontab -l ; echo "$1") | sort | uniq | crontab -
    _cron_restart
}

_rm_cron_script()
{
    crontab -l | grep -v "$1" |  sort | uniq | crontab -
    _cron_restart
}

_get_uci_value_raw()
{
    local value
    value=$(uci get $1 2> /dev/null)
    local rc=$?
    echo ${value}
    return ${rc}
}

_get_uci_value()
{
    local value
    value=$(_get_uci_value_raw $1)
    local rc=$?
    if [ ${rc} -ne 0 ]; then
        _log "Could not determine UCI value $1"
        return 1
    fi
    echo ${value}
}

_format_dow_list()
{
    local dow=$1
    local flist=""
    local day
    for day in ${dow}
    do
        if [ ! -z ${flist} ]; then
            flist="${flist},"
        fi
        flist="${flist}${day:0:3}"
    done
    echo ${flist}
}

_enable_wifi_schedule()
{
    local radio=$1
    local entry=$2
    local starttime
    local stoptime
    local dow

    stoptime=$(_get_uci_value ${PACKAGE}.${entry}.starttime) || _exit 1
    starttime=$(_get_uci_value ${PACKAGE}.${entry}.stoptime) || _exit 1
    dow=$(_get_uci_value_raw ${PACKAGE}.${entry}.daysofweek) || _exit 1

    local fdow=$(_format_dow_list "$dow")

    local stop_cron_entry="$(echo ${stoptime} | awk -F':' '{print $2, $1}') * * ${fdow} ${SCRIPT} stop ${radio}" # ${entry}"
    _add_cron_script "${stop_cron_entry}"

    if [[ $starttime != $stoptime ]]
    then
        local start_cron_entry="$(echo ${starttime} | awk -F':' '{print $2, $1}') * * ${fdow} ${SCRIPT} start ${radio}" # ${entry
        _add_cron_script "${start_cron_entry}"
    fi

    return 0
}

_get_wireless_interfaces()
{
    local n=$(cat /proc/net/wireless | wc -l)

    if [[ "${RF}" == "2G" ]]; then
        cat /proc/net/wireless | tail -n 12 | awk -F':' '{print $1}' | sed  's/ //' | grep 'ra[0-4]'
    fi

    if [[ "${RF}" == "5G" ]]; then
        cat /proc/net/wireless | tail -n 12 | awk -F':' '{print $1}' | sed  's/ //' | grep 'rax[0-4]'
    fi
}

_create_radio_cron_entries()
{
    local entries
    local radio=$1

    if [[ "${radio}" == "2G" ]]; then
        entries=$(uci show wifi_schedule 2> /dev/null | awk -F'.' '{print $2}' | grep '@schdule_rule_2G' | grep -v '=' | uniq | sort)
    fi

    if [[ "${radio}" == "5G" ]]; then
        entries=$(uci show wifi_schedule 2> /dev/null | awk -F'.' '{print $2}' | grep '@schdule_rule_5G' | grep -v '=' | uniq | sort)
    fi

    local entry
    for entry in ${entries}
    do
        _enable_wifi_schedule ${radio} ${entry}
    done
}

_create_cron_entries()
{
    local radio_list
    local radio
    local cron_2g_enabled
    local cron_5g_enabled

    cron_2g_enabled=$(_get_uci_value ${GLOBAL}.radio_2G_enabled)
    cron_5g_enabled=$(_get_uci_value ${GLOBAL}.radio_5G_enabled)

    if [ ${cron_2g_enabled} -eq 1 ]; then
        radio_list="2G"
    fi

    if [ ${cron_5g_enabled} -eq 1 ]; then
        radio_list="$radio_list 5G"
    fi

    for radio in ${radio_list}
    do
        _create_radio_cron_entries ${radio}
    done
}

check_cron_status()
{
    local global_enabled
    global_enabled=$(_get_uci_value ${GLOBAL}.enabled) || _exit 1
    _rm_cron_script "${SCRIPT}"

    if [ ${global_enabled} -eq 1 ]; then
        _create_cron_entries
    fi
}

add_wifi_schedule_cron()
{
    local fdow=$(_format_dow_list "$TW_DOW")

    local cron_entry="$(echo ${TW_TIME} | awk -F':' '{print $2, $1}') * * ${fdow} ${SCRIPT} ${TW_ACTION} ${TW_RF}"
    _add_cron_script "${cron_entry}"
}

rm_wifi_schedule_cron()
{
    _rm_cron_script "${SCRIPT}"
}

disable_wifi()
{
    local radio
    local wire_sche

    _rm_cron_script "${SCRIPT} recheck"

    if [[ "${RF}" == "2G" ]]; then
        if_device=$(uci get wireless.2g.device)
    fi

    if [[ "${RF}" == "5G" ]]; then
        if_device=$(uci get wireless.5g.device)
    fi

    radio=${if_device//_/.};

    if [ -z ${radio} ]; then
        _log "No radio interface is vailable, skipping"
        return 1
    fi

    wire_sche=$(uci get system.logs.log_wire_sche)
    if [ $wire_sche -eq 1 ];then
        if [ -f /tmp/ntp_sync_ok ];then
            /usr/bin/redis-cli -s /tmp/.redis.sock lpush logs "[Wireless signal schedule] The wireless ${RF} signal is OFF, $(date +"%A, %B %d, %Y %H:%M:%S")"
        else
            /usr/bin/redis-cli -s /tmp/.redis.sock lpush logs "[Wireless signal schedule] The wireless ${RF} signal is OFF, TIME::$(cat /proc/uptime | awk -F'.' '{print $1}')"
        fi
        /usr/bin/redis-cli -s /tmp/.redis.sock ltrim logs 0 1023
    fi

    if [ ! -z ${radio} ]; then
        /sbin/wifi down ${radio}
        #Fix B2101150003:If we disable this interface,we should disable this interface radio for GUI display
        if [[ "${RF}" == "2G" ]]; then
            /sbin/uci set wireless.2g.rfRadioOn='0'
            /sbin/uci commit wireless
            ifBase_2g=`/sbin/uci -q get wireless.2g.ifName`
            echo 0 > /tmp/wlan_link_time_stamp_2g
        fi

        if [[ "${RF}" == "5G" ]]; then
            /sbin/uci set wireless.5g.rfRadioOn='0'
            /sbin/uci commit wireless
            ifBase_5g=`/sbin/uci -q get wireless.5g.ifName`
            echo 0 > /tmp/wlan_link_time_stamp_5g
        fi
    fi
}

soft_disable_wifi()
{
    local _disable_wifi=1

[ 0 -eq 1 ] && {
    local iwinfo=/usr/bin/iwinfo

    if [ ! -e ${iwinfo} ]; then
        _log "${iwinfo} not available, skipping"
        return 1
    fi

    # check if no stations are associated
    local _if
    for _if in $(_get_wireless_interfaces)
    do
        output=$(${iwinfo} ${_if} assoclist)
        if [[ "$output" != "No information available" ]]
        then
            _disable_wifi=0
            local stations=$(echo ${output}| grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}' | tr '\n' ' ')
            _log "Station(s) ${stations}associated on ${_if}"
        fi
    done
}

    if [ ${_disable_wifi} -eq 1 ]; then
        _log "No stations associated, disable wifi."
        disable_wifi
    else
        _log "Could not disable wifi due to associated stations, retrying..."
        local recheck_interval=$(_get_uci_value ${GLOBAL}.recheck_interval)
        _add_cron_script "*/${recheck_interval} * * * * ${SCRIPT} recheck"
    fi
}

enable_wifi()
{
    local radio
    local wire_sche
    list="0 1 2"

    _rm_cron_script "${SCRIPT} recheck"

    if [[ "${RF}" == "2G" ]]; then
        if_device=$(uci get wireless.2g.device)
    fi

    if [[ "${RF}" == "5G" ]]; then
        if_device=$(uci get wireless.5g.device)
    fi

    radio=${if_device//_/.};

    if [ -z ${radio} ]; then
        _log "No radio interface is vailable, skipping"
        return 1
    fi

    wire_sche=$(uci get system.logs.log_wire_sche)
    if [ $wire_sche -eq 1 ];then
        if [ -f /tmp/ntp_sync_ok ];then
            /usr/bin/redis-cli -s /tmp/.redis.sock lpush logs "[Wireless signal schedule] The wireless ${RF} signal is ON, $(date +"%A, %B %d, %Y %H:%M:%S")"
        else
            /usr/bin/redis-cli -s /tmp/.redis.sock lpush logs "[Wireless signal schedule] The wireless ${RF} signal is ON, TIME::$(cat /proc/uptime | awk -F'.' '{print $1}')"
        fi
        /usr/bin/redis-cli -s /tmp/.redis.sock ltrim logs 0 1023
    fi

    if [ ! -z ${radio} ]; then
        /sbin/wifi up ${radio}
        #Fix B2101150003:If we enable this interface,we should enable this interface radio for GUI display
        if [[ "${RF}" == "2G" ]]; then
            /sbin/uci set wireless.2g.rfRadioOn='1'
            /sbin/uci commit wireless
            ifBase_2g=`/sbin/uci -q get wireless.2g.ifName`
            for idx in $list
            do
                iwpriv $ifBase_2g$idx set RadioOn=1
            done
            sysUptime=$(cat /proc/uptime | awk -F'.' '{print $1}')
            echo $sysUptime> /tmp/wlan_link_time_stamp_2g
        fi

        if [[ "${RF}" == "5G" ]]; then
            $(uci set wireless.5g.rfRadioOn='1')
            $(uci commit wireless)
            ifBase_5g=`/sbin/uci -q get wireless.5g.ifName`
            for idx in $list
            do
                iwpriv $ifBase_5g$idx set RadioOn=1
            done
            sysUptime=$(cat /proc/uptime | awk -F'.' '{print $1}')
            echo $sysUptime> /tmp/wlan_link_time_stamp_5g
        fi
    fi
}

usage()
{
    echo ""
    echo "$0 cron|start|stop|forcestop|recheck|help"
    echo ""
    echo "    UCI Config File: /etc/config/${PACKAGE}"
    echo ""
    echo "    cron: Create cronjob entries."
    echo "    start: Start wifi."
    echo "    stop: Stop wifi gracefully, i.e. check if there are stations associated and if so keep retrying."
    echo "    forcestop: Stop wifi immediately."
    echo "    recheck: Recheck if wifi can be disabled now."
    echo "    help: This description."
    echo ""
}

###############################################################################
# MAIN
###############################################################################
LOGGING=$(_get_uci_value ${GLOBAL}.logging) || _exit 1
_log ${SCRIPT} $1 $2 $3
lock ${LOCKFILE}

case "$1" in
    cron) check_cron_status ;;
    rmcron) rm_wifi_schedule_cron ;;
    addcron) add_wifi_schedule_cron ;;
    start) enable_wifi ;;
    forcestop) disable_wifi ;;
    stop) soft_disable_wifi ;;
    recheck) soft_disable_wifi ;;
    help|--help|-h|*) usage ;;
esac

_exit 0
