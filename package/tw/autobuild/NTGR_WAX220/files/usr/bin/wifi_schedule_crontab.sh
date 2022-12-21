#!/bin/sh

ifaceId=$1
ifname2g=$2
ifname2gAction=$3
ifname5g=$4
ifname5gAction=$5

ifName2gSwitch=$(uci get wireless.@wifi-iface[$ifaceId].radio 2> /dev/null)
if [ "$ifname2gAction" = "up" ]; then
    if [ $ifName2gSwitch -eq 1 ]; then
        ifconfig $ifname2g up
    fi
elif [ "$ifname2gAction" = "down" ]; then
    ifconfig $ifname2g down
fi

ifName5gSwitch=$(uci get wireless.@wifi-iface[$((ifaceId+5))].radio 2> /dev/null)
if [ "$ifname5gAction" = "up" ]; then
    if [ $ifName5gSwitch -eq 1 ]; then
        ifconfig $ifname5g up
    fi
elif [ "$ifname5gAction" = "down" ]; then
    ifconfig $ifname5g down
fi
