# SPDX-License-Identifier:	GPL-2.0

# Empty file to make sure compilation pass
obj-y += empty.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_MEDIATEK_BOOTMENU) += load_data.o upgrade_helper.o boot_helper.o \
				   untar.o image_helper.o
ifdef CONFIG_MTD
obj-$(CONFIG_MEDIATEK_BOOTMENU) += ubi_helper.o
endif

obj-$(CONFIG_MEDIATEK_BOOTMENU) += cmd_mtkupgrade.o cmd_mtkload.o \
				   cmd_mtkboardboot.o cmd_mtkautoboot.o
endif

obj-$(CONFIG_MTK_ANTI_ROLLBACK) += mtk_ar.o mtk_efuse.o
