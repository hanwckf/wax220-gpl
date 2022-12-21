	var hostname_wifi=new Array(), mac_wifi=new Array(), ip_wifi=new Array();
	var display={};
	var meshdata, macdata, host_alfred;
	var RefreshDelay = 30000;
    var  support_sta_ap=0;

/* 	function getClientInfo(client_mac)
	{
		//console.log(hostname_wifi);
		//console.log(mac_wifi);
		//console.log(ip_wifi);
		var clinetIndex;
		for(var i=0;i<=mac_wifi.length-1;i++)
		{	
			if(client_mac == mac_wifi[i])
			{
				clinetIndex = i;
				break;
			}
			
		}
		return clinetIndex;
	} */


	function hide_delete_button()
	{
		if(document.getElementById('device_list').style.display == "none")
		{
			document.getElementById('del_mesh').style.display = "none";
		}		
	}

	display.kickmacList=[];
	display.maclist={};
	display.transfer_byte = function(bytes)
	{
		var uby = '$kb';
		var kby = bytes;
		if (kby >= 1024)
		{
			uby = '$mb';
			kby = kby / 1024;
			if (kby >= 1024)
			{
				uby = '$gb';
				kby = kby / 1024;
			}
			kby = kby.toFixed(1);
		}
		tmp = kby + uby;
		return tmp;
		//return String.format("%f %s", kby, uby);
	};

	display.wds_bridge = function(data, title)
	{
		var html="", t_idx;
		html += "<table>";
		html += '<tr><td class="title" colspan="4">'+title+'</tr>' +
				'<tr style="background: #EEEEEE;" class="title-option">' +
				'<td style="width:20%;">$wds_link_id#</td>' +
				'<td style="width:30%;">$mac_address</td>' +
				'<td style="width:20%;">$link_status</td>' +
				'<td style="width:20%;">$rssi_dbm</td>' +
				'</tr>';
		for(var i =0;i<data.networks.length;i++)
		{
			if(data.networks[i].nmode == data.opmode)
			{
				//if(!data.networks[i].ssid)
				//{
					t_idx = i;
					break;
				//}
			}
		}
		var k_idx=1, net = data.networks[t_idx],
			assoclist = net.assoclist, obj;
		for (var k in assoclist)
		{
			var isUP=0;

			if(assoclist[k])
			{
				obj = assoclist[k];
				// wds 2.4G connection status
				//if (data.device == "wifi0"){
					if(parseInt(obj.RXRATE)==0){
						isUP = 0;
					}
					else{
						if(obj.idle < 30){
							isUP = 1;
						}
						else{
							isUP = 0;
						}
					}					
				//}
				// wds 5G connection status
				// if (data.device == "wifi1"){
				// 	if(parseInt(obj.RXRATE)==0){
				// 		isUP = 0;
				// 	}
				// 	else{
				// 		// if(obj.idle < 30){
				// 			isUP = 1;
				// 		// }
				// 		// else{
				// 		// 	isUP = 0;
				// 		// }
				// 	}					
				// }
				html += "<tr class='title-option'>" +
						"<td>#" + k_idx + "</td>" +
						"<td>" + k + "</td>" +
						// "<td>" + ((obj.idle < 120) ? "UP" : "DOWN") + "</td>" +
						"<td>" + ((isUP == 1) ? "UP" : "DOWN") + "</td>" +
						"<td>" + obj.rssi + "</td>" +
						"</tr>";
				k_idx += 1;
			}
		}
		
		html += "<tr>" +
				"<td>&nbsp;</td>" +
				"<td>&nbsp;</td>" +
				"<td>&nbsp;</td>" +
				"<td>&nbsp;</td>" +
				"</tr>";
		html += "</table>";
		return html;
	};

	display.wds_sta = function(data, title)
	{
		var html="",t_idx=0, is_assoc;
		if(typeof(data) != "object")
		{
			return html;
		}

		for(var i =0;i<data.networks.length;i++)
		{
			if(data.networks[i].nmode == data.opmode)
			{
				if (support_sta_ap==1)
				{
                    if ( data.opmode == "sta_ap" )
                    {
                        if ( data.networks[i].mode == "Client" )
                        {
                            t_idx = i;
                            break;
                        }
                    }
                }
				else
				{
					t_idx = i;
					break;
				}
			}
		}

		var net = data.networks[t_idx];
		var ssid = net.ssid;//SpecHTML(net.ssid);
		if ((net.bssid != "00:00:00:00:00:00") && (net.bitrate != 0))
			is_assoc = true;
		else
			is_assoc = false;

		html += "<table>";
		html += "<tr>" +
				"<td class='title' colspan='2'>" + title + "</td>" +
				"</tr>" +
				"<tr class='title-option'>" +
				"<td style='width:40%;'>SSID</td>" + "<td style=\"word-break:break-all;\">" + ((net.ssid)?htmlEncode(ssid):"N/A") + "</td>" +
				"</tr>" +
				"<tr class='title-option'>" +
				"<td>BSSID</td>" + "<td>" + ((is_assoc)?net.bssid:"N/A") + "</td>" +
				"</tr>" +
				"<tr class='title-option'>" +
				"<td>$connection_status</td>" + "<td>" + ((is_assoc)?"$associated":"$not_associated") + "</td>" +
				"</tr>"
				
		if(is_assoc)
		{
			html += "<tr class='title-option'>" +
					"<td>$wireless_mode</td>" + "<td>" + showStaHWMode(net.hwmode) + "</td>" +
					"</tr>"+
					"<tr class='title-option'>" +
					"<td>$current_channel</td>" + "<td>" + ((net.frequency) ? net.frequency : "-") + " GHz($channel" + ((net.channel) ? net.channel : "-") + ")</td>" +
					"</tr>";
		}
		else
		{
			html += "<tr class='title-option'>" +
					"<td>$wireless_mode</td>" + "<td>" + "802.11 ac/n/a" + "</td>" +
					"</tr>"+
					"<tr class='title-option'>" +
					"<td>$current_channel</td>" + "<td>N/A</td>" +
					"</tr>";
		}
		html += "<tr class='title-option'>" +
				//"<td>$$security</td>" + "<td>" + showEncryption(net.encryption_option) + "</td>" +
                "<td>$security</td>" + "<td>" + net.encryption_option + "</td>" +
				"</tr>";
		if(is_assoc)
		{
			html += "<tr class='title-option'>" +
					"<td>$tx_data_rates(Mbps)</td>" + "<td>" + ((net.bitrate) ? (((net.bitrate_unit.match("Gb/s")) ? ( net.bitrate * 1000 ) : net.bitrate) + " Mb/s") : "N/A") + "</td>" +
					"</tr>" +
					"<tr class='title-option'>" +
					"<td>$current_noise_level</td>" + "<td>" + net.noise + "&nbsp;dBm</td>" +
					"</tr>" +
					"<tr class='title-option'>" +
					"<td>$signal_strength</td>" + "<td>" + net.signal + "&nbsp;dBm</td>" +
					"</tr>";
		}
		else
		{
			html += "<tr class='title-option'>" +
					"<td>$tx_data_rates(Mbps)</td>" + "<td>N/A</td>" +
					"</tr>" +
					"<tr class='title-option'>" +
					"<td>$current_noise_level</td>" + "<td>N/A</td>" +
					"</tr>" +
					"<tr class='title-option'>" +
					"<td>$signal_strength</td>" + "<td>N/A</td>" +
					"</tr>";
		}
		html += "</table>";
		return html;
	};
	display.kickMe = function(mac, ifname, networkname)
	{
		var j = display.maclist[networkname];
		var denylistarray = j.deny.split(" ");
		var max_size = 32;
		if (parseInt(denylistarray.length) >= max_size) {
			alert("$wireless_connection_alert_1");
		}
		else {
			var str;
			(j.allow.indexOf(mac.toUpperCase()) > -1) ? str = "This " + mac + " will be deleted from the allow list." : str = "MAC filter deny mode will be enabled. This " + mac + " will be added to the deny list."
			if (confirm(str)) {
				var form = document.forms[0];

				form.networkname.value = networkname;
				form.mac.value = mac;

				display.kickmacList.push(mac);

				return true;
			}
		}
		return false;
	};
	display.ap = function(data, title)
	{
		var net, is_assoc, html="", obj;
		if(typeof(data) != "object")
		{
			return html;
		}

		html ="<table style='min-width:1200px'>" +
/* <% if uci:get('functionlist','functionlist','SUPPORT_FINGER_PRINT') == '1' then -----#### SUPPORT_FINGER_PRINT START ###
%>
				"<tr><td colspan='7' class='title'>"+title+"</td></tr>" +
				"<tr style='background: #EEEEEE;' class='title-option'>" +
				'<td style="width:15%;"><%:Hostname%></td>' +
				'<td style="width:15%;"><%:MAC Address%></td>' +
				'<td style="width:15%;"><%:SSID%></td>' +
				'<td style="width:15%;"><%:TX%> (KB)</td>' +
				'<td style="width:15%;"><%:RX%> (KB)</td>' +
				'<td style="width:15%;"><%:RSSI%> (dBm)</td>' +
				'<td style="width:10%;"><%:Block%></td>' +
<%
	else -----#### SUPPORT_FINGER_PRINT ELSE ###
%> */
				"<tr><td colspan='8' class='title'>"+title+"</td></tr>" +
				"<tr style='background: #EEEEEE;' class='title-option'>" +
				'<td style="width:15%;">$hostname</td>' +
				'<td style="width:10%;">$ipaddr</td>' +
				'<td style="width:14%;">$mac_address</td>' +
				'<td style="width:25%;">$ssid</td>' +
				'<td style="width:10%;">$tx($bytes)</td>' +
				'<td style="width:10%;">$rx($bytes)</td>' +
				'<td style="width:8%;">$rssi</td>' +
				'<td style="width:8%;">$block</td>' +
/* <%
	end -----#### SUPPORT_FINGER_PRINT END ###
%> */
				"</tr>";

		for(var i=0;i<data.networks.length;i++)
		{
			net = data.networks[i];
			var ssid = net.ssid;//SpecHTML(net.ssid);

			if(!net.ssid || net.nawds == "1") 
			{
				continue;  //is nawds
			}

			is_assoc = ((net.bssid != '00:00:00:00:00:00') && (net.up == "true") && (net.networkname.indexOf("sta_ap_2") == -1)); //skip ath29
			if(is_assoc)
			{
				for(key in net.assoclist)
				{
					obj = net.assoclist[key];
					if(obj && ($$.inArray(key, display.kickmacList) == -1))
					{
						html+="<tr id='ap_"+ obj.mac +"' style=\"background: #FFFFFF; font-size: 16px;\" class='title-option'>";
						html+="<td>"+obj.hostname+"</td>"; //<%#Hostname%>
						html+="<td>"+obj.ipaddr+"</td>"; //<%#Hostname%>
						html+="<td>"+obj.mac+"</td>"; //<%#MAC addresss%>
						html+="<td style=\"word-break:break-all;\">"+htmlEncode(ssid)+"</td>"; //<%#SSID%>

						if (obj.info.tx_bytes)
						{
							html+="<td>"+this.transfer_byte(obj.info.tx_bytes.split('Kb')[0])+"</td>"; //<%#TX%>
						}
						else
						{
							html+="<td>Kb</td>"; //<%#TX%>
						}
						if (obj.info.rx_bytes)
						{
							html+="<td>"+this.transfer_byte(obj.info.rx_bytes.split('Kb')[0])+"</td>"; //<%#RX%>
						}
						else
						{
							html+="<td>Kb</td>"; //<%#RX%>
						}
						html+="<td>"+obj.info.rssi+"dBm</td>"; //<%#RSSI%>

                        var apcontroller_capwap_enable=0;//<% cfg_get("apcontroller_capwap_enable") %>;
						
                        if (apcontroller_capwap_enable)
                        {
                            html+="<td>" +"<input class='cbi-button' type='submit' onclick='return display.kickMe(\""+obj.mac+"\",\""+net.ifname+"\",\""+net.networkname+"\");' value='Kick' disabled>" +"</td>"; //<%#Block%>
                        }						
                        else
                        {
                            html+="<td>" +"<input class='cbi-button' type='submit' onclick='return display.kickMe(\""+obj.mac+"\",\""+net.ifname+"\",\""+net.networkname+"\");' value=$Kick>" +"</td>"; //<%#Block%>
                        }
						html+="</tr>";
					}
				}
			}

			display.maclist[net.networkname] = {filter: net.filter, allow: net.allow, deny: net.deny};
		}
		html += "</table>";
		return html;
	};
/* <%
local uci = require "luci.model.uci".cursor()
if uci:get('functionlist','functionlist','SUPPORT_RENEW_CONNECT_STATUS_BY_BUTTON') == '1' then -----#### SUPPORT_RENEW_CONNECT_STATUS_BY_BUTTON START ###
%> */
function renew_connection_func(){
	dataStr = {anticsrf: '<% generateToken("get_lan_dev") %>', submitType:"get_lan_dev"};
	ajax_normal({
		async: false,
		type : "post",
		url: '<% action_url("apply.cgi", "wireless_connections.htm") %>',
		data:dataStr,
		dataType:"json",
		error:function(){
			//alert("ajax_checkChannel error");
		},
		success:function(result){
			//info = <% cfg_get("lan_dev") %>;
			{
				var disp="";
				var wifiTable = {0:"2.4GHz",1:"5GHz"};
				for (var didx = 0; didx < result.wifinets.length; didx++)
				{
					if (result.wifinets[didx] && result.wifinets[didx].device != "") {
						//if(result.wifinets[didx].opmode == "wds_sta" || result.wifinets[didx].opmode == "sta" <% if support_sta_ap==1 then %> || info.wifinets[didx].opmode == "sta_ap" <% end %>)
						if(result.wifinets[didx].opmode == "wds_sta" || result.wifinets[didx].opmode == "sta")
						{
							disp += display.wds_sta(result.wifinets[didx], "$connection_status - "+wifiTable[didx]+"");

							if (support_sta_ap==1)
							{
								if(result.wifinets[didx].opmode == "sta_ap"){
									disp += display.ap(result.wifinets[didx], "$connection_list - "+wifiTable[didx]+"");
								}
							}
						}
						else if(result.wifinets[didx].opmode == "wds_ap" || result.wifinets[didx].opmode == "wds_bridge")
						{
							if(result.wifinets[didx].opmode == "wds_ap"){
								disp += display.ap(result.wifinets[didx], "$connection_list - "+wifiTable[didx]+"");
							}
						}
						else if(result.wifinets[didx].opmode == "ap" )
						{
							disp += display.ap(result.wifinets[didx], "$connection_list ($total: "+result.wifinets[didx].total+") - "+wifiTable[didx]+"");
						}
					}
				}

				$$('#connection_display').html(disp);
				document.getElementById('loading').style.display = "none";
				document.getElementById('connection_display').style.display = "";
			}
		}
	});
}
/* function getClietData()
{
	var url,data;
				url='<%=luci.dispatcher.build_url("admin/status/clientInfo")%>';
				data =  {};
				ajax_normal(
				{
				    async: false,
			        type : "GET",
			        url:url,
			        data:data,
			        dataType:"json",
				    error:function(){},
			        success:function(result)
			        {
						var wifi_client_info = result["info"];
						for(var i=0;i<=wifi_client_info.length-1;i++)
						{
							if(wifi_client_info[i]!="")
							{
								var wifi_devlist;
								wifi_devlist = wifi_client_info[i].split("|");
								hostname_wifi[i] = wifi_devlist[3];
								mac_wifi[i] = wifi_devlist[0];
								ip_wifi[i] = wifi_devlist[1];
							}
						}
			        }
				});
} */
function refresh_devs (){
	document.getElementById('loading').style.display = "";
	window.setTimeout("renew_connection_func()", 3000);
   }
$$( document ).ready(function() {
	renew_connection_func();
});
/* <%
else-----####  SUPPORT_RENEW_CONNECT_STATUS_BY_BUTTON ELSE #### 
%>	
	XHR.poll(3, '<%=luci.dispatcher.build_url("admin", "status", "overview")%>', { status:1 },
	function(x, info){
		if(x.responseText)
		{
			var disp="";

<% if uci:get('functionlist','functionlist','SUPPORT_WLAN5G_2') == '1' then --[[ #### WLAN5G_2 feature ### --]] %>
		var wifiTable = {0:"2.4GHz",1:"5GHz - 1",2:"5GHz - 2"};
<% else %>
		var wifiTable = {0:"2.4GHz",1:"5GHz"};
<% end --[[ #### WLAN5G_2 feature ### --]] %>
	
			for (var didx = 0; didx < info.wifinets.length; didx++)
			{
				if (info.wifinets[didx]) {
					if(info.wifinets[didx].opmode == "wds_sta" || info.wifinets[didx].opmode == "sta" <% if support_sta_ap==1 then %> || info.wifinets[didx].opmode == "sta_ap" <% end %>)
					{
						disp += display.wds_sta(info.wifinets[didx], "<%:Connection Status%> - "+wifiTable[didx]+"");
<% if support_sta_ap==1 then %>
						if(info.wifinets[didx].opmode == "sta_ap"){
							disp += display.ap(info.wifinets[didx], "<%:Connection List%> - "+wifiTable[didx]+"");
						}
<% end %>
					}
					else if(info.wifinets[didx].opmode == "wds_ap" || info.wifinets[didx].opmode == "wds_bridge")
					{
						//disp += display.wds_bridge(info.wifinets[didx], "<%:WDS Link List%> - "+wifiTable[didx]+"");
						if(info.wifinets[didx].opmode == "wds_ap"){
							disp += display.ap(info.wifinets[didx], "<%:Connection List%> - "+wifiTable[didx]+"");
						}
					}
					else if(info.wifinets[didx].opmode == "ap")
					{
						disp += display.ap(info.wifinets[didx], "<%:Connection List%> - "+wifiTable[didx]+"");
					}
				}
			}

			$$('#connection_display').html(disp);
			if(document.getElementById('loading').style.display == "")
			{
				document.getElementById('loading').style.display = "none";
				document.getElementById('connection_display').style.display = "";
				if("<%=uci:get('functionlist','functionlist','SUPPORT_MESH_SETTING')%>" == "2")
				{
					if("<%=uci:get('wireless','wifi0_mesh','disabled')%>" == "0" || "<%=uci:get('wireless','wifi1_mesh','disabled')%>" == "0")
					document.getElementById('mesh_table').style.display = "";
				}
			}
		}
	});
<%
end-----####  SUPPORT_RENEW_CONNECT_STATUS_BY_BUTTON END #### 
%> */
