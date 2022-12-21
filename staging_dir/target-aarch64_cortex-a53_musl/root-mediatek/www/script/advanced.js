//var JSONDATA_LIGHTTPD = <%=JSONDATA_LIGHTTPD%>
var JSONDATA_LIGHTTPD = {"https":{".name":"https",".type":"https","enable":"1","forward":"1",".anonymous":false,".index":0}};

var dropbearEnable;
var emailEnable;
var emailFrom;
var emailTo;
var emailSubject;
var emailUser;
var emailPassword;
var emailSmtpaddr;
var emailSmtpport;
var emailSecurity;
var subject;

function snmp_status(s){
    /* s = 0: general settings
       s = 1: snmp v3 settings
       s = 2: auth v3 settings
       s = 3: private settings */

    var snmp_st = $$('#SnmpEnable_enable').prop('checked');
    var v3_st = $$('#snmp_gen_v3_enable').prop('checked');
    var auth_st = ($$('#snmp_v3_auth_protocol').val() != '2')?1:0;
    var pri_st = ($$('#snmp_v3_auth_private_protocol').val() != '1')?1:0;

    switch (s)
    {
        default:
        case 0:
            if (snmp_st){
                $$('input[name^="snmp_gen_"]').removeAttr('disabled');
                $$('select[name^="snmp_gen_"]').removeAttr('disabled');
                if (v3_st){
                    $$('input[name^="snmp_v3_username"]').removeAttr('disabled');
                    $$('select[name^="snmp_v3_auth_protocol"]').removeAttr('disabled');
                    $$('input[name^="snmp_v3_engine_id"]').removeAttr('disabled');
                    if (auth_st){
                        $$('input[name^="snmp_v3_auth_key"]').removeAttr('disabled');
                        $$('select[name^="snmp_v3_auth_private_protocol"]').removeAttr('disabled');
                        if (pri_st)
                            $$('input[name^="snmp_v3_auth_private_key"]').removeAttr('disabled');
                        else
                            $$('input[name^="snmp_v3_auth_private_key"]').attr('disabled', 'disabled');
                    }
                    else{
                        $$('input[name^="snmp_v3_auth_key"]').attr('disabled', 'disabled');
                        $$('select[name^="snmp_v3_auth_private_protocol"]').attr('disabled', 'disabled');
                        $$('select[name^="snmp_v3_auth_private_protocol"]').val('1');
                        $$('input[name^="snmp_v3_auth_private_key"]').attr('disabled', 'disabled');
                    }
                }
                else{
                    $$('input[name^="snmp_v3"]').attr('disabled', 'disabled');
                    $$('select[name^="snmp_v3"]').attr('disabled', 'disabled');
                }
            }
            else{
                $$('input[name^="snmp_"]').attr('disabled', 'disabled');
                $$('select[name^="snmp_"]').attr('disabled', 'disabled');
            }
            break;
        case 1:
            if (v3_st){
                $$('input[name^="snmp_v3_username"]').removeAttr('disabled');
                $$('select[name^="snmp_v3_auth_protocol"]').removeAttr('disabled');
                $$('input[name^="snmp_v3_engine_id"]').removeAttr('disabled');
                if (auth_st){
                    $$('input[name^="snmp_v3_auth_key"]').removeAttr('disabled');
                    $$('select[name^="snmp_v3_auth_private_protocol"]').removeAttr('disabled');
                    if (pri_st)
                        $$('input[name^="snmp_v3_auth_private_key"]').removeAttr('disabled');
                }
            }
            else{
                $$('input[name^="snmp_v3"]').attr('disabled', 'disabled');
                $$('select[name^="snmp_v3"]').attr('disabled', 'disabled');
            }
            break;
        case 2:
            if (auth_st){
                $$('input[name^="snmp_v3_auth_key"]').removeAttr('disabled');
                $$('select[name^="snmp_v3_auth_private_protocol"]').removeAttr('disabled');
                if (pri_st)
                    $$('input[name^="snmp_v3_auth_private_key"]').removeAttr('disabled');
            }
            else{
                $$('input[name^="snmp_v3_auth_key"]').attr('disabled', 'disabled');
                $$('select[name^="snmp_v3_auth_private_protocol"]').attr('disabled', 'disabled');
                $$('select[name^="snmp_v3_auth_private_protocol"]').val('1');
                $$('input[name^="snmp_v3_auth_private_key"]').attr('disabled', 'disabled');
            }
            break;
        case 3:
            if (pri_st)
                $$('input[name^="snmp_v3_auth_private_key"]').removeAttr('disabled');
            else
                $$('input[name^="snmp_v3_auth_private_key"]').attr('disabled', 'disabled');
            break;
    }
}
/*
function copyto(){

}

function https_status(){
    var ret = $$('#httpsEnable_enable').prop('checked');
    if (ret){
        $$('input[name^="httpsForward"]').removeAttr('disabled');
    }
    else{
        $$('input[name^="httpsForward"]').attr('disabled', 'disabled');
    }
}*/

function email_alert_status(){
    var ret = $$('#email_enable').prop('checked');
    if (ret){
        $$('input[name^="em_"]').removeAttr('disabled');
        $$('select[name^="em_"]').removeAttr('disabled');
    }
    else{
        $$('input[name^="em_"]').attr('disabled', 'disabled');
        $$('select[name^="em_"]').attr('disabled', 'disabled');
    }
}

function defServPort()
{
    var security_mode = parseInt($$('#em_security').val(), 10);
    switch (security_mode)
    {
        case 0:
        default:
            $$('#em_smtp_port').val(25);
            break;
        case 1:
            $$('#em_smtp_port').val(465);
            break;
        case 2:
            $$('#em_smtp_port').val(587);
            break;
    }
}

function changeInputType(field, image)
{
    if ($$('#email_enable').prop('checked')){
        var pw_value = document.getElementById(field).value;
        if (document.getElementById(field).type == 'password') {
            $$("#"+field+"").replaceWith("<input type=text name="+field+" id="+field+" style='height:27px;'>");
            $$("#"+image+"").attr("src", "image/eye.svg");
        } else {
            $$("#"+field+"").replaceWith("<input type=password name="+field+" id="+field+" style='height:27px;'>");
            $$("#"+image+"").attr("src", "image/eye-slash.svg");
        }
        document.getElementById(field).value = pw_value;
    }
}

function init()
{
<%
if uci:get('functionlist','functionlist','SUPPORT_ATKK_FW_VERSION') == '1' then -----#### SUPPORT_ATKK_FW_VERSION START ###
%>
    //document.getElementsByName("ControllerMode")[('<%=uci:get("cwmagent","cwmagent","status")%>'=='1')?0:1].checked=true;
<%
end
%>
<%
if uci:get('functionlist','functionlist','SUPPORT_MANAGEMENT_MODE') == '1' then -----#### SUPPORT_MANAGEMENT_MODE START ###
%>
    //document.getElementsByName("MGModeEnable")[('<%=uci:get("apcontroller","capwap","enable")%>'=='1')?0:1].checked=true;
<%
end
%>
    document.getElementsByName("SnmpEnable")[('<%=uci:get_first("snmpd","system","sysEnable")%>'=="1")?0:1].checked=true;
//<%
//    local sysContact = luci.util.repSpec(tostring(uci:get_first("snmpd","system","sysContact") or ""));
//    local sysLocation = luci.util.repSpec(tostring(uci:get_first("snmpd","system","sysLocation") or ""));
//    local community = luci.util.repSpec(tostring(uci:get_first("snmpd","trap","community") or ""));
//    local userName = luci.util.repSpec(tostring(uci:get_first("snmpd","snmpv3","userName") or ""));
//    local authKey = luci.util.repSpec(tostring(uci:get_first("snmpd","snmpv3","authKey") or ""));
//    local privKey = luci.util.repSpec(tostring(uci:get_first("snmpd","snmpv3","privKey") or ""));
//    local engineID = luci.util.repSpec(tostring(uci:get_first("snmpd","snmpv3","engineID") or ""));
//    local community_public = luci.util.repSpec(tostring(uci:get("snmpd","public","community") or ""));
//    local community_private = luci.util.repSpec(tostring(uci:get("snmpd","private","community") or ""));
//%>
    var sysContact = repSpec("<%=sysContact%>"),sysLocation = repSpec("<%=sysLocation%>"), community = repSpec("<%=community%>"), userName = repSpec("<%=userName%>"), authKey = repSpec("<%=authKey%>"), privKey = repSpec("<%=privKey%>"), engineID = repSpec("<%=engineID%>");
    var community_public = repSpec("<%=community_public%>"), community_private =repSpec("<%=community_private%>");
    $$('#snmp_gen_contact').val(sysContact);
    $$('#snmp_gen_loaction').val(sysLocation);
    $$('#snmp_gen_ro').val(community_public);
    $$('#snmp_gen_rw').val(community_private);

    //var snmp_gen_main_port = '<%=uci:get_first("snmpd","agent","address")%>';
    //$$('#snmp_gen_main_port').val(snmp_gen_main_port.replace(/\w*\:/,""));

    $$('#snmp_gen_port').val('<%=uci:get_first("snmpd","trap","destPort")%>');
    $$('#snmp_gen_ip').val('<%=uci:get_first("snmpd","trap","destIpAddr")%>');
    $$('#snmp_gen_comm').val(community);
    document.getElementsByName("snmp_gen_v3")[('<%=uci:get_first("snmpd","snmpv3","snmpv3Enable")%>'=="1")?0:1].checked=true;
    $$('#snmp_v3_username').val(userName);
    $$('#snmp_v3_auth_protocol').val('<%=uci:get_first("snmpd","snmpv3","authProtocol")%>');
    $$('#snmp_v3_auth_key').val(authKey);
    $$('#snmp_v3_auth_private_protocol').val('<%=uci:get_first("snmpd","snmpv3","privProtocol")%>');
    $$('#snmp_v3_auth_private_key').val(privKey);
    $$('#snmp_v3_engine_id').val(engineID);

//<%
//    local emailEnable = luci.util.repSpec(tostring(uci:get("emailalert","email","enable") or ""))
//    local emailFrom = luci.util.repSpec(tostring(uci:get("emailalert","email","from") or ""))
//    local emailTo = luci.util.repSpec(tostring(uci:get("emailalert","email","alert_to") or ""))
//    local emailSubject = luci.util.repSpec(tostring(uci:get("emailalert","email","subject") or ""))
//    local emailUser = luci.util.repSpec(tostring(uci:get("emailalert","email","user") or ""))
//    local emailPassword = luci.util.repSpec(tostring(uci:get("emailalert","email","password") or ""))
//    local emailSmtpaddr = luci.util.repSpec(tostring(uci:get("emailalert","email","smtpaddr") or ""))
//    local emailSmtpport = luci.util.repSpec(tostring(uci:get("emailalert","email","smtpport") or ""))
//    local emailSecurity = luci.util.repSpec(tostring(uci:get("emailalert","email","security") or ""))
//%>
    emailEnable = "<% cfg_get("email_alert_advanced", "emailEnable") %>";
    emailFrom = "<% cfg_get("email_alert_advanced", "emailFrom") %>";
    emailTo = "<% cfg_get("email_alert_advanced", "emailTo") %>";
    emailSubject = "<% cfg_get("email_alert_advanced", "emailSubject") %>";
    emailUser = "<% cfg_get("email_alert_advanced", "emailUser") %>";
    emailPassword = "<% cfg_get("email_alert_advanced", "emailPassword") %>";
    emailSmtpaddr = "<% cfg_get("email_alert_advanced", "emailSmtpaddr") %>";
    emailSmtpport = "<% cfg_get("email_alert_advanced", "emailSmtpport") %>";
    emailSecurity = "<% cfg_get("email_alert_advanced", "emailSecurity") %>";
    dropbearEnable = "<% cat_file("/tmp/enable_ssh") %>";

    var mac = "<% lan_mac() %>";
    var devicename = '<% cfg_get("wl_deviceName") %>';
    subject = "[$email_alert]["+devicename+"]["+mac+"] $configuration_changed";

    document.getElementsByName("sshEnable")[(dropbearEnable=="on")?0:1].checked=true;
    //document.getElementsByName("httpsEnable")[(JSONDATA_LIGHTTPD.https.enable=="1")?0:1].checked=true;
    //document.getElementsByName("httpsForward")[(JSONDATA_LIGHTTPD.https.forward=="1")?0:1].checked=true;
    document.getElementsByName("email_enable")[0].checked=(emailEnable=="1")?true:false;
    $$('#em_from').val(emailFrom);
    $$('#em_to').val(emailTo);
    if (emailSubject == "")
    {
        $$('#em_subject').val(subject);
    }
    else
    {
        $$('#em_subject').val(emailSubject);
    }
    $$('#em_username').val(emailUser);
    $$('#em_password').val(emailPassword);
    $$('#em_smtp_server').val(emailSmtpaddr);
    if (emailSmtpport == "0" && emailSecurity == "0")
        $$('#em_smtp_port').val(25);
    else
        $$('#em_smtp_port').val(emailSmtpport);
    $$('#em_security').val(emailSecurity);

    snmp_status();
    //tps_status();
    email_alert_status();
}

$$(function() {
    //<% if uci:get('functionlist','functionlist','SUPPORT_MYID') == '1' then %>
    //AddMyid("form", "advanced_idchange");
    //<% end %>

    init();

    //copyto();
    //document.getElementById("httpsPart").style.display = "none";
    //getEtcHost();
    //refresh_controllerSettings();
    //$$('#test_ac_btn').click(TestAddr);
});


function savechanges(type){
    type = type || 0;
    //getById('submitType').value = type;
    //RefreshTemplates();
    var form_emailEnable;
    var form_emailFrom = getById('em_from').value;
    var form_emailTo = getById('em_to').value;
    var form_emailSubject = getById('em_subject').value;
    var form_emailUser = getById('em_username').value;
    var form_emailPassword = getById('em_password').value;
    var form_emailSmtpaddr = getById('em_smtp_server').value;
    var form_emailSmtpport = getById('em_smtp_port').value;
    var form_emailSecurity = getById('em_security').value;
    var form_dropbearEnable;

    if (type != 2)
    {
        if (document.getElementsByName("sshEnable")[0].checked)
	    {
	        form_dropbearEnable = 'on';
	    }
	    else
	    {
	        form_dropbearEnable = 'off';
	    }

        if ($$('#SnmpEnable_enable').prop('checked'))
        {
            // if (hasSpecialChar($$('#snmp_gen_ro').val())){
            //     alert(invalid("$community_name_read_only"));
            //     setfocus(getByName('snmp_gen_ro'));
            //     return false;
            // }
            // if (hasSpecialChar($$('#snmp_gen_rw').val())){
            //     alert(invalid("$community_name_read_write"));
            //     setfocus(getByName('snmp_gen_rw'));
            //     return false;
            // }
            if (!isPattern1($$('#snmp_gen_contact').val())){
                alert("<%=translatef('Contact: %s are invalid characters.','the : and ;')%>");
                return false;
            }
            if (!isPattern1($$('#snmp_gen_loaction').val())){
                alert("<%=translatef('Location: %s are invalid characters.','the : and ;')%>");
                return false;
            }
            if (!isPattern1($$('#snmp_gen_ro').val())){
                alert("<%=translatef('Community Name (read only): %s are invalid characters.','the : and ;')%>");
                return false;
            }
            if (!isPattern1($$('#snmp_gen_rw').val())){
                alert("<%=translatef('Community Name (read write): %s are invalid characters.','the : and ;')%>");
                return false;
            }

            //if (!isNumber($$('#snmp_gen_main_port').val()) || !isBetween($$('#snmp_gen_main_port').val(), 1, 65535)){
            //    alert(invalid("$port")+" $range: [1 - 65535]");
            //    setfocus(getByName('snmp_gen_main_port'));
            //    return false;
            //}

            if (!isNumber($$('#snmp_gen_port').val()) || !isBetween($$('#snmp_gen_port').val(), 1, 65535)){
                alert(invalid("$port")+" $range: [1 - 65535]");
                setfocus(getByName('snmp_gen_port'));
                return false;
            }
            if ($$('input[name="snmp_gen_ip"]').val()!="" && !isIpaddr($$('input[name="snmp_gen_ip"]').val()) && !isDomainName($$('input[name="snmp_gen_ip"]').val())){
                alert(invalid("$trap_ip_address"));
                setfocus(getByName('snmp_gen_ip'));
                return false;
            }
            if (!isPattern1($$('#snmp_gen_comm').val())){
                alert("<%=translatef('Community Name: %s are invalid characters.','the : and ;')%>");
                return false;
            }
            if ($$('#snmp_gen_v3_enable').prop('checked'))
            {
                if (!isBetween($$('#snmp_v3_username').val().length, 1, 31)){
                    alert(invalid("$snmp_username"));
                    setfocus(getByName('snmp_v3_username'));
                    return false;
                }
                if (!isPattern1($$('#snmp_v3_username').val())){
                    alert("<%=translatef('SNMP username: %s are invalid characters.','the : and ;')%>");
                    return false;
                }
                if ($$('#snmp_v3_auth_protocol').val() != '2')
                {

                    if (!isBetween($$('#snmp_v3_auth_key').val().length, 8, 32)){
                        alert(invalid("$snmp_authorized_key"));
                        setfocus(getByName('snmp_v3_auth_key'));
                        return false;
                    }
                    if (!isPattern1($$('#snmp_v3_auth_key').val())){
                        alert("<%=translatef('SNMP authorized key: %s are invalid characters.','the : and ;')%>");
                        return false;
                    }
                    if ($$('#snmp_v3_auth_private_protocol').val() != '1')
                    {
                        if (!isBetween($$('#snmp_v3_auth_private_key').val().length, 8, 32)){
                            alert(invalid("$snmp_private_key"));
                            setfocus(getByName('snmp_v3_auth_private_key'));
                            return false;
                        }
                        if (!isPattern1($$('#snmp_v3_auth_private_key').val())){
                            alert("<%=translatef('SNMP private key: %s are invalid characters.','the : and ;')%>");
                            return false;
                        }
                    }
                }
                if (!isPattern1($$('#snmp_v3_engine_id').val())){
                    alert("<%=translatef('SNMP Engine ID: %s are invalid characters.','the : and ;')%>");
                    return false;
                }
            }
        }

        if (dropbearEnable == form_dropbearEnable)
        {
            document.getElementById("sshEnable_enable").disabled="disabled";
            document.getElementById("sshEnable_disable").disabled="disabled";
        }
    }

    if ($$('#email_enable').prop('checked'))
    {
        if (!isEmail($$('#em_from').val())){
            alert(invalid("$source_mail_address"));
            setfocus(getByName('em_from'));
            return false;
        }
        if (!isEmail($$('#em_to').val())){
            alert(invalid("$destination_mail_address"));
            setfocus(getByName('em_to'));
            return false;
        }
        if (!isHostName($$('#em_smtp_server').val())  && !isIpaddr($$('#em_smtp_server').val())){
            alert(invalid("$smtp_server"));
            setfocus(getByName('em_smtp_server'));
            return false;
        }
        if (!isNumber($$('#em_smtp_port').val()) || !isBetween($$('#em_smtp_port').val(), 1, 65535)){
            alert(invalid("$smtp_server_port")+" $range: [1 - 65535]");
            setfocus(getByName('em_smtp_port'));
            return false;
        }
        /*if ($$('#em_username').val()==""){
            alert("$advanced_note1");
            setfocus(getByName('em_username'));
            return false;
        }
        if ($$('#em_password').val()==""){
            alert("$advanced_note2");
            setfocus(getByName('em_password'));
            return false;
        }*/
    }

    if (document.getElementsByName("email_enable")[0].checked == true)
    {
        if (type == 2)
        {
            getById('emailStatus').value = "2";
            form_emailEnable = "2";
        }
        else
        {
            getById('emailStatus').value = "1";
            form_emailEnable = "1";
        }
    }
    else
    {
        getById('emailStatus').value = "0";
        form_emailEnable = "0";
    }

    if ((emailEnable == form_emailEnable) && (emailFrom == form_emailFrom) && (emailTo == form_emailTo)
        && ((emailSubject == "" && subject == form_emailSubject) || (emailSubject == form_emailSubject))
        && (emailUser == form_emailUser) && (emailPassword == form_emailPassword) && (emailSmtpaddr == form_emailSmtpaddr)
        && ((emailSmtpport == "0" && form_emailSmtpport == "25") || (emailSmtpport == form_emailSmtpport)) && (emailSecurity == form_emailSecurity))
    {
        document.getElementById("emailStatus").disabled="disabled";
    }

    //var snmp_gen_main_port = '<%=uci:get_first("snmpd","agent","address")%>';
    //$$('#snmp_gen_main_port').val(snmp_gen_main_port.replace(/\:\d*/,":"+$$('#snmp_gen_main_port').val()));

    getById('submitType').value = "advanced";
    $$('form').submit();

    //ajax_setCsrf();

    return true;
}

