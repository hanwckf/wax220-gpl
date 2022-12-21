#!/bin/sh
clear_switch="$1"
clear_bridge="$2"

echo "param1  1--> clear switch table"
echo "param1  2--> clear non-local bridge table"

if [ $clear_switch = "1" ]; then
	echo "execute clear switch table"
	switch clear
fi
if [ $clear_bridge = "1" ]; then
	echo "execute clear non-local bridge table"
	bridge_name=`cat br_name | awk '{ print $1}'`
	ip link set $bridge_name type bridge fdb_flush
fi
