include $(TOPDIR)/rules.mk

PKG_NAME:=telnetenabled
PKG_RELEASE:=1
PKG_VERSION:=2021-1-27

include $(INCLUDE_DIR)/package.mk

define Package/telnetenabled
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Netgear telnetenabled
	DEPENDS:=+ubus +ubox
	SUBMENU:=Applications
	MENU:=1
endef

define Package/telnetenabled/description
	This package is a demonstration of generate-package
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	$(CP) ./files/*.h $(PKG_BUILD_DIR)
	[ ./files/telnetenabled ] && $(CP) ./files/telnetenabled $(PKG_BUILD_DIR)
endef

define Package/telnetenabled/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,telnetenabled))
