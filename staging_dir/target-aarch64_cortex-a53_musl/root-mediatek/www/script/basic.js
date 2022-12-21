function change_size() {
  setFooterClass();
  var is_double =
      "footer_double" == document.getElementById("footer").className,
    height = (navigator.userAgent, document.documentElement.clientHeight - 97);
  if (isIE_or_Opera() && IE_version() < 9) {
    (height > 560 && !is_double) || (height > 603 && is_double)
      ? ((document.getElementById("container").style.height = height),
        (document.getElementById("middle").style.height = height - 5),
        (document.getElementById("menu").style.height = is_double
          ? height - 93
          : height - 50))
      : ((document.getElementById("container").style.height = is_double
          ? "603px"
          : height),
        (document.getElementById("middle").style.height = is_double
          ? "598px"
          : height - 9),
        (document.getElementById("menu").style.height = "410px"));
    var width = document.documentElement.clientWidth - 40;
    (document.getElementById("top").style.width =
      width > 820 ? width : "820px"),
      (document.getElementById("container").style.width =
        width > 820 ? width : "820px"),
      (document.getElementById("formframe_div").style.width =
        width > 820 ? width - 195 : "625px");
  }
  1 == isIE()
    ? (document.getElementById("middle").style.height = is_double
        ? "598px"
        : height - 9 + "px")
    : (document.getElementById("middle").style.minHeight = is_double
        ? "598px"
        : height - 5),
    (document.getElementById("formframe_div").style.bottom = is_double
      ? "88px"
      : "0px");
}
function close_all_sub(click_name) {
  var sub_list = "internet",
    button_name = sub_list + "_bt",
    sub_name = sub_list + "_sub";
  sub_name != click_name &&
    (settingClass(
      getTop(window).document.getElementById(button_name),
      "advanced_white_close_button"
    ),
    (getTop(window).document.getElementById(sub_name).style.display = "none"));
}
function open_or_close_sub(name) {
  var button_name = name + "_bt",
    sub_name = name + "_sub",
    open_flag = getTop(window).document.getElementById(sub_name).style.display;
  close_all_sub(sub_name);
  var button_div = getTop(window).document.getElementById(button_name);
  "none" == open_flag
    ? (settingClass(button_div, "advanced_white_open_button"),
      (getTop(window).document.getElementById(sub_name).style.display = ""),
      subItemsClass(sub_name),
      enabledItemsClass_basic())
    : (settingClass(button_div, "advanced_white_close_button"),
      (getTop(window).document.getElementById(sub_name).style.display =
        "none"));
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
function basic_menu_class_default() {
  var i,
    menu_div = getTop(window).document.getElementById("menu"),
    menu_btns = menu_div.getElementsByTagName("div");
  for (i = 0; i < menu_btns.length; i++)
    if (
      1 != getTop(window).have_broadband ||
      (1 != getTop(window).is_ru_version &&
        1 != getTop(window).is_pr_version) ||
      2 != i
    ) {
      (1 != getTop(window).enable_bridge_flag &&
        1 != getTop(window).enabled_wds &&
        1 != getTop(window).enable_ap_flag &&
        "MyDetc" != getTop(window).broadband_mode &&
        "1" != getTop(window).enable_extender_flag &&
        1 != getTop(window).enable_mapt &&
        "1" != getTop(window).device_mode) ||
        2 != i ||
        set_menu_grey("internet");
      var height = menu_btns[i].getElementsByTagName("span")[0].clientHeight;
      "market" == menu_btns[i].id
        ? (menu_btns[i].className =
            height > 30
              ? "basic_button_big_green"
              : height > 16
              ? "basic_button_mid_green"
              : "basic_button_green")
        : (menu_btns[i].className =
            height > 32
              ? "basic_button_big"
              : height > 16
              ? "basic_button_mid"
              : "basic_button");
    } else
      settingClass(
        (menu_div = getTop(window).document.getElementById("internet_bt")),
        "advanced_white_close_button"
      );
  if (1 == getTop(window).sso_limit_access)
    return (
      set_menu_grey("attached"),
      set_menu_grey("intqos"),
      set_menu_grey("parental"),
      set_menu_grey("guest"),
      set_menu_grey("wireless"),
      set_menu_grey("readyshare"),
      set_menu_grey("vpn_client"),
      void set_menu_grey("funjsq")
    );
  (1 != getTop(window).enable_ap_flag &&
    1 != getTop(window).enable_bridge_flag &&
    "1" != getTop(window).enable_extender_flag &&
    "1" != getTop(window).device_mode) ||
    1 != getTop(window).have_dynamic_qos ||
    set_menu_grey("intqos"),
    (1 != getTop(window).enable_ap_flag &&
      1 != getTop(window).enable_bridge_flag &&
      "1" != getTop(window).enable_extender_flag &&
      "1" != getTop(window).device_mode) ||
      set_menu_grey("parental"),
    (1 != getTop(window).enabled_wds &&
      1 != getTop(window).enable_bridge_flag &&
      "1" != getTop(window).enable_extender_flag &&
      "1" != getTop(window).device_mode) ||
      set_menu_grey("guest"),
    (1 != getTop(window).enable_bridge_flag &&
      "1" != getTop(window).device_mode) ||
      set_menu_grey("wireless"),
    "1" == getTop(window).device_mode && set_menu_grey("readyshare"),
    (1 != getTop(window).enable_ap_flag &&
      1 != getTop(window).enable_bridge_flag) ||
      set_menu_grey("vpn_client"),
    1 != getTop(window).funjsq_flag ||
      (1 != getTop(window).enable_ap_flag &&
        1 != getTop(window).enable_bridge_flag &&
        "1" != getTop(window).enable_extender_flag) ||
      "Chinese" != getTop(window).gui_region ||
      "PR" != getTop(window).netgear_region ||
      set_menu_grey("funjsq");
}
function set_menu_grey(id) {
  var obj = getTop(window).document.getElementById(id);
  obj && (obj.className = obj.className + "_grey");
}
function subItemsClass(argv) {
  var sub_menu, items, words_height, i, num;
  for (num = 0; num < arguments.length; num++)
    if (
      "none" !=
      (sub_menu = getTop(window).document.getElementById(arguments[num])).style
        .display
    )
      for (
        items = sub_menu.getElementsByTagName("dt"), i = 0;
        i < items.length && getTop(window).old_div != items[i];
        i++
      )
        (words_height = items[i].getElementsByTagName("a")[0].clientHeight),
          (items[i].className =
            words_height > 28
              ? "long_name"
              : words_height > 14
              ? "middle_name"
              : "sub_back");
}
function enabledItemsClass_basic() {
  var cur_div = getTop(window).document.getElementById("3g"),
    cur_div_1 = getTop(window).document.getElementById("ethernet");
  if (
    1 != getTop(window).have_broadband ||
    (1 != getTop(window).is_pr_version && 1 != getTop(window).is_ru_version)
  ) {
    height = cur_div.getElementsByTagName("a")[0].clientHeight;
    cur_div.className =
      height > 28 ? "long_name" : height > 14 ? "middle_name" : "sub_back";
  } else {
    var height = cur_div.getElementsByTagName("a")[0].clientHeight;
    "AutoDetc" == getTop(window).broadband_mode
      ? (cur_div.className =
          height > 28 ? "long_grey" : height > 14 ? "middle_grey" : "sub_grey")
      : (cur_div.className =
          height > 28 ? "long_name" : height > 14 ? "middle_name" : "sub_back");
    var height_1 = cur_div_1.getElementsByTagName("a")[0].clientHeight;
    1 == getTop(window).enabled_wds ||
    1 == getTop(window).enable_ap_flag ||
    "1" == getTop(window).enable_extender_flag
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
}
function clickSubMenu(clicked_item) {
  if ("" != getTop(window).old_div) {
    var old_div_class = getTop(window).old_div.className;
    "sub_back_purple" == old_div_class
      ? (getTop(window).old_div.className = "sub_back")
      : "sub_back_purple_double" == old_div_class
      ? (getTop(window).old_div.className = "middle_name")
      : "sub_back_purple_triple" == old_div_class &&
        (getTop(window).old_div.className = "long_name");
  }
  if ("0" != clicked_item) {
    var current_class = clicked_item.className;
    "sub_back" == current_class
      ? (clicked_item.className = "sub_back_purple")
      : "middle_name" == current_class
      ? (clicked_item.className = "sub_back_purple_double")
      : "long_name" == current_class &&
        (clicked_item.className = "sub_back_purple_triple"),
      (getTop(window).old_div = clicked_item);
  } else getTop(window).old_div = "";
}
function basic_menu_color_change(change_id) {
  basic_menu_class_default();
  var clicked_item = getTop(window).document.getElementById(change_id);
  if (
    "broadband" == change_id ||
    "ethernet" == change_id ||
    "3g" == change_id
  ) {
    var btn_id = getTop(window)
      .document.getElementById(change_id)
      .parentNode.parentNode.id.replace("sub", "bt");
    settingClass(
      getTop(window).document.getElementById(btn_id),
      "advanced_white_open_button"
    ),
      clickSubMenu(clicked_item);
  } else
    (clicked_item.className = clicked_item.className + "_purple"),
      clickSubMenu(clicked_item);
}

function click_action(id) {
  //console.log("click_action:", id);
  if (id == 'device_status') {
    return basic_menu_color_change("device_status"), goto_formframe("device_status.htm");
  } else if (id == 'connections') {
    return basic_menu_color_change("connections"), goto_formframe("wireless_connections.htm");
  } else if (id == 'realtime') {
    return basic_menu_color_change("realtime"), goto_formframe("load.htm");
  }

  return;
}

// function click_action(id) {
//   if (getTop(window).page_id = id, enable_action) {
//     if (1 == getTop(window).sso_limit_access && "home" != id && "internet" != id && "no_internet" != id) return;
//     (function () {
//       if ("home" == id) {
//         return basic_menu_color_change("home"), goto_formframe("basic_home.htm");
//       }

//       return function () {
//         if ("internet" == id && 0 == getTop(window).enabled_wds && 1 != getTop(window).enable_ap_flag && "MyDetc" != getTop(window).broadband_mode && 0 == getTop(window).enable_bridge_flag && "1" != getTop(window).enable_extender_flag && 1 != getTop(window).enable_mapt && "1" != getTop(window).device_mode) {
//           return function () {
//             if (1 == getTop(window).support_internet_lables_flag && "ipv6" == parent.internet_label) {
//               return basic_menu_color_change("internet"), goto_formframe("IPv6_index.htm");
//             }

//             return function () {
//               if (1 != getTop(window).have_broadband || 1 != getTop(window).is_ru_version && 1 != getTop(window).is_pr_version) {
//                 return basic_menu_color_change("internet"), function () {
//                   if (0 == getTop(window).dsl_enable_flag) {
//                     return goto_formframe("BAS_basic.htm");
//                   }

//                   return goto_formframe("BAS_basic_dsl.htm");
//                 }();
//               }

//               return open_or_close_sub("internet"), basic_menu_color_change("ethernet"), function () {
//                 if (0 == getTop(window).dsl_enable_flag) {
//                   return goto_formframe("BAS_basic.htm");
//                 }

//                 return goto_formframe("BAS_basic_dsl.htm");
//               }();
//             }();
//           }();
//         }

//         return function () {
//           if ("broadband" == id && 1 == getTop(window).have_broadband) {
//             return basic_menu_color_change("broadband"), goto_formframe("BAS_broadband.htm");
//           }

//           return function () {
//             if ("ethernet" == id && 1 == getTop(window).have_broadband && 0 == getTop(window).enabled_wds && 1 != getTop(window).enable_ap_flag) {
//               return basic_menu_color_change("ethernet"), function () {
//                 if (0 == getTop(window).dsl_enable_flag) {
//                   return goto_formframe("BAS_basic.htm");
//                 }

//                 return goto_formframe("BAS_basic_dsl.htm");
//               }();
//             }

//             return function () {
//               if ("3g" == id && 1 == getTop(window).have_broadband && "AutoDetc" != getTop(window).broadband_mode) {
//                 return basic_menu_color_change("3g"), goto_formframe("BAS_3g.htm");
//               }

//               return function () {
//                 if ("wireless" == id && 0 == getTop(window).enable_bridge_flag && "1" != getTop(window).device_mode) {
//                   return basic_menu_color_change("wireless"), function () {
//                     if (1 == getTop(window).three_ssid_flag) {
//                       return goto_formframe("WLG_wireless.htm");
//                     }

//                     return function () {
//                       if ("1" == endis_wl_radio || "1" == endis_wla_radio || "1" == getTop(window).tri_router_flag && "1" == endis_wla_2nd_radio) {
//                         return goto_formframe("WLG_wireless.htm");
//                       }

//                       return goto_formframe("WLG_adv.htm");
//                     }();
//                   }();
//                 }

//                 return function () {
//                   if ("wireless1" != id && "wireless2" != id && "wireless3" != id || 0 != getTop(window).enable_bridge_flag || "1" == getTop(window).device_mode) {
//                     return function () {
//                       if ("attached" == id) {
//                         return function () {
//                           if (1 == getTop(window).have_dynamic_qos || 1 == getTop(window).use_orbi_style_flag) {
//                             return basic_menu_color_change("attached"), goto_formframe("QOS_device.htm");
//                           }

//                           return basic_menu_color_change("attached"), goto_formframe("DEV_device.htm");
//                         }();
//                       }

//                       return function () {
//                         if ("intqos" != id || 1 != getTop(window).have_dynamic_qos && 1 != top.trend_micro_qos || 1 == getTop(window).enable_ap_flag || 0 != getTop(window).enable_bridge_flag || "0" != getTop(window).enable_extender_flag || "1" == getTop(window).device_mode) {
//                           return function () {
//                             if ("parental" == id && 1 != getTop(window).enable_ap_flag && 0 == getTop(window).enable_bridge_flag && "0" == getTop(window).enable_extender_flag && "1" != getTop(window).device_mode) {
//                               return basic_menu_color_change("parental"), open_window("parental_ctrl.htm");
//                             }

//                             if ("speedtest" === id) {
//                               return basic_menu_color_change("speedtest"), goto_formframe("ookla_speedtest.htm");
//                             }

//                             return function () {
//                               if ("readyshare" == id && "1" != getTop(window).device_mode) {
//                                 return basic_menu_color_change("readyshare"), goto_formframe("USB_basic.htm");
//                               }

//                               return function () {
//                                 if ("guest" == id && 0 == getTop(window).enabled_wds && 0 == getTop(window).enable_bridge_flag && "0" == getTop(window).enable_extender_flag && "1" != getTop(window).device_mode) {
//                                   return basic_menu_color_change("guest"), goto_formframe("WLG_wireless_guest1.htm");
//                                 }

//                                 return function () {
//                                   if ("quick_qos" == id) {
//                                     return basic_menu_color_change("quick_qos"), goto_formframe("Quick_wait.htm");
//                                   }

//                                   return function () {
//                                     if ("green" == id && 1 == getTop(window).have_green_download && "1" != getTop(window).device_mode) {
//                                       return function () {
//                                         if ("http" == download_type) {
//                                           return goto_formframe("GREEN_http_basic.htm");
//                                         }

//                                         return function () {
//                                           if ("emule" == download_type) {
//                                             return goto_formframe("GREEN_emule_basic.htm");
//                                           }

//                                           return goto_formframe("GREEN_bt_basic.htm");
//                                         }();
//                                       }(), basic_menu_color_change("green");
//                                     }

//                                     return function () {
//                                       if ("fastlane" == id) {
//                                         return basic_menu_color_change("fastlane"), goto_formframe("FL_fastLane.htm");
//                                       }

//                                       return function () {
//                                         if ("no_internet" == id && 0 == getTop(window).enabled_wds && 1 != getTop(window).enable_ap_flag && "MyDetc" != getTop(window).broadband_mode && 0 == getTop(window).enable_bridge_flag && "0" == getTop(window).enable_extender_flag && "1" != getTop(window).device_mode) {
//                                           return function () {
//                                             if (1 != getTop(window).have_broadband || 1 != getTop(window).is_ru_version && 1 != getTop(window).is_pr_version) {
//                                               return basic_menu_color_change("internet");
//                                             }

//                                             return open_or_close_sub("internet"), basic_menu_color_change("ethernet");
//                                           }(), function () {
//                                             if (0 == portstatus) {
//                                               return location.href = "BRS_03A_A_noWan.html";
//                                             }

//                                             return document.forms[0].submit();
//                                           }();
//                                         }

//                                         return function () {
//                                           if ("funjsq" == id && 1 != getTop(window).enable_ap_flag && 0 == getTop(window).enable_bridge_flag && "0" == getTop(window).enable_extender_flag) {
//                                             return basic_menu_color_change("funjsq"), goto_formframe("funjsq.htm");
//                                           }

//                                           return function () {
//                                             if ("mobile_internet" == id && 0 == getTop(window).enable_bridge_flag) {
//                                               return getTop(window).click_lte_sim = 0, basic_menu_color_change("internet"), goto_formframe("check_mobile_internet_wait.htm");
//                                             }

//                                             return function () {
//                                               if ("plex" == id) {
//                                                 return basic_menu_color_change("plex"), goto_formframe("plex_media.htm");
//                                               }

//                                               return function () {
//                                                 if ("cloud_backup" == id) {
//                                                   return basic_menu_color_change("cloud_backup"), goto_formframe("goto_Netdisk.htm");
//                                                 }

//                                                 return function () {
//                                                   if ("usb_backup" == id) {
//                                                     return basic_menu_color_change("usb_backup"), goto_formframe("USB_backup.htm");
//                                                   }

//                                                   return "vpn_client" == id && "1" == getTop(window).vpn_client_flag && 1 != getTop(window).enable_ap_flag && 0 == getTop(window).enable_bridge_flag && (basic_menu_color_change("vpn_client"), goto_formframe("vpn_client.htm"));
//                                                 }();
//                                               }();
//                                             }();
//                                           }();
//                                         }();
//                                       }();
//                                     }();
//                                   }();
//                                 }();
//                               }();
//                             }();
//                           }();
//                         }

//                         return basic_menu_color_change("intqos"), function () {
//                           if (IsGameRouter() || "1" != top.trend_micro_qos) {
//                             return function () {
//                               if ("1" == getTop(window).have_advanced_qos) {
//                                 return goto_formframe("QOS_wait.htm");
//                               }

//                               return function () {
//                                 if ("1" == getTop(window).trend_micro_flag) {
//                                   return please_wait(!1), getTop(window).formframe.location.href = "new_waiting_page.htm";
//                                 }

//                                 return goto_formframe("QOS_dynamic.htm");
//                               }();
//                             }();
//                           }

//                           return please_wait(!1), top.formframe.location.href = "new_waiting_page.htm";
//                         }();
//                       }();
//                     }();
//                   }

//                   return basic_menu_color_change("wireless"), goto_formframe("WLG_wireless.htm");
//                 }();
//               }();
//             }();
//           }();
//         }();
//       }();
//     })();
//   }
// }
function setIconClass(argv) {
  var height, words_div;
  for (num = 0; num < arguments.length; num++)
    null != (words_div = document.getElementById(arguments[num])) &&
      ((height = words_div.getElementsByTagName("span")[0].clientHeight),
      (words_div.className = height > 20 ? "icon_long_status" : "icon_status"));
}
function jump_armor() {
  document.getElementById("modalBox_armor").style.display = "none";
}
function armor_done() {
  (document.getElementById("armor_nvrm").style.display = "none"),
    (document.getElementById("armor_done").style.display = "");
}
