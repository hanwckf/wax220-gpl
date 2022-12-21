include $(TOPDIR)/rules.mk

PKG_NAME:=libpkt_redirect
PKG_RELEASE:=0

include $(INCLUDE_DIR)/package.mk

define Package/libpkt_redirect
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=custom lib for data interface
	DEPENDS:=+fwk +libuci +dai
	SUBMENU:=Applications
	MENU:=1
endef

define Build/InstallDev
	mkdir -p $(1)/usr/include/$(PKG_NAME)
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/$(PKG_NAME)/
	mkdir -p $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/libpkt_redirect.so $(1)/usr/lib/
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ -d ./files/include ] && $(CP) -rf ./files/include $(PKG_BUILD_DIR)
	$(CP) ./files/*.so $(PKG_BUILD_DIR)
endef

define Package/libpkt_redirect/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,libpkt_redirect))
