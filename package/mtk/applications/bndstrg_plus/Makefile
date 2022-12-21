#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=bndstrg_plus
PKG_REVISION:=8350508d
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/bndstrg_plus
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Band Steering Daemon Support Tri-Band
  SUBMENU:=Applications
  DEPENDS:= +libpthread +librt
endef

define Package/bndstrg_plus/description
  Band Steering  Daemon For support MT7615 New Band Steering
endef



TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT

MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

define Package/bndstrg_plus/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bndstrg2 $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bndstrg.conf $(1)/etc/
endef


$(eval $(call BuildPackage,bndstrg_plus))

