#!/bin/bash 

netmode=$(uci get system.@system[0].netmode 2> /dev/null)
netmode="${netmode:-"router"}"
wanifname=$(uci get network.wan.ifname 2> /dev/null)
[ "$netmode" != "router" -o "x$wanifname" = "x" ] && exit 1

iptables -N pfw_log 2> /dev/null
iptables -F pfw_log
iptables -t nat -N pfw_zone_lan_postrouting 2> /dev/null
iptables -t nat -F pfw_zone_lan_postrouting

iptables -t nat -N pfw_zone_lan_prerouting 2> /dev/null
iptables -t nat -F pfw_zone_lan_prerouting

iptables -t nat -N pfw_zone_wan_prerouting 2> /dev/null
iptables -t nat -F pfw_zone_wan_prerouting


iptables -D FORWARD -j pfw_log
iptables -I FORWARD -j pfw_log

iptables -t nat -D zone_lan_postrouting -j pfw_zone_lan_postrouting
iptables -t nat -A zone_lan_postrouting -j pfw_zone_lan_postrouting

iptables -t nat -D zone_lan_prerouting -j pfw_zone_lan_prerouting
iptables -t nat -A zone_lan_prerouting -j pfw_zone_lan_prerouting

iptables -t nat -D zone_wan_prerouting -j pfw_zone_wan_prerouting
iptables -t nat -A zone_wan_prerouting -j pfw_zone_wan_prerouting

lanipaddr=$(uci get network.lan.ipaddr 2> /dev/null)
lannetmask=$(uci get network.lan.netmask 2> /dev/null)
wanip=$(ubus call network.interface.wan status | grep \"address\" | grep -oE '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}')

#获取lan子网掩码lanmasknum
a=$(echo "$lannetmask" | awk -F "." '{print $1" "$2" "$3" "$4}')
for num in $a;
do
	while [ $num != 0 ];do
		echo -n $(($num%2)) >> /tmp/num;
		num=$(($num/2));
	done
done
lanmasknum=$(grep -o "1" /tmp/num | wc -l)
rm -rf /tmp/num

#获取lan子网ip lanmaskip
declare -a tmplanip
b=$(echo "$lanipaddr" | awk -F "." '{print $1" "$2" "$3" "$4}')
ipnum=0
for var in $b;
do
	tmplanip[$ipnum]="$var"
	ipnum=$((ipnum+1))
done

listnum=${#tmplanip[@]}

if [ $listnum != '4' ];then
	echo "find tmplanip error"
	exit 1;
fi

if [ $lanmasknum == 24 ];then
	lanmaskip=${tmplanip[0]}.${tmplanip[1]}.${tmplanip[2]}.0
elif [ $masknum == 16 ];then
	lanmaskip=${tmplanip[0]}.${tmplanip[1]}.0.0
elif [ $lanmasknum == 8 ];then
	lanmaskip=${tmplanip[0]}.0.0.0
elif [ $lanmasknum == 32 ];then
	lanmaskip=${tmplanip[0]}.${tmplanip[1]}.${tmplanip[2]}.${tmplanip[3]}
fi

# the max number of portforward 64
for i in $(seq 0 63); do
    rule=$(uci get port_firewall.@forwarding[$i] 2> /dev/null)
    if [ "x$rule" = "x" ];then
         break;
    fi
	
    exter_port=$(uci get port_firewall.@forwarding[$i].exter_port 2> /dev/null)
    internal_port=$(uci get port_firewall.@forwarding[$i].internal_port 2> /dev/null)
    dest_ip=$(uci get port_firewall.@forwarding[$i].dest_ip 2> /dev/null)
    protocol=$(uci get port_firewall.@forwarding[$i].proto 2> /dev/null)
	name=$(uci get port_firewall.@forwarding[$i].name 2> /dev/null)
	
#分析port格式
	declare -a exter_port_array
	declare -a internal_port_array
	exter_port_num=0
	internal_port_num=0

	array_exter=`echo $exter_port | tr ',' " "`
	for exter_var in $array_exter;
	do
		exter_port_array[$exter_port_num]="$exter_var"
		exter_port_num=$((exter_port_num+1))
	done

	internal_exter=`echo $internal_port | tr ',' " "`

	for internal_var in $internal_exter;
	do
		internal_port_array[$internal_port_num]="$internal_var"
		internal_port_num=$((internal_port_num+1))
	done
	
	if [ $internal_port_num != $exter_port_num ];then
		echo "this portlist $exter_port $internal_port is error"
		continue;
	fi
    
    proto_tcp=""
    proto_udp=""
    if [ "$protocol" = "tcp" ];then
        proto_tcp="-p tcp"
    elif [ "$protocol" = "udp" ];then
        proto_udp="-p udp"
    else
        proto_tcp="-p tcp"
        proto_udp="-p udp"
    fi
	
    for proto in "$proto_tcp" "$proto_udp"
    do
        if [ "x$proto" = "x" ];then
            continue
        fi
		for j in $(seq 0 $((exter_port_num-1)));
		do
			#internal_port_array,exter_port_array格式一样,值判断一个
			result=$(echo ${exter_port_array[$j]} | grep "-")
			if [[ "$result" != "" ]];then			
				exter_start=`echo ${exter_port_array[$j]} |awk -F '-' '{print $1}'`
				exter_end=`echo ${exter_port_array[$j]} |awk -F '-' '{print $2}'`
				internal_start=`echo ${internal_port_array[$j]} |awk -F '-' '{print $1}'`
				internal_end=`echo ${internal_port_array[$j]} |awk -F '-' '{print $2}'`			

				if [ $exter_start -eq $exter_end ];then
					src_port=$exter_start
				elif [ $exter_start -gt $exter_end ];then
					src_port=$exter_end:$exter_start
				else
					src_port=$exter_start:$exter_end
				fi
				if [ $internal_start -eq $internal_end ];then
					dest_port=$internal_start
					new_dest_port=$dest_port
				elif [ $internal_start -gt $internal_end ];then
					dest_port=$internal_end:$internal_start
					new_dest_port=$internal_end-$internal_start
				else
					dest_port=$internal_start:$internal_end
					new_dest_port=$internal_start-$internal_end
				fi	
			else
				src_port=${exter_port_array[$j]}
				dest_port=${internal_port_array[$j]}
				new_dest_port=$dest_port
			fi
			iptables -t nat -A pfw_zone_lan_postrouting -s $lanmaskip/$lanmasknum -d $dest_ip $proto --dport $dest_port -m comment --comment "!fw3: $name" -j SNAT --to-source $lanipaddr
			iptables -t nat -A pfw_zone_lan_prerouting -s $lanmaskip/$lanmasknum -d $wanip $proto --dport $src_port -m comment --comment "!fw3: $name" -j DNAT --to-destination $dest_ip:$new_dest_port
			iptables -t nat -A pfw_zone_wan_prerouting $proto --dport $src_port -m comment --comment "!fw3: $name" -j DNAT --to-destination $dest_ip:$new_dest_port
			iptables -A pfw_log -i $wanifname $proto --dport $dest_port -d $dest_ip -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "portforward$(($i+1))"
		done
    done
	unset internal_port_array
	unset exter_port_array
done

dmz=$(uci get firewall.dmz 2> /dev/null)
if [ "x$dmz" != "x" ];then
	dest_ip=$(uci get firewall.dmz.dest_ip 2> /dev/null)
	iptables -t nat -A pfw_zone_lan_postrouting -s $lanmaskip/$lanmasknum -d ${dest_ip}/32 -p tcp -m comment --comment "!fw3: DMZ" -j SNAT --to-source $lanipaddr
	iptables -t nat -A pfw_zone_lan_postrouting -s $lanmaskip/$lanmasknum -d ${dest_ip}/32 -p udp -m comment --comment "!fw3: DMZ" -j SNAT --to-source $lanipaddr
	iptables -t nat -A pfw_zone_lan_prerouting -s $lanmaskip/$lanmasknum -d ${wanip}/32 -p tcp -m comment --comment "!fw3: DMZ" -j DNAT --to-destination $dest_ip
	iptables -t nat -A pfw_zone_lan_prerouting -s $lanmaskip/$lanmasknum -d ${wanip}/32 -p udp -m comment --comment "!fw3: DMZ" -j DNAT --to-destination $dest_ip
	iptables -t nat -A pfw_zone_wan_prerouting -p tcp -m comment --comment "!fw3: DMZ" -j DNAT --to-destination $dest_ip
	iptables -t nat -A pfw_zone_wan_prerouting -p udp -m udp ! --sport 67 -m comment --comment "!fw3: DMZ" -j DNAT --to-destination $dest_ip
	iptables -A pfw_log -i $wanifname -d $dest_ip -p tcp -m limit --limit 40/minute --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "portforward_dmz"
	iptables -A pfw_log -i $wanifname -d $dest_ip -p udp -m limit --limit 40/minute --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "portforward_dmz"
fi
