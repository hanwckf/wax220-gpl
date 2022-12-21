include $(TOPDIR)/rules.mk

PKG_NAME:=protest
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/protest
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Factory Manufacture Command
	DEPENDS:=+dai +fwk +libnvram
	SUBMENU:=Applications
	MENU:=1
endef

define Package/protest/description
	Factory Manufacture Command
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ ./files/protest ] && $(CP) ./files/protest $(PKG_BUILD_DIR)
endef

define Package/protest/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,protest))
