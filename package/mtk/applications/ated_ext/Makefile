#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ated_ext
PKG_REVISION:=c78699ee
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=2
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk


TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

CFLAGS += \
	-I$(LINUX_DIR)/include

define Package/ated_ext
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  DEPENDS:=+libblkid
  TITLE:=ated_ext
  SUBMENU:=Applications
endef

define Package/ated_ext/description
  ated_ext Daemon
endef


define Package/ated_ext/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ated_ext $(1)/usr/bin/ated
endef


$(eval $(call BuildPackage,ated_ext))

