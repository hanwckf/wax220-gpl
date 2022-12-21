include $(TOPDIR)/rules.mk

PKG_NAME:=product_config
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_CONFIG_DEPENDS:=

PKG_MAINTAINER:=Amber Planet <zhangdingli@twsz.com>

include $(INCLUDE_DIR)/package.mk

define Package/product_config/config
	source "$(SOURCE)/Config.in"
endef

define Package/product_config
	SECTION:=TW Properties
	CATEGORY:=TW Properties
	TITLE:=Products default config
endef

define Package/product_config/description
	Products default config
endef

define Build/Compile
	true
endef

define Package/product_config/install
	$(INSTALL_DIR) $(1)/cfg
ifeq ($(CONFIG_PRODUCT_NTGR_ROUTER_WAX206),y)
	cp -a ./ntgr_router_WAX206/generic/* $(1)/cfg
	$(INSTALL_DIR) $(1)/cfg/WAX206
	cp -a ./ntgr_router_WAX206/WAX206/* $(1)/cfg/WAX206
	$(INSTALL_DIR) $(1)/etc/config/
	cp -rf ./ntgr_router_WAX206/WAX206/wireless $(1)/etc/config/
endif

ifeq ($(CONFIG_PRODUCT_NTGR_ROUTER_WAX202),y)
	cp -a ./ntgr_router_WAX202/generic/* $(1)/cfg
	$(INSTALL_DIR) $(1)/cfg/WAX202
	cp -a ./ntgr_router_WAX202/WAX202/* $(1)/cfg/WAX202
	$(INSTALL_DIR) $(1)/etc/config/
	cp -rf ./ntgr_router_WAX202/WAX202/wireless $(1)/etc/config/
endif

ifeq ($(CONFIG_PRODUCT_NTGR_AP_WAX214v2),y)
	cp -a ./ntgr_ap_WAX214v2/generic/* $(1)/cfg
	$(INSTALL_DIR) $(1)/cfg/WAX214v2
	cp -a ./ntgr_ap_WAX214v2/WAX214v2/* $(1)/cfg/WAX214v2
	$(INSTALL_DIR) $(1)/etc/config/
	cp -rf ./ntgr_ap_WAX214v2/WAX214v2/wireless $(1)/etc/config/
endif
ifeq ($(CONFIG_PRODUCT_NTGR_AP_WAX220),y)
	cp -a ./ntgr_ap_WAX220/generic/* $(1)/cfg
	$(INSTALL_DIR) $(1)/cfg/WAX220
	cp -a ./ntgr_ap_WAX220/WAX220/* $(1)/cfg/WAX220
	$(INSTALL_DIR) $(1)/etc/config/
	cp -rf ./ntgr_ap_WAX220/WAX220/wireless $(1)/etc/config/
endif
endef

$(eval $(call BuildPackage,product_config))
