function getElementFromTop(element) {
  return IsGameRouter() ? eval(element) : eval("top." + element);
}
function close_all_sub(click_name) {
  if (IsGameRouter())
    sub_list = "setup,usb,security,green,admin,advanced,moniter,plex_media";
  else var sub_list = "network,management,system";
  var sub_array = sub_list.split(",");
  for (i = 0; i < sub_array.length; i++) {
    var flag = 0,
      button_name = sub_array[i] + "_bt",
      sub_name = sub_array[i] + "_sub";
    if (sub_name != click_name) {
      var div_name = getElementFromTop("document").getElementById(button_name);
      if (!div_name) continue;
      for (
        var div_class_name = div_name.className.split(/\s+/), j = 0;
        j < div_class_name.length;
        j++
      )
        if (div_class_name[j].indexOf("advanced_grey_button") > -1) {
          flag = 1;
          break;
        }
      if (1 == flag) continue;
      settingClass(div_name, "advanced_white_close_button"),
        getElementFromTop("document").getElementById(sub_name) &&
          (getElementFromTop("document").getElementById(
            sub_name
          ).style.display = "none");
    }
  }
}
function open_sub(name) {
  var sub_name = name + "_sub";
  "none" == document.getElementById(sub_name).style.display &&
    open_or_close_sub(name);
}
function open_or_close_sub(name) {
  for (
    var button_name = name + "_bt",
      sub_name = name + "_sub",
      sub_exist = 0,
      flag = 0,
      div_class_name = getElementFromTop("document")
        .getElementById(button_name)
        .className.split(/\s+/),
      j = 0;
    j < div_class_name.length;
    j++
  )
    if (div_class_name[j].indexOf("advanced_grey_button") > -1) {
      flag = 1;
      break;
    }
  if (1 != flag) {
    if (getElementFromTop("document").getElementById(sub_name)) {
      var open_flag = getElementFromTop("document").getElementById(sub_name)
        .style.display;
      sub_exist = 1;
    }
    close_all_sub(sub_name);
    var button_div = getElementFromTop("document").getElementById(button_name);
    sub_exist && "none" == open_flag
      ? (settingClass(button_div, "advanced_white_open_button"),
        (getElementFromTop("document").getElementById(sub_name).style.display =
          ""),
        subItemsClass(sub_name),
        enabledItemsClass())
      : sub_exist
      ? (settingClass(button_div, "advanced_white_close_button"),
        (getElementFromTop("document").getElementById(sub_name).style.display =
          "none"))
      : -1 != button_div.className.indexOf("advanced_white_close_button")
      ? settingClass(button_div, "advanced_white_open_button")
      : settingClass(button_div, "advanced_white_close_button"),
      change_menu_height();
  }
}
function change_menu_height() {
  var is_double =
      "footer_double" == document.getElementById("footer").className,
    con_height = document.documentElement.clientHeight - 97,
    menu_height =
      document.getElementById("menu").clientHeight > 510
        ? document.getElementById("menu").clientHeight
        : 510;
  if (navigator.userAgent.indexOf("MSIE 9.0") > -1)
    document.getElementById("middle").style.minHeight = is_double
      ? menu_height + 87 + "px"
      : "0px";
  else if (isIE_or_Opera() && IE_version() < 9) {
    var height = is_double
      ? document.documentElement.clientHeight - 190
      : document.documentElement.clientHeight - 147;
    (menu_height = height > menu_height ? height : menu_height),
      (document.getElementById("container").style.height = is_double
        ? menu_height + 93 + "px"
        : con_height + "px"),
      (document.getElementById("middle").style.height = is_double
        ? menu_height + 87 + "px"
        : con_height - 9 + "px");
  }
  (document.getElementById("middle").style.minHeight = is_double
    ? menu_height + 87 + "px"
    : "0px"),
    menu_height > 510
      ? ((document.getElementById("middle").style.minHeight = is_double
          ? menu_height + 87 + "px"
          : "0px"),
        IsGameRouter() &&
          1 == isIE() &&
          (document.getElementById("middle").style.height =
            con_height + 94 + "px"))
      : 1 == isIE()
      ? IsGameRouter()
        ? ((document.getElementById("middle").style.minHeight = is_double
            ? menu_height + 87 + "px"
            : "0px"),
          (document.getElementById("middle").style.height = is_double
            ? menu_height + 87 + "px"
            : con_height + 94 + "px"))
        : (document.getElementById("middle").style.height = is_double
            ? menu_height + 87 + "px"
            : con_height - 9 + "px")
      : (document.getElementById("middle").style.minHeight = is_double
          ? menu_height + 87 + "px"
          : "0px");
}
function change_size() {
  setFooterClass();
  var is_double =
    "footer_double" == document.getElementById("footer").className;
  navigator.userAgent;
  if (isIE_or_Opera() && IE_version() < 9) {
    var width = document.documentElement.clientWidth - 40;
    (document.getElementById("top").style.width =
      width > 820 ? width : "820px"),
      (document.getElementById("container").style.width =
        width > 820 ? width : "820px"),
      (document.getElementById("formframe_div").style.width =
        width > 820 ? width - 195 : "625px");
  }
  (document.getElementById("formframe_div").style.bottom = is_double
    ? "88px"
    : "0px"),
    change_menu_height();
}
function settingClass(obj, class_name) {
  if (!obj)
    return;
  var height = obj.getElementsByTagName("span")[0].clientHeight;
  obj.className =
    height > 30
      ? class_name + "_triple"
      : height > 15
      ? class_name + "_double"
      : class_name;
}
function subItemsClass(argv) {
  var sub_menu, items, words_height, i, num;
  for (num = 0; num < arguments.length; num++)
    if (
      "none" !=
      (sub_menu = getElementFromTop("document").getElementById(arguments[num]))
        .style.display
    )
      for (
        items = sub_menu.getElementsByTagName("dt"), i = 0;
        i < items.length;
        i++
      )
        getElementFromTop("old_div") != items[i] &&
          ((words_height = items[i].getElementsByTagName("a")[0].clientHeight),
          (items[i].className =
            words_height > 28
              ? "long_name"
              : words_height > 14
              ? "middle_name"
              : "sub_back"));
}
function clickSubMenu(current_div, change_id) {
  if ("" != getTop(window).old_div) {
    var old_div_class = getTop(window).old_div.className;
    "sub_back_purple" == old_div_class || "sub_back_purple_usb" == old_div_class
      ? (getTop(window).old_div.className = "sub_back")
      : "sub_back_purple_double" == old_div_class ||
        "sub_back_purple_usb_double" == old_div_class
      ? (getTop(window).old_div.className = "middle_name")
      : "sub_back_purple_triple" == old_div_class &&
        (getTop(window).old_div.className = "long_name");
  }
  if ("0" != current_div) {
    var current_class = current_div.className;
    "sub_back" == current_class
      ? (current_div.className =
          "usb_bas" == change_id ||
          "usb_adv" == change_id ||
          "media" == change_id ||
          "userset" == change_id
            ? "sub_back_purple_usb"
            : "sub_back_purple")
      : "middle_name" == current_class
      ? (current_div.className =
          "usb_bas" == change_id ||
          "usb_adv" == change_id ||
          "media" == change_id ||
          "userset" == change_id
            ? "sub_back_purple_usb_double"
            : "sub_back_purple_double")
      : "long_name" == current_class &&
        (current_div.className = "sub_back_purple_triple"),
      (getTop(window).old_div = current_div);
  } else IsGameRouter() ? (old_div = "") : (top.old_div = "");
}
var array_name = [
    "wds_items",
    "ap_items",
    "bridge_items",
    "extender_items",
    "mapt_items",
    "devmode_items",
    "all_items",
    "sso_limit_items",
  ],
  enable_flags = [
    "enabled_wds",
    "enable_ap_flag",
    "enable_bridge_flag",
    "enable_extender_flag",
    "enable_mapt",
    "device_mode",
    "ookla_speedtest_flag",
    "sso_limit_access",
  ],
  wds_items = [
    "internet",
    "wan",
    "block_site",
    "block_services",
    "forwarding_triggering",
    "qos",
    "vpn",
    "ipsec_vpn",
    "dns",
    "static",
    "remote",
    "upnp",
    "traffic",
    "wl_bridge",
    "guest",
    "email",
    "schedule",
    "log",
  ],
  ap_items = [
    "internet",
    "wan",
    "block_site",
    "block_services",
    "forwarding_triggering",
    "qos",
    "vpn",
    "ipsec_vpn",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "lan",
    "ipv6",
    "parental",
    "vpn_client",
    "static",
    "schedule"
  ],
  extender_items = [
    "internet",
    "wan",
    "block_site",
    "block_services",
    "forwarding_triggering",
    "vpn",
    "ipsec_vpn",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "lan",
    "ipv6",
    "led",
    "fbwifi",
  ],
  bridge_items = [
    "internet",
    "wan",
    "block_site",
    "block_services",
    "forwarding_triggering",
    "qos",
    "vpn",
    "ipsec_vpn",
    "dns",
    "static",
    "remote",
    "upnp",
    "wladv",
    "traffic",
    "traffic_rule",
    "wireless",
    "guest",
    "lan",
    "parental",
    "access_control",
    "email",
    "schedule",
    "wds",
    "ipv6",
    "wlap",
    "vpn_client",
  ],
  mapt_items = ["internet"],
  devmode_items = [
    "internet",
    "wireless",
    "guest",
    "wan",
    "lan",
    "qos",
    "readyshare_stor",
    "usb_bas",
    "usb_adv",
    "media",
    "print",
    "vault",
    "block_site",
    "block_services",
    "schedule",
    "email",
    "wladv",
    "rae",
    "forwarding_triggering",
    "dns",
    "vpn",
    "ipsec_vpn",
    "static",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "ipv6",
    "parental",
    "access_control",
    "usb_set",
    "vlan",
    "multi_vlan",
    "led",
    "devname",
  ],
  all_items = [
    "internet",
    "wireless",
    "guest",
    "wan",
    "lan",
    "readyshare_stor",
    "usb_bas",
    "usb_adv",
    "cloud",
    "media",
    "print",
    "vault",
    "block_site",
    "block_services",
    "schedule",
    "email",
    "green_basic",
    "green_manager",
    "status",
    "log",
    "wladv",
    "wlap",
    "rae",
    "attached",
    "bak_set",
    "passwd",
    "upgrade",
    "forwarding_triggering",
    "dns",
    "vpn",
    "ipsec_vpn",
    "static",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "ipv6",
    "parental",
    "access_control",
    "usb_set",
    "vlan",
    "multi_vlan",
    "led",
    "devname",
    "devmode",
    "lacp",
    "vpn_client",
    "ntp",
  ],
  sso_limit_items = [
    "wireless",
    "wireless2",
    "wireless3",
    "guest",
    "wan",
    "lan",
    "readyshare_stor",
    "usb_bas",
    "usb_adv",
    "cloud",
    "media",
    "print",
    "vault",
    "block_site",
    "block_services",
    "schedule",
    "email",
    "green_basic",
    "green_manager",
    "wladv",
    "wlap",
    "rae",
    "attached",
    "passwd",
    "forwarding_triggering",
    "dns",
    "vpn",
    "ipsec_vpn",
    "static",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "ipv6",
    "parental",
    "access_control",
    "usb_set",
    "vlan",
    "led",
    "devname",
    "devmode",
    "lacp",
    "vpn_client",
    "ntp",
    "qos",
  ],
  game_router_array_name = [
    "game_router_wds_items",
    "game_router_ap_items",
    "game_router_bridge_items",
    "game_router_extender_items",
    "game_router_mapt_items",
    "game_router_devmode_items",
  ],
  game_router_enable_flags = [
    "enabled_wds",
    "enable_ap_flag",
    "enable_bridge_flag",
    "enable_extender_flag",
    "enable_mapt",
    "device_mode",
  ],
  game_router_wds_items = [
    "vlan",
    "multi_vlan",
    "internet",
    "adv_setup_wizard",
    "adv_wps",
    "wan",
    "block_site",
    "block_services",
    "forwarding",
    "triggering",
    "qos",
    "vpn",
    "ipsec_vpn",
    "dns",
    "static",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "guest",
    "email",
    "schedule",
    "log",
  ],
  game_router_ap_items = [
    "vpn_client",
    "vlan",
    "multi_vlan",
    "internet",
    "adv_setup_wizard",
    "wan",
    "block_site",
    "block_services",
    "forwarding",
    "triggering",
    "qos",
    "vpn",
    "ipsec_vpn",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "lan",
    "ipv6",
    "parental",
    "access_control",
    "conn_status",
  ],
  game_router_extender_items = [
    "vlan",
    "multi_vlan",
    "internet",
    "adv_setup_wizard",
    "wan",
    "block_site",
    "block_services",
    "forwarding",
    "triggering",
    "vpn",
    "ipsec_vpn",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "lan",
    "ipv6",
    "led",
    "fbwifi",
    "conn_status",
  ],
  game_router_bridge_items = [
    "vlan",
    "multi_vlan",
    "internet",
    "adv_setup_wizard",
    "adv_wps",
    "wan",
    "block_site",
    "block_services",
    "forwarding",
    "triggering",
    "qos",
    "vpn",
    "ipsec_vpn",
    "dns",
    "static",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wireless",
    "guest",
    "lan",
    "parental",
    "access_control",
    "email",
    "schedule",
    "wds",
    "ipv6",
    "wlap",
  ],
  game_router_mapt_items = ["internet", "adv_setup_wizard"],
  game_router_devmode_items = [
    "internet",
    "adv_setup_wizard",
    "adv_wps",
    "wireless",
    "guest",
    "wan",
    "lan",
    "qos",
    "readyshare_stor",
    "usb_bas",
    "usb_adv",
    "media",
    "print",
    "vault",
    "block_site",
    "block_services",
    "schedule",
    "email",
    "wladv",
    "rae",
    "forwarding",
    "triggering",
    "dns",
    "vpn",
    "ipsec_vpn",
    "static",
    "remote",
    "upnp",
    "traffic",
    "traffic_rule",
    "wl_bridge",
    "ipv6",
    "parental",
    "access_control",
    "usb_set",
    "vlan",
    "multi_vlan",
    "led",
    "devname",
    "plex_media",
  ];
function enabledItemsClass() {
  var i, j, enable_flag, larray;
  for (
    larray = IsGameRouter() ? game_router_array_name.length : array_name.length,
      i = 0;
    i < larray;
    i++
  ) {
    var item_group = [];
    for (
      IsGameRouter()
        ? ((enable_flag = eval("" + game_router_enable_flags[i])),
          (item_group = eval(game_router_array_name[i])))
        : ((enable_flag = eval("top." + enable_flags[i])),
          (item_group = eval(array_name[i]))),
        j = 0;
      j < item_group.length;
      j++
    ) {
      var cur_div = getElementFromTop("document").getElementById(item_group[j]);
      if (cur_div) {
        var height = cur_div.getElementsByTagName("a")[0].clientHeight;
        if ("none" == cur_div.style.display) break;
        ("1" == enable_flag ||
          ("admin" != master && "upgrade" == item_group[j])) &&
          (IsGameRouter()
            ? (cur_div.className = "middle_grey")
            : ((38 != height && 52 != height) || (height -= 10),
              (cur_div.className =
                height > 28
                  ? "long_grey"
                  : height > 14
                  ? "middle_grey"
                  : "sub_grey")));
      }
    }
  }
  if (1 == top.have_lte_flag) {
    var cur_div = getElementFromTop("document").getElementById(
        "mobile_internet"
      ),
      cur_div_1 = getElementFromTop("document").getElementById("internet"),
      height = cur_div.getElementsByTagName("a")[0].clientHeight,
      height_1 = cur_div_1.getElementsByTagName("a")[0].clientHeight;
    "AutoDetc" == top.broadband_wan_type
      ? (cur_div.className =
          height > 28 ? "long_grey" : height > 14 ? "middle_grey" : "sub_grey")
      : (cur_div.className =
          height > 28 ? "long_name" : height > 14 ? "middle_name" : "sub_back"),
      "MyDetc" == top.broadband_wan_type
        ? (cur_div_1.className =
            height_1 > 28
              ? "long_grey"
              : height_1 > 14
              ? "middle_grey"
              : "sub_grey")
        : (cur_div_1.className =
            height_1 > 28
              ? "long_name"
              : height_1 > 14
              ? "middle_name"
              : "sub_back");
  }
  IsGameRouter() &&
    ("static" == wan_type &&
      (document.getElementById("conn_status").className = "middle_grey"),
    0 == enabled_wps &&
      (document.getElementById("adv_wps").className = "middle_grey"));
}
function menu_class_default() {
  IsGameRouter() ? menu_class_default2() : menu_class_default1();
}
function menu_class_default2() {
  var menu_div,
    last_div,
    i,
    extensible_items = [
      "setup_bt",
      "usb_bt",
      "security_bt",
      "green_bt",
      "admin_bt",
      "advanced_bt",
      "moniter_bt",
      "plex_media_bt",
    ];
  for (
    (void 0 !== (last_div = top.old_div) && "" != last_div) ||
      ((menu_div = document.getElementById("internet")).className =
        "middle_name"),
      i = 0;
    i < extensible_items.length;
    i++
  )
    (menu_div = document.getElementById(extensible_items[i])) &&
      settingClass(menu_div, "advanced_white_close_button");
  enabledItemsClass();
}
function menu_class_default1() {
  var menu_div;
  settingClass(
    (menu_div = top.document.getElementById("adv_home")),
    "advanced_black_button"
  ),
    1 != top.have_lte_flag &&
      ((menu_div = top.document.getElementById("adv_setup_wizard")),
      "admin" != master ||
      1 == top.enabled_wds ||
      1 == top.enable_ap_flag ||
      1 == top.enable_bridge_flag ||
      "1" == top.enable_extender_flag ||
      "1" == top.device_mode
        ? settingClass(menu_div, "advanced_grey_button")
        : settingClass(menu_div, "advanced_black_button")),
    1 == top.have_wifi_flag &&
      ((menu_div = top.document.getElementById("adv_wps")),
      1 == top.enabled_wps &&
      0 == top.enabled_wds &&
      0 == top.enable_bridge_flag &&
      "1" != top.device_mode &&
      1 != top.sso_limit_access
        ? settingClass(menu_div, "advanced_black_button")
        : settingClass(menu_div, "advanced_grey_button"));
  var i,
    extensible_items = [
      "setup_bt",
      "usb_bt",
      "security_bt",
      "green_bt",
      "admin_bt",
      "advanced_bt",
    ];
  for (i = 0; i < extensible_items.length; i++)
    (menu_div = top.document.getElementById(extensible_items[i])) &&
      (1 == top.sso_limit_access
        ? settingClass(
            menu_div,
            "setup_bt" == extensible_items[i] ||
              "admin_bt" == extensible_items[i]
              ? "advanced_white_close_button"
              : "advanced_grey_button"
          )
        : settingClass(menu_div, "advanced_white_close_button"));
  enabledItemsClass();
}
function menu_color_change(change_id) {
  menu_class_default();
  var current_div = getElementFromTop("document").getElementById(change_id),
    change = 0;
  if (
    (IsGameRouter()
      ? "adv_home" == change_id && (change = 1)
      : ("adv_home" != change_id &&
          "adv_setup_wizard" != change_id &&
          "adv_wps" != change_id) ||
        (change = 1),
    change)
  )
    settingClass(current_div, "advanced_purple_button"),
      clickSubMenu(0, change_id);
  else {
    var btn_id = getElementFromTop("document")
      .getElementById(change_id)
      .parentNode.parentNode.id.replace("sub", "bt");
    settingClass(
      getElementFromTop("document").getElementById(btn_id),
      "advanced_white_open_button"
    ),
      clickSubMenu(current_div, change_id);
  }
}

function click_adv_action(id) {
  if (id == "basic") {
    menu_color_change("basic");
    goto_formframe("network.htm");
  } else if (id == "wireless") {
    menu_color_change("wireless");
    goto_formframe("wifi_Setting.htm");
  } else if (id == "advanced") {
    menu_color_change("advanced");
    goto_formframe("advanced.htm");
  } else if (id == "timezone") {
    menu_color_change("timezone");
    goto_formframe("time_zone.htm");
  } else if (id == "wifi_scheduler") {
    menu_color_change("wifi_scheduler");
    goto_formframe("wifi_schedule.htm");
  } else if (id == "tools") {
    menu_color_change("tools");
    goto_formframe("diagnostics.htm");
  } else if (id == "account") {
    menu_color_change("account");
    goto_formframe("account.htm");
  } else if (id == "firmware") {
    menu_color_change("firmware");
    goto_formframe("flashops.htm");
  } else if (id == "backup_settings") {
    menu_color_change("backup_settings");
    goto_formframe("backup_settings.htm");
  } else if (id == "log") {
    menu_color_change("log");
    goto_formframe("syslog.htm");
  }
  change_menu_height();
}

// 220
// function click_adv_action(id) {
//   if (
//     ((setup_wizard_flag = "adv_setup_wizard" == id ? 1 : 0),
//     (page_id = id),
//     1 == enable_action)
//   ) {
//     var larray;
//     larray = IsGameRouter() ? game_router_array_name.length : array_name.length;
//     for (var i = 0; i < larray; i++) {
//       var item_group;
//       if (IsGameRouter())
//         var enable_flag = eval("" + game_router_enable_flags[i]),
//           item_group = eval(game_router_array_name[i]);
//       else
//         var enable_flag = eval("top." + enable_flags[i]),
//           item_group = eval(array_name[i]);
//       for (var j = 0; j < item_group.length; j++)
//         if (item_group[j] == id && 1 == enable_flag) {
//           id = "NOTACTIVE";
//           break;
//         }
//       if ("NOTACTIVE" == id) break;
//     }
//     IsGameRouter() &&
//       "static" == wan_type &&
//       "conn_status" == id &&
//       (id = "NOTACTIVE"),
//       "adv_home" == id
//         ? (menu_color_change("adv_home"),
//           "1" == enable_bridge_flag
//             ? goto_formframe("RST_bridge_status.htm")
//             : goto_formframe("RST_status.htm"))
//         : "adv_setup_wizard" == id &&
//           "admin" == master &&
//           "1" != getElementFromTop("enable_ap_flag") &&
//           "1" != getElementFromTop("enabled_wds") &&
//           "1" != getElementFromTop("enable_bridge_flag") &&
//           "1" != getElementFromTop("enable_extender_flag") &&
//           "1" != getElementFromTop("device_mode")
//         ? (menu_color_change("adv_setup_wizard"),
//           "1" == getElementFromTop("dsl_enable_flag")
//             ? goto_formframe("DSL_WIZ_sel.htm")
//             : (("WW" == getElementFromTop("netgear_region").toUpperCase() ||
//                 "" == getElementFromTop("netgear_region")) &&
//                 "Russian" == getElementFromTop("gui_region")) ||
//               "RU" == getElementFromTop("netgear_region").toUpperCase()
//             ? goto_formframe("RU_WIZ_sel.htm")
//             : goto_formframe("WIZ_sel.htm"))
//         : "adv_wps" == id &&
//           "1" == getElementFromTop("enabled_wps") &&
//           "1" != getElementFromTop("enabled_wds") &&
//           "1" != getElementFromTop("enable_bridge_flag") &&
//           "1" != getElementFromTop("device_mode") &&
//           1 != getElementFromTop("sso_limit_access")
//         ? (goto_formframe("Add_WPS_Client.htm"), menu_color_change("adv_wps"))
//         : "internet" == id
//         ? 1 == getTop(window).support_internet_lables_flag &&
//           "ipv6" == parent.internet_label
//           ? (goto_formframe("IPv6_index.htm"), menu_color_change("internet"))
//           : (1 == getElementFromTop("have_lte_flag") &&
//               "MyDetc" == getElementFromTop("broadband_wan_type")) ||
//             (0 == getElementFromTop("dsl_enable_flag")
//               ? goto_formframe("BAS_basic.htm")
//               : goto_formframe("BAS_basic_dsl.htm"),
//             menu_color_change("internet"))
//         : "wireless" == id || "wireless2" == id || "wireless3" == id
//         ? (goto_formframe("WLG_wireless.htm"), menu_color_change("wireless"))
//         : "guest" == id
//         ? (goto_formframe("WLG_wireless_guest1.htm"),
//           menu_color_change("guest"))
//         : "wan" == id
//         ? (goto_formframe("WAN_wan.htm"), menu_color_change("wan"))
//         : "lan" == id
//         ? (goto_formframe("LAN_lan.htm"), menu_color_change("lan"))
//         : "qos" == id
//         ? (IsGameRouter() || "1" != top.trend_micro_qos
//             ? "1" == getElementFromTop("have_advanced_qos")
//               ? goto_formframe("QOS_wait.htm")
//               : IsGameRouter() || "1" != top.trend_micro_flag
//               ? goto_formframe("QOS_dynamic.htm")
//               : (please_wait(!1),
//                 (top.formframe.location.href = "new_waiting_page.htm"))
//             : (please_wait(!1),
//               (top.formframe.location.href = "new_waiting_page.htm")),
//           menu_color_change("qos"))
//         : "usb_bas" == id
//         ? (goto_formframe("USB_basic.htm"), menu_color_change("usb_bas"))
//         : "usb_adv" == id
//         ? (goto_formframe("USB_advanced.htm"), menu_color_change("usb_adv"))
//         : "userset" == id
//         ? (goto_formframe("hdd_usr_setup.htm"), menu_color_change("userset"))
//         : "media" == id
//         ? (goto_formframe("UPNP_media.htm"), menu_color_change("media"))
//         : "plex_media" == id
//         ? (goto_formframe("plex_media.htm"), open_or_close_sub("plex_media"))
//         : "cloud" == id
//         ? (goto_formframe("RMT_invite.htm"), menu_color_change("cloud"))
//         : "print" == id
//         ? (goto_formframe("RMT_print.htm"), menu_color_change("print"))
//         : "vault" == id
//         ? (goto_formframe("RMT_vault.htm"), menu_color_change("vault"))
//         : "mobile" == id
//         ? (goto_formframe("BAS_mobile.htm"), menu_color_change("mobile"))
//         : "amazon" == id
//         ? (goto_formframe("goto_Netdisk.htm"), menu_color_change("amazon"))
//         : "parental" == id
//         ? (open_window("parental_ctrl.htm"), menu_color_change("parental"))
//         : "block_site" == id
//         ? (goto_formframe("BKS_keyword.htm"), menu_color_change("block_site"))
//         : "block_services" == id
//         ? (goto_formframe("BKS_service.htm"),
//           menu_color_change("block_services"))
//         : "schedule" == id
//         ? (goto_formframe("FW_schedule.htm"), menu_color_change("schedule"))
//         : "email" == id
//         ? (goto_formframe("FW_email.htm"), menu_color_change("email"))
//         : "ipmac" == id
//         ? (goto_formframe("ipmac.htm"), menu_color_change("ipmac"))
//         : "status" == id
//         ? (1 == getElementFromTop("have_lte_flag")
//             ? goto_formframe("get_mobile_status.html")
//             : "1" == enable_bridge_flag
//             ? goto_formframe("RST_bridge_status.htm")
//             : goto_formframe("RST_status.htm"),
//           menu_color_change("status"))
//         : "log" == id
//         ? (goto_formframe("FW_log.htm"), menu_color_change("log"))
//         : "attached" == id
//         ? 1 == getElementFromTop("have_dynamic_qos") ||
//           1 == getElementFromTop("use_orbi_style_flag")
//           ? (goto_formframe("QOS_device.htm"), menu_color_change("attached"))
//           : (goto_formframe("DEV_device.htm"), menu_color_change("attached"))
//         : "bak_set" == id
//         ? (goto_formframe("BAK_backup.htm"), menu_color_change("bak_set"))
//         : "passwd" == id
//         ? (goto_formframe("PWD_password.htm"), menu_color_change("passwd"))
//         : "upgrade" == id && "admin" == master
//         ? (goto_formframe("UPG_upgrade.htm"), menu_color_change("upgrade"))
//         : "plc" == id
//         ? (goto_formframe("PLC_wait_scan.htm"), menu_color_change("plc"))
//         : "wladv" == id
//         ? (goto_formframe("WLG_adv.htm"), menu_color_change("wladv"))
//         : "wlap" == id
//         ? (goto_formframe("WLG_wap.htm"), menu_color_change("wlap"))
//         : "wl_bridge" == id
//         ? (goto_formframe("WLG_bridge.htm"), menu_color_change("wl_bridge"))
//         : "wds" == id
//         ? (goto_formframe("WLG_wds.htm"), menu_color_change("wds"))
//         : IsGameRouter() || "forwarding_triggering" != id
//         ? IsGameRouter() && "forwarding" == id
//           ? (goto_formframe("forwarding.htm"), menu_color_change("forwarding"))
//           : IsGameRouter() && "triggering" == id
//           ? (goto_formframe("triggering.htm"), menu_color_change("triggering"))
//           : "dns" == id
//           ? (goto_formframe("DNS_ddns.htm"), menu_color_change("dns"))
//           : "static" == id
//           ? (goto_formframe("STR_routes.htm"), menu_color_change("static"))
//           : "remote" == id
//           ? (goto_formframe("FW_remote.htm"), menu_color_change("remote"))
//           : "usb_set" == id
//           ? (goto_formframe("USB_settings.htm"), menu_color_change("usb_set"))
//           : "upnp" == id
//           ? (goto_formframe("UPNP_upnp.htm"), menu_color_change("upnp"))
//           : "ipv6" == id
//           ? (goto_formframe("IPv6_index.htm"), menu_color_change("ipv6"))
//           : "tr069" == id
//           ? (goto_formframe("tr069.htm"), menu_color_change("tr069"))
//           : "traffic" == id
//           ? (goto_formframe("traffic.htm"), menu_color_change("traffic"))
//           : "traffic_rule" == id
//           ? (goto_formframe("traffic_rules.htm"),
//             menu_color_change("traffic_rule"))
//           : "green_basic" == id
//           ? (goto_formframe("green_download.htm"), menu_color_change(id))
//           : "green_manager" == id
//           ? ("emule" == download_type
//               ? goto_formframe("GREEN_emule_basic.htm")
//               : "http" == download_type
//               ? goto_formframe("GREEN_http_basic.htm")
//               : goto_formframe("GREEN_bt_basic.htm"),
//             menu_color_change(id))
//           : "lte_broadband" == id && 1 == getElementFromTop("have_lte_flag")
//           ? (goto_formframe("BAS_lte_broadband.htm"), menu_color_change(id))
//           : "mobile_internet" == id &&
//             "AutoDetc" != getElementFromTop("broadband_wan_type")
//           ? (IsGameRouter() ? (click_lte_sim = 0) : (top.click_lte_sim = 0),
//             goto_formframe("check_mobile_internet_wait.htm"),
//             menu_color_change(id))
//           : "sim" == id
//           ? (IsGameRouter() ? (click_lte_sim = 1) : (top.click_lte_sim = 1),
//             goto_formframe("check_sim_wait.htm"),
//             menu_color_change(id))
//           : "mobile_upg" == id
//           ? (goto_formframe("UPG_module.htm"), menu_color_change(id))
//           : "access_control" == id
//           ? (goto_formframe("access_control.htm"),
//             menu_color_change("access_control"))
//           : "led" == id
//           ? (goto_formframe("LED_control_setting.htm"),
//             menu_color_change("led"))
//           : "vpn" == id
//           ? (getElementFromTop("vpn_smartphone_flag")
//               ? goto_formframe("openvpn_service.htm")
//               : goto_formframe("vpn_service.htm"),
//             menu_color_change("vpn"))
//           : "pptp_vpn" == id
//           ? (goto_formframe("vpn_pptp.htm"), menu_color_change(id))
//           : "ipsec_vpn" == id
//           ? (goto_formframe("ipsec_vpn.htm"), menu_color_change(id))
//           : "fbwifi" == id
//           ? (goto_formframe("fbwifi.htm"), menu_color_change("fbwifi"))
//           : "lacp" == id
//           ? (goto_formframe("LACP_setting.htm"), menu_color_change("lacp"))
//           : "rae" == id
//           ? (goto_formframe("rae_main.htm"), menu_color_change("rae"))
//           : "vlan" == id
//           ? (goto_formframe("VLAN_IPTV.htm"), menu_color_change("vlan"))
//           : "multi_vlan" == id
//           ? (goto_formframe("redirect_vlan.htm"),
//             menu_color_change("multi_vlan"))
//           : "devname" == id
//           ? (goto_formframe("edit_device_name.htm"),
//             menu_color_change("devname"))
//           : "priozone" == id
//           ? (goto_formframe("priority_zone.htm"), menu_color_change("priozone"))
//           : "devmode" == id
//           ? (goto_formframe("device_mode_setting.htm"),
//             menu_color_change("devmode"))
//           : "ntp" == id
//           ? (goto_formframe("NTP_debug.htm"), menu_color_change("ntp"))
//           : "vpn_client" == id && "1" == getElementFromTop("vpn_client_flag")
//           ? (goto_formframe("vpn_client.htm"), menu_color_change("vpn_client"))
//           : IsGameRouter() && "statistics" == id
//           ? (goto_formframe("RST_statistic.htm", !1),
//             menu_color_change("statistics"))
//           : IsGameRouter() && "reboot" == id
//           ? (goto_formframe("FW_reboot.htm", !1), menu_color_change(id))
//           : IsGameRouter() && "conn_status" == id
//           ? (goto_formframe("Change_RST_status.htm", !1),
//             menu_color_change("conn_status"))
//           : "reg_key" == id &&
//             (goto_formframe("registration_key.htm"),
//             menu_color_change("reg_key"))
//         : (goto_formframe("FW_forward.htm"),
//           menu_color_change("forwarding_triggering"));
//   }
//   change_menu_height();
// }

function setFooterClass() {
  var footer_div = document.getElementById("footer"),
    go_btn = document.getElementById("search_button");
  (content_len = go_btn.value.length),
    content_len >= 7
      ? (go_btn.className = go_btn.className + "_long")
      : content_len >= 4
      ? (go_btn.className = go_btn.className + "_middle")
      : (go_btn.className = go_btn.className);
  var width =
      document.getElementById("support").clientWidth +
      document.getElementById("search").clientWidth,
    screen_width = document.documentElement.clientWidth;
  footer_div.className = width < screen_width - 60 ? "footer" : "footer_double";
}
