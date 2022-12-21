include $(TOPDIR)/rules.mk

PKG_NAME:=ledControl
PKG_RELEASE:=1
PKG_VERSION:=2020-12-12

include $(INCLUDE_DIR)/package.mk

define Package/ledControl
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Netgear ledControl
	DEPENDS:=+ubus +ubox +fwk +dai +ssk +powerdetection
	SUBMENU:=Applications
	MENU:=1
endef

define Package/ledControl/description
	This package is a demonstration of generate-package
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	$(CP) ./files/*.h $(PKG_BUILD_DIR)
	[ ./files/ledControl ] && $(CP) ./files/ledControl $(PKG_BUILD_DIR)
endef

define Package/ledControl/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,ledControl))
