#!/bin/sh

internetOK=0
isTimeCover=0
month=$(date +%m)
day==$(date +%d)
week=$(date +%w)
hour=$(date +%H)
minute=$(date +%M)
startMonth=$(uci get system.ntp.start_month 2> /dev/null)
startWeek=$(uci get system.ntp.start_week 2> /dev/null)
startDay=$(uci get system.ntp.start_day 2> /dev/null)
startHour=$(uci get system.ntp.start_hour 2> /dev/null)
endMonth=$(uci get system.ntp.end_month 2> /dev/null)
endWeek=$(uci get system.ntp.end_week 2> /dev/null)
endDay=$(uci get system.ntp.end_day 2> /dev/null)
endHour=$(uci get system.ntp.end_hour 2> /dev/null)
daylightSavingEnable=$(uci get system.ntp.dst_enable 2> /dev/null)
ntpSyncOkFile="/tmp/ntp_sync_ok"

if [ $daylightSavingEnable -eq 1 ]; then
    ping -c 2 8.8.8.8 > /tmp/ping_test.txt 2>&1
    exec < /tmp/ping_test.txt 
    read FILE_CONTENT
    while [[ $? -eq 0 ]];do
    	result=$(echo $FILE_CONTENT | grep "bytes from")
    	if [[ "$result" != "" ]]; then
            internetOK=1
            break
    	fi
        read FILE_CONTENT	
    done

    if [ $internetOK -eq 0 ]; then
        exit
    fi

    if [ $startMonth -lt $endMonth ]; then
    	if [ $startMonth -lt $month -a $month -lt $endMonth ]; then
            isTimeCover=1
    	elif [ $month -eq $startMonth ]; then
            weekId1stDay = $(($week - ($day%7) + 1))
            if [ $weekId1stDay -lt 0 ]; then
                weekId1stDay = $(($weekId1stDay + 7))
            fi
    		if [ $weekId1stDay -eq $startDay ]; then
                setDay = $((1 + ($startWeek - 1)*7))
    		elif [ $weekId1stDay -gt $startDay ]; then
                setDay = $((8 + $startDay - $weekId1stDay + ($startWeek - 1)*7))
            else
                setDay = $((1 + $startDay - $weekId1stDay + ($startWeek - 1)*7))
            fi
    		if [ $day -gt $setDay ]; then
                isTimeCover=1
            elif [ $setDay -eq $day ]; then
                if [ $hour -ge $startHour ]; then
                    isTimeCover=1
                fi
            fi
        elif [ $month -eq $endMonth ]; then
            weekId1stDay = $(($week - ($day%7) + 1))
            if [ $weekId1stDay -lt 0 ]; then
                weekId1stDay = $(($weekId1stDay + 7))
            fi
            if [ $weekId1stDay -eq $endDay ]; then
                setDay = $((1 + ($endWeek - 1)*7))
            elif [ $weekId1stDay -gt $endDay ]; then
                setDay = $((8 + $endDay - $weekId1stDay + ($endWeek - 1)*7))
            else
                setDay = $((1 + $endDay - $weekId1stDay + ($endWeek - 1)*7))
            fi
            if [ $day -lt $setDay ]; then
                isTimeCover=1
            elif [ $setDay -eq $day ]; then
                if [ $hour -lt $endHour ]; then
                    isTimeCover=1
                fi
            fi
        fi
    elif [ $startMonth -eq $endMonth ]; then
        if [ $month -eq $startMonth ]; then
            weekId1stDay = $(($week - ($day%7) + 1))
            if [ $weekId1stDay -lt 0 ]; then
                weekId1stDay = $(($weekId1stDay + 7))
            fi
            if [ $weekId1stDay -eq $startDay ]; then
                setDay = $((1 + ($startWeek - 1)*7))
            elif [ $weekId1stDay -gt $startDay ]; then
                setDay = $((8 + $startDay - $weekId1stDay + ($startWeek - 1)*7))
            else
                setDay = $((1 + $startDay - $weekId1stDay + ($startWeek - 1)*7))
            fi
            if [ $setDay -lt $day ]; then
                isTimeCover=1
            elif [ $setDay -eq $day ]; then
                if [ $startHour -le $hour ]; then
                    isTimeCover=1
                fi
            fi
        fi
    else
        if [ $month -gt $startMonth -o $month -lt $endMonth ]; then
            isTimeCover=1
        elif [ $month -eq $endMonth ]; then
            weekId1stDay = $(($week - ($day%7) + 1))
            if [ $weekId1stDay -lt 0 ]; then
                weekId1stDay = $(($weekId1stDay + 7))
            fi
            if [ $weekId1stDay -eq $endDay ]; then
                setDay = $((1 + ($endWeek - 1)*7))
            elif [ $weekId1stDay -gt $endDay ]; then
                setDay = $((8 + $endDay - $weekId1stDay + ($endWeek - 1)*7))
            else
                setDay = $((1 + $endDay - $weekId1stDay + ($endWeek - 1)*7))
            fi
            if [ $day -lt $setDay ]; then
                isTimeCover=1
            elif [ $setDay -eq $day ]; then
                if [ $hour -lt $endHour ]; then
                    isTimeCover=1
                fi
            fi
        elif [ $month -eq $startMonth ]; then
            weekId1stDay = $(($week - ($day%7) + 1))
            if [ $weekId1stDay -lt 0 ]; then
                weekId1stDay = $(($weekId1stDay + 7))
            fi
            if [ $weekId1stDay -eq $startDay ]; then
                setDay = $((1 + ($startWeek - 1)*7))
            elif [ $weekId1stDay -gt $startDay ]; then
                setDay = $((8 + $startDay - $weekId1stDay + ($startWeek - 1)*7))
            else
                setDay = $((1 + $startDay - $weekId1stDay + ($startWeek - 1)*7))
            fi
            if [ $day -gt $setDay ]; then
                isTimeCover=1
            elif [ $setDay -eq $day ]; then
                if [ $hour -ge $startHour ]; then
                    isTimeCover=1
                fi
            fi
        fi
    fi

    if [ $isTimeCover -eq 1 ]; then
        time=$(date +%s)
        offset=3600
        adjust_time=`expr $time + $offset`
        time_str=$(date -d @$adjust_time)
        year=`echo $time_str | awk -F ' ' '{print $6}'`
        month_name=`echo $time_str | awk -F ' ' '{print $2}'`
        
        case $month_name in
            Jan)
                month=1
                ;;
            Feb)
                month=2
                ;;
            Mar)
                month=3
                ;;
            Apr)
                month=4
                ;;
            May)
                month=5
                ;;
            Jun)
                month=6
                ;;
            Jul)
                month=7
                ;;
            Aug)
                month=8
                ;;
            Sep)
                month=9
                ;;
            Oct)
                month=10
                ;;
            Nov)
                month=11
                ;;
            Dec)
                month=12
                ;;
        esac
        
        day=`echo $time_str | awk -F ' ' '{print $3}'`
        time=`echo $time_str | awk -F ' ' '{print $4}'`
        full_time=`echo $year-$month-$day $time`
        if [ -f "$ntpSyncOkFile" ]; then
            date -s "$full_time"
            /etc/init.d/sysntpd stop
        fi
    fi
fi
