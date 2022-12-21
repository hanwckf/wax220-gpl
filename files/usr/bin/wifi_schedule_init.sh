#!/bin/sh

week=$(date +%w)
hour=$(date +%H)
minute=$(date +%M)

wifiScheduleEnable=$(uci get wifi_schedule.wireless.ScheduleEnable 2> /dev/null)
if [ $wifiScheduleEnable -eq 1 ]; then
    for i in $(seq 0 3); do
        isTimeCover=0
        ifName2G=$(uci get wireless.@wifi-iface[$i].ifName 2> /dev/null)
        ifName2GSwitch=$(uci get wireless.@wifi-iface[$i].radio 2> /dev/null)
        ifName5G=$(uci get wireless.@wifi-iface[$((i+5))].ifName 2> /dev/null)
        ifName5GSwitch=$(uci get wireless.@wifi-iface[$((i+5))].radio 2> /dev/null)
        status=$(uci get wifi_schedule.cfg_iface${i}_day${week}.status 2> /dev/null)
        timeStart=$(uci get wifi_schedule.cfg_iface${i}_day${week}.timeStart 2> /dev/null)
        timeEnd=$(uci get wifi_schedule.cfg_iface${i}_day${week}.timeEnd 2> /dev/null)

    	if [ ${#status} -gt 0 ] && [ ${#timeStart} -gt 0 ] && [ ${#timeEnd} -gt 0 ]; then
            startHour=${timeStart%:*}
            startMinute=${timeStart#*:}
            endHour=${timeEnd%:*}
            endMinute=${timeEnd#*:}
            if [ $startHour -eq $hour ]; then
    	    	if [ $hour -eq $endHour ]; then
                    if [ $startMinute -le $minute -a $minute -lt $endMinute ]; then
                        isTimeCover=1
                    fi
    	    	elif [ $hour -lt $endHour ]; then
                    if [ $startMinute -le $minute ]; then
                        isTimeCover=1
                    fi
    	    	fi
            elif [ $startHour -lt $hour ]; then
    	    	if [ $hour -lt $endHour ]; then
                    isTimeCover=1
    	    	elif [ $hour -eq $endHour ]; then
                    if [ $minute -lt $endMinute ]; then
                        isTimeCover=1
                    fi
    	    	fi
            fi
    	fi

    	if [[ $status -eq 1 ]]; then
            if [ $isTimeCover -eq 1 ]; then
    	    	if [ $ifName2GSwitch -eq 1 ]; then
    	    	    ifconfig $ifName2G up
    	    	fi
    	    	if [ $ifName5GSwitch -eq 1 ]; then
    	    	    ifconfig $ifName5G up
    	    	fi
            else
    	    	ifconfig $ifName2G down
    	    	ifconfig $ifName5G down
            fi
    	elif [[ $status -eq 0 ]]; then
            if [ $isTimeCover -eq 0 ]; then
    	    	if [ $ifName2GSwitch -eq 1 ]; then
    	    	    ifconfig $ifName2G up
    	    	fi
    	    	if [ $ifName5GSwitch -eq 1 ]; then
    	    	    ifconfig $ifName5G up
    	    	fi
            else
    	    	ifconfig $ifName2G down
    	    	ifconfig $ifName5G down
            fi
    	fi
    done
fi
