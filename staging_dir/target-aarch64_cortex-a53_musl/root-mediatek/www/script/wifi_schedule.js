var SCHEDULEDATA = <% cfg_get("wifi_schedule_data") %>;
var SCHEDULEDAY = {"ssid0":{"day0":"cfg00", "day1":"cfg01", "day2":"cfg02", "day3":"cfg03", "day4":"cfg04", "day5":"cfg05", "day6":"cfg06"}, "ssid1":{ "day0":"cfg10", "day1":"cfg11", "day2":"cfg12", "day3":"cfg13", "day4":"cfg14", "day5":"cfg15", "day6":"cfg16"}, "ssid2": { "day0":"cfg20", "day1":"cfg21", "day2":"cfg22", "day3":"cfg23", "day4":"cfg24", "day5":"cfg25", "day6":"cfg26"}, "ssid3":{ "day0": "cfg30", "day1": "cfg31", "day2": "cfg32", "day3": "cfg33", "day4": "cfg34", "day5": "cfg35", "day6": "cfg36"}};

var opmode = {}, wifiTable = {}, radioNum = 0;

<% if WLAN24G == "1" then
    radioNum = radioNum+1
%>
    opmode[0] = "ap";
    wifiTable[0] = "2.4GHz";
    radioNum = radioNum+1;
<% end %>
<% if WLAN5G == "1" then
    radioNum = radioNum+1
%>
    opmode[1]= "ap";
    wifiTable[1] = "5GHz";
    radioNum = radioNum+1;
    <% if WLAN5G_2 == "1" then
        radioNum = radioNum+1
    %>
        opmode[2] = "<%=opmode_5g_2%>";
        wifiTable[1] = "5GHz-1";
        wifiTable[2] = "5GHz-2";
        radioNum = radioNum+1;
    <% end %>
<% end %>
//<%
//    if uci:get("functionlist","functionlist","SUPPORT_WIFI_SCHEDULE_ONLY_AP_MODE") == "1" then
//        if uci:get("wireless","wifi1", "opmode") == "ap" or uci:get("wireless","wifi1", "opmode") == "wds_ap" then
//            hideSch = "0";
//        else
//            hideSch = "1";
//        end
//    end
//%>

function auto_reboot()
{
    var ret = $$('#power_RB_enable').prop('checked');
    if (ret)
    {
        $$('input[name^="auto_reboot_day"]').removeAttr('disabled');
    }
    else
    {
        $$('input[name^="auto_reboot"]').attr('disabled', 'disabled');
        return;
    }

    if ( $$('#sunday').prop('checked') ||  $$('#monday').prop('checked') ||  $$('#tuesday').prop('checked') || 
         $$('#wednesday').prop('checked') ||  $$('#thursday').prop('checked') ||  $$('#friday').prop('checked') || 
         $$('#saturday').prop('checked'))
    {
        $$('input[name^="auto_reboot_hour"]').removeAttr('disabled');
        $$('input[name^="auto_reboot_minute"]').removeAttr('disabled');
    }
    else
    {
        $$('input[name^="auto_reboot_hour"]').attr('disabled', 'disabled');
        $$('input[name^="auto_reboot_minute"]').attr('disabled', 'disabled');
    }
}
var schedule={};
schedule.status=function(){
    var ret = $$('#schedule_enable').prop('checked');
    if (ret)
    {
        $$('input[name^="wifi_schedule"]').removeAttr('disabled');
        $$('select[name^="wifi_schedule"]').removeAttr('disabled');
    }
    else
    {
        $$('input[name^="wifi_schedule"]').attr('disabled', 'disabled');
        $$('select[name^="wifi_schedule"]').attr('disabled', 'disabled');
    }
};
schedule.ssidChange=function(){
    if (SCHEDULEDAY["ssid"+$$("#wifi_schedule_iface").val()])
    {
        schedule.tm.case4();
        RefreshTemplates();
    }
    else
    {
        schedule.tm.case1();
        $$('#wifi_schedule_templates').val("0");
    }
};
schedule.ssidOption = function(){
    XHR.get('', {status:1},
    function(x,info){
        if (x.responseText)
        {
            var ret = ($$('#schedule_enable').prop('checked')) ? "" : " disabled";
            var ht = '<select name="wifi_schedule_iface" id="wifi_schedule_iface"' + ret + '>';
            //var ws = info.wifinets;
            var ap_iface_num = '4';
            var count = 1;
            var opmode = 'ap';
            if (1)
            {
                var show_ap = true;
                if (1 == SCHEDULEDATA.wireless.ScheduleEnable)
                {
                    $$('#schedule_enable').prop("checked", true);
                }
                else
                {
                    $$('#schedule_disable').prop("checked", true);
                }
                //var dev = ws["1"]; // if combined ssid, show all devices's ssid.
                if (1)
                {
                    if (opmode != "ap" || (opmode == "ap" && show_ap))
                    {
                        if (opmode == "ap")
                            show_ap = false ; // ap show once
                        for (var nidx = 0; nidx < 4; nidx++)
                        {
                            //var net = dev.networks[nidx];
                            //var net = dev.networks[nidx];
                            if (0 == nidx)
                            {
                               var ssid = SpecHTML("<% cfg_get_ssid_value("wl_ssid")%>");
                            }
                            else if (1 == nidx)
                            {
                               var ssid = SpecHTML("<% cfg_get_ssid_value("wlg1_ssid")%>");
                            }
                            else if (2 == nidx)
                            {
                               var ssid = SpecHTML("<% cfg_get_ssid_value("wlg2_ssid")%>");
                            }
                            else if (3 == nidx)
                            {
                               var ssid = SpecHTML("<% cfg_get_ssid_value("wlg3_ssid")%>");
                            }
                            //if ((net.nmode == opmode) && net.vlan_id && !net.networkname.match("enjet") && !net.networkname.match("mgmt"))
                            {
                                if ((opmode == "ap" && count <= ap_iface_num) || opmode != "ap")
                                {
                                    ht += "<option value='" + nidx + "'>" + ((opmode == "ap")?"AP":"WDS") + " - " + ssid + "</option>"
                                }
                                if (opmode == "ap")
                                    count++;
                            }
                        }
                    }
                }
            }
            else
            {
                ht += "<option>$wifi_not_found_or_disabled.</option>"
            }
            ht += "</select>";
            getById('wifi_schedule_ssid').innerHTML = ht;
            getById('wifi_schedule_iface').selectedIndex = 0;

            $$('#wifi_schedule_iface option').each(function(){
                if ($$(this).val() == SCHEDULEDATA.wireless.iface)
                    $$('#wifi_schedule_iface').val(SCHEDULEDATA.wireless.iface);
            });
            schedule.ssidChange();
            $$('#wifi_schedule_iface').change(function(){
                schedule.ssidChange();
            });
        }
    });
};

schedule.showDay=function(){
    var ht = "", days, i;
    days = ["$sunday", "$monday", "$tuesday", "$wednesday", "$thursday", "$friday", "$saturday"];

    for (i=0; i<days.length; i++)
    {
        ht+='<tr class="title-option">' +
            '<td>'+days[i]+'</td>' +
            '<td>' +
                '<select name="wifi_schedule_day_sw_'+i+'" id="wifi_schedule_day_sw_'+i+'">' +
                    '<option value="1">$available_lowercase</option><option value="0">$unavailable_lowercase</option>' +
                '</select>' +
            '</td>' +
            '<td>' +
                '<input type="text" style="width:30px;" id="wifi_schedule_day_sh_'+i+'" name="wifi_schedule_day_sh_'+i+'" value="00" maxlength="2" size="2">:' +
                '<input type="text" style="width:30px;" id="wifi_schedule_day_sm_'+i+'" name="wifi_schedule_day_sm_'+i+'" value="00" maxlength="2" size="2">~' +
                '<input type="text" style="width:30px;" id="wifi_schedule_day_eh_'+i+'" name="wifi_schedule_day_eh_'+i+'" value="24" maxlength="2" size="2">:' +
                '<input type="text" style="width:30px;" id="wifi_schedule_day_em_'+i+'" name="wifi_schedule_day_em_'+i+'" value="00" maxlength="2" size="2">' +
            '</td>' +
        '</tr>';
    }
    document.write(ht);
};

schedule.templateInvoke=function(caseId){
    switch(parseInt(caseId))
    {
        case 3: //<%#Available 8-17 daily execpt weekends%>
            schedule.tm.case3();
            break;
        case 2: //<%#Available 8-17 daily%>
            schedule.tm.case2();
            break;
        case 1: //<%#always available%>
            schedule.tm.case1();
            break;
        case 4: //<%#Custom schedule%>
            schedule.tm.case4();
            break;
        default :
        case 0: //<%#choose a template%>
            break;
    }
};

schedule.tm={}
schedule.tm.case1 = function(){
    $$('select[name^="wifi_schedule_day_"]').val(1);
    $$('input[name^="wifi_schedule_day_sh"], input[name^="wifi_schedule_day_em"], input[name^="wifi_schedule_day_sm"]').val("00");
    $$('input[name^="wifi_schedule_day_eh"]').val("24");
};
schedule.tm.case2 = function(){
    $$('select[name^="wifi_schedule_day_"]').val(1);
    $$('input[name^="wifi_schedule_day_em"], input[name^="wifi_schedule_day_sm"]').val("00");
    $$('input[name^="wifi_schedule_day_eh"]').val("17");
    $$('input[name^="wifi_schedule_day_sh"]').val("08");
};
schedule.tm.case3 = function(){
    $$('select[name^="wifi_schedule_day_"]').val(1);
    $$('input[name^="wifi_schedule_day_em"], input[name^="wifi_schedule_day_sm"]').val("00");
    $$('input[name^="wifi_schedule_day_sh"]').val("08");
    $$('input[name^="wifi_schedule_day_eh"]').val("17");
    $$('select[name^="wifi_schedule_day_"]:first').val(0);
    $$('select[name^="wifi_schedule_day_"]:last').val(0);
    $$('input[name^="wifi_schedule_day_sh"]:first, input[name^="wifi_schedule_day_sh"]:last').val("00");
    $$('input[name^="wifi_schedule_day_eh"]:first, input[name^="wifi_schedule_day_eh"]:last').val("24");
};
schedule.tm.case4 = function(){
    var i, sidx, sh, eh, sm, em, sche = SCHEDULEDATA;

    for (i=0; i<=6; i++)
    {
        sidx = "#wifi_schedule_day_sw_"+i;
        sh = "#wifi_schedule_day_sh_"+i;
        eh = "#wifi_schedule_day_eh_"+i;
        sm = "#wifi_schedule_day_sm_"+i;
        em = "#wifi_schedule_day_em_"+i;

        $$(sidx).val(sche[SCHEDULEDAY["ssid"+getById("wifi_schedule_iface").value]["day"+i]].status);
        $$(sh).val(sche[SCHEDULEDAY["ssid"+getById("wifi_schedule_iface").value]["day"+i]].timeStart.split(":")[0]);
        $$(sm).val(sche[SCHEDULEDAY["ssid"+getById("wifi_schedule_iface").value]["day"+i]].timeStart.split(":")[1]);
        $$(eh).val(sche[SCHEDULEDAY["ssid"+getById("wifi_schedule_iface").value]["day"+i]].timeEnd.split(":")[0]);
        $$(em).val(sche[SCHEDULEDAY["ssid"+getById("wifi_schedule_iface").value]["day"+i]].timeEnd.split(":")[1]);
    }
};

function init(){
    var auto = SCHEDULEDATA.reboot;
    var sche = SCHEDULEDATA.wireless;
    var radio_face;
    if (auto)
    {
        document.getElementsByName("power_en")[(auto.status=="1")?0:1].checked = true;
        document.getElementsByName('auto_reboot_hour')[0].value = auto.time.split(":")[0];
        document.getElementsByName('auto_reboot_minute')[0].value = auto.time.split(":")[1];
        if (auto.day)
        {
            var i, days = auto.day.split(",");
            if (days[0] != " ")
            {
                for (i=0; i<days.length; i++)
                {
                    document.getElementsByName('auto_reboot_day')[parseInt(days[i])].checked = true;
                }
            }
        }
    }
    if (sche)
    {
        document.getElementsByName("schedule_en")[(sche.ScheduleEnable=="1")?0:1].checked = true;

        for (var i = 0; i < 3; i++){
            if (opmode[i] == "ap" || opmode[i] == "wds_ap")
            {
                radio_face += '<option value="'+i+'">'+wifiTable[i]+'</option>';
            }
        }

        $$('#wifi_schedule_radio').html(radio_face);

        if (opmode[parseInt(sche.radio, 10)] == "ap" || opmode[parseInt(sche.radio, 10)] == "wds_ap")
        {
            $$('#wifi_schedule_radio').val(sche.radio);
        }

        $$('#wifi_schedule_templates').val(sche.templates);
    }

    auto_reboot();
    schedule.status();
    schedule.ssidOption();

    //Disable WiFi schedule function when project only support 2.4G
    if ((opmode[1] == null) && (opmode[2] == null))
    {
        if (opmode[parseInt(sche.radio, 10)] == "ap" || opmode[parseInt(sche.radio, 10)] == "wds_ap")
        {
            //do nothing
        }
        else
        {
            document.getElementsByName("schedule_en")[0].disabled = true;
            document.getElementsByName("schedule_en")[1].disabled = true;
        }
    }
    //Disable WiFi schedule function when project only support 5G
    else if ((opmode[0] == null) && (opmode[2] == null))
    {
        if (opmode[1] != "ap" && opmode[1]!="wds_ap")
        {
            document.getElementsByName("schedule_en")[0].disabled = true;
            document.getElementsByName("schedule_en")[1].disabled = true;
            $$('input[name^="wifi_schedule"]').attr('disabled', 'disabled');
            $$('select[name^="wifi_schedule"]').attr('disabled', 'disabled');
        }
    }
}
$$(function() {
    init();
});

function isprotecting()
{
    var url = '<% action_url("apply.cgi", "wifi_schedule.htm") %>';
    var data = $$('#wifi_schedule_form').serialize();
    ajax_normal(
    {
        async: false,
        type : "POST",
        url : url,
        data : data,
        dataType: "JSON",
        error:function(){},
        success:function(){}
    });
}

function savechanges(type){
    var ret = false, sh, sm, eh, em;
    var str = "$must_be_zero", str2 = "$invalid_time_range";
    if (!isRange(document.getElementsByName('auto_reboot_hour')[0], "$auto_reboot_hour", 0, 24))
    {
        return false;
    }
    if (!isRange(document.getElementsByName('auto_reboot_minute')[0], "$auto_reboot_minute", 0, 59))
    {
        return false;
    }
    if (parseInt(document.getElementsByName('auto_reboot_hour')[0].value) == 24 && parseInt(document.getElementsByName('auto_reboot_minute')[0].value) != 0)
    {
        alert(String.format(str, "$reboot_minute"));
        setfocus(document.getElementsByName('auto_reboot_minute')[0]);
        return false;
    }

    $$('input[name^="wifi_schedule_day_sh"]').each(function(){
        if (!isClockRange($$(this).val(), "$schedule_table_start_hour", 0, 24))
        {
            setfocus($$(this));
            ret = true;
            return false;
        }
    });
    if (ret) return false;

    $$('input[name^="wifi_schedule_day_sm"]').each(function(){
        if (!isClockRange($$(this).val(), "$schedule_table_start_minute", 0, 60))
        {
            setfocus($$(this));
            ret = true;
            return false;
        }
    });
    if (ret) return false;

    $$('input[name^="wifi_schedule_day_eh"]').each(function(){
        if (!isClockRange($$(this).val(), "$schedule_table_end_hour", 0, 24))
        {
            setfocus($$(this));
            ret = true;
            return false;
        }
    });
    if (ret) return false;

    $$('input[name^="wifi_schedule_day_em"]').each(function(){
        if (!isClockRange($$(this).val(), "$schedule_table_end_minute", 0, 60))
        {
            setfocus($$(this));
            ret = true;
            return false;
        }
    });
    if (ret) return false;

    for (var i=0; i<7; i++)
    {
        sh = document.getElementById('wifi_schedule_day_sh_'+i);
        sm = document.getElementById('wifi_schedule_day_sm_'+i);
        eh = document.getElementById('wifi_schedule_day_eh_'+i);
        em = document.getElementById('wifi_schedule_day_em_'+i);

        if (parseInt(sh.value) == 24 && parseInt(sm.value) != 0)
        {
            alert(String.format(str, "$start_minute"));
            setfocus(sm);
            ret = true;
            break;
        }

        if (parseInt(eh.value) == 24 && parseInt(em.value) != 0)
        {
            alert(String.format(str, "$end_minute"));
            setfocus(em);
            ret = true;
            break;
        }

        if ((parseInt(sh.value) == 0 && parseInt(eh.value) == 24))
        {
            if (parseInt(sh.value) == parseInt(eh.value))
            {
                if (parseInt(sm.value) >= parseInt(em.value))
                {
                    alert(str2);
                    setfocus(sm);
                    ret = true;
                    break;
                }
            }
        }
        else
        {
            if (parseInt(sh.value) > parseInt(eh.value))
            {
                alert(str2);
                setfocus(sh);
                ret = true;
                break;
            }
            else if (parseInt(sh.value) == parseInt(eh.value))
            {
                if (parseInt(sm.value) >= parseInt(em.value))
                {
                    alert(str2);
                    setfocus(sm);
                    ret = true;
                    break;
                }
            }
        }
    }
    if (ret)
        return false;

    type = type || 0;
    RefreshTemplates();
    isprotecting();
    ajax_setCsrf();

    return true;
}

function RefreshTemplates()
{
    var i, ret;
    getById("wifi_schedule_templates").value = "4";//<%#initial template%>
    //<%#CASE 1%>
    for (i=0; i<=6; i++)
    {
        ret = CheckScheduleTable(i, "1", "00", "00", "24", "00");
        if (false == ret)
        {
            break;
        }
    }
    if (true == ret)
    {
        getById("wifi_schedule_templates").value = "1";
        return;
    }

    //<%#CASE 2%>
    for (i=0; i<=6; i++)
    {
        ret = CheckScheduleTable(i, "1", "08", "00", "17", "00");
        if (false == ret)
        {
            break;
        }
    }
    if (true == ret)
    {
        getById("wifi_schedule_templates").value = "2";
        return;
    }

    //<%#CASE 3%>
    for (i=1; i<=5; i++)
    {
        ret = CheckScheduleTable(i, "1", "08", "00", "17", "00");
        if (false == ret)
        {
            break;
        }
    }
    ret &= CheckScheduleTable(0, "0", "00", "00", "24", "00");
    ret &= CheckScheduleTable(6, "0", "00", "00", "24", "00");
    if (true == ret)
    {
        getById("wifi_schedule_templates").value = "3";
        return;
    }
}

function CheckScheduleTable(day, sw, startHour, startMin, endHour, endMin)
{
    if (document.getElementById("wifi_schedule_day_sw_"+day).value != sw)
    {
        return false;
    }
    if (document.getElementById("wifi_schedule_day_sh_"+day).value != startHour)
    {
        return false;
    }
    if (document.getElementById("wifi_schedule_day_sm_"+day).value != startMin)
    {
        return false;
    }
    if (document.getElementById("wifi_schedule_day_eh_"+day).value != endHour)
    {
        return false;
    }
    if (document.getElementById("wifi_schedule_day_em_"+day).value != endMin)
    {
        return false;
    }
    return true;
}

