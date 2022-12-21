var JSONDATA_NTP = <% cfg_get("ntp_daylight_saving") %>;
var j; // # of zone
var ntp_array={
zone:[
    ["UTC12","UTC-12:00 $Kwajalein"],
    ["UTC11","UTC-11:00 $Midway_island_Samoa"],
    ["UTC10","UTC-10:00 $Hawaii"],
    ["NAST9","UTC-09:00 $Alaska"],
    ["PST8","UTC-08:00 $Pacific_time"],
    ["UTC7","UTC-07:00 $Arizona"],
    ["MST7","UTC-07:00 $Mountain_time"],
    ["UTC6","UTC-06:00 $Mexico"],
    ["CST6","UTC-06:00 $Central_time"],
    ["UTC5","UTC-05:00 $Colombia_Panama"],
    ["EST5","UTC-05:00 $Eastern_time"],
    ["UTC4","UTC-04:00 $Bolivia_Venezuela"],
    ["AST4","UTC-04:00 $Atlantic_time"],
    ["BRWST4","UTC-04:00 $Brazil_west"],
    ["NST3:30","UTC-03:30 $Newfoundland"],
    ["WGST3","UTC-03:00 $Greenland"],
    ["BRST3","UTC-03:00 $Brazil_east"],
    ["UTC3","UTC-03:00 $Guyana"],
    ["UTC2","UTC-02:00 $Mid_atlantic"],
    ["STD1","UTC-01:00 $Azores"],
    ["UTC0","UTC+00:00 $Gambia_Liberia_Morocco"],
    ["GMT0","UTC+00:00 $England"],
    ["UTC-1","UTC+01:00 $Tunisia"],
    ["STD-1","UTC+01:00 $France_Germany_Italy"],
    ["UTC-2","UTC+02:00 $South_africa"],
    ["STD-2","UTC+02:00 $Greece_Ukraine_Romania_Turkey"],
    ["UTC-3","UTC+03:00 $Iraq_Jordan_Kuwait"],
    ["EEST-3","UTC+03:00 $Finland"],
    ["UTC-4","UTC+04:00 $Armenia"],
    ["UTC-5","UTC+05:00 $Pakistan_Russia"],
    ["UTC-5:30","UTC+05:30 $Bombay_Calcutta_Madras_New_delhi"],
    ["UTC-6","UTC+06:00 $Bangladesh_Russia"],
    ["UTC-7","UTC+07:00 $Thailand_Russia"],
    ["UTC-8","UTC+08:00 $China_Hong_kong_Western_australia_Singapore_Taiwan_Russia"],
    ["UTC-9","UTC+09:00 $Japan_Korea"],
    ["CST-9:30","UTC+09:30 $South_ustralia"],
    ["UTC-10","UTC+10:00 $Guam_Russia"],
    ["STD-10","UTC+10:00 $Australia"],
    ["UTC-11","UTC+11:00 $Solomon_islands"],
    ["UTC-12","UTC+12:00 $Fiji"],
    ["NZST-12","UTC+12:00 $New_zealand"]]
};

var daylight_array = {
mon:[
    ["1","$january"],
    ["2","$february"],
    ["3","$march"],
    ["4","$april"],
    ["5","$may"],
    ["6","$june"],
    ["7","$july"],
    ["8","$august"],
    ["9","$september"],
    ["10","$october"],
    ["11","$november"],
    ["12","$december"]],
week_idx:[
    ["1","$first"],
    ["2","$second"],
    ["3","$third"],
    ["4","$fourth"],
    ["5","$fifth"]],
week:[
    ["0","$sunday"],
    ["1","$monday"],
    ["2","$tuesday"],
    ["3","$wednesday"],
    ["4","$thursday"],
    ["5","$friday"],
    ["6","$saturday"]],
time:[
    ["0","00:00"],
    ["1","01:00"],
    ["2","02:00"],
    ["3","03:00"],
    ["4","04:00"],
    ["5","05:00"],
    ["6","06:00"],
    ["7","07:00"],
    ["8","08:00"],
    ["9","09:00"],
    ["10","10:00"],
    ["11","11:00"],
    ["12","12:00"],
    ["13","13:00"],
    ["14","14:00"],
    ["15","15:00"],
    ["16","16:00"],
    ["17","17:00"],
    ["18","18:00"],
    ["19","19:00"],
    ["20","20:00"],
    ["21","21:00"],
    ["22","22:00"],
    ["23","23:00"]]
};

function date_time_status()
{
    $$(".cbi-button").attr("disabled", false);
    // $$('.cbi-button').css("color", "#333");
    $$('input[type="submit"]').attr("disabled", false);
    // $$('input[type="submit"]').css("color", "#333");

    var ret = $$('#ntpserverEnable_enable').prop('checked');
    if (ret){
        $$('input[name^="man_"]').attr('disabled', 'disabled');
        $$('input[name^="ntp_server"]').removeAttr('disabled');
    }
    else{
        $$('input[name^="ntp_server"]').attr('disabled', 'disabled');
        $$('input[name^="man_"]').removeAttr('disabled');
    }
}

function daylight_status()
{
    var ret = $$('#daylight_enable').prop('checked');
    if (ret){
        $$('select[name^="day_"]').removeAttr('disabled');
    }
    else{
        $$('select[name^="day_"]').attr('disabled', 'disabled');
    }
}

function init()
{
    var zone_i = "<% cfg_get("ntp_hidden_select") %>";
    var enable_server = "<% cfg_get("ntp_server_enable") %>";
    document.getElementsByName("ntpserverEnable")[(enable_server=="1")?1:0].checked = true;
    $$('#time_zone').val(zone_i);
    document.getElementsByName("daylight_enable")[0].checked = (JSONDATA_NTP.daylightsaving.DayLightEnable=="1")?true:false;
    $$('#day_s_mon').val(JSONDATA_NTP.daylightsaving.startMonth);
    $$('#day_s_week_idx').val(JSONDATA_NTP.daylightsaving.startWeek);
    $$('#day_s_week').val(JSONDATA_NTP.daylightsaving.startDay);
    $$('#day_s_time').val(JSONDATA_NTP.daylightsaving.startHour);
    $$('#day_e_mon').val(JSONDATA_NTP.daylightsaving.endMonth);
    $$('#day_e_week_idx').val(JSONDATA_NTP.daylightsaving.endWeek);
    $$('#day_e_week').val(JSONDATA_NTP.daylightsaving.endDay);
    $$('#day_e_time').val(JSONDATA_NTP.daylightsaving.endHour);
    date_time_status();
    daylight_status();
}

$$(function() {
    init();
});

function isBigMonth(month)
{
    if (month==1 || month==3 || month==5 || month==7 || month==8 || month==9 || month==10 || month==12)
        return true;
    else
        return false;
}

function isLeapYear(year)
{
    if (((year%4==0) && (year%100!=0)) || (year%400==0))
        return true;
    else
        return false;
}

function isprotecting()
{
    $$('form').submit(function() {
        $$("input[name='submitType']").val("ntp_debug");
    });
}

function savechanges(type){
    if (document.getElementsByName("ntpserverEnable")[0].checked == true){
        var setTime;
        if (2 == type) //sync with PC
        {
            var date = new Date();
            var pcYear = date.getFullYear();
            var pcMonth = date.getMonth() + 1;
            var pcDate = date.getDate();
            var pcHours = date.getHours();
            var pcMinutes = date.getMinutes();
            pcMonth = (pcMonth.toString().length==1?"0":"")+pcMonth;
            pcDate = (pcDate.toString().length==1?"0":"")+pcDate;
            pcHours = (pcHours.toString().length==1?"0":"")+pcHours;
            pcMinutes = (pcMinutes.toString().length==1?"0":"")+pcMinutes;
            $$('#man_year').val(pcYear)
            $$('#man_mon').val(pcMonth)
            $$('#man_day').val(pcDate)
            $$('#man_hour').val(pcHours)
            $$('#man_min').val(pcMinutes)
            setTime = pcYear+"-"+pcMonth+"-"+pcDate+" "+pcHours+":"+pcMinutes;
        }
        else
        {
            var mo = $$('#man_mon').val();
            var d = $$('#man_day').val();
            var h = $$('#man_hour').val();
            var mi = $$('#man_min').val();
            var year = $$('#man_year').val();
            mo = (mo.toString().length==1?"0":"")+mo;
            d = (d.toString().length==1?"0":"")+d;
            h = (h.toString().length==1?"0":"")+h;
            mi = (mi.toString().length==1?"0":"")+mi;

            if (!isNumber(mo) || !isBetween(mo, 1, 12)){
                alert(invalid("$month"));
                setfocus(getByName('man_mon'));
                return false;
            }
            if (!isBigMonth(mo))
            {
                if (!isBetween(d, 1, 30))
                {
                    alert(invalid("$day"));
                    setfocus(getByName('man_day'));
                    return false;
                }
            }
            if (2 == mo)
            {
                if (isLeapYear(year))
                {
                    if (!isBetween(d, 1, 29))
                    {
                        alert(invalid("$day"));
                        setfocus(getByName('man_day'));
                        return false;
                    }
                }
                else
                {
                    if (!isBetween(d, 1, 28))
                    {
                        alert(invalid("$day"));
                        setfocus(getByName('man_day'));
                        return false;
                    }
                }
            }
            if (!isNumber(d) || !isBetween(d, 1, 31)){
                alert(invalid("$day"));
                setfocus(getByName('man_day'));
                return false;
            }
            if (!isNumber(h) || !isBetween(h, 0, 23)){
                alert(invalid("$hour"));
                setfocus(getByName('man_hour'));
                return false;
            }
            if (!isNumber(mi) || !isBetween(mi, 0, 59)){
                alert(invalid("$minute"));
                setfocus(getByName('man_min'));
                return false;
            }
            if (!isNumber(year)){
                alert(invalid("$year"));
                setfocus(getByName('man_year'));
                return false;
            }
            setTime = $$('#man_year').val().toString()+"-"+mo+"-"+d+" "+h+":"+mi;
        }
        getById('setTime').value = setTime;
    }
    else
    {
        var ntp_srv = $$('#ntp_server').val();
        if (!isHostName(ntp_srv) && !isIpaddr(ntp_srv)){
            alert(invalid("$ntp_server"));
            setfocus(getByName('ntp_server'));
            return false;
        }
        if (isLoopback(ntp_srv) || isMulticast(ntp_srv))
        {
            alert(invalid("$ntp_server"));
            setfocus(getByName('ntp_server'));
            return false;
        }
    }
    var tmp = ntp_array.zone[$$('#time_zone').val()][1].split(':');
    getById('timeZone').value = ntp_array.zone[$$('#time_zone').val()][0];
    getById('zoneName').value = tmp[1].substr(3);
    type = type || 0;
    if (true == document.getElementsByName("daylight_enable")[0].checked)
    {
        getById('daylightStatus').value = "1";
    }
    else
    {
        getById('daylightStatus').value = "0";
    }
    //ajax_setCsrf();
    isprotecting();
    //$$('form').submit();

    return true;
}

