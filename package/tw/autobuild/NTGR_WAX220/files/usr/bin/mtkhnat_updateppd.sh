#!/bin/sh

modes=
gppdev=$(cat /sys/kernel/debug/hnat/hnat_ppd_if | awk -F' ' '{print $5}' | awk -F'=' '{print $2}')

case "$1" in
	*rem) 
		modes="remove"
	;;
	*add)
		modes="add"
	;;
	*) echo "Invalid command: $1";;
esac

if [ "$modes" = "remove" ]; then
	if [ "$gppdev" = "$2" ]; then
		echo "eth0" > /sys/kernel/debug/hnat/hnat_ppd_if
	fi
elif [ "$modes" = "add" ]; then
	for iface in $(uci get network.lan.ifname 2>/dev/null); do
		if [[ "$gppdev" = "eth0" ]] && [[ "$iface" = "$2" ]]; then
			echo "$2" > /sys/kernel/debug/hnat/hnat_ppd_if
			exit 0
		fi
		if [[ -z "$gppdev" ]] && [[ "$iface" = "$2" ]]; then
			echo "$2" > /sys/kernel/debug/hnat/hnat_ppd_if
			exit 0
		fi
		if [[ -z "$gppdev" ]] && [[ "$iface" = "$2" ]]; then
			echo "$2" > /sys/kernel/debug/hnat/hnat_ppd_if
			exit 0
		fi
	done
fi