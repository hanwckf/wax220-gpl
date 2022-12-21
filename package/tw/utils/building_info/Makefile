include $(TOPDIR)/rules.mk

PKG_NAME:=building_info
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/building_info
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Products building info
endef

define Package/building_info/description
	Products building info
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Package/building_info/install
	tar -zxvf files/data.tar.gz -C $(1)/
endef

$(eval $(call BuildPackage,building_info))
