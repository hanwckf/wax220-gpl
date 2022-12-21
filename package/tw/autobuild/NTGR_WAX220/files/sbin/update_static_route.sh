#!/bin/bash 

iface=$1
new_gateway=$2
new_netmask=$3
no_reload=$4
network_change=0

netmode=$(uci get system.@system[0].netmode 2> /dev/null)
netmode="${netmode:-"router"}"
[ "$netmode" != "router" ] && exit 1
[ "x$iface" = "x" -o "x$new_gateway" = "x" -o "x$new_netmask" = "x" ] && exit 1

aton()
{
    echo $1|awk '{c=256;split($0,ip,".");print ip[4]+ip[3]*c+ip[2]*c^2+ip[1]*c^3}'
}

tag=0
# the max number of static route is 32
for i in $(seq 0 31); do
    route=$(uci get static_route.@route[$i] 2> /dev/null)
    if [ "x$route" = "x" ];then
         break;
    fi

    gateway=$(uci get static_route.@route[$i].gateway 2> /dev/null)
    active=$(uci get static_route.@route[$i].active 2> /dev/null)
    interface=$(uci get static_route.@route[$i].interface 2> /dev/null)

    if [ "$active" = "0" ];then
        continue
    fi
    
    if [ "x$interface" = "x" ];then
        gatewayn=$(aton $gateway)
        new_gatewayn=$(aton $new_gateway)
        new_netmaskn=$(aton $new_netmask)
        if [ $(($gatewayn & $new_netmaskn)) -eq $(($new_gatewayn & $new_netmaskn)) ];then
            uci set static_route.@route[$i].interface=$iface
            target=$(aton $(uci get static_route.@route[$i].target 2> /dev/null))
            uci set network.route${target}=route
            uci set network.route${target}.target=$(uci get static_route.@route[$i].target 2> /dev/null)
            uci set network.route${target}.netmask=$(uci get static_route.@route[$i].netmask 2> /dev/null)
            uci set network.route${target}.gateway=$(uci get static_route.@route[$i].gateway 2> /dev/null)
            uci set network.route${target}.private=$(uci get static_route.@route[$i].private 2> /dev/null)
            uci set network.route${target}.active=$(uci get static_route.@route[$i].active 2> /dev/null)
            uci set network.route${target}.metric=$(uci get static_route.@route[$i].metric 2> /dev/null)
            if [ "$iface" = "br-lan" ];then
                uci set network.route${target}.interface=lan
            elif [ "$iface" = "pptp-vpn" -o "$iface" = "l2tp-vpn" ];then
                uci set network.route${target}.interface=vpn
            else
                uci set network.route${target}.interface=wan
            fi
            network_change=1
        fi
    elif [ "$interface" = "$iface" ];then
        gatewayn=$(aton $gateway)
        new_gatewayn=$(aton $new_gateway)
        new_netmaskn=$(aton $new_netmask)
        if [ $(($gatewayn & $new_netmaskn)) -ne $(($new_gatewayn & $new_netmaskn)) ];then
            target=$(aton $(uci get static_route.@route[$i].target 2> /dev/null))
            remove_route[$tag]=$i
            remove_network_route[$tag]=$target
            tag=$(($tag + 1))
        fi
    fi
done

if [ ${#remove_route[@]} -gt 0 ];then
    j=${#remove_route[@]}
    while [ $j -gt 0 ]
    do
        j=$(($j - 1))
        if [ "$iface" = "br-lan" ];then
            uci delete static_route.@route[${remove_route[${j}]}]
        fi
        uci set static_route.@route[${remove_route[${j}]}].interface=
        uci delete network.route${remove_network_route[${j}]}
        network_change=1
    done
fi

if [ "$network_change" = "1" ];then
    uci commit static_route
    uci commit network
    if [ "$no_reload" != "no_reload" ];then
        /etc/init.d/network reload
    fi
fi
