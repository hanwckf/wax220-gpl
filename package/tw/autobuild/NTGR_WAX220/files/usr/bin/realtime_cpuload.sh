#!/bin/sh

log=/tmp/cpu_load.txt


while true
do

cpu_load="$(mpstat -P ALL 1 1 | grep 'Average' | grep -v 'CPU' | grep 'all' | awk '{print$11}')"
time="$(cat /proc/uptime | awk '{print$1}' | cut -d '.' -f 0)"
str="$time $cpu_load"
echo $str >> $log

line="$(sed -n '$=' $log)"
		if [ $line -gt 60 ]; then
			sed -i '1d' $log
		fi

done

exit 0
