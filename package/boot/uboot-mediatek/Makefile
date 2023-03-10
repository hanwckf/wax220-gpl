include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=u-boot-mtk
PKG_VERSION:=2021.01
PKG_RELEASE:=1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://gerrit.mediatek.inc/gateway/bootloader/Uboot-upstream
PKG_SOURCE_VERSION:=icb-rebb-main

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/host-build.mk

define U-Boot/Default
  BUILD_TARGET:=mediatek
  UBOOT_IMAGE:=u-boot-mtk.bin
  DEFAULT:=y
endef

define U-Boot/mt7622
  NAME:=MT7622
  BUILD_SUBTARGET:=mt7622
  UBOOT_IMAGE:=u-boot.bin
  UBOOT_CONFIG:=mt7622_rfb
endef

define U-Boot/mt7623a_unielec_u7623
  NAME:=UniElec U7623 (mt7623)
  BUILD_SUBTARGET:=mt7623
  UBOOT_CONFIG:=mt7623a_unielec_u7623_02
endef

define U-Boot/mt7623n_bpir2
  NAME:=Banana Pi R2 (mt7623)
  BUILD_SUBTARGET:=mt7623
  UBOOT_IMAGE:=u-boot.bin
  UBOOT_CONFIG:=mt7623n_bpir2
endef

define U-Boot/mt7629
  NAME:=MT7629
  BUILD_SUBTARGET:=mt7629
  UBOOT_CONFIG:=mt7629_rfb
endef

define U-Boot/mt7986
  NAME:=MT7986
  BUILD_SUBTARGET:=mt7986
  UBOOT_IMAGE:=u-boot.bin
  UBOOT_CONFIG:=mt7986_fpga
endef

UBOOT_TARGETS := mt7629 mt7622 mt7623n_bpir2 mt7623a_unielec_u7623 mt7986

UBOOT_MAKE_FLAGS += $(UBOOT_IMAGE)

Build/Exports:=$(Host/Exports)

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(UBOOT_IMAGE) $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-$(UBOOT_IMAGE)
endef

$(eval $(call BuildPackage/U-Boot))
