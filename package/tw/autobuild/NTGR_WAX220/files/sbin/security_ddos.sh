#!/bin/bash 

netmode=$(uci get system.@system[0].netmode 2> /dev/null)
[ "$netmode" != "router" ] && exit 1

wan_if=$(uci get network.wan.ifname)
proto=$(uci get network.wan.proto 2> /dev/null)
if [ "$proto" = "pppoe" ];then
    wan_if="pppoe-wan"
fi

proto=$(uci get network.vpn.proto 2> /dev/null)
if [ "$proto" = "l2tp" ];then
    wan_if="l2tp-vpn"
elif [ "$proto" = "pptp" ];then
    wan_if="pptp-vpn"
fi
[ "x$wan_if" = "x" ] && exit 1


add_ddos_chain() {
	iptables -t filter -F syn_flood
	iptables -t filter -D FORWARD -i $wan_if -j syn_flood
	iptables -t filter -I FORWARD -i $wan_if -j syn_flood
	
	#DOS_ATTACK:SYN/RST Scan
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags SYN,RST SYN,RST -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags SYN,RST SYN,RST -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: SYN/RST Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags SYN,RST SYN,RST -j DROP
	#DOS_ATTACK:RST Scan 
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags RST RST -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags RST RST -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: RST Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags RST RST -j DROP

	#DOS_ATTACK:ACK Scan
	#iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ACK ACK -m limit --limit 200/sec --limit-burst 25 -j RETURN
	#iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ACK ACK -m limit --limit 2/sec -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: ACK Scan"
	#iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ACK ACK -j DROP
	#DOS_ATTACK:IMAP Scan
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags SYN,FIN SYN,FIN -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags SYN,FIN SYN,FIN -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: IMAP Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags SYN,FIN SYN,FIN -j DROP
	#DOS_ATTACK:NULL Scan
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL NONE -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL NONE -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: NULL Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL NONE -j DROP
	#DOS_ATTACK:FIN Scan 
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL FIN -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL FIN -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: FIN Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL FIN -j DROP
	#DOS_ATTACK:Xmas Tress Scan 1 
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL FIN,URG,PSH -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL FIN,URG,PSH -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: Xmas Tress Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL FIN,URG,PSH -j DROP
	#DOS_ATTACK:Xmas Tress Scan 2
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL ALL -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL ALL -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: Xmas Tress Scan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL ALL -j DROP
	#DOS_ATTACK:nmap-push
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -m limit --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: nmap-push"
	iptables -t filter -A syn_flood -i $wan_if -p tcp -m tcp --tcp-flags ALL SYN,RST,ACK,FIN,URG -j DROP
	#DOS_ATTACK:TCP SYN Flood 
	iptables -t filter -A syn_flood -i $wan_if -p tcp --syn -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp --syn -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: TCP SYN Flood"
	iptables -t filter -A syn_flood -i $wan_if -p tcp --syn -j DROP
	#DOS_ATTACK:UDP Flood
	iptables -t filter -A syn_flood -i $wan_if -p udp -m limit --limit 1500/sec --limit-burst 1500 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p udp -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: UDP Flood"
	iptables -t filter -A syn_flood -i $wan_if -p udp -j DROP
	#DOS_ATTACK:DoSPortScan
	iptables -t filter -A syn_flood -i $wan_if -p tcp --tcp-flags SYN,ACK,FIN,RST RST -m limit --limit 64/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p tcp --tcp-flags SYN,ACK,FIN,RST RST -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: DoSPortScan"
	iptables -t filter -A syn_flood -i $wan_if -p tcp --tcp-flags SYN,ACK,FIN,RST RST -j DROP
	#DOS_ATTACK:ICMP-unreachable flood #ok
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type destination-unreachable -m limit --limit 128/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type destination-unreachable -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: ICMP-unreachable flood"
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type destination-unreachable -j DROP
	#DOS_ATTACK:ICMP-time-exceeded flood
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type time-exceeded -m limit --limit 128/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type time-exceeded -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: ICMP-time-exceeded flood"
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type time-exceeded -j DROP
	#DOS_ATTACK:ICMP-param-problem flood
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type parameter-problem -m limit --limit 128/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type parameter-problem -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: ICMP-param-problem flood"
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type parameter-problem -j DROP
	#DOS_ATTACK:ICMP-reply(pong) flood:
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type echo-reply  -m limit --limit 128/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type echo-reply  -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: ICMP-reply(pong) flood"
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type echo-reply  -j DROP
	#DOS_ATTACK:ICMP-source-quench flood
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type source-quench -m limit --limit 128/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type source-quench -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: ICMP-source-quench flood"
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type source-quench -j DROP
	#DOS_ATTACK:Ping of Death/Ping Flood
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type echo-request -m limit --limit 128/sec --limit-burst 64 -j RETURN
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type echo-request -m limit --limit 1/sec --limit-burst 1 -j NFLOG --nflog-group 2 --nflog-prefix "DoS attack: Ping Flood"
	iptables -t filter -A syn_flood -i $wan_if -p icmp --icmp-type echo-request -j DROP
}

enable=$(uci get firewall.@defaults[0].syn_flood 2> /dev/null)

[ "x$enable" = "x" ] && exit 1

add_ddos_chain

