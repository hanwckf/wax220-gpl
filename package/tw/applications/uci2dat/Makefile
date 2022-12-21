include $(TOPDIR)/rules.mk

PKG_NAME:=uci2dat
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/uci2dat
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	DEPENDS:=+libuci
	TITLE:=Translate uci config into ralink wifi dat format
	SUBMENU:=Applications
	MENU:=1
endef

define Package/uci2dat/description
	Translate uci config into ralink wifi dat format
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Package/uci2dat/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,uci2dat))
