include $(TOPDIR)/rules.mk

PKG_NAME:=dai
PKG_RELEASE:=0

include $(INCLUDE_DIR)/package.mk

define Package/dai
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=custom lib for data interface
	DEPENDS:=+fwk +libuci +redis-server +libhiredis +libjson-c +libswitch +libnvram +mii_mgr
	#+libnvram +uci +datconf +libkvcutil
	SUBMENU:=Applications
	MENU:=1
endef

define Build/InstallDev
	mkdir -p $(1)/usr/include/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/$(PKG_NAME)/
	mkdir -p $(1)/usr/include/$(PKG_NAME)/hal
	$(CP) $(PKG_BUILD_DIR)/hal/hal_switch.h $(1)/usr/include/$(PKG_NAME)/hal
	mkdir -p $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libdai.so $(1)/usr/lib/
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ -d ./files/include ] && $(CP) -rf ./files/include $(PKG_BUILD_DIR)
	$(CP) ./files/*.so $(PKG_BUILD_DIR)
	[ -d ./files/hal ] && $(CP) -rf ./files/hal $(PKG_BUILD_DIR)
endef

define Package/dai/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,dai))
