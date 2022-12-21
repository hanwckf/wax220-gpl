var action = "";

function reboot_device()
{
    var url, data;
    url = '<% action_url("apply.cgi", "applyreboot.htm") %>';
    data = {anticsrf:'<% generateToken("reboot") %>', submitType:"reboot"};
    ajax_normal({
        async: false,
        type : "POST",
        url  : url,
        data : data,
    });
}

function reset_to_default()
{
    var url, data;
    url = '<% action_url("apply.cgi", "backup_settings.htm") %>';
    data = {anticsrf:'<% generateToken("factory") %>', submitType:"factory", reset_type: "0"};
    ajax_normal({
        async: false,
        type : "POST",
        url  : url,
        data : data,
    });
}

function backup_settings()
{
    $$('<form action=\'<% action_url("backup.cgi", "backup_settings.htm") %>\' method="post">'+
            '<input type="hidden" name="anticsrf" value=\'<% generateToken("backup") %>\'>'+
        '</form>')
        .appendTo('body').submit().remove();
}

function check_restore_file()
{
    var url, data;
    url = '<% action_url("apply.cgi", "backup_settings.htm") %>';
    data = {anticsrf:'<% generateToken("gui_restore_check") %>', submitType:"gui_restore_check"};
    ajax_normal(
    {
        async: false,
        type : "POST",
        url  : url,
        data : data,
        dataType: "JSON",
        error:function(){},
        success:function(result)
        {
            if ("1" == result.ret)
            {
                document.getElementById('invalid_backup').style.display = "";
            }
            else
            {
                getTop(window).location.href="applyreboot.htm";
            }
        }
    });
}

function restore_new_setting()
{
    var restoreFile = $$("input[name='archive']").val();
    if ("" == restoreFile) {
        document.getElementById('invalid_backup').style.display = "";
        return;
    }
    else {
        var size = $$("input[name='archive']")[0].files[0].size;
        if (size > 1024*1024) {
            document.getElementById('invalid_backup').style.display = "";
            return;
        }
        else {
            document.getElementById('invalid_backup').style.display = "none";
        }
    }

    var formData = new FormData();
    formData.append('mtenRestoreCfg', $$("input[name='archive']")[0].files[0]);
    formData.append('anticsrf', '<% generateToken("backup_restore") %>');
    var url = '<% action_url("restore.cgi", "backup_settings.htm") %>';
    ajax_normal({
        async: false,
        type : "POST",
        data : formData,
        cache: false,
        url  : url,
        processData : false,
        contentType : false,
        success: function() {},
        error: function() {}
    });
    check_restore_file();
}

$$(function()
{
    $$(".cbi-section")[((action == "reset") ? "1" : "2")].style.display = "block";
    $$("input[name='reset']").on("click", function()
    {
        var msg = confirm("$upgrade_note6");
        if (true == msg)
        {
            reset_to_default();
            getTop(window).location.href="system_erasing.htm";
        }
    });
    $$("input[name='user_restore']").on("click", function()
    {
        return confirm("$upgrade_note7");
    });
    $$("input[name='reboot']").on("click", function()
    {
        if (confirm("$upgrade_note8")) {
            reboot_device();
            getTop(window).location.href="applyreboot.htm";
        }
    });
    $$("input[name='user_backup']").on("click", function()
    {
        return confirm("$upgrade_note9");
    });

    window.alert = function(al, $$){
        return function(msg) {
            al.call(window,msg);
            $$(window).trigger("okbuttonclicked");
        };
    }(window.alert, window.jQuery);

    $$(window).on("okbuttonclicked", function() {
        modalAction(false, "");
    });
});

