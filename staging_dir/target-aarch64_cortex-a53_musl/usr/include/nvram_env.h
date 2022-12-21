#ifndef _NVRAM_ENV_H
#define _NVRAM_ENV_H 	1

#include "nvram.h"

extern		void  nvram_printenv(int index, int argc, char *argv[]);
extern unsigned char *nvram_getenv  (int index, unsigned char *name);
extern		int   nvram_setenv  (int index, int argc, char *argv[]);
extern		int   nvram_buff_setenv  (int index, int argc, char *argv[]);
extern 		int   do_nvram_commit(int index);
extern unsigned	long  crc32	 (unsigned long, const unsigned char *, unsigned);


static block_t fb[FLASH_BLOCK_NUM+EXTEND_BLOCK_NUM] =
{
#ifdef CONFIG_DUAL_IMAGE
	{
		.name = "uboot",
		.flash_offset =  0x0,
		.flash_max_len = ENV_UBOOT_SIZE,
		.valid = 0,
		.max_cache_idx = 0
	},
#endif
#if 0
	{
		.name = FB_2860_BLOCK_NAME,
		.flash_offset =  0x2000,
#ifdef CONFIG_CONFIG_SHRINK
		.flash_max_len = ENV_BLK_SIZE*16,
#else
		.flash_max_len = ENV_BLK_SIZE*4,
#endif
		.valid = 0,
		.max_cache_idx = 0
	},
	{
		.name = "dev2",
		.flash_offset = 0x6000,
		.flash_max_len = ENV_BLK_SIZE*2,
		.valid = 0,
		.max_cache_idx = 0
	},
	{
		.name = "dev3",
		.flash_offset = 0x8000,
		.flash_max_len = ENV_BLK_SIZE*2,
		.valid = 0,
		.max_cache_idx = 0
	},
	{
		.name = "cert",
		.flash_offset = 0xe000,
		.flash_max_len = ENV_BLK_SIZE,
		.valid = 0,
		.max_cache_idx = 0
#if defined CONFIG_EXTEND_NVRAM
	},
	{
		.name = FB_CONFIG2_BLOCK_NAME,
		.flash_offset = 0x0,
		.flash_max_len = ENV_BLK_SIZE * 8,
		.valid = 0,
		.max_cache_idx = 0
#if defined CONFIG_WAPI_SUPPORT
	},
	{
		.name = "wapi",
		.flash_offset = 0x8000,
		.flash_max_len = ENV_BLK_SIZE * 8,
		.valid = 0,
		.max_cache_idx = 0
#else
	},
	{
		.name = "tr069cert",
		.flash_offset = 0x8000,
		.valid = 0,
		.max_cache_idx = 0
#endif
#endif
	}
#else
	{
		.name = "FENV",
		.flash_offset =  0x40000,
		.flash_max_len = ENV_BLK_SIZE * 1,
		.valid = 0,
		.max_cache_idx = 0
	},
	{
		.name = "UENV",
		.flash_offset =  0x60000,
		.flash_max_len = ENV_BLK_SIZE * 1,
		.valid = 0,
		.max_cache_idx = 0
	},
#endif
};
#endif
