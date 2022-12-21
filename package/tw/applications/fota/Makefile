include $(TOPDIR)/rules.mk

PKG_NAME:=fota
PKG_RELEASE:=0

include $(INCLUDE_DIR)/package.mk

define Package/fota
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=custom lib for data interface
	DEPENDS:=+curl +ca-certificates
	SUBMENU:=Applications
	MENU:=1
endef

define Package/$(PKG_NAME)/extra_provides
	echo "libfwk.so"; echo "libkvcutil.so"; echo "libcurl.so.4"; echo "libdai.so"; echo "libuci.so"; echo "libubox.so"; echo "libblobmsg_json.so"; echo "libubus.so"; echo "libkvcutil.so.1"; echo "libblobmsg_json.so.20210516"; echo "libubox.so.20210516"; echo "libubus.so.20210630"
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ -d ./files/include ] && $(CP) -rf ./files/include $(PKG_BUILD_DIR)
	[ ./files/fota ] && $(CP) ./files/fota $(PKG_BUILD_DIR)
endef

define Package/fota/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,fota))
