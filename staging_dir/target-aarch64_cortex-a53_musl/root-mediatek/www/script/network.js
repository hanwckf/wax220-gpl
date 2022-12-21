//var stp={en:"<% cfg_get("stp_status") %>"};
var lan={proto:"<% cfg_get("lan_dhcp") %>", dns:"<% cfg_get("dns") %>"};
var lan_ipaddr="<% cfg_get("lan_ipaddr") %>";
var lan_netmask="<% cfg_get("lan_netmask") %>";
var lan_gateway="<% cfg_get("lan_gateway") %>";
var t_dns="";
var dns1="<% cfg_get("dns1") %>";
var dns2="<% cfg_get("dns2") %>";
var ipv6_addr="<% cfg_get("Ipv6rdPrefix") %>";
var ipv6_prefix="<% cfg_get("Ipv6rdPrefix") %>";
var ipv6_dns1="<% cfg_get("ipv6_fixed_dns1") %>";
var ipv6_dns2="<% cfg_get("ipv6_fixed_dns2") %>";
var ipv6_gw="<% cfg_get("ipv6_fixed_gw_ip") %>";
var ipv6_set_mode=0;//"<% cfg_get("ipv6_set_mode") %>";
var ethernet_bonding="<% cfg_get("ethernet_bonding") %>";
// var stp_hello_time="2";//"<% cfg_get("stp_hello_time") %>";
// var stp_max_age="20";//"<% cfg_get("stp_max_age") %>";
// var stp_forward_delay="2";//"<% cfg_get("stp_forward_delay") %>";
// var stp_priority="32768";//"<% cfg_get("stp_priority") %>";

//var ipv6={linklocal:"<%=laninfo['ip6LinkLocalEn']%>", addr:"<%=laninfo['ip6addr']%>",gw:"<%=laninfo['ip6gw']%>"};    
var ipv6={linklocal:"1", addr:"",gw:""};


$$(document).ready(function() {
    if(lan.dns.length)
    {
        t_dns = lan.dns.split(" ");
        //dns1 = t_dns[0] || "";
        //dns2 = t_dns[1] || "";
        ipv6_dns1 = t_dns[2] || "";
        ipv6_dns2 = t_dns[3] || "";
    }

    if(ipv6.addr != "")
    {
        ipv6_addr = ipv6.addr.split("/")[0] || "";
        ipv6_prefix = ipv6.addr.split("/")[1] || "";
    }
    
    if(ipv6.gw != "")
    {
        ipv6_gw = ipv6.gw || "";
    }


    if (ipv6_set_mode)
    {
        //$$('select[name$$="ipv6_proto"]').val("<%=laninfo['ipv6_proto']%>");
        $$('select[name$$="ipv6_proto"]').val("");
    }
    else
    {
        document.getElementsByName('linklocal_ipv6')[0].checked = (ipv6.linklocal == "1");
    }

    document.getElementsByName("ipv6_ipaddr")[0].value=ipv6_addr;
    document.getElementsByName('ipv6_subprefixleng')[0].value=ipv6_prefix;
    document.getElementsByName('ipv6_gateway')[0].value=ipv6_gw;
    document.getElementsByName('ipv6_dns1')[0].value = ipv6_dns1;
    document.getElementsByName('ipv6_dns2')[0].value = ipv6_dns2;

    document.getElementsByName('ipv4_dns1')[0].value=dns1;
    document.getElementsByName('ipv4_dns2')[0].value=dns2;
    document.getElementsByName('ipv4_proto')[((lan.proto=="static")?"1":"0")].checked = true;
    // document.getElementsByName('enable_stp')[((stp.en=="1")?"0":"1")].checked = true;

    // document.getElementsByName('stp_hello_time')[0].value=stp_hello_time;
    // document.getElementsByName('stp_max_age')[0].value=stp_max_age;
    // document.getElementsByName('stp_forward_delay')[0].value=stp_forward_delay;
    // document.getElementsByName('stp_priority')[0].value=stp_priority;

    if(0)//(functionlist.SUPPORT_CBMODE_DISABLE_STP=="1")
    {
        //var wifi0_mode='<%=uci:get("wireless","wifi0","opmode")%>';
        //var wifi1_mode='<%=uci:get("wireless","wifi1","opmode")%>';
        var wifi0_mode='ap';
        var wifi1_mode='ap';
        // if ((wifi0_mode=="sta") || (wifi1_mode=="sta"))
        // {
        //     $$('input[name="enable_stp"]').attr("disabled", "disabled");
        // }
    }

    if(0)//(functionlist.SUPPORT_MESH_SETTING=="1")
    {
        //var mesh_disable='<%=uci:get("mesh","wifi","disabled")%>';
        var mesh_disable='1';
        // if(mesh_disable==0)
        //     $$('input[name="enable_stp"]').attr("disabled", "disabled");
    }

    var proto=document.getElementsByName('ipv4_proto')[0].checked;

    proto_display(1);
    //stp_status();
});


function proto_display(idx)
{
    var proto=document.getElementsByName('ipv4_proto')[0].checked;
    if (!proto && idx)
    {
        document.getElementById('ipv4_ipaddr').value = lan_ipaddr;
        document.getElementById('ipv4_netmask').value = lan_netmask;
        document.getElementById('ipv4_gateway').value = lan_gateway;
    }
    document.getElementById('proto_display').style.display=((proto)?"none":"");

    if(ipv6_set_mode)
    {
        var ipv6_proto=$$('select[name$$="ipv6_proto"]').find('option:selected').val();
            if(ipv6_proto=="static")
            {
                $$("input[name^='ipv6_']").removeAttr("disabled");
                $$('#ipv6_setting_span').show();
            }
            else
            {
                
                $$("input[name^='ipv6_']").attr("disabled", "disabled");
                //$$('#ipv6_setting_span').hide();
            }        
    }
    else
    {
        if(proto)
        {
            document.getElementsByName('linklocal_ipv6')[0].checked = "1";
            $$("input[name='linklocal_ipv6_checked']").val("1");
            $$("input[name='linklocal_ipv6']").attr("disabled", "disabled");
            $$("input[name^='ipv6_']").attr("disabled", "disabled");
        }
        else
        {
            $$("input[name^='ipv6_']").removeAttr("disabled");
            $$("input[name='linklocal_ipv6']").removeAttr("disabled");
            ipv6_display();
        }    
    }

    if (ethernet_bonding)
    {
        $$("#table_lacp_set").show();
    }
    else
    {
        $$("#table_lacp_set").hide();
    }
}

function ipv6_display()
{
    var sta = document.getElementsByName('linklocal_ipv6')[0].checked;
    if(sta)
    {
        $$("input[name='linklocal_ipv6_checked']").val("1");
        $$("input[name^='ipv6_']").attr("disabled", "disabled");
    }
    else
    {
        $$("input[name^='ipv6_']").removeAttr("disabled");
    }
}

/* function stp_status()
{
    var sta=document.getElementsByName('enable_stp')[0].checked;
    if(sta)
    {
        $$('input[name^="stp_"]').removeAttr("disabled");
    }
    else
    {
        $$('input[name^="stp_"]').attr("disabled", "disabled");
    }
} */


function isprotecting(){
    $$('form').submit(function() {
        $$("input[name='submitType']").val("basic");
            // var formdata = $(this).serialize()+"19930408\n";
            // var reg = /cbi\.apply\=Apply|submitType\=Save|&|\=|-*/g;
            // formdata = formdata.replace(reg,"");
            // doCookieSetup("serialize", hex_md5(formdata), 1);
    });
}

function setfocusNT(target)
{
    //target.value = target.defaultValue;
    target.focus();
}


function saveChanges()
{
    //isprotecting();
    //ajax_setCsrf();
    // if(functionlist.SUPPORT_ETHERNET_BONDING==1){
    //     get_lacp_mut_status();            
    // }        
    /*<%#ipv4 check%>*/
    //please_wait(1);
    if(document.getElementsByName('ipv4_proto')[1].checked || (ipv6_set_mode)) //<%#Static%>
    {
        if(!isIpaddr(getByName('ipv4_ipaddr').value))
        {
            alert(invalid("$ip_address"));
            setfocusNT(getByName('ipv4_ipaddr'));
            return false;
        }
        if(isMulticast(getByName('ipv4_ipaddr').value))
        {
            alert("The ip address cannot be a multicast ip address.");
            setfocusNT(getByName('ipv4_ipaddr'));
            return false;
        }
        if(isLinklocal(getByName('ipv4_ipaddr').value))
        {
            alert("The ip address cannot be a linklocal ip address.");
            setfocusNT(getByName('ipv4_ipaddr'));
            return false;
        }
        if(isLoopback(getByName('ipv4_ipaddr').value))
        {
            alert("The ip address cannot be a loopback ip address.");
            setfocusNT(getByName('ipv4_ipaddr'));
            return false;
        }
        
        if(!isSubMask(getByName('ipv4_netmask').value))
        {
            alert(invalid("$subnet_mask"));
            setfocusNT(getByName('ipv4_netmask'));
            return false;
        }

        //var gn1_dis='<%=uci:get("wireless", "wifi0_guest", "disabled")%>';
        //var gn2_dis='<%=uci:get("wireless", "wifi1_guest", "disabled")%>';
        //var gn_ip='<%=uci:get("network", "guest", "ipaddr")%>';
        //var gn_mask='<%=uci:get("network", "guest", "netmask")%>';
        var gn1_dis='1';
        var gn2_dis='1';
        var gn_ip='192.168.200.1';
        var gn_mask='255.255.255.0';
        if(gn1_dis == 0 || gn2_dis == 0){
            if(isSameSubnet(gn_ip, gn_mask, getByName('ipv4_ipaddr').value, getByName('ipv4_netmask').value)){
                alert("$lan_ip_notice4");
                setfocusNT(getByName('ipv4_ipaddr'));
                return false;
            }                
        }
        if(getByName('ipv4_gateway').value != "")
        {
            if(!isIpaddr(getByName('ipv4_gateway').value))
            {
                alert(invalid("$gateway"));
                setfocusNT(getByName('ipv4_gateway'));
                return false;
            }
            if(isMulticast(getByName('ipv4_gateway').value))
            {
                alert("$gateway_notice1");
                setfocusNT(getByName('ipv4_gateway'));
                return false;
            }
            if(isLinklocal(getByName('ipv4_gateway').value))
            {
                alert("$gateway_notice2");
                setfocusNT(getByName('ipv4_gateway'));
                return false;
            }
            if(isLoopback(getByName('ipv4_gateway').value))
            {
                alert("$gateway_notice3");
                setfocusNT(getByName('ipv4_gateway'));
                return false;
            }
        }
        if(getByName('ipv4_gateway').value != "" && getByName('ipv4_ipaddr').value != "")
        {
            if(!isSameSubnet(getByName('ipv4_ipaddr').value, getByName('ipv4_netmask').value, getByName('ipv4_gateway').value))
            {
                alert(invalid("$gateway_notice4"));
                setfocusNT(getByName('ipv4_ipaddr'));
                return false;
            }
        }
        if (0 == getByName('ipv4_dns1').value.length)
        {
            alert("$dns_notice4");
            setfocusNT(getByName('ipv4_dns1'));
            return false;
        }
        if(getByName('ipv4_dns1').value != "" && getByName('ipv4_dns1').value != "0.0.0.0")
        {
            if(!isIpaddr(getByName('ipv4_dns1').value))
            {
                alert(invalid("$primary_dns"));
                setfocusNT(getByName('ipv4_dns1'));
                return false;
            }
            if(isMulticast(getByName('ipv4_dns1').value))
            {
                alert("$primary_dns_error1");
                setfocusNT(getByName('ipv4_dns1'));
                return false;
            }
            if(isLinklocal(getByName('ipv4_dns1').value))
            {
                alert("$primary_dns_error2");
                setfocusNT(getByName('ipv4_dns1'));
                return false;
            }
            if(isLoopback(getByName('ipv4_dns1').value))
            {
                alert("$primary_dns_error3");
                setfocusNT(getByName('ipv4_dns1'));
                return false;
            }
        }
        if(getByName('ipv4_dns2').value != "" && getByName('ipv4_dns2').value != "0.0.0.0")
        {
            if(!isIpaddr(getByName('ipv4_dns2').value))
            {
                alert(invalid("Secondary DNS"));
                setfocusNT(getByName('ipv4_dns2'));
                return false;
            }
            if(isMulticast(getByName('ipv4_dns2').value))
            {
                alert("$secondary_dns_error1");
                setfocusNT(getByName('ipv4_dns2'));
                return false;
            }
            if(isLinklocal(getByName('ipv4_dns2').value))
            {
                alert("$secondary_dns_error2");
                setfocusNT(getByName('ipv4_dns2'));
                return false;
            }
            if(isLoopback(getByName('ipv4_dns2').value))
            {
                alert("$secondary_dns_error3");
                setfocusNT(getByName('ipv4_dns2'));
                return false;
            }

            if (getByName('ipv4_dns1').value == getByName('ipv4_dns2').value)
            {
                alert("$secondary_dns_error5");
                setfocusNT(getByName('ipv4_dns2'));
                return false;
            }
        }

        /*<%#IPv6 check%>*/
        if(ipv6_set_mode?($$('select[name$$="ipv6_proto"]').find('option:selected').val()=="static"):(!$$('input[name$$="linklocal_ipv6"]').prop('checked')))
        {
            if(checkIpAddrV6(getByName('ipv6_ipaddr')) != IPv6_VALID_IP)
            {
                alert("$invalid_ipv6_address");
                setfocusNT(getByName('ipv6_ipaddr'));
                return false;
            }
            if(!isRange(getByName('ipv6_subprefixleng'), "IPv6 Subnet Prefix Length", 2, 128))
            {
                setfocusNT(getByName('ipv6_subprefixleng'));
                return false;
            }
            if(checkIpAddrV6allowEmpty(getByName('ipv6_gateway')) != IPv6_VALID_IP)
            {
                alert("$invalid_ipv6_gateway");
                setfocusNT(getByName('ipv6_gateway'));
                return false;
            }
            if((getByName('ipv6_dns1').value == "") && (getByName('ipv6_dns2').value != ""))
            {
                getByName('ipv6_dns1').value = getByName('ipv6_dns2').value;
                getByName('ipv6_dns2').value = "";
            }
            if(checkIpAddrV6allowEmpty(getByName('ipv6_dns1')) != IPv6_VALID_IP)
            {
                alert("$primary_dns_error4");
                setfocusNT(getByName('ipv6_dns1'));
                return false;
            }
            if(getByName('ipv6_dns2').value != "")
            {
                if(checkIpAddrV6allowEmpty(getByName('ipv6_dns2')) != IPv6_VALID_IP)
                {
                    alert("$secondary_dns_error4");
                    setfocusNT(getByName('ipv6_dns2'));
                    return false;
                }
            }
        }

    }
    if ("<% cfg_get("wlg_vlanEnable") %>" == "1"){
        if(document.getElementsByName('ipv4_proto')[1].checked){
            alert("$ip_address_range_notice");
        }
    }

    
    /*<%#STP check%>*/
    /* if(document.getElementsByName('enable_stp')[0].checked)
    {
        if(!isRange(document.getElementsByName('stp_hello_time')[0], "$$hello_time", 1, 10))
        {
            return false;
        }
        if(!isRange(document.getElementsByName('stp_max_age')[0], "$$max_age", 6, 40))
        {
            return false;
        }
        if(!isRange(document.getElementsByName('stp_forward_delay')[0], "$$forward_delay", 4, 30))
        {
            return false;
        }
        if(!isRange(document.getElementsByName('stp_priority')[0], "$$priority", 0, 65535))
        {
            return false;
        }
        if(!(2*(parseInt($$("input[name='stp_hello_time']").val(),10) + 1) <= parseInt($$("input[name='stp_max_age']").val(),10) && parseInt($$("input[name='stp_max_age']").val(),10) <= 2*(parseInt($$("input[name='stp_forward_delay']").val(),10) - 1)))
        {
            alert("$the_stp_settings_should_follow_rule : 2*($$hello_time + 1.0 second)  < = $$max_age_time <= 2*($$forward_delay - 1.0 second)")
            return false;
        }
    } */
    // if(1)//(functionlist.SUPPORT_ETHERNET_BONDING==1)
    // {
    //     if(document.getElementsByName('lacp_enable')[0].checked){
    //         if(!isRange(document.getElementsByName('system_priority')[0], "$$system_priority", 1, 65535)){
    //             return false;
    //         }
            // if(document.getElementsByName('enable_stp')[0].checked){
            //     alert("$lacp_and_stp_can_not_be_enable_at_the_same_time")
            //     return false;
            // }
            // ATKK think that lacp and vlan can be enable together, so i mark these check
            // if(mut_status["vlan"]=="1"){
            //     alert("$lacp_and_vlan_can_not_be_enable_at_the_same_time")
            //     return false;
            // }                
    //     }        
    // }
    isprotecting();
    return true;
}

// for IPv6
var IPv6_VALID_IP = 99;
var IPv6_INVALID_IP = 0;
var IPv6_ZERO_IP = 1;
var IPv6_1st_IP_ERROR = 2;
var IPv6_8th_IP_ERROR = 9;
var IPv6_MULTICAST_IP_ERROR = 19;
var IPV6_STR_ZERO_SYMBOL = 0;
var IPV6_STR_ONE_SYMBOL = 1;
var IPV6_STR_MORETHANTWO_SYMBOL = 2;
var IPV6_ADDR_NOTALLOWZERO = 0;
var IPV6_REGX = new RegExp("^((([0-9A-Fa-f]{1,4}:){7}([0-9A-Fa-f]{1,4}|:))|(([0-9A-Fa-f]{1,4}:){6}(:[0-9A-Fa-f]{1,4}|((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){5}(((:[0-9A-Fa-f]{1,4}){1,2})|:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3})|:))|(([0-9A-Fa-f]{1,4}:){4}(((:[0-9A-Fa-f]{1,4}){1,3})|((:[0-9A-Fa-f]{1,4})?:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){3}(((:[0-9A-Fa-f]{1,4}){1,4})|((:[0-9A-Fa-f]{1,4}){0,2}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){2}(((:[0-9A-Fa-f]{1,4}){1,5})|((:[0-9A-Fa-f]{1,4}){0,3}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(([0-9A-Fa-f]{1,4}:){1}(((:[0-9A-Fa-f]{1,4}){1,6})|((:[0-9A-Fa-f]{1,4}){0,4}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:))|(:(((:[0-9A-Fa-f]{1,4}){1,7})|((:[0-9A-Fa-f]{1,4}){0,5}:((25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)(\\.(25[0-5]|2[0-4]\\d|1\\d\\d|[1-9]?\\d)){3}))|:)))(%.+)?$");
var IPV6_LOCAL_REGX = new RegExp("^([0]{1,4}::){1}[0-9A-Fa-f]{1,4}$");

function check_char_hex(charstr)
{
    charstr = charstr.toUpperCase();
    if(!(charstr >= 'A' && charstr <= 'F') && !(charstr >= '0' && charstr <= '9'))
    {
        return false;
    }
    return true;
}

function check_ipv6_symbol_num(str)
{
    if(str.indexOf("::") == -1)
        return IPV6_STR_ZERO_SYMBOL;
    if(str.indexOf("::") == str.lastIndexOf("::"))
        return IPV6_STR_ONE_SYMBOL;
    if(str.indexOf("::") != str.lastIndexOf("::"))
        return IPV6_STR_MORETHANTWO_SYMBOL;
}

function reserveIpa6Adar(addr, prefix)
{
    /*
        a. 2001:2::/48 (reserved for BMWG)
        b. 2001::/32 (reserved for TEREDO)
        c. 2002::/16 (reserved for 6to4)
        d. 2001:db8::/32 (reserved for Documentation)
        e. 2001:10::/28 (reserveed for IETF Protocol Assignment)
        f: 2001::/28 (reserver for IETF Protocol Assignment)
        g. 3ffe::/16 (reserved for 6bone)
    */
    var str = addr.toLowerCase() + "/" + prefix, invalid = 0,
            ary = [/^(2001:2::)\S+(48)$/, /^(2001::)\S+(32)$/, /^(2002::)\S+(16)$/, /^(2001:db8::)\S+(32)$/, /^(2001:10::)\S+(28)$/, /^(2001::)\S+(28)$/, /^(3ffe::)\S+(16)$/, /^\S+(::0)\/\d+$/];
    for(var i = 0; i < ary.length; i++)
    {
        if (ary[i].test(str)){
            invalid = 1;
        }
    }
    return invalid;
}

function checkIpAddrV6(obj)
{
    var ipv6array;
    var zero_count;
    var ipv6temp;
    var block_count;
    var sum;
    
    if(!/[23]/.test(obj.value[0]) || reserveIpa6Adar(obj.value, getByName('ipv6_subprefixleng').value) || check_ipv6_symbol_num(obj.value) == IPV6_STR_MORETHANTWO_SYMBOL)
    {
        return IPv6_INVALID_IP;
    }
    else if(check_ipv6_symbol_num(obj.value) == IPV6_STR_ZERO_SYMBOL)
    {
        ipv6array = obj.value.split(":");
        sum = 0;
        if(ipv6array.length == 8)
        {
            for(var i = 0; i < ipv6array.length; i++)
            {
                if(ipv6array[i].length > 4)
                    return IPv6_INVALID_IP;
                for(var j = 0; j < ipv6array[i].length; j++)
                {
                    if(!check_char_hex(ipv6array[i].charAt(j)))
                    {
                        return IPv6_1st_IP_ERROR + i;
                    }
                    sum += parseInt(ipv6array[i].charAt(j), 16);
                }
            }
            if(sum == 0)
            {
                return IPv6_ZERO_IP;
            }
        }
        else
        {
            return IPv6_INVALID_IP;
        }
    }
    else if(check_ipv6_symbol_num(obj.value) == IPV6_STR_ONE_SYMBOL)
    {
        ipv6array = obj.value.split("::");
        block_count = 0;
        sum = 0;
        if(ipv6array.length == 2)
        {
            for(var m = 0; m <= 1; m++)
            {
                ipv6temp = ipv6array[m].split(":");
                for(var n = 0; n < ipv6temp.length; n++)
                {
                    if(ipv6temp[n].length > 4)
                        return IPv6_INVALID_IP;
                    for(var p = 0; p < ipv6temp[n].length; p++)
                    {
                        if(!check_char_hex(ipv6temp[n].charAt(p)))
                        {
                            return IPv6_1st_IP_ERROR + block_count;
                        }
                        sum += parseInt(ipv6temp[n].charAt(p), 16);
                    }
                    block_count++;
                }
            }
            if(sum == 0)
            {
                return IPv6_ZERO_IP;
            }
        }
        else
        {
            return IPv6_INVALID_IP;
        }
    }
    if(obj.value.charAt(0) == 'f' || obj.value.charAt(0) == 'F')
    {
        if(obj.value.charAt(1) == 'f' || obj.value.charAt(1) == 'F')
        {
            return IPv6_MULTICAST_IP_ERROR;
        }
    }
    return IPv6_VALID_IP;
}

function checkIpAddrV6allowEmpty(obj)
{
    var ipv6array;
    var zero_count;
    var ipv6temp;
    var block_count;
    var sum;
    var empty=true;

    for ( var i = 0 ; i < obj.value.length ; i++ )
    {
        if(obj.value[i]!=" ")
            empty=false;
    }
    if(empty||obj.value.length==0)
        return IPv6_VALID_IP;

    if(!/[23]/.test(obj.value[0]) || reserveIpa6Adar(obj.value, getByName('ipv6_subprefixleng').value) || check_ipv6_symbol_num(obj.value) == IPV6_STR_MORETHANTWO_SYMBOL)
    {
        return IPv6_INVALID_IP;
    }
    else if(check_ipv6_symbol_num(obj.value) == IPV6_STR_ZERO_SYMBOL)
    {
        ipv6array = obj.value.split(":");
        sum = 0;
        if(ipv6array.length == 8)
        {
            for(var i = 0; i < ipv6array.length; i++)
            {
                if(ipv6array[i].length > 4)
                    return IPv6_INVALID_IP;
                for(var j = 0; j < ipv6array[i].length; j++)
                {
                    if(!check_char_hex(ipv6array[i].charAt(j)))
                    {
                        return IPv6_1st_IP_ERROR + i;
                    }
                    sum += parseInt(ipv6array[i].charAt(j), 16);
                }
            }
            if(sum == 0)
            {
                return IPv6_ZERO_IP;
            }
        }
        else
        {
            return IPv6_INVALID_IP;
        }
    }
    else if(check_ipv6_symbol_num(obj.value) == IPV6_STR_ONE_SYMBOL)
    {
        ipv6array = obj.value.split("::");
        block_count = 0;
        sum = 0;
        if(ipv6array.length == 2)
        {
            for(var m = 0; m <= 1; m++)
            {
                ipv6temp = ipv6array[m].split(":");
                for(var n = 0; n < ipv6temp.length; n++)
                {
                    if(ipv6temp[n].length > 4)
                        return IPv6_INVALID_IP;
                    for(var p = 0; p < ipv6temp[n].length; p++)
                    {
                        if(!check_char_hex(ipv6temp[n].charAt(p)))
                        {
                            return IPv6_1st_IP_ERROR + block_count;
                        }
                        sum += parseInt(ipv6temp[n].charAt(p), 16);
                    }
                    block_count++;
                }
            }
            if(sum == 0)
            {
                return IPv6_ZERO_IP;
            }
        }
        else
        {
            return IPv6_INVALID_IP;
        }
    }
    if(obj.value.charAt(0) == 'f' || obj.value.charAt(0) == 'F')
    {
        if(obj.value.charAt(1) == 'f' || obj.value.charAt(1) == 'F')
        {
            return IPv6_MULTICAST_IP_ERROR;
        }
    }
    return IPv6_VALID_IP;
}

function IPV6_ADDR_CHECK(obj)
{
    //alert("####IPV6_ADDR_CHECK 1: " + LANG_TOOLS_ALERT[45] + "   " + obj);  
    this.InvalidIP = LANG_TOOLS_ALERT[45];
    this.checkIPv6 = function(tag, allowzero)
    {
        var ERROR_NO = 0;
        if((ERROR_NO = checkIpAddrV6(obj)) != IPv6_VALID_IP)
        {
            //alert("IPV6_ADDR_CHECK 3");
            for(var i = IPv6_1st_IP_ERROR; i <= IPv6_8th_IP_ERROR;
                i++)
            {
                if(ERROR_NO == i)
                    alert(sprintf(LANG_IPV6_ALERT[ERROR_NO], tag));
            }
            if(ERROR_NO == IPv6_INVALID_IP || ERROR_NO == IPv6_MULTICAST_IP_ERROR)
                alert(sprintf(LANG_IPV6_ALERT[ERROR_NO], tag));
            if(typeof(allowzero) == "undefined" || allowzero == IPV6_ADDR_NOTALLOWZERO)
            {
                if(ERROR_NO == IPv6_ZERO_IP)
                    alert(sprintf(LANG_IPV6_ALERT[ERROR_NO], tag));
            }
            //alert("IPV6_ADDR_CHECK 4");
            obj.focus();
            return false;
        }
        if(!IPV6_REGX.test(obj.value))
        {
            alert(this.InvalidIP);
            obj.focus();
            return false;
        }
        if(IPV6_LOCAL_REGX.test(obj.value))
        {
            alert(this.InvalidIP);
            obj.focus();
            return false;
        }
        return true;
    }
    ;
    this.InvalidSuffix_hex = LANG_TOOLS_ALERT[46];
    this.InvalidSuffix = LANG_TOOLS_ALERT[47];
    this.check_ipv6_addr_suffix = function(tag)
    {
        if(obj.value.length > 0 && obj.value.length < 5)
        {
            for(var index = 0; index < obj.value.length;
                index++)
            {
                if(!check_char_hex(obj.value.charAt(index)))
                {
                    alert(sprintf(this.InvalidSuffix_hex, tag));
                    obj.focus();
                    return false;
                }
            }
        }
        else
        {
            alert(sprintf(this.InvalidSuffix, tag));
            obj.focus();
            return false;
        }
        return true;
    }
    ;
}


