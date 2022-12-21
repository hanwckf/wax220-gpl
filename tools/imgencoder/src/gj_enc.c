#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "aes.h"
#include "imagekey.h"

#ifndef BRCM_CMS_BUILD
#define cmsMem_alloc(a,b) malloc(a)
#define cmsMem_free(a) do {if(a) free(a);}while(0)
#else
#include "cms.h"
#include "cms_util.h"
#include "cms_msg.h"
#include "cms_boardcmds.h"
#include "cms_boardioctl.h"
#endif

#define FILENAME "image.w"
#define ONEBLOCK 128*1024

#define RSA_SIGN_BUF_SIZE 256 /*2048 bit rsa sign size*/
#define RSA_PKCS1_PADDING_SIZE  11
#define RSA_SIGN_ORI_DATA_MAX_SIZE (RSA_SIGN_BUF_SIZE - RSA_PKCS1_PADDING_SIZE)

typedef struct _rsaSignData
{
    char imageHeadDigest[32];
    char plaintextDigest[32];
} RSA_SIGN_DATA;

typedef  struct _image_head
{
    char model[32];        /*model name*/
    char region[32];       /*region*/
    char version[64];      /*version*/
    char dateTime[64];     /*date*/
    char reserved[64];    /*reserved space, if add struct member, please adjust this reserved size to keep the head total size is 512 bytes*/
    char sign[RSA_SIGN_BUF_SIZE];       /*2048 bit rsa sign*/
}__attribute__((__packed__)) IMAGE_HEAD;

typedef  struct _image_tail
{
    char checkSum[4];       /*checkSum*/
}__attribute__((__packed__)) IMAGE_TAIL;

/* Table of CRC-32's of all single-byte values (made by make_crc_table) */
static const unsigned int crc32_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
    0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
    0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
    0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
    0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
    0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
    0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
    0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
    0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
    0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
    0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
    0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
    0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
    0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
    0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
    0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
    0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
    0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
    0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
    0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
    0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
    0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
    0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
    0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
    0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
    0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
    0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
    0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
    0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
    0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
    0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
    0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
    0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
    0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
    0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
    0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
    0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
    0x2d02ef8dL
};

/***************************************************************************
Function Name: get_crc32
Description  : caculate the CRC 32 of the given data.
Parameters   : pdata - array of data.
               size - number of input data bytes.
               crc - either CRC32_INIT_VALUE or previous return value.
Returns      : crc.
****************************************************************************/
unsigned int get_crc32(unsigned char *pdata, unsigned int size)
{
    unsigned int crc = 0;

    while (size-- > 0)
        crc = (crc >> 8) ^ crc32_table[(crc ^ *pdata++) & 0xff];

    return crc;
}

unsigned int calc_single_byte_crc32(char data, unsigned int preCrc)
{
    unsigned int crc = 0;

    crc = (preCrc >> 8) ^ crc32_table[(preCrc ^ data) & 0xff];

    return crc;
}

/******************************************************************************
Function:  load_genupf
Description:  this function generate upgrade package file from image file.
Input:  imagetype:image type:master,agent,olt,onu
        version:the image version
        infile: the image file name
        outfile: out put upgrade package file name

Output:  NONE,
Return:  BOS_OK on success,OTHERS on failure.
Others:  none
******************************************************************************/
int gj_add_image_head_tail(IMAGE_HEAD *pHead, IMAGE_TAIL*pTail, const char* infile, const char * outfile)
{
    FILE *pfin, *pfout;
    int filesize, buffsize;
    unsigned char *buff = NULL;
    int readlen = 0;
    int writelen= 0;
    int writeCrc= 0;
    int ret     = 0;

    pfin = fopen(infile,"rb");

    if (NULL == pfin)
    {
        goto errorhandler;
    }

    pfout = fopen(outfile,"wb+");
    if (NULL == pfout)
    {
        fclose(pfin);
        goto errorhandler;
    }

    /* get the in file size, and malloc */
    fseek(pfin, 0, SEEK_END);
    filesize = ftell(pfin);
    buffsize = sizeof(IMAGE_HEAD) + filesize;
    rewind(pfin);

    buff = (unsigned char *)malloc(buffsize);
    if (NULL == buff)
    {
        printf("filesize is %d, malloc err\r\n", filesize);
        return -1;
    }

    writelen = fwrite(pHead, sizeof(IMAGE_HEAD), 1, pfout);
    if (writelen != 1)
    {
        goto errorhandler;
    }

    memcpy(buff, pHead, sizeof(IMAGE_HEAD));

    readlen = fread(buff + sizeof(IMAGE_HEAD), 1, filesize, pfin);
    {
        writeCrc = get_crc32(buff, readlen + sizeof(IMAGE_HEAD));
        writelen = fwrite(buff + sizeof(IMAGE_HEAD), 1, readlen, pfout);
        if (writelen != readlen)
        {
            printf("miss write in genfile.\n");
            goto errorhandler;
        }
    }

    ret = fseek(pfout, 0, SEEK_END);
    if (0 != ret)
    {
        goto errorhandler;
    }

    pTail->checkSum[0] = (writeCrc >> 24) & 0xFF;
    pTail->checkSum[1] = (writeCrc >> 16) & 0xFF;
    pTail->checkSum[2] = (writeCrc >> 8)  & 0xFF;
    pTail->checkSum[3] = (writeCrc >> 0)  & 0xFF;
    writelen = fwrite(pTail->checkSum, sizeof(IMAGE_TAIL), 1, pfout);
    if (writelen != 1)
    {
        goto errorhandler;
    }

    fclose(pfin);
    fclose(pfout);
    if (buff)
    {
        free(buff);
    }

    return ret;

errorhandler:
    if (pfin)
    {
        fclose(pfin);
    }
    if (pfout)
    {
        fclose(pfout);
    }
    if (buff)
    {
        free(buff);
    }

    return -1;
}


int gj_encode(const char *pOrgBuff,int nOrgSize,char**ppOutBuf,int*pOutSize)
{
    aes_context handler;
    unsigned char szKey[32];
    unsigned char szNor_iv[16];
    int nEncodeSize = 0;
    unsigned char *pEncodeBuf = NULL;

    nEncodeSize = (nOrgSize % 16) > 0 ? (nOrgSize / 16 + 1) * 16 : nOrgSize;
    *pOutSize=nEncodeSize;
    *ppOutBuf=(char*)cmsMem_alloc(*pOutSize, 0);
    if (NULL == *ppOutBuf)
    {
        printf("alloc memory failed %d", *pOutSize);
        return 1;
    }
    pEncodeBuf=(unsigned char*)(*ppOutBuf);
    memcpy(pEncodeBuf, pOrgBuff, nEncodeSize);
    
    memset(szKey, 0, sizeof(szKey));
    memcpy(szKey, KEY_256, strlen(KEY_256) > sizeof(szKey) ? sizeof(szKey) : strlen(KEY_256));
    memset(szNor_iv, 0, sizeof(szNor_iv));
    memcpy(szNor_iv, NOR_IV, strlen(NOR_IV) > sizeof(szNor_iv) ? sizeof(szNor_iv) : strlen(NOR_IV));

    aes_set_key(&handler, szKey, 256);
    aes_cbc_encrypt(&handler, szNor_iv, pEncodeBuf, pEncodeBuf, nEncodeSize);

    return 0;
}

int gj_decode(const char *pInputBuf,int nInputSize,char**ppOutBuf,int*pOutSize)
{
    aes_context handler;
    unsigned char szKey[32];
    unsigned char szNor_iv[16];
    int nEncodeSize = 0;
    unsigned char *pEncodeBuf = NULL;

    nEncodeSize = (nInputSize % 16) > 0 ? (nInputSize / 16 + 1) * 16 : nInputSize;
    *pOutSize=nEncodeSize;
    pEncodeBuf = (unsigned char*)cmsMem_alloc(nEncodeSize, 0);  /* new unsigned char[nEncodeSize]; */
    if(pEncodeBuf == NULL) 
    {
        printf("pEncodeBuf = new char[%d], alloc memory failed\n", nEncodeSize);
        return 1;
    }
    *ppOutBuf = (char *)pEncodeBuf;
    memcpy(pEncodeBuf, pInputBuf, nEncodeSize);

    memset(szKey, 0, sizeof(szKey));
    memcpy(szKey, KEY_256, strlen(KEY_256) > sizeof(szKey) ? sizeof(szKey) : strlen(KEY_256));
    memset(szNor_iv, 0, sizeof(szNor_iv));
    memcpy(szNor_iv, NOR_IV, strlen(NOR_IV) > sizeof(szNor_iv) ? sizeof(szNor_iv) : strlen(NOR_IV));

    aes_set_key(&handler, szKey, 256);
    aes_cbc_decrypt(&handler, szNor_iv, pEncodeBuf, pEncodeBuf, nEncodeSize);

    return 0;
}

#if !defined(BRCM_CMS_BUILD) && !defined(_CFE_)

static int sgCodeSign(IMAGE_HEAD *pImageHead, const char* imgPath, const char* priKeyPath)
{
    int ret = -1;
    int rpipe[2] = {0};
    int wpipe[2] = {0};
    char cmd[1024] = {0};
    FILE *fcmd = NULL;
    RSA_SIGN_DATA sigData;

    pipe(rpipe);
    pipe(wpipe);

    switch (fork())
    {
        case 0:
            close(wpipe[1]);
            close(rpipe[0]);
            dup2(wpipe[0], 0);
            dup2(rpipe[1], 1);
            execlp("openssl", "sha256", "-binary", NULL);
            exit(EXIT_FAILURE);
        case -1:
            perror("imageHeadDigest");
            exit(EXIT_FAILURE);
        default:
            close(rpipe[1]);
            close(wpipe[0]);
            memset(&sigData, 0, sizeof(sigData));
            write(wpipe[1], pImageHead, sizeof(IMAGE_HEAD));
            close(wpipe[1]);
            read(rpipe[0], sigData.imageHeadDigest, sizeof(sigData.imageHeadDigest));
            close(rpipe[0]);
            break;
    }

    snprintf(cmd, sizeof(cmd) - 1, "openssl sha256 -binary %s", imgPath);
    fcmd = popen(cmd, "r");
    if (NULL == fcmd)
    {
        perror("plaintextDigest");
        exit(EXIT_FAILURE);
    }

    fread(sigData.plaintextDigest, 1, sizeof(sigData.plaintextDigest), fcmd);
    pclose(fcmd);

    memset(rpipe, 0, sizeof(rpipe));
    memset(wpipe, 0, sizeof(wpipe));
    pipe(rpipe);
    pipe(wpipe);

    switch (fork())
    {
        case 0:
            close(wpipe[1]);
            close(rpipe[0]);
            dup2(wpipe[0], 0);
            dup2(rpipe[1], 1);
            execlp("openssl", "rsautl", "-sign", "-inkey", priKeyPath, NULL);
            exit(EXIT_FAILURE);
        case -1:
            perror("sign");
            exit(EXIT_FAILURE);
        default:
            close(rpipe[1]);
            close(wpipe[0]);
            write(wpipe[1], &sigData, sizeof(sigData));
            close(wpipe[1]);
            read(rpipe[0], pImageHead->sign, sizeof(pImageHead->sign));
            close(rpipe[0]);
            break;
    }

    return ret;
}

/*************************************************************************************************
./gj_image_aes --encode XXXX  --blocksize XXXXX --region XXX --model XXXX   --sw_version XXXXX
./gj_image_aes --decode XXXX  --blocksize XXXXX 
**************************************************************************************************/
int main(int argc, char **argv)
{
    char* pBuffer = NULL;
    int ret = -1;
    int bufLen = 0;
    char *data;
    int block_count = 0;
    int i = 0;
    int len = 0;
    int filesize = 0;
    int blocksize = ONEBLOCK;
    int encblocksize = 0;
    FILE *fido;
    FILE *fid;
    uint32_t realFilesize = 0;
    uint32_t nRet = 0;

    IMAGE_HEAD image_head;
    IMAGE_TAIL image_tail;
    time_t nowTime;
    char infilename[2048] = {0}, outfilename[2048] = {0};
    char original_name[256] = {0};
    char filename[256] = {0};

    /*char achCmd[512] = {0};*/
    char *pchPath = NULL;

    if (argc < 5)
    {
        printf("argument error!\n");
    }

    fid = fopen(argv[2], "rb");
    if (NULL == fid)
    {
        printf("file:%s error\n", argv[2]);
        return -1;
    }

    strcpy(infilename, argv[2]);
    strcat(infilename, ".enc");
    fido = fopen(infilename, "wb");
    if (NULL == fido)
    {
        printf("open file:%s error\n", infilename);
        fclose(fid);
        return -1;
    }

    if (strcmp(argv[3], "--blocksize")==0)
    {
        blocksize = atoi(argv[4]);
    }
    encblocksize = blocksize ;  /* ((blocksize % 16) > 0 ? (blocksize / 16 + 1) * 16 : blocksize); */

    fseek (fid, 0, SEEK_END);
    filesize = ftell(fid);
    rewind (fid);

    if (0 == strcmp(argv[1], "--encode"))  /* encrypt image */
    {
        block_count = ceil((double)filesize/blocksize);
        data = cmsMem_alloc(blocksize, 0);
        fwrite("encrpted_img",sizeof(char), strlen("encrpted_img"), fido);
        nRet = htonl(filesize);
        fwrite(&nRet, sizeof(nRet), 1, fido);
        nRet = htonl(blocksize);
        fwrite(&nRet, sizeof(nRet), 1, fido);
    }
    else if (0 == strcmp(argv[1], "--decode"))
    {
        filesize -= strlen("encrpted_img");
        filesize -= sizeof(nRet);
        filesize -= sizeof(nRet);
        block_count = ceil((double)filesize/encblocksize);
        data = cmsMem_alloc(encblocksize,0);

        fread(data, sizeof(char), sizeof(IMAGE_HEAD), fid);
        fread(data, sizeof(char), strlen("encrpted_img"), fid);
        fread(data, sizeof(nRet), 1, fid);
        realFilesize = ntohl(*((uint32_t*)data));
        fread(data, sizeof(nRet), 1, fid);
    }

    for (i = 0; i < block_count; i++)
    {
        if (0 == strcmp(argv[1], "--encode"))
        {
            memset(data, 0, encblocksize);
            len = fread(data,sizeof(char), blocksize, fid);
            ret = gj_encode(data,len, &pBuffer, &bufLen);
        }
        else if (0 == strcmp(argv[1], "--decode"))
        {
            memset(data, 0, encblocksize);
            len = fread(data, sizeof(char),encblocksize, fid);
            ret = gj_decode(data, len, &pBuffer, &bufLen);
        }

        if(0 == ret)
        {
            if (0 == strcmp(argv[1], "--encode"))
            {
                fwrite(pBuffer, sizeof(char), bufLen, fido);
            }
            else if (0 == strcmp(argv[1], "--decode"))
            {
                fwrite(pBuffer, sizeof(char), bufLen, fido);
            }
            cmsMem_free(pBuffer);
        }
        else
        {
            printf("crypto error!\n");
        }
    }

    cmsMem_free(data);
    fclose(fido);
    fclose(fid);

    if (0 == strcmp(argv[1],"--encode"))
    {
        memset(&image_head, 0, sizeof(image_head));
        memset(&image_tail, 0, sizeof(image_tail));

        /* add netgear image heaer and tail */
        if (0 == strcmp(argv[5], "--region"))
        {
            strcpy(image_head.region, argv[6]);
        }

        if (0 == strcmp(argv[7], "--model"))
        {
            strcpy(image_head.model, argv[8]);
        }

        if (0 == strcmp(argv[9], "--sw_version"))
        {
            strcpy(image_head.version, argv[10]);
        }

        time(&nowTime);
        sprintf(image_head.dateTime, "%s", asctime(gmtime(&nowTime)));
        image_head.dateTime[strlen(image_head.dateTime) - 1] = '\0';

        pchPath = strrchr(infilename, '/');
        sscanf(strrchr(infilename, '/'), "%[^.]", original_name);
	memset(filename, 0, sizeof(filename));
	strncpy(filename, infilename, pchPath-infilename);
	snprintf(outfilename, sizeof(outfilename) - 1, "%s/%s-%s_64_%s.bin", filename, image_head.model, image_head.version, original_name+1);
	if (0 == strcmp(argv[11], "--output"))
	{
	    strncpy(outfilename, argv[12], sizeof(outfilename));
	}

	if ((argc >= 15) && (0 == strcmp(argv[13], "--prikey")))
	{
	    ret = sgCodeSign(&image_head, argv[2], argv[14]);
	}

	ret = gj_add_image_head_tail(&image_head, &image_tail, infilename, outfilename);

        /*sprintf(achCmd, "rm %s", infilename);*/
        /*system(achCmd);*/
    }
    else if (0 == strcmp(argv[1], "--decode"))
    {
        truncate(infilename, realFilesize);
    }

    return 0;
}
#endif

