#
# yogender.pathak@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mapd
PKG_REVISION:=64a19d04
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

PKG_BUILD_DEPENDS:=libmapd
define Package/mapd
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=map daemon
  SUBMENU:=Applications
  DEPENDS:=+wapp +1905daemon +libmapd
endef

define Package/mapd/description
  Multi AP daemon from mediatek.
  yogender.pathak@mediatek.com
endef

define Package/mapd/config
	if PACKAGE_mapd
		config MAP_R2_SUPPORT
			bool "MAPR2"
			default n
		config MAP_R3_SUPPORT
			bool "MAPR3"
			default n
	endif
endef


define Package/mapd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mapd $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mapd_cli $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bs20 $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mapd_user_iface $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/map
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/EasyMesh_openwrt5x.sh $(1)/usr/bin/EasyMesh_openwrt.sh; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/config_agent.lua $(1)/usr/bin; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/map_config_agent.lua $(1)/usr/bin; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/map_cert_script.sh $(1)/usr/bin; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/brsw-del.sh $(1)/usr/bin;
	$(CP) $(PKG_BUILD_DIR)/wts_bss_info_config  $(1)/etc/map
	$(CP) $(PKG_BUILD_DIR)/mapd_user.cfg $(1)/etc/map
	$(CP) $(PKG_BUILD_DIR)/mapd_default.cfg  $(1)/etc/map
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/easymesh_init $(1)/etc/init.d/easymesh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/easymesh_bridge_init $(1)/etc/init.d/easymesh_bridge
endef

$(eval $(call BuildPackage,mapd))
