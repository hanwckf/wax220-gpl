include $(TOPDIR)/rules.mk

PKG_NAME:=mix
PKG_RELEASE:=1
PKG_VERSION:=2021-2-25

include $(INCLUDE_DIR)/package.mk

define Package/mix
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Netgear mix tools
	DEPENDS:=+uci
	SUBMENU:=Applications
	MENU:=1
endef

define Package/mix/description
	This package is a demonstration of generate-package
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Package/mix/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,mix))
