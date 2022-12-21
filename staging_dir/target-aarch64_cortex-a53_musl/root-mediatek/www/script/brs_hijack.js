/**
 * @param frameWindow {Window}
 * @returns {Window}
*/
function getTop(frameWindow) {
  try {
    var parentWindow = frameWindow.parent;
    return void 0 !== frameWindow.netgear_version
      ? frameWindow
      : parentWindow === frameWindow
      ? frameWindow
      : parentWindow.origin !== frameWindow.origin
      ? frameWindow
      : getTop(parentWindow);
  } catch (e) {
    return top;
  }
}
function goto_home_page() {
  getTop(window).location.href = "/";
}
function addLoadEvent(func) {
  var oldonload = window.onload;
  "function" != typeof window.onload
    ? (window.onload = func)
    : (window.onload = function () {
        oldonload(), func();
      });
}
function insertAfter(newElement, targetElement) {
  var parent = targetElement.parentNode;
  parent.lastChild == targetElement
    ? parent.appendChild(newElement)
    : parent.insertBefore(newElement, targetElement.nextSibling);
}
function addClass(element, value) {
  element.className
    ? ((newClassName = element.className),
      (newClassName += " "),
      (newClassName += value),
      (element.className = newClassName))
    : (element.className = value);
}
function showFirmVersion(flag) {
  var iframe = getTop(window).document.getElementById("header_frame");
  if (iframe) {
    var version_div = iframe.contentWindow.document.getElementById(
      "firmware_version"
    );
    version_div && (version_div.style.display = flag);
  }
}
function ssidKeyCode(event) {
  var evt = event || (window.event ? window.event : null);
  return 32 != (window.event ? window.event.keyCode : evt ? evt.which : null);
}
function ipaddrKeyCode(event) {
  var evt = event || (window.event ? window.event : null),
    keycode = window.event ? window.event.keyCode : evt ? evt.which : null;
  return (
    (keycode > 47 && keycode < 58) ||
    8 == keycode ||
    0 == keycode ||
    46 == keycode
  );
}
function numKeyCode(event) {
  var evt = event || (window.event ? window.event : null),
    keycode = window.event ? window.event.keyCode : evt ? evt.which : null;
  return (keycode > 47 && keycode < 58) || 8 == keycode || 0 == keycode;
}
function numLetterKeyCode(event) {
  var evt = event || (window.event ? window.event : null),
    keycode = window.event ? window.event.keyCode : evt ? evt.which : null;
  return (
    (keycode > 47 && keycode < 58) ||
    (keycode > 64 && keycode < 91) ||
    (keycode > 96 && keycode < 123) ||
    8 == keycode ||
    0 == keycode
  );
}
function hostnameKeyCode(event) {
  var evt = event || (window.event ? window.event : null),
    keycode = window.event ? window.event.keyCode : evt ? evt.which : null;
  return (
    (keycode > 47 && keycode < 58) ||
    45 == keycode ||
    (keycode > 64 && keycode < 91) ||
    (keycode > 96 && keycode < 123) ||
    8 == keycode ||
    0 == keycode
  );
}
function ddnsHostnameKeyCode(event) {
  var evt = event || (window.event ? window.event : null),
    keycode = window.event ? window.event.keyCode : evt ? evt.which : null;
  return (
    (keycode > 47 && keycode < 58) ||
    45 == keycode ||
    46 == keycode ||
    (keycode > 64 && keycode < 91) ||
    (keycode > 96 && keycode < 123) ||
    8 == keycode ||
    0 == keycode
  );
}
function macKeyCode(event) {
  var evt = event || (window.event ? window.event : null),
    keycode = window.event ? window.event.keyCode : evt ? evt.which : null;
  return (
    (keycode > 47 && keycode < 58) ||
    (keycode > 64 && keycode < 71) ||
    (keycode > 96 && keycode < 103) ||
    8 == keycode ||
    0 == keycode ||
    58 == keycode ||
    45 == keycode
  );
}
function detectOS() {
  var sUserAgent = navigator.userAgent,
    isWin =
      "Win32" == navigator.platform ||
      "Win64" == navigator.platform ||
      "Windows" == navigator.platform,
    isMac =
      "Mac68K" == navigator.platform ||
      "MacPPC" == navigator.platform ||
      "Macintosh" == navigator.platform ||
      "MacIntel" == navigator.platform;
  return isMac
    ? "Mac"
    : "X11" != navigator.platform || isWin || isMac
    ? String(navigator.platform).indexOf("Linux") > -1
      ? "Linux"
      : isWin
      ? sUserAgent.indexOf("Windows NT 5.0") > -1 ||
        sUserAgent.indexOf("Windows 2000") > -1
        ? "Win2000"
        : sUserAgent.indexOf("Windows NT 5.1") > -1 ||
          sUserAgent.indexOf("Windows XP") > -1
        ? "WinXP"
        : sUserAgent.indexOf("Windows NT 5.2") > -1 ||
          sUserAgent.indexOf("Windows 2003") > -1
        ? "Win2003"
        : sUserAgent.indexOf("Windows NT 6.0") > -1 ||
          sUserAgent.indexOf("Windows Vista") > -1
        ? "WinVista"
        : sUserAgent.indexOf("Windows NT 6.1") > -1 ||
          sUserAgent.indexOf("Windows 7") > -1
        ? "Win7"
        : sUserAgent.indexOf("Windows NT 6.2") > -1 ||
          sUserAgent.indexOf("Windows NT 6.3") > -1 ||
          sUserAgent.indexOf("Windows 8") > -1
        ? "Win8"
        : sUserAgent.indexOf("Windows NT 10.0") > -1 ||
          sUserAgent.indexOf("Windows 10") > -1
        ? "Win10"
        : "Win"
      : "None"
    : "Unix";
}
function isMac() {
  return "Mac" == detectOS();
}
function control_display(page) {
  if ("dsl_dhcp" == page)
    1 == lan_ports_num &&
      ((document.getElementById("bridge_doc").style.display = "none"),
      (document.getElementById("bridge_lans").style.display = "none"),
      (document.getElementById("content_div").style.width = "100%"),
      (document.getElementById("connection_identi").style.height = "60px"));
  else if (
    "dsl_pppoe" == page &&
    ("1" == display_iptv2
      ? ((document.getElementById("iptv").style.display = ""),
        "1" == wan2_bridge && 1 != lan_ports_num
          ? ((document.getElementById("bridge").style.display = ""),
            (document.getElementById("bridge1").style.display = ""),
            (document.getElementById("bridge2").style.display = ""))
          : ((document.getElementById("bridge").style.display = "none"),
            (document.getElementById("bridge1").style.display = "none"),
            (document.getElementById("bridge2").style.display = "none")))
      : (document.getElementById("iptv").style.display = "none"),
    "" == vlan_id)
  ) {
    var obj = document.getElementById("vlanid_text");
    null != obj &&
      ((document.getElementById("vlanid").style.display = "none"),
      (obj.style.display = "none"));
  }
}
