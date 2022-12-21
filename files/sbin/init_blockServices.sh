#!/bin/bash 

option=$1
need_update=1
netmode=$(uci get system.@system[0].netmode 2> /dev/null)
netmode="${netmode:-"router"}"
[ "$netmode" != "router" ] && exit 0

block_option=$(uci get block_services.config.block_option 2> /dev/null)
iptables -N block_services 2> /dev/null
if [ "$?" = "1" -a "$option" != "update_rules" ];then
    need_update=0
fi
iptables -N block_services_log 2> /dev/null

if [ "$block_option" = "always" ];then
    iptables -D FORWARD -j block_services 2> /dev/null
    iptables -D FORWARD -j block_services_log 2> /dev/null
    iptables -I FORWARD -j block_services
    iptables -I FORWARD -j block_services_log
#   perschedule setup in /etc/init.d/done
elif [ "$block_option" = "perschedule" ];then
    sh /usr/bin/filtering_schedule.sh add blockservice
    sh /etc/init.d/filteringschedule restart
fi

#if not need to update block services rule, exit
[ "$need_update" = "0" ] && exit 0

[ -f /tmp/block_services_lock ] && exit 0
touch /tmp/block_services_lock

iptables -F block_services
iptables -F block_services_log
# the max number of block services is 20
for i in $(seq 0 19); do
    rule=$(uci get block_services.@rule[$i] 2> /dev/null)
    if [ "x$rule" = "x" ];then
         break;
    fi

    portstart=$(uci get block_services.@rule[$i].portstart 2> /dev/null)
    portend=$(uci get block_services.@rule[$i].portend 2> /dev/null)
    iptype=$(uci get block_services.@rule[$i].iptype 2> /dev/null)
    iprange_start=$(uci get block_services.@rule[$i].iprange_start 2> /dev/null)
    iprange_end=$(uci get block_services.@rule[$i].iprange_end 2> /dev/null)
    only_ip=$(uci get block_services.@rule[$i].only_ip 2> /dev/null)
    protocol=$(uci get block_services.@rule[$i].protocol 2> /dev/null)
    userdefined=$(uci get block_services.@rule[$i].userdefined | base64 2> /dev/null)

    proto_tcp=""
    proto_udp=""
    if [ "$protocol" = "TCP" ];then
        proto_tcp="-p tcp"
    elif [ "$protocol" = "UDP" ];then
        proto_udp="-p udp"
    else
        proto_tcp="-p tcp"
        proto_udp="-p udp"
    fi

    for proto in "$proto_tcp" "$proto_udp"
    do
        if [ "x$proto" = "x" ];then
            continue
        fi
        if [ "$iptype" = "single" ];then
            iptables -A block_services $proto --dport $portstart:$portend -s $only_ip -j DROP
            iptables -A block_services_log $proto --dport $portstart:$portend -s $only_ip -m limit --limit 5/s -j NFLOG --nflog-group 2 --nflog-prefix "blockService${userdefined}"
        elif [ "$iptype" = "range_addr" ];then
            iptables -A block_services $proto --dport $portstart:$portend -m iprange --src-range ${iprange_start}-${iprange_end} -j DROP
            iptables -A block_services_log $proto --dport $portstart:$portend -m iprange --src-range ${iprange_start}-${iprange_end} -m limit --limit 5/s -j NFLOG --nflog-group 2 --nflog-prefix "blockService${userdefined}"
        else
            iptables -A block_services $proto --dport $portstart:$portend -j DROP
            iptables -A block_services_log $proto --dport $portstart:$portend -m limit --limit 5/s -j NFLOG --nflog-group 2 --nflog-prefix "blockService${userdefined}"
        fi
    done
done
rm -fr /tmp/block_services_lock

