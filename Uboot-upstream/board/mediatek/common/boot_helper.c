// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 MediaTek Inc. All Rights Reserved.
 *
 * Author: Weijie Gao <weijie.gao@mediatek.com>
 *
 * Generic image boot helper
 */

#include <errno.h>
#include <image.h>
#include <mmc.h>
#include <part.h>
#include <part_efi.h>
#include <linux/types.h>
#include <linux/mtd/mtd.h>
#include <linux/sizes.h>

#include "upgrade_helper.h"

int boot_from_mem(ulong data_load_addr)
{
	char cmd[64];

#ifdef CONFIG_MTK_SECURE_BOOT
	int ret;

	/* boot processes for secure boot */
	/* verify FIT image */
	snprintf(cmd, sizeof(cmd),
		 "bootm start 0x%lx#config-1", data_load_addr);
	ret = run_command(cmd, 0);
	if (ret)
		return ret;

	/* run u-boot script to get dm-verity information */
	snprintf(cmd, sizeof(cmd), "source 0x%lx:script-1", data_load_addr);
	ret = run_command(cmd, 0);
	if (ret)
		return ret;

	/* using config-1 to boot */
	snprintf(cmd, sizeof(cmd), "bootm 0x%lx#config-1", data_load_addr);
#else
	/* boot processes for normal boot */
	snprintf(cmd, sizeof(cmd), "bootm 0x%lx", data_load_addr);
#endif
	return run_command(cmd, 0);
}

#ifdef CONFIG_MMC
static int _boot_from_mmc(u32 dev, struct mmc *mmc, u64 offset)
{
	ulong data_load_addr;
	u32 size;
	int ret;

	/* Set load address */
#if defined(CONFIG_SYS_LOAD_ADDR)
	data_load_addr = CONFIG_SYS_LOAD_ADDR;
#elif defined(CONFIG_LOADADDR)
	data_load_addr = CONFIG_LOADADDR;
#endif

	ret = _mmc_read(mmc, offset, (void *)data_load_addr, mmc->read_bl_len);
	if (ret)
		return ret;

	switch (genimg_get_format((const void *)data_load_addr)) {
#if defined(CONFIG_LEGACY_IMAGE_FORMAT)
	case IMAGE_FORMAT_LEGACY:
		size = image_get_image_size((const void *)data_load_addr);
		break;
#endif
#if defined(CONFIG_FIT)
	case IMAGE_FORMAT_FIT:
		size = fit_get_size((const void *)data_load_addr);
		break;
#endif
	default:
		printf("Error: no Image found in MMC device %u at 0x%llx\n",
		       dev, offset);
		return -EINVAL;
	}

	ret = _mmc_read(mmc, offset, (void *)data_load_addr, size);
	if (ret)
		return ret;

	return boot_from_mem(data_load_addr);
}

int boot_from_mmc_generic(u32 dev, int part, u64 offset)
{
	struct mmc *mmc;

	mmc = _mmc_get_dev(dev, part, false);
	if (!mmc)
		return -ENODEV;

	return _boot_from_mmc(dev, mmc, offset);
}

#ifdef CONFIG_PARTITIONS
int boot_from_mmc_partition(u32 dev, int part, const char *part_name)
{
	struct disk_partition dpart;
	struct mmc *mmc;
	int ret;

	mmc = _mmc_get_dev(dev, part, false);
	if (!mmc)
		return -ENODEV;

	ret = _mmc_find_part(mmc, part_name, &dpart);
	if (ret)
		return ret;

	return _boot_from_mmc(dev, mmc, (u64)dpart.start * dpart.blksz);
}
#endif  /* CONFIG_PARTITIONS */
#endif /* CONFIG_GENERIC_MMC */

#ifdef CONFIG_MTD
int boot_from_mtd(struct mtd_info *mtd, u64 offset)
{
	ulong data_load_addr;
	u32 size;
	int ret;

	/* Set load address */
#if defined(CONFIG_SYS_LOAD_ADDR)
	data_load_addr = CONFIG_SYS_LOAD_ADDR;
#elif defined(CONFIG_LOADADDR)
	data_load_addr = CONFIG_LOADADDR;
#endif

	ret = mtd_read_generic(mtd, offset, (void *)data_load_addr,
			       mtd->writesize);
	if (ret)
		return ret;

	switch (genimg_get_format((const void *)data_load_addr)) {
#if defined(CONFIG_LEGACY_IMAGE_FORMAT)
	case IMAGE_FORMAT_LEGACY:
		size = image_get_image_size((const void *)data_load_addr);
		break;
#endif
#if defined(CONFIG_FIT)
	case IMAGE_FORMAT_FIT:
		size = fit_get_size((const void *)data_load_addr);
		break;
#endif
	default:
		printf("Error: no Image found in %s at 0x%llx\n", mtd->name,
		       offset);
		return -EINVAL;
	}

	ret = mtd_read_generic(mtd, offset, (void *)data_load_addr, size);
	if (ret)
		return ret;

	return boot_from_mem(data_load_addr);
}
#endif

#ifdef CONFIG_DM_SPI_FLASH
int boot_from_snor(struct spi_flash *snor, u32 offset)
{
	ulong data_load_addr;
	u32 size;
	int ret;

	/* Set load address */
#if defined(CONFIG_SYS_LOAD_ADDR)
	data_load_addr = CONFIG_SYS_LOAD_ADDR;
#elif defined(CONFIG_LOADADDR)
	data_load_addr = CONFIG_LOADADDR;
#endif

	ret = snor_read_generic(snor, offset, (void *)data_load_addr,
				snor->page_size);
	if (ret)
		return ret;

	switch (genimg_get_format((const void *)data_load_addr)) {
#if defined(CONFIG_LEGACY_IMAGE_FORMAT)
	case IMAGE_FORMAT_LEGACY:
		size = image_get_image_size((const void *)data_load_addr);
		break;
#endif
#if defined(CONFIG_FIT)
	case IMAGE_FORMAT_FIT:
		size = fit_get_size((const void *)data_load_addr);
		break;
#endif
	default:
		printf("Error: no Image found in SPI-NOR at 0x%x\n", offset);
		return -EINVAL;
	}

	ret = snor_read_generic(snor, offset, (void *)data_load_addr, size);
	if (ret)
		return ret;

	return boot_from_mem(data_load_addr);
}
#endif
