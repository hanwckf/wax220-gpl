#ifndef  __HAL_NAND_H__
#define  __HAL_NAND_H__
#include <stdint.h>
#include <mtd/mtd-user.h>
#define TRAFFIC_MTD_NAME                  "Traffic"
int hal_nandGetBlockSize(int *blocksize);
int haL_nandGetMtdInfo(struct mtd_info_user *pmtdInfo);
int  hal_nandWrite(uint64_t start, unsigned char *buff, int len);
int hal_nandRead(uint64_t start, unsigned char *buff, int len);
int hal_nandErase(int start, int erasesize);
#endif