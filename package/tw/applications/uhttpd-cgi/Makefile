include $(TOPDIR)/rules.mk

PKG_NAME:=uhttpd-cgi-plugin
PKG_VERSION:=20200925

include $(INCLUDE_DIR)/package.mk

define Package/uhttpd-cgi-plugin
  SECTION:=TW Properties
  CATEGORY:=TW Properties
  SUBMENU:=Applications
  TITLE:=uHTTPd CGI and plugin
  DEPENDS:=+uhttpd +nginx +redis-server +libhiredis +libjson-c +fwk +dai +ubus
endef

define Package/uhttpd-cgi-plugin/description
	uhttpd cgi plugin
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	$(CP) ./files/*.so $(PKG_BUILD_DIR)
endef

define Package/uhttpd-cgi-plugin/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,uhttpd-cgi-plugin))
