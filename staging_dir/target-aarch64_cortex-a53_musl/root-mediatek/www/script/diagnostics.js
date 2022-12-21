var stxhr = new XHR();
var diag_nslookup_csrftoken='<% generateToken("diag_nslookup") %>';
var diag_cat_csrftoken='<% generateToken("diag_cat") %>';
var diag_ping_csrftoken='<% generateToken("diag_ping") %>';
var diag_iperf_csrftoken='<% generateToken("diag_iperf") %>';
var diag_traceroute_csrftoken='<% generateToken("diag_traceroute") %>';
var diag_led_csrftoken='<% generateToken("diag_led") %>';


function update_display(field)
{
	document.getElementById("tab_ping").style.display="none";
	document.getElementById("tab_traceroute").style.display="none";
	document.getElementById("tab_nslookup").style.display="none";
	document.getElementById("tab_speedtest").style.display="none";
	document.getElementById("tab_led").style.display="none";
	
	document.getElementById("ping").setAttribute("class", "cbi-tab-disable");
	document.getElementById("traceroute").setAttribute("class", "cbi-tab-disable");
	document.getElementById("nslookup").setAttribute("class", "cbi-tab-disable");
	document.getElementById("iperf").setAttribute("class", "cbi-tab-disable");
	document.getElementById("led").setAttribute("class", "cbi-tab-disable");
	
	if ("ping" == field)
	{
		document.getElementById("tab_ping").style.display="";
		document.getElementById("ping").setAttribute("class", "cbi-tab active");
	}
	else if ("traceroute" == field)
	{
		document.getElementById("tab_traceroute").style.display="";
		document.getElementById("traceroute").setAttribute("class", "cbi-tab active");
	}
	else if ("nslookup" == field)
	{
		document.getElementById("tab_nslookup").style.display="";
		document.getElementById("nslookup").setAttribute("class", "cbi-tab active");
	}
	else if ("iperf" == field)
	{
		document.getElementById("tab_speedtest").style.display="";
		document.getElementById("iperf").setAttribute("class", "cbi-tab active");
	}
	else
	{
		document.getElementById("tab_led").style.display="";
		document.getElementById("led").setAttribute("class", "cbi-tab active");
		update_led(0);
	}
}

function update_saveButtonStatus(enable)
{
    if (!enable)
    {
        document.getElementById("save_ping").setAttribute("disabled", true);
        document.getElementById("save_traceroute").setAttribute("disabled", true);
        document.getElementById("save_nslookup").setAttribute("disabled", true);
        document.getElementById("save_iperf").setAttribute("disabled", true);
    }
    else
    {
        document.getElementById("save_ping").removeAttribute("disabled");
        document.getElementById("save_traceroute").removeAttribute("disabled");
        document.getElementById("save_nslookup").removeAttribute("disabled");
        document.getElementById("save_iperf").removeAttribute("disabled");
    }
}

function update_led(doSet)
{
    var doLedData = null;
    var powerEnable = $$("input[name='led_power'][value='0']:checked").val() == 0 ? 1 : 0;
    var otherEnable = $$("input[name='led_other'][value='0']:checked").val() == 0 ? 1 : 0;

    if (!doSet)
    {
        doLedData = {anticsrf: diag_led_csrftoken, submitType:'diag_led', set:doSet};
    }
    else
    {
        doLedData = {anticsrf: diag_led_csrftoken, submitType:'diag_led', set:doSet, powerLed:powerEnable, otherLed:otherEnable};
    }

    console.log("powerEnable = ", powerEnable);
    console.log("otherEnable = ", otherEnable);

    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "diagnostics.htm") %>',
        data: doLedData,
        dataType: "json",
        error:function(){
            console.log("led error");
        },
        success:function(result){
            if (!doSet)
            {
                powerEnable = result['powerEnable']^1;
                otherEnable = result['otherEnable']^1;

                $$("input[name='led_power'][value='"+powerEnable+"']").prop("checked", true);
                $$("input[name='led_other'][value='"+otherEnable+"']").prop("checked", true);
            }
        }
    });
}

function update_status(field, proto, output_id, legend_id)
{
    var tool = field, invalid_addr = false, timer, op_str;
    var addr = document.getElementsByName(field)[0].value;
    var protocol = proto ? "6" : "";
    var output_id = output_id || "diag-rc-output",
        legend_id = legend_id || "diag-rc-legend";

    /*Check rule*/
    if (!/^[a-zA-Z0-9][a-zA-Z0-9%-.:_]+$$/.test(addr)) invalid_addr = true;
    if (isMulticast(addr)) invalid_addr = true;
    if (isBroadcastIp(addr, "<%=luci.model.uci.cursor():get('network', 'lan', 'netmask') or '255.255.255.0'%>")) invalid_addr = true;
    if (isLoopback(addr)) invalid_addr = true;
    if (isInvalid(addr)) invalid_addr = true;
    if (addr[addr.length-1] == "\.") invalid_addr = true;

    if (invalid_addr)
    {
        setfocus(getByName(field));
        alert("$target_ip_or_domain_name_is_invalid");
        return false;
    }

    var legend = document.getElementById(legend_id);
    var output = document.getElementById(output_id);
    var doDiagData = null;
    var diagCatData = null;
    var catTimer = 0;

    if (tool == "ping")
    {
        if (!isBetween(getById('pks').value, 64/*<%=PING_SIZE_MIN%>*/, 20480/*<%=PING_SIZE_MAX%>*/) || !isNumber(getById('pks').value))
        {
            setfocus(getById('pks'));
            alert(String.format("$diagnostics_note6", ":", 64/*<%=PING_SIZE_MIN%>*/, 20480/*<%=PING_SIZE_MAX%>*/,"]"));
            return false;
        }
        if (!isBetween(getById('pings').value, 1, 200) || !isNumber(getById('pings').value))
        {
            setfocus(getById('pings'));
            alert("$number_of_pings_is_invalid");
            return false;
        }
        doDiagData = {anticsrf: diag_ping_csrftoken, submitType:'diag_ping', ip:addr, pks:document.getElementById('pks').value, pings:document.getElementById('pings').value};
        catTimer = document.getElementById('pings').value;
    }

    if (tool == "iperf")
    {
        var port_value = document.getElementById('iperf_port').value;
        var iperf_addr = document.getElementById('iperfIp').value;
        if (!isBetween(getById('iperf_timePeriod').value, 1, 9999) || !isNumber(getById('iperf_timePeriod').value))
        {
            setfocus(getById('iperf_timePeriod'));
            alert("$time_period_is_invalid");
            return false;
        }

        if (!isBetween(getById('iperf_checkInterval').value, 1, 60) || !isNumber(getById('iperf_checkInterval').value))
        {
            setfocus(getById('iperf_checkInterval'));
            alert(String.format("$diagnostics_note7", "1", 60));
            return false;
        }
        if (Number(getById('iperf_checkInterval').value) > Number(getById('iperf_timePeriod').value))
        {
            setfocus(getById('iperf_checkInterval'));
            alert("$diagnostics_note8")
            return false;
        }
        if (!isBetween(getById('iperf_port').value, 1, 65535))
        {
            setfocus(getById('iperf_port'));
            alert("$port_is_invalid");
            return false;
        }

        if (!isBetween(getById('iperf_port_v6').value, 1, 65535))
        {
            setfocus(getById('iperf_port_v6'));
            alert("$port_is_invalid");
            return false;
        }

        if (true == isIpv6Addr(addr)){
            port_value = document.getElementById('iperf_port_v6').value;
            if (addr.indexOf("fe80") == 0){
                iperf_addr+="\%br-lan";
            }
        }        

        doDiagData = {anticsrf: diag_iperf_csrftoken, submitType:'diag_iperf', port:port_value, timePeriod:document.getElementById('iperf_timePeriod').value, checkInterval:document.getElementById('iperf_checkInterval').value, iperf:iperf_addr};
        catTimer = document.getElementById('iperf_timePeriod').value;
        catTimer = Number(catTimer) + 1;
    }

    if (tool == "traceroute")
    {
        if (true == isIpv6Addr(addr))
            tool = "traceroute6";
        doDiagData = {anticsrf: diag_traceroute_csrftoken, submitType:'diag_traceroute', ip:addr, "tool":tool};
        catTimer = 30;
    }

    if (tool == "nslookup")
    {
        doDiagData = {anticsrf: diag_nslookup_csrftoken, submitType:'diag_nslookup', ip:addr, "tool":tool};
        catTimer = 4;
    }

    diagCatData = {anticsrf: diag_cat_csrftoken, submitType:'diag_cat', "tool":tool};

    if (legend && output)
    {
        update_saveButtonStatus(false);
        output.innerHTML =
            '<img src="/image/loading.gif" alt="$$loading" style="vertical-align:middle" /> ';

        legend.parentNode.style.display = 'block';
        legend.style.display = 'inline';

        var timeCount = 0;
        timer = setInterval(function(){
            timeCount ++;
            ajax_normal({
                async: false,
                type : "POST",
                url: '<% action_url("apply.cgi", "diagnostics.htm") %>',
                data: diagCatData,
                //dataType: "json",
                error:function(){
                    clearInterval(timer);
                },
                success:function(result){
                    if ("" == result || "NO_INTERNET" == result)
                    {
                        if ("iperf" == tool)
                        {
                            if (timeCount > document.getElementById('iperf_checkInterval').value)
                            {
                                if ("NO_INTERNET" == result)
                                {
                                    output.innerHTML = '<span class="error">$check_internet_and_try_again</span>';
                                }
                                else
                                {
                                    output.innerHTML = '<span class="error">$bad_address_specified</span>';
                                }
                                legend.style.display = 'none';
                                update_saveButtonStatus(true);
                                clearInterval(timer);
                            }
                        }
                        else
                        {
                            if ("NO_INTERNET" == result)
                            {
                                output.innerHTML = '<span class="error">$check_internet_and_try_again</span>';
                            }
                            else
                            {
                                output.innerHTML = '<span class="error">$bad_address_specified</span>';
                            }
                            legend.style.display = 'none';
                            update_saveButtonStatus(true);
                            clearInterval(timer);
                        }
                    }
                    else
                    {
                        op_str = String.format('<pre>%h</pre>', result);
                        output.innerHTML = op_str;
                        if ("ping" == tool)
                        {
                            if (0 <= result.search("%"))
                            {
                                legend.style.display = 'none';
                                update_saveButtonStatus(true);
                                clearInterval(timer);
                            }
                        }
                        else
                        {
                            if (timeCount > catTimer)
                            {
                                legend.style.display = 'none';
                                update_saveButtonStatus(true);
                                clearInterval(timer);
                            }
                        }
                    }
                }
            });
        }, 1000);

        ajax_normal({
            async: false,
            type : "POST",
            url: '<% action_url("apply.cgi", "diagnostics.htm") %>',
            data: doDiagData,
            //dataType: "json",
            error:function(){
                console.log("set cfg error");
            },
            success:function(result){
            }
        });
    }
}

function update_device(){
    var exist_discover = "<%=discover%>",
            emptyRow = "<tr class='title-option'><td colspan='5'>&nbsp;</td></tr>";
    if ("true" == exist_discover)
    {
        var html = "";
        html = "<img src='/image/loading.gif' style='width:21px;'>&nbsp;$$loading....";
        document.getElementById('locator_loading').innerHTML=html;
        XHR.get('<%=luci.dispatcher.build_url("admin", "network")%>/diag_deviceDiscover', null,
            function(x)
            {
                if (x.responseText)
                {
                    var rows = "", device;
                    rows = x.responseText.split("\n");
                    if (rows.length > 2)
                    {
                        html = "";
                        for (var i=1; i<rows.length; i++)
                        {
                            device=rows[i].split("\t");
                            if (device[0] != "")
                            {
                                html+="<tr class='title-option'>"+
                                        "<td>"+device[0]+"</td>"+
                                        "<td>"+device[1]+"</td>"+
                                        "<td>"+device[2]+"</td>"+
                                        "<td>"+device[3]+"</td>"+
                                        "<td>"+device[4]+"</td>"+
                                        "</tr>";
                            }
                        }
                        html += emptyRow;
                    }
                    else
                    {
                        html = emptyRow;
                    }
                }
                else
                {
                    html = emptyRow;
                }
                document.getElementById('locator_content').innerHTML = html;
                document.getElementById('locator_loading').innerHTML = "";
            }
        );
    }
}
function set_otherled(value){
<% if uci:get('functionlist','functionlist','SUPPORT_LED_MODULE_NAME') == '1' then %>
    $$("input[name='led_lan_1'][value='"+value+"']").prop("checked", true);
<% else %>
    $$("input[name='led_lan'][value='"+value+"']").prop("checked", true);
<% end %>
    $$("input[name='led_wlan24'][value='"+value+"']").prop("checked", true);
    $$("input[name='led_wlan5'][value='"+value+"']").prop("checked", true);
    $$("input[name='led_mesh'][value='"+value+"']").prop("checked", true);
    $$("input[name='led_wlan5_2'][value='"+value+"']").prop("checked", true);
}
