var ts = '<% cfg_get("sso_login") %>';
var factory_mode = '<% cfg_get("factory_mode") %>';

function doCookieSetup(name, value, days)
{
    var date = new Date();
    date.setTime(date.getTime()+(days*24*60*60*1000));
    var expires = "; expires="+date.toGMTString();

    //console.log("---------name+days:"+name+"["+days+"]");
    if (days == 0)
    {
        //console.log("----Erase-----document.cookie ="+document.cookie);
        document.cookie = name+"="+value+expires+"; path=/cgi-bin/luci";
        document.cookie = name+"="+value+expires+"; path=/cgi-bin";
        document.cookie = name+"="+value+expires;
    }

    document.cookie = name+"="+value+expires+"; path=/";
    //console.log("---------document.cookie ="+document.cookie);
}
function eraseCookie(name)
{
    doCookieSetup(name,"",0);
}

// eraseCookie("is_login");
// eraseCookie("serialize");

function changeInputType(field, image)
{
    var pw_value = document.getElementById(field).value;

    if (document.getElementById(field).type == 'password') {
        $$("#"+field+"").replaceWith("<input id="+field+" name="+field+" type=\"text\" myid=\"password\" maxLength=\"32\" size=\"35\" placeholder=\"password\" autocomplete=\"off\" />");
        $$("#"+image+"").attr("src", "image/eye.svg");
    } else {
        $$("#"+field+"").replaceWith("<input id="+field+" name="+field+" type=\"password\" myid=\"password\" maxLength=\"32\" size=\"35\" placeholder=\"password\" autocomplete=\"off\" />");
        $$("#"+image+"").attr("src", "image/eye-slash.svg");
    }
    document.getElementById(field).value = pw_value;
}

var timeHandle = void 0;

function login_failed_three(secs) {
    clearInterval(timeHandle);
    timeHandle = void 0;
    var flag = new Date().getTime();

    if (secs <= 0) {
        document.getElementById('password_plain_text').disabled = false;
        document.getElementById('password_plain_text').focus();
        document.querySelector('#retry_msg').innerHTML = "";
        pwChange();
    } else {
        function countdown() {
            var curr = new Date().getTime();
            var last = secs - parseInt((curr - flag) / 1000, 10);

            if (last > 0) {
                document.querySelector('#retry_msg').innerHTML = "$login_error_info_1 " + parseInt(last / 60) + " $login_error_info_2 " + parseInt(last % 60) + " $login_error_info_3";
            } else {
                clearInterval(timeHandle);
                timeHandle = void 0;
                document.getElementById('password_plain_text').disabled = false;
                document.getElementById('password_plain_text').focus();
                document.querySelector('#retry_msg').innerHTML = "";
                pwChange();
            }
        }

        clearInterval(timeHandle);
        countdown();
        timeHandle = setInterval(function(){countdown();}, 1000);
    }
}

function pwChange()
{
    if (document.getElementById('password_plain_text').value.length > 0) {
        document.getElementById("login_button").disabled = false;
    } else {
        document.getElementById("login_button").disabled = true;
    }
}

function saveChanges()
{
    if (document.getElementById('password_plain_text').value.length <= 0)
        return false;

    var f = document.formname;

    f.password.value = hex_md5(f.password_plain_text.value+"\n");

    // doCookieSetup("is_login", "1", 1);

    if ( f.account.value.length == 0 )
    {
        alert("Please enter username");
        return false;
    }

    f.username.value = f.account.value;
    document.getElementById('account').disabled = true;
    document.getElementById('password_plain_text').disabled = true;
    document.getElementById("login_button").disabled = true;
    if (document.getElementById("agree_info").checked == true)
    {
        f.agree.value = 1;
    }

    $$.ajax({
        url: 'sso_login.cgi?sysauth.htm timestamp=' + ts,
        type: "POST",
        dataType: "json",
        data: {'submitType': 'sso_login', 'username': f.account.value, 'password': f.password_plain_text.value},
        success: function(json) {
            ts = json.ts;
            // console.log("success:", json);
            // status: 0, success; 1, multi login; 2, login fail; 3, login fail times > max times
            if (json.status == "0") {
                top.location.href = "index.htm";
            } else if (json.status == "1") {
                top.location.href = "multi_login.html";
            } else if (json.status == "2") {
                document.getElementById('account').disabled = false;
                document.getElementById('password_plain_text').disabled = false;
                document.getElementById('password_plain_text').value="";
                document.getElementById('password_plain_text').focus();
                pwChange();
                document.querySelector('#retry_msg').innerHTML = "$login_error_info_4";
            } else if (json.status == "3") {
                document.getElementById('password_plain_text').disabled = true;
                document.getElementById('password_plain_text').value="";
                pwChange();
                if (!timeHandle)
                    login_failed_three(json.time);
            } else {
                document.querySelector('#retry_msg').innerHTML = "$login_error_info_5";
                document.getElementById('account').disabled = true;
                document.getElementById('password_plain_text').disabled = true;
                document.getElementById("login_button").disabled = true;
            }
        },
        error: function(json) {
            // console.log("error:", json);
        }
    })
    // document.formname.submit();
}
function only_password_display()
{
    document.getElementById('account').value = '<% cfg_get("http_loginname") %>';
    document.getElementById('username_part').style.display = "none";
    // document.getElementById('terms_part').style.display = "none";
}

var disable_submit = false;
var agree = true;
function startTimer(duration) {
    disable_submit = true;
    var timer = duration;
    var countDownTimer = setInterval(function () {
        time = timer--;
        var hours = Math.floor(time / 3600);
        time = time - hours * 3600;
        var minutes = Math.floor(time / 60);
        var seconds = time - minutes * 60;
        if (timer < 0)
        {
            $$('#login_button').removeAttr("disabled");
            $$('#login_button').css("color", "white");
            document.querySelector('#retry_msg').innerHTML="";
            clearInterval(countDownTimer);
            disable_submit = false;
        }
        else
        {
            $$('#login_button').attr('disabled', 'disabled');
            $$('#login_button').css("color", "grey");
            if ( hours > 0 )
                document.querySelector('#retry_msg').innerHTML="Please try again after " + hours + " Hours, " + minutes + " Minutes and " + seconds + " Seconds.";
            else if ( minutes > 0 )
                document.querySelector('#retry_msg').innerHTML="Please try again after " + minutes + " Minutes and " + seconds + " Seconds.";
            else
                document.querySelector('#retry_msg').innerHTML="Please try again after " + seconds +" Seconds.";
        }
    }, 1000);
}

function login_display()
{
    if ((document.getElementById("agree_info").checked == true) || (1 == factory_mode))
    {
        $$("#login_button").attr("disabled", false);
        $$('#login_button').css("color", "white");
        agree = true;
    }
    else
    {
        $$("#login_button").attr("disabled", true);
        $$('#login_button').css("color", "grey");
        agree = false;
    }
}

$$(document).ready(function() {
    var now_url = window.location.href;
    if(now_url.indexOf("BRS_config_basic")!=-1){
        location.href = '/BRS_config_basic.html';
    }

    document.getElementsByName('account')[0].focus();

    if (document.getElementById("agree_info").checked == true)
        agree = true;
    else
        agree = false;

    $$("input").on( "keydown", function( event ) {
        if ( event.which == 13 && !disable_submit && agree) {
            saveChanges();
        }
    });

    // When input account and password then change underline color.
    // $$("#account").on( "keydown", function( event ) {
    //     $$("#account").css("border-bottom","1px solid #3a3a3a");
    //     $$("#password_plain_text").css("border-bottom","1px solid #3a3a3a");
    // });

    // $$("#password_plain_text").on( "keydown", function( event ) {
    //     $$("#account").css("border-bottom","1px solid #3a3a3a");
    //     $$("#password_plain_text").css("border-bottom","1px solid #3a3a3a");
    // });
    document.getElementsByName("agree_info")[0].checked=('<% cfg_get("agree_full_TC") %>'=="1")?true:false;
    login_display();
    pwChange();

    only_password_display();
    document.formname.password_plain_text.focus();
});