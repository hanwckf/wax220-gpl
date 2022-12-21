include $(TOPDIR)/rules.mk

PKG_NAME:=powerdetection
PKG_RELEASE:=0

include $(INCLUDE_DIR)/package.mk

define Package/powerdetection
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Power source detection
	DEPENDS:=+dai +fwk
	SUBMENU:=Applications
endef

define Package/$(PKG_NAME)/extra_provides
	echo "libuci.so"; echo "libubox.so"; echo "libblobmsg_json.so"; echo "libubus.so"; echo "libubox.so.20210516"; echo "libubus.so.20210630"; echo "libblobmsg_json.so.20210516";
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ ./files/powerdetection ] && $(CP) ./files/powerdetection $(PKG_BUILD_DIR)
endef

define Package/powerdetection/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,powerdetection))
