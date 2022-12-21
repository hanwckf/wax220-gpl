#!/bin/sh
# (C) 2008 openwrt.org

i=0
while true
do
	sleep 1
	let i++
	echo -ne "\r$i.." > /dev/console
	if [ $i -eq 20 ]
	then
		led.sh timer power amber 250 750
	fi
done

