var SUPPORT_DUAL_LAN_PORT="";
var SUPPORT_DEMO_APPLY="";
var SUPPORT_WIFIJET="";
var HIDE_LAN_PORT="";
var SUPPORT_WLAN24G="1";
var SUPPORT_WLAN5G="1";
var SUPPORT_WLAN5G_2="";
var SUPPORT_SAVE_MEMORY="";
var SUPPORT_COMBINED_SSID_SETTING="1";

var firmwareVersion = '<%=firmwareVersion or "?"%>';
var wan_stp = '<%=laninfo["stp"] or "0"%>';
var _status = {"0":"<%:Disable%>", "1":"<%:Enable%>"};
var _short_timeout = {"1":"<%:Short%>", "0":"<%:Long%>"};
var wan6_linklocal = "<%=laninfo['ip6LinkLocalEn']%>";
var preChannels = [];
var opmodeArr = [];
var firstInterval;
var secondInterval;
var thirdInterval;

$$(document).ready(function()
{
    var htmlStr = "";
    var devicename = '<% cfg_get("wl_deviceName") %>';
    var firmwareversion = '<% cat_file("/firmware_version") %>';
    var gateway = '<% cfg_get("lan_gateway") %>';
    var dnsStr = '<% cfg_get("dns") %>';
    var dns = '';
    var proto = '<% cfg_get("lan_dhcp") %>';
    var wl_country = '<% cfg_get("wl_country") %>';
    var wl_mgmtVlan = '<% cfg_get("wl_mgmtVlan") %>';
    var wl_mgmtVlanEnable = '<% cfg_get("wl_mgmtVlanEnable") %>';

    if (SUPPORT_WIFIJET)
    {
        htmlStr = '<td width="40%" myid="title_Device_Name_text">$airbridge_name</td><td myid="Device_Name_text"></td>';
    }
    else
    {
        htmlStr = '<td width="40%" myid="title_Device_Name_text">$ap_name_js</td><td myid="Device_Name_text">'+ devicename +'</td>';
    }

    $$("#title_Device_Name_text").append(htmlStr);

    getById('ws_country').innerHTML = showCountry(wl_country);

    htmlStr = '<td width="40%" myid="title_fw_ver_text">$firmware_version</td><td myid="fw_ver_text">'+ firmwareversion +'</td>';
    $$("#title_fw_ver_text").append(htmlStr);

    if ("" != wl_mgmtVlan && "1" == wl_mgmtVlanEnable)
    {
        getById('mg_vlan_id').innerHTML = wl_mgmtVlan;
    }

    if (gateway == "")
    {
        gateway = "N/A";
    }
    getById('ipv4_gwaddr').innerHTML = gateway;

    if (dnsStr == " " || dnsStr == "")
    {
        getById('ipv4_dns').innerHTML = "$undefined";
    }
    else
    {
        dns = dnsStr.split(" ");
        getById('ipv4_dns').innerHTML = dns[0];
    }

    if (dnsStr == " " || dnsStr == "" || dns[1] == "")
    {
        getById('ipv4_dns2').innerHTML = "$undefined";
    }
    else
    {
        getById('ipv4_dns2').innerHTML = dns[1];
    }

    getById('ipv4_proto').innerHTML = (proto == "dhcp") ? "$enable" : "$disable";

    if (HIDE_LAN_PORT)
    {
        $$("#tr-lan1").hide();
        $$("#tr-lan2").hide();
        $$("#tr-lan").hide();
    }
    else
    {
        if (SUPPORT_DUAL_LAN_PORT)
        {
            $$("#tr-lan1").show();
            $$("#tr-lan2").show();
            $$("#tr-lan").hide();
        }
        else
        {
            $$("#tr-lan1").hide();
            $$("#tr-lan2").hide();
            $$("#tr-lan").show();
        }

        if (SUPPORT_DEMO_APPLY)
        {
            $$("#td-demo-mac").show();
            $$("#td-brlan-mac").hide();
        }
        else
        {
            $$("#td-demo-mac").hide();
            $$("#td-brlan-mac").show();
        }
    }

    if (SUPPORT_WLAN24G)
    {
        $$("#tr-wifi24-enable").show();
        if (SUPPORT_DEMO_APPLY)
        {
            $$("#td-demo-bssid1").show();
            $$("#td-wifi0-bssid1").hide();
        }
        else
        {
            $$("#td-demo-bssid1").hide();
            $$("#td-wifi0-bssid1").show();
        }
    }
    else
    {
        $$("#tr-wifi24-enable").hide();
    }

    if (SUPPORT_WLAN5G)
    {
        if (SUPPORT_DEMO_APPLY)
        {
            $$("#td-demo-5g-bssid1").show();
            $$("#td-wifi1-5g-bssid1").hide();
        }
        else
        {
            $$("#td-wifi1-5g-bssid1").show();
            $$("#td-demo-5g-bssid1").hide();
        }

        if (SUPPORT_WLAN5G_2)
        {
            $$("#tr-wifi5_2-enable").show();
        }
        else
        {
            $$("#tr-wifi5_2-enable").hide();
        }
    }
    else
    {
        $$("#tr-wifi5-enable").hide();
        $$("#tr-wifi5_2-enable").hide();
    }

    if (SUPPORT_WLAN24G)
    {
        $$("#wifi24-country").show();
        $$("#wifi5-country").hide();
    }
    else
    {
        $$("#wifi24-country").hide();
        $$("#wifi5-country").show();
    }

    $$("#span-tree-protocol-stp").hide();
    $$("#span-tree-protocol-lacp").hide();

}
);


function changeBytes(limit)
{
    var size = "";

    if (limit < 0.1 * 1024){
        size = limit.toFixed(2)
    }else if (limit < 0.1 * 1024 * 1024){
        size = (limit/1024).toFixed(2) + "K"
    }else if (limit < 0.1 * 1024 * 1024 * 1024){
        size = (limit/(1024 * 1024)).toFixed(2) + "M"
    }else {
        size = (limit/(1024 * 1024 * 1024)).toFixed(2) + "G"
    }

    var sizeStr = size + "";
    var index = sizeStr.indexOf(".");
    var dou = sizeStr.substr(index + 1 ,2)
    if (dou == "00"){
        return sizeStr.substring(0, index) + sizeStr.substr(index + 3, 2)
    }
    return size;
}


function progressbar(v, m)
{
    var v1 = v;
    var m1 = m;
    var vn = parseInt(v1) || 0;
    var mn = parseInt(m1) || 100;
    var pc = Math.floor((100 / mn) * vn);
    var htmlStr;

    htmlStr = '<div style="width:200px; position:relative; border:1px solid #999999">' +
            '<div style="background-color:#CCCCCC; width:'+ pc +'%; height:15px">' +
                '<div style="position:absolute;left: 50%;top: 50%; text-align:center; width:100%; color:#000000;height: 100%;transform: translate(-50%, -50%);">' +
                    '<small style="font-size: 13px; line-height: 100%;">'+ v + ' / ' + m + '('+ pc +'%)</small>' +
                '</div>' +
            '</div>' +
        '</div>';

    return htmlStr;
}


function renew_ifaces_status(){
    var data = {anticsrf: '<% generateToken("wifi_status") %>', submitType:"wifi_status", wifi:1};
    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "device_status.htm") %>',
        data:data,
        dataType:"json",
        error:function(){
            //console.log("wifi_Channel error");
        },
        success:function(result){
            var ws = document.getElementById('wifi_status_table');
            if (ws && result)
            {
                var myidTable = {0:"24",1:"5",2:"5_1"};
                var wsbody = ws.rows.length > 0 ?ws.rows[0].parentNode:ws;

                while (ws.rows.length > 0)
                    wsbody.deleteRow(0);

                var tr, td, s='', dev, t_idx=0, i, net, show_profile;
                for (var didx = 0; didx < result.length; didx++)
                {
                    dev = result[didx];
                    tr = wsbody.insertRow(-1);

                    s = (didx == 0)?"2.4":"5";
                    bandSelect = (didx == 0)?"2.4":"5";
                    td = tr.insertCell(-1);
                    td.colSpan="2";
                    td.className="title";

                    td.innerHTML = "$wlan_information"+ " - "+s+"GHz";

                    var showBW = 0;

                    tr = wsbody.insertRow(-1);
                    tr.className = "title-option";
                    td = tr.insertCell(-1);
                    td.width     = "40%";
                    td.setAttribute("myid", "title_wifi"+myidTable[didx]+"_band_text");
                    td.innerHTML = "$wireless_mode";
                    td = tr.insertCell(-1);
                    td.setAttribute("myid", "wifi"+myidTable[didx]+"_band_text");

                    td.innerHTML = showWMode(dev.hwmode);
                    if (!(dev.hwmode  == "11bg" || dev.hwmode == "11b" || dev.hwmode == "11g" || dev.hwmode == "11a"))
                    {
                        showBW = 1;
                    }

                    if (showBW)
                    {
                        tr = wsbody.insertRow(-1);
                        tr.className = "title-option";
                        td = tr.insertCell(-1);
                        td.width = "40%";
                        td.innerHTML = "$channel_bandwidth";
                        td.setAttribute("myid", "title_wifi"+myidTable[didx]+"_htmode_text");
                        td = tr.insertCell(-1);
                        td.setAttribute("myid", "wifi"+myidTable[didx]+"_htmode_text");
                        td.innerHTML = showBandwidth(dev.htmode);
                    }

                    tr = wsbody.insertRow(-1);
                    tr.className = "title-option";
                    td = tr.insertCell(-1);
                    td.width     = "40%";
                    td.setAttribute("myid", "title_wifi"+myidTable[didx]+"_channel_text");
                    td.innerHTML = "$channel";
                    td = tr.insertCell(-1);
                    td.setAttribute("myid", "wifi"+myidTable[didx]+"_channel_text");
                    dev.channel = dev.channel.split("/")[0];
                    var frequency = showFrequency(dev.channel);
                    if (frequency != "undefined GHz")
                        td.innerHTML = showFrequency(dev.channel)+" ($channel "+dev.channel+")";
                    else if (dev.channel == "0")
                        td.innerHTML = "NA";
                    else
                        td.innerHTML = "$channel "+dev.channel;
                }
            }
        }
    });
}


function check_channel()
{
    data1 = {anticsrf: '<% generateToken("wifi_channel") %>', submitType:"wifi_channel", wifi:1};

    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "device_status.htm") %>',
        data:data1,
        dataType:"json",
        error:function(){
            //console.log("wifi_Channel error");
        },
        success:function(result){
            if ( preChannels.length == 0 && result)
                preChannels = result;
            else
            {
                for ( i = 0 ; i < preChannels.length ; i++ )
                {
                    if ( preChannels[i].channel != result[i].channel )
                    {
                        renew_ifaces_status();
                        break;
                    }
                }
            }
        }
    });

    if (thirdInterval)
        clearInterval(thirdInterval);

    thirdInterval = setInterval("check_channel()", 10000);
}

$$( document ).ready(function() {
    setTimeout("renew_ifaces_status()", 2000);
});


function get_hardware_version(){
    var e = document.getElementById('device_version');
    var model_name = '<%=uci:get('sysProductInfo','model','modelName')%>'.slice(-2);
    if (model_name.slice(0, 1)=="v" && isNaN(model_name.slice(-1))==false) 
    {
        e.innerHTML = model_name.slice(-1)+'.0';
    }
    else
    {
        e.innerHTML = "1.0";
    }
}


function refresh_statistics(){
    getById('loading').style.display = "";
    window.setTimeout("renew_statistics_func_SSID_based()", 3000);
}

function renew_statistics_func_SSID_based(){
    getById('loading').style.display = "";
    data1 = {anticsrf: '<% generateToken("wifi_statistics") %>', submitType:"wifi_statistics", wifi:1};

    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "device_status.htm") %>',
        data:data1,
        dataType:"json",
        error:function(){
            //console.log("wifi_Channel error");
        },
        success:function(result){
            if (result)
            {
                var ap_str="";
                var wds_ap_str="";

                var combined_ssid_ap=[];
                var combined_ssid_wds_ap=[];
                var pattern_ap;
                pattern_ap = 0;

                var classification_ap=[];

                for (var i=0;i<8;i++){
                    classification_ap[i]=0;
                }

                var classification_wds_ap=[];
                for (var i=0;i<5;i++){
                    classification_wds_ap[i]=0;
                }
                var myid_ap_num=1;
                var myid_wds_ap_num=1;

                for (var i = 0; i < result.length; i++){
                    for (var j = 0; j < result.length; j++){
                        if (result[i]["ifname"] == result[j]["ifname"] && i < j)
                        {
                            result[i]["rx_bytes"] = parseInt(result[i]["rx_bytes"]) + parseInt(result[j]["rx_bytes"]);
                            result[i]["tx_bytes"] = parseInt(result[i]["tx_bytes"]) + parseInt(result[j]["tx_bytes"]);
                            result[i]["rx_packets"] = parseInt(result[i]["rx_packets"]) + parseInt(result[j]["rx_packets"]);
                            result[i]["tx_packets"] = parseInt(result[i]["tx_packets"]) + parseInt(result[j]["tx_packets"]);
                            result.splice(j, 1);
                        }
                    }
                }

                for (var idx = 0; idx < result.length; idx++)
                {
                    var ifc = result[idx];
                    var vlanId = "1" == ifc["vlanIsolation"] ? ifc["vlanId"] : "-";
                    var currMode = "ap";
                    switch (currMode) {
                        case "ap":
                            classification_ap[pattern_ap]+=1;
                            if (classification_ap[pattern_ap]>=2){
                                combined_ssid_ap[ifc["ifname"]]=pattern_ap+","+ifc["rx_bytes"]+","+ifc["rx_packets"]+","+ifc["tx_bytes"]+","+ifc["tx_packets"];
                            }
                            else{
                                ap_str += '<tr><td id="ap_profile"></td><td style="display:none;" id="statistic_ap_'+pattern_ap+'">'+htmlEncode(ifc["ifname"])+'</td><td class="tbl-value one-long-line"><span myid="wifi_ssid'+myid_ap_num+'_text">'+htmlEncode(ifc["ifname"])+'</span></td><td class="tbl-value" myid="wifi_securitymode'+myid_ap_num+'_text">'+showEncryption(ifc["encr"])+'</td><td class="tbl-value" myid="wifi_vlan_id'+myid_ap_num+'_text">'+vlanId+'</td><td class="tbl-value" myid="wifi_8021q'+myid_ap_num+'_text">'+((ifc["vlanIsolation"]=="1")?"$enable":"$disable")+'</td><td id="rx" class="tbl-value" >'+ifc["rx_bytes"]+','+ifc["rx_packets"]+'</td><td id="tx" class="tbl-value" >'+ifc["tx_bytes"]+','+ifc["tx_packets"]+'</td></tr>';
                                myid_ap_num++;
                                pattern_ap++;
                            }
                            break;
                        case "wds_ap":
                            if (ifc["ifname"].slice(-1)!="4"){
                                var pattern_wds_ap;
                                pattern_wds_ap = ifc["ifname"].slice(-1); //get last char
                                classification_wds_ap[pattern_wds_ap]+=1;
                                if (classification_wds_ap[pattern_wds_ap]>=2){
                                    combined_ssid_wds_ap[ifc["ifname"]]=pattern_wds_ap+","+ifc["rx_bytes"]+","+ifc["rx_packets"]+","+ifc["tx_bytes"]+","+ifc["tx_packets"];
                                }else{
                                    wds_ap_str += '<tr><td id="wds_ap_profile"></td><td style="display:none;" id="statistic_wds_ap_'+pattern_wds_ap+'">'+htmlEncode(ifc["ifname"])+'</td><td class="tbl-value one-long-line"><span myid="wifi_ssid'+myid_wds_ap_num+'_text">'+SpecHTML(ifc["name"])+'</span></td><td class="tbl-value" myid="wifi_securitymode'+myid_wds_ap_num+'_text">'+showEncryption(ifc["encr"])+'</td><td class="tbl-value"  myid="wifi_vlan_id'+myid_wds_ap_num+'_text">'+((ifc["isolation"]=="1")?ifc["vlanid"]:"-")+'</td><td class="tbl-value" myid="wifi_8021q'+myid_wds_ap_num+'_text">'+((ifc["isolation"]=="1")?"<%:Enable%>":"<%:Disable%>")+'</td><td id="rx" class="tbl-value" >'+ifc["rx_bytes"]+','+ifc["rx_packets"]+'</td><td id="tx" class="tbl-value" >'+ifc["tx_bytes"]+','+ifc["tx_packets"]+'</td></tr>';
                                        myid_wds_ap_num++;
                                }
                            }
                            break;
                        case "sta_ap":
                            if (ifc["ifname"].slice(-1)=="8"){
                                var pattern_ap=10;
                                ap_str += '<tr><td id="ap_profile"></td><td style="display:none;" id="statistic_ap_'+pattern_ap+'">'+htmlEncode(ifc["ifname"])+'</td><td class="tbl-value one-long-line"><span myid="wifi_ssid'+myid_ap_num+'_text">'+ifc["name"]+'</span></td><td class="tbl-value" myid="wifi_securitymode'+myid_ap_num+'_text">'+showEncryption(ifc["encr"])+'</td><td class="tbl-value" myid="wifi_vlan_id'+myid_ap_num+'_text">'+((ifc["isolation"]=="1" && ifc["guest_network"]=="Disable")?ifc["vlanid"]:"-")+'</td><td class="tbl-value" myid="wifi_8021q'+myid_ap_num+'_text">'+((ifc["isolation"]=="1")?"<%:Enable%>":"<%:Disable%>")+'</td><td id="rx" class="tbl-value" >'+ifc["rx_bytes"]+','+ifc["rx_packets"]+'</td><td id="tx" class="tbl-value" >'+ifc["tx_bytes"]+','+ifc["tx_packets"]+'</td></tr>';
                                myid_ap_num++;
                            }
                            break;
                    }
                }
                if (ap_str!=""){
                        var title_ssid_radio_str = "$statistics"
                        title_ssid_radio_str += " - Access Point ";
                            title_ssid_radio_str+= "2.4GHz"
                            if (title_ssid_radio_str!=("$statistics" + " - Access Point ")){
                                title_ssid_radio_str+= "/5GHz";
                            }else{
                                title_ssid_radio_str+= "5GHz";
                            }
                        ap_str='<tr><td colspan="7" class="title">'+title_ssid_radio_str+'</td></tr><tr style="background-color: #EEEEEE;" class="title-option"><td class="tbl-grey" myid="title_wifi_Profile_text" style="width:5%;">Profile</td><td class="tbl-grey" myid="title_wifi_ssid_text" style="width:30%;">SSID</td><td class="tbl-grey" myid="title_wifi_securitymode_text" style="width:15%;">Security</td><td class="tbl-grey" myid="title_wifi_vlan_id_text" style="width:10%;">VID</td><td class="tbl-grey" myid="title_wifi_8021q_text" style="width:10%;">802.1Q</td><td class="tbl-grey" style="width:15%;">Rx($bytes)</td><td class="tbl-grey" style="width:15%;">Tx($bytes)</td></tr>'+ap_str;
                            $$('#wifi_status_table_ap').html(ap_str);
                }else{
                    $$('#wifi_status_table_ap').css( "display", "none" );
                }

                if (wds_ap_str!=""){
                        var title_ssid_radio_str = "<%:Statistics%>"
                        title_ssid_radio_str += " - AirBridge Master ";
                        if (opmodeArr[0]=="wds_ap"){title_ssid_radio_str+= "2.4GHz"}
                        if (opmodeArr[1]=="wds_ap"){
                            if (title_ssid_radio_str!=("<%:Statistics%>" + " - WDS Access Point ")){
                                title_ssid_radio_str+= "/5GHz";
                            }else{
                                title_ssid_radio_str+= "5GHz";
                            }
                        }
                        if (opmodeArr[2]=="wds_ap"){
                            if (title_ssid_radio_str!=("<%:Statistics%>" + " - WDS Access Point ")){
                                title_ssid_radio_str+= "/5GHz - 2";
                            }else{
                                title_ssid_radio_str+= "5GHz - 2";
                            }
                        }
                        wds_ap_str='<tr><td colspan="7" class="title">'+title_ssid_radio_str+'</td></tr><tr style="background-color: #EEEEEE;" class="title-option"><td class="tbl-grey" myid="title_wifi_Profile_text" style="width:5%;">Profile</td><td class="tbl-grey" myid="title_wifi_ssid_text" style="width:20%;">SSID</td><td class="tbl-grey" myid="title_wifi_securitymode_text" style="width:15%;">Security</td><td class="tbl-grey" myid="title_wifi_vlan_id_text" style="width:5%;">VID</td><td class="tbl-grey" myid="title_wifi_8021q_text" style="width:5%;">802.1Q</td><td class="tbl-grey" style="width:20%;">Rx($bytes)</td><td class="tbl-grey" style="width:20%;">Tx($bytes)</td></tr>'+wds_ap_str;
                            $$('#wifi_status_table_wds_ap').html(wds_ap_str);
                }else{
                    $$('#wifi_status_table_wds_ap').css( "display", "none" );
                }

                //deal with ap table, add up rx, tx info
                for (var i in combined_ssid_ap){ 
                    var curPattern = combined_ssid_ap[i].slice(0,1);
                    $$('[id=statistic_ap_'+curPattern+']').each(function(){
                        var rxInfo = $$(this).siblings().filter(function(){ return this.id.match(/rx/) }).text().split(",");
                        var txInfo = $$(this).siblings().filter(function(){ return this.id.match(/tx/) }).text().split(",");

                        var addUpRxBytes = parseInt(rxInfo[0],10);
                        var addUpRxPackets = parseInt(rxInfo[1],10);
                        addUpRxBytes += parseInt(currIfaceInfo[1],10);
                        addUpRxPackets += parseInt(currIfaceInfo[2],10);

                        var addUpTxBytes = parseInt(txInfo[0],10);
                        var addUpTxPackets = parseInt(txInfo[1],10);
                        addUpTxBytes += parseInt(currIfaceInfo[3],10);
                        addUpTxPackets += parseInt(currIfaceInfo[4],10);

                        $$(this).siblings().filter(function(){ return this.id.match(/rx/) }).text(addUpRxBytes+","+addUpRxPackets);
                        $$(this).siblings().filter(function(){ return this.id.match(/tx/) }).text(addUpTxBytes+","+addUpTxPackets);
                    });
                } //deal with ap table end

                //deal with wds-ap table, add up rx, tx info
                for (var i in combined_ssid_wds_ap)
                {
                    var curPattern = combined_ssid_wds_ap[i].slice(0,1);
                    $$('[id=statistic_wds_ap_'+curPattern+']').each(function(){
                        var rxInfo = $$(this).siblings().filter(function(){ return this.id.match(/rx/) }).text().split(",");
                        //console.log("rxInfo "+rxInfo[0]+"  "+rxInfo[1]); //0:bytes, 1:packets

                        var txInfo = $$(this).siblings().filter(function(){ return this.id.match(/tx/) }).text().split(",");
                        //console.log("txInfo "+txInfo[0]+"  "+txInfo[1]); //0:bytes, 1:packets

                        var addUpRxBytes = parseInt(rxInfo[0],10);
                        var addUpRxPackets = parseInt(rxInfo[1],10);

                        var addUpTxBytes = parseInt(txInfo[0],10);
                        var addUpTxPackets = parseInt(txInfo[1],10);

                        $$(this).siblings().filter(function(){ return this.id.match(/rx/) }).text(addUpRxBytes+","+addUpRxPackets);
                        $$(this).siblings().filter(function(){ return this.id.match(/tx/) }).text(addUpTxBytes+","+addUpTxPackets);
                    });
                }//deal with wds-ap table end

                var ap_num=1;
                $$('[id=ap_profile]').each(function(){
                    $$(this).html("#"+ap_num);
                    $$(this).attr("myid","wifi_Profile"+ap_num+"_text");
                    ap_num++;
                });

                var wds_ap_num=1; 
                $$('[id=wds_ap_profile]').each(function(){
                        $$(this).html("#"+wds_ap_num);
                        $$(this).attr("myid","wifi_Profile"+wds_ap_num+"_text");
                        wds_ap_num++;
                });

                $$('[id^=statistic_]').each(function(){
                    var rx_raw_info = $$(this).siblings().filter(function(){ return this.id.match(/rx/) }).text().split(",");
                    var tx_raw_info = $$(this).siblings().filter(function(){ return this.id.match(/tx/) }).text().split(",");

                    var RxBytes = parseInt(rx_raw_info[0],10);
                    var TxBytes = parseInt(tx_raw_info[0],10);

                    var ifc_rx= changeBytes(RxBytes);
                    var ifc_tx= changeBytes(TxBytes);

                    $$(this).siblings().filter(function(){ return this.id.match(/rx/) }).text(ifc_rx);
                    $$(this).siblings().filter(function(){ return this.id.match(/tx/) }).text(ifc_tx);
                });
            }

            if (getById('loading').style.display == "")
            {
                getById('loading').style.display = "none";
            }
        }
    });
}

function getLanSpeed()
{
    data1 = {anticsrf: '<% generateToken("lan_speed") %>', submitType:"lan_speed", speed:1};

    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "device_status.htm") %>',
        data:data1,
        dataType:"json",
        error:function(){
            //console.log("wifi_Channel error");
        },
        success:function(result){
            var speed = parseInt(result.lan_speed);
            if (speed == 0)
                $$('#lan_speed').text("Link down");
            else if (speed < 1000)
                $$('#lan_speed').text(speed+" Mbps");
            else
                $$('#lan_speed').text(speed/1000+" Gbps");

        }
    });

    if (firstInterval)
        clearInterval(firstInterval);

    firstInterval = setInterval("getLanSpeed()", 3000);
}

function getSFM(seconds, dateFormat)
{
    var obj = {};
    var format = "H i s";
    var rs = "";
    obj.H = Number.parseInt(seconds / 3600);
    obj.i = Number.parseInt((seconds - obj.H * 3600) / 60);
    obj.s = Number.parseInt(seconds - obj.H * 3600 - obj.i * 60);

    if (dateFormat) {
        rs = dateFormat.replace('H', obj.H+'h').replace('i', obj.i+'m').replace('s', obj.s+'s');
    } else {
        format = format.replace('H', obj.H+'h').replace('i', obj.i+'m').replace('s', obj.s+'s');
    }
    return rs;
}

function sync_deviceinfo()
{
    data1 = {anticsrf: '<% generateToken("sync_deviceinfo") %>', submitType:"sync_deviceinfo", time:1, mem:1};

    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "device_status.htm") %>',
        data:data1,
        dataType:"json",
        error:function(){
            //console.log("wifi_Channel error");
        },
        success:function(result){
            var e;
            if (e = document.getElementById('localtime'))
                e.innerHTML = result.localtime;
            if (e = document.getElementById('uptime'))
                e.innerHTML = String.format("%t", result.uptime);
            if (e = document.getElementById('memtotal'))
                e.innerHTML = progressbar((result.memfree + result.membuffers + result.memcached) + " KB", result.memtotal + " KB");
            if (e = document.getElementById('memfree'))
                e.innerHTML = progressbar(result.memfree + " KB", result.memtotal + " KB");
            if (e = document.getElementById('memcache'))
                e.innerHTML = progressbar(result.memcached + " KB", result.memtotal + " KB");
            if (e = document.getElementById('membuff'))
                e.innerHTML = progressbar(result.membuffers + " KB", result.memtotal + " KB");
        }
    });

    if (secondInterval)
        clearInterval(secondInterval);

    secondInterval = setInterval("sync_deviceinfo()", 5000);
}

$$( document ).ready(function() {
    if (SUPPORT_COMBINED_SSID_SETTING)
    {
        setTimeout("renew_statistics_func_SSID_based()", 6000);
    }
    else
    {
        setTimeout("renew_statistics_func()", 6000);
    }
    get_hardware_version();
    getLanSpeed();
    sync_deviceinfo();
    check_channel();
});

