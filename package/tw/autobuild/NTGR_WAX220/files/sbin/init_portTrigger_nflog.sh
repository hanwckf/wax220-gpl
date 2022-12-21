#!/bin/bash 

PACKAGE=port_firewall
OLD_PACKAGE=firewall
triggerEnabled=$(uci get firewall.trigger.enabled    2>/dev/null)
triggerTimeout=$(uci get firewall.trigger.timeout    2>/dev/null)
routeLanAddress=$(ubus call network.interface.lan status | grep "\"address\":" | grep -oE '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' | awk 'NR==1'    2>/dev/null)
routeLanMask=$(ubus call network.interface.lan status | grep "\"mask\":" | awk '{print $2}' | awk 'NR==1'    2>/dev/null)
netmode=$(uci get system.@system[0].netmode 2> /dev/null)
netmode="${netmode:-"router"}"
wanifname=$(uci get network.wan.ifname 2> /dev/null)
[ "$netmode" != "router" -o "x$wanifname" = "x" ] && exit 1

_create_trigger_iptables() {
    local triggerChainInFORWARDList="FORWARD_WAN porttrigger_log"
    local triggerChainInPREROUTINGList="PREROUTING_RULE PREROUTING_WAN"
    local ret=0

    for i in ${triggerChainInFORWARDList}; do
        iptables -t filter -C FORWARD -j ${i}   2>/dev/null
        ret=$(echo $?)
        if [ ${ret} -ne 0 ]; then
            iptables -t filter -N ${i} 2> /dev/null
            iptables -t filter -I FORWARD -j ${i}
        fi
    done

    for i in ${triggerChainInPREROUTINGList}; do
        iptables -t nat -C PREROUTING -j ${i}   2>/dev/null
        ret=$(echo $?)
        if [ ${ret} -ne 0 ]; then
            iptables -t nat -N ${i} 2> /dev/null
            iptables -t nat -I PREROUTING -j ${i}
        fi
    done
}

_empty_trigger_iptables() {
    iptables -t nat -F PREROUTING_WAN
    iptables -t nat -F PREROUTING_RULE
    iptables -t filter -F FORWARD_WAN
    iptables -t filter -F porttrigger_log
}

_enable_trigger_entries () {
    local entry=$1
    local entryNum=$2
    local serviceIp=$(uci get ${PACKAGE}.${entry}.service_ip)
    local serviceUser=$(uci get ${PACKAGE}.${entry}.service_user)
    local proto=$(uci get ${PACKAGE}.${entry}.proto)
    local triggerPort=$(uci get ${PACKAGE}.${entry}.trigger_port)
    local openPortStart=$(uci get ${PACKAGE}.${entry}.open_portstart)
    local openPortEnd=$(uci get ${PACKAGE}.${entry}.open_portend)
    local openProto=$(uci get ${PACKAGE}.${entry}.open_proto)

    if [[ ${serviceUser} -eq 0 || "${serviceIp}" == "any" ]]; then
        serviceIp="${routeLanAddress}/${routeLanMask}"
    fi

    if [ -n ${openProto} ]; then
        if [[ "${openProto}" == "TCP/UDP" || "${openProto}" == "tcp/udp" ]]; then
            iptables -t nat -A PREROUTING_WAN -p tcp --dport ${openPortStart}:${openPortEnd} -j TRIGGER --trigger-type dnat --trigger-timeout ${triggerTimeout}
            iptables -t nat -A PREROUTING_WAN -p udp --dport ${openPortStart}:${openPortEnd} -j TRIGGER --trigger-type dnat --trigger-timeout ${triggerTimeout}
            iptables -A FORWARD_WAN  -p tcp --dport ${openPortStart}:${openPortEnd} -j TRIGGER --trigger-type in --trigger-match ${triggerPort} --trigger-relate ${openPortStart}-${openPortEnd} --trigger-timeout ${triggerTimeout}
            iptables -A FORWARD_WAN  -p udp --dport ${openPortStart}:${openPortEnd} -j TRIGGER --trigger-type in --trigger-match ${triggerPort} --trigger-relate ${openPortStart}-${openPortEnd} --trigger-timeout ${triggerTimeout}
            iptables -t nat -A PREROUTING_RULE -s ${serviceIp} -p ${proto} --dport ${triggerPort} -j TRIGGER --trigger-type out --trigger-match ${triggerPort} --trigger-relate ${openPortStart}-${openPortEnd} --trigger-timeout ${triggerTimeout}
            iptables -A porttrigger_log -d ${serviceIp} -i ${wanifname} -p tcp --dport ${openPortStart}:${openPortEnd} -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "porttrigger$(($entryNum+1))"
            iptables -A porttrigger_log -d ${serviceIp} -i ${wanifname} -p udp --dport ${openPortStart}:${openPortEnd} -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "porttrigger$(($entryNum+1))"
        else
            iptables -t nat -A PREROUTING_WAN -p ${openProto} --dport ${openPortStart}:${openPortEnd} -j TRIGGER --trigger-type dnat --trigger-timeout ${triggerTimeout}
            iptables -A FORWARD_WAN -p ${openProto} --dport ${openPortStart}:${openPortEnd} -j TRIGGER --trigger-type in --trigger-match ${triggerPort} --trigger-relate ${openPortStart}-${openPortEnd} --trigger-timeout ${triggerTimeout}
            iptables -t nat -A PREROUTING_RULE -s ${serviceIp} -p ${proto} --dport ${triggerPort} -j TRIGGER --trigger-type out --trigger-match ${triggerPort} --trigger-relate ${openPortStart}-${openPortEnd} --trigger-timeout ${triggerTimeout}
            iptables -A porttrigger_log -d ${serviceIp} -i ${wanifname} -p ${openProto} --dport ${openPortStart}:${openPortEnd} -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "porttrigger$(($entryNum+1))"
        fi
    fi
}

_create_trigger_entries() {
    local entries=$(uci show ${PACKAGE} 2> /dev/null | awk -F'.' '{print $2}' | grep -v '=' | grep '@triggering\[' | uniq | sort)

    if [ -n "$entries" ]; then
        local entry
        for entry in ${entries}
        do
            local entryEnabled=$(uci get ${PACKAGE}.${entry}.enabled    2>/dev/null)
            local entryNum=$(echo "${entry}" | awk -F\[ '{print $2}' | awk -F\] '{print $1}'    2>/dev/null)
            
            if [[ "${entryEnabled}" == "1" ]]; then
                _enable_trigger_entries ${entry} ${entryNum}
            fi
        done
    fi
}

start_service() {
    _create_trigger_iptables
    _empty_trigger_iptables

    if [[ "${triggerEnabled}" == "1" ]]; then
        _create_trigger_entries
    fi
}

_checkSameEntryExist() {
    local old_entry=$1
    local old_entryNname=$(uci get ${OLD_PACKAGE}.${old_entry}.name    2>/dev/null)
    local ret=0
    local entries=$(uci show ${PACKAGE} 2> /dev/null | awk -F'.' '{print $2}' | grep -v '=' | grep '@triggering\[' | uniq | sort)

    if [ -n "$entries" ]; then
        local entry
        for entry in ${entries}
        do
            local entryNname=$(uci get ${PACKAGE}.${entry}.name    2>/dev/null)
            if [[ "${entryNname}" == "${old_entryNname}" ]]; then
                ret=1
            fi
        done
    fi
    return ${ret}
}

add_oldconfig() {
    local old_entries=$(uci show ${OLD_PACKAGE} 2> /dev/null | awk -F'.' '{print $2}' | grep -v '=' | grep '@triggering\[' | uniq | sort)

    if [ -n "$old_entries" ]; then
        local old_entry
        for old_entry in ${old_entries}
        do
            _checkSameEntryExist ${old_entry}
            if [ $? -eq 0 ]; then
                uci add ${PACKAGE} triggering   2>/dev/null
                local entry_configlist="name enabled service_ip service_user proto trigger_port open_portstart open_portend open_proto"
                local config
                for config in ${entry_configlist}
                do
                    local entry_config=$(uci get ${OLD_PACKAGE}.${old_entry}.${config}    2>/dev/null)
                    if [ -n "$entry_config" ]; then
                        uci set ${PACKAGE}.@triggering[-1].${config}=${entry_config}    2>/dev/null
                    else
                        uci delete ${PACKAGE}.@triggering[-1]    2>/dev/null
                        break
                    fi
                done
            fi
            uci delete ${OLD_PACKAGE}.${old_entry}    2>/dev/null
        done
    fi
}

add_oldconfig
start_service

