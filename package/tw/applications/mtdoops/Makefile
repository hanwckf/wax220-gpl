include $(TOPDIR)/rules.mk

PKG_NAME:=mtdoops
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/mtdoops
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Read mtdoops partition
	DEPENDS:=
	SUBMENU:=Applications
	MENU:=1
endef

define Package/mtdoops/description
	Read mtdoops partition
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
	[ ./files/mtdoops ] && $(CP) ./files/mtdoops $(PKG_BUILD_DIR)
endef

define Package/mtdoops/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,mtdoops))
