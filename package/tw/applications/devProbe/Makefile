include $(TOPDIR)/rules.mk

PKG_NAME:=devProbe
PKG_RELEASE:=2

include $(INCLUDE_DIR)/package.mk

define Package/devProbe
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Connected device probe
	DEPENDS:=+libubus +libubox +uci +fwk +dai +libnetfilter-log +nbtscan
	SUBMENU:=Applications
	MENU:=1
endef

define Package/devProbe/description
	Connected device probe
endef

define Package/$(PKG_NAME)/extra_provides
	echo "libblobmsg_json.so"; echo "libfwk.so"; echo "libc.so.6";
endef

define Package/$(PKG_NAME)/extra_provides
	echo "libblobmsg_json.so.20210516"; 
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	$(CP) ./files/*.h $(PKG_BUILD_DIR)
	[ ./files/devProbe ] && $(CP) ./files/devProbe $(PKG_BUILD_DIR)
endef

define Package/devProbe/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,devProbe))
