# SPDX-License-Identifier:	GPL-2.0

obj-y	+= mt7986_rfb.o
ccflags-y += -I$(srctree)/board/mediatek/common

obj-$(CONFIG_MT7986_BOOTMENU_SNOR) += bootmenu_snor.o
obj-$(CONFIG_MT7986_BOOTMENU_SNAND) += bootmenu_snand.o
obj-$(CONFIG_MT7986_BOOTMENU_EMMC) += bootmenu_emmc.o
obj-$(CONFIG_MT7986_BOOTMENU_SD) += bootmenu_sd.o
obj-$(CONFIG_MT7986_BOOTMENU_UBI) += bootmenu_ubi.o
obj-y += image_decrypt.o
ccflags-y += -I$(srctree)/board/mediatek/mt7986
