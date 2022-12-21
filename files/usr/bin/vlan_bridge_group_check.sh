#!/bin/sh

netmode=$(uci get system.@system[0].netmode 2> /dev/null)
netmode="${netmode:-"router"}"
[ "$netmode" != "router" ] && exit 1

group_mode=$(uci get vlanctl.global.mode 2> /dev/null)
enabled=$(uci get vlanctl.global.enabled 2> /dev/null)

if [ "$enabled" != "1" ];then
    exit 1
fi

if [ "$group_mode" = "bridge" ];then
    ssidlist=$(uci get vlanctl.bridge.ssid 2> /dev/null)
    for ssid in $ssidlist
    do
        radio=$(uci get wireless.@wifi-iface[$ssid].radio 2> /dev/null)
        if [ "$radio" = "1" ];then
            ifname=$(uci get wireless.@wifi-iface[$ssid].ifName 2> /dev/null)
            if [ "x$ifname" != "x" ];then
                isUp=$(ifconfig | grep "$ifname" 2> /dev/null)
                if [ "x$isUp" = "x" ];then
                    brctl delif br-lan $ifname
                    ifconfig $ifname up
                    brctl addif br-wan $ifname
                    echo "bridge group bring up" $ifname
                fi
            fi
        fi
        radio=$(uci get wireless.@wifi-iface[$(($ssid+3))].radio 2> /dev/null)
        if [ "$radio" = "1" ];then
            ifname=$(uci get wireless.@wifi-iface[$(($ssid+3))].ifName 2> /dev/null)
            if [ "x$ifname" != "x" ];then
                isUp=$(ifconfig | grep "$ifname" 2> /dev/null)
                if [ "x$isUp" = "x" ];then
                    brctl delif br-lan $ifname
                    ifconfig $ifname up
                    brctl addif br-wan $ifname
                    echo "bridge group bring up" $ifname
                fi
            fi
        fi
    done
fi

if [ "$group_mode" = "vlan" ];then
    for i in $(seq 0 31); do
        vlan_enable=$(uci get vlanctl.@vlan[$i].enabled 2> /dev/null)
        if [ "x$vlan_enable" = "x" ];then
            break
        fi

        if [ "$vlan_enable" = "1" ];then
            vlan=$(uci get vlanctl.@vlan[$i].vlan 2> /dev/null)
            if [ "x$vlan" != "x" ];then
                ssidlist=$(uci get vlanctl.@vlan[$i].ssid 2> /dev/null)
                for ssid in $ssidlist
                do
                    radio=$(uci get wireless.@wifi-iface[$ssid].radio 2> /dev/null)
                    if [ "$radio" = "1" ];then
                        ifname=$(uci get wireless.@wifi-iface[$ssid].ifName 2> /dev/null)
                        if [ "x$ifname" != "x" ];then
                            isUp=$(ifconfig | grep "$ifname" 2> /dev/null)
                            if [ "x$isUp" = "x" ];then
                                brctl delif br-lan $ifname
                                ifconfig $ifname up
                                brctl addif br-vlan$vlan $ifname
                                echo "vlan group bring up" $ifname
                            fi
                        fi
                    fi
                    radio=$(uci get wireless.@wifi-iface[$(($ssid+3))].radio 2> /dev/null)
                    if [ "$radio" = "1" ];then
                        ifname=$(uci get wireless.@wifi-iface[$(($ssid+3))].ifName 2> /dev/null)
                        if [ "x$ifname" != "x" ];then
                            isUp=$(ifconfig | grep "$ifname" 2> /dev/null)
                            if [ "x$isUp" = "x" ];then
                                brctl delif br-lan $ifname
                                ifconfig $ifname up
                                brctl addif br-vlan$vlan $ifname
                                echo "vlan group bring up" $ifname
                            fi
                        fi
                    fi
                done
            fi
        fi
    done
fi
