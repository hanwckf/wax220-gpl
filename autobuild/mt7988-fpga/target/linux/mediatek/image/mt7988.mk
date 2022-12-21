KERNEL_LOADADDR := 0x48080000

define Device/mediatek_mt7988-rfb
  DEVICE_VENDOR := MediaTek
  DEVICE_MODEL := MTK7988 RFB
  DEVICE_DTS := mt7988-rfb
  DEVICE_DTS_DIR := $(DTS_DIR)/mediatek
endef
TARGET_DEVICES += mediatek_mt7988-rfb

define Device/mediatek_mt7988-fpga
  DEVICE_VENDOR := MediaTek
  DEVICE_MODEL := MTK7988 FPGA
  DEVICE_DTS := mt7988-fpga
  DEVICE_DTS_DIR := $(DTS_DIR)/mediatek
endef
TARGET_DEVICES += mediatek_mt7988-fpga
