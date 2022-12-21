var firmwareVersion = "<% cat_file("/firmware_version") %>";
var hardware_version = "<% cat_file("/hardware_version") %>";
var action = "";
var obj_newFWInfo = "", str_newFWInfo = "";
var modelName = "<% cat_file("/module_name") %>";
var newFWInfo = <% cfg_get("new_firmware_info") %>;
var checkFW = "<% cfg_get("agree_auto_up_TC") %>";

if ((newFWInfo != "") && (newFWInfo != "0") && (!(JSON.stringify(newFWInfo)==="{}")))
{
    str_newFWInfo = JSON.stringify(newFWInfo);
    str_newFWInfo = str_newFWInfo.replace(/\r/g, ' ');
    str_newFWInfo = str_newFWInfo.replace(/\n/g, '<br>');
    obj_newFWInfo = JSON.parse(str_newFWInfo);
}

function showReleaseNote()
{
    var w = window.open();
    var str = obj_newFWInfo.change_log;

    str = str.replace(/::_n::/g,"<br>");
    str = str.replace(/::_t::/g,"&nbsp;&nbsp;&nbsp;&nbsp;");
    w.document.write(str||"");
    w.document.close();
}

function upgrade_check_mem()
{
    document.getElementById('invalid_firmware').style.display = "none";
    document.getElementById("uploadModal").style.display = "";
    document.getElementById("uploadModal").style.display = "block";
    var imageFile = $$("input[name='image']").val();
    if ("" == imageFile) {
        document.getElementById("uploadModal").style.display = "none";
        document.getElementById('invalid_firmware').style.display = "";
        return;
    }
    else {
        var size = $$("input[name='image']")[0].files[0].size;
        if (size <= 10*1024*1024) {
            document.getElementById("uploadModal").style.display = "none";
            document.getElementById('invalid_firmware').style.display = "";
            return;
        }
        else if (size > 40*1024*1024) {
            document.getElementById("uploadModal").style.display = "none";
            document.getElementById('invalid_firmware').style.display = "";
            return;
        }
        else {
            document.getElementById('invalid_firmware').style.display = "none";
        }
    }

    var formData = new FormData();
    formData.append('mtenFWUpload', $$("input[name='image']")[0].files[0]);
    formData.append('anticsrf', '<% generateToken("upgrade_check") %>');
    var url = '<% action_url("upgrade_check.cgi", "flashops.htm") %>';
    ajax_normal({
        async: true,
        type : "POST",
        data : formData,
        cache: false,
        url  : url,
        processData : false,
        contentType : false,
        error: function() {
            document.getElementById("uploadModal").style.display = "none";
            document.getElementById('invalid_firmware').style.display = "";
        },
        success: function(result) {
            if ("2" == result.ret) {
                document.location.href="upgrade.htm";
            }
        }
    });
}

function saveAutoFW(){
    var url, data;
    var enable = (document.getElementById("autoFWEnable_enable").checked == true) ? 1 : 0;
    url = '<% action_url("apply.cgi", "flashops.htm") %>';
    data = {anticsrf:'<% generateToken("upg_agree_conditions") %>', submitType:"upg_agree_conditions", autoFWEnable: enable};
    ajax_normal({
        async: false,
        type : "POST",
        url  : url,
        data : data,
    });
}

function modalAction(enable)
{
    if (enable == true) {
        document.getElementById("myModal").style.display = "";
        document.getElementById("myModal").style.display = "block";
    }
    else {
        document.getElementById("myModal").style.display = "none";
    }
}

function get_online_check_result()
{
    var url, data, fail = 0;
    url = '<% action_url("apply.cgi", "flashops.htm") %>';
    data = {anticsrf:'<% generateToken("gui_online_check") %>', submitType:"gui_online_check"};
    ajax_normal(
    {
        async: false,
        type : "POST",
        url  : url,
        data : data,
        dataType: "JSON",
        error:function(){},
        success:function(result) {
            if ("0" == result.internet) {
                document.location.href="upgrade_no_internet.htm";
            }
            else {
                if ("1" == result.newVersion) {
                    document.location.href="upgrade_found_new_version.htm";
                }
                else {
                    document.location.href="upgrade_no_new_version.htm";
                }
            }
        }
    });
}

function check_new_fw_version()
{
    modalAction(true);
    var url, data = 0;
    url = '<% action_url("func.cgi", "flashops.htm") %>';
    data = {anticsrf:'<% generateToken("download_confile") %>', submitType:"download_confile"};
    ajax_normal({
        async: false,
        type : "POST",
        url:url,
        data:data,
        success: function(re) {
            if ("" == re) {
                alert("$upgrade_note13");
                $$("#new_ver").text("");
                $$("#release_date").text("");
                $$("#last_check").text("");
            }
            else {
                obj_newFWInfo = re;
                str_newFWInfo = obj_newFWInfo;
                str_newFWInfo = str_newFWInfo.replace(/\r/g,' ');
                str_newFWInfo = str_newFWInfo.replace(/\n/g,'<br>');
                obj_newFWInfo = JSON.parse(str_newFWInfo);
                if (obj_newFWInfo.avaliable == "0" && obj_newFWInfo.version == "0")
                    alert("$upgrade_note13");
                $$("#new_ver").text((obj_newFWInfo.avaliable != "0")?obj_newFWInfo.version:"");
                $$("#release_date").text((obj_newFWInfo.avaliable != "0")?obj_newFWInfo.release_date:"");
                $$("#last_check").text(obj_newFWInfo.last_check || "");
                document.getElementById('upgradeAction').style.display = ((obj_newFWInfo.avaliable == "1") ? "" : "none");
                modalAction(false, "");
            }
        }
    });
    setTimeout("get_online_check_result()", 10000);
}

function check_download_firmware()
{
    modalAction(true, "<% cat_file("/module_name") %>$upgrade_note14");
    ajax_normal({
        url: '<% action_url("apply.cgi", "flashops.htm") %>',
        data:"",
        success: function(re) {
            if (0 == re) {
                alert("$upgrade_note15")
            }
            else {
                modalAction(false, "");
                upgrade();
            }
        }
    });
}

function upgrade()
{
    ajax_normal({
        url: '<% action_url("apply.cgi", "flashops.htm") %>',
        data:"",
        success: function(re) {
            if (0 == re) {
            }
            else {
                applyreboot();
            }
        }
    });
}

$$(function()
{
    $$("input[name='upgradeAction']").on("click", function ()
    {
        return confirm("$upgrade_note10");
    });
    document.getElementsByName("autoFWEnable")[(checkFW == "1") ? 0 : 1].checked = true;
    if (obj_newFWInfo != "")
    {
        $$("#new_ver").text(obj_newFWInfo.version || "unknown");
        $$("#release_date").text(obj_newFWInfo.release_date || "unknown");
        document.getElementById('checkBtn').style.display = "none";
        document.getElementById('autoFWInfo').style.display = ((checkFW == "1") ? "" : "none");
    }

    window.alert = function(al, $$){
        return function(msg) {
            al.call(window,msg);
            $$(window).trigger("okbuttonclicked");
        };
    }(window.alert, window.jQuery);

    $$(window).on("okbuttonclicked", function() {
        modalAction(false, "");
    });

    document.getElementsByName("autoFWEnable")[(checkFW == "1") ? 0 : 1].checked = true;
    if (obj_newFWInfo != "")
    {
        $$("#new_ver").text((obj_newFWInfo.avaliable != "0")?obj_newFWInfo.version:"");
        $$("#release_date").text((obj_newFWInfo.avaliable != "0")?obj_newFWInfo.release_date:"");
        $$("#last_check").text(obj_newFWInfo.last_check || "");
        document.getElementById('upgradeAction').style.display = ((obj_newFWInfo.avaliable == "1") ? "" : "none");
    }
});
