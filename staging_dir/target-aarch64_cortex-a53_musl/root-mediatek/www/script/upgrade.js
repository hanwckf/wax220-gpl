function cancel_image()
{
    var url = '<% action_url("upgrade.cgi", "flashops.htm") %>';
    var data = {anticsrf:'<% generateToken("upload_firmware") %>', submitType:"upload_firmware", upgrade_yes_no:"0"};
    ajax_normal({
        async: false,
        type : "POST",
        url  : url,
        data : data,
        dataType: "JSON",
        error:function(){},
        success:function(){}
    });
    document.location.href="flashops.htm";
}

function upgrade_image()
{
    var url = '<% action_url("upgrade.cgi", "upgrade.htm") %>';
    var data = {anticsrf:'<% generateToken("upload_firmware") %>', submitType:"upload_firmware", upgrade_yes_no:"1"};
    ajax_normal({
        async: false,
        type : "POST",
        url  : url,
        data : data,
        dataType: "JSON",
        error:function(){},
        success:function(){}
    });
    getTop(window).location.href="system_flashing.htm";
}

