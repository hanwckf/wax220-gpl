/**
 * \brief    Administrator account is not permitted.
 * \param    usr        The user name string.
 * \return    Return 0 if OK.
 */
function checkUserName(usr)
{
    if (usr == "root" || usr == "nobody" || usr == "daemon"
        || usr == "ftp" || usr == "network"){
        alert("$account_note2");
        return CHECK_FAILED;
    }
    return CHECK_PASS;
}

/**
 * \brief    test the validity of the usre name.
 * \param    usr_name    The name string.
 * \param    min            The minimum length of the name.
 * \param    max            The maximum length of the name.
 * \return    Return 0 if OK.
 */
var CHECK_PASS = 0;
var CHECK_FAILED = 1;
function validateUsr(usr_name, min, max)
{
    if ("" == usr_name)
    {
        alert("$account_note3");
        return CHECK_FAILED;
    }
    else if (min > usr_name.length || max < usr_name.length)
    {
        alert(String.format("$account_note4", min, max));
        return CHECK_FAILED;
    }
    else if (isChinese(usr_name))
    {
        alert(String.format("$account_note5"));
        return CHECK_FAILED;
    }
/*<% if uci:get("functionlist","functionlist","SUPPORT_MULTI_LOGIN") == "1" then%>
    var ReservedChars = /^[^#\^\$\.\*\%\'\":\\\/\[\]& ]+$/;
    if (!ReservedChars.test(usr_name) || isFullwidth(usr_name))
    {
        alert('<%=translatef("%s (Space) are invalid characters. Please input a new one.", " ^ $ % * .  # \\\' \" : \\\\ / [ ] &")%>');
        return CHECK_FAILED;
    }
<% else %>*/
    var ReservedChars = /^[^#\`\'\":\\\/\[\]& ]+$/;
    if (!ReservedChars.test(usr_name) || isFullwidth(usr_name))
    {
        alert("$account_note8");
        return CHECK_FAILED;
    }
/*<% end %>*/
    return CHECK_PASS;
}

function messageInfo()
{
    var msg = "$account_note1"+"!@#$$%^&()*";
    alert(msg);
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

    if (iRet == 0)
    {
        /*
        ******Force has one special character !@#$%^&*()
        if (!hasNumber(pw) || !hasCapital(pw) || !hasLowercase(pw) || !hasValidSpecialChar(pw)|| !hasSpecialChar2(pw))
        */
        /*
        ******Option has one special character !@#$%^&*()
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
            alert("$account_note6");
            return CHECK_FAILED;
        }
    }
    else
    {
        if (pw2 == pw1)
        {
            alert("$account_note7");
            return CHECK_FAILED;
        }
    }

    return CHECK_PASS;
}

/**
 * \brief    check    The current password.
 * \param    curpw    The password string.
 * \return    Return 0 if OK.
 */
function checkCurrentPW(curpw)
{
    var fail = 0;
    var olduser = '<% cfg_get("http_username") %>';
    if (olduser == $$("input[name='usr_name']").val())
    {
        var url, data, fail = 0;
        url = '<% action_url("apply.cgi", "account.htm") %>';
        data = {anticsrf:'<% generateToken("checkpasswd") %>', submitType:"checkpasswd", curpasswd: curpw};
        ajax_normal(
        {
            async: false,
            type : "POST",
            url:url,
            data:data,
            dataType: "JSON",
            error:function(){},
            success:function(result)
            {
                if (result.ret == "0"){
                    alert("$invalid_current_password");
                    fail = 1;
                }
            }
        });
    }
    if (1 == fail)
        return CHECK_FAILED;
    else
        return CHECK_PASS;
}

function changeInputType(field, image)
{
    var pw_value = document.getElementById(field).value;

    if (document.getElementById(field).type == 'password') {
        $$("#"+field+"").replaceWith("<input type=text maxlength='32' name="+field+" id="+field+" autocomplete=\"off\" style='width:170px;'>");
        $$("#"+image+"").attr("src", "image/eye.svg");
    } else {
        $$("#"+field+"").replaceWith("<input type=password maxlength='32' name="+field+" id="+field+" autocomplete=\"off\" style='width:170px;'>");
        $$("#"+image+"").attr("src", "image/eye-slash.svg");
    }
    document.getElementById(field).value = pw_value;
}

function isprotecting(pw1){
    var url = '<% action_url("apply.cgi", "account.htm") %>';
    var data = {anticsrf:'<% generateToken("passwd") %>', submitType:"passwd", pw1:pw1};
    ajax_normal(
    {
        async: false,
        type : "POST",
        url  : url,
        data : data,
        dataType: "JSON",
        error:function(){},
        success:function(){}
    });
}

function savechanges(){
    var szRet = "";
    var usr_name = document.getElementById("usr_name").value;
    var curpw = document.getElementById("cur_pw").value;
    var pw1 = document.getElementsByName("pw1")[0].value;
    var pw2 = document.getElementsByName("pw2")[0].value;
    if ((checkUserName(usr_name)) ||
        (validateUsr(usr_name, 1, 12)) ||
        (validatePW2(pw1)) ||
        (checkPW1PW2(pw1, pw2, szRet)) ||
        (checkCurrentPW($$.base64.encode(curpw))) ||
        (checkPW1PW2(pw1, curpw, 1)))
    {
        return false;
    }

    alert("$password_changed_successfully");
    isprotecting($$.base64.encode(pw1));
    //ajax_setCsrf();
    // getTop(window).location.href="sysauth.htm";

    return true;
}
//]]>
$$(function() {

});
