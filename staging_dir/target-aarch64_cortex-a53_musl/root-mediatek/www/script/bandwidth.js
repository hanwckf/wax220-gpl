var opmode_path;
var G, G_5g;
var not_apmode;
var curdev = "";
var TIME = 0;
var RXB  = 1;
var RXP  = 2;
var TXB  = 3;
var TXP  = 4;

var width  = 760;
var height = 300;
var step   = 5;

var data_wanted = Math.floor(width / step);
var data_fill   = 0;
var data_stamp  = 0;
var iface_24g;
var data_rx = [ ];
var data_tx = [ ];
var line_rx;
var line_tx;
var label_25;
var label_50;
var label_75;
var label_rx_cur;
var label_rx_avg;
var label_rx_peak;
var label_tx_cur;
var label_tx_avg;
var label_tx_peak;
var label_scale;

var iface_5g;
var data_rx_5g = [ ];
var data_tx_5g = [ ];
var line_rx_5g;
var line_tx_5g;
var label_25_5g;
var label_50_5g;
var label_75_5g;
var label_rx_cur_5g;
var label_rx_avg_5g;
var label_rx_peak_5g;
var label_tx_cur_5g;
var label_tx_avg_5g;
var label_tx_peak_5g;
var data_stamp_5g  = 0;
var label_scale_5g;

var data_rx_5g_2 = [ ];
var data_tx_5g_2 = [ ];
var line_rx_5g_2;
var line_tx_5g_2;
var label_25_5g_2;
var label_50_5g_2;
var label_75_5g_2;
var label_rx_cur_5g_2;
var label_rx_avg_5g_2;
var label_rx_peak_5g_2;
var label_tx_cur_5g_2;
var label_tx_avg_5g_2;
var label_tx_peak_5g_2;
var label_scale_5g_2;
var iface_5g_2;
var data_stamp_5g_2  = 0;

var data_rx_lan = [ ];
var data_tx_lan = [ ];
var line_rx_lan;
var line_tx_lan;
var label_25_lan;
var label_50_lan;
var label_75_lan;
var label_rx_cur_lan;
var label_rx_avg_lan;
var label_rx_peak_lan;
var label_tx_cur_lan;
var label_tx_avg_lan;
var label_tx_peak_lan;
var label_scale_lan;
var iface_lan;
var data_stamp_lan  = 0;
var iface1_24g_disabled, iface1_5g_disabled;
var iface2_24g_disabled, iface2_5g_disabled;
var iface3_24g_disabled, iface3_5g_disabled;
var iface4_24g_disabled, iface4_5g_disabled;
var cbi_flag="";


function setCookie(name, value, day){

	if(day !== 0){
	var expires = day * 24 * 60 * 60 * 1000;
	var date = new Date(+new Date()+expires);
	document.cookie = name + "=" + escape(value) + ";expires=" + date.toUTCString() + ";path=/";
	}else{
	document.cookie = name + "=" + escape(value) + ";path=/";
	}
}

function delCookie(name) {
	setCookie(name, ' ', -1);
}

function  show1() {
	setCookie("cbi_flag", "ssid1", 0);
}

function  show2() {
	setCookie("cbi_flag", "ssid2", 0);
}

function  show3() {
	setCookie("cbi_flag", "ssid3", 0);
}

function  show4() {
	setCookie("cbi_flag", "ssid4", 0);
}

function  show5() {
	setCookie("cbi_flag", "lan", 0);
}

function graph_default(radio)
{
	var svg = eval(document.getElementById('bwsvg'+radio+''));

	if(svg)
	{
		try
		{
			G=svg.getSVGDocument
					?svg.getSVGDocument():svg.contentDocument;
		}
		catch (e)
		{
			G=document.embeds['bwsvg'].getSVGDocument();
		}
	}
	if (G)
	{
		/* find sizes */
		width       = svg.offsetWidth  - 2;
		height      = svg.offsetHeight - 2;
		data_wanted = Math.ceil(width / step);

		/* prefill datasets */
		for (var i = 0; i < data_wanted; i++)
		{
			eval("data_rx"+radio+"[i]= 0");
			eval("data_tx"+radio+"[i]= 0");
		}

		/* find svg elements */
		eval("line_rx"+radio+" = G.getElementById('rx')");
		eval("line_tx"+radio+" = G.getElementById('tx')");
		eval("label_25"+radio+" = G.getElementById(\"label_25"+radio+"\")");
		eval("label_50"+radio+" = G.getElementById(\"label_50"+radio+"\")");
		eval("label_75"+radio+" = G.getElementById(\"label_75"+radio+"\")");
		eval("label_rx_cur"+radio+" = document.getElementById(\"rx_bw_cur"+radio+"\")");
		eval("label_rx_avg"+radio+" = document.getElementById(\"rx_bw_avg"+radio+"\")");
		eval("label_rx_peak"+radio+" = document.getElementById(\"rx_bw_peak"+radio+"\")");
		eval("label_tx_cur"+radio+" = document.getElementById(\"tx_bw_cur"+radio+"\")");
		eval("label_tx_avg"+radio+" = document.getElementById(\"tx_bw_avg"+radio+"\")");
		eval("label_tx_peak"+radio+" = document.getElementById(\"tx_bw_peak"+radio+"\")");
		eval("label_scale"+radio+" = document.getElementById(\"scale"+radio+"\")");

		/* plot horizontal time interval lines */
		for (var i = width % (step * 60); i < width; i += step * 60)
		{
			var line = G.createElementNS('http://www.w3.org/2000/svg', 'line');
				line.setAttribute('x1', i);
				line.setAttribute('y1', 0);
				line.setAttribute('x2', i);
				line.setAttribute('y2', '100%');
				line.setAttribute('style', 'stroke:black;stroke-width:0.1');

			var text = G.createElementNS('http://www.w3.org/2000/svg', 'text');
				text.setAttribute('x', i + 5);
				text.setAttribute('y', 15);
				text.setAttribute('style', 'fill:#999999; font-size:9pt');
				text.appendChild(G.createTextNode(Math.round((width - i) / step / 60) + 'm'));

		}
		var num = Math.floor(data_wanted / 60);
		var str = "label_scale"+radio+".innerHTML = String.format('$traffic_info', num, 3)";
		eval(str);
	}
}
function drawGraph(radio)
{
	if (!G)
	{
		//XHR.get('<%=build_url("admin/status/realtime/bandwidth_status", curdev)%>', null,
			//function(x, data)
			{
				eval("label_rx_cur"+radio+" = document.getElementById(\"rx_bw_cur"+radio+"\")");
				eval("label_rx_avg"+radio+" = document.getElementById(\"rx_bw_avg"+radio+"\")");
				eval("label_rx_peak"+radio+" = document.getElementById(\"rx_bw_peak"+radio+"\")");
				eval("label_tx_cur"+radio+" = document.getElementById(\"tx_bw_cur"+radio+"\")");
				eval("label_tx_avg"+radio+" = document.getElementById(\"tx_bw_avg"+radio+"\")");
				eval("label_tx_peak"+radio+" = document.getElementById(\"tx_bw_peak"+radio+"\")");
				
				var data_max   = 0;

				var data_rx_avg = 0;
				var data_tx_avg = 0;

				var data_rx_peak = 0;
				var data_tx_peak = 0;

				if((data != null) && (data.length != null))
				{
					for (var i = eval("data_stamp"+radio+"") ? 0 : 1; i < data.length; i++)
					{
						/* skip overlapping entries */
						if (data[i].time_tmp <= eval("data_stamp"+radio+""))
							continue;

						/* normalize difference against time interval */
						if (i > 0)
						{
							var time_delta = data[i].time_tmp - data[i-1].time_tmp;
							if (time_delta)
							{
								eval("data_rx"+radio+".push((data[i].rxb - data[i-1].rxb) / time_delta)");
								eval("data_tx"+radio+".push((data[i].txb - data[i-1].txb) / time_delta)");
							}
						}
					}

					/* cut off outdated entries */
					eval("data_rx"+radio+" = data_rx"+radio+".slice(data_rx"+radio+".length - data_wanted, data_rx"+radio+".length)");
					eval("data_tx"+radio+" = data_tx"+radio+".slice(data_tx"+radio+".length - data_wanted, data_tx"+radio+".length)");

					/* find peak */
					for (var i = 0; i < eval("data_rx"+radio+".length"); i++)
					{
						eval("data_max = Math.max(data_max, data_rx"+radio+"[i])");
						eval("data_max = Math.max(data_max, data_tx"+radio+"[i])");

						eval("data_rx_peak = Math.max(data_rx_peak, data_rx"+radio+"[i])");
						eval("data_tx_peak = Math.max(data_tx_peak, data_tx"+radio+"[i])");

						if (i > 0)
						{
							eval("data_rx_avg = (data_rx_avg + data_rx"+radio+"[i]) / 2");
							eval("data_tx_avg = (data_tx_avg + data_tx"+radio+"[i]) / 2");
						}
						else
						{
							eval("data_rx_avg = data_rx"+radio+"[i]");
							eval("data_tx_avg = data_tx"+radio+"[i]");
						}
					}
					/* remember current timestamp, calculate horizontal scale */
					eval("label_rx_cur"+radio+".innerHTML = bandwidth_label(data_rx"+radio+"[data_rx"+radio+".length-1], true)");
					eval("label_tx_cur"+radio+".innerHTML = bandwidth_label(data_tx"+radio+"[data_tx"+radio+".length-1], true)");
					eval("label_rx_avg"+radio+".innerHTML = bandwidth_label(data_rx_avg, true)");
					eval("label_tx_avg"+radio+".innerHTML = bandwidth_label(data_tx_avg, true)");
					eval("label_rx_peak"+radio+".innerHTML = bandwidth_label(data_rx_peak, true)");
					eval("label_tx_peak"+radio+".innerHTML = bandwidth_label(data_tx_peak, true)");
				}
			}
		//);
		
		window.setTimeout(arguments.callee, 1000);
	}
	else
	{
			var message = cbi_flag + radio;
			var index;
			if (message == "ssid1")
			{
				index = 0;
			}
			else if (message == "ssid2")
			{
				index = 1;
			}
			else if (message == "ssid3")
			{
				index = 2;
			}
			else if (message == "ssid4")
			{
				index = 3;
			}
			else if (message == "ssid1_5g")
			{
				index = 5;
			}
			else if (message == "ssid2_5g")
			{
				index = 6;
			}
			else if (message == "ssid3_5g")
			{
				index = 7;
			}
			else if (message == "ssid4_5g")
			{
				index = 8;
			}
			else if (message == "lan_lan")
			{
				index = 9;
			}

			data1 = {anticsrf: '<% generateToken("traffic_load") %>', submitType:"traffic_load", load:index};

			ajax_normal({
				async: false,
				type : "POST",
				url: '<% action_url("apply.cgi", "bandwidth.htm") %>',
				data:data1,
				dataType:"json",
				error:function(){
					//console.log("wifi_Channel error");
				},
				success:function(data){

				if (!data)
				{
					eval("label_rx_cur"+radio+".innerHTML = bandwidth_label(0, true)");
					eval("label_tx_cur"+radio+".innerHTML = bandwidth_label(0, true)");
					eval("label_rx_avg"+radio+".innerHTML = bandwidth_label(0, true)");
					eval("label_tx_avg"+radio+".innerHTML = bandwidth_label(0, true)");
					eval("label_rx_peak"+radio+".innerHTML = bandwidth_label(0, true)");
					eval("label_tx_peak"+radio+".innerHTML = bandwidth_label(0, true)");
					
					eval("line_rx"+radio+".setAttribute('style', 'display:none;')");
					eval("line_tx"+radio+".setAttribute('style', 'display:none;')");
					return;
				}

				var data_max   = 0;
				var data_scale = 0;

				var data_rx_avg = 0;
				var data_tx_avg = 0;

				var data_rx_peak = 0;
				var data_tx_peak = 0;

				for (var i = eval("data_stamp"+radio+"") ? 0 : 1; i < data.length; i++)
				{
					/* skip overlapping entries */
					if (data[i].time_tmp <= eval("data_stamp"+radio+""))
						continue;

					/* normalize difference against time interval */
					if (i > 0)
					{
						var time_delta = data[i].time_tmp - data[i-1].time_tmp;
						if (time_delta)
						{
							eval("data_rx"+radio+".push((data[i].rxb - data[i-1].rxb) / time_delta)");
							eval("data_tx"+radio+".push((data[i].txb - data[i-1].txb) / time_delta)");
						}
					}
				}

				/* cut off outdated entries */
				eval("data_rx"+radio+" = data_rx"+radio+".slice(data_rx"+radio+".length - data_wanted, data_rx"+radio+".length)");
				eval("data_tx"+radio+" = data_tx"+radio+".slice(data_tx"+radio+".length - data_wanted, data_tx"+radio+".length)");

				/* find peak */
				for (var i = 0; i < eval("data_rx"+radio+".length"); i++)
				{
					eval("data_max = Math.max(data_max, data_rx"+radio+"[i])");
					eval("data_max = Math.max(data_max, data_tx"+radio+"[i])");

					eval("data_rx_peak = Math.max(data_rx_peak, data_rx"+radio+"[i])");
					eval("data_tx_peak = Math.max(data_tx_peak, data_tx"+radio+"[i])");

					if (i > 0)
					{
						eval("data_rx_avg = (data_rx_avg + data_rx"+radio+"[i]) / 2");
						eval("data_tx_avg = (data_tx_avg + data_tx"+radio+"[i]) / 2");
					}
					else
					{
						eval("data_rx_avg = data_rx"+radio+"[i]");
						eval("data_tx_avg = data_tx"+radio+"[i]");
					}
				}

				/* remember current timestamp, calculate horizontal scale */
				eval("data_stamp"+radio+"=data[data.length-1][TIME]");
				if(data_max!=0){
					data_scale = height / (data_max * 1.1);
				}else{
					data_scale = 0;
				}

				eval("data_rx"+radio+".reverse()");
				eval("data_tx"+radio+".reverse()");

				/* plot data */
				var pt_rx = '0,' + height;
				var pt_tx = '0,' + height;

				var y_rx = 0;
				var y_tx = 0;

				for (var i = 0; i < eval("data_rx"+radio+".length"); i++)
				{
					var x = i * step;

					y_rx = height - Math.floor(eval("data_rx"+radio+"[i] * data_scale"));
					y_tx = height - Math.floor(eval("data_tx"+radio+"[i] * data_scale"));

					pt_rx += ' ' + x + ',' + y_rx;
					pt_tx += ' ' + x + ',' + y_tx;
				}

				pt_rx += ' ' + width + ',' + y_rx + ' ' + width + ',' + height;
				pt_tx += ' ' + width + ',' + y_tx + ' ' + width + ',' + height;
		
				eval("line_rx"+radio+".setAttribute('points', pt_rx)");
				eval("line_rx"+radio+".setAttribute('style', 'fill:none;stroke:blue;stroke-width:1;')");
				eval("line_tx"+radio+".setAttribute('points', pt_tx)");
				eval("line_tx"+radio+".setAttribute('style', 'fill:none;stroke:green;stroke-width:1;')");

				eval("data_rx"+radio+".reverse()");
				eval("data_tx"+radio+".reverse()");

				var v_top = bandwidth_label(1.1 * 0.25 * data_max, true, "none");
				eval($$("#bwsvg"+radio+"").css("width",  (v_top != 0)? (v_top >= 100)?"93%":"95%" :"97%"));
				
				eval($$("#label_25"+radio+"").html(bandwidth_label(1.1 * 0.25 * data_max, true, "none")));
				eval($$("#label_50"+radio+"").html(bandwidth_label(1.1 * 0.50 * data_max, true, "none")));
				eval($$("#label_75"+radio+"").html(bandwidth_label(1.1 * 0.75 * data_max, true, "none")));

				eval("label_rx_cur"+radio+".innerHTML = bandwidth_label(data_rx"+radio+"[data_rx"+radio+".length-1], true)");
				eval("label_tx_cur"+radio+".innerHTML = bandwidth_label(data_tx"+radio+"[data_tx"+radio+".length-1], true)");
				eval("label_rx_avg"+radio+".innerHTML = bandwidth_label(data_rx_avg, true)");
				eval("label_tx_avg"+radio+".innerHTML = bandwidth_label(data_tx_avg, true)");
				eval("label_rx_peak"+radio+".innerHTML = bandwidth_label(data_rx_peak, true)");
				eval("label_tx_peak"+radio+".innerHTML = bandwidth_label(data_tx_peak, true)");	
			}
		});
	}
}
function bandwidth_label(bytes, br, showParamters)
{
	showParamters = showParamters || true;
	var uby = 'KB/s';
	var kby = (bytes / 1024);

	if (kby >= 1024)
	{
		uby = 'MB/s';
		kby = kby / 1024;
	}

	var ubi = 'kbit/s';
	var kbi = (bytes * 8 / 1024);

	if (kbi >= 1024)
	{
		ubi = 'Mbit/s';
		kbi = kbi / 1024;
	}

	$$('#bandwidth').html(uby);
	var a = kby.toFixed(2);
	var b;
	if (showParamters != "none")
		b = uby;
	else
		b = "";
	var str = a+b;
	return str;

}

/* wait for SVG */
//function abc(){
window.setTimeout(
	function() {

		if (cbi_flag == "lan") // lan
		{
			document.getElementById('graph_lan').style.display = "";
			graph_default("_lan");
			window.setInterval("drawGraph(\"_lan\")",3000);
		}
		else
		{
			if (cbi_flag == "ssid1")
			{
				if(iface1_24g_disabled == 0)
				{
					document.getElementById('graph_24g').style.display = "";
					graph_default("");
					window.setInterval("drawGraph(\"\")",3000);
				}

				if(iface1_5g_disabled == 0)
				{
					document.getElementById('graph_5g').style.display = "";
					graph_default("_5g");
					window.setInterval("drawGraph(\"_5g\")",3000);
				}
			}
			else if (cbi_flag == "ssid2")
			{
				if(iface2_24g_disabled == 0)
				{
					document.getElementById('graph_24g').style.display = "";
					graph_default("");
					window.setInterval("drawGraph(\"\")",3000);
				}

				if(iface2_5g_disabled == 0)
				{
					document.getElementById('graph_5g').style.display = "";
					graph_default("_5g");
					window.setInterval("drawGraph(\"_5g\")",3000);
				}
			}
			else if (cbi_flag == "ssid3")
			{
				if(iface3_24g_disabled == 0)
				{
					document.getElementById('graph_24g').style.display = "";
					graph_default("");
					window.setInterval("drawGraph(\"\")",3000);
				}

				if(iface3_5g_disabled == 0)
				{
					document.getElementById('graph_5g').style.display = "";
					graph_default("_5g");
					window.setInterval("drawGraph(\"_5g\")",3000);
				}
			}
			else if (cbi_flag == "ssid4")
			{
				if(iface4_24g_disabled == 0)
				{
					document.getElementById('graph_24g').style.display = "";
					graph_default("");
					window.setInterval("drawGraph(\"\")",3000);
				}
			
				if(iface4_5g_disabled == 0)
				{
					document.getElementById('graph_5g').style.display = "";
					graph_default("_5g");
					window.setInterval("drawGraph(\"_5g\")",3000);
				}
			}
		}
	//}
	}, 1000
);

$$(document).ready(function(){
	var l = "cbi_flag=".length;
	var s = document.cookie.indexOf("cbi_flag");
	var e = document.cookie.indexOf(";", s + l);
	if (s != -1 && e != -1){
		// cookie存在，拿到数据
		cbi_flag = document.cookie.substr(s + l, e - s - l);
		delCookie("cbi_flag");
	} else if (s != -1) {
		// cookie存在，拿到数据
		cbi_flag = document.cookie.substr(s + l);
		delCookie("cbi_flag");
	}

	if (cbi_flag == "")
	{
		if (wl_radio == "1" || wla_radio == "1")
		{
			cbi_flag = "ssid1";
		}
		else if (wl1_radio == "1" || wla1_radio == "1")
		{
			cbi_flag = "ssid2";
		}
		else if (wl2_radio == "1" || wla2_radio == "1")
		{
			cbi_flag = "ssid3";
		}
		else if (wl3_radio == "1" || wla3_radio == "1")
		{
			cbi_flag = "ssid4";
		}
	}

	if (cbi_flag == "" || cbi_flag == "lan")
	{
		cbi_flag = "lan";
		$$('#graph_24g').css('display','none');
		$$('#graph_5g').css('display','none');
	}
	else if (cbi_flag == "ssid1")
	{
		if (wl_radio != "1")
			$$('#graph_24g').css('display','none');
		else
			iface1_24g_disabled=0;
		if (wla_radio != "1")
			$$('#graph_5g').css('display','none');
		else
			iface1_5g_disabled=0;
		$$('#graph_lan').css('display','none');
	}
	else if (cbi_flag == "ssid2")
	{
		if (wl1_radio != "1")
			$$('#graph_24g').css('display','none');
		else
			iface2_24g_disabled=0;
		if (wla1_radio != "1")
			$$('#graph_5g').css('display','none');
		else
			iface2_5g_disabled=0;
		$$('#graph_lan').css('display','none');
	}
	else if (cbi_flag == "ssid3")
	{
		if (wl2_radio != "1")
			$$('#graph_24g').css('display','none');
		else
			iface3_24g_disabled=0;
		if (wla2_radio != "1")
			$$('#graph_5g').css('display','none');
		else
			iface3_5g_disabled=0;
		$$('#graph_lan').css('display','none');
	}
	else if (cbi_flag == "ssid4")
	{
		if (wl3_radio != "1")
			$$('#graph_24g').css('display','none');
		else
			iface4_24g_disabled=0;
		if (wla3_radio != "1")
			$$('#graph_5g').css('display','none');
		else
			iface4_5g_disabled=0;
		$$('#graph_lan').css('display','none');
	}

	getById(cbi_flag).classList.remove('cbi-tab-disabled');
	getById(cbi_flag).classList.add('cbi-tab');

	$$('#graph_5g_2').css('display','none');

})
