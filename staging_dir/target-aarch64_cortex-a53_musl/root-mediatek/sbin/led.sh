#!/bin/sh
# (C) 2008 openwrt.org

. /lib/functions.sh
ACTION=$1
NAME=$2
COLOUR=$3
do_led() {
	local name
	local sysfs
	config_get name $1 name
	config_get board $1 board
	[ "$name" = "$NAME" -o "$sysfs" = "$NAME" -a -e "/sys/class/leds/${board}:${COLOUR}:${name}" ] && {
        [ "$ACTION" = "set" ] && {
            echo default-on >/sys/class/leds/${board}:${COLOUR}:${name}/trigger
            exit 0
        }
        [ "$ACTION" = "clear" ] && {
			echo none >/sys/class/leds/${board}:${COLOUR}:${name}/trigger
            exit 0
        }
        [ "$ACTION" = "blink" ] && {
			echo timer >/sys/class/leds/${board}:${COLOUR}:${name}/trigger
            exit 0
        }
        [ "$ACTION" = "heartbeat" ] && {
			echo heartbeat >/sys/class/leds/${board}:${COLOUR}:${name}/trigger
            exit 0
        }
	}
}

[ -n "$1" ] && [ -n "$2" ]
	[ -n "$3" ] &&{
		config_load system
		config_foreach do_led
		exit 1
	}
    echo "led.sh  <set|clear|blink|heartbeat>  <power|net|wifin|wifia>  <green|red>"
