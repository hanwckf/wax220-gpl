function languageShowlist() {
  /*if (
    (document.write("<option value=Auto>$auto_mark</option>"),
    "" != language_oriArray)
  )*/
    for (j = 0; j < language_oriArray.length; j++)
      document.write(
        "<option value=" +
          language_oriArray[j] +
          ">" +
          language_showArray[j] +
          "</option>"
      );
  /*else
    document.write(
      "<option value=English>" + language_oriArray[0] + "</option>"
    );*/
}
function change_container_posision() {
  document.body.clientWidth < document.body.scrollWidth
    ? (document.getElementById("container").className = "container_left")
    : (document.getElementById("container").className = "container_center");
}
function goto_top(page) {
  1 == getTop(window).enable_action && (getTop(window).location.href = page);
}
function change_select() {
  if (
    ((form = document.forms[0]),
    form.language.value != lang_select ||
      ("Auto" == lang_select && browser_lang != gui_region))
  ) {
    if (1 == bgn_pr_wds_support_wpa || 1 == an_pr_wds_support_wpa)
      return (
        alert("$pr_wps_support_wpa_others_not"),
        goto_formframe("WLG_wireless.htm"),
        (document.forms[0].language.value = lang_select),
        !1
      );
    (form.language.disabled = !0),
      (form.hidden_lang_avi.value = form.language.value),
      (form.submitType.value = "select_language"),
      (form.anticsrf.value = select_language_token),
      (form.target = "formframe"),
      form.submit();
  } else
    "1" == jp_multiPPPoE && "Japanese" != form.language.value
      ? ((form.hidden_lang_avi.value = form.language.value),
        (form.action = '<% action_url("apply.cgi", "index.htm") %>'),
        (form.submitType.value = "change_multiPPPoE_status"),
        (form.anticsrf.value = change_multiPPPoE_status_token),
        form.submit())
      : (location.href = "/top.html");
}
function firmwareUpgrade() {
  goto_formframe("upgrade_found_new_version.htm");
}
function do_search() {
  if ("1" == getTop(window).use_orbi_style_flag)
    var key = document.forms[0].search.value.replace(/\'/g, "&apos;");
  else
    key = getTop(window)
      .document.getElementsByTagName("input")[0]
      .value.replace(/\'/g, "&apos;");
  var url = "";
  (url =
    "" == key || "$ent_srh_item" == key
      ? "http://support.netgear.com/product/" + getTop(window).host_name
      : "http://kb.netgear.com/app/answers/list/kw/" +
        (key = key.replace(/ /g, "%20"))),
    window.open(
      url,
      "_blank",
      "width=960,height=800,menubar=yes,scrollbars=yes,toolbar=yes,status=yes,location=yes,resizable=yes"
    );
}
function setLabelClass(label, className) {
  var words_len = label.getElementsByTagName("span")[0].innerHTML.length;
  label.className =
    words_len >= 16
      ? className + "_longest"
      : words_len >= 12
      ? className + "_long"
      : words_len >= 10
      ? className + "_middle"
      : className;
}
function load_top_value() {
  form = document.forms[0];
  navigator.userAgent;
  var width = getTop(window).document.documentElement.clientWidth,
    upgrade_div = document.getElementById("update_info");
  if ("1" == getTop(window).have_app_ads) {
    "1" == getTop(window).use_orbi_style_flag &&
      (upgrade_div.style.top = "60px");
    var app_div = document.getElementById("orbi-alert");
    "1" == app_ad_mark
      ? (app_div.style.display = "")
      : (app_div.style.display = "none");
  }
  null != upgrade_div &&
    (1 == wan_status && 9999 == config_status && 1 == updateFirmware
      ? (upgrade_div.style.display = "inline")
      : (upgrade_div.style.display = "none"));
  var basic_label = document.getElementById("basic_lab"),
    advanced_label = document.getElementById("advanced_lab");
  if (
    ("basic" == parent.type
      ? ((basic_label.className = "label_click"),
        (advanced_label.className = "label_unclick"))
      : "advanced" == parent.type &&
        ((basic_label.className = "label_unclick"),
        (advanced_label.className = "label_click")),
    "none" != upgrade_div.style.display)
  ) {
    upgrade_div.getElementsByTagName("i")[0];
    var left = document.getElementById("labels").clientWidth + 20,
      free_width = width - left - 181,
      info_width =
        document.getElementById("update_info_middle").clientWidth + 34;
    if (free_width > info_width) {
      var upgrade_left =
        (free_width - info_width) / 2 > 15 ? 15 : (free_width - info_width) / 2;
      (upgrade_div.className = "update_info_down"),
        (upgrade_div.style.left = left + upgrade_left + "px");
    } else
      (upgrade_div.className = "update_info_up"),
        (upgrade_div.style.left = "270px");
  }
}
function detectEnter(type, e) {
  var keycode;
  if (
    ("1" != getTop(window).r9000_router_flag &&
      ((form = document.forms[0]),
      (form.hidden_lang_avi.value = form.language.value)),
    window.event)
  )
    window.event, (keycode = window.event.keyCode);
  else {
    if (!e) return !0;
    e, (keycode = e.which);
  }
  if ("num" != type) return !1;
  13 == keycode && do_search();
}
function hide_warn() {
  form = document.forms[0];
  var upgrade_div = document.getElementById("update_info");
  (document.getElementById("orbi-alert").style.display = "none"),
    null != upgrade_div &&
      (1 != wan_status ||
      (9999 != config_status && 10004 != config_status) ||
      1 != updateFirmware
        ? (upgrade_div.style.display = "none")
        : (upgrade_div.style.display = "inline"));
}
