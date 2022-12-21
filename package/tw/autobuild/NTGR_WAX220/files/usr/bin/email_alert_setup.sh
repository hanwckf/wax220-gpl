#!/bin/sh

smtpc=/usr/sbin/ssmtp
email_enable=$(uci get system.email.enable)
log=/tmp/uci.txt
tmp_log=/tmp/tmp_uci.txt
tail_log=/tmp/uci_tail.txt

if [ "$email_enable" != 1 ];then
	exit
fi

ubus listen UCI_COMMIT_DELTA > /tmp/uci.txt &

print_smtpc_conf()
{
	local smtp_server=$(/sbin/uci get system.email.smtpaddr)
	local smtp_port=$(/sbin/uci get system.email.smtpport)
	echo "mailhub=$smtp_server:$smtp_port"
	echo "FromLineOverride=yes"
	echo "AuthUser=$(/sbin/uci get system.email.user)"
	echo "AuthPass=$(/sbin/uci get system.email.password)"

	if [ "x$smtp_port" = "x465" ]; then
		echo "UseTLS=YES"
	fi
	if [ "x$smtp_port" = "x465" ]; then
		echo "UseSTARTTLS=NO"
	elif [ "x$smtp_port" = "x587" ]; then
		echo "UseSTARTTLS=YES"
	fi
}

print_email_header()
{
	local from="$(/sbin/uci get system.email.from)"
	local addr="$(/sbin/uci get system.email.alert_to)"
	local subject="$(/sbin/uci get system.email.subject)"

	cat <<EOF
Subject: $subject
From: $from
To: $addr

EOF
}

print_log()
{
	local time="$(/bin/date)"
	tail -n$((line2-line1)) $log > $tail_log
	print_email_header
	cat $tail_log | while read line
	do
		echo $line > $tmp_log
		local package="$(cat $tmp_log | cut -d ":" -f 3 | cut -d "," -f 0 | sed 's/\"//g')"
		local section_name="$(cat $tmp_log | cut -d ":" -f 7 | cut -d "," -f 0 | sed 's/\"//g')"
		local name="$(cat $tmp_log | cut -d ":" -f 9 | cut -d "," -f 0 | sed 's/\"//g')"
		local value="$(cat $tmp_log | cut -d ":" -f 10 | cut -d "}" -f 0 | sed 's/\"//g')"
		local str="[Configuration Changed]-$package.$section_name.$name='$value'"

		if [ "x$1" != "xtest" ]; then
			echo "$str"
		fi
	done
	echo "--"
	echo "$time"
}

sendmail()
{
	local conf=/tmp/ssmtp.conf
	local email_file=/tmp/tmp_email_file
	local addr="$(/sbin/uci get system.email.alert_to)"
	print_smtpc_conf > $conf
	print_log "$1" > $email_file
	rm $tmp_log
	cat $email_file | $smtpc -C$conf $addr
}

case "$1" in
	test) sendmail "test";;
esac

while true
do

	if [ -f "$log" ]; then
		md5sum1="$(md5sum $log | awk '{print $1}')"
		line1="$(sed -n '$=' $log)"
	fi

	sleep 3

	if [ -f "$log" ]; then
		md5sum2="$(md5sum $log | awk '{print $1}')"
		line2="$(sed -n '$=' $log)"
	fi

	if [ $md5sum1 != $md5sum2 ]; then
		sendmail
	fi

done

exit 0
