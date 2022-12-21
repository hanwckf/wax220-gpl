var guiTraversalPort = "0";
var camGuiTraversalPort = "8080";
var camLiveViewInfo = "";
var lanip = "192.168.18.200";
var clientip = '192.168.18.200';
var secondsInterval;
var lang;

function doCookieSetup(name, value, days)
{
    if (days)
    {
        var date = new Date();
        date.setTime(date.getTime()+(days*24*60*60*1000));
        var expires = "; expires="+date.toGMTString();
    }
    else
    {
        var expires = "";
    }
    document.cookie = name+"="+value+expires+"; path=/";
}

function eraseCookie(name)
{
    doCookieSetup(name,"",-1);
}

eraseCookie("is_login");
eraseCookie("serialize");

//if (guiTraversalPort!=0 && guiTraversalPort==window.document.location.port)
    if (lanip != clientip)
    {
        camGuiTraversalPort = "";
        camLiveViewInfo = "?onboard_rtsp=&onboard_rtmp=&onboard_gui=";
    }
    else
    {
        camLiveViewInfo = "?onboard_rtsp=&onboard_rtmp=1935";
    }

function ajax_getCsrf(){
    var url, container, data;
    url = '/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/ajax_getCsrf';
    //container = "#cbi_set";
    $$.ajax({
        async: false,
        type: "GET",
        url:url,
        data:data,
        dataType:"json",
        error:function(){
            //ajax_getChannelList(countryCode);
        },
        success:function(result){
        }
    });
}

function ajax_setCsrf(){
    var url , container ,data;
    url = '/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/ajax_setCsrf';
    //container = "#cbi_set";
    $$.ajax({
        async: false,
        type : "GET",
        url:url,
        data:data,
        dataType:"json",
        error:function(){
            // ajax_getChannelList(countryCode);
        },
        success:function(result){
        }
    });
}

function invalid(str){
    var invalidStr = "$invalud_value";
    return String.format("%s %s!", invalidStr, str);
}

function isRange(target, name, min, max){
    var ret = false;
    var invalidStr = "$invalud_value";
    var str1 = "$between_value";
    var str2 = "$decimal_number";
    if (isNumber(target.value))
    {
        if (isBetween(target.value, min, max))
        {
            ret = true;
        }
        else
        {
            alert(String.format("%s %s! %s %s-%s.", invalidStr, name, str1, min, max));
        }
    }
    else
    {
        alert(String.format("%s %s! %s", invalidStr, name, str2));
    }
    if (!ret)
    {
        setfocus(target);
    }
    return ret;
}

function isClockRange(val, name, min, max){
    var invalidStr = "$invalud_value";
    var str1 = "$decimal_number";
    var str2 = "$between_value";
    if (!isNumber(val))
    {
        alert(String.format("%s %s! %s", invalidStr, name, str1));
        return false;
    }
    if (!isBetween(val, min, max))
    {
        alert(String.format("%s %s! %s %s-%s.", invalidStr, name, str2, min, max));
        return false;
    }
    return true;
}

function showEncryption(e)
{
    var encryption = {"none":"None", "wep-shared":"WEP Shared", "wep-open":"WEP Open", "psk+tkip":"WPA/PSK TKIP", "psk+ccmp":"WPA/PSK AES", "psk+tkip+ccmp":"WPA/PSK TKIP+AES", "psk2+tkip":"WPA2/PSK TKIP", "psk2+ccmp":"WPA2-Personal", "psk2+tkip+ccmp":"WPA2/PSK TKIP+AES", "psk-mixed+tkip+ccmp":"WPA/WPA2-PSK TKIP+AES", "psk-mixed+tkip":"WPA/WPA2-PSK TKIP", "psk-mixed+ccmp":"WPA/WPA2-PSK AES", "wpa+tkip+ccmp":"WPA TKIP+AES", "wpa+tkip":"WPA TKIP", "wpa+ccmp":"WPA AES", "wpa2+tkip+ccmp":"WPA2 TKIP+AES", "wpa2+tkip":"WPA2 TKIP", "wpa2+ccmp":"WPA2-Enterprise", "wpa-mixed+tkip+ccmp":"WPA/WPA2 TKIP+AES", "wpa-mixed+tkip":"WPA/WPA2 TKIP", "wpa-mixed+ccmp":"WPA/WPA2 AES", "wpa":"WPA", "wpa2":"WPA2-Enterprise", "owe":"OWE", "sae+ccmp":"WPA3-Personal", "sae-mixed+ccmp":"Mixed-Personal", "wpa3-mixed+ccmp":"Mixed-Enterprise", "wpa3":"WPA3-Enterprise"};
    return (encryption.hasOwnProperty(e))?encryption[e]:e;
}

function logout(){
    if (confirm("Are you sure you want to logout?"))
    {
        // location.href = "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/logout";
        location.href = "/unauth.cgi";
    }
}

function unSaveChanges(){
    location.href='/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/uci/changes';
}

function reboot(){
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/reboot";
}

function reset(){
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/flashops?action=reset";
}

function live()
{
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Live";
}

function wizard()
{
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/network/wizard_init";
}

function config()
{
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/status/overview";
}

function home()
{
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/status/home_info";
}

function mesh_link()
{
    location.href="/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/network/mesh_tools";
}

$$(function() {
    if (window.PIE) {
        $$('#menu_div').each(function() {
            PIE.attach(this);
        });
        $$('.PIE').each(function() {
            PIE.attach(this);
        });
    }
    "1" == "1" ? $$('#languagebar2').show() : $$('#languagebar2').hide();
});

function changeMenu(value)
{
    if (0 == value)
    {
        getById("ap_menu").style.display = "";
        getById("camera_menu").style.display = "none";
        //$$("#ap_menu_div").removeAttr('style').attr("class","blue_menu");
        //$$("#camera_menu_div").removeAttr('style').attr("class","white_menu");
        $$("#ap_menu_div").css({"background-color":"#1b489c","color":"#ffffff"});
        $$("#camera_menu_div").css({"background-color":"#ffffff","color":"#000000"});
    }
    else
    {
        getById("ap_menu").style.display = "none";
        getById("camera_menu").style.display = "";
        //$$("#ap_menu_div").removeAttr('style').attr("class","white_menu");
        //$$("#camera_menu_div").removeAttr('style').attr("class","blue_menu");
        $$("#ap_menu_div").css({"background-color":"#ffffff","color":"#000000"});
        $$("#camera_menu_div").css({"background-color":"#1b489c","color":"#ffffff"});
    }
}
function showMenu(){
    $$("#change_password_tbl").find("input").attr("disabled", "disabled");
    var bg,i,menuHtml="",m=[
        {str: "$overview", pic: "image/icon_info.png", url: ""},
        {str: "$device_status", pic: "", url: "index.htm", myid: "Device_Status"},
        {str: "$connections", pic: "", url: "wireless_connections.htm", myid: "Connections"},
        {str: "$realtime", pic: "", url: "load.htm", myid: "Realtime"},
        {str: "$network", pic: "image/icon_network.png", url: "", myid: ""},
        {str: "$basic", pic: "", url: "basic.htm", myid: "Basic"},
        {str: "$wireless", pic: "", url: "wifi_Setting.htm", myid: "Wireless"},
        {str: "$management", pic: "image/icon_manage.png", url: "", myid: ""},
        {str: "$advanced", pic: "", url: "advanced.htm", myid: "Advanced"},
        {str: "$time_zone", pic: "", url: "time_zone.htm", myid: "Time Zone"},
        {str: "$wifi_scheduler", pic: "", url: "wifi_schedule.htm", myid: "WiFi Scheduler"},
        {str: "$tools", pic: "", url: "diagnostics.htm", myid: "Tools"},
        {str: "$system_manager", pic: "image/icon_admin.png", url: "", myid: ""},
        {str: "$account", pic: "", url: "account.htm", myid: "Account"},
        {str: "$firmware", pic: "", url: "flashops.htm", myid: "Firmware"},
        {str: "$log", pic: "", url: "syslog.htm", myid: "Log"},
    ];
    for (i=0; i<m.length; i++)
    {
        if (m[i].pic != "")
        {
            menuHtml+='<table class="menu"><tr><td style="width:15%;vertical-align:middle;padding: 6px 0;"><img src="'+m[i].pic+'" alt=""/></td><td style="padding: 6px 0;"><p class="menu">'+m[i].str+'</p></td></tr></table>';
        }
        else
        {
            // for flashops
            //bg = ('/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/flashops/'.split(m[i].url).length > 1)?"style=' background-color: #9FDCFF;'":"";
            bg = ('/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/flashops/'.split(m[i].url).length > 1)?"style=''":"";
            if (bg != "")
            {
                menuHtml+='<p class="dropdown-menu-sel"'+bg+'><a href="'+m[i].url+'" myid="'+m[i].myid+'">'+m[i].str+'</a></p>';
            }
            else
            {
                menuHtml+='<p class="dropdown-menu"'+bg+'><a href="'+m[i].url+'" myid="'+m[i].myid+'">'+m[i].str+'</a></p>';
            }
        }
    }
    menuHtml+='<p style="height:20px;"></p>';
    dw(menuHtml);
}

function showMenu2(){
    var bg, i, menuHtml = "", m = [
        //OverView
        
        {str: "OverView",pic: "image/icon_info.png",url: ""},
        {str: "Camera Status",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Stainfo_video",myid: ""},
        //Media
        {str: "Media",pic: "image/icon_media_on.png",url: ""},
        {str: "Video",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Video",myid: ""},
        {str: "Camera",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Camera",myid: ""},
        {str: "Advanced",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Advanced",myid: ""},
        {str: "Privacy Mask",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Privacy_Mask",myid: ""},
        {str: "Audio",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Audio",myid: ""},
        
        //Event Management
        {str: "Event Management",pic: "image/icon_event_on.png",url: ""},
        {str: "Event Control",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Profile",myid: ""},
        {str: "Motion Detection",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Motion",myid: ""},
        {str: "Audio Detection",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Detect_Audio",myid: ""},
        {str: "Tampering Detection",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Tampering",myid: ""},
        {str: "Event Action",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Action",myid: ""},
        //{str: "Time-Lapse",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Time-Lapse",myid: ""},
        //Event Server
        {str: "Event Server",pic: "image/icon_storage_on.png",url: ""},
        {str: "Network Storage",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Netstorage",myid: ""},
        {str: "FTP",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/FTP",myid: ""},
        {str: "E-mail",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/E-mail",myid: ""},
        //Storage Info
        {str: "Storage Info",pic: "image/icon_SDcard_on.png",url: ""},
        {str: "Storage Info",pic: "",url: "/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/ipcam/Storage",myid: ""}
    ];
    for (i=0; i<m.length; i++)
    {
        if (m[i].pic != "")
        {
            menuHtml+='<table class="menu"><tr><td style="width:15%;vertical-align:middle;padding: 6px 0;"><img src="'+m[i].pic+'" alt=""/></td><td style="padding: 6px 0;"><p class="menu">'+m[i].str+'</p></td></tr></table>';
        }
        else
        {
            bg = ('/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/flashops/'.split(m[i].url).length > 1)?"style=' background-color: #9FDCFF;'":"";
            menuHtml+='<p class="dropdown-menu"'+bg+'><a href="'+m[i].url+'" myid="'+m[i].myid+'">'+m[i].str+'</a></p>';
        }
    }
    menuHtml+='<p style="height:20px;"></p>';
    dw(menuHtml);
}

function languageSelectionHandle(lang){
    var language_selection = "<% cfg_get("Language_Selection") %>";
    if ("English" == language_selection)
    {
        document.getElementById("language_select")[0].selected = true;
    }
    else if ("German" == language_selection)
    {
        document.getElementById("language_select")[1].selected = true;
    }
    else if ("Spanish" == language_selection)
    {
        document.getElementById("language_select")[2].selected = true;
    }
    else if ("French" == language_selection)
    {
        document.getElementById("language_select")[3].selected = true;
    }
    if (secondsInterval)
    {
        clearInterval(secondsInterval);
    }

    secondsInterval = setInterval("languageSelectionHandle()", 1000);
}

$$(document).ready(function(){
    ajax_getCsrf();
    var language = 0;
    if ('' != null)
        language = 'auto'
    $$('#language_select').val(language);
    $$('#language_select').change(function(){
        lang = $$('#language_select').find('option:selected').val();
        var url = 'apply.cgi';
        var data = {submitType:"change_language", selectLanguage:lang};
        $$.ajax(
        {
            async: false,
            type : "POST",
            url  : url,
            data : data,
            dataType : "JSON",
            error : function(){location.href = "/index.htm";},
            success : function(){location.href = "/index.htm";}
        });
    });

    getById("language_select").style.display = "";
    //window.location.reload();
    languageSelectionHandle(lang);
});

//--------- checkrule for account and password----------------------
//<![CDATA[
/**
 * \brief    test the validity of the usre name.
 * \param    usr_name    The name string.
 * \param    min            The minimum length of the name.
 * \param    max            The maximum length of the name.
 * \return    Return 0 if OK.
 */
var CHECK_PASS=0
var CHECK_FAILED=1
function validateUsr(usr_name, min, max)
{
    if ("" == usr_name)
    {
        alert("Please enter the username!");
        return CHECK_FAILED;
    }
    else if (min > usr_name.length || max < usr_name.length)
    {
        alert(String.format("Name: length must between %d and %d!", min, max));
        return CHECK_FAILED;
    }
    else if (isChinese(usr_name))
    {
        alert(String.format("Chinese are invalid characters. Please input a new one."));
        return CHECK_FAILED;
    }

    var ReservedChars = /^[^#\`\'\":\\\/\[\]& ]+$$/;
    if (!ReservedChars.test(usr_name) || isFullwidth(usr_name))
    {
        alert(' # ` \' " : \\ / [ ] & (Space) are invalid characters. Please input a new one.');
        return CHECK_FAILED;
    }

    return CHECK_PASS;
}

/**
 * \brief    test the validity of the password.
 * \param    pw        The password string.
 * \return    Return 0 if OK.
 */
function validatePW(pw)
{
    // var ReservedChars = /^[^#\'\":\\\/\[& ]+$$/;
    // var ReservedChars = /^[^:#\'\";\\\/\[& $$\(\)]+$$/;
    if ("" == pw)
    {
        alert("Please enter the new password!");
        return CHECK_FAILED;
    }
    else if (isChinese(pw))
    {
        alert(String.format("Chinese are invalid characters. Please input a new one."));
        return CHECK_FAILED;
    }

    var ReservedChars = /^[^#\`\'\":\\\/\[\]& ]+$$/;
    if (!ReservedChars.test(pw) || isFullwidth(pw))
    {
        alert(' # ` \' " : \\ / [ ] & (Space) are invalid characters. Please input a new one.');
        return CHECK_FAILED;
    }

    // For some special characters, we use mt5sum to replace nixio.crypt
    // else if (!ReservedChars.test(pw))
    // {
    //     alert(": , # , \' , \" , ; , \\ , / , [ , & , $$ , ( , ) ,(Space)  are invalid characters. Please input a new one.");
    //     iRet = 1;
    // }
    return CHECK_PASS;
}

/**
 * \brief    test the validity of the password.
 * \param    pw        The password string.
 * \return    Return 0 if OK.
 */
function validatePW2(pw)
{
    var iRet = 0;

    if (pw.length < 8 || pw.length > 32)
    {
        messageInfo();
        iRet = 1;
    }

    if (0 == iRet)
    {
        /*
        ******Force has one special character !@#$$%^&*()
        if (!hasNumber(pw) || !hasCapital(pw) || !hasLowercase(pw) || !hasValidSpecialChar(pw)|| !hasSpecialChar2(pw))
        */
        /*
        ******Option has one special character !@#$$%^&*()
        */
        if (!hasNumber(pw) || !hasCapital(pw) || !hasLowercase(pw) || !hasValidSpecialChar(pw))
        {
            messageInfo();
            iRet = 1;
        }
    }

    return iRet;
}

/**
 * \brief    Administrator account is not permitted.
 * \param    usr        The user name string.
 * \return   Return 0 if OK.
 */
function checkUserName(usr)
{
    if ( usr == "root" || usr == "nobody" || usr == "daemon"
        || usr == "ftp" || usr == "network"){
        alert("This user name is invalid. Please input a new one.");
        return CHECK_FAILED;
    }
    return CHECK_PASS;
}

/**
 * \brief    check the new password.
 * \param    pw1            The password string.
 * \param    pw2            The password string.
 * \param    szRet        The error message.
 * \return    Return 0 if OK.
 */
function checkPW1PW2(pw1, pw2, szRet)
{
    if ("" == szRet)
    {
        if (pw2 != pw1)
        {
            alert("Given password confirmation did not match, password not changed!");
            return CHECK_FAILED;
        }
    }
    else
    {
        if (pw2 == pw1)
        {
            alert("New password cannot be the same as the old password.");
            return CHECK_FAILED;
        }
    }
    return CHECK_PASS;
}
//--------- checkrule for account and password end----------------------

function change_webpasswd(){
    $$("#change_password_tbl").find("input").removeAttr('disabled');
    $$('input:enabled[name$$=".key"]').val('');
    $$('#change_password_window').show();
}

function checkpwd(){
    var szRet = "";
    var user_account = document.getElementById("user_account").value;
    var user_password = document.getElementsByName("user_password")[0].value;
    var user_password_confirm = document.getElementsByName("user_password_confirm")[0].value;

    if ((checkUserName(user_account)) ||
        (validateUsr(user_account, 1, 12)) ||
        (validatePW(user_password)) ||
        (checkPW1PW2(user_password, user_password_confirm, szRet)))
    {
        return false;
    }

    ajax_setCsrf();
    document.change_password_form.submit();
}

function messageInfo()
{
    var msg="Password must be 8-32 characters in length, with at least one uppercase letter, one lowercase letter, and one number. Allowed symbols are "+'!@#$$%^&()*';
    alert(msg);
}

function pop_out_window(option){
    if (1 == option){
        $$('#change_password_window').hide();
        $$('#warning_window').show();
    }
    else if (2 == option){
        $$('#warning_window').hide();
        $$('#change_password_window').show();
    }
}

function copyto2()
{
    setTimeout("insight_msg()", 1000);
}

function insight_msg()
{

}

$$(function() {
    var url = '/cgi-bin/luci/;stok=bdb0eecd3b2bdd526e00347edcce5d06/admin/system/flashops';

    if (url.indexOf('wireless_device') != -1)  // In Wirelss page
    {
        $$(".cbi-button-save").attr("disabled", false);
        $$('.cbi-button-save').css("color", "white");
    }
    else if (url.indexOf('system/system') != -1)  // In Time Zone page
    {
        $$(".cbi-button").attr("disabled", false);
        $$('.cbi-button').css("color", "#333");
        $$('input[type="submit"]').attr("disabled", false);
        $$('input[type="submit"]').css("color", "white");
    }
    else if (url.indexOf('flashops') != -1)
    {
        $$('input[type="submit"]').attr("disabled", false);
        $$('input[type="submit"]').css("color", "black");
        $$('.cbi-button-save').css("color", "white");
        $$('.cbi-button-reset').css("color", "white");
        $$('.cbi-button-apply').css("color", "white");
    }
    else  // The other pages
    {
        $$('input[type="submit"]').attr("disabled", false);
        $$('input[type="submit"]').css("color", "white");
    }
});