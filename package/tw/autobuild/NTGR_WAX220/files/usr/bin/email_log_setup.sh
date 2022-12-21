#!/bin/sh
email_notify=$(uci get system.email.email_notify)
netmode=$(uci get system.@system[0].netmode 2> /dev/null)

if [ "$email_notify" != 1 -o "$netmode" == "wds" ];then
    email_schedule.sh rmcron email
    exit
fi

is_24h=0
guiRegion=$(uci get system.@system[0].guiRegion)
netgearRegion=$(protest --region -r | sed 's/[!~]//g')
if [ "$guiRegion" == "German" -a "$netgearRegion" == "WW" ] || [ "$netgearRegion" == "GR" ];then
    is_24h=1
fi

# create cron entry
alert_select=$(uci get system.email.alert_select)
if [ "$alert_select" == "full" ]; then
    cron_entry="*/1 * * * * /usr/bin/email_log email_full_log"
elif [ "$alert_select" == "Hourly" ]; then
    cron_entry="0 */1 * * * /usr/bin/email_log email_log"
elif [ "$alert_select" == "Daily" ]; then
    alert_hour=$(uci get system.email.alert_hour)
    [ "x$alert_hour" == "x" -o "$alert_hour" -lt 0 -o "$alert_hour" -gt 24 ] && exit 1
    if [ "$is_24h" -eq 1 ];then
        cron_entry="0 $alert_hour * * * /usr/bin/email_log email_log"
    else
        alert_am=$(uci get system.email.alert_am)
        if [ "$alert_am" == "pm" ]; then
            alert_hour=$(($alert_hour + 12))
        fi
        cron_entry="0 $alert_hour * * * /usr/bin/email_log email_log"
    fi
elif [ "$alert_select" == "Weekly" ]; then
    alert_day=$(uci get system.email.alert_day)
    [ "x$alert_day" == "x" -o "$alert_day" -lt 0 -o "$alert_day" -gt 6 ] && exit 1
    alert_hour=$(uci get system.email.alert_hour)
    [ "x$alert_hour" == "x" -o "$alert_hour" -lt 0 -o "$alert_hour" -gt 24 ] && exit 1
    if [ "$is_24h" -eq 1 ];then
        cron_entry="0 $alert_hour * * $alert_day /usr/bin/email_log email_log"
    else
        alert_am=$(uci get system.email.alert_am)
        if [ "$alert_am" == "pm" ]; then
            alert_hour=$(($alert_hour + 12))
        fi
        cron_entry="0 $alert_hour * * $alert_day /usr/bin/email_log email_log"
    fi
else
    exit
fi

# rmcron email
email_schedule.sh rmcron email

# addcron email
email_schedule.sh addcron "$cron_entry"

exit 0
