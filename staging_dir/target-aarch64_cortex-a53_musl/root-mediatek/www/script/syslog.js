var stxhr = new XHR();
var lan_ip, lan_mask;

var logs_getLanIpInfo_csrftoken='<% generateToken("logs_getLanIpInfo") %>';
var logs_getSystemLog_csrftoken='<% generateToken("logs_getSystemLog") %>';
var logs_clearSyslog_csrftoken='<% generateToken("logs_clearSyslog") %>';
var logs_setCfg_csrftoken='<% generateToken("logs_setCfg") %>';
var logs_getCfg_csrftoken='<% generateToken("logs_getCfg") %>';

$$(function() {
    var getLanIpInfoData = null;
    getLanIpInfoData = {anticsrf:logs_getLanIpInfo_csrftoken, submitType:'logs_getLanIpInfo'};
    ajax_normal({
    async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "syslog.htm") %>',
        data:getLanIpInfoData,
        dataType:"json",
        error:function(){
        console.log("do diag syslog error");
        },
        success:function(result){
            if (result)
            {
                lan_ip = result['lanIp'];
                lan_mask = result['lanIpMask'];
            }
        }
    });
});

function syslog_status()
{
    var ret = $$('#syslogEnable_enable').prop('checked');
    if (ret){
        $$('input[name^="log_"]').removeAttr('disabled');
        $$('select[name^="log_"]').removeAttr('disabled');
        $$('#log_result').removeAttr('disabled');
    }
    else{
        $$('input[name^="log_"]').attr('disabled', 'disabled');
        $$('select[name^="log_"]').attr('disabled', 'disabled');
        $$('#log_result').attr('disabled', 'disabled');
    }
}

function remote_log_status()
{
    var ret = $$('#remoteLogEnable_enable').prop('checked');
    if (ret){
        $$('input[name^="remote_"]').removeAttr('disabled');
    }
    else{
        $$('input[name^="remote_"]').attr('disabled', 'disabled');
    }
}

function getSystemLogByType(type)
{
    var getSystemLogData = null;
    getSystemLogData = {anticsrf:logs_getSystemLog_csrftoken, submitType:'logs_getSystemLog', "type":type};
    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "syslog.htm") %>',
        data: getSystemLogData,
        //dataType: "json",
        error:function(){
            console.log("get log error");
        },
        success:function(result){
            $$('#log_result').val(result);
        }
    });
}

function logTypeChange(type)
{
    var setLogTypeData = null;
    setLogTypeData = {anticsrf:logs_setCfg_csrftoken, submitType:'logs_setCfg', "type":type};
    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "syslog.htm") %>',
        data: setLogTypeData,
        //dataType: "json",
        error:function(){
            console.log("get log error");
        },
        success:function(result){
        }
    });
	
	getSystemLogByType(type);
}

function clearSysLog()
{
    var clearSyslogData = null;
    clearSyslogData = {anticsrf:logs_clearSyslog_csrftoken, submitType:'logs_clearSyslog'};
    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "syslog.htm") %>',
        data: clearSyslogData,
        //dataType: "json",
        error:function(){
            console.log("clear log error");
        },
        success:function(result){
            $$('#log_result').val(result);
        }
    });
}

function downloadSysLog()
{
    $$('<form action=\'<% action_url("apply.cgi", "syslog.htm") %>\' method="post">'+
            '<input type="hidden" name="submitType" value="logs_downloadSyslog"/>'+
            '<input type="hidden" name="anticsrf" value=\'<% generateToken("logs_downloadSyslog") %>\'>'+
            '<input type="hidden" name="type" value="'+$$('#log_type').val()+'"/>'+
        '</form>')
        .appendTo('body').submit().remove();
}

function saveCfg(){
    var setCfgData = null;
    var logEnable = $$('#syslogEnable_enable').prop('checked');
    var remoteEnable = $$('#remoteLogEnable_enable').prop('checked');
    var trafficEnable = $$('#remote_trafficLogEnable_enable').prop('checked');
    var remoteLogEnable = $$('#remoteLogEnable_enable').prop('checked');

    if (remoteLogEnable)
    {
        if (!isIpaddr(getByName('remote_ip').value))
        {
            alert("$invalid_log_server_ip");
            setfocus(getByName('remote_ip'));
            return false;
        }
    }
    if ((getByName('remote_ip').value==lan_ip) || 
        isMulticast(getByName('remote_ip').value) || 
        isLinklocal(getByName('remote_ip').value) ||
        isSameSubnet("127.0.0.1", "255.0.0.0", getByName('remote_ip').value))
    {
        alert("$invalid_log_server_ip");
        setfocus(getByName('remote_ip'));
        return false;
    }
    if (!isNumber($$('#remote_port').val()) || !isBetween($$('#remote_port').val(), 1, 65535))
    {
        alert("$invalid_port_value");
        setfocus(getByName('remote_port'));
        return false;
    }
    setCfgData = {anticsrf:logs_setCfg_csrftoken, submitType:'logs_setCfg', "enable":logEnable ? 1 : 0, "remoteEnable":remoteEnable ? 1: 0, "trafficEnable":trafficEnable ? 1 : 0, "remoteIp":$$('#remote_ip').val(), "remotePort":$$('#remote_port').val()};

    ajax_normal({
        async: false,
        type : "POST",
        url: '<% action_url("apply.cgi", "syslog.htm") %>',
        data: setCfgData,
        //dataType: "json",
        error:function(){
            console.log("set cfg error");
        },
        success:function(result){
            location.reload();
        }
    });

    return true;
}

function handle_log_type(bitMast){
    if ('' == bitMast){
        return;
    }
    for (var i=0,j=bitMast.length; i<bitMast.length; i++,j--){
        if ("0" == bitMast[i]){
            $$('#log_type').find('option[value='+j+']').hide();
        }
    }
}

function insight_display()
{
    $$('#apply').css("color", "white");
}


function updateAllLogCfg()
{
	var logData;
	logData = {anticsrf:logs_getCfg_csrftoken, submitType:'logs_getCfg'};
	ajax_normal({
			async: false,
			type : "POST",
			url: '<% action_url("apply.cgi", "syslog.htm") %>',
			data:logData,
			dataType:"json",
			error:function(){
				console.log("get log cfg error");
			},
			success:function(result){
				if (result)
				{
					if ("1" == result['logEnable'])
					{
						$$("#syslogEnable_enable").attr("checked", "checked");
						$$("#syslogEnable_disable").removeAttr("checked");
					}
					else
					{
						$$('#syslogEnable_disable').attr("checked", "checked");
						$$('#syslogEnable_enable').removeAttr("checked");
					}
					
					if ("1" == result['remoteEnable'])
					{
						$$('#remoteLogEnable_enable').attr("checked", "checked");
						$$('#remoteLogEnable_disable').removeAttr("checked");
					}
					else
					{
						$$('#remoteLogEnable_disable').attr("checked", "checked");
						$$('#remoteLogEnable_enable').removeAttr("checked");
					}
					
					if ("1" == result['trafficEnable'])
					{
						$$('#remote_trafficLogEnable_enable').attr("checked", "checked");
						$$('#remote_trafficLogEnable_disable').removeAttr("checked");
					}
					else
					{
						$$('#remote_trafficLogEnable_disable').attr("checked", "checked");
						$$('#remote_trafficLogEnable_enable').removeAttr("checked");
					}
					
					$$('#log_type').val(result['logType']);
					$$('#remote_ip').val(result['remoteIp']);
					$$('#remote_port').val(result['remotePort']);
				}
			}
		});
	
}

function forminit()
{
	updateAllLogCfg();
    syslog_status();
    remote_log_status();
    //handle_log_type('<%=uci:get_first("functionlist","vendorlist","SYSLOG_TYPE_MASK")%>');
    insight_display();
	getSystemLogByType($$('#log_type').val());
}

$$(function() {
    forminit();
});
