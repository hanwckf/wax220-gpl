--This file is created for check some deamons

    local mtkwifi = require("mtkwifi")
    local devs = mtkwifi.get_all_devs()
    local nixio = require("nixio")

function miniupnpd_chk(devname,vif,enable)
    local WAN_IF=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get network.wan.ifname"))

    os.execute("rm -rf /etc/miniupnpd.conf")

    if mtkwifi.exists("/tmp/run/miniupnpd."..vif) then
        os.execute("cat /tmp/run/miniupnpd."..vif.." | xargs kill -9")
    end

    if enable then
        local profile = mtkwifi.search_dev_and_profile()[devname]
        local cfgs = mtkwifi.load_profile(profile)
        local ssid_index = devs[devname]["vifs"][vif].vifidx
        local wsc_conf_mode = ""
        local PORT_NUM = 7777+(string.byte(vif, -1)+string.byte(vif, -2))
        local LAN_IPADDR = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get network.lan.ipaddr"))
        local LAN_MASK = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get network.lan.netmask"))
        local port = 6352 + (string.byte(vif, -1)+string.byte(vif, -2))
        LAN_IPADDR = LAN_IPADDR.."/"..LAN_MASK
        wsc_conf_mode = mtkwifi.token_get(cfgs["WscConfMode"], ssid_index, "")

        local file = io.open("/etc/miniupnpd.conf", "w")
        if nil == file then
            nixio.syslog("debug","open file /etc/miniupnpd.conf fail")
        end

        file:write("ext_ifname=",WAN_IF,'\n','\n',
                   "listening_ip=",LAN_IPADDR,'\n','\n',
                   "port=",port,'\n','\n',
                   "bitrate_up=800000000",'\n',
                   "bitrate_down=800000000",'\n','\n',
                   "secure_mode=no",'\n','\n',
                   "system_uptime=yes",'\n','\n',
                   "notify_interval=30",'\n','\n',
                   "uuid=68555350-3352-3883-2883-335030522880",'\n','\n',
                   "serial=12345678",'\n','\n',
                   "model_number=1",'\n','\n',
                   "enable_upnp=no",'\n','\n')
        file:close()

        if wsc_conf_mode ~= "" and wsc_conf_mode ~= "0" then
            os.execute("miniupnpd -m 1 -I "..vif.." -P /var/run/miniupnpd."..vif.." -G -i "..WAN_IF.." -a "..LAN_IPADDR.." -n "..PORT_NUM)
        end
    end
end

function d8021xd_chk(devname, prefix, vif, enable)
    if mtkwifi.exists("/tmp/run/8021xd_"..vif..".pid") then
        os.execute("cat /tmp/run/8021xd_"..vif..".pid | xargs kill -9")
        os.execute("rm /tmp/run/8021xd_"..vif..".pid")
    end

    if enable then
        local profile = mtkwifi.search_dev_and_profile()[devname]
        local cfgs = mtkwifi.load_profile(profile)
        local auth_mode = cfgs.AuthMode
        local ieee8021x = cfgs.IEEE8021X
        local pat_auth_mode = {"WPA$", "WPA;", "WPA2$", "WPA2;", "WPA1WPA2$", "WPA1WPA2;", "WPA3$", "WPA3;", "192$", "192;", "WPA2-Ent-OSEN$", "WPA2-Ent-OSEN;"}
        local pat_ieee8021x = {"1$", "1;"}
        local apd_en = false

        os.execute("echo [d8021xd_chk] enable is true >> /tmp/wifiLuaDebug.log")
		
        for _, pat in ipairs(pat_auth_mode) do
            if string.find(auth_mode, pat) then
                apd_en = true
            end
        end

        for _, pat in ipairs(pat_ieee8021x) do
            if string.find(ieee8021x, pat) then
                apd_en = true
            end
        end

        if apd_en then
            os.execute("8021xd -p "..prefix.. " -i "..vif)
        end
    end
end


function doBrctlAddIf(onlyDoBrctlAddIf)
    local ap2g5gradio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless1radio"))
    local ap2g5gradio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless2radio"))
    local ap2g5gradio3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless3radio"))
    local ap2g5gradio4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless4radio"))
    local ap2g5gradio5=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless5radio"))
    local ap2gradio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].radio"))
    local ap2gradio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].radio"))
    local ap2gradio3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].radio"))
    local ap2gradio4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].radio"))
    local ap2gradio5=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[4].radio"))
    local ap2gName1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].ifName"))
    local ap2gName2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].ifName"))
    local ap2gName3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].ifName"))
    local ap2gName4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].ifName"))
    local ap2gName5=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[4].ifName"))
    local ap5gradio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[5].radio"))
    local ap5gradio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[6].radio"))
    local ap5gradio3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[7].radio"))
    local ap5gradio4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[8].radio"))
    local ap5gradio5=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[9].radio"))
    local ap5gName1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[5].ifName"))
    local ap5gName2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[6].ifName"))
    local ap5gName3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[7].ifName"))
    local ap5gName4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[8].ifName"))
    local ap5gName5=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[9].ifName"))
    local guest_work1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].guest_network"))
    local guest_work2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].guest_network"))
    local guest_work3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].guest_network"))
    local guest_work4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].guest_network"))

    os.execute("ubus send wifi_radio_update '{\"ap2gradio1\":"..ap2gradio1..", \"ap2gradio2\":"..ap2gradio2..", \"ap2gradio3\":"..ap2gradio3..", \"ap2gradio4\":"..ap2gradio4..", \"ap2gradio5\":"..ap2gradio5..", \"ap5gradio1\":"..ap5gradio1..", \"ap5gradio2\":"..ap5gradio2..", \"ap5gradio3\":"..ap5gradio3..", \"ap5gradio4\":"..ap5gradio4..", \"ap5gradio5\":"..ap5gradio5.."}'")
    if ap2g5gradio1 ~= "OFF" then
        if ap2gradio1 == "0" then
            os.execute("ifconfig "..ap2gName1.." down 1>/dev/null 2>&1")
            os.execute("brctl delif br-lan "..ap2gName1.." 1>/dev/null 2>&1")
            os.execute("brctl delif br-guest "..ap2gName1.." 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap2gName1.." up 1>/dev/null 2>&1")
            if guest_work1 == "0" then
                os.execute("brctl addif br-lan "..ap2gName1.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap2gName1.." 1>/dev/null 2>&1")
            end
        end
        if ap5gradio1 == "0" then
            os.execute("ifconfig "..ap5gName1.." down 1>/dev/null 2>&1")
            os.execute("brctl delif br-lan "..ap5gName1.." 1>/dev/null 2>&1")
            os.execute("brctl delif br-guest "..ap5gName1.." 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap5gName1.." up 1>/dev/null 2>&1")
            if guest_work1 == "0" then
                os.execute("brctl addif br-lan "..ap5gName1.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap5gName1.." 1>/dev/null 2>&1")
            end
        end
    else
        os.execute("ifconfig "..ap2gName1.." down 1>/dev/null 2>&1")
        os.execute("ifconfig "..ap5gName1.." down 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap2gName1.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap5gName1.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap2gName1.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap5gName1.." 1>/dev/null 2>&1")
    end
    if ap2g5gradio2 ~= "OFF" then
        if ap2gradio2 == "0" then
            os.execute("ifconfig "..ap2gName2.." down 1>/dev/null 2>&1")
            os.execute("brctl delif br-lan "..ap2gName2.." 1>/dev/null 2>&1")
            os.execute("brctl delif br-guest "..ap2gName2.." 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap2gName2.." up 1>/dev/null 2>&1")
            if guest_work2 == "0" then
                    os.execute("brctl addif br-lan "..ap2gName2.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap2gName2.." 1>/dev/null 2>&1")
            end
        end
        if ap5gradio2 == "0" then
            os.execute("ifconfig "..ap5gName2.." down 1>/dev/null 2>&1")
            os.execute("brctl delif br-lan "..ap5gName2.." 1>/dev/null 2>&1")
            os.execute("brctl delif br-guest "..ap5gName2.." 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap5gName2.." up 1>/dev/null 2>&1")
            if guest_work2 == "0" then
                    os.execute("brctl addif br-lan "..ap5gName2.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap5gName2.." 1>/dev/null 2>&1")
            end
        end
    else
        os.execute("ifconfig "..ap2gName2.." down 1>/dev/null 2>&1")
        os.execute("ifconfig "..ap5gName2.." down 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap2gName2.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap5gName2.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap2gName2.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap5gName2.." 1>/dev/null 2>&1")
    end
    if ap2g5gradio3 ~= "OFF" then
        if ap2gradio3 == "0" then
            os.execute("ifconfig "..ap2gName3.." down 1>/dev/null 2>&1")
            os.execute("brctl delif br-lan "..ap5gName3.." 1>/dev/null 2>&1")
            os.execute("brctl delif br-guest "..ap5gName3.." 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap2gName3.." up 1>/dev/null 2>&1")
            if guest_work3 == "0" then
                os.execute("brctl addif br-lan "..ap2gName3.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap2gName3.." 1>/dev/null 2>&1")
            end
        end
        if ap5gradio3 == "0" then
            os.execute("ifconfig "..ap5gName3.." down 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap5gName3.." up 1>/dev/null 2>&1")
            if guest_work3 == "0" then
                os.execute("brctl addif br-lan "..ap5gName3.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap5gName3.." 1>/dev/null 2>&1")
            end
        end
    else
        os.execute("ifconfig "..ap2gName3.." down 1>/dev/null 2>&1")
        os.execute("ifconfig "..ap5gName3.." down 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap2gName3.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap5gName3.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap2gName3.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap5gName3.." 1>/dev/null 2>&1")
    end
    if ap2g5gradio4 ~= "OFF" then
        if ap2gradio4 == "0" then
            os.execute("ifconfig "..ap2gName4.." down 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap2gName4.." up 1>/dev/null 2>&1")
            if guest_work4 == "0" then
                os.execute("brctl addif br-lan "..ap2gName4.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap2gName4.." 1>/dev/null 2>&1")
            end
        end
        if ap5gradio4 == "0" then
            os.execute("ifconfig "..ap5gName4.." down 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap5gName4.." up 1>/dev/null 2>&1")
            if guest_work4 == "0" then
                os.execute("brctl addif br-lan "..ap5gName4.." 1>/dev/null 2>&1")
            else
                os.execute("brctl addif br-guest "..ap5gName4.." 1>/dev/null 2>&1")
            end
        end
    else
        os.execute("ifconfig "..ap2gName4.." down 1>/dev/null 2>&1")
        os.execute("ifconfig "..ap5gName4.." down 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap2gName4.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-lan "..ap5gName4.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap2gName4.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-guest "..ap5gName4.." 1>/dev/null 2>&1")
    end

    if ap2g5gradio5 ~= "OFF" then
        if ap2gradio5 == "0" then
            os.execute("ifconfig "..ap2gName5.." down 1>/dev/null 2>&1")
            os.execute("brctl delif br-mngt "..ap5gName5.." 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap2gName5.." up 1>/dev/null 2>&1")
            os.execute("brctl addif br-mngt "..ap5gName5.." 1>/dev/null 2>&1")
        end
        if ap5gradio5 == "0" then
            os.execute("ifconfig "..ap5gName5.." down 1>/dev/null 2>&1")
        else
            os.execute("ifconfig "..ap5gName5.." up 1>/dev/null 2>&1")
            os.execute("brctl addif br-mngt "..ap5gName5.." 1>/dev/null 2>&1")
        end
    else
        os.execute("ifconfig "..ap2gName5.." down 1>/dev/null 2>&1")
        os.execute("ifconfig "..ap5gName5.." down 1>/dev/null 2>&1")
        os.execute("brctl delif br-mngt "..ap2gName5.." 1>/dev/null 2>&1")
        os.execute("brctl delif br-mngt "..ap5gName5.." 1>/dev/null 2>&1")
    end
end


function connetRootAp(dev)
    local conf_mode=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get system.@system[0].netmode"))
    
    if conf_mode == "wds" then
        local isRootApExist_2g=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.apcli_2g.apcli_existOption")) 
        local isRootApExist_5g=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.apcli_5g.apcli_existOption"))
        local devname_2g=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.apcli_2g.device")) 
        local devname_5g=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.apcli_5g.device"))
        if devname_2g then devname_2g = devname_2g:gsub("%_", ".") end
        if devname_5g then devname_5g = devname_5g:gsub("%_", ".") end

        if isRootApExist_2g == '1' and dev == "2g" then
            for _,vif in ipairs(string.split(mtkwifi.read_pipe("ls /sys/class/net"), "\n"))
            do
                if string.match(vif, "apcli%d") then
                    mtkwifi.apcli_connect(devname_2g, vif);
                end
            end
        end

        if isRootApExist_5g == '1' and dev == "5g" then
            for _,vif in ipairs(string.split(mtkwifi.read_pipe("ls /sys/class/net"), "\n"))
            do
                if string.match(vif, "apclix%d") or string.match(vif, "apclii%d") then
                    mtkwifi.apcli_connect(devname_5g, vif);
                end
            end
        end

        for _,vif in ipairs(string.split(mtkwifi.read_pipe("ls /sys/class/net"), "\n")) do
            if isRootApExist_2g == '1' or isRootApExist_5g == '1' then
                if string.match(vif, "ra.") then
                    mtkwifi.set_netgear_vie(vif, 1)
                end
            elseif string.match(vif, "ra.") then
                mtkwifi.set_netgear_vie(vif, 0)
            end
        end
    end
end

function startAllApPin()
    local pinCode = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wpsPinCode"))
    local attackNum = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wpsPinAttackNum"))
    local wpsLock = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wpsLockdown"))
    local attackCheck = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wpsPinAttackCheck"))

    if attackCheck == '0' then
        attackNum = '0'
    end

    for _,vif in ipairs(string.split(mtkwifi.read_pipe("ls /sys/class/net"), "\n"))
    do
        if string.match(vif, "ra%a-%d+") then
            mtkwifi.__wps_ap_pin_start_all(vif, pinCode, wpsLock, attackNum)
        end
    end
end

function applyMacFilter()
    ifIdx = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"}
    local apName
    local filter
    local allow
    local deny

    for i, v in ipairs(ifIdx) do
        apName=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].ifName"))
        filter=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].mac_filter"))
        allow=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].mac_allow"))
        deny=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].mac_deny"))
        mtkwifi.__config_mac_filter(apName, filter, allow, deny)
    end
end

function guestNetActive(vif, allowed)
    os.execute("ebtables -D INPUT -p IPv4 -i "..vif.." --ip-proto 17 --ip-dport 67:68 -j ACCEPT 1>/dev/null 2>&1")
    os.execute("ebtables -D INPUT -p ARP -i "..vif.." -j ACCEPT 1>/dev/null 2>&1")
    os.execute("ebtables -D INPUT -i "..vif.." -j DROP 1>/dev/null 2>&1")

    if allowed == "0" then
        os.execute("ebtables -A INPUT -p IPv4 -i "..vif.." --ip-proto 17 --ip-dport 67:68 -j ACCEPT")
        os.execute("ebtables -A INPUT -p ARP -i "..vif.." -j ACCEPT")
        os.execute("ebtables -A INPUT -i "..vif.." -j DROP")
    end

    os.execute("ebtables -D FORWARD -p IPv4 -i "..vif.." --ip-proto 17 --ip-dport 53 -j ACCEPT 1>/dev/null 2>&1")
    os.execute("ebtables -D FORWARD -p IPv4 -i "..vif.." --ip-proto 17 --ip-dport 67:68 -j ACCEPT 1>/dev/null 2>&1")

    if allowed == "0" then
        os.execute("ebtables -A FORWARD -p IPv4 -i "..vif.." --ip-proto 17 --ip-dport 53 -j ACCEPT")
        os.execute("ebtables -A FORWARD -p IPv4 -i "..vif.." --ip-proto 17 --ip-dport 67:68 -j ACCEPT")
    end

    local fd = io.open("/tmp/br-lan-ipaddr"..vif, "r")
    if fd ~= nil then
        local oldIp = fd:read("*l")
        fd:close()
        if oldIp ~= nil then
            os.execute("ebtables -D FORWARD -p IPv4 -i "..vif.." --ip-dst "..oldIp.." -j DROP 1>/dev/null 2>&1")
        end
    end

    local cmdfd = io.popen("ifconfig br-lan | awk -F '[ :]+' '/inet addr/ {print $4}'")
    local curIp = cmdfd:read("*l")
    cmdfd:close()

    local cmdfd = io.popen("ifconfig br-lan | awk -F '[ :]+' '/inet addr/ {print $8}'")
    local curIpMask = cmdfd:read("*l")
    cmdfd:close()

    if allowed == "0"  and curIp ~= nil and curIpMask ~= nil then
        os.execute("ebtables -A FORWARD -p IPv4 -i "..vif.." --ip-dst "..curIp.."/"..curIpMask.." -j DROP")
    end

    if curIp ~= nil and  curIpMask ~= nil then
        local fd = io.open("/tmp/br-lan-ipaddr"..vif, "w")
        if nil ~= fd then
            fd:write(curIp.."/"..curIpMask)
            fd:close()
        end
    else
        os.remove("/tmp/br-lan-ipaddr"..vif)
    end
end

function guestNetwork()
    local if2g="ra1"
    local if2g1="ra2"
    local if5g="rai1"
    local if5g1="rai2"
    local guest2g = mtkwifi.__trim(mtkwifi.read_pipe("uci get wireless.@wifi-iface[1].allowLocalNetwork"))
    local guest5g = mtkwifi.__trim(mtkwifi.read_pipe("uci get wireless.@wifi-iface[4].allowLocalNetwork"))
    local guest2g1 = mtkwifi.__trim(mtkwifi.read_pipe("uci get wireless.@wifi-iface[2].allowLocalNetwork"))
    local guest5g1 = mtkwifi.__trim(mtkwifi.read_pipe("uci get wireless.@wifi-iface[5].allowLocalNetwork"))

    if mtkwifi.exists("/sys/class/net/"..if2g) then
        guestNetActive(if2g, guest2g)
    end

    if mtkwifi.exists("/sys/class/net/"..if2g1) then
        guestNetActive(if2g1, guest2g1)
    end

    if mtkwifi.exists("/sys/class/net/"..if5g) then
        guestNetActive(if5g, guest5g)
    end

    if mtkwifi.exists("/sys/class/net/"..if5g1) then
        guestNetActive(if5g1, guest5g1)
    end
end

function startFwdd()
    os.execute("/etc/init.d/fwdd stop")
    os.execute("/etc/init.d/fwdd start")
end

function ledAction()
    local ap2gRadio=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].radio"))
    local ap5gRadio=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].radio"))
    local wpsLock = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wpsLockdown"))
    local ap2gsecurity = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].security"))
    local ap5gsecurity = mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].security"))

    --os.execute("iwpriv ra0 e2p 3a=0d00") --config wifi driver LED_MODE:WPS_LED_MODE_13
    --os.execute("iwpriv rax0 e2p 3a=0d00") --config wifi driver LED_MODE:WPS_LED_MODE_13

    if ap2gRadio == '0' and ap5gRadio == '0' then
        os.execute(". /lib/functions/led_control.sh && platform_led_off green wps")
    --elseif wpsLock == '1' then
        --os.execute(". /lib/functions/led_control.sh && platform_led_set_timer green wps 200 200")
    else
        if ap2gRadio == '1' or ap5gRadio == '0' then
            if ap2gsecurity == "None" or ap2gsecurity == "OFF" then
                os.execute(". /lib/functions/led_control.sh && platform_led_off green wps")
            else
                os.execute(". /lib/functions/led_control.sh && platform_led_on green wps")
            end
        elseif ap2gRadio == '0' or ap5gRadio == '1' then
            if ap5gsecurity == "None" or ap5gsecurity == "OFF" then
                os.execute(". /lib/functions/led_control.sh && platform_led_off green wps")
            else
                os.execute(". /lib/functions/led_control.sh && platform_led_on green wps")
            end
        else
            if (ap2gsecurity == "None" or ap2gsecurity == "OFF") and (ap5gsecurity == "None" or ap5gsecurity == "OFF") then
                os.execute(". /lib/functions/led_control.sh && platform_led_off green wps")
            else
                os.execute(". /lib/functions/led_control.sh && platform_led_on green wps")
            end
        end
    end
end

function closeWifiForFactory()
    local factory_mode=mtkwifi.__trim(mtkwifi.read_pipe("envctl factory get factory_mode")) 
    local ap2gName=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].ifName")) 
    local ap5gName=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[5].ifName"))

    if factory_mode ~= "off" then
        os.execute("ifconfig "..ap2gName.." down 1>/dev/null 2>&1")
        os.execute("ifconfig "..ap5gName.." down 1>/dev/null 2>&1")
    end
end

function otpAction()
    local model=mtkwifi.__trim(mtkwifi.read_pipe("envctl factory get model"))
    local ap2gRadio0=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].radio"))
    local ap2gRadio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].radio"))
    local ap2gRadio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].radio"))
    local ap5gRadio0=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].radio"))
    local ap5gRadio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[4].radio"))
    local ap5gRadio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[5].radio"))

    if model == "WAX206" then
        --2.4G
        local radio2g="ra0"

        if ap2gRadio0 == '1' then
            radio2g="ra0"
        elseif ap2gRadio1 == '1' then
            radio2g="ra1"
        elseif ap2gRadio2 == '1' then
            radio2g="ra2"
        end

        if ap2gRadio0 == '1' or ap2gRadio1 == '1' or ap2gRadio2 == '1'then
            os.execute("iwpriv "..radio2g.." set tpc_duty=100:090:080:060")
            os.execute("iwpriv "..radio2g.." set tpc=1:1:1:122:116:125:0060:1")
        end

        --5G
        local radio5g="rai0"

        if ap5gRadio0 == '1' then
            radio5g="rai0"
        elseif ap5gRadio1 == '1' then
            radio5g="rai1"
        elseif ap5gRadio2 == '1' then
            radio5g="rai2"
        end

        if ap5gRadio0 == '1' or ap5gRadio1 == '1' or ap5gRadio2 == '1'then
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=0:0:100")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=0:1:90")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=0:2:80")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=0:3:60")
            os.execute("iwpriv "..radio5g.." set thermal_protect_disable=0:1:1")
            os.execute("iwpriv "..radio5g.." set thermal_protect_disable=0:2:1")
            os.execute("iwpriv "..radio5g.." set thermal_protect_enable=0:1:1:122:116:0060")
            os.execute("iwpriv "..radio5g.." set thermal_protect_enable=0:2:1:125:000:0060")
        end
    end

    if model == "WAX202" then
        --2.4G
        local radio2g="ra0"

        if ap2gRadio0 == '1' then
            radio2g="ra0"
        elseif ap2gRadio1 == '1' then
            radio2g="ra1"
        elseif ap2gRadio2 == '1' then
            radio2g="ra2"
        end

        if ap2gRadio0 == '1' or ap2gRadio1 == '1' or ap2gRadio2 == '1'then
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:0:100")
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:1:80")
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:2:70")
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:3:60")
            os.execute("iwpriv "..radio2g.." set thermal_protect_disable=0:1:1")
            os.execute("iwpriv "..radio2g.." set thermal_protect_disable=0:2:1")
            os.execute("iwpriv "..radio2g.." set thermal_protect_enable=0:1:1:122:116:0060")
            os.execute("iwpriv "..radio2g.." set thermal_protect_enable=0:2:1:125:000:0060")
        end

        --5G
        local radio5g="rax0"

        if ap5gRadio0 == '1' then
            radio5g="rax0"
        elseif ap5gRadio1 == '1' then
            radio5g="rax1"
        elseif ap5gRadio2 == '1' then
            radio5g="rax2"
        end

        if ap5gRadio0 == '1' or ap5gRadio1 == '1' or ap5gRadio2 == '1'then
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:0:100")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:1:80")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:2:70")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:3:60")
            os.execute("iwpriv "..radio5g.." set thermal_protect_disable=1:1:1")
            os.execute("iwpriv "..radio5g.." set thermal_protect_disable=1:2:1")
            os.execute("iwpriv "..radio5g.." set thermal_protect_enable=1:1:1:122:116:0060")
            os.execute("iwpriv "..radio5g.." set thermal_protect_enable=1:2:1:125:000:0060")
        end
    end

    if model == "WAX220" then
        local ap2g5gradio0=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless1radio"))
        local ap2g5gradio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless2radio"))
        local ap2g5gradio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless3radio"))
        local ap2g5gradio3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless4radio"))
        local ap2g5gradio4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.wireless5radio"))
        local ap2gRadio0=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].radio"))
        local ap2gRadio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].radio"))
        local ap2gRadio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].radio"))
        local ap2gRadio3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].radio"))
        local ap2gRadio4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[4].radio"))
        local ap5gRadio0=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[5].radio"))
        local ap5gRadio1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[6].radio"))
        local ap5gRadio2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[7].radio"))
        local ap5gRadio3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[8].radio"))
        local ap5gRadio4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[9].radio"))
        --2.4G
        local radio2g="ra0"
        local radio2g0='0'
        local radio2g1='0'
        local radio2g2='0'
        local radio2g3='0'
        local radio2g4='0'

        if ap2gRadio0 == '1' and ap2g5gradio0 ~= "OFF" then
            radio2g="ra0"
            radio2g0='1'
        elseif ap2gRadio1 == '1' and ap2g5gradio1 ~= "OFF" then
            radio2g="ra1"
            radio2g1='1'
        elseif ap2gRadio2 == '1' and ap2g5gradio2 ~= "OFF" then
            radio2g="ra2"
            radio2g2='1'
        elseif ap2gRadio3 == '1' and ap2g5gradio3 ~= "OFF" then
            radio2g="ra3"
            radio2g3='1'
        elseif ap2gRadio4== '1' and ap2g5gradio4 ~= "OFF" then
            radio2g="ra4"
            radio2g4='1'
        end

        if radio2g0 == '1' or radio2g1 == '1' or radio2g2 == '1' or radio2g3 == '1' or radio2g4 == '1' then
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:0:100")
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:1:80")
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:2:70")
            os.execute("iwpriv "..radio2g.." set thermal_protect_duty_cfg=0:3:60")
            os.execute("iwpriv "..radio2g.." set thermal_protect_disable=0:1:1")
            os.execute("iwpriv "..radio2g.." set thermal_protect_disable=0:2:1")
            os.execute("iwpriv "..radio2g.." set thermal_protect_enable=0:1:1:120:114:0060")
            os.execute("iwpriv "..radio2g.." set thermal_protect_enable=0:2:1:124:000:0060")
        end

        --5G
        local radio5g="rax0"
        local radio5g0='0'
        local radio5g1='0'
        local radio5g2='0'
        local radio5g3='0'
        local radio5g4='0'

        if ap5gRadio0 == '1' and ap2g5gradio10 ~= "OFF" then
            radio5g="rax0"
            radio5g0='1'
        elseif ap5gRadio1 == '1' and ap2g5gradio1 ~= "OFF" then
            radio5g="rax1"
            radio5g1='1'
        elseif ap5gRadio2 == '1' and ap2g5gradio2 ~= "OFF" then
            radio5g="rax2"
            radio5g2='1'
        elseif ap5gRadio3 == '1' and ap2g5gradio3 ~= "OFF" then
            radio5g="rax3"
            radio5g3='1'
        elseif ap5gRadio4 == '1' and ap2g5gradio4 ~= "OFF" then
            radio5g="rax4"
            radio5g4='1'
        end

        if radio5g0 == '1' or radio5g1 == '1' or radio5g2 == '1' or radio5g3 == '1' or radio5g4 == '1' then
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:0:100")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:1:80")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:2:70")
            os.execute("iwpriv "..radio5g.." set thermal_protect_duty_cfg=1:3:60")
            os.execute("iwpriv "..radio5g.." set thermal_protect_disable=1:1:1")
            os.execute("iwpriv "..radio5g.." set thermal_protect_disable=1:2:1")
            os.execute("iwpriv "..radio5g.." set thermal_protect_enable=1:1:1:120:114:0060")
            os.execute("iwpriv "..radio5g.." set thermal_protect_enable=1:2:1:124:000:0060")
        end
    end
end

function doSsidIsolate()
    local ap2gName1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].ifName"))
    local ap2gName2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].ifName"))
    local ap2gName3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].ifName"))
    local ap2gName4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].ifName"))
	
    local ap5gName1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[5].ifName"))
    local ap5gName2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[6].ifName"))
    local ap5gName3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[7].ifName"))
    local ap5gName4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[8].ifName"))

    local clientIsolation1=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[0].clientIsolation"))
    local clientIsolation2=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[1].clientIsolation"))
    local clientIsolation3=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[2].clientIsolation"))
    local clientIsolation4=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface[3].clientIsolation"))

	--local baseifName2G=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g.ifName"))
	--local baseifName5G=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.5g.ifName"))

	--os.execute("ebtables -X ssid_client_isolation 1>/dev/null 2>&1")
	--os.execute("ebtables -N ssid_client_isolation 1>/dev/null 2>&1")
	--os.execute("ebtables -D FORWARD -j ssid_client_isolation 1>/dev/null 2>&1")
	--os.execute("ebtables -A FORWARD -j ssid_client_isolation 1>/dev/null 2>&1")
	--os.execute("ebtables -F ssid_client_isolation 1>/dev/null 2>&1")

	os.execute("ebtables -D FORWARD -i "..ap2gName1.." -o "..ap5gName1.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap5gName1.." -o "..ap2gName1.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap2gName2.." -o "..ap5gName2.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap5gName2.." -o "..ap2gName2.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap2gName3.." -o "..ap5gName3.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap5gName3.." -o "..ap2gName3.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap2gName4.." -o "..ap5gName4.." -j DROP 1>/dev/null 2>&1")
	os.execute("ebtables -D FORWARD -i "..ap5gName4.." -o "..ap2gName4.." -j DROP 1>/dev/null 2>&1")
	
	if clientIsolation1 == '1' then
		os.execute("ebtables -A FORWARD -i "..ap2gName1.." -o "..ap5gName1.." -j DROP 1>/dev/null 2>&1")
		os.execute("ebtables -A FORWARD -i "..ap5gName1.." -o "..ap2gName1.." -j DROP 1>/dev/null 2>&1")
	end

	if clientIsolation2 == '1' then
		os.execute("ebtables -A FORWARD -i "..ap2gName2.." -o "..ap5gName2.." -j DROP 1>/dev/null 2>&1")
		os.execute("ebtables -A FORWARD -i "..ap5gName2.." -o "..ap2gName2.." -j DROP 1>/dev/null 2>&1")
	end

	if clientIsolation3 == '1' then
		os.execute("ebtables -A FORWARD -i "..ap2gName3.." -o "..ap5gName3.." -j DROP 1>/dev/null 2>&1")
		os.execute("ebtables -A FORWARD -i "..ap5gName3.." -o "..ap2gName3.." -j DROP 1>/dev/null 2>&1")
	end
	
	if clientIsolation4 == '1' then
		os.execute("ebtables -A FORWARD -i "..ap2gName4.." -o "..ap5gName4.." -j DROP 1>/dev/null 2>&1")
		os.execute("ebtables -A FORWARD -i "..ap5gName4.." -o "..ap2gName4.." -j DROP 1>/dev/null 2>&1")
	end
end


function doVlanCfg()
	ifIdx = {"0", "1", "2", "3", "5", "6", "7", "8"}
	local mgmtVlan=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.mgmtVlan"))
	local lastMgmtVlan=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.lastMgmtVlan"))
	local mgmtVlanEnable=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.2g_5g.mgmtVlanEnable"))
	local apName=ra0
	local vlanIso=0
	local vlanId=0
	
	for i, v in ipairs(ifIdx) do
		os.execute("echo [doVlanCfg] i="..i.."  v="..v.." >> /tmp/wifiLuaDebug.log")
		apName=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].ifName"))
		vlanIso=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].vlanIsolation"))
		vlanId=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].vlanId"))
		guestNetwork=mtkwifi.__trim(mtkwifi.read_pipe("uci -q get wireless.@wifi-iface["..v.."].guest_network"))
		
		if vlanIso == '1' then
			os.execute("iwpriv "..apName.." set VLANID="..vlanId.." 1>/dev/null 2>&1")
			os.execute("iwpriv "..apName.." set VLANPolicy=0:1  1>/dev/null 2>&1")
			os.execute("iwpriv "..apName.." set VLANPolicy=1:3  1>/dev/null 2>&1")
			os.execute("iwpriv "..apName.." set VLANTag=0  1>/dev/null 2>&1")
			os.execute("iwpriv "..apName.." set VLANTag=0  1>/dev/null 2>&1")
		else
			os.execute("iwpriv "..apName.." set VLANID=0 1>/dev/null 2>&1")
			os.execute("vconfig rem "..apName.."."..vlanId.." 1>/dev/null 2>&1")
			-- os.execute("iwpriv "..apName.." set VLANPolicy=1:0  1>/dev/null 2>&1")
			-- os.execute("iwpriv "..apName.." set VLANPolicy=0:0  1>/dev/null 2>&1")
		end	
		
	end
end

-- wifi service that require to start after wifi up
function wifi_service_misc()
    os.execute("echo [wifi_services] start wifi_service_misc >> /tmp/wifiLuaDebug.log")
    -- 0.brctl
    --doBrctlAddIf()

    -- 1.startFwdd
    startFwdd()

    -- 1.1 .doSsidIsolate
    doSsidIsolate()

    -- 2.apcli_connect
    --if mtkwifi.exists("/tmp/mtk/wifi/"..apclient2gName..".changed") or mtkwifi.exists("/tmp/mtk/wifi/normal_reload") then
    --    os.execute("rm /tmp/mtk/wifi/"..apclient2gName..".changed")
    --    connetRootAp("2g")
    --end
    --if mtkwifi.exists("/tmp/mtk/wifi/"..apclient5gName..".changed") or mtkwifi.exists("/tmp/mtk/wifi/normal_reload") then
    --    os.execute("rm /tmp/mtk/wifi/normal_reload")
    --    os.execute("rm /tmp/mtk/wifi/"..apclient5gName..".changed")
    --    connetRootAp("5g")
    --end

    -- 3.startAllApPin
    --startAllApPin()

    -- 4.applyMacFilter
    applyMacFilter()

    -- 5.guestnetwork
    --guestNetwork()

    -- 6.ledAction
    --ledAction()

    -- 7.close WIFI for factory model
    closeWifiForFactory()

    -- 8.config vlan
    --doVlanCfg()
    
    -- otp
    otpAction()
        
    local mapd_default = mtkwifi.load_profile("/etc/map/mapd_default.cfg")
    local mapd_user = mtkwifi.load_profile("/etc/map/mapd_user.cfg")
    local first_card_cfgs = mtkwifi.load_profile(mtkwifi.detect_first_card())
    if mapd_default.mode then
        local eth_mode = mapd_default.mode
        local device_role = mapd_default.DeviceRole
        if mapd_user.mode then
            eth_mode = mapd_user.mode
        end
        if mapd_user.DeviceRole then
            device_role = mapd_user.DeviceRole
        end
        -- 1.Wapp
        if mtkwifi.exists("/usr/bin/wapp_openwrt.sh") then
            os.execute("/etc/init.d/wapp start")
        end
        -- 2.EasyMesh
        if mtkwifi.exists("/usr/bin/EasyMesh_openwrt.sh") then
            if first_card_cfgs.MapMode == "1" then
                if (eth_mode == "0" and device_role == "1") or eth_mode == "1" then
                    os.execute("/etc/init.d/easymesh start")
                else
                    os.execute("/etc/init.d/easymesh_bridge start")
                end
            else
                os.execute("/etc/init.d/easymesh start")
            end
        end
    else		
        -- 1.Wapp
        if mtkwifi.exists("/usr/bin/wapp_openwrt.sh") then
            os.execute("/etc/init.d/wapp start")
        end
        -- 2.EasyMesh
        if mtkwifi.exists("/usr/bin/EasyMesh_openwrt.sh") then
            os.execute("/etc/init.d/easymesh start")
        end 
    end
end

if arg[1] == "guestNetwork" then
    guestNetwork()
end

-- wifi service that require to clean up before wifi down
function wifi_service_misc_clean()
    os.execute("rm -rf /tmp/wapp_ctrl")
    os.execute("killall -15 mapd")
    os.execute("killall -15 wapp")
    os.execute("killall -15 p1905_managerd")
    os.execute("killall -15 bs20")
end
