#!/bin/sh

cli_enable=$(uci get system.@system[0].cli_enable)

if [ "$cli_enable" = "1" ]; then
	passwd -u root
	passwd -u admin
elif [ "$cli_enable" = "0" ]; then
	passwd -l root
	passwd -l admin
fi

exit 0

