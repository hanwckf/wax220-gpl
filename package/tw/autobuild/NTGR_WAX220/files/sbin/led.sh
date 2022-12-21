#!/bin/sh
# (C) 2008 openwrt.org

. /lib/functions.sh

do_led_action() {
	if [ $colour = "blue" -o $colour = "green" -o $colour = "amber" ];then
		if [ -e "/sys/class/leds/${board}:${colour}:$1" ] ;then
			echo $control > /sys/class/leds/${board}:${colour}:$1/power_ctl
			echo ${trigger} > /sys/class/leds/${board}:${colour}:$1/trigger
			[ -n "$ON_TIME" ] && echo $ON_TIME >/sys/class/leds/${board}:${colour}:$1/delay_on
			[ -n "$OFF_TIME" ] && echo $OFF_TIME >/sys/class/leds/${board}:${colour}:$1/delay_off
		fi
	elif [ $colour = "mixed" ];then
		for item in green blue amber;
		do
			if [ $colour != "mixed" ];then
				continue;
			fi
			if [ -e "/sys/class/leds/${board}:${item}:$1" ];then
				echo $control > /sys/class/leds/${board}:${item}:$1/power_ctl
				echo ${trigger} > /sys/class/leds/${board}:${item}:$1/trigger
				[ -n "$ON_TIME" ] && echo $ON_TIME >/sys/class/leds/${board}:${item}:$1/delay_on
				[ -n "$OFF_TIME" ] && echo $OFF_TIME >/sys/class/leds/${board}:${item}:$1/delay_off
			fi
		done
	fi
}

do_led() {
    config_get board $1 model
    if [ $name = "all" ];then
        for item in power net wifin wifia;
        do
            do_led_action $item
        done
    else
        do_led_action $name
    fi
}

if [ "$#" -lt "2" ] ; then
    echo "usage: led.sh  <default-on|on|off|none|timer>  <all|power|net|wifin|wifia|>  <green|blue|amber|mixed> [on_time ms] [off_time ms]"
else
    colour=both
    trigger=$1
    control='0'
    name=$2
    board="AP"
    if [ $1 = "on" -o $1 = "default-on" ];then
        trigger=default-on
        control="1"
    fi
    if [ $1 = "off" -o $1 = "none" ];then
        trigger=none
        control="0"
    fi

    if [ "$#" -ge "3" ] ; then
        colour=$3
    fi
    if [ $trigger = "timer" ];then
        if [ "$#" -lt "5" ];then
            exit 1
        fi
        ON_TIME=$4
        OFF_TIME=$5
        control="2"
    fi
    config_load system
    config_foreach do_led system
    exit 1
fi
