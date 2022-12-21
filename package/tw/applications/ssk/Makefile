include $(TOPDIR)/rules.mk

PKG_NAME:=ssk
PKG_RELEASE:=1
PKG_VERSION:=2020-12-21

include $(INCLUDE_DIR)/package.mk

define Package/ssk
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Netgear ssk center monitor process
	DEPENDS:=+ubus +ubox +fwk +dai +libpkt_redirect
	SUBMENU:=Applications
	MENU:=1
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include/$(PKG_NAME)
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/$(PKG_NAME)/
endef

define Package/ssk/description
	This package is a demonstration of generate-package
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	$(CP) ./files/*.h $(PKG_BUILD_DIR)
	[ -d ./files/include ] && $(CP) -rf ./files/include $(PKG_BUILD_DIR)
	[ ./files/ssk ] && $(CP) ./files/ssk $(PKG_BUILD_DIR)
endef

define Package/ssk/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,ssk))
