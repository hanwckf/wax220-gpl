#
# jie.shen@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=1905daemon
PKG_REVISION:=a244f087
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628 MACH_MT7623 GE1_SGMII_FORCE_2500 P5_RGMII_TO_MT7530_MODE SUPPORT_OPENWRT MT753X_GSW
MAKE_FLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$c)))
MAKE_FLAGS += GENL_NETLINK_SUPPORT=y
MAKE_FLAGS += PLANTFORM_DISABLE_GENL_NETLINK=y
MAKE_FLAGS += SWTICH_DSA_ARCH=y

TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

TARGET_CFLAGS += \
	-I$(LINUX_DIR)/drivers/net/ethernet/raeth

TARGET_CFLAGS += \
        -D_GNU_SOURCE \
        -I$(LINUX_DIR)/user_headers/include \
        -I$(STAGING_DIR)/usr/include/libnl-tiny \
	-I$(PKG_BUILD_DIR) \

TARGET_LDFLAGS += -lnl-tiny -lm \

define Package/1905daemon
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=1905 daemon
  SUBMENU:=Applications
  DEPENDS:=+wapp +libnl-tiny +ip-bridge
endef

define Package/1905daemon/description
  wifi app daemon
endef


define Package/1905daemon/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/map
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/p1905_managerd $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/1905ctrl $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/tp_ts_switch.sh $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/1905d.cfg $(1)/etc/map
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ethernet_cfg.txt $(1)/etc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/1905_dpp_keys.txt $(1)/etc/map
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/ethernet/libeth_1905ops.so* $(1)/usr/lib/
endef

$(eval $(call BuildPackage,1905daemon))

