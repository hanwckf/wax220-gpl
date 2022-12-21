include $(TOPDIR)/rules.mk

PKG_NAME:=fwk
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/fwk
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	DEPENDS:=+libopenssl
	TITLE:=custom lib for framework
	SUBMENU:=Applications
endef

define Package/fwk/description
	custom lib for framework
endef

define Build/InstallDev
	mkdir -p $(1)/usr/include/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/$(PKG_NAME)/
	mkdir -p $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libfwk.so $(1)/usr/lib/
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ -d ./files/include ] && $(CP) -rf ./files/include $(PKG_BUILD_DIR)
	$(CP) ./files/*.so $(PKG_BUILD_DIR)
endef

define Package/fwk/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,fwk))
