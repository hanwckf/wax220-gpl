KERNEL_LOADADDR := 0x44080000

define Build/append-mtk-boot
  dd if=/dev/zero ibs=5632K count=1 | tr "\000" "\377" > $@
	dd if=$(PLATFORM_DIR)/image/bl2-$(1).img of=$@ bs=128K seek=0 conv=notrunc
	dd if=$(PLATFORM_DIR)/image/fip-$(1).bin of=$@ bs=128K seek=28 conv=notrunc
endef

define Build/append-language
	dd if=$(PLATFORM_DIR)/image/language.bin >> $@
endef

define Build/GJEncoder
  Version=`cat $(STAGING_DIR)/root-mediatek/cfg/$(word 1, $(1))/system|grep "softVersion"|awk '{print $$3}'|sed "s/'//g"`; \
  $(STAGING_DIR_HOST)/bin/imgencoder \
               --encode $@ \
               --blocksize $(word 3, $(1)) \
               --region $(word 2, $(1)) \
               --model $(word 1, $(1)) \
               --sw_version $$Version \
               --output $@.new
  rm $@
  mv $@.new $@
endef

define Device/mt7986c-ax4200-spim-nor-rfb
  DEVICE_VENDOR := MediaTek
  DEVICE_MODEL := mt7986c-ax4200-spim-nor-rfb
  DEVICE_DTS := mt7986b-spim-nor-rfb
  DEVICE_DTS_DIR := $(DTS_DIR)/mediatek
endef
TARGET_DEVICES += mt7986c-ax4200-spim-nor-rfb

define Device/mt7986c-ax4200-spim-nand-rfb
  DEVICE_VENDOR := MediaTek
  DEVICE_MODEL := mt7986c-ax4200-snand-rfb (SPI-NAND,UBI)
  DEVICE_DTS := mt7986b-spim-nand-rfb
  DEVICE_DTS_DIR := $(DTS_DIR)/mediatek
  SUPPORTED_DEVICES := mediatek,mt7986b-spim-nand-rfb
  UBINIZE_OPTS := -E 5
  BLOCKSIZE := 128k
  PAGESIZE := 2048
  IMAGE_SIZE := 131072k
  KERNEL_IN_UBI := 1
  NTGR_SW_REGION := US
  IMAGES += factory-demo-ddr3.bin
  IMAGES += factory-tw-ddr4.bin
  IMAGES += sysupgrade.enc
  IMAGE/factory-demo-ddr3.bin := append-mtk-boot demo-ddr3 | append-ubi | pad-to 93952k | append-language | check-size $$$$(IMAGE_SIZE)
  IMAGE/factory-tw-ddr4.bin := append-mtk-boot tw-ddr4 | append-ubi | pad-to 93952k | append-language | check-size $$$$(IMAGE_SIZE)
  IMAGE/sysupgrade.bin := sysupgrade-tar | append-metadata
  IMAGE/sysupgrade.enc := sysupgrade-tar | append-metadata | GJEncoder WAX220 $$$$(NTGR_SW_REGION) $$$$(BLOCKSIZE)
endef
TARGET_DEVICES += mt7986c-ax4200-spim-nand-rfb

define Device/mt7986c-ax4200-2500wan-spim-nand-rfb
  DEVICE_VENDOR := MediaTek
  DEVICE_MODEL := mt7986c-ax4200-2500wan-spim-nand-rfb (SPI-NAND,UBI)
  DEVICE_DTS := mt7986b-2500wan-spim-nand-rfb
  DEVICE_DTS_DIR := $(DTS_DIR)/mediatek
  SUPPORTED_DEVICES := mediatek,mt7986b-2500wan-spim-nand-rfb
  UBINIZE_OPTS := -E 5
  BLOCKSIZE := 128k
  PAGESIZE := 2048
  IMAGE_SIZE := 65536k
  KERNEL_IN_UBI := 1
  IMAGES += factory.bin
  IMAGE/factory.bin := append-ubi | check-size $$$$(IMAGE_SIZE)
  IMAGE/sysupgrade.bin := sysupgrade-tar | append-metadata
endef
TARGET_DEVICES += mt7986c-ax4200-2500wan-spim-nand-rfb
