#!/bin/sh

time=$(date +%s)
offset=3600

if [ $1 -eq 1 ]
then
    adjust_time=`expr $time + $offset`
    $(uci set system.ntp.dst_implement='1')
    $(uci commit system)
elif [ $1 -eq 0 ]
then
    adjust_time=`expr $time - $offset`
    $(uci set system.ntp.dst_implement='0')
    $(uci commit system)
else
    exit
fi

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
week_index=1
week_days=7
num=1

if [ $day -le 8 ]
then
    num=1
else
    while [ `expr $day - $week_days` -gt 0 ]
    do
        day=`expr $day - $week_days`
        num=`expr $num + 1`
    done
fi

if [ $num -eq $2 ]
then
    date -s "$full_time"
fi
