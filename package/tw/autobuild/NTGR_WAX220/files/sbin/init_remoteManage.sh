#!/bin/bash 

# shutdown remote manage
exit 0

http_rmenable=$(uci get system.remote.http_rmenable 2> /dev/null)
rm_access=$(uci get system.remote.rm_access 2> /dev/null)
ip_list=$(uci get system.remote.ip_list 2> /dev/null)
ip_start=$(uci get system.remote.ip_start 2> /dev/null)
ip_end=$(uci get system.remote.ip_end 2> /dev/null)
http_rmport=$(uci get system.remote.http_rmport 2> /dev/null)

recover_nginx() {
    local need_update

    if [ "x$http_rmport" != "x" -a "x$http_rmport" != "x443" ]; then
        need_update=$(cat /etc/nginx/https_server.conf | grep "\[::\]:${http_rmport} ssl")
        if [ "x$need_update" != "x" ]; then
            echo "server {" > /etc/nginx/https_server.conf
            echo "    listen       443 ssl;" >> /etc/nginx/https_server.conf
            echo "    listen       [::]:443 ssl;" >> /etc/nginx/https_server.conf
            echo "" >> /etc/nginx/https_server.conf
            echo "    ssl_certificate /tmp/cert.pem;" >> /etc/nginx/https_server.conf
            echo "    ssl_certificate_key /tmp/key.pem;" >> /etc/nginx/https_server.conf
            echo "    include /etc/nginx/service.conf;" >> /etc/nginx/https_server.conf
            echo "}" >> /etc/nginx/https_server.conf
            /etc/init.d/nginx restart
        fi
    fi
}

netmode=$(uci get system.@system[0].netmode 2> /dev/null)
netmode="${netmode:-"router"}"
if [ "$netmode" != "router" ]; then
    recover_nginx
    exit 0
fi

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

#iptables -N remote_manage 2> /dev/null
iptables -F remote_manage
#iptables -D INPUT -j remote_manage 2> /dev/null
#iptables -I INPUT -j remote_manage

if [ "x$http_rmenable" != "x1" ]; then
    recover_nginx
    exit 0
fi

[ "$rm_access" != "ip_single" ] && [ "$rm_access" != "ip_range" ] && [ "$rm_access" != "all" ] && exit 1

if [ "$rm_access" = "ip_single" ];then
    iptables -A remote_manage -i $wan_if -p tcp --dport $http_rmport -s $ip_list -j ACCEPT
elif [ "$rm_access" = "ip_range" ];then
    iptables -A remote_manage -i $wan_if -p tcp --dport $http_rmport -m iprange --src-range ${ip_start}-${ip_end} -j ACCEPT
else
    iptables -A remote_manage -i $wan_if -p tcp --dport $http_rmport -j ACCEPT
fi

# if the remote port is 443, don't need to setup nginx and care about the lan side
[ "x$http_rmport" = "x443" ] && exit 0
iptables -A remote_manage -i br-lan -p tcp --dport $http_rmport -j DROP

# if the remote port have already setuped in nginx, don't setup again.
nginx_updated=$(cat /etc/nginx/https_server.conf | grep "\[::\]:${http_rmport} ssl")
[ "x$nginx_updated" != "x" ] && exit 0

echo "server {" > /etc/nginx/https_server.conf
echo "    listen       443 ssl;" >> /etc/nginx/https_server.conf
echo "    listen       [::]:443 ssl;" >> /etc/nginx/https_server.conf
echo "    listen       $http_rmport ssl;" >> /etc/nginx/https_server.conf
echo "    listen       [::]:$http_rmport ssl;" >> /etc/nginx/https_server.conf
echo "" >> /etc/nginx/https_server.conf
echo "    ssl_certificate /tmp/cert.pem;" >> /etc/nginx/https_server.conf
echo "    ssl_certificate_key /tmp/key.pem;" >> /etc/nginx/https_server.conf
echo "    include /etc/nginx/service.conf;" >> /etc/nginx/https_server.conf
echo "}" >> /etc/nginx/https_server.conf
/etc/init.d/nginx restart

exit 0
