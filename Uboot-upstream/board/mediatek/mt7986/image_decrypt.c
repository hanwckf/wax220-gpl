#include <common.h>
#include <config.h>
#include <image.h>
#include <aes.h>
#include <asm/io.h>

#define ENCRPTED_IMG_TAG  "encrpted_img"
#define AES_KEY_256  "he9-4+M!)d6=m~we1,q2a3d1n&2*Z^%8$"
#define AES_NOR_IV  "J%1iQl8$=lm-;8AE@"

typedef  struct
{
	char model[32]; 	   /*model name*/
	char region[32];	   /*region*/
	char version[64];	   /*version*/
	char dateTime[64];	   /*date*/
	char reserved[320];    /*reserved space, if add struct member, please adjust this reserved size to keep the head total size is 512 bytes*/
} __attribute__((__packed__)) image_head_t;

typedef  struct
{
	char checkSum[4];		/*checkSum*/
} __attribute__((__packed__)) image_tail_t;

int decrypt_image(void *data, size_t *size)
{
	u32 min_size = 0;
	unsigned char *src_addr = NULL;
	unsigned char *dst_addr = NULL;
	image_head_t *image_head = NULL;
	char *image_tag = NULL;
	//char *fenv_model = NULL;
	//char *fenv_region = NULL;
	u32 image_size = 0;
	u32 encrypted_size = 0;
	u32 block_size = 0;
	u32 checksum = 0;
	u32 curr_checksum = 0;
	unsigned char key_exp[AES256_EXPAND_KEY_LENGTH] = {0};
	unsigned int aes_blocks = 0;

	/* env_set("decrypt_result", "bad"); */

	min_size = sizeof(image_head_t) + strlen(ENCRPTED_IMG_TAG) + 4 * 2;

	if (size < min_size)
	{
		printf("Image head not found!\n");
		goto good;
	}

	src_addr = (unsigned char *)data;
	dst_addr = (unsigned char *)data;

	image_head = (image_head_t *)src_addr;
	src_addr += sizeof(image_head_t);

	image_tag = (char *)src_addr;
	if (strncmp(image_tag, ENCRPTED_IMG_TAG, strlen(ENCRPTED_IMG_TAG)))
	{
		printf("Encrpted tag not found!\n");
		goto good;
	}
	src_addr += strlen(ENCRPTED_IMG_TAG);

	printf("Image is encrypted\n");
	printf("model: %s\n", image_head->model);
	printf("region: %s\n", image_head->region);
	printf("version: %s\n", image_head->version);
	printf("dateTime: %s\n", image_head->dateTime);

#if 0
	fenv_model = env_get("fenv_model");
	if (!fenv_model || strcmp(fenv_model, image_head->model))
	{
		printf("Image model not match!\n");
		return 1;
	}

	fenv_region = env_get("fenv_region");
	if (!fenv_region || strcmp(fenv_region, image_head->region))
	{
		printf("Image region not match!\n");
		return 1;
	}
#endif

	image_size = ntohl(*(u32 *)src_addr);
	src_addr += sizeof(u32);
	printf("size: 0x%lx\n", image_size);

	encrypted_size = DIV_ROUND_UP(image_size, AES_BLOCK_LENGTH) * AES_BLOCK_LENGTH;

	block_size = ntohl(*(u32 *)src_addr);
	src_addr += sizeof(u32);
	printf("block size: 0x%lx\n", block_size);
	if (block_size % AES_BLOCK_LENGTH)
	{
		printf("Image block size not times of AES_BLOCK_LENGTH!\n");
		return 1;
	}

	if (size < (min_size + encrypted_size + sizeof(image_tail_t)))
	{
		printf("Image incomplete!\n");
		return 1;
	}

	checksum = ntohl(*(u32 *)(src_addr + encrypted_size));
	printf("checksum: 0x%lx\n", checksum);

	curr_checksum = crc32_no_comp(0, (uchar *)data, min_size + encrypted_size);
	if (curr_checksum != checksum)
	{
		printf("Image checksum error!\n");
		return 1;
	}

	printf("Decrypt image...\n");

	aes_expand_key((u8 *)AES_KEY_256, AES256_KEY_LENGTH, key_exp);
	for (min_size = 0; min_size < encrypted_size; min_size += block_size)
	{
		if (min_size + block_size > encrypted_size)
		{
			block_size = encrypted_size - min_size;
		}

		aes_blocks = DIV_ROUND_UP(block_size, AES_BLOCK_LENGTH);
		aes_cbc_decrypt_blocks(AES256_KEY_LENGTH, key_exp, (u8 *)AES_NOR_IV, (u8 *)src_addr, (u8 *)dst_addr, aes_blocks);

		src_addr += block_size;
		dst_addr += block_size;
	}
	printf("Decrypt finish\n");

	/* env_set_hex("filesize", image_size); */
  *size = image_size;

good:
	/* env_set("decrypt_result", "good"); */
	return 0;
}
