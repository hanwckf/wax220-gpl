var vdsl_list = {
    Australia: { TPG: { num: "1", vlanid1: "2" } },
    Austria: {
      "A1 Telekom": { num: "2", vlanid1: "2", vlanid2: "4" },
      "Comteam.at": { num: "1", vlanid1: "2" },
    },
    Belgium: {
      "Proximus(Belgacom)": { num: "2", vlanid1: "10", vlanid2: "30" },
    },
    Canada: {
      SaskTel: { num: "1", vlanid1: "3328" },
      TekSavvy: { num: "1", vlanid1: "35" },
    },
    Denmark: {
      Telenor: { num: "1", vlanid1: "101" },
      TDC: { num: "1", vlanid1: "101" },
    },
    Finland: { "DNA Welho": { num: "1", vlanid1: "" } },
    France: {
      Free: { num: "2", vlanid1: "", vlanid2: "100" },
      Orange: { num: "2", vlanid1: "835", vlanid2: "838" },
    },
    Germany: {
      "Deutsche Telekom": { num: "2", vlanid1: "7", vlanid2: "8" },
      "1&1": { num: "1", vlanid1: "7" },
      "Telefonica O2": { num: "1", vlanid1: "7" },
      Netcologne: { num: "1", vlanid1: "10" },
      Vodafone: { num: "1", vlanid1: "7" },
    },
    Ireland: { Eircom: { num: "1", vlanid1: "10" } },
    Italy: {
      Fastweb: { num: "1", vlanid1: "1" },
      "Telecom Italia": { num: "1", vlanid1: "835" },
    },
    Netherlands: { Telfort: { num: "1", vlanid1: "34" } },
    New_Zealand: {
      IHug: { num: "1", vlanid1: "10" },
      "Kiwi Online(KOL)": { num: "1", vlanid1: "10" },
      Orcon: { num: "1", vlanid1: "10" },
      Paradise: { num: "1", vlanid1: "10" },
      Slingshot: { num: "1", vlanid1: "10" },
      Spark: { num: "1", vlanid1: "10" },
      "Xnet(World Exchange)": { num: "1", vlanid1: "10" },
      Bigpipe: { num: "1", vlanid1: "10" },
      Vodafone: { num: "1", vlanid1: "10" },
      "Trust power": { num: "1", vlanid1: "10" },
      Snap: { num: "1", vlanid1: "10" },
      "Telstra Clear": { num: "1", vlanid1: "10" },
      Other: { num: "1", vlanid1: "10" },
    },
    Singapore: { SingTel: { num: "1", vlanid1: "10" } },
    Spain: {
      Jazztel: { num: "1", vlanid1: "1079" },
      Movistar: { num: "2", vlanid1: "6", vlanid2: "2" },
    },
    Sweden: { Telia: { num: "2", vlanid1: "835", vlanid2: "845" } },
    Switzerland: {
      Swisscom: { num: "1", vlanid1: "10" },
      "Swisscom All IP(with phone)": { num: "1", vlanid1: "" },
      Sunrise: { num: "1", vlanid1: "" },
      Telfort: { num: "1", vlanid1: "34" },
    },
    UK: {
      BT: { num: "2", vlanid1: "101", vlanid2: "101" },
      PlusNet: { num: "2", vlanid1: "101", vlanid2: "101" },
      TalkTalk: { num: "1", vlanid1: "101" },
      Sky: { num: "1", vlanid1: "101" },
      "EE(Orange)": { num: "1", vlanid1: "101" },
      "ZEN Internet": { num: "1", vlanid1: "101" },
    },
    USA: { CenturyLink: { num: "1", vlanid1: "201" } },
  },
  adsl_list = {
    Australia: {
      Soul: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Exetel: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      "People Telcom": { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Adam: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Telstra: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Internode: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Westnet: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Optus: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Primus: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      TPG: {
        vpi_num: "0",
        vpi2: "0",
        vci2: "32",
        multi2: "llc",
        vpi: "8",
        vci: "35",
        encap: "pppoe",
        multi: "llc",
      },
      iiNet: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Dodo: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "Telstra Bigpond": { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      TransACT: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Clubtelco: { vpi: "8", vci: "35", encap: "pppoa", multi: "llc" },
      "UPC Austria": { vpi: "9", vci: "35", encap: "pppoe", multi: "llc" },
      UTA2: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Engin: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Other: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Austria: {
      "UPC Austria": { vpi: "9", vci: "35", encap: "pppoe", multi: "llc" },
      UTA2: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
      "A1 Telekom": { vpi: "8", vci: "48", encap: "pppoa", multi: "llc" },
      Other: { vpi: "8", vci: "48", encap: "pppoe", multi: "llc" },
    },
    Belgium: {
      "Proximus(Belgacom)": {
        vpi: "8",
        vci: "35",
        encap: "pppoe",
        multi: "llc",
      },
    },
    Brazil: {
      "Gvt-Global Village Telecom": {
        vpi: "0",
        vci: "35",
        encap: "pppoe",
        multi: "llc",
      },
      "Telemar Oi Velox": { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      Oi: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
    },
    Canada: {
      "Bell Canada(Western)": {
        vpi: "0",
        vci: "32",
        encap: "pppoe",
        multi: "llc",
      },
      SaskTel: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
      TekSavvy: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
    },
    China: {
      "China Telecom": { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "Bell Canada(Western)": {
        vpi: "0",
        vci: "32",
        encap: "pppoe",
        multi: "llc",
      },
      Other: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Czech_Republic: {
      O2: { vpi: "8", vci: "48", encap: "pppoe", multi: "llc" },
      Tiscali: { vpi: "8", vci: "48", encap: "pppoe", multi: "llc" },
      "T-Mobile": { vpi: "8", vci: "48", encap: "pppoe", multi: "llc" },
    },
    Denmark: {
      Telenor: { vpi: "0", vci: "35", encap: "pppoa", multi: "vc" },
      TDC: { vpi: "0", vci: "35", encap: "pppoa", multi: "vc" },
    },
    Finland: {
      Teliasonera: { vpi: "0", vci: "33", encap: "pppoa", multi: "llc" },
      "Elisa Oyj": { vpi: "0", vci: "100", encap: "pppoe", multi: "llc" },
      Other: { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
    },
    France: {
      SFR: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Orange: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      OVH: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Free: { vpi: "8", vci: "36", encap: "ipoa", multi: "vc" },
      Nordnet: { vpi: "8", vci: "35", encap: "pppoa", multi: "llc" },
      Other: { vpi: "0", vci: "35", encap: "pppo5", multi: "llc" },
    },
    Germany: {
      "1&1": { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      "Deutsche Telekom": {
        vpi_num: "0",
        vpi2: "1",
        vci2: "33",
        multi2: "llc",
        vpi: "1",
        vci: "32",
        encap: "pppoe",
        multi: "llc",
      },
      "Telefonica O2": { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      "m-net": { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      Telstra: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Vodafone: { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      Netcologne: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Hongkong: { PCCW: { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" } },
    Hungary: {
      Actel: { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      "GTS Datanet": { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      Invitel: { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
      "T-Home": { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
    },
    India: {
      MTNL: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
      TataIndicom: { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      BSNL: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Inedit: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Indonesia: {
      "Telkom Speedy": { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Speedy: { vpi: "8", vci: "81", encap: "pppoe", multi: "llc" },
      Other: { vpi: "8", vci: "35", encap: "pppoa", multi: "llc" },
    },
    Italy: {
      "Telecom Italia": { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Infostrada: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Aruba: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Tiscali: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Infostrada: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Twt: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Acantho: { vpi: "8", vci: "35", encap: "pppoa", multi: "vc" },
      Fastweb: { vpi: "8", vci: "36", encap: "dhcp", multi: "llc" },
      "Wind(Infostrada)": { vpi: "8", vci: "35", encap: "pppoe", multi: "vc" },
      Tiscali: { vpi: "0", vci: "38", encap: "pppoa", multi: "vc" },
      TELE2: { vpi: "8", vci: "36", encap: "pppoe", multi: "llc" },
      "MC-link": { vpi: "8", vci: "75", encap: "pppoa", multi: "vc" },
      Intred: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "KPN Qwest Italia": { vpi: "8", vci: "35", encap: "ipoa", multi: "vc" },
    },
    Malaysia: {
      Streamyx: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Netherlands: {
      Vodafonevast: { vpi: "0", vci: "34", encap: "pppoe", multi: "llc" },
      Telfort: { vpi: "0", vci: "34", encap: "pppoe", multi: "llc" },
      "Online-nl": { vpi: "8", vci: "35", encap: "dhcp", multi: "llc" },
    },
    New_Zealand: {
      IHug: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      "Kiwi Online(KOL)": { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Orcon: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Paradise: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Slingshot: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      "Telstra Clear": { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Spark: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      "Xnet(World Exchange)": {
        vpi: "0",
        vci: "100",
        encap: "pppoa",
        multi: "vc",
      },
      Snap: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Bigpipe: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Vodafone: { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      "Trust power": { vpi: "0", vci: "100", encap: "pppoa", multi: "vc" },
      Other: { vpi: "0", vci: "100", encap: "pppoa", multi: "llc" },
    },
    Other: { Streamyx: { vpi: "0", vci: "38", encap: "pppoa", multi: "vc" } },
    Philippine: {
      PLDT: { vpi: "0", vci: "100", encap: "pppoe", multi: "llc" },
      TelPlus: { vpi: "0", vci: "100", encap: "pppoe", multi: "llc" },
    },
    Poland: {
      Multimo: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Tele2: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Netia: { vpi: "0", vci: "35", encap: "pppoa", multi: "vc" },
      Orange: { vpi: "0", vci: "35", encap: "pppoa", multi: "vc" },
      Other: { vpi: "0", vci: "35", encap: "pppoa", multi: "llc" },
    },
    Portugal: {
      PT: { vpi: "0", vci: "35", encap: "pppoe", multi: "vc" },
      Vodafone: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Zon: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Russia: {
      Beltelecom: { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      "Domolink CentrTelekom": {
        vpi: "0",
        vci: "35",
        encap: "pppoe",
        multi: "llc",
      },
      "Avangard-DSL": { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      "MTS Stream": { vpi: "1", vci: "50", encap: "pppoe", multi: "llc" },
      MGTS: { vpi: "1", vci: "50", encap: "pppoe", multi: "llc" },
      "Jdsl Volgatelekom": {
        vpi: "1",
        vci: "100",
        encap: "pppoe",
        multi: "llc",
      },
      Combellga: { vpi: "8", vci: "63", encap: "pppoa", multi: "vc" },
      Rostelecom: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Other: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
    },
    Saudi_Arabia: {
      STC: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Singapore: {
      PacificNet: { vpi: "0", vci: "100", encap: "pppoe", multi: "llc" },
      Singnet: { vpi: "0", vci: "100", encap: "pppoe", multi: "llc" },
      Other: { vpi: "0", vci: "100", encap: "pppoe", multi: "vc" },
    },
    Spain: {
      "Telefonica Movistar(dynamic IP)": {
        vpi: "8",
        vci: "32",
        encap: "pppoe",
        multi: "llc",
      },
      Orange: { vpi: "8", vci: "32", encap: "pppoe", multi: "llc" },
      Jazztel: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Vodafone: { vpi: "0", vci: "33", encap: "pppoa", multi: "vc" },
      Pepephone: { vpi: "0", vci: "33", encap: "pppoa", multi: "vc" },
      "Telefonica Movistar(fixed IP)": {
        vpi: "8",
        vci: "32",
        encap: "ipoa",
        multi: "llc",
      },
      Other: { vpi: "8", vci: "35", encap: "ipoa", multi: "llc" },
    },
    Sweden: {
      Telia: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Ljusnet: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "Bahnhof AB": { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Bredbandsbolaget: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Other: { vpi: "8", vci: "35", encap: "pppoa", multi: "llc" },
    },
    Switzerland: {
      Sunrise: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "Monzoon Networks": { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Siwsscom: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Telfort: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Other: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
    },
    Thailand: {
      "TT&T": { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      "3BB": { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      "CAT-Telecom": { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      "CS-Loxinfo": { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Samart: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      "TRUE Internet": { vpi: "0", vci: "100", encap: "pppoe", multi: "llc" },
      TOT: { vpi: "1", vci: "32", encap: "pppoe", multi: "llc" },
    },
    Turkey: { Other: { vpi: "8", vci: "35", encap: "pppoe", multi: "vc" } },
    UK: {
      BT: {
        vpi_num: "0",
        vpi2: "0",
        vci2: "35",
        multi2: "vc",
        vpi: "0",
        vci: "38",
        encap: "pppoe",
        multi: "llc",
      },
      Sky: { vpi: "0", vci: "38", encap: "pppoe", multi: "llc" },
      TalkTalk: { vpi: "0", vci: "38", encap: "pppoe", multi: "llc" },
      PlusNet: { vpi: "0", vci: "38", encap: "pppoe", multi: "llc" },
      Virgin: { vpi: "0", vci: "38", encap: "pppoe", multi: "llc" },
      Media: { vpi: "0", vci: "38", encap: "pppoe", multi: "llc" },
      "EE(Orange)": { vpi: "0", vci: "38", encap: "pppoe", multi: "llc" },
      Other: { vpi: "8", vci: "36", encap: "pppoe", multi: "vc" },
    },
    USA: {
      "AT&T": { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Earthlink: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Verizon: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Windstream: { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      "Frontier Communications": {
        vpi: "0",
        vci: "35",
        encap: "pppoa",
        multi: "llc",
      },
      "Rivercity Internet Group": {
        vpi: "0",
        vci: "35",
        encap: "pppoa",
        multi: "llc",
      },
      CenturyLink: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "Bigriver.net DSL": { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      Qwest: { vpi: "0", vci: "32", encap: "pppoe", multi: "llc" },
      "cox communications": {
        vpi: "8",
        vci: "129",
        encap: "dhcp",
        multi: "vc",
      },
      BEVCOMM: { vpi: "0", vci: "35", encap: "dhcp", multi: "llc" },
      Other: { vpi: "0", vci: "32", encap: "pppoa", multi: "llc" },
    },
    Vietnam: {
      FPT: { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      NATNAM: { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      SPT: { vpi: "0", vci: "33", encap: "pppoe", multi: "llc" },
      "VNN(in Hanoi)": { vpi: "0", vci: "35", encap: "pppoe", multi: "llc" },
      Viettel: { vpi: "8", vci: "35", encap: "pppoe", multi: "llc" },
      "VNN(in HAM)": { vpi: "8", vci: "38", encap: "pppoe", multi: "llc" },
    },
  };

function set_checkbox_value(cb_obj, hid_obj) {
  1 == cb_obj.checked ? (hid_obj.value = "1") : (hid_obj.value = "0");
}
function load_checkbox_value(cfg_val, cb_obj) {
  cb_obj.checked = "1" == cfg_val;
}
function sAlert(str, callback_ok, callback_cancel, dwidth, anc, button_lang) {
  IsGameRouter()
    ? sAlert2(str, callback_ok, callback_cancel, dwidth, anc, button_lang)
    : sAlert1(str, callback_ok, callback_cancel, dwidth, anc, button_lang);
}
function sAlert2(str, callback_ok, callback_cancel, dwidth, anc, button_lang) {
  var mode = "alert";
  callback_ok = callback_ok || 0;
  var msgw,
    sWidth,
    sHeight,
    anc_v = anc || 0;
  (msgw = dwidth || 420),
    "function" == typeof (callback_cancel = callback_cancel || 0) &&
      (mode = "confirm"),
    null != document.getElementById("bgDiv") && removeObj(),
    (titleheight = 25),
    (sWidth = document.body.offsetWidth),
    (sHeight = screen.height);
  var bgObj = document.createElement("div");
  bgObj.setAttribute("id", "bgDiv"),
    (bgObj.style.position = "absolute"),
    (bgObj.style.top = "0"),
    (bgObj.style.filter =
      "progid:DXImageTransform.Microsoft.Alpha(style=3,opacity=25,finishOpacity=75"),
    (bgObj.style.opacity = "0.6"),
    (bgObj.style.left = "0"),
    (bgObj.style.width = sWidth + "px"),
    (bgObj.style.height = sHeight + "px"),
    (bgObj.style.zIndex = "10000"),
    document.body.appendChild(bgObj);
  var msgObj = document.createElement("div");
  msgObj.setAttribute("id", "msgDiv"),
    msgObj.setAttribute("align", "center"),
    (msgObj.style.position = "absolute"),
    (msgObj.style.left = "40%"),
    (msgObj.style.top = "30%"),
    (msgObj.style.marginLeft = "-225px"),
    (msgObj.style.width = msgw + "px"),
    (msgObj.style.zIndex = "10001"),
    (msgObj.className = msgObj.className + " pop_box");
  var div1 = document.createElement("div");
  div1.setAttribute("id", "msgTitle"),
    div1.setAttribute("align", "left"),
    (div1.style.marginLeft = "30px"),
    (div1.style.marginRight = "30px"),
    (div1.style.marginBottom = "20px"),
    (div1.style.padding = "0px"),
    (div1.style.filter =
      "progid:DXImageTransform.Microsoft.Alpha(startX=20, startY=20, finishX=100, finishY=100,style=1,opacity=75,finishOpacity=100);"),
    (div1.style.opacity = "0.75"),
    (div1.style.font = "12px Verdana, Geneva, Arial, Helvetica, sans-serif"),
    (div1.style.cursor = "pointer"),
    (div1.innerHTML = str);
  var button = document.createElement("input");
  button.setAttribute("type", "button"),
    "yes/no" == button_lang
      ? (button.setAttribute("value", "$yes_mark"),
        button.setAttribute("id", "yes_bt"),
        button.setAttribute("name", "yes_bt"))
      : "cancel/apply" == button_lang
      ? (button.setAttribute("value", "$cancel_mark"),
        button.setAttribute("id", "cancel_bt2"),
        button.setAttribute("name", "cancel_bt2"))
      : (button.setAttribute("value", "$ok_mark"),
        button.setAttribute("id", "ok_bt"),
        button.setAttribute("name", "ok_bt")),
    (button.style.minWidth = "80px"),
    (button.style.marginLeft = "140px"),
    (button.style.marginBottom = "10px"),
    (button.style.background = " #de1821"),
    (button.style.border = "1px solid " + " #de1821"),
    (button.style.color = "white"),
    (button.onclick = function () {
      0 == anc_v && removeObj();
      "function" == typeof callback_ok && callback_ok();
    });
  var button1 = document.createElement("input");
  function removeObj() {
    document.body.removeChild(document.getElementById("bgDiv")),
      document
        .getElementById("msgDiv")
        .removeChild(document.getElementById("msgTitle")),
      document
        .getElementById("msgDiv")
        .parentNode.removeChild(document.getElementById("msgDiv"));
  }
  button1.setAttribute("type", "button"),
    "yes/no" == button_lang
      ? (button1.setAttribute("value", "$no_mark"),
        button.setAttribute("id", "no_bt"),
        button.setAttribute("name", "no_bt"))
      : "cancel/apply" == button_lang
      ? (button1.setAttribute("value", "$apply_mark"),
        button.setAttribute("id", "apply_bt2"),
        button.setAttribute("name", "apply_bt2"))
      : (button1.setAttribute("value", "$cancel_mark"),
        button.setAttribute("id", "cancel_bt"),
        button.setAttribute("name", "cancel_bt")),
    (button1.style.minWidth = "80px"),
    (button1.style.marginLeft = "10px"),
    (button1.style.marginBottom = "10px"),
    (button1.style.background = "#de1821"),
    (button1.style.border = "1px solid " + "#de1821"),
    (button1.style.color = "white"),
    (button1.onclick = function () {
      "function" == typeof callback_cancel && callback_cancel();
      "cancel/apply" != button_lang && removeObj();
      "yes/no" == button_lang &&
        "" != apply_btn_state &&
        (document.getElementById("apply").disabled = !1);
    }),
    "yes/no" == button_lang &&
      (apply_btn_state = document
        .getElementById("apply")
        .getAttribute("disabled")),
    document.forms[0].appendChild(msgObj),
    document.getElementById("msgDiv").appendChild(div1);
  document.createElement("p");
  document.getElementById("msgDiv").appendChild(div1),
    document.getElementById("msgDiv").appendChild(button),
    "confirm" == mode && document.getElementById("msgDiv").appendChild(button1),
    "yes/no" == button_lang &&
      ((document.getElementById("fix_button").style.zIndex = "10001"),
      (document.getElementById("apply").disabled = !0));
}
function sAlert1(str, callback_ok, callback_cancel, dwidth, anc, button_lang) {
  var mode = "alert";
  (callback_ok = callback_ok || 0), (button_lang = button_lang || "");
  var msgw,
    msgh,
    sWidth,
    sHeight,
    anc_v = anc || 0;
  (msgw = dwidth || 420),
    (msgh = 280),
    "function" == typeof (callback_cancel = callback_cancel || 0) &&
      (mode = "confirm"),
    null != document.getElementById("bgDiv") && removeObj(),
    (titleheight = 25),
    (sWidth = document.body.offsetWidth),
    (sHeight = screen.height);
  var bgObj = document.createElement("div");
  bgObj.setAttribute("id", "bgDiv"),
    (bgObj.style.position = "absolute"),
    (bgObj.style.top = "0"),
    (bgObj.style.filter =
      "progid:DXImageTransform.Microsoft.Alpha(style=3,opacity=25,finishOpacity=75"),
    (bgObj.style.opacity = "0.6"),
    (bgObj.style.left = "0"),
    (bgObj.style.width = sWidth + "px"),
    (bgObj.style.height = sHeight + "px"),
    (bgObj.style.zIndex = "10000"),
    document.body.appendChild(bgObj);
  var msgObj = document.createElement("div");
  msgObj.setAttribute("id", "msgDiv"),
    msgObj.setAttribute("align", "center"),
    (msgObj.style.position = "absolute"),
    (msgObj.style.left = "40%"),
    (msgObj.style.top = "20%"),
    (msgObj.style.marginLeft = "-225px"),
    (msgObj.style.width = msgw + "px"),
    (msgObj.style.maxHeight = msgh + "px"),
    (msgObj.style.zIndex = "10001"),
    (msgObj.className = msgObj.className + " pop_box");
  var div1 = document.createElement("div");
  div1.setAttribute("id", "msgTitle"),
    div1.setAttribute("align", "left"),
    (div1.style.marginLeft = "30px"),
    (div1.style.marginRight = "30px"),
    (div1.style.marginBottom = "20px"),
    (div1.style.padding = "0px"),
    (div1.style.filter =
      "progid:DXImageTransform.Microsoft.Alpha(startX=20, startY=20, finishX=100, finishY=100,style=1,opacity=75,finishOpacity=100);"),
    (div1.style.opacity = "0.75"),
    (div1.style.font = "12px Verdana, Geneva, Arial, Helvetica, sans-serif"),
    (div1.style.cursor = "pointer"),
    (div1.innerHTML = str);
  var button = document.createElement("input");
  button.setAttribute("type", "button");
  var pattion = button_lang.indexOf("/");
  if (
    ("yes/no" == button_lang
      ? (button.setAttribute("value", "$yes_mark"),
        button.setAttribute("id", "yes_bt"))
      : "cancel/apply" == button_lang
      ? (button.setAttribute("value", "$cancel_mark"),
        button.setAttribute("id", "cancel_bt2"))
      : "cancel/ok" == button_lang
      ? (button.setAttribute("value", "$ok_mark"),
        button.setAttribute("id", "ok_bt"))
      : "" != button_lang
      ? -1 == pattion
        ? button.setAttribute("value", button_lang)
        : button.setAttribute("value", button_lang.substring(0, pattion))
      : (button.setAttribute("value", "$ok_mark"),
        button.setAttribute("id", "ok_bt")),
    (button.style.minWidth = "80px"),
    (button.style.cursor = "pointer"),
    (button.style.marginBottom = "10px"),
    -1 != this.location.href.indexOf("plex_") ||
      -1 != this.location.href.indexOf("Netdisk_"))
  )
    var oldSty = 1;
  "cancel/apply" == button_lang || "cancel/ok" == button_lang
    ? 1 == oldSty
      ? ((button.style.background = " #6562AC"),
        (button.style.border = "1px solid " + " #6562AC"))
      : ((button.style.background = " #5bb6e5"),
        (button.style.border = "1px solid " + " #5bb6e5"))
    : ((button.style.background = " #702b86"),
      (button.style.border = "1px solid " + " #702b86")),
    (button.style.color = "white"),
    (button.onclick = function () {
      0 == anc_v && removeObj();
      "function" == typeof callback_ok && callback_ok();
    });
  var button1 = document.createElement("input");
  function removeObj() {
    document.body.removeChild(document.getElementById("bgDiv")),
      document
        .getElementById("msgDiv")
        .removeChild(document.getElementById("msgTitle")),
      document.forms[0].removeChild(document.getElementById("msgDiv"));
  }
  button1.setAttribute("type", "button"),
    "yes/no" == button_lang
      ? (button1.setAttribute("value", "$no_mark"),
        button1.setAttribute("id", "no_bt"))
      : "cancel/apply" == button_lang
      ? (button1.setAttribute("value", "$apply_mark"),
        button1.setAttribute("id", "apply_bt2"))
      : "cancel/ok" == button_lang
      ? (button1.setAttribute("value", "$cancel_mark"),
        button1.setAttribute("id", "cancel_bt"))
      : "" != button_lang
      ? -1 == pattion
        ? button1.setAttribute("value", button_lang)
        : button1.setAttribute("value", button_lang.substring(pattion + 1))
      : (button1.setAttribute("value", "$cancel_mark"),
        button1.setAttribute("id", "cancel_bt")),
    (button1.style.minWidth = "80px"),
    (button1.style.cursor = "pointer"),
    (button1.style.marginLeft = "10px"),
    (button1.style.marginBottom = "10px"),
    "cancel/apply" == button_lang || "cancel/ok" == button_lang
      ? 1 == oldSty
        ? ((button1.style.background = "#7EA83C"),
          (button1.style.border = "1px solid " + "#7EA83C"))
        : ((button1.style.background = "#702b86"),
          (button1.style.border = "1px solid " + "#702b86"))
      : ((button1.style.background = "#5bb6e5"),
        (button1.style.border = "1px solid " + "#5bb6e5")),
    (button1.style.color = "white"),
    (button1.onclick = function () {
      "function" == typeof callback_cancel && callback_cancel();
      "cancel/apply" != button_lang &&
        "cancel/ok" != button_lang &&
        removeObj();
      "yes/no" == button_lang &&
        "" != apply_btn_state &&
        (document.getElementById("apply").disabled = !1);
    }),
    "yes/no" == button_lang &&
      (apply_btn_state = document
        .getElementById("apply")
        .getAttribute("disabled")),
    document.forms[0].appendChild(msgObj),
    document.getElementById("msgDiv").appendChild(div1);
  document.createElement("p");
  document.getElementById("msgDiv").appendChild(div1),
    document.getElementById("msgDiv").appendChild(button),
    "confirm" == mode && document.getElementById("msgDiv").appendChild(button1),
    "yes/no" == button_lang &&
      ((document.getElementById("fix_button").style.zIndex = "10001"),
      (document.getElementById("apply").disabled = !0));
}
function createXMLHttpRequest() {
  return (
    "undefined" == typeof XMLHttpRequest &&
      (XMLHttpRequest = function () {
        try {
          return new ActiveXObject("Msxml2.XMLHTTP.6.0");
        } catch (e) {}
        try {
          return new ActiveXObject("Msxml2.XMLHTTP.3.0");
        } catch (e) {}
        try {
          return new ActiveXObject("Msxml2.XMLHTTP");
        } catch (e) {}
        return !1;
      }),
    new XMLHttpRequest()
  );
}
function edit_devicename(name) {
  (location.href = "edit_device_name.htm"),
    "basic" != name &&
      (getTop(window).open_sub("setup"),
      getTop(window).menu_color_change("devname"));
}
function showWps_alert() {
  "1" == wps_alert && alert("$wps_in_progress");
}
function getDaysInMonth(year, month) {
  return (
    (month = parseInt(month, 10) + 1),
    new Date(year + "/" + month + "/0").getDate()
  );
}
function num_month(month) {
  return "Jan" == month
    ? "1"
    : "Feb" == month
    ? "2"
    : "Mar" == month
    ? "3"
    : "Apr" == month
    ? "4"
    : "May" == month
    ? "5"
    : "Jun" == month
    ? "6"
    : "Jul" == month
    ? "7"
    : "Aug" == month
    ? "8"
    : "Sep" == month
    ? "9"
    : "Oct" == month
    ? "10"
    : "Nov" == month
    ? "11"
    : "Dec" == month
    ? "12"
    : month;
}
function setFooterClass() {
  var footer_div = top.document.getElementById("footer"),
    go_btn = top.document.getElementById("search_button");
  (content_len = go_btn.value.length),
    content_len >= 7
      ? (go_btn.className = go_btn.className + "_long")
      : content_len >= 4
      ? (go_btn.className = go_btn.className + "_middle")
      : (go_btn.className = go_btn.className);
  var width =
      top.document.getElementById("support").clientWidth +
      top.document.getElementById("search").clientWidth,
    screen_width = top.document.documentElement.clientWidth;
  footer_div.className = width < screen_width - 60 ? "footer" : "footer_double";
}
function open_window(page) {
  window.open(
    page,
    null,
    "width=640,height=480,menubar=yes,scrollbars=yes,toolbar=yes,status=yes,location=yes,resizable=yes"
  );
}
function goto_home_page() {
  -1 != top.location.href.indexOf("adv_index.htm")
    ? (top.location.href = "adv_index.htm")
    : top.location.href.indexOf("BRS_index.htm") > -1
    ? toInternet()
    : (top.location.href = "index.htm");
}
function existClassName(classname) {
  if (document.getElementsByClassName)
    return document.getElementsByClassName(classname);
  var divs = document.getElementsByTagName("div");
  for (i = 0; i < divs.length; i++)
    if (divs[i].className == classname) return divs[i];
  return null;
}
function please_wait(flag) {
  var obj = parent.document.getElementById("pls_wait_div"),
    frame = parent.document.getElementById("formframe");
  void 0 !== obj &&
    void 0 !== frame &&
    null != obj &&
    null != frame &&
    (flag
      ? ((frame.style.display = "none"),
        (obj.style.display = ""),
        parent.timeoutfunc && parent.clearTimeout(parent.timeoutfunc),
        (parent.timeoutfunc = parent.setTimeout("please_wait(false);", 3e4)))
      : (parent.timeoutfunc && parent.clearTimeout(parent.timeoutfunc),
        (obj.style.display = "none"),
        (frame.style.display = ""),
        setTimeout(function () {
          isIE() &&
            document.getElementById("help_switch") &&
            (document.getElementById("buttom")
              ? show_hidden_help_green(1)
              : existClassName("fix_button")
              ? show_hidden_help_top_button(1)
              : show_hidden_help(1));
        }, 10)));
}
function goto_formframe(page, flag) {
  please_wait(void 0 === flag || flag),
    (getTop(window).formframe.location.href = page);
}
function goto_page(page) {
  location.href = page;
}
function main_top_button_div_show_scroll() {
  if (isIE_or_Opera() && IE_version() < 9) {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    document.getElementById("main").style.height = frame_height - 81;
  }
}
function main_div_show_scroll() {
  if (isIE_or_Opera() && IE_version() < 9) {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    document.getElementById("main").style.height = frame_height - 51;
  }
}
function IE_RST_status() {
  if (isIE_or_Opera() && IE_version() < 9) {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    document.getElementById("content_icons").style.height = frame_height;
  }
}
function Not_IE_show_hidden_help(help_flag) {
  if (isIE()) {
    document.getElementById("help").style.height = "340px";
    document.getElementById("helpframe").style.height = "98%";
  }

  if (help_flag % 2 == 0) {
    document.getElementById("main").style.bottom = "150px";
    document.getElementById("help").style.display = "";
    document.getElementById("help_switch").className = "open_help";
  } else {
    document.getElementById("main").style.bottom = "30px";
    document.getElementById("help").style.display = "none";
    document.getElementById("help_switch").className = "close_help";
  }
}
function show_hidden_help_green(help_flag) {
  if (!isIE_or_Opera() || IE_version() >= 9) Not_IE_show_hidden_help(help_flag);
  else {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    frame_height ||
      (frame_height = getTop(window).document.getElementById("formframe_div")
        .clientHeight);
    var top_height = document
      .getElementById("top")
      .style.height.replace(/px/, "");
    help_flag % 2 == 0
      ? ((document.getElementById("main").style.height =
          frame_height - 150 + "px"),
        (document.getElementById("buttom").style.height =
          frame_height - 150 - top_height + "px"),
        (document.getElementById("help").style.display = ""),
        (document.getElementById("help_switch").className = "open_help"))
      : ((document.getElementById("help").style.display = "none"),
        (document.getElementById("help_switch").className = "close_help"),
        (document.getElementById("main").style.height =
          frame_height - 30 + "px"),
        (document.getElementById("buttom").style.height =
          frame_height - 30 - top_height + "px"));
  }
}
function show_hidden_help(help_flag) {
  if (!isIE_or_Opera() || IE_version() >= 8) Not_IE_show_hidden_help(help_flag);
  else {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    help_flag % 2 == 0
      ? ((document.getElementById("main").style.height = frame_height - 170),
        (document.getElementById("help").style.display = ""),
        (document.getElementById("help_switch").className = "open_help"))
      : ((document.getElementById("help").style.display = "none"),
        (document.getElementById("help_switch").className = "close_help"),
        (document.getElementById("main").style.height = frame_height - 50));
  }
}
function show_hidden_help_top_button(help_flag) {
  if (!isIE_or_Opera() || IE_version() >= 8) Not_IE_show_hidden_help(help_flag);
  else {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    help_flag % 2 == 0
      ? ((document.getElementById("main").style.height = frame_height - 200),
        (document.getElementById("help").style.display = ""),
        (document.getElementById("help_switch").className = "open_help"))
      : ((document.getElementById("help").style.display = "none"),
        (document.getElementById("help_switch").className = "close_help"),
        (document.getElementById("main").style.height = frame_height - 80));
  }
}
function open_help_button() {
  (document.getElementById("help").style.display = "block"),
    (document.getElementById("black_over_lay").style.display = "block");
}
function close_help_button() {
  (document.getElementById("help").style.display = "none"),
    (document.getElementById("black_over_lay").style.display = "none");
}
function port_range_interception(port) {
  return (port = parseInt(port, 10));
}
function address_parseInt(addr) {
  if ("" == addr) return addr;
  for (addr_array = addr.split("."), i = 0; i < 4; i++)
    "" == addr_array[i] && (addr_array[i] = 0),
      (addr =
        0 == i
          ? parseInt(addr_array[i], 10)
          : addr + "." + parseInt(addr_array[i], 10));
  return addr;
}
function mtu_change(wanpro) {
  var cf = document.forms[0];
  "dhcp" == old_wan_type && 1500 != wan_mtu_now
    ? ("pptp" == wanpro && wan_mtu_now < 1436) ||
      ("l2tp" == wanpro && wan_mtu_now < 1428) ||
      ("pppoe" == wanpro && wan_mtu_now < 1492) ||
      ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
      ("bigpond" == wanpro && wan_mtu_now < 1500) ||
      ("3g" == wanpro && wan_mtu_now < 1448) ||
      ("lte" == wanpro && wan_mtu_now < 1486)
      ? (cf.hid_mtu_value.value = wan_mtu_now)
      : default_mtu(wanpro)
    : "pptp" == old_wan_type && 1436 != wan_mtu_now
    ? ("dhcp" == wanpro && wan_mtu_now < 1500) ||
      ("pppoe" == wanpro && wan_mtu_now < 1492) ||
      ("l2tp" == wanpro && wan_mtu_now < 1428) ||
      ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
      ("bigpond" == wanpro && wan_mtu_now < 1500) ||
      ("3g" == wanpro && wan_mtu_now < 1448) ||
      ("lte" == wanpro && wan_mtu_now < 1486)
      ? (cf.hid_mtu_value.value = wan_mtu_now)
      : default_mtu(wanpro)
    : ("pppoe" != old_wan_type && "orange_pppoe" != old_wan_type) ||
      1492 == wan_mtu_now
    ? "mulpppoe1" == old_wan_type && 1454 != wan_mtu_now
      ? ("dhcp" == wanpro && wan_mtu_now < 1500) ||
        ("pptp" == wanpro && wan_mtu_now < 1436) ||
        ("l2tp" == wanpro && wan_mtu_now < 1428) ||
        ("pppoe" == wanpro && wan_mtu_now < 1492) ||
        ("bigpond" == wanpro && wan_mtu_now < 1500) ||
        ("3g" == wanpro && wan_mtu_now < 1448) ||
        ("lte" == wanpro && wan_mtu_now < 1486)
        ? (cf.hid_mtu_value.value = wan_mtu_now)
        : default_mtu(wanpro)
      : "bigpond" == old_wan_type && 1500 != wan_mtu_now
      ? ("dhcp" == wanpro && wan_mtu_now < 1500) ||
        ("pptp" == wanpro && wan_mtu_now < 1436) ||
        ("l2tp" == wanpro && wan_mtu_now < 1428) ||
        ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
        ("pppoe" == wanpro && wan_mtu_now < 1492) ||
        ("3g" == wanpro && wan_mtu_now < 1448) ||
        ("lte" == wanpro && wan_mtu_now < 1486)
        ? (cf.hid_mtu_value.value = wan_mtu_now)
        : default_mtu(wanpro)
      : "static" == old_wan_type && 1500 != wan_mtu_now
      ? ("dhcp" == wanpro && wan_mtu_now < 1500) ||
        ("pptp" == wanpro && wan_mtu_now < 1436) ||
        ("l2tp" == wanpro && wan_mtu_now < 1428) ||
        ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
        ("pppoe" == wanpro && wan_mtu_now < 1492) ||
        ("bigpond" == wanpro && wan_mtu_now < 1500) ||
        ("3g" == wanpro && wan_mtu_now < 1448) ||
        ("lte" == wanpro && wan_mtu_now < 1486)
        ? (cf.hid_mtu_value.value = wan_mtu_now)
        : default_mtu(wanpro)
      : "l2tp" == old_wan_type && 1428 != wan_mtu_now
      ? ("dhcp" == wanpro && wan_mtu_now < 1500) ||
        ("pptp" == wanpro && wan_mtu_now < 1436) ||
        ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
        ("pppoe" == wanpro && wan_mtu_now < 1492) ||
        ("bigpond" == wanpro && wan_mtu_now < 1500) ||
        ("3g" == wanpro && wan_mtu_now < 1448) ||
        ("lte" == wanpro && wan_mtu_now < 1486)
        ? (cf.hid_mtu_value.value = wan_mtu_now)
        : default_mtu(wanpro)
      : "3g" == old_wan_type && 1448 != wan_mtu_now
      ? ("dhcp" == wanpro && wan_mtu_now < 1500) ||
        ("pptp" == wanpro && wan_mtu_now < 1436) ||
        ("l2tp" == wanpro && wan_mtu_now < 1428) ||
        ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
        ("pppoe" == wanpro && wan_mtu_now < 1492) ||
        ("bigpond" == wanpro && wan_mtu_now < 1500) ||
        ("lte" == wanpro && wan_mtu_now < 1486)
        ? (cf.hid_mtu_value.value = wan_mtu_now)
        : default_mtu(wanpro)
      : "lte" == old_wan_type &&
        1486 != wan_mtu_now &&
        (("dhcp" == wanpro && wan_mtu_now < 1500) ||
          ("pptp" == wanpro && wan_mtu_now < 1436) ||
          ("l2tp" == wanpro && wan_mtu_now < 1428) ||
          ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
          ("pppoe" == wanpro && wan_mtu_now < 1492) ||
          ("bigpond" == wanpro && wan_mtu_now < 1500) ||
          ("3g" == wanpro && wan_mtu_now < 1448))
      ? (cf.hid_mtu_value.value = wan_mtu_now)
      : default_mtu(wanpro)
    : ("dhcp" == wanpro && wan_mtu_now < 1500) ||
      ("pptp" == wanpro && wan_mtu_now < 1436) ||
      ("l2tp" == wanpro && wan_mtu_now < 1428) ||
      ("mulpppoe1" == wanpro && wan_mtu_now < 1454) ||
      ("bigpond" == wanpro && wan_mtu_now < 1500) ||
      ("3g" == wanpro && wan_mtu_now < 1448) ||
      ("lte" == wanpro && wan_mtu_now < 1486)
    ? (cf.hid_mtu_value.value = wan_mtu_now)
    : default_mtu(wanpro);
}
function default_mtu(wanpro) {
  var cf = document.forms[0];
  cf.hid_mtu_value.value =
    "pptp" == wanpro
      ? "1436"
      : "pppoe" == wanpro || "orange_pppoe" == wanpro
      ? "1492"
      : "mulpppoe1" == wanpro
      ? "1454"
      : "l2tp" == wanpro
      ? "1428"
      : "lte" == wanpro
      ? "1486"
      : "3g" == wanpro
      ? "1448"
      : "1500";
}
function check_DNS(dnsaddr1, dnsaddr2, wan_assign, wan_ip) {
  if ("" != dnsaddr1) {
    if (0 == checkdnsaddr(dnsaddr1)) return alert("$invalid_primary_dns"), !1;
    if (1 == wan_assign && isSameIp(dnsaddr1, wan_ip))
      return alert("$invalid_primary_dns"), !1;
  }
  if ("" != dnsaddr2) {
    if (0 == checkdnsaddr(dnsaddr2)) return alert("$invalid_second_dns"), !1;
    if (1 == wan_assign && isSameIp(dnsaddr2, wan_ip))
      return alert("$invalid_second_dns"), !1;
  }
  return "" != dnsaddr1 || "" != dnsaddr2 || (alert("$dns_must_specified"), !1);
}
function check_RU_DNS(dnsaddr1, dnsaddr2, wan_assign, wan_ip) {
  if ("" != dnsaddr1) {
    if (0 == checkdnsaddr(dnsaddr1)) return alert(bh_invalid_primary_dns), !1;
    if (1 == wan_assign && isSameIp(dnsaddr1, wan_ip))
      return alert(bh_invalid_primary_dns), !1;
  }
  if ("" != dnsaddr2) {
    if (0 == checkdnsaddr(dnsaddr2)) return alert(bh_invalid_second_dns), !1;
    if (1 == wan_assign && isSameIp(dnsaddr2, wan_ip))
      return alert(bh_invalid_second_dns), !1;
  }
  return "" != dnsaddr1 || "" != dnsaddr2 || (alert(bh_dns_must_specified), !1);
}
function change_cur_time(old_str, gui_region) {
  return (
    (each_str = old_str.split(", ")),
    (week = each_str[0]),
    (show_week = change_full_week(week)),
    (date_info = each_str[1].split(" ")),
    (month = date_info[0]),
    (show_month = change_month(month)),
    (day = date_info[1]),
    (time = each_str[2]),
    (new_str =
      "German" == gui_region
        ? show_week + ", " + day + "." + show_month + ", " + time
        : show_week + ", " + show_month + " " + day + ", " + time),
    new_str
  );
}
function change_week(week) {
  return "Mon" == week
    ? "$schedule_mon"
    : "Tue" == week
    ? "$schedule_tue"
    : "Wed" == week
    ? "$schedule_wed"
    : "Thu" == week
    ? "$schedule_thu"
    : "Fri" == week
    ? "$schedule_fri"
    : "Sat" == week
    ? "$schedule_sat"
    : "Sun" == week
    ? "$schedule_sun"
    : week;
}
function change_full_week(week) {
  return "Monday" == week
    ? "$schedule_mon"
    : "Tuesday" == week
    ? "$schedule_tue"
    : "Wednesday" == week
    ? "$schedule_wed"
    : "Thursday" == week
    ? "$schedule_thu"
    : "Friday" == week
    ? "$schedule_fri"
    : "Saturday" == week
    ? "$schedule_sat"
    : "Sunday" == week
    ? "$schedule_sun"
    : week;
}
function change_month(month) {
  return "Jan" == month
    ? "$January"
    : "Feb" == month
    ? "$February"
    : "Mar" == month
    ? "$March"
    : "Apr" == month
    ? "$April"
    : "May" == month
    ? "$May"
    : "Jun" == month
    ? "$June"
    : "Jul" == month
    ? "$July"
    : "Aug" == month
    ? "$August"
    : "Sep" == month
    ? "$September"
    : "Oct" == month
    ? "$October"
    : "Nov" == month
    ? "$November"
    : "Dec" == month
    ? "$December"
    : month;
}
function SelectionTextLength(text) {
  var select_text = "";
  return (
    document.selection && document.selection.createRange
      ? (select_text = document.selection.createRange().text)
      : "" == select_text &&
        null != text.selectionStart &&
        (select_text = text.value.substring(
          text.selectionStart,
          text.selectionEnd
        )),
    select_text.length
  );
}
function keydown(e, text) {
  (190 != e.keyCode && 110 != e.keyCode) ||
    0 == text.value.length ||
    0 != SelectionTextLength(text) ||
    text.form[(getIndex(text) + 1) % text.form.length].focus();
}
function keyup(e, text) {
  3 == text.value.length &&
    ((e.keyCode > 47 && e.keyCode < 58) ||
      (e.keyCode > 95 && e.keyCode < 106)) &&
    text.form[(getIndex(text) + 1) % text.form.length].focus();
}
function keyup_n(e, text, num) {
  text.value.length == num &&
    190 != e.keyCode &&
    110 != e.keyCode &&
    9 != e.keyCode &&
    text.form[(getIndex(text) + 1) % text.form.length].focus();
}
function getIndex(input) {
  for (var index = -1, i = 0; i < input.form.length && -1 == index; )
    input.form[i] == input ? (index = i) : i++;
  return index;
}
function getObj(name) {
  return document.getElementById
    ? document.getElementById(name)
    : document.all
    ? document.all[name]
    : document.layers
    ? document.layers[name]
    : void 0;
}
function check_maxNumAdd(form, nowNum, maxNum, msg, go2href) {
  if ((nowNum = parseInt(nowNum, 10)) >= maxNum) return alert(msg), !1;
  location.href = go2href;
}
function checkIPMain(ip, max) {
  if (0 == isNumeric(ip, max)) return !1;
}
function checkIP(ip1, ip2, ip3, ip4, max) {
  return (
    0 != checkIPMain(ip1, 255) &&
    0 != checkIPMain(ip2, 255) &&
    0 != checkIPMain(ip3, 255) &&
    0 != checkIPMain(ip4, max) &&
    (0 != parseInt(ip1) ||
      0 != parseInt(ip2) ||
      0 != parseInt(ip3) ||
      0 != parseInt(ip4)) &&
    0 != parseInt(ip1)
  );
}
function isNumeric(str, max) {
  if (0 == str.length || null == str || "" == str) return !1;
  for (i = 0; i < str.length; i++) {
    var c = str.substring(i, i + 1);
    if (!("0" <= c && c <= "9")) return !1;
  }
  var i = parseInt(str);
  return !(i > max);
}
function isIE() {
  var browser = new Object();
  return (
    (browser.version = parseInt(navigator.appVersion)),
    (browser.isNs = !1),
    (browser.isIe = !1),
    -1 != navigator.appName.indexOf("Microsoft") ||
    -1 != navigator.userAgent.indexOf("Trident")
      ? (browser.isIe = !0)
      : -1 != navigator.appName.indexOf("Netscape") && (browser.isNs = !0),
    !browser.isNs && !!browser.isIe
  );
}
function get_browser() {
  return window.ActiveXObject || "ActiveXObject" in window
    ? "IE"
    : -1 != navigator.userAgent.indexOf("Chrome")
    ? "Chrome"
    : -1 != navigator.userAgent.indexOf("Firefox")
    ? "Firefox"
    : -1 != navigator.userAgent.indexOf("Safari")
    ? "Safari"
    : -1 != navigator.userAgent.indexOf("Camino")
    ? "Camino"
    : -1 != navigator.userAgent.indexOf("Gecko/")
    ? "Gecko"
    : -1 != navigator.userAgent.indexOf("Opera")
    ? "Opera"
    : "";
}
function isIE_or_Opera() {
  var browser = get_browser();
  return "IE" == browser || "Opera" == browser;
}
function IE_version() {
  var s,
    Sys = {};
  return (
    (s = navigator.userAgent.toLowerCase().match(/msie ([\d.]+)/)) &&
      (Sys.ie = s[1]),
    "6.0" == Sys.ie
      ? 6
      : "7.0" == Sys.ie
      ? 7
      : "8.0" == Sys.ie
      ? 8
      : "9.0" == Sys.ie
      ? 9
      : "10.0" == Sys.ie
      ? 10
      : 11
  );
}

function isSafari() {
  return (get_browser() === "Safari");
}

/**
 * @param {string} url
 */
function topRedirect(url) {
  if (isSafari()) {
    var aEle = document.createElement("a");
    aEle.href = url;
    aEle.target = "_top";
    aEle.click();
  } else {
    getTop(window).location.href = url;
  }
}

function _isNumeric(str) {
  var i;
  for (i = 0; i < str.length; i++) {
    var c = str.substring(i, i + 1);
    if (!("0" <= c && c <= "9")) return !1;
  }
  return !0;
}
function isSameIp(ipstr1, ipstr2) {
  var count = 0,
    ip1_array = ipstr1.split("."),
    ip2_array = ipstr2.split(".");
  for (i = 0; i < 4; i++)
    (num1 = parseInt(ip1_array[i], 10)),
      (num2 = parseInt(ip2_array[i], 10)),
      num1 == num2 && count++;
  return 4 == count;
}
function cp_ip2(from, to) {
  var total1 = 0,
    total2 = 0,
    from_array = from.split("."),
    to_array = to.split("."),
    from1 = from_array[0],
    to1 = to_array[0];
  if (parseInt(from1, 10) <= 127 && parseInt(to1, 10) >= 127) return !1;
  var from2 = from_array[1],
    from3 = from_array[2],
    from4 = from_array[3],
    to2 = to_array[1],
    to3 = to_array[2],
    to4 = to_array[3];
  return (
    (total1 += parseInt(from4, 10)),
    (total1 += 256 * parseInt(from3, 10)),
    (total1 += 256 * parseInt(from2, 10) * 256),
    (total1 += 256 * parseInt(from1, 10) * 256 * 256),
    (total2 += parseInt(to4, 10)),
    (total2 += 256 * parseInt(to3, 10)),
    (total2 += 256 * parseInt(to2, 10) * 256),
    total1 <= (total2 += 256 * parseInt(to1, 10) * 256 * 256)
  );
}
function is_sub_or_broad(be_checkip, ip, mask) {
  addr_arr = be_checkip.split(".");
  var ip_addr = 0;
  if ("255.255.255.255" == mask) return !0;
  for (i = 0; i < 4; i++)
    (addr_str = parseInt(addr_arr[i], 10)),
      (ip_addr = 256 * ip_addr + parseInt(addr_str));
  var ip_sub = isSub(ip, mask),
    ip_broadcast = isBroadcast(ip, mask);
  return ip_addr != ip_sub && ip_addr != ip_broadcast;
}
function isGateway(lanIp, lanMask, gtwIp) {
  gtw_arr = gtwIp.split(".");
  var ip_gtw = 0;
  for (i = 0; i < 4; i++)
    (gtw_str = parseInt(gtw_arr[i], 10)),
      (ip_gtw = 256 * ip_gtw + parseInt(gtw_str));
  addr_arr = lanIp.split(".");
  var ip_addr = 0;
  for (i = 0; i < 4; i++)
    (addr_str = parseInt(addr_arr[i], 10)),
      (ip_addr = 256 * ip_addr + parseInt(addr_str));
  var ip_sub = isSub(lanIp, lanMask),
    ip_broadcast = isBroadcast(lanIp, lanMask);
  return (
    parseInt(ip_sub) < parseInt(ip_gtw) &&
    parseInt(ip_gtw) < parseInt(ip_broadcast)
  );
}
function isSub(lanIp, lanMask) {
  (ip_arr = lanIp.split(".")), (mask_arr = lanMask.split("."));
  var ip_sub = 0;
  for (i = 0; i < 4; i++)
    (ip_str = parseInt(ip_arr[i], 10)),
      (mask_str = parseInt(mask_arr[i], 10)),
      (ip_sub = 256 * ip_sub + parseInt(ip_str & mask_str));
  return ip_sub;
}
function isBroadcast(lanIp, lanMask) {
  (ip_arr = lanIp.split(".")), (mask_arr = lanMask.split("."));
  var ip_broadcast = 0;
  for (i = 0; i < 4; i++)
    (ip_str = parseInt(ip_arr[i], 10)),
      (mask_str = parseInt(mask_arr[i], 10)),
      (n_str = ~mask_str + 256),
      (ip_broadcast = 256 * ip_broadcast + parseInt(ip_str | n_str));
  return ip_broadcast;
}
function isSameSubNet(lan1Ip, lan1Mask, lan2Ip, lan2Mask) {
  var count = 0;
  for (
    lan1a = lan1Ip.split("."),
      lan1m = lan1Mask.split("."),
      lan2a = lan2Ip.split("."),
      lan2m = lan2Mask.split("."),
      i = 0;
    i < 4;
    i++
  )
    (l1a_n = parseInt(lan1a[i], 10)),
      (l1m_n = parseInt(lan1m[i], 10)),
      (l2a_n = parseInt(lan2a[i], 10)),
      (l2m_n = parseInt(lan2m[i], 10)),
      (l1a_n & l1m_n) == (l2a_n & l2m_n) && count++;
  return 4 == count;
}
function checkdnsaddr(dnsaddr) {
  document.forms[0];
  var dnsArray = dnsaddr.split("."),
    dnsstr = dnsArray[0] + dnsArray[1] + dnsArray[2] + dnsArray[3],
    i = 0;
  if (
    "" == dnsArray[0] ||
    dnsArray[0] < 0 ||
    dnsArray[0] > 255 ||
    "" == dnsArray[1] ||
    dnsArray[1] < 0 ||
    dnsArray[1] > 255 ||
    "" == dnsArray[2] ||
    dnsArray[2] < 0 ||
    dnsArray[2] > 255 ||
    "" == dnsArray[3] ||
    dnsArray[3] < 0 ||
    dnsArray[3] > 255
  )
    return !1;
  for (i = 0; i < dnsstr.length; i++)
    if (
      "0" != dnsstr.charAt(i) &&
      "1" != dnsstr.charAt(i) &&
      "2" != dnsstr.charAt(i) &&
      "3" != dnsstr.charAt(i) &&
      "4" != dnsstr.charAt(i) &&
      "5" != dnsstr.charAt(i) &&
      "6" != dnsstr.charAt(i) &&
      "7" != dnsstr.charAt(i) &&
      "8" != dnsstr.charAt(i) &&
      "9" != dnsstr.charAt(i)
    )
      return !1;
  if (dnsArray[0] > 223 || 0 == dnsArray[0]) return !1;
  if ("0.0.0.0" == dnsaddr || "255.255.255.255" == dnsaddr) return !1;
  if ("127" == dnsaddr.split(".")[0]) return !1;
  if (!dnsArray || 4 != dnsArray.length) return !1;
  for (i = 0; i < 4; i++) {
    if (((thisSegment = dnsArray[i]), "" == thisSegment)) return !1;
    if (!(thisSegment >= 0 && thisSegment <= 255)) return !1;
  }
  return !0;
}
function checkipaddr(ipaddr) {
  document.forms[0];
  var ipArray = ipaddr.split("."),
    ipstr = ipArray[0] + ipArray[1] + ipArray[2] + ipArray[3],
    i = 0;
  if (
    "" == ipArray[0] ||
    ipArray[0] < 0 ||
    ipArray[0] > 255 ||
    "" == ipArray[1] ||
    ipArray[1] < 0 ||
    ipArray[1] > 255 ||
    "" == ipArray[2] ||
    ipArray[2] < 0 ||
    ipArray[2] > 255 ||
    "" == ipArray[3] ||
    ipArray[3] <= 0 ||
    ipArray[3] >= 255
  )
    return !1;
  for (i = 0; i < ipstr.length; i++)
    if (
      "0" != ipstr.charAt(i) &&
      "1" != ipstr.charAt(i) &&
      "2" != ipstr.charAt(i) &&
      "3" != ipstr.charAt(i) &&
      "4" != ipstr.charAt(i) &&
      "5" != ipstr.charAt(i) &&
      "6" != ipstr.charAt(i) &&
      "7" != ipstr.charAt(i) &&
      "8" != ipstr.charAt(i) &&
      "9" != ipstr.charAt(i)
    )
      return !1;
  if (ipArray[0] > 223 || 0 == ipArray[0]) return !1;
  if ("0.0.0.0" == ipaddr || "255.255.255.255" == ipaddr) return !1;
  if ("127" == ipaddr.split(".")[0]) return !1;
  if (!ipArray || 4 != ipArray.length) return !1;
  for (i = 0; i < 4; i++) {
    if (((thisSegment = ipArray[i]), "" == thisSegment)) return !1;
    if (!(thisSegment >= 0 && thisSegment <= 255)) return !1;
  }
  return !0;
}
function checksubnet(subnet, flag) {
  var subnetArray = subnet.split("."),
    subnetstr =
      subnetArray[0] + subnetArray[1] + subnetArray[2] + subnetArray[3],
    i = 0,
    maskTest = 0,
    validValue = !0;
  if (0 == flag && "255255255255" == subnetstr) return !1;
  if (
    "" == subnetArray[0] ||
    subnetArray[0] < 0 ||
    subnetArray[0] > 255 ||
    "" == subnetArray[1] ||
    subnetArray[1] < 0 ||
    subnetArray[1] > 255 ||
    "" == subnetArray[2] ||
    subnetArray[2] < 0 ||
    subnetArray[2] > 255 ||
    "" == subnetArray[3] ||
    subnetArray[3] < 0 ||
    subnetArray[3] > 255
  )
    return !1;
  for (i = 0; i < subnetstr.length; i++)
    if (
      "0" != subnetstr.charAt(i) &&
      "1" != subnetstr.charAt(i) &&
      "2" != subnetstr.charAt(i) &&
      "3" != subnetstr.charAt(i) &&
      "4" != subnetstr.charAt(i) &&
      "5" != subnetstr.charAt(i) &&
      "6" != subnetstr.charAt(i) &&
      "7" != subnetstr.charAt(i) &&
      "8" != subnetstr.charAt(i) &&
      "9" != subnetstr.charAt(i)
    )
      return !1;
  if (!subnetArray || 4 != subnetArray.length) return !1;
  for (i = 0; i < 4; i++) {
    if (((thisSegment = subnetArray[i]), "" == thisSegment)) return !1;
    if (!(thisSegment >= 0 && thisSegment <= 255)) return !1;
  }
  if (
    (subnetArray[0] < 255
      ? subnetArray[1] > 0 || subnetArray[2] > 0 || subnetArray[3] > 0
        ? (validValue = !1)
        : (maskTest = subnetArray[0])
      : subnetArray[1] < 255
      ? subnetArray[2] > 0 || subnetArray[3] > 0
        ? (validValue = !1)
        : (maskTest = subnetArray[1])
      : subnetArray[2] < 255
      ? subnetArray[3] > 0
        ? (validValue = !1)
        : (maskTest = subnetArray[2])
      : (maskTest = subnetArray[3]),
    validValue)
  ) {
    switch (maskTest) {
      case "0":
      case "00":
      case "000":
      case "128":
      case "192":
      case "224":
      case "240":
      case "248":
      case "252":
      case "254":
      case "255":
      case "000":
        break;
      default:
        validValue = !1;
    }
    "0.0.0.0" == subnet && (validValue = !1);
  } else validValue = !1;
  return validValue;
}
function ipNum(ipStr) {
  var total = 0,
    ip_array = ipStr.split("."),
    ip1 = ip_array[0],
    ip2 = ip_array[1],
    ip3 = ip_array[2],
    ip4 = ip_array[3];
  return (
    (total += parseInt(ip4)),
    (total += 256 * parseInt(ip3)),
    (total += 256 * parseInt(ip2) * 256),
    (total += 256 * parseInt(ip1) * 256 * 256),
    (total = parseInt(total))
  );
}
function isIncludeInvIp(inv_ip, start_ip, end_ip) {
  return (
    (inv_ip_num = ipNum(inv_ip)),
    (start_ip_num = ipNum(start_ip)),
    (end_ip_num = ipNum(end_ip)),
    inv_ip_num >= start_ip_num && inv_ip_num <= end_ip_num
  );
}
function checkgateway(gateway) {
  document.forms[0];
  var dgArray = gateway.split("."),
    dgstr = dgArray[0] + dgArray[1] + dgArray[2] + dgArray[3],
    i = 0;
  if (
    "" == dgArray[0] ||
    dgArray[0] < 0 ||
    dgArray[0] > 255 ||
    "" == dgArray[1] ||
    dgArray[1] < 0 ||
    dgArray[1] > 255 ||
    "" == dgArray[2] ||
    dgArray[2] < 0 ||
    dgArray[2] > 255 ||
    "" == dgArray[3] ||
    dgArray[3] < 0 ||
    dgArray[3] > 255
  )
    return !1;
  for (i = 0; i < dgstr.length; i++)
    if (
      "0" != dgstr.charAt(i) &&
      "1" != dgstr.charAt(i) &&
      "2" != dgstr.charAt(i) &&
      "3" != dgstr.charAt(i) &&
      "4" != dgstr.charAt(i) &&
      "5" != dgstr.charAt(i) &&
      "6" != dgstr.charAt(i) &&
      "7" != dgstr.charAt(i) &&
      "8" != dgstr.charAt(i) &&
      "9" != dgstr.charAt(i)
    )
      return !1;
  if (dgArray[0] > 223 || 0 == dgArray[0]) return !1;
  if ("0.0.0.0" == gateway || "255.255.255.255" == gateway) return !1;
  if ("127.0.0.1" == gateway) return !1;
  if (!dgArray || 4 != dgArray.length) return !1;
  for (i = 0; i < 4; i++) {
    if (((thisSegment = dgArray[i]), "" == thisSegment)) return !1;
    if (!(thisSegment >= 0 && thisSegment <= 255)) return !1;
  }
  return !0;
}
function loadhelp(fname, anchname) {
  var page = "/help/" + fname + "_help.html";
  this.help_iframe
    ? ((this.help_iframe.location.href = page + "#" + anchname),
      (this.help_iframe.location.href = page + "#" + anchname))
    : parent.help_iframe &&
      ((page = parent.help_iframe.location.href.split("#")[0]),
      (parent.help_iframe.location.href = page + "#" + anchname),
      (parent.help_iframe.location.href = page + "#" + anchname));
}
function getkeya(e) {
  var keycode;
  return window.event
    ? ((keycode = window.event.keyCode) > 47 && keycode < 58) ||
        8 == keycode ||
        (keycode > 64 && keycode < 71) ||
        (keycode > 96 && keycode < 103)
    : !e ||
        ((keycode = e.which) > 47 && keycode < 58) ||
        8 == keycode ||
        0 == keycode ||
        (keycode > 64 && keycode < 71) ||
        (keycode > 96 && keycode < 103);
}
function getkey(type, e) {
  var keycode, event;
  if (window.event) (event = window.event), (keycode = window.event.keyCode);
  else {
    if (!e) return !0;
    (event = e), (keycode = e.which);
  }
  return (
    !(!event.ctrlKey || (99 != keycode && 118 != keycode && 120 != keycode)) ||
    ("apname" == type
      ? 34 != keycode && 39 != keycode && 92 != keycode
      : "ipaddr" == type
      ? (keycode > 47 && keycode < 58) ||
        8 == keycode ||
        0 == keycode ||
        46 == keycode
      : "ssid" == type
      ? 32 != keycode
      : "wep" == type
      ? (keycode > 47 && keycode < 58) ||
        (keycode > 64 && keycode < 71) ||
        (keycode > 96 && keycode < 103) ||
        8 == keycode ||
        0 == keycode
      : "num-" == type
      ? (keycode > 47 && keycode < 56) || 8 == keycode || 0 == keycode
      : "num" == type
      ? (keycode > 47 && keycode < 58) || 8 == keycode || 0 == keycode
      : "wps_pin" == type
      ? (keycode > 47 && keycode < 58) ||
        8 == keycode ||
        0 == keycode ||
        32 == keycode ||
        45 == keycode
      : "num_letter" == type
      ? (keycode > 47 && keycode < 58) ||
        (keycode > 64 && keycode < 91) ||
        (keycode > 96 && keycode < 123) ||
        8 == keycode ||
        0 == keycode
      : "hostname" == type
      ? (keycode > 47 && keycode < 58) ||
        45 == keycode ||
        (keycode > 64 && keycode < 91) ||
        (keycode > 96 && keycode < 123) ||
        8 == keycode ||
        0 == keycode
      : "ddns_hostname" == type
      ? (keycode > 47 && keycode < 58) ||
        45 == keycode ||
        46 == keycode ||
        (keycode > 64 && keycode < 91) ||
        (keycode > 96 && keycode < 123) ||
        8 == keycode ||
        0 == keycode
      : "mac" == type
      ? (keycode > 47 && keycode < 58) ||
        (keycode > 64 && keycode < 71) ||
        (keycode > 96 && keycode < 103) ||
        8 == keycode ||
        0 == keycode ||
        58 == keycode ||
        45 == keycode
      : "folderPath" == type
      ? 47 != keycode &&
        42 != keycode &&
        63 != keycode &&
        34 != keycode &&
        60 != keycode &&
        62 != keycode &&
        124 != keycode
      : "shareName" == type
      ? 47 != keycode &&
        42 != keycode &&
        63 != keycode &&
        34 != keycode &&
        58 != keycode &&
        60 != keycode &&
        62 != keycode &&
        92 != keycode &&
        93 != keycode &&
        124 != keycode
      : "deviceName" == type
      ? (keycode > 47 && keycode < 58) ||
        45 == keycode ||
        (keycode > 64 && keycode < 91) ||
        (keycode > 96 && keycode < 123) ||
        8 == keycode ||
        0 == keycode ||
        95 == keycode
      : "mediaServerName" == type
      ? (47 != keycode &&
          42 != keycode &&
          63 != keycode &&
          34 != keycode &&
          60 != keycode &&
          62 != keycode &&
          92 != keycode &&
          93 != keycode &&
          124 != keycode) ||
        (alert("$media_server_name_colon"), !1)
      : "colon_num" == type
      ? (keycode > 47 && keycode < 58) ||
        46 == keycode ||
        8 == keycode ||
        0 == keycode
      : "vlan" == type &&
        (32 == keycode ||
          40 == keycode ||
          41 == keycode ||
          46 == keycode ||
          (keycode > 47 && keycode < 58) ||
          (keycode > 64 && keycode < 91) ||
          95 == keycode ||
          (keycode > 96 && keycode < 123)))
  );
}
function changesectype(fname) {
  var html_href;
  1 == fname.options[0].selected
    ? (html_href = "security_off.asp")
    : 1 == fname.options[1].selected
    ? (html_href = "wep.asp")
    : 1 == fname.options[2].selected
    ? (html_href = "wpa.asp")
    : 1 == fname.options[3].selected
    ? (html_href = "wpa2.asp")
    : 1 == fname.options[4].selected && (html_href = "wpas.asp"),
    (location.href = html_href);
}
function printableKeyFilter() {
  (event.keyCode < 32 || event.keyCode > 126) && (event.returnValue = !1);
}

/**
 * @param passphrase {HTMLInputElement}
 * @param passphrase_len {HTMLInputElement}
 */
function checkWpa3SAEPWD(passphrase, passphrase_len) {
  var len = passphrase.value.length;
  var cd_less_flag = 0;
  if (-1 != getTop(window).location.href.search("BRS_index.htm")) {
    cd_less_flag = 1;
  }

  if (len < 8) {
    if (1 == cd_less_flag) {
      alert(passphrase_short8)
    } else {
      alert("$passphrase_short8")
    }
    return false;
  }

  if (len > 63) {
    if (1 == cd_less_flag) {
      alert(passphrase_long63)
    } else {
      alert("$passphrase_long63")
    }
    return false;
  }

  for (i = 0; i < passphrase.value.length; i++) {
    if (0 == isValidChar_space(passphrase.value.charCodeAt(i))) {
      if (1 == cd_less_flag) {
        alert(notallowpassps)
      } else {
        alert("$notallowpassps")
      }
      return false;
    }
  }

  passphrase_len.value = len

  return true;
}
function checkpsk(passphrase, passphrase_len) {
  return IsGameRouter()
    ? checkpsk2(passphrase, passphrase_len)
    : checkpsk1(passphrase, passphrase_len);
}
function checkpsk2(passphrase, passphrase_len) {
  var cd_less_flag = 0;
  -1 != getTop(window).location.href.search("BRS_index.htm") &&
    (cd_less_flag = 1);
  var len = passphrase.value.length;
  if (64 == len) {
    for (i = 0; i < len; i++)
      if (0 == isValidHex(passphrase.value.charAt(i)))
        return (
          1 == cd_less_flag ? alert(notallowpassps) : alert("$notallowpassps"),
          !1
        );
  } else {
    if (len < 8)
      return (
        1 == cd_less_flag
          ? alert(passphrase_short8)
          : alert("$passphrase_short8"),
        !1
      );
    if (len > 63)
      return (
        1 == cd_less_flag
          ? alert(passphrase_long63)
          : alert("$passphrase_long63"),
        !1
      );
    for (i = 0; i < passphrase.value.length; i++)
      if (0 == isValidChar_space(passphrase.value.charCodeAt(i)))
        return (
          1 == cd_less_flag ? alert(notallowpassps) : alert("$notallowpassps"),
          !1
        );
  }
  return (passphrase_len.value = len), !0;
}
function checkpsk1(passphrase, passphrase_len) {
  "undefined" == typeof notallowpassps && (notallowpassps = ""),
    "undefined" == typeof passphrase_short8 && (passphrase_short8 = ""),
    "undefined" == typeof passphrase_long63 && (passphrase_long63 = "");
  var len = passphrase.value.length;
  if (64 == len) {
    for (i = 0; i < len; i++)
      if (0 == isValidHex(passphrase.value.charAt(i)))
        return alert(getText(notallowpassps, "$notallowpassps")), !1;
  } else {
    if (len < 8)
      return alert(getText(passphrase_short8, "$passphrase_short8")), !1;
    if (len > 63)
      return alert(getText(passphrase_long63, "$passphrase_long63")), !1;
    for (i = 0; i < passphrase.value.length; i++) {
      if ("ad" == arguments[2]) {
        var code = passphrase.value.charCodeAt(i);
        if (
          "34" == code ||
          "38" == code ||
          "39" == code ||
          "40" == code ||
          "41" == code ||
          "42" == code ||
          "59" == code ||
          "60" == code ||
          "62" == code
        )
          return (
            alert(
              "60G wireless passphrase doesn't support these characters \"&'()*;<>"
            ),
            !1
          );
      }
      if (0 == isValidChar_space(passphrase.value.charCodeAt(i)))
        return alert(getText(notallowpassps, "$notallowpassps")), !1;
    }
  }
  return (passphrase_len.value = len), !0;
}
function checkpsk128(passphrase, passphrase_len) {
  "undefined" == typeof notallowpassps && (notallowpassps = ""),
    "undefined" == typeof passphrase_short8 && (passphrase_short8 = ""),
    "undefined" == typeof passphrase_long127 && (passphrase_long127 = "");
  var len = passphrase.value.length;
  if (128 == len) {
    for (i = 0; i < len; i++)
      if (0 == isValidHex(passphrase.value.charAt(i)))
        return (
          alert(
            getText(
              notallowpassps,
              "$notallowpassps".replace("63", "127").replace("64", "128")
            )
          ),
          !1
        );
  } else {
    if (len < 8)
      return alert(getText(passphrase_short8, "$passphrase_short8")), !1;
    if (len > 127)
      return (
        alert(
          getText(passphrase_long127, "$passphrase_long63".replace("63", "127"))
        ),
        !1
      );
    for (i = 0; i < passphrase.value.length; i++) {
      if ("ad" == arguments[2]) {
        var code = passphrase.value.charCodeAt(i);
        if (
          "34" == code ||
          "38" == code ||
          "39" == code ||
          "40" == code ||
          "41" == code ||
          "42" == code ||
          "59" == code ||
          "60" == code ||
          "62" == code
        )
          return (
            alert(
              "60G wireless passphrase doesn't support these characters \"&'()*;<>"
            ),
            !1
          );
      }
      if (0 == isValidChar_space(passphrase.value.charCodeAt(i)))
        return (
          alert(
            getText(
              notallowpassps,
              "$notallowpassps".replace("63", "127").replace("64", "128")
            )
          ),
          !1
        );
    }
  }
  return (passphrase_len.value = len), !0;
}
var wep_128 = "$wep_128",
  wep_64 = "$wep_64";
function show_alert(wep_bit) {
  10 == wep_bit ? alert(wep_64) : 26 == wep_bit && alert(wep_128);
}
function check_key(key, wep_bit) {
  var ascii_len, i;
  if (
    (10 == wep_bit ? (ascii_len = 5) : 26 == wep_bit && (ascii_len = 13),
    key.length == wep_bit)
  ) {
    for (i = 0; i < key.length; i++)
      if (0 == isValidHex(key.charAt(i))) return show_alert(wep_bit), !1;
  } else {
    if (0 != key.length && key.length != wep_bit && key.length != ascii_len)
      return show_alert(wep_bit), !1;
    for (i = 0; i < key.length; i++)
      if (0 == isValidChar_space(key.charCodeAt(i)))
        return show_alert(wep_bit), !1;
  }
  return !0;
}
function checkwep(form) {
  form.wep_press_flag.value = 0;
  var KEY1 = form.KEY1.value,
    KEY2 = form.KEY2.value,
    KEY3 = form.KEY3.value,
    KEY4 = form.KEY4.value;
  if (13 == form.wepenc.value) {
    if (
      1 == form.wep_key_no[0].checked &&
      26 != form.KEY1.value.length &&
      13 != form.KEY1.value.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY1, 26)) return !1;
    if (
      1 == form.wep_key_no[1].checked &&
      26 != form.KEY2.value.length &&
      13 != form.KEY2.value.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY2, 26)) return !1;
    if (
      1 == form.wep_key_no[2].checked &&
      26 != form.KEY3.value.length &&
      13 != form.KEY3.value.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY3, 26)) return !1;
    if (
      1 == form.wep_key_no[3].checked &&
      26 != form.KEY4.value.length &&
      13 != form.KEY4.value.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY4, 26)) return !1;
  }
  if (5 == form.wepenc.value) {
    if (
      1 == form.wep_key_no[0].checked &&
      10 != form.KEY1.value.length &&
      5 != form.KEY1.value.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY1, 10)) return !1;
    if (
      1 == form.wep_key_no[1].checked &&
      10 != form.KEY2.value.length &&
      5 != form.KEY2.value.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY2, 10)) return !1;
    if (
      1 == form.wep_key_no[2].checked &&
      10 != form.KEY3.value.length &&
      5 != form.KEY3.value.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY3, 10)) return !1;
    if (
      1 == form.wep_key_no[3].checked &&
      10 != form.KEY4.value.length &&
      5 != form.KEY4.value.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY4, 10)) return !1;
  }
  return !0;
}
function checkwep_a(form) {
  form.wep_press_flag.value = 0;
  var KEY1 = form.KEY1_an.value,
    KEY2 = form.KEY2_an.value,
    KEY3 = form.KEY3_an.value,
    KEY4 = form.KEY4_an.value;
  if (13 == form.wepenc_an.value) {
    if (
      1 == form.wep_key_no_an[0].checked &&
      26 != KEY1.length &&
      13 != KEY1.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY1, 26)) return !1;
    if (
      1 == form.wep_key_no_an[1].checked &&
      26 != KEY2.length &&
      13 != KEY2.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY2, 26)) return !1;
    if (
      1 == form.wep_key_no_an[2].checked &&
      26 != KEY3.length &&
      13 != KEY3.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY3, 26)) return !1;
    if (
      1 == form.wep_key_no_an[3].checked &&
      26 != KEY4.length &&
      13 != KEY4.length
    )
      return alert(wep_128), !1;
    if (0 == check_key(KEY4, 26)) return !1;
  }
  if (5 == form.wepenc_an.value) {
    if (
      1 == form.wep_key_no_an[0].checked &&
      10 != KEY1.length &&
      5 != KEY1.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY1, 10)) return !1;
    if (
      1 == form.wep_key_no_an[1].checked &&
      10 != KEY2.length &&
      5 != KEY2.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY2, 10)) return !1;
    if (
      1 == form.wep_key_no_an[2].checked &&
      10 != KEY3.length &&
      5 != KEY3.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY3, 10)) return !1;
    if (
      1 == form.wep_key_no_an[3].checked &&
      10 != KEY4.length &&
      5 != KEY4.length
    )
      return alert(wep_64), !1;
    if (0 == check_key(KEY4, 10)) return !1;
  }
  return !0;
}
function HexToAscii(wepenc, wep_key_no, I, S, D) {
  var temp1 = "";
  S = S.toUpperCase();
  var optionindex = wepenc.selectedIndex;
  if (
    ("13" == wepenc.options[optionindex].value
      ? (wordCount = 26)
      : (wordCount = 10),
    1)
  ) {
    if (S.length != wordCount) {
      if (wep_key_no[I].checked) {
        var s = "Hex type key length must be ";
        alert(s + wordCount);
      }
      return (D.value = ""), (S = "");
    }
    for (i = 0; i < wordCount; i += 2) {
      var c = S.charCodeAt(i),
        d = S.charCodeAt(i + 1);
      if (c >= 48 && c <= 57) c -= 48;
      else {
        if (!(c >= 65 && c <= 70)) {
          s = "Over Hex range (0~F)";
          return alert(s), S;
        }
        c -= 55;
      }
      if (d >= 48 && d <= 57) d -= 48;
      else {
        if (!(d >= 65 && d <= 70)) {
          s = "Over Hex range (0~F)";
          return alert(s), S;
        }
        d -= 55;
      }
      var value = 16 * c + d;
      (value >= 0 && value < 32) || (value > 128 && value <= 255)
        ? ((temp1 += String.fromCharCode(92)), (temp1 += S.substring(i, i + 2)))
        : 92 == value
        ? ((temp1 += String.fromCharCode(value)),
          (temp1 += String.fromCharCode(value)))
        : (temp1 += String.fromCharCode(value));
    }
    D.value = temp1;
  }
  return S;
}
function PassPhrase40(
  passphraseStr,
  wepenc,
  wep_key_no,
  KEY1,
  KEY2,
  KEY3,
  KEY4
) {
  var seed = 0,
    pseed = new Array(0, 0, 0, 0),
    pkey = new Array(4),
    asciiObj = new Array(4);
  if (((Length = passphraseStr.value.length), 0 != Length)) {
    for (i = 0; i < Length; i++)
      pseed[i % 4] ^= passphraseStr.value.charCodeAt(i);
    (seed = pseed[0]),
      (seed += pseed[1] << 8),
      (seed += pseed[2] << 16),
      (seed += pseed[3] << 24);
  }
  for (
    KEY1.value = KEY2.value = "",
      KEY3.value = KEY4.value = "",
      pkey[0] = KEY1,
      pkey[1] = KEY2,
      pkey[2] = KEY3,
      pkey[3] = KEY4,
      j = 0;
    j < 4;
    j++
  )
    for (i = 0; i < 5; i++)
      (seed =
        2147483648 & (seed = (214013 * seed) & 4294967295)
          ? (2147483647 & seed) + 2147483648 + 2531011
          : (2147483647 & seed) + 2531011),
        (temp = (seed >> 16) & 255),
        temp < 16
          ? (pkey[j].value += "0" + temp.toString(16).toUpperCase())
          : (pkey[j].value += temp.toString(16).toUpperCase());
  for (
    asciiObj[0] = "",
      asciiObj[1] = "",
      asciiObj[2] = "",
      asciiObj[3] = "",
      k = 0;
    k < 4;
    k++
  )
    HexToAscii(wepenc, wep_key_no, k, pkey[k].value, asciiObj[k]);
  (wepkey1 = pkey[0].value),
    (wepkey2 = pkey[1].value),
    (wepkey3 = pkey[2].value),
    (wepkey4 = pkey[3].value);
}
var hex_chr = "0123456789abcdef";
function rhex(num) {
  for (str = "", j = 0; j <= 3; j++)
    str +=
      hex_chr.charAt((num >> (8 * j + 4)) & 15) +
      hex_chr.charAt((num >> (8 * j)) & 15);
  return str;
}
function str2blks_MD5(str) {
  for (
    nblk = ((str.length + 8) >> 6) + 1, blks = new Array(16 * nblk), i = 0;
    i < 16 * nblk;
    i++
  )
    blks[i] = 0;
  for (i = 0; i < str.length; i++)
    blks[i >> 2] |= str.charCodeAt(i) << ((i % 4) * 8);
  return (
    (blks[i >> 2] |= 128 << ((i % 4) * 8)),
    (blks[16 * nblk - 2] = 8 * str.length),
    blks
  );
}
function add(x, y) {
  var lsw = (65535 & x) + (65535 & y);
  return (((x >> 16) + (y >> 16) + (lsw >> 16)) << 16) | (65535 & lsw);
}
function rol(num, cnt) {
  return (num << cnt) | (num >>> (32 - cnt));
}
function cmn(q, a, b, x, s, t) {
  return add(rol(add(add(a, q), add(x, t)), s), b);
}
function ff(a, b, c, d, x, s, t) {
  return cmn((b & c) | (~b & d), a, b, x, s, t);
}
function gg(a, b, c, d, x, s, t) {
  return cmn((b & d) | (c & ~d), a, b, x, s, t);
}
function hh(a, b, c, d, x, s, t) {
  return cmn(b ^ c ^ d, a, b, x, s, t);
}
function ii(a, b, c, d, x, s, t) {
  return cmn(c ^ (b | ~d), a, b, x, s, t);
}
function calcMD5(str) {
  for (
    x = str2blks_MD5(str),
      a = 1732584193,
      b = -271733879,
      c = -1732584194,
      d = 271733878,
      i = 0;
    i < x.length;
    i += 16
  )
    (olda = a),
      (oldb = b),
      (oldc = c),
      (oldd = d),
      (a = ff(a, b, c, d, x[i + 0], 7, -680876936)),
      (d = ff(d, a, b, c, x[i + 1], 12, -389564586)),
      (c = ff(c, d, a, b, x[i + 2], 17, 606105819)),
      (b = ff(b, c, d, a, x[i + 3], 22, -1044525330)),
      (a = ff(a, b, c, d, x[i + 4], 7, -176418897)),
      (d = ff(d, a, b, c, x[i + 5], 12, 1200080426)),
      (c = ff(c, d, a, b, x[i + 6], 17, -1473231341)),
      (b = ff(b, c, d, a, x[i + 7], 22, -45705983)),
      (a = ff(a, b, c, d, x[i + 8], 7, 1770035416)),
      (d = ff(d, a, b, c, x[i + 9], 12, -1958414417)),
      (c = ff(c, d, a, b, x[i + 10], 17, -42063)),
      (b = ff(b, c, d, a, x[i + 11], 22, -1990404162)),
      (a = ff(a, b, c, d, x[i + 12], 7, 1804603682)),
      (d = ff(d, a, b, c, x[i + 13], 12, -40341101)),
      (c = ff(c, d, a, b, x[i + 14], 17, -1502002290)),
      (b = ff(b, c, d, a, x[i + 15], 22, 1236535329)),
      (a = gg(a, b, c, d, x[i + 1], 5, -165796510)),
      (d = gg(d, a, b, c, x[i + 6], 9, -1069501632)),
      (c = gg(c, d, a, b, x[i + 11], 14, 643717713)),
      (b = gg(b, c, d, a, x[i + 0], 20, -373897302)),
      (a = gg(a, b, c, d, x[i + 5], 5, -701558691)),
      (d = gg(d, a, b, c, x[i + 10], 9, 38016083)),
      (c = gg(c, d, a, b, x[i + 15], 14, -660478335)),
      (b = gg(b, c, d, a, x[i + 4], 20, -405537848)),
      (a = gg(a, b, c, d, x[i + 9], 5, 568446438)),
      (d = gg(d, a, b, c, x[i + 14], 9, -1019803690)),
      (c = gg(c, d, a, b, x[i + 3], 14, -187363961)),
      (b = gg(b, c, d, a, x[i + 8], 20, 1163531501)),
      (a = gg(a, b, c, d, x[i + 13], 5, -1444681467)),
      (d = gg(d, a, b, c, x[i + 2], 9, -51403784)),
      (c = gg(c, d, a, b, x[i + 7], 14, 1735328473)),
      (b = gg(b, c, d, a, x[i + 12], 20, -1926607734)),
      (a = hh(a, b, c, d, x[i + 5], 4, -378558)),
      (d = hh(d, a, b, c, x[i + 8], 11, -2022574463)),
      (c = hh(c, d, a, b, x[i + 11], 16, 1839030562)),
      (b = hh(b, c, d, a, x[i + 14], 23, -35309556)),
      (a = hh(a, b, c, d, x[i + 1], 4, -1530992060)),
      (d = hh(d, a, b, c, x[i + 4], 11, 1272893353)),
      (c = hh(c, d, a, b, x[i + 7], 16, -155497632)),
      (b = hh(b, c, d, a, x[i + 10], 23, -1094730640)),
      (a = hh(a, b, c, d, x[i + 13], 4, 681279174)),
      (d = hh(d, a, b, c, x[i + 0], 11, -358537222)),
      (c = hh(c, d, a, b, x[i + 3], 16, -722521979)),
      (b = hh(b, c, d, a, x[i + 6], 23, 76029189)),
      (a = hh(a, b, c, d, x[i + 9], 4, -640364487)),
      (d = hh(d, a, b, c, x[i + 12], 11, -421815835)),
      (c = hh(c, d, a, b, x[i + 15], 16, 530742520)),
      (b = hh(b, c, d, a, x[i + 2], 23, -995338651)),
      (a = ii(a, b, c, d, x[i + 0], 6, -198630844)),
      (d = ii(d, a, b, c, x[i + 7], 10, 1126891415)),
      (c = ii(c, d, a, b, x[i + 14], 15, -1416354905)),
      (b = ii(b, c, d, a, x[i + 5], 21, -57434055)),
      (a = ii(a, b, c, d, x[i + 12], 6, 1700485571)),
      (d = ii(d, a, b, c, x[i + 3], 10, -1894986606)),
      (c = ii(c, d, a, b, x[i + 10], 15, -1051523)),
      (b = ii(b, c, d, a, x[i + 1], 21, -2054922799)),
      (a = ii(a, b, c, d, x[i + 8], 6, 1873313359)),
      (d = ii(d, a, b, c, x[i + 15], 10, -30611744)),
      (c = ii(c, d, a, b, x[i + 6], 15, -1560198380)),
      (b = ii(b, c, d, a, x[i + 13], 21, 1309151649)),
      (a = ii(a, b, c, d, x[i + 4], 6, -145523070)),
      (d = ii(d, a, b, c, x[i + 11], 10, -1120210379)),
      (c = ii(c, d, a, b, x[i + 2], 15, 718787259)),
      (b = ii(b, c, d, a, x[i + 9], 21, -343485551)),
      (a = add(a, olda)),
      (b = add(b, oldb)),
      (c = add(c, oldc)),
      (d = add(d, oldd));
  return rhex(a) + rhex(b) + rhex(c) + rhex(d);
}
function PassPhrase104(passphraseStr, KEY1, KEY2, KEY3, KEY4) {
  var pseed2 = "";
  for (Length2 = passphraseStr.value.length, p = 0; p < 64; p++)
    (tempCount = p % Length2),
      (pseed2 += passphraseStr.value.substring(tempCount, tempCount + 1));
  (md5Str = calcMD5(pseed2)),
    (KEY1.value = md5Str.substring(0, 26).toUpperCase()),
    (KEY2.value = md5Str.substring(0, 26).toUpperCase()),
    (KEY3.value = md5Str.substring(0, 26).toUpperCase()),
    (KEY4.value = md5Str.substring(0, 26).toUpperCase());
}
function clickgenerate(form) {
  if (0 == form.passphraseStr.value.length) return !1;
  for (i = 0; i < form.passphraseStr.value.length; i++)
    if (0 == isValidChar_space(form.passphraseStr.value.charCodeAt(i)))
      return alert("$notallowpassp"), !1;
  1 == form.wepenc.options[0].selected
    ? PassPhrase40(
        form.passphraseStr,
        form.wepenc,
        form.wep_key_no,
        form.KEY1,
        form.KEY2,
        form.KEY3,
        form.KEY4
      )
    : PassPhrase104(
        form.passphraseStr,
        form.KEY1,
        form.KEY2,
        form.KEY3,
        form.KEY4
      ),
    (form.generate_flag.value = 1);
}
function clickgenerate_a(form) {
  if (0 == form.passphraseStr_an.value.length) return !1;
  for (i = 0; i < form.passphraseStr_an.value.length; i++)
    if (0 == isValidChar_space(form.passphraseStr_an.value.charCodeAt(i)))
      return alert("$notallowpassp"), !1;
  1 == form.wepenc_an.options[0].selected
    ? PassPhrase40(
        form.passphraseStr_an,
        form.wepenc_an,
        form.wep_key_no_an,
        form.KEY1_an,
        form.KEY2_an,
        form.KEY3_an,
        form.KEY4_an
      )
    : PassPhrase104(
        form.passphraseStr_an,
        form.KEY1_an,
        form.KEY2_an,
        form.KEY3_an,
        form.KEY4_an
      ),
    (form.generate_flag.value = 1);
}
function doPortChange(check) {
  location.href = 0 == check ? "forwarding.htm" : "triggering.htm";
}
function setBlank(OnOffFlag, formFields) {
  if (1 == OnOffFlag)
    for (var i = 1; i < setBlank.arguments.length; i++)
      setBlank.arguments[i].value = "";
}
function setDisabled(OnOffFlag, formFields) {
  for (var i = 1; i < setDisabled.arguments.length; i++)
    setDisabled.arguments[i].disabled = OnOffFlag;
}

/**
 * @param select {HTMLSelectElement}
 * @param value  {string}
 * @param text {string}
 * @param id {string?}
*/
function addOption(select, value, text, id)
{
  var option = new Option(text, value);
  if (id) option.id = id;
  select.options.add(option);
}

var securityStrValMap = {
  "Disable": 1,
  "WEP": 2,
  "WPA-PSK": 3,
  "WPA2-PSK": 4,
  "AUTO-PSK": 5,
  "WPA-Enterprise": 6,
  "WPA3-PSK": 7,
  "AUTO-WPA3-PSK": 8
};

/**
 * @param securityName {string}
 * @returns number
 */
function securityStrMapVal(securityName) {
  if (securityStrValMap.hasOwnProperty(securityName)) {
    return securityStrValMap[securityName];
  } else {
    return 0;
  }
}

/**
 * @param securityVal {number}
 * @returns string
 */
function securityValMapStr(securityVal) {
  var ret = "Disable";
  for (var key in securityStrValMap) {
    if (securityStrValMap.hasOwnProperty(key)) {
      var value = securityStrValMap[key];
      if (securityVal == value) {
        ret = key;
      }
    }
  }
  return ret;
}

function change_serv(cf) {
  "PPTP" == cf.login_type.value
    ? goto_formframe("BAS_pptp.htm", !1)
    : "L2TP" == cf.login_type.value
    ? goto_formframe("BAS_l2tp.htm", !1)
    : "Telstra Bigpond" == cf.login_type.value
    ? goto_formframe("BAS_bpa.htm", !1)
    : "PPPoE" == cf.login_type.value
    ? 0 == getTop(window).dsl_enable_flag
      ? goto_formframe("BAS_pppoe.htm", !1)
      : goto_formframe("BAS_pppoe_dsl.htm", !1)
    : "multiPPPoE" == cf.login_type.value
    ? "JP" != getTop(window).netgear_region
      ? goto_formframe("BAS_mulpppoe.htm", !1)
      : goto_formframe("BAS_mulpppoe_ww.htm", !1)
    : 1 == getTop(window).support_orange_flag &&
      "Orange PPPoE" == cf.login_type.value
    ? goto_formframe("BAS_orange_pppoe.htm")
    : 1 == getTop(window).support_orange_flag &&
      "Orange DHCP" == cf.login_type.value
    ? goto_formframe("BAS_orange_dhcp.htm")
    : 1 == getTop(window).support_singapore_isp_flag &&
      "SingTel Singapore DHCP" == cf.login_type.value
    ? goto_formframe("BAS_singtel_singa_dhcp.htm")
    : 1 == getTop(window).support_malaysia_isp_flag &&
      "Unifi Malaysia DHCP" == cf.login_type.value
    ? goto_formframe("BAS_unifi_malaysia_dhcp.htm")
    : 1 == getTop(window).support_malaysia_isp_flag &&
      "Maxis Malaysia DHCP" == cf.login_type.value
    ? goto_formframe("BAS_maxis_malaysia_dhcp.htm")
    : 1 == getTop(window).support_malaysia_pppoe_isp_flag &&
      "Unifi Malaysia PPPoE" == cf.login_type.value
    ? goto_formframe("BAS_unifi_malaysia_pppoe.htm")
    : 1 == getTop(window).support_malaysia_pppoe_isp_flag &&
      "Maxis Malaysia PPPoE" == cf.login_type.value
    ? goto_formframe("BAS_maxis_malaysia_pppoe.htm")
    : 1 == getTop(window).support_spain_isp_flag &&
      "Orange Spain DHCP" == cf.login_type.value
    ? goto_formframe("BAS_orange_spain_dhcp.htm")
    : 1 == getTop(window).support_spain_isp_flag &&
      "Movistar Spain PPPoE" == cf.login_type.value
    ? goto_formframe("BAS_movi_spain_pppoe.htm")
    : 1 == getTop(window).support_spain_isp_flag &&
      "Vodafone Spain PPPoE" == cf.login_type.value &&
      goto_formframe("BAS_voda_spain_pppoe.htm");
}
function open_all_browser(form, flag) {
  (greendl_open = 1 == flag ? 1 : 0),
    window
      .open(
        "BT_browse.htm",
        "browse",
        "resizable=0,scrollvars=yes,width=400,height=400,left=400,top=300"
      )
      .focus();
}
function change_ipv6(type) {
  switch (type) {
    case "disabled":
      getTop(window).formframe.location.href = "IPv6_disabled.htm";
      break;
    case "autoDetect":
      getTop(window).formframe.location.href = "IPv6_auto.htm";
      break;
    case "autoConfig":
      getTop(window).formframe.location.href = "IPv6_autoConfig.htm";
      break;
    case "6to4":
      getTop(window).formframe.location.href = "IPv6_tunnel.htm";
      break;
    case "bridge":
      getTop(window).formframe.location.href = "IPv6_passThrougth.htm";
      break;
    case "fixed":
      getTop(window).formframe.location.href = "IPv6_fixed.htm";
      break;
    case "dhcp":
      getTop(window).formframe.location.href = "IPv6_dhcp.htm";
      break;
    case "pppoe":
      getTop(window).formframe.location.href = "IPv6_pppoe.htm";
      break;
    case "6rd":
      getTop(window).formframe.location.href = "IPv6_6rd.htm";
      break;
    case "orange":
      getTop(window).formframe.location.href = "IPv6_orange.htm";
      break;
    case "dslite":
      1 == getTop(window).have_mape && 1 == getTop(window).is_jp_version
        ? (getTop(window).formframe.location.href = "IPv6_dslite.htm")
        : (getTop(window).formframe.location.href = "IPv6_disabled.htm");
      break;
    case "v6plus":
      1 == getTop(window).have_mape && 1 == getTop(window).is_jp_version
        ? (getTop(window).formframe.location.href = "IPv6_plus.htm")
        : (getTop(window).formframe.location.href = "IPv6_disabled.htm");
      break;
    default:
      getTop(window).formframe.location.href = "IPv6_disabled.htm";
  }
}
function maccheck_multicast(mac_addr) {
  mac_array = mac_addr.split(":");
  var mac11 = mac_array[0];
  if (
    "1" == (mac11 = mac11.substr(1, 1)) ||
    "3" == mac11 ||
    "5" == mac11 ||
    "7" == mac11 ||
    "9" == mac11 ||
    "b" == mac11 ||
    "d" == mac11 ||
    "f" == mac11 ||
    "B" == mac11 ||
    "D" == mac11 ||
    "F" == mac11
  )
    return alert("$invalid_mac"), !1;
  if (6 != mac_array.length) return alert("$invalid_mac"), !1;
  if (
    "" == mac_array[0] ||
    "" == mac_array[1] ||
    "" == mac_array[2] ||
    "" == mac_array[3] ||
    "" == mac_array[4] ||
    "" == mac_array[5]
  )
    return alert("$invalid_mac"), !1;
  if (
    ("00" == mac_array[0] &&
      "00" == mac_array[1] &&
      "00" == mac_array[2] &&
      "00" == mac_array[3] &&
      "00" == mac_array[4] &&
      "00" == mac_array[5]) ||
    ("ff" == mac_array[0] &&
      "ff" == mac_array[1] &&
      "ff" == mac_array[2] &&
      "ff" == mac_array[3] &&
      "ff" == mac_array[4] &&
      "ff" == mac_array[5]) ||
    ("FF" == mac_array[0] &&
      "FF" == mac_array[1] &&
      "FF" == mac_array[2] &&
      "FF" == mac_array[3] &&
      "FF" == mac_array[4] &&
      "FF" == mac_array[5])
  )
    return alert("$invalid_mac"), !1;
  if (
    2 != mac_array[0].length ||
    2 != mac_array[1].length ||
    2 != mac_array[2].length ||
    2 != mac_array[3].length ||
    2 != mac_array[4].length ||
    2 != mac_array[5].length
  )
    return alert("$invalid_mac"), !1;
  for (i = 0; i < mac_addr.length; i++)
    if (0 == isValidMac(mac_addr.charAt(i))) return alert("$invalid_mac"), !1;
  return !0;
}
function maccheck(mac_addr) {
  mac_array = mac_addr.split(":");
  var mac11 = mac_array[0];
  if (
    "1" == (mac11 = mac11.substr(1, 1)) ||
    "3" == mac11 ||
    "5" == mac11 ||
    "7" == mac11 ||
    "9" == mac11 ||
    "b" == mac11 ||
    "d" == mac11 ||
    "f" == mac11 ||
    "B" == mac11 ||
    "D" == mac11 ||
    "F" == mac11
  )
    return alert("$invalid_mac"), !1;
  if (6 != mac_array.length) return alert("$invalid_mac"), !1;
  if (
    "" == mac_array[0] ||
    "" == mac_array[1] ||
    "" == mac_array[2] ||
    "" == mac_array[3] ||
    "" == mac_array[4] ||
    "" == mac_array[5]
  )
    return alert("$invalid_mac"), !1;
  if (
    ("00" == mac_array[0] &&
      "00" == mac_array[1] &&
      "00" == mac_array[2] &&
      "00" == mac_array[3] &&
      "00" == mac_array[4] &&
      "00" == mac_array[5]) ||
    ("ff" == mac_array[0] &&
      "ff" == mac_array[1] &&
      "ff" == mac_array[2] &&
      "ff" == mac_array[3] &&
      "ff" == mac_array[4] &&
      "ff" == mac_array[5]) ||
    ("FF" == mac_array[0] &&
      "FF" == mac_array[1] &&
      "FF" == mac_array[2] &&
      "FF" == mac_array[3] &&
      "FF" == mac_array[4] &&
      "FF" == mac_array[5])
  )
    return alert("$invalid_mac"), !1;
  if (
    2 != mac_array[0].length ||
    2 != mac_array[1].length ||
    2 != mac_array[2].length ||
    2 != mac_array[3].length ||
    2 != mac_array[4].length ||
    2 != mac_array[5].length
  )
    return alert("$invalid_mac"), !1;
  for (i = 0; i < mac_addr.length; i++)
    if (0 == isValidMac(mac_addr.charAt(i))) return alert("$invalid_mac"), !1;
  return !0;
}
function setMAC(cf, this_mac) {
  var dflag;
  cf.MACAssign[0].checked || cf.MACAssign[1].checked
    ? ((dflag = !0),
      (cf.Spoofmac.value = this_mac),
      setDisabled(dflag, cf.Spoofmac))
    : (setDisabled((dflag = !1), cf.Spoofmac), (cf.Spoofmac.value = this_mac));
}
function maccheck_wds(mac_addr, num, form) {
  var return_num = 0;
  if ("" == mac_addr) return 2;
  var mac_array = mac_addr.split(":"),
    mac11 = mac_array[0];
  if (
    ((mac11 = mac11.substr(1, 1)),
    !(
      ("1" != mac11 &&
        "3" != mac11 &&
        "5" != mac11 &&
        "7" != mac11 &&
        "9" != mac11 &&
        "b" != mac11 &&
        "d" != mac11 &&
        "f" != mac11 &&
        "B" != mac11 &&
        "D" != mac11 &&
        "F" != mac11) ||
      ("1" == mac11 && "11" == mac_array[0])
    ))
  )
    return 1;
  if (17 != mac_addr.length && 0 != mac_addr.length) return 1;
  if (
    "" == mac_array[0] ||
    "" == mac_array[1] ||
    "" == mac_array[2] ||
    "" == mac_array[3] ||
    "" == mac_array[4] ||
    "" == mac_array[5]
  )
    return "" == mac_array[0] &&
      "" == mac_array[1] &&
      "" == mac_array[2] &&
      "" == mac_array[3] &&
      "" == mac_array[4] &&
      "" == mac_array[5]
      ? 2
      : 1;
  if (
    ("00" == mac_array[0] &&
      "00" == mac_array[1] &&
      "00" == mac_array[2] &&
      "00" == mac_array[3] &&
      "00" == mac_array[4] &&
      "00" == mac_array[5]) ||
    ("ff" == mac_array[0] &&
      "ff" == mac_array[1] &&
      "ff" == mac_array[2] &&
      "ff" == mac_array[3] &&
      "ff" == mac_array[4] &&
      "ff" == mac_array[5]) ||
    ("FF" == mac_array[0] &&
      "FF" == mac_array[1] &&
      "FF" == mac_array[2] &&
      "FF" == mac_array[3] &&
      "FF" == mac_array[4] &&
      "FF" == mac_array[5])
  )
    return 1;
  if (
    2 != mac_array[0].length ||
    2 != mac_array[1].length ||
    2 != mac_array[2].length ||
    2 != mac_array[3].length ||
    2 != mac_array[4].length ||
    2 != mac_array[5].length
  )
    return 1;
  for (i = 0; i < mac_addr.length; i++)
    if (0 == isValidMac(mac_addr.charAt(i))) return 1;
  if ("" != num && 0 != num && 1 != num)
    for (k = 1; k < num; k++)
      if (
        ((mac_str = eval("the_mac" + k)),
        "" != mac_str && mac_str.toLowerCase() == mac_addr.toLowerCase())
      )
        return 3;
  return return_num;
}
function change_sec_to_time(uptime) {
  var sec = uptime,
    day_sec = (sec = parseInt(sec)) % 86400;
  new_day = day_sec != sec ? (sec - day_sec) / 86400 : 0;
  var hour_sec = day_sec % 3600;
  new_hour = hour_sec != day_sec ? (day_sec - hour_sec) / 3600 : 0;
  var min_sec = hour_sec % 60;
  new_min = min_sec != hour_sec ? (hour_sec - min_sec) / 60 : 0;
  var new_sec = min_sec;
  if (
    ((new_day = new_day.toString()),
    (new_hour = new_hour.toString()),
    (new_min = new_min.toString()),
    (new_sec = new_sec.toString()),
    1 == new_day.length && (new_day = "0" + new_day),
    1 == new_hour.length && (new_hour = "0" + new_hour),
    1 == new_min.length && (new_min = "0" + new_min),
    1 == new_sec.length && (new_sec = "0" + new_sec),
    "00" == new_day)
  )
    var new_time = new_hour + ":" + new_min + ":" + new_sec;
  else new_time = new_day + ":" + new_hour + ":" + new_min + ":" + new_sec;
  return new_time;
}
function goTestApply() {
  var winoptions =
    "width=640,height=480,menubar=yes,scrollbars=yes,toolbar=yes,status=yes,location=yes,resizable=yes";
  "test" == run_test &&
    (1 == in_hijack
      ? window.open("BRS_check_manulConfig.html", null, winoptions)
      : window.open(getTop(window).success_url, null, winoptions));
}
function isValidForwardPort(each_char) {
  if (
    !(
      (each_char > 47 && each_char < 58) ||
      45 == each_char ||
      32 == each_char ||
      44 == each_char ||
      8 == each_char ||
      0 == each_char
    )
  )
    return !1;
}
function isValidMac(digit) {
  var macVals = new Array(
      "0",
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "9",
      "A",
      "B",
      "C",
      "D",
      "E",
      "F",
      "a",
      "b",
      "c",
      "d",
      "e",
      "f",
      ":"
    ),
    len = macVals.length,
    i = 0,
    ret = !1;
  for (i = 0; i < len && digit != macVals[i]; i++);
  return i < len && (ret = !0), ret;
}
function isValidHex(each_char) {
  var macVals = new Array(
      "0",
      "1",
      "2",
      "3",
      "4",
      "5",
      "6",
      "7",
      "8",
      "9",
      "A",
      "B",
      "C",
      "D",
      "E",
      "F",
      "a",
      "b",
      "c",
      "d",
      "e",
      "f"
    ),
    len = macVals.length,
    i = 0,
    ret = !1;
  for (i = 0; i < len && each_char != macVals[i]; i++);
  return i < len && (ret = !0), ret;
}
function isValidDevName(each_char) {
  if (
    !(
      45 == each_char ||
      95 == each_char ||
      (each_char > 47 && each_char < 58) ||
      (each_char > 64 && each_char < 91) ||
      (each_char > 96 && each_char < 123)
    )
  )
    return !1;
}
function isValidChar_space(each_char) {
  if (each_char < 32 || each_char > 127) return !1;
}
function isValidChar(each_char) {
  if (each_char < 33 || each_char > 126) return !1;
}
function isValidCharFolderName(each_char) {
  return (
    !(each_char < 32 || each_char > 126) &&
    34 != each_char &&
    42 != each_char &&
    47 != each_char &&
    58 != each_char &&
    60 != each_char &&
    62 != each_char &&
    63 != each_char &&
    92 != each_char &&
    124 != each_char &&
    void 0
  );
}
function isValidDdnsHost(each_char) {
  if (
    !(
      (each_char > 47 && each_char < 58) ||
      45 == each_char ||
      46 == each_char ||
      (each_char > 64 && each_char < 91) ||
      (each_char > 96 && each_char < 123) ||
      8 == each_char ||
      0 == each_char
    )
  )
    return !1;
}
function isValidDdnsOrayUserName(each_char) {
  if (
    !(
      (each_char > 47 && each_char < 58) ||
      45 == each_char ||
      95 == each_char ||
      (each_char > 64 && each_char < 91) ||
      (each_char > 96 && each_char < 123) ||
      8 == each_char ||
      0 == each_char
    )
  )
    return !1;
}
function isValidNumLetter(each_char) {
  return (
    (each_char > 47 && each_char < 58) ||
    (each_char > 64 && each_char < 91) ||
    (each_char > 96 && each_char < 123)
  );
}
function isValidLetter(each_char) {
  return (
    (each_char > 64 && each_char < 91) || (each_char > 96 && each_char < 123)
  );
}
function remove_space(str) {
  return (str = (str = delete_end_space(str)).replace(/^\s*/, ""));
}
function printPage() {
  window.print ? window.print() : alert("$not_support_print");
}
function top_left_nolink() {
  IsGameRouter() ||
    (1 == parent.multi_lang_router_flag &&
      (parent.topframe.document.forms[0].language.disabled = !0));
}
function wlan_txctrl(
  form,
  tx_power_ctrl,
  tx_power_ctrl_an,
  wla_channel,
  country
) {
  ("WW" != netgear_region && "" != netgear_region) ||
  "3" == country ||
  "10" == country
    ? ("100" == tx_power_ctrl
        ? (form.wl_tx_ctrl.value = "44")
        : "75" == tx_power_ctrl
        ? (form.wl_tx_ctrl.value = "18")
        : "50" == tx_power_ctrl
        ? (form.wl_tx_ctrl.value = "12")
        : "25" == tx_power_ctrl && (form.wl_tx_ctrl.value = "6"),
      "100" == tx_power_ctrl_an && (form.wla_tx_ctrl.value = "44"),
      parseInt(wla_channel) >= 36 && parseInt(wla_channel) <= 48
        ? "75" == tx_power_ctrl_an
          ? (form.wla_tx_ctrl.value = "10.5")
          : "50" == tx_power_ctrl_an
          ? (form.wla_tx_ctrl.value = "7")
          : "25" == tx_power_ctrl_an && (form.wla_tx_ctrl.value = "3.5")
        : parseInt(wla_channel) >= 52 &&
          parseInt(wla_channel) <= 165 &&
          ("75" == tx_power_ctrl_an
            ? (form.wla_tx_ctrl.value = "15.5")
            : "50" == tx_power_ctrl_an
            ? (form.wla_tx_ctrl.value = "10.5")
            : "25" == tx_power_ctrl_an && (form.wla_tx_ctrl.value = "5")))
    : ("100" == tx_power_ctrl
        ? (form.wl_tx_ctrl.value = "44")
        : "75" == tx_power_ctrl
        ? (form.wl_tx_ctrl.value = "10.5")
        : "50" == tx_power_ctrl
        ? (form.wl_tx_ctrl.value = "7")
        : "25" == tx_power_ctrl && (form.wl_tx_ctrl.value = "3.5"),
      "100" == tx_power_ctrl_an && (form.wla_tx_ctrl.value = "44"),
      parseInt(wla_channel) >= 36 && parseInt(wla_channel) <= 64
        ? "75" == tx_power_ctrl_an
          ? (form.wla_tx_ctrl.value = "12.5")
          : "50" == tx_power_ctrl_an
          ? (form.wla_tx_ctrl.value = "8.5")
          : "25" == tx_power_ctrl_an && (form.wla_tx_ctrl.value = "4")
        : parseInt(wla_channel) >= 100 &&
          ("75" == tx_power_ctrl_an
            ? (form.wla_tx_ctrl.value = "15.5")
            : "50" == tx_power_ctrl_an
            ? (form.wla_tx_ctrl.value = "10.5")
            : "25" == tx_power_ctrl_an && (form.wla_tx_ctrl.value = "5"))),
    (form.wl_tx_ctrl.value = 2 * (parseFloat(form.wl_tx_ctrl.value) + 6)),
    (form.wla_tx_ctrl.value = 2 * (parseFloat(form.wla_tx_ctrl.value) + 6)),
    "super_wifi" == tx_power_ctrl_an && (form.hid_super_wifi_an.value = "1"),
    "super_wifi" == tx_power_ctrl && (form.hid_super_wifi.value = "1");
}
function delete_end_space(str) {
  var i;
  for (i = str.length - 1; " " == str.charAt(i); i--) str = str.substring(0, i);
  return str;
}
function check_port_range(input_start_port, input_end_port, port_using) {
  return !(
    parseInt(input_start_port) <= parseInt(port_using) &&
    parseInt(input_end_port) >= parseInt(port_using)
  );
}
function check_readyshare_port(input_start_port, input_end_port, type) {
  if (
    "0" == show_enableHTTP &&
    ("LAN" == type || "ALL" == type) &&
    0 == check_port_range(input_start_port, input_end_port, 80)
  )
    return !1;
  if (
    "0" == show_enableHvia &&
    ("WAN" == type || "ALL" == type) &&
    0 == check_port_range(input_start_port, input_end_port, show_HTTP_via_port)
  )
    return !1;
  if (1 == is_ftp) {
    if (
      "0" == show_enableFTP &&
      ("LAN" == type || "ALL" == type) &&
      0 == check_port_range(input_start_port, input_end_port, 21)
    )
      return !1;
    if (
      "0" == show_enableFvia &&
      ("WAN" == type || "ALL" == type) &&
      0 == check_port_range(input_start_port, input_end_port, show_FTP_via_port)
    )
      return !1;
  }
  return !0;
}
function format_IP() {
  var argv = format_IP.arguments,
    cf = document.forms[0],
    i,
    input_form;
  for (i = 0; i < argv.length; i++)
    (input_form = eval("cf." + argv[i])),
      null != input_form &&
        "" != input_form.value &&
        (input_form.value = parseInt(input_form.value, 10).toString(10));
  return !0;
}
function close_top_window() {
  isCDLESS() && !getTop(window).hidden_upgrade
    ? toInternet()
    : "IE" == get_browser()
    ? (window.open("", "_self", ""), getTop(window).window.close())
    : (open(location, "_parent").close(),
      getTop(window).window.location.replace("about:blank"),
      getTop(window).window.close());
}
function ru_wizard() {
  if (isIE_or_Opera() && IE_version() < 9) {
    var frame_height = getTop(window)
      .document.getElementById("formframe_div")
      .style.height.replace(/px/, "");
    document.getElementsByTagName("div")[0].style.height = frame_height;
  }
}
function scroll_show() {
  if (-1 != getTop(window).location.href.indexOf("adv_index.htm")) {
    var frame_div = getTop(window).document.getElementById("formframe_div");
    ru_wizard(),
      isIE() && (frame_div.onresize = ru_wizard),
      "Opera" == get_browser() && (window.onresize = ru_wizard);
  } else
    -1 != getTop(window).location.href.indexOf("BRS_index.htm") &&
      (document.getElementsByTagName("div")[0].style.height = "500");
}
function convert(value, dataType) {
  switch (dataType) {
    case "int":
      var each_info = value.split(".");
      return 4 != each_info.length
        ? 0
        : ((value =
            parseInt(each_info[0]) +
            parseInt(each_info[1]) +
            parseInt(each_info[2]) +
            parseInt(each_info[3])),
          parseInt(value));
    default:
      return value.toString();
  }
}
function compareCols(col, dataType) {
  return function (tr1, tr2) {
    return (
      (value1 = convert(tr1.cells[col].innerHTML, dataType)),
      (value2 = convert(tr2.cells[col].innerHTML, dataType)),
      value1 < value2 ? -1 : value1 > value2 ? 1 : 0
    );
  };
}
function sortTable(tableId, col, dataType) {
  for (
    var tbody = document.getElementById(tableId).tBodies[0],
      tr = tbody.rows,
      trValue = new Array(),
      i = 0;
    i < tr.length;
    i++
  )
    trValue[i] = tr[i];
  tbody.sortCol == col
    ? trValue.reverse()
    : trValue.sort(compareCols(col, dataType));
  var fragment = document.createDocumentFragment();
  for (i = 0; i < trValue.length; i++)
    (trValue[i].className = i % 2 == 1 ? "even_line" : "odd_line"),
      (trValue[i].cells[0].innerHTML = i + 1),
      (trValue[i].cells[0].className = "subhead"),
      fragment.appendChild(trValue[i]);
  tbody.appendChild(fragment), (tbody.sortCol = col);
}
function getElementsByTagAndName(tagName, eName) {
  tags = document.getElementsByTagName(tagName);
  var elements = new Array();
  if (null != tags && tags.length > 0)
    for (var z = 0; z < tags.length; z++)
      tags[z].getAttribute("name") == eName &&
        (elements[elements.length] = tags[z]);
  return elements;
}
function isCDLESS() {
  return getTop(window).location.href.indexOf("BRS_index.htm") > -1;
}
function isWIZARD() {
  return (
    -1 != getTop(window).location.href.indexOf("adv_index.htm") &&
    1 == getTop(window).setup_wizard_flag
  );
}
function toInternet() {
  getTop(window).location.href = "to_internet_no_auth.htm";
}
function getText(str1, str2) {
  return void 0 !== str1 && (isCDLESS() || isWIZARD()) ? str1 : str2;
}
function printText(str1, str2) {
  document.write(getText(str1, str2));
}
function select_type(type) {
  void 0 === type && (type = document.forms[0].operation_type.value),
    0 == type
      ? (location.href = "rae_router.htm")
      : 1 == type
      ? (location.href = "rae_ap.htm")
      : 2 == type && goto_formframe("rae_bridge.htm");
}
function gotto_link(sub, id) {
  "None" != sub && getTop(window).open_or_close_sub(sub),
    getTop(window).click_adv_action(id);
}
function makeStr(strSize, fillChar) {
  var temp = "";
  for (i = 0; i < strSize; i++) temp += fillChar;
  return temp;
}
function grayoutElements(formFields) {
  for (var i = 0; i < grayoutElements.arguments.length; i++)
    for (
      var tag = grayoutElements.arguments[i],
        elements = document.getElementsByTagName(tag),
        j = 0,
        len = elements.length;
      j < len;
      j++
    )
      elements[j].style.color = "gray";
}
function disableElements(formFields) {
  for (var i = 0; i < disableElements.arguments.length; i++)
    for (
      var tag = disableElements.arguments[i],
        elements = document.getElementsByTagName(tag),
        j = 0,
        len = elements.length;
      j < len;
      j++
    )
      elements[j].disabled = !0;
}
function setHeight_for_IE6() {
  if (isIE_or_Opera && 6 == IE_version()) {
    var divHeight =
      ("CSS1Compat" == document.compatMode
        ? document.documentElement.clientHeight
        : document.body.clientHeight) - 149;
    (document.getElementById("footer").style.top = divHeight + "px"),
      (document.getElementById("formframe_div").style.height =
        divHeight + "px");
  }
}
function resize_pure_button() {
  for (var i = 0; i < arguments.length; i++) {
    var old_size = arguments[i].offsetWidth;
    (arguments[i].style.width = "auto"),
      arguments[i].offsetWidth < old_size &&
        (arguments[i].style.width = old_size + "px");
  }
}
function back_reload_page(page) {
  console.log("back_flag=%s", getTop(window).back_flag),
    1 == getTop(window).back_flag &&
      ((location.href = page), (getTop(window).back_flag = 0));
}

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
function IsGameRouter() {
  return getTop(window).game_router_flag;
}
function wan_preference_status() {
  var statusStr = "",
    el = document.getElementById("wan-port-status"),
    retried = 0,
    totalTry = 5;
  if (
    ("1" === wan_preference && "Link down" === wan_sfp_cable
      ? (statusStr = "$sfp_error1")
      : "1" !== wan_preference && "Link down" === wan_internet_cable
      ? (statusStr = "$sfp_error2")
      : "1" !== wan_valid_ip_address && (statusStr = "$sfp_error3"),
    "" !== statusStr)
  )
    return (el.innerHTML = statusStr), void (el.style.color = "red");
  if (window.XMLHttpRequest) var reqHttp = new XMLHttpRequest();
  else reqHttp = new ActiveXObject("Microsoft.XMLHTTP");
  (reqHttp.onreadystatechange = function () {
    if (4 == reqHttp.readyState && 200 == reqHttp.status) {
      var resp = reqHttp.responseText.trim();
      "Success;" !== resp && retried < totalTry
        ? setTimeout(function () {
            reqHttp.open("GET", "ajax_ping_result.txt", !0),
              reqHttp.send(null),
              retried++;
          }, 500)
        : "Success;" === resp
        ? ((statusStr = "$sfp_connected"),
          (el.innerHTML = statusStr),
          IsGameRouter()
            ? (el.style.color = "rgb(0,156,225)")
            : (el.style.color = "blue"))
        : retried > totalTry - 1 &&
          ((statusStr = "$sfp_error3"),
          (el.innerHTML = statusStr),
          (el.style.color = "red"));
    }
  }),
    setTimeout(function () {
      reqHttp.open("GET", "ajax_ping_result.txt", !0), reqHttp.send(null);
    }, 4e3);
}
function wan_aggregation_status() {
  var statusStr = "",
    el = document.getElementById("wan-port-status1");
  for (i = 2; i <= array_num; i++) {
    var sel_str = eval("vlanArray" + i),
      each_info_1 = sel_str.split(" "),
      lan_port = parseInt(each_info_1[4], 10),
      tmp_lan = parseInt(lan_port, 10).toString(2),
      zero = "";
    for (u = 0; u < parent.lan_ports_num + 1 - tmp_lan.length; u++) zero += "0";
    var lan_ports = (zero + tmp_lan).split("");
    if (
      1 == lan_ports[parent.lan_ports_num - wan_agg_port + 1] ||
      1 == bri_lan_tag1
    )
      return (
        (statusStr = "$wan_aggregation_error2"),
        (el.innerHTML = statusStr),
        (el.style.color = "red"),
        void (document.getElementById("sfp_port1").disabled = !0)
      );
  }
  "active" == wan_aggre
    ? ((statusStr = "$wan_aggregation_active"),
      (el.innerHTML = statusStr),
      (el.style.color = "blue"))
    : "no" == wan_aggre ||
      "Invalid bond id" == wan_aggre ||
      "Link down" === wan_internet_cable
    ? ((statusStr = "$wan_aggregation_error1"),
      (el.innerHTML = statusStr),
      (el.style.color = "red"))
    : "config" == wan_aggre &&
      ((statusStr = "$wan_aggregation_error2"),
      (el.innerHTML = statusStr),
      (el.style.color = "red"));
}
function have_wan_preference(flag) {
  1 === flag
    ? ((document.getElementById("wan_preference_tr1").style.display = ""),
      (document.getElementById("wan_preference_tr2").style.display = ""),
      (document.getElementById("wan_preference_tr3").style.display = ""),
      (document.getElementById("wan_preference_hr").style.display = ""),
      (document.getElementById("sfp_module_tr1").style.display = ""),
      (document.getElementById("sfp_module_tr2").style.display = ""),
      wan_preference_status())
    : "1" == getTop(window).wan_agg_flag
    ? ((document.getElementById("wan_preference_tr5").style.display = ""),
      (document.getElementById("wan_preference_tr6").style.display = ""),
      (document.getElementById("wan_preference_tr7").style.display = ""),
      "1" == getTop(window).have_eth5g_flag &&
        (document.getElementById("wan_preference_tr8").style.display = ""),
      (document.getElementById("wan_preference_hr1").style.display = ""),
      "1" === wan_preference && wan_aggregation_status())
    : (document.getElementById("main").style.top = "135px");
}
function change_button_position() {
  var form0 = document.forms[0],
    main = (form0.childNodes, document.createElement("div")),
    fixbutton = document.getElementsByClassName("fix_button");
  if (
    ((main.className = "main"),
    form0 && "formframe" == form0.target && fixbutton.length > 0)
  ) {
    for (var i = 0; i < form0.childNodes.length; )
      main.appendChild(form0.childNodes[i]);
    form0.appendChild(main);
    var overylay = document.getElementById("black_over_lay");
    overylay && form0.appendChild(overylay),
      (fixbutton = document.getElementsByClassName("fix_button")).length > 0 &&
        form0.appendChild(fixbutton[0]);
  }
}
function vlanlink_click() {
  1 != getTop(window).sso_limit_access &&
    ((location.href = "VLAN_IPTV.htm"),
    getTop(window).menu_color_change("vlan"),
    getTop(window).open_sub("advanced"));
}
(String.prototype.checkFolder = function () {
  for (
    var s = ["\\", '"', "'", "?", ":", "<", ">", "|", "*"], i = 0;
    i < s.length;
    i++
  )
    if (-1 != this.indexOf(s[i])) return !0;
  return !1;
}),
  (String.prototype.checkShareName = function () {
    for (
      var s = ["\\", '"', "/", "?", ":", "<", ">", "|", "*", "]"], i = 0;
      i < s.length;
      i++
    )
      if (-1 != this.indexOf(s[i])) return !0;
    return !1;
  }),
  (String.prototype.replaceXSSItem = function () {
    return this.replace(/&#92;/g, "\\")
      .replace(/&lt;/g, "<")
      .replace(/&gt;/g, ">")
      .replace(/&#40;/g, "(")
      .replace(/&#41;/g, ")")
      .replace(/&#34;/g, '"')
      .replace(/&#39;/g, "'")
      .replace(/&#35;/g, "#")
      .replace(/&#38;/g, "&");
  });
var store_location_list = { 0: ["0", "System Memory"], 1: ["1", "USB Device"] },
  pptp_dod_list = (l2tp_dod_list = pppoe_dod_list = mulpppoe_demand_list = {
    0: ["0", "Always On"],
    1: ["1", "Dial on Demand"],
    2: ["2", "Manually Connect"],
  }),
  WRegion_list = {
    0: ["0", "Africa"],
    1: ["1", "Asia"],
    2: ["2", "Australia"],
    3: ["3", "Canada"],
    4: ["11", "China"],
    5: ["4", "Europe"],
    6: ["12", "India"],
    7: ["5", "Israel"],
    8: ["6", "Japan"],
    9: ["7", "Korea"],
    10: ["13", "Malaysia"],
    11: ["8", "Mexico"],
    12: ["14", "Algeria"],
    13: ["15", "Iran"],
    14: ["16", "Egypt"],
    15: ["17", "Turkey"],
    16: ["18", "Saudi"],
    17: ["19", "Russia"],
    18: ["20", "Singapore"],
    19: ["9", "South America"],
    20: ["21", "Taiwan"],
    21: ["10", "United States"],
    22: ["22", "Hong Kong"],
    23: ["23", "Vietnam"],
    24: ["24", "New Zealand"],
    25: ["25", "United Kingdom"],
  },
  priority_list = {
    0: ["0", "Highest"],
    1: ["1", "High"],
    2: ["2", "Normal"],
    3: ["3", "Low"],
  },
  category_list = {
    0: ["0", "Applications"],
    1: ["1", "Online Gaming"],
    2: ["3", "MAC Address"],
  },
  allow_or_block_list = { 0: ["Allowed", "Allow"], 1: ["Blocked", "Block"] },
  cfAlert_Select_list = {
    0: ["0", "full"],
    1: ["1", "Hourly"],
    2: ["2", "Daily"],
    3: ["3", "Weekly"],
    4: ["4", "None"],
  },
  sysDNSProviderlist_list = {
    0: ["NETGEAR", "NETGEAR"],
    1: ["www/var/dynupdate.no-ip.com", "No-IP"],
    2: ["www/var/www.DynDNS.org", "Dyn"],
  };
function rewrite_list_value(cf, obj_name) {
  var list_name = obj_name + "_list",
    obj = eval("cf." + obj_name);
  if (null != window[list_name])
    for (var i in (console.log("rewrite_list_value():", obj),
    window[list_name]))
      for (var j = 0; j < obj.options.length; j++)
        window[list_name][i][0] == obj.options[j].value &&
          ((obj.options[j].value = window[list_name][i][1]),
          console.log(
            "[rewrite_list_value]",
            j,
            " current_value:",
            window[list_name][i][0],
            ", rewrite_value:",
            obj.options[j].value
          ));
}
function rewrite_list_value_to_original(cf, obj_name) {
  var list_name = obj_name + "_list",
    obj = eval("cf." + obj_name);
  if (null != window[list_name])
    for (var i in (console.log("rewrite_list_value_to_original():", obj),
    window[list_name]))
      for (var j = 0; j < obj.options.length; j++)
        window[list_name][i][1] == obj.options[j].value &&
          ((obj.options[j].value = window[list_name][i][0]),
          console.log(
            "[rewrite_list_value_to_original]",
            j,
            " current_value:",
            window[list_name][i][1],
            ", rewrite_value:",
            obj.options[j].value
          ));
}
function convert_value(cf, obj_name, current_value) {
  var list_name = obj_name + "_list",
    obj = eval("cf." + obj_name);
  if (null == window[list_name]) return current_value;
  for (var i in window[list_name])
    if (window[list_name][i][0] == current_value)
      return (
        console.log(
          "[convert_value]",
          i,
          " current_value:",
          current_value,
          ", convert_value:",
          window[list_name][i][1]
        ),
        window[list_name][i][1]
      );
  return current_value;
}
function convert_value_to_original(cf, obj_name) {
  var list_name = obj_name + "_list",
    obj = eval("cf." + obj_name),
    current_value = obj.value;
  if (null == window[list_name]) return current_value;
  for (var i in window[list_name])
    if (window[list_name][i][1] == current_value)
      return (
        console.log(
          "[convert_value_to_original]",
          i,
          " current_value:",
          current_value,
          ", convert_value:",
          window[list_name][i][0]
        ),
        window[list_name][i][0]
      );
  return current_value;
}
function check_size(max_value, unit, id) {
  var maxsize;
  switch (unit) {
    case "K":
    case "k":
      maxsize = 1024 * max_value;
      break;
    case "M":
    case "m":
      maxsize = 1024 * max_value * 1024;
      break;
    default:
      maxsize = max_value;
  }
  var browserCfg = {},
    ua = window.navigator.userAgent;
  ua.indexOf("MSIE") >= 1
    ? (browserCfg.ie = !0)
    : ua.indexOf("Firefox") >= 1
    ? (browserCfg.firefox = !0)
    : ua.indexOf("Chrome") >= 1 && (browserCfg.chrome = !0);
  var obj_file = document.getElementById(id);
  if ("" == obj_file.value) return !0;
  var filesize = 0;
  if (browserCfg.firefox || browserCfg.chrome)
    filesize = obj_file.files[0].size;
  else if (browserCfg.ie) {
    if (IE_version() < 11) return !0;
    filesize = new ActiveXObject("Scripting.FileSystemObject").GetFile(
      obj_file.value
    ).size;
  } else filesize = obj_file.files[0].size;
  return -1 == filesize || !(filesize > maxsize);
}
function ajax_post(post_type, input, success_cb, error_cb, ts, htm) {
  var data = input || {};
  $$.ajax({
    url: "/" + post_type + "?" + (htm || "") + " timestamp=" + ts,
    type: "POST",
    data: data,
    dataType: "json",
    contentType: "application/json; charset=utf-8",
    success: function (output) {
      console.log("success!"),
        "function" == typeof success_cb && success_cb(output);
    },
    error: function (err) {
      console.log("error!"),
        !err.responseText ||
        "string" != typeof err.responseText ||
        (-1 == err.responseText.indexOf("<html>") &&
          -1 == err.responseText.indexOf("<HTML>"))
          ? "function" == typeof error_cb && error_cb(err)
          : (document.body.innerHTML = err.responseText);
    },
  });
}
function select_internet_lable(num) {
  (document.getElementById("ipv4").className =
    0 == num ? "label_click label_click-2" : "label_unclick"),
    (document.getElementById("ipv6").className =
      1 == num ? "label_click label_click-2" : "label_unclick"),
    (select_num = num),
    0 == select_num
      ? 0 == getTop(window).dsl_enable_flag
        ? goto_formframe("BAS_basic.htm")
        : goto_formframe("BAS_basic_dsl.htm")
      : goto_formframe("IPv6_index.htm");
}
function load_ipv4_ipv6_lable(flag) {
  document.write("<div>"),
    document.write("<TABLE width=100% border=0 cellpadding=0 cellspacing=2>"),
    document.write('<tr id="labels"><td colspan=2>'),
    document.write(
      '<div id="ipv4" class="label_unclick" onclick="select_internet_lable(0)">'
    ),
    document.write('<div class="label_left"></div>'),
    document.write(
      '<div class="label_middle"><b><span id="ipv4">$ipv4_head</span></b></div>'
    ),
    document.write('<div class="label_right"></div>'),
    document.write("</div>"),
    document.write(
      '<div id="ipv6" class="label_unclick" onclick="select_internet_lable(1)">'
    ),
    document.write('<div class="label_left"></div>'),
    document.write(
      '<div class="label_middle"><b><span id="ipv6">  &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;$ipv6_head  &nbsp;&nbsp; &nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;</span></b></div>'
    ),
    document.write('<div class="label_right"></div>'),
    document.write("</div>"),
    document.write("</td>"),
    document.write("</tr>"),
    document.write("</TABLE>"),
    document.write("</div>"),
    1 != getTop(window).support_internet_lables_flag ||
    (1 == getTop(window).support_internet_lables_flag &&
      "advanced" == parent.type &&
      "ipv6" == parent.page_id)
      ? (document.getElementById("labels").style.display = "none")
      : document.write('<div id="form_div" class="labels_form">'),
    1 == flag
      ? ((document.getElementById("ipv4").className = "label_unclick"),
        (document.getElementById("ipv6").className =
          "label_click label_click-2"))
      : ((document.getElementById("ipv6").className = "label_unclick"),
        (document.getElementById("ipv4").className =
          "label_click label_click-2"));
}

function change_common_password_display(ele) {
  $$(ele).parents(".tdright").find(".input1").prop("outerHTML");
  var replaceInput,
    pwd = $$(ele).parents(".tdright").find(".input1"),
    pwd_value = $$(ele).parents(".tdright").find(".input1").val();
  "password" == pwd.attr("type")
    ? ((replaceInput = $$(ele)
        .parents(".tdright")
        .find(".input1")
        .prop("outerHTML")
        .replace("password", "text")),
      $$(ele).attr("src", "image/pwd_display_eye.png"))
    : ((replaceInput = $$(ele)
        .parents(".tdright")
        .find(".input1")
        .prop("outerHTML")
        .replace("text", "password")),
      $$(ele).attr("src", "image/pwd_close_eye.png")),
    pwd.replaceWith(replaceInput),
    $$(ele).parents(".tdright").find(".input1").val(pwd_value);
}

/**
 * @param pwd {string}
 */
function verifyPassword(pwd) {
  if (typeof pwd !== 'string') return false;

  if (pwd.length < 8 || pwd.length > 32) {
    return false;
  }

  var sameCharReg = /^.*(.)\1{2}.*$/;
  if (sameCharReg.test(pwd)) {
    return false;
  }

  var meet_complex = 0;

  if (/[A-Z]/.test(pwd)) {
    meet_complex ++;
  }

  if (/[a-z]/.test(pwd)) {
    meet_complex ++;
  }

  if (/[0-9]/.test(pwd)) {
    meet_complex ++;
  }

  if (/((?=[\x21-\x7e]+)[^A-Za-z0-9])/.test(pwd)) {
    meet_complex ++;
  }

  return (meet_complex >= 3);
}

function htmlEncode(value){
  return $$('<div/>').text(value).html();
}

function htmlDecode(value){
  return $$('<div/>').html(value).text();
}

function getCharLength(str) {
     if (str == null || str === undefined) return 0;
     if (typeof str != "string") {
         return 0;
     }
     var total = 0, charCode, i, len;
     for (i = 0, len = str.length; i < len; i++) {
         charCode = str.charCodeAt(i);
         if (charCode <= 0x007f) {
             total += 1;//字符代码在000000 – 00007F之间的，用一个字节编码
         } else if (charCode <= 0x07ff) {
             total += 2;//000080 – 0007FF之间的字符用两个字节
         } else if (charCode <= 0xffff) {
             total += 3;//000800 – 00D7FF 和 00E000 – 00FFFF之间的用三个字节，注: Unicode在范围 D800-DFFF 中不存在任何字符
         } else {
             total += 4;//010000 – 10FFFF之间的用4个字节
         }
     }
     return total;
}
 
function CutStrWithLength(elementID, len) {
    if (null == document.getElementById(elementID).value) return 0;
    var str = document.getElementById(elementID).value;
    var curStr = "";
    for (var i = 0; i < str.length; i++)
    {
        curStr += str.charAt(i);
        if(getCharLength(curStr) >= len)
        {
            document.getElementById(elementID).value = str.substring(0,i);  //截取多余的字符,并把剩余字符串赋给要进行处理的对象
            return;
        }
    }
}

/**
 * @typedef {0 | 1} ORDER_TYPE - 0: descending order 1: ascending order
 * @param func {(order: ORDER_TYPE, a: any, b: any) => number}
 * @param done {(order?: ORDER_TYPE, newArr?: any[]) => void}
 * @return {(arr: any[]) => any[]}
*/
function generateSortFunc(func, done) {
	var order = 0;
	return function(arr) {
		order = order ? 0 : 1;
		var newArr = arr.sort((function(a, b) {
			return func(order, a, b);
		}).bind(this));

		if (done) done(order, newArr);
		return newArr;
	}
}

function generateSortArrow(id) {
	return '<div id="' + id + '" class="sortArrow"><span class="sortAsc"></span><span class="sortDesc"></span></div>';
}

/**
 * @param {string} str
 * @returns {string}
*/
function toCapitalize(str) {
  var ss = str.toLowerCase();
  ss = ss.replace(ss[0],ss[0].toUpperCase());
  return ss;
}

/**
 * @param {string} querystring 
 * @param {string} key
*/
function getUrlParam(querystring, key) {
  key = key.replace(/[*+?^$$.\[\]{}()|\\\/]/g, "\\$$&"); // escape RegEx meta chars
  var match = querystring.match(new RegExp("[?&]"+key+"=([^&]+)(&|$$)"));
  return match && decodeURIComponent(match[1].replace(/\+/g, " "));
}