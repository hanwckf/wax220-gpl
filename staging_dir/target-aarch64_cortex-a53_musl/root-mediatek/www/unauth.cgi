<html><head><link rel="stylesheet" href="/style/form.css">
<link rel="stylesheet" href="/style/hijack_style.css">
<link rel="stylesheet" href="/style/advanced.css">
<link rel="stylesheet" href="/style/top_style.css">
<title> 401 Authorization</title>
<meta http-equiv='content-type' content='text/html; charset=UTF-8'>
<script>
var enable_recovery="<% cfg_get("enable_password_recovery") %>";
var third_error="<% cfg_get("third_error") %>";
var enter_sn_again="<% cfg_get("enter_sn_again") %>";
function loadvalue()
{
        if(enter_sn_again == "1")
        	recovery_div();
        else if( third_error == "0")
        	setTimeout("recovery_div()",1000)
        else
        	recovery_div();
}
function recovery_div()
{
        if( enable_recovery == "1")
        {
            document.getElementById("recovery").style.display="";
            document.getElementById("password_reset").innerHTML = "$password_reset";
            if( enter_sn_again == "1" )
            {
                alert("$sn_not_match");
            }
            else
                document.forms[0].serial_num.value="";
        }
        else
        {
                document.getElementById("recovery").style.display="none";
        }
}
function click_cancel()
{
	document.forms[0].serial_num.value="";
}
</script>
</head>
<body onLoad="loadvalue()">
<div id="top" class='standalone-top'>
<div id="logo"> </div>
<div id="firm_version" name="firm_version">$firmware_version<br /><% cat_file("/firmware_version") %></div>
</div>
<div id="container_unauth" class="container_center">
<h1 id="password_reset"> $unauthorized</h1>
$no_permission

<div id="recovery" style="display: none">
<% form_submit("recover", "unauth.cgi", "match_sn") %>
<p>$password_reset_tip2</p>
<p>$enter_sn<input type="text" size="13" maxlength="13" name="serial_num" id="serial_number" value=""><br/>
$find_sn</p>
<p><input class="cancel_bt" type='button' name="Cancel" id="cancel" value=' $cancel ' onClick='click_cancel();'>&nbsp;&nbsp;
<input class="apply_bt" type="submit" name="continue" id="continue" value=" $continue "></p></form>
</div>
</div>
</div>
</body></html>