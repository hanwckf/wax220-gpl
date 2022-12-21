#!/bin/sh

SCRIPT=$0
LOCKFILE=/tmp/email_schedule.lock
LOGFILE=/tmp/log/email_schedule.log
LOGGING=0 #default is off
#PACKAGE=email
TW_OP=$1
TW_CRON_ENTRY=$2

_log()
{
    if [ ${LOGGING} -eq 1 ]; then
        local ts=$(date)
        echo "$ts $@" >> ${LOGFILE}
    fi
}

_exit()
{
    local rc=$1
    lock -u ${LOCKFILE}
    exit ${rc}
}

_cron_restart()
{
    /etc/init.d/cron restart > /dev/null
}

_add_cron_script()
{
    (crontab -l ; echo "$1") | sort | uniq | crontab -
    _cron_restart
}

_rm_cron_script()
{
    crontab -l | grep -v "$1" |  sort | uniq | crontab -
    _cron_restart
}

_get_uci_value_raw()
{
    local value
    value=$(uci get $1 2> /dev/null)
    local rc=$?
    echo ${value}
    return ${rc}
}

_get_uci_value()
{
    local value
    value=$(_get_uci_value_raw $1)
    local rc=$?
    if [ ${rc} -ne 0 ]; then
        _log "Could not determine UCI value $1"
        return 1
    fi
    echo ${value}
}

_format_dow_list()
{
    local dow=$1
    local flist=""
    local day
    for day in ${dow}
    do
        if [ ! -z ${flist} ]; then
            flist="${flist},"
        fi
        flist="${flist}${day:0:3}"
    done
    echo ${flist}
}

add_email_schedule_cron()
{
    _add_cron_script "${TW_CRON_ENTRY}"
}

rm_email_schedule_cron()
{
    _rm_cron_script "${TW_CRON_ENTRY}"
}

usage()
{
    echo ""
    echo "$0 rmcron|addcron|help"
    echo ""
    echo "    UCI Config File: /etc/config/system"
    echo ""
    echo "    rmcron: rm email log schedule."
    echo "    addcron: add email log schedule"
    echo "    help: This description."
    echo ""
}

###############################################################################
# MAIN
###############################################################################
#LOGGING=$(_get_uci_value ${GLOBAL}.logging) || _exit 1
_log ${SCRIPT} $1
lock ${LOCKFILE}

case "$1" in
    rmcron) rm_email_schedule_cron ;;
    addcron) add_email_schedule_cron ;;
    help|--help|-h|*) usage ;;
esac

_exit 0
