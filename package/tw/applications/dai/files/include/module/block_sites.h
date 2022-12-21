#ifndef __BLOCK_SITES_H__
#define __BLOCK_SITES_H__
#include "json-c/json.h"
#include "json-c/json_inttypes.h"
#include "json-c/json_object.h"
#include "json-c/json_tokener.h"
#include "json-c/json_util.h"


#define BLOCK_SITES_LIST_BUF_SIZE    261120
#define BLOCK_SITES_KEYWORD_MAX     255
#define BLOCK_SITES_OLD_KEYWORDLIST    "block_sites_old_keyword"
#define BLOCK_SITES_IPTABLE_FWD_CHAIN   "block_sites"
#define BLOCK_SITES_IPTABLE_FWD_REJECT_CHAIN   "http_reject"
#define BLOCK_SITES_REJECT_WITH         "http-site-block"
#define BLOCK_SITES_REDIS_LOGGED_KEY    "blocksitelogkey:"
//blocksite的log只第一次访问记录，再次访问不记录。默认1 表示只记录1次不重复记录，设置为0 表示每次访问都记录
#define SHOW_BLOCKSITE_LOG_ONLYONCE     1

typedef struct{
    char keywrod[BUFLEN_128];         //keywrod
} BLOCK_SITES_KEYWORD_LIST_T;

typedef struct{
    char blockoption[BUFLEN_32];
    int  trusted_IP_Enable;
    char cfTrusted_IPAddress[BUFLEN_32];
} BLOCK_SITES_T;


int dai_getBlockSites_endis_Trusted_IP(char *enable, int len);
int dai_getBlockSites_Option(char *option, int len);
int dai_getBlockSites_Trusted_IP(char *ip, int len);
int dai_getBlockSites_KeywordList(BLOCK_SITES_KEYWORD_LIST_T **keywordListRef, int *num);
int dai_getBlockSites_cfg(BLOCK_SITES_T *pBlockSites);
int dai_setBlockSites_cfg(BLOCK_SITES_T *pBlockSites);
int dai_setBlockSites_Keyword(char *keyword);
int dai_delBlockSites_allKeyword();
int dai_delBlocksiteAllredisKey();
#endif
