# All rights reserved.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=warp
P4REV:=
PKG_VERSION:=
PKG_SOURCE:=warp_20220329-.tar.xz
PKG_SOURCE_URL:=
PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:= \
	WARP_VERSION \
	WARP_ATC_SUPPORT \
	WARP_DBG_SUPPORT \
	WARP_WDMA_RECYCLE_SUPPORT \
	WED_HW_RRO_SUPPORT \
	MTK_MEMORY_SHRINK \
	WARP_CHIPSET \
	WARP_WO_EMBEDDED_LOAD \
	WARP_MEMORY_LEAK_DBG

PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))

include $(INCLUDE_DIR)/package.mk

TAR_CMD=$(HOST_TAR) -C $(1)/.. $(TAR_OPTIONS)

define KernelPackage/warp
  CATEGORY:=MTK Properties
  TITLE:=MTK warp driver
ifneq ($(CONFIG_NET_MEDIATEK_HNAT), )
  DEPENDS:= +kmod-mediatek_hnat
endif
  FILES:=$(PKG_BUILD_DIR)/mtk_warp.ko
  AUTOLOAD:=$(call AutoLoad,60,mtk_warp,1)
  SUBMENU:=Drivers
  MENU:=1
endef

define KernelPackage/warp/config
	source "$(SOURCE)/config.in"
endef


MTK_WIFI_DIR:=$(TOPDIR)/../ko_module/wlan_driver/jedi
USE_BIN_DIR:=$(MTK_WIFI_DIR)/warp_driver/bin

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" V=1 \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		M="$(PKG_BUILD_DIR)" \
		$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$(c)))) \
		modules
endef

TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

MAKE_FLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$c))) 

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

define KernelPackage/warp/install
	$(INSTALL_DIR) $(1)/etc/wifi_rom
	cp $(PKG_BUILD_DIR)/bin/*WOCPU*_RAM_CODE_release.bin $(1)/etc/wifi_rom/;
endef

$(eval $(call KernelPackage,warp))


