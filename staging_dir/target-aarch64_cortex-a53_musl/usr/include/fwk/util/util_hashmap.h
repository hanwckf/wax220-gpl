#ifndef __UTIL_HASHMAP_H__
#define __UTIL_HASHMAP_H__

#include "../fwk.h"


#define UTIL_HASHMAP_SIZE 1024


typedef struct hash_map {
    UINT32 size;
    LIST_ENTRY_T **key;
    LIST_ENTRY_T **value;
} HASH_MAP_T, *pHASH_MAP_T;


typedef void(*hmap_value_free_hook)(void *value);


void hashmap_create(pHASH_MAP_T *hmap, SINT32 size);

void hashmap_destroy(pHASH_MAP_T hmap, hmap_value_free_hook pFreeHook);

void hashmap_insert(pHASH_MAP_T hmap, const char *key, SINT32 keyLen, void *value);

void *hashmap_search(pHASH_MAP_T hmap, const char *key);

void hashmap_delete(pHASH_MAP_T hmap, const char *key, hmap_value_free_hook pFreeHook);

    
#endif /* __UTIL_HASHMAP_H__ */
