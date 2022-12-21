#!/bin/sh

log=/tmp/if_statistics.txt

while true
do
	ifname="$(cat /proc/net/dev | grep -E 'ra|eth' | grep -v 'eth1\.' | grep -Ev 'Inter|face' | awk -F ' ' '{print $1}' | awk -F ':' '{print $1}')"
	rx_bytes="$(cat /proc/net/dev | grep -E 'ra|eth' | grep -Ev 'Inter|face' | awk -F ' ' '{print $2}')"
	tx_bytes="$(cat /proc/net/dev | grep -E 'ra|eth' | grep -Ev 'Inter|face' | awk -F ' ' '{print $10}')"
	time="$(cat /proc/uptime | awk '{print$1}' | cut -d '.' -f 0)"
	str="$ifname $rx_bytes $tx_bytes $time"
	echo $str >> $log
	line="$(sed -n '$=' $log)"
	if [ $line -gt 60 ]; then
		sed -i '1d' $log
	fi
	sleep 1
done
exit 0


